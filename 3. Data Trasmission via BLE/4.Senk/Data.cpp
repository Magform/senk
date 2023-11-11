#include "Data.h"
#include <cstdio> //for sprintf and sscanf

#include <Arduino.h>

Data::Data()
    : accelerometerX(-32768), accelerometerY(-32768), accelerometerZ(-32768),
      gyroscopeX(-32768), gyroscopeY(-32768), gyroscopeZ(-32768) {

}

Data::Data(short accelX, short accelY, short accelZ, short gyroX, short gyroY, short gyroZ)
    : accelerometerX(accelX), accelerometerY(accelY), accelerometerZ(accelZ),
      gyroscopeX(gyroX), gyroscopeY(gyroY), gyroscopeZ(gyroZ) {
}

Data::Data(char* csv) {
  std::sscanf(csv, "%hd, %hd, %hd, %hd, %hd, %hd",
    &accelerometerX, &accelerometerY, &accelerometerZ,
    &gyroscopeX, &gyroscopeY, &gyroscopeZ);
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

const char* Data::toString() const {
  int maxSize = 5 * 6 + 60; // 5 characters for each number, 60 characters
  char* result = new char[maxSize];
  snprintf(result, maxSize, "Accelerometer (X, Y, Z): (%d, %d, %d), Gyroscope (X, Y, Z): (%d, %d, %d)",
          accelerometerX, accelerometerY, accelerometerZ, gyroscopeX, gyroscopeY, gyroscopeZ);
  return result;
}

const char* Data::toCSV() const {
  int maxSize = 5 * 6 + 5 + 5 + 2; // max 5 characters for each number, 60 characters
  char* result = new char[maxSize];
  snprintf(result, maxSize, "%d, %d, %d, %d, %d, %d\n",
          accelerometerX, accelerometerY, accelerometerZ, gyroscopeX, gyroscopeY, gyroscopeZ);
  return result;
}
