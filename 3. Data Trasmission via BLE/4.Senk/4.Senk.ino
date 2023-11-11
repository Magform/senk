#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <LittleFileSystem.h>

#include "Configuration.h"
#include "Data.h"
#include "DataSaver.h"
#include "BLEConnection.h"

//File system
mbed::LittleFileSystem fs(userRoot);

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
void takeDataSet(int);

DataSaver dataSaver;
BLEConnection BLEcon;

void setup() {
  Serial.begin(115200);
  if(debugStatus){
    Serial.print("Initializing ");
  }

  dataSaver.begin(save_File_Name);
  dataSaver.fileDelete();
  BHY2.begin();
  accel.begin();
  gyro.begin();
  BLEcon.initialize();

  if(debugStatus){
    Serial.println(" done!");
  }
}

void loop(){
  static auto lastSet = millis()-distanceBetweenSet;
  static auto lastSent = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    Data dataSet[std::min(maxDataSetDimension, dataPerSet)];
    for(int i=0; i<(1+dataPerSet/maxDataSetDimension); i++){
      takeDataSet(dataSet, std::min(maxDataSetDimension, dataPerSet));
      lastSet = millis();
      dataSaver.saveData(dataSet, std::min(maxDataSetDimension, dataPerSet));
    }
  }

  if(millis() - lastSent >= sendTime){;
    for(int i=0; i<(1+dataToSend/maxDataSetDimension); i++){
      Data* dataSet = dataSaver.getData(std::min(maxDataSetDimension, dataToSend));
      BLEcon.send(dataSet, std::min(maxDataSetDimension, dataToSend));
      delete[] dataSet;
    }
  }

  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(Data dataSet[], int length){
  for(int i = 0; i<length; i++){
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