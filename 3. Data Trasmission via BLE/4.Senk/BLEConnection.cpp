#include "BLEConnection.h"
#include <ArduinoBLE.h>
#include "Configuration.h"

BLEConnection::BLEConnection() : DataSend("1000"),
    Accelerometer("1001", BLERead | BLENotify, 3*sizeof(short)), Gyroscope("1002", BLERead | BLENotify, 3*sizeof(short)){

    }

int BLEConnection::initialize(){

  if(!BLE.begin()) {
    return 0;
  }

  BLE.setLocalName("Senk");
  BLE.setAdvertisedService("DataSend");
  DataSend.addCharacteristic(Accelerometer);
  DataSend.addCharacteristic(Gyroscope);
  BLE.addService(DataSend);
  BLE.advertise();
  
  return 1;
}

void BLEConnection::send(short aX, short aY, short aZ, short gX, short gY, short gZ){
  if(aX != -32768 & aY != -32768 & aZ != -32768 & gX != -32768 & gY != -32768 & gZ != -32768){
      short accelerometerValues[3] = {gX, gY, gZ};
      short gyroscopeValues[3] = {gX, gY, gZ};
      Accelerometer.writeValue(accelerometerValues, sizeof(accelerometerValues));
      Gyroscope.writeValue(gyroscopeValues, sizeof(gyroscopeValues));
    if(debugStatus){
      Serial.println("Data sent via BLE");
    }
  }else{
    if(debugStatus){
      Serial.println("Invalid data");
    }
  }
}   

void BLEConnection::send(Data toSend){
  send(toSend.getAccelerometerX(), toSend.getAccelerometerY(), toSend.getAccelerometerZ(), toSend.getGyroscopeX(), toSend.getGyroscopeY(), toSend.getGyroscopeZ());
}

void BLEConnection::send(Data dataSet[], int length){
  for(int i=0; i<length; i++){
    send(dataSet[i]);
  }
  if(debugStatus){
    Serial.println("DataSet sent");
  }
}

