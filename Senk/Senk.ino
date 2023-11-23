#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>

//Configuration
#include "Configuration.h"

//Util
#include "Data.h"
#if DATA_SAVER || DATA_SAVER_KEEP_OPEN
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
#if DATA_SAVER || DATA_SAVER_KEEP_OPEN
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
int toSend = 0;
#endif

void setup() {
  Serial.begin(115200);

  debugPrint("Initializing ");

  #if DATA_SAVER || DATA_SAVER_KEEP_OPEN
    dataSaver.initialize(SAVE_FILE_NAME);
    #if DELETE_FILE
    dataSaver.format();
    #endif
  #endif

  BHY2.begin();
  accel.begin();
  gyro.begin();
  while(accel.x() == 0 || accel.y() == 0 || accel.z() == 0){BHY2.update();} // wait for sensor to start
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
    int totalIteration = DATA_PER_SET/MAX_DATASET_DIMENSION;
    for(int i=0; i<=totalIteration; i++){
      
      int dataSize = (i == totalIterations) ? DATA_PER_SET%MAX_DATASET_DIMENSION : MAX_DATASET_DIMENSION;

      takeDataSet(dataSet, dataSize);
      lastSet = millis();
      
      #if SEND_DATASET
      BLEcom.send(dataSet, dataSize);
      #endif
      
      #if !SEND_DATASET && SEND_DATASET_THREAD
      dataSentForBLE.acquire();
      toSend = dataSize;
      dataAviableForBLE.release();
      BLEsending.start(mbed::callback([&BLEcom, &dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE]() {
        BLEcom.send(dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE);
      }));
      #endif

      #if DATA_SAVER
      dataSaver.saveData(dataSet, dataSize);
      #endif
      
      #if DATA_SAVER_KEEP_OPEN && !DATA_SAVER
      dataSaver.saveDataKeepOpen(dataSet, dataSize, DATA_PER_ITERATION);
      #endif
    }
  }

  #if ( DATA_SAVER || DATA_SAVER_KEEP_OPEN ) && DATA_SENDER
  if(millis() - lastScan >= SCAN_TIME){;
    int totalIteration = DATA_TO_SCAN/MAX_DATASET_DIMENSION
    for(int i=0; i<totalIteration; i++){
      int dataSize = (i == totalIterations) ? (DATA_TO_SCAN % MAX_DATASET_DIMENSION) : MAX_DATASET_DIMENSION;
      dataSaver.getData(dataSet, dataSize);
      BLEcom.send(dataSet, dataSize);
    }
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