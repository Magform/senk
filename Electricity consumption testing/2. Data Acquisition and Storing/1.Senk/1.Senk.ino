#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>

#include "Data.h"
#include "Configuration.h"

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet(Data dataSet[], int length);
void printDataSet(Data dataSet[], int length);


void setup() {
  #if DEBUG_STATUS
  Serial.begin(115200);
  #endif
  debugPrint("Initializing ");
  
  BHY2.begin();
  accel.begin();
  gyro.begin();

  debugPrint(" done!");

}

void loop(){
  static auto lastSet = millis();
  BHY2.update();

  Data dataSet[DATA_PER_SET];

  if (millis() - lastSet >= DISTANCE_BETWEEN_SET){
    takeDataSet(dataSet, DATA_PER_SET);
    lastSet = millis();
    printDataSet(dataSet, DATA_PER_SET);
  }

  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(Data dataSet[], int length){
  for(int i = 0; i<length; i++){
    BHY2.update();
    dataSet[i] = Data(accel.x(), accel.y(), accel.z(), gyro.x(), gyro.y(), gyro.z());
    delay(DATA_DISTANCE);
  }
}

void printDataSet(Data dataSet[], int length){
  for(int i = 0; i<length; i++){
    const char* toPrint = dataSet[i].toString();
    debugPrint(toPrint);
    delete[] toPrint;
  }
}
