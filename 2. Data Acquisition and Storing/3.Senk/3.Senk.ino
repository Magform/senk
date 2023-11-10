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
void takeDataSet(int);

Data dataSet[std::min(50, dataPerSet)];
int toRepeat = dataPerSet%50 + 1;

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
    for(int i=0; i<toRepeat; i++){
      takeDataSet(std::min(50, dataPerSet));
      lastSet = millis();
      dataSaver.saveData(dataSet, dataPerSet);
    }
  }

  if(millis() - lastPrint >= printFile){
    dataSaver.printData();
    lastPrint = millis();
  }

  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(int length){
  for(int i = 0; i<length; i++){
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