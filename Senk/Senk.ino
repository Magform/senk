#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>
#include <vector>

#include "Configuration.h"

//Bluetooth Service and characteristics
BLEService Accelerometer("1101");
BLEService Gyroscope("1102");
BLEShortCharacteristic AccX("2101", BLERead | BLENotify);
BLEShortCharacteristic AccY("2102", BLERead | BLENotify);  
BLEShortCharacteristic AccZ("2103", BLERead | BLENotify);
BLEShortCharacteristic GyroX("3101", BLERead | BLENotify);  
BLEShortCharacteristic GyroY("3102", BLERead | BLENotify);
BLEShortCharacteristic GyroZ("3103", BLERead | BLENotify);  

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
int initializeBLE();
void sendDataBLE();
void takeDataSet();
void sendDataSet_BLE();

short dataSet[dataPerSet][6];

void setup() {
  if(debug){
    Serial.begin(115200);
  }

  BHY2.begin();
  accel.begin();
  gyro.begin();

  initializeBLE();
}

void loop(){
  BLEDevice central = BLE.central();
  static auto lastSet = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    lastSet = millis();
    takeDataSet();
    sendDataSet_BLE();
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
  BLE.setAdvertisedService(Accelerometer);
  Accelerometer.addCharacteristic(AccX);
  Accelerometer.addCharacteristic(AccY);
  Accelerometer.addCharacteristic(AccZ);
  BLE.setAdvertisedService(Gyroscope);
  Gyroscope.addCharacteristic(GyroX);
  Gyroscope.addCharacteristic(GyroY);
  Gyroscope.addCharacteristic(GyroZ);
  BLE.addService(Accelerometer);
  BLE.addService(Gyroscope);
  BLE.advertise();
  
  return 1;
}

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(){
  for(int i = 0; i<dataPerSet; i++){
    BHY2.update();

    dataSet[i][0]=accel.x();
    dataSet[i][1]=accel.y();
    dataSet[i][2]=accel.z();
    dataSet[i][3]=gyro.x();
    dataSet[i][4]=gyro.y();
    dataSet[i][5]=gyro.z();
    delay(distanceData);
  }
}

//Send data from accelerometer and gyroscopo on BLE
void sendDataBLE(){
  AccX.writeValue(accel.x());
  AccY.writeValue(accel.y());
  AccZ.writeValue(accel.z());

  GyroX.writeValue(gyro.x());
  GyroY.writeValue(gyro.y());
  GyroZ.writeValue(gyro.z());
}

//Send data from dataset to BLE
void sendDataSet_BLE(){
  for(int i = 0; i<dataPerSet; i++){
    AccX.writeValue(dataSet[i][0]);
    AccY.writeValue(dataSet[i][1]);
    AccZ.writeValue(dataSet[i][2]);
    GyroX.writeValue(dataSet[i][3]);
    GyroY.writeValue(dataSet[i][4]);
    GyroZ.writeValue(dataSet[i][5]);
    delay(1);
  }
}
