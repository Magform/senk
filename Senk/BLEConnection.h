#ifndef BLEConnection_H_
#define BLEConnection_H_
#include <ArduinoBLE.h>

#include "Data.h"

class BLEConnection {
  private:
    BLEService DataSend;
    BLECharacteristic Accelerometer;
    BLECharacteristic Gyroscope;
  public:
    BLEConnection();
    int initialize();
    void send(short aX, short aY, short aZ, short gX, short gY, short gZ);
    void send(Data dataSet[], int length);
    void send(Data toSend);
};

#endif // BLEConnection_H_