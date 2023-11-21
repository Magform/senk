#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>

//Configuration
#include "Configuration.h"

//Util
#include "Data.h"
#if DATA_SAVER
#include "DataSaver.h"
#endif
#if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
#include "BLECommunication.h"
#endif
#if SEND_DATASET_THREAD
#include <mbed.h>
#include <rtos.h>
#include <platform/Callback.h>
#endif

//File system
#if DATA_SAVER
mbed::LittleFileSystem fs(USER_ROOT);
DataSaver dataSaver;
#endif

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet(Data dataSet[], int length);

#if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
BLECommunication BLEcom;
#endif

#if !SEND_DATASET && SEND_DATASET_THREAD
rtos::Semaphore dataAviableForBLE(0);
rtos::Semaphore dataSentForBLE(1);
rtos::Thread BLEsending;
#endif

void setup() {
  Serial.begin(115200);

  debugPrint("Initializing ");

  #if DATA_SAVER
    dataSaver.initialize(SAVE_FILE_NAME);
    #if DELETE_FILE
    dataSaver.format();
    #endif
  #endif

  BHY2.begin();
  accel.begin();
  gyro.begin();
  
  #if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
  BLEcom.initialize();
  #endif

  debugPrint(" done!");
}

void loop(){
  static auto lastSet = millis() - DISTANCE_BETWEEN_SET;
  static auto lastScan = millis();
  BHY2.update();
  
  Data dataSet[std::min(MAX_DATASET_DIMENSION, std::max(DATA_TO_SCAN, DATA_PER_SET))];

  if (millis() - lastSet >= DISTANCE_BETWEEN_SET){
    int toSend = 0;
    for(int i=0; i<DATA_PER_SET/MAX_DATASET_DIMENSION; i++){
      takeDataSet(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      #if SEND_DATASET
      BLEcom.send(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      #endif
      #if !SEND_DATASET && SEND_DATASET_THREAD
      dataSentForBLE.acquire();
      toSend = std::min(MAX_DATASET_DIMENSION, DATA_PER_SET);
      dataAviableForBLE.release();
      BLEsending.start(mbed::callback([&BLEcom, &dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE]() {
        BLEcom.send(dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE);
      }));
      #endif
      #if DATA_SAVER_STATUS
      dataSaver.saveData(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      #endif
    }
    takeDataSet(dataSet, DATA_PER_SET%MAX_DATASET_DIMENSION);
    lastSet = millis();
    #if SEND_DATASET
    BLEcom.send(dataSet, DATA_PER_SET%MAX_DATASET_DIMENSION);
    #endif
    #if !SEND_DATASET && SEND_DATASET_THREAD
    dataSentForBLE.acquire();
    toSend = DATA_PER_SET%MAX_DATASET_DIMENSION;
    dataAviableForBLE.release();
    BLEsending.start(mbed::callback([&BLEcom, &dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE]() {
      BLEcom.send(dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE);
    }));
    #endif
    #if DATA_SAVER_STATUS
    dataSaver.saveData(dataSet, DATA_PER_SET%MAX_DATASET_DIMENSION);
    #endif
  }

  #if DATA_SAVER_STATUS && DATA_SENDER
  if(millis() - lastScan >= SCAN_TIME){;
    for(int i=0; i<DATA_TO_SCAN/MAX_DATASET_DIMENSION; i++){
      dataSaver.getData(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_TO_SCAN));
      BLEcom.send(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_TO_SCAN));
    }
    dataSaver.getData(dataSet, DATA_PER_SET%MAX_DATASET_DIMENSION);
    BLEcom.send(dataSet, DATA_PER_SET%MAX_DATASET_DIMENSION);
    lastScan = millis();
  }
  #endif
  
  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(Data dataSet[], int length){
  for(int i = 0; i<length; i++){
    BHY2.update();
    dataSet[i] = Data(accel.x(), accel.y(), accel.z(), gyro.x(), gyro.y(), gyro.z());
    #if DEBUG_STATUS
      const char* toPrint = dataSet[i].toString();
      debugPrint(toPrint);
      delete[] toPrint;
    #endif
    delay(DATA_DISTANCE);
  }
}