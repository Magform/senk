#ifndef BLEConnection_H_
#define BLEConnection_H_
#include <ArduinoBLE.h>

class BLEConnection {
  private:
    BLEService Accelerometer;
    BLEService Gyroscope;
    BLEShortCharacteristic AccX;
    BLEShortCharacteristic AccY;  
    BLEShortCharacteristic AccZ;
    BLEShortCharacteristic GyroX;  
    BLEShortCharacteristic GyroY;
    BLEShortCharacteristic GyroZ;  
  public:
    BLEConnection();
    int initialize();
    void send(short aX, short aY, short aZ, short gX, short gY, short gZ);
};

#endif // BLEConnection_H_