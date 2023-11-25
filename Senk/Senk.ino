#include <Arduino.h>
#include <Nicla_System.h>
#include <Arduino_BHY2.h>
#include <mbed.h>
#include <rtos.h>
#include <platform/Callback.h>

#include "Configuration.h"
#include "Data.h"
#include "util.h"

//Initialize data saving
#if DATA_SAVER || DATA_SAVER_KEEP_OPEN
#include "DataSaver.h"
#include <LittleFileSystem.h>
mbed::LittleFileSystem fs(USER_ROOT);
DataSaver dataSaver;
#endif

//Initialize BLE communication
#if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
#include "BLECommunication.h"
BLECommunication BLECom;
#endif

//Initialize sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

Data dataSet[std::min(MAX_DATASET_DIMENSION, std::max(DATA_TO_SCAN, DATA_PER_SET))];

//Declaration of utility function
long dataManager(Data dataSet[]);
#if ( DATA_SAVER || DATA_SAVER_KEEP_OPEN ) && DATA_SENDER
long sendScanData(Data dataSet[]);
#endif

void setup(){
  Serial.begin(115200);
  debugPrint("Initializing");

  #if DATA_SAVER || DATA_SAVER_KEEP_OPEN
    dataSaver.initialize(SAVE_FILE_NAME);
    #if DELETE_FILE
    dataSaver.format();
    #endif
  #endif
  BHY2.begin();
  accel.begin();
  gyro.begin();
  //wait for sensor to start
  while(accel.x() == 0 || accel.y() == 0 || accel.z() == 0 || gyro.x() == 0 || gyro.y() == 0 || gyro.z() == 0){BHY2.update();}

  #if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
  BLEcom.initialize();
  #endif

  debugPrint("done!");
}

void loop(){
  BHY2.update();
  static long lastDataSet = -DISTANCE_BETWEEN_SET;
  static long lastFileScan = 0;
  if(millis()-lastDataSet>=DISTANCE_BETWEEN_SET){
    lastDataSet = dataManager(dataSet);
  }
  #if ( DATA_SAVER || DATA_SAVER_KEEP_OPEN ) && DATA_SENDER
  if(millis()-lastFileScan>=SCAN_TIME){
    lastFileScan = sendScanData(dataSet); 
  }
  #endif;
}


//Definition of utility function
long dataManager(Data dataSet[]){
  int totalIteration = DATA_PER_SET / MAX_DATASET_DIMENSION;
  long lastScan = millis();
  for (int i = 0; i <= totalIteration; i++) {
    int dataSize = (i == totalIteration) ? (DATA_PER_SET % MAX_DATASET_DIMENSION) : MAX_DATASET_DIMENSION;
      
    takeDataSet(dataSet, dataSize, &accel, &gyro);
    lastScan = millis();
    #if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
    sendDataToBLE(dataSet, dataSize, &BLEcom);
    #endif
    #if DATA_SAVER || DATA_SAVER_KEEP_OPEN
    sendDataToSaver(dataSet, dataSize, &dataSaver);
    #endif
  }
  return lastScan;
}

#if ( DATA_SAVER || DATA_SAVER_KEEP_OPEN ) && DATA_SENDER
long sendScanData(Data dataSet[]){
  long lastScan = millis();
  int totalIteration = DATA_TO_SCAN / MAX_DATASET_DIMENSION;

  for (int i = 0; i <= totalIteration; i++) {
    int dataSize = (i == totalIteration) ? (DATA_TO_SCAN % MAX_DATASET_DIMENSION) : MAX_DATASET_DIMENSION;
      dataSaver.getData(dataSet, dataSize);
      lastScan = millis();
      BLEcom.send(dataSet, dataSize);
    }
  }
  return lastScan;
}
#endif