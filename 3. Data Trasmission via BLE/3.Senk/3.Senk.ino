#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"

#include "Configuration.h"
#include "BLEConnection.h"
#include "Data.h"

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

void takeDataSetAndSend();

BLEConnection BLECon;
Data dataSet[std::min(200, dataPerSet)];

void setup() {
  Serial.begin(115200);
  if(debugStatus){
    Serial.print("Initializing ");
  }

  BHY2.begin();
  accel.begin();
  gyro.begin();

  BLECon.initialize();

  if(debugStatus){
    Serial.println(" done!");
  }
}

void loop(){
  static auto lastSet = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    for(int i=0; i<(1+dataPerSet%200); i++){
      takeDataSet();
      lastSet = millis();
      BLECon.send(dataSet, std::min(200, dataPerSet));
    }
  }
  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(){
  for(int i = 0; i<std::min(200, dataPerSet); i++){
    BHY2.update();
    dataSet[i] = Data(accel.x(), accel.y(), accel.z(), gyro.x(), gyro.y(), gyro.z());
    if(debugStatus){
      const char* toPrint = dataSet[i].toString();
      Serial.println(toPrint);
      delete[] toPrint;
    }
    delay(distanceData);
  }
}