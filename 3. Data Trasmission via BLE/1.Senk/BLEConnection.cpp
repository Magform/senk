#include "BLEConnection.h"
#include <ArduinoBLE.h>
#include "Configuration.h"

BLEConnection::BLEConnection() : Accelerometer("2000"), Gyroscope("3000"),
    AccX("2001", BLERead | BLENotify), AccY("2002", BLERead | BLENotify), AccZ("2003", BLERead | BLENotify),
    GyroX("3001", BLERead | BLENotify), GyroY("3002", BLERead | BLENotify), GyroZ("3003", BLERead | BLENotify){

    }

int BLEConnection::initialize(){

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

void BLEConnection::send(short aX, short aY, short aZ, short gX, short gY, short gZ){
  AccX.writeValue(aX);
  AccY.writeValue(aY);
  AccZ.writeValue(aZ);
  GyroX.writeValue(gX);
  GyroY.writeValue(gY);
  GyroZ.writeValue(gZ);
  if(debugStatus){
    Serial.println("Data sent via BLE");
  }
}   