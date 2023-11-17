#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>

//Configuration
#include "Configuration.h"

//Util
#include "BLECommunication.h"

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet(Data dataSet[], int length);

BLECommunication BLEcom;

void setup() {
  Serial.begin(115200);

  debugPrint("Initializing ");

  BHY2.begin();
  accel.begin();
  gyro.begin();
  
  BLEcom.initialize();

  debugPrint(" done!");
}

void loop(){
  static auto lastSet = millis() - DISTANCE_BETWEEN_SET;
  static auto lastScan = millis();
  BHY2.update();
  
  Data dataSet[DATA_PER_SET];

  if (millis() - lastSet >= DISTANCE_BETWEEN_SET){
    takeDataSet(dataSet, DATA_PER_SET);
    lastSet = millis();
    BLEcom.send(dataSet, DATA_PER_SET);
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