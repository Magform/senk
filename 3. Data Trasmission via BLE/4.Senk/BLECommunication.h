#ifndef BLEConnection_H_
#define BLEConnection_H_
#include <ArduinoBLE.h>

#include "Data.h"

class BLECommunication {
  private:
    BLEService DataSend;
    BLECharacteristic Accelerometer;
    BLECharacteristic Gyroscope;
  public:
    BLECommunication();
    int initialize();
    int send(short aX, short aY, short aZ, short gX, short gY, short gZ);
    int send(Data toSend);
    void send(Data dataSet[], int length);
};

#endif // BLEConnection_H_