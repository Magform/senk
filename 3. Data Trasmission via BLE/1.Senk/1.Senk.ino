#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>

#include "Configuration.h"

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
void takeDataSetAndSend();

void setup() {
  Serial.begin(115200);
  if(debug){
    Serial.print("Initializing ");
  }

  BHY2.begin();
  accel.begin();
  gyro.begin();

  initializeBLE();

  if(debug){
    Serial.println(" done!");
  }
}

void loop(){
  static auto lastSet = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    lastSet = millis();
    takeDataSetAndSend();
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

//Send data from dataset to BLE
void sendData_BLE(short aX, short aY, short aZ, short gX, short gY, short gZ){
  AccX.writeValue(aX);
  AccY.writeValue(aY);
  AccZ.writeValue(aZ);
  GyroX.writeValue(gX);
  GyroY.writeValue(gY);
  GyroZ.writeValue(gZ);
  if(debug){
    Serial.println("Data sent via BLE");
  }
}   

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSetAndSend(){
  for(int i = 0; i<dataPerSet; i++){
    BHY2.update();
    short aX = accel.x();
    short aY = accel.y();
    short aZ = accel.z();
    short gX = gyro.x(); 
    short gY = gyro.y();
    short gZ = gyro.z();
    sendData_BLE(aX, aY, aZ, gX, gY, gZ);
    if(debug){
      Serial.print("Accelerometer (X, Y, Z): (");
      Serial.print(aX);
      Serial.print(", ");
      Serial.print(aY);
      Serial.print(", ");
      Serial.print(aZ);
      Serial.print("); Gyroscope (X, Y, Z): (");
      Serial.print(gX);
      Serial.print(", ");
      Serial.print(gY);
      Serial.print(", ");
      Serial.print(gZ);
      Serial.println(")");
    }
    delay(distanceData);
  }
}
