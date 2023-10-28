#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>
#include <vector>

BLEService Accelerometer("1101");
BLEService Gyroscope("1102");
BLEShortCharacteristic AccX("2101", BLERead);
BLEShortCharacteristic AccY("2102", BLERead);  
BLEShortCharacteristic AccZ("2103", BLERead);
BLEShortCharacteristic GyroX("3101", BLERead);  
BLEShortCharacteristic GyroY("3102", BLERead);
BLEShortCharacteristic GyroZ("3103", BLERead);  


SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

#define distanceData 1000

void setup() {
  Serial.begin(115200);
  
  BHY2.begin();
  accel.begin();
  gyro.begin();

    while(!BLE.begin()) {
    //BLE problem
  }

  BLE.setLocalName("Senk");
  BLE.setAdvertisedService(Accelerometer);
  Accelerometer.addCharacteristic(AccX);
  Accelerometer.addCharacteristic(AccY);
  Accelerometer.addCharacteristic(AccZ);
  BLE.setAdvertisedService(Gyroscope);
  Gyroscope.addCharacteristic(GyroX);
  Gyroscope.addCharacteristic(GyroY);
  Gyroscope.addCharacteristic(GyroZ);
  BLE.addService(Accelerometer);
  BLE.addService(Gyroscope);
  BLE.advertise();

}

void loop() {
  BLEDevice central = BLE.central();
  static auto lastCheck = millis();
  BHY2.update();

  if (millis() - lastCheck >= distanceData){
    lastCheck = millis();
    Serial.print("Accelerometer: " + accel.toString());
    Serial.print("Gyroscope: " + gyro.toString());
    Serial.println();

    AccX.writeValue(accel.x());
    AccY.writeValue(accel.y());
    AccZ.writeValue(accel.z());

    GyroX.writeValue(gyro.x());
    GyroY.writeValue(gyro.y());
    GyroZ.writeValue(gyro.z());
  }
  delay(1);
}