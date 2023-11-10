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
void takeDataSet();
void printDataSet();

Data dataSet[dataPerSet];

void setup() {
  if(debug){
    Serial.begin(115200);
    Serial.print("Initializing ");
  }
  
  BHY2.begin();
  accel.begin();
  gyro.begin();

  if(debug){
    Serial.println(" done!");
  }
}

void loop(){
  static auto lastSet = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    takeDataSet();
    lastSet = millis();
    printDataSet();
  }

  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(){
  for(int i = 0; i<dataPerSet; i++){
    BHY2.update();
    dataSet[i] = Data(accel.x(), accel.y(), accel.z(), gyro.x(), gyro.y(), gyro.z());
    delay(distanceData);
  }
}

void printDataSet(){
  for(int i = 0; i<dataPerSet; i++){
    if(debug){
      const char* toPrint = dataSet[i].toString();
      Serial.println(toPrint);
      delete[] toPrint;
    }
  }
}
