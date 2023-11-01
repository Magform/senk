#include "Data.h"

Data::Data()
    : accelerometerX(-32768), accelerometerY(-32768), accelerometerZ(-32768),
      gyroscopeX(-32768), gyroscopeY(-32768), gyroscopeZ(-32768) {

}

Data::Data(short accelX, short accelY, short accelZ, short gyroX, short gyroY, short gyroZ)
    : accelerometerX(accelX), accelerometerY(accelY), accelerometerZ(accelZ),
      gyroscopeX(gyroX), gyroscopeY(gyroY), gyroscopeZ(gyroZ) {
  }

short Data::getAccelerometerX() const {
  return accelerometerX;
}

short Data::getAccelerometerY() const {
  return accelerometerY;
}

short Data::getAccelerometerZ() const {
  return accelerometerZ;
}

short Data::getGyroscopeX() const {
  return gyroscopeX;
}

short Data::getGyroscopeY() const {
  return gyroscopeY;
}

short Data::getGyroscopeZ() const {
  return gyroscopeZ;
}