#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>
#include <BlockDevice.h>
#include <Dir.h>
#include <File.h>
#include <FileSystem.h>
#include <LittleFileSystem.h>
#include <mbed.h>
#include <FileHandle.h>


#include "Configuration.h"
#include "Data.h"
#include "DataSaver.h"

//File system
mbed::BlockDevice* spif;
mbed::LittleFileSystem fs(userRoot);

//Bluetooth Service and characteristics
BLEService Accelerometer("2000");
BLEService Gyroscope("3000");
BLEShortCharacteristic AccX("2001", BLERead | BLENotify);
BLEShortCharacteristic AccY("2002", BLERead | BLENotify);  
BLEShortCharacteristic AccZ("2003", BLERead | BLENotify);
BLEShortCharacteristic GyroX("3001", BLERead | BLENotify);  
BLEShortCharacteristic GyroY("3002", BLERead | BLENotify);
BLEShortCharacteristic GyroZ("3003", BLERead | BLENotify);  

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
int initializeBLE();
void sendDataBLE();
void takeDataSet();
void sendDataSet_BLE();


Data dataSet[dataPerSet];
DataSaver dataSaver;

void setup() {
  if(debug){
    Serial.begin(115200);
    Serial.print("Initializing ");
  }

  dataSaver.begin(save_File_Name);
  initializeBLE();
  
  BHY2.begin();
  accel.begin();
  gyro.begin();

  if(debug){
    Serial.println(" done!");
  }
}

void loop(){
  BLEDevice central = BLE.central();
  static auto lastSet = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    lastSet = millis();
    takeDataSet();
    dataSaver.saveData(dataSet, dataPerSet);
    sendDataSet_BLE();
    dataSaver.printData();
  }

  delay(1);
}

//Function definition

//Inizialize Bluetooth with Name, Service and all Service Characteristic
int initializeBLE(){

  if(!BLE.begin()) {
    return 0;
  }

  BLE.setLocalName("Senk");
  BLE.setAdvertisedService("Accelerometer");
  Accelerometer.addCharacteristic(AccX);
  Accelerometer.addCharacteristic(AccY);
  Accelerometer.addCharacteristic(AccZ);
  BLE.setAdvertisedService("Gyroscope");
  Gyroscope.addCharacteristic(GyroX);
  Gyroscope.addCharacteristic(GyroY);
  Gyroscope.addCharacteristic(GyroZ);
  BLE.addService(Accelerometer);
  BLE.addService(Gyroscope);
  BLE.advertise();
  
  return 1;
}

int initializeFileSystem(){
  spif = mbed::BlockDevice::get_default_instance();
  spif->init();

  // Mount the filesystem
  int err = fs.mount(spif);
  if (err) {
    err = fs.reformat(spif);
    if(debug){
      Serial.print("Error mounting file system: ");
      Serial.println(err);
    }
    while (true){
      ;
    }
  }
}

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

//Send data from dataset to BLE
void sendDataSet_BLE(){
  for(int i = 0; i<dataPerSet; i++){
    AccX.writeValue(dataSet[i].getAccelerometerX());
    AccY.writeValue(dataSet[i].getAccelerometerY());
    AccZ.writeValue(dataSet[i].getAccelerometerZ());
    GyroX.writeValue(dataSet[i].getGyroscopeX());
    GyroY.writeValue(dataSet[i].getGyroscopeY());
    GyroZ.writeValue(dataSet[i].getGyroscopeZ());
    delay(1);
  }
}
