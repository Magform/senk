#include "BLECommunication.h"
#include <ArduinoBLE.h>
#include <rtos.h>
#include "Configuration.h"

BLECommunication::BLECommunication() : DataSend(SERVICE_UUID),
    Accelerometer(ACCELEROMETER_UUID, BLERead | BLENotify, 3*sizeof(short)), Gyroscope(GYROSCOPE_UUID, BLERead | BLENotify, 3*sizeof(short)){

    }

int BLECommunication::initialize(){

  if(!BLE.begin()) {
    debugPrint("Bluetooth initialization failed");
    return -1;
  }

  BLE.setLocalName("Senk");
  BLE.setAdvertisedService(DataSend);
  DataSend.addCharacteristic(Accelerometer);
  DataSend.addCharacteristic(Gyroscope);
  BLE.addService(DataSend);
  BLE.advertise();
  debugPrint("BLE configured");

  return 0;
}

int BLECommunication::send(short aX, short aY, short aZ, short gX, short gY, short gZ){
  if (aX != -32768 && aY != -32768 && aZ != -32768 && gX != -32768 && gY != -32768 && gZ != -32768) {
      short accelerometerValues[3] = {aX, aY, aZ};
      short gyroscopeValues[3] = {gX, gY, gZ};
      Accelerometer.writeValue(accelerometerValues, sizeof(accelerometerValues));
      Gyroscope.writeValue(gyroscopeValues, sizeof(gyroscopeValues));
      debugPrint("Data sent via BLE");
      return 0;
  } else {
    debugPrint("Data is invalid");
    return -1;
  }
}

int BLECommunication::send(Data toSend){
  return send(toSend.getAccelerometerX(), toSend.getAccelerometerY(), toSend.getAccelerometerZ(), toSend.getGyroscopeX(), toSend.getGyroscopeY(), toSend.getGyroscopeZ());
}

void BLECommunication::send(const Data dataSet[], int length){
  for(int i=0; i<length; i++){
    send(dataSet[i]);
  }
  debugPrint("DataSet sent");
}

void BLECommunication::send(const Data dataSet[], int* length, rtos::Semaphore *dataAviable, rtos::Semaphore *dataSent){
  while(1){
    dataAviable->acquire();
    for(int i=0; i<*length; i++){
      send(dataSet[i]);
    }
    debugPrint("DataSet sent");
    dataSent->release();
  }
}
