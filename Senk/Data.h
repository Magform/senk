#ifndef Data_H_
#define Data_H_

class Data {
  private:
    short accelerometerX;
    short accelerometerY;
    short accelerometerZ;
    short gyroscopeX;
    short gyroscopeY;
    short gyroscopeZ;

  public:
    Data(); //inizialize with all -32768
    Data(short accelX, short accelY, short accelZ, short gyroX, short gyroY, short gyroZ);
    short getAccelerometerX() const;
    short getAccelerometerY() const;
    short getAccelerometerZ() const;
    short getGyroscopeX() const;
    short getGyroscopeY() const;
    short getGyroscopeZ() const;
    const char* toString() const;
};

#endif Data_H_