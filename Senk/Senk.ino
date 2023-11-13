#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>

//Configuration
#include "Configuration.h"

//Util
#include "Data.h"
#if DATA_SAVER_STATUS
#include "DataSaver.h"
#endif
#if SEND_DATASET || DATA_SENDER
#include "BLECommunication.h"
#endif

//File system
#if DATA_SAVER_STATUS
mbed::LittleFileSystem fs(USER_ROOT);
DataSaver dataSaver;
#endif

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet(int);

#if SEND_DATASET || DATA_SENDER
BLECommunication BLEcon;
#endif

void setup() {
  Serial.begin(115200);

  debugPrint("Initializing ");

  #if DATA_SAVER_STATUS
    dataSaver.begin(SAVE_FILE_NAME);
    #if DELETE_FILE
    dataSaver.fileDelete();
    #endif
  #endif

  BHY2.begin();
  accel.begin();
  gyro.begin();
  
  #if SEND_DATASET || DATA_SENDER
  BLEcon.initialize();
  #endif

  debugPrint(" done!");
}

void loop(){
  static auto lastSet = millis() - DISTANCE_BETWEEN_SET;
  static auto lastScan = millis();
  BHY2.update();
  
  if (millis() - lastSet >= DISTANCE_BETWEEN_SET){
    Data dataSet[std::min(MAX_DATASET_DIMENSION, DATA_PER_SET)];
    for(int i=0; i<(1+DATA_PER_SET/MAX_DATASET_DIMENSION); i++){
      takeDataSet(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      lastSet = millis();
      #if DATA_SAVER_STATUS
      dataSaver.saveData(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      #endif
      #if SEND_DATASET
        BLEcon.send(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      #endif
    }
  }

  #if DATA_SAVER_STATUS && DATA_SENDER
  if(millis() - lastScan >= SCAN_TIME){;
    for(int i=0; i<(1+DATA_TO_SCAN/MAX_DATASET_DIMENSION); i++){
      Data* dataSet = dataSaver.getData(std::min(MAX_DATASET_DIMENSION, DATA_TO_SCAN));
      BLEcon.send(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_TO_SCAN));
      lastScan = millis();
      delete[] dataSet;
    }
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