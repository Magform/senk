#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>

//Configuration
#include "Configuration.h"

//Util
#include "Data.h"
#include "DataSaver.h"


//File system
mbed::LittleFileSystem fs(USER_ROOT);
DataSaver dataSaver;

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet(Data dataSet[], int length);

void setup() {
  Serial.begin(115200);

  debugPrint("Initializing ");

  dataSaver.initialize(SAVE_FILE_NAME);
  #if DELETE_FILE
  dataSaver.format();
  #endif

  BHY2.begin();
  accel.begin();
  gyro.begin();

  debugPrint(" done!");
}

void loop(){
  static auto lastSet = millis() - DISTANCE_BETWEEN_SET;
  static auto lastScan = millis();
  BHY2.update();
  
  Data dataSet[std::min(MAX_DATASET_DIMENSION, DATA_PER_SET)];

  if (millis() - lastSet >= DISTANCE_BETWEEN_SET){
    for(int i=0; i<(1+DATA_PER_SET/MAX_DATASET_DIMENSION); i++){
      takeDataSet(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
      lastSet = millis();
      dataSaver.saveData(dataSet, std::min(MAX_DATASET_DIMENSION, DATA_PER_SET));
    }
    #if PRINT_FILE
    dataSaver.printFile();
    #endif
  }
  
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