#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>


#include "Configuration.h"
#include "Data.h"
#include "DataSaver.h"

//File system
mbed::LittleFileSystem fs(userRoot);

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet();

Data dataSet[dataPerSet];
DataSaver dataSaver;

void setup() {
  Serial.begin(115200);
  if(debug){
    Serial.print("Initializing ");
  }

  dataSaver.begin(save_File_Name);
  dataSaver.fileDelete();

  BHY2.begin();
  accel.begin();
  gyro.begin();

  if(debug){
    Serial.println(" done!");
  }
}

void loop(){
  static auto lastSet = millis()-distanceBetweenSet;
  static auto lastPrint = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    lastSet = millis();
    takeDataSet();
    dataSaver.saveData(dataSet, dataPerSet);
  }

  if(millis() - lastPrint >= printFile){
    dataSaver.printData();
  }

  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(){
  for(int i = 0; i<dataPerSet; i++){
    BHY2.update();
    dataSet[i] = Data(accel.x(), accel.y(), accel.z(), gyro.x(), gyro.y(), gyro.z());
    if(debug){
      const char* toPrint = dataSet[i].toString();
      Serial.println(toPrint);
      delete[] toPrint;
    }
    delay(distanceData);
  }
}