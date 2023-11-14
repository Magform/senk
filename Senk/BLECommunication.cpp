#include "BLECommunication.h"
#include <ArduinoBLE.h>
#include "Configuration.h"

BLECommunication::BLECommunication() : DataSend("1000"),
    Accelerometer("1001", BLERead | BLENotify, 3*sizeof(short)), Gyroscope("1002", BLERead | BLENotify, 3*sizeof(short)){

    }

int BLECommunication::initialize(){

  if(!BLE.begin()) {
    debugPrint("Bluetooth initialization failed");
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

int BLECommunication::send(short aX, short aY, short aZ, short gX, short gY, short gZ){
  if(aX != -32768 & aY != -32768 & aZ != -32768 & gX != -32768 & gY != -32768 & gZ != -32768){
      short accelerometerValues[3] = {gX, gY, gZ};
      short gyroscopeValues[3] = {gX, gY, gZ};
      Accelerometer.writeValue(accelerometerValues, sizeof(accelerometerValues));
      Gyroscope.writeValue(gyroscopeValues, sizeof(gyroscopeValues));
      debugPrint("Data sent via BLE");
      return 0;
  }else{
    debugPrint("Data is invalid");
    return -1;
  }
}   

int BLECommunication::send(Data toSend){
  return send(toSend.getAccelerometerX(), toSend.getAccelerometerY(), toSend.getAccelerometerZ(), toSend.getGyroscopeX(), toSend.getGyroscopeY(), toSend.getGyroscopeZ());
}

void BLECommunication::send(Data dataSet[], int length){
  for(int i=0; i<length; i++){
    send(dataSet[i]);
  }
  debugPrint("DataSet sent");
}
