#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>
#include <vector>

#include "Configuration.h"

//Bluetooth Service and characteristics
BLEService Accelerometer("1101");
BLEService Gyroscope("1102");
BLEShortCharacteristic AccX("2101", BLERead);
BLEShortCharacteristic AccY("2102", BLERead);  
BLEShortCharacteristic AccZ("2103", BLERead);
BLEShortCharacteristic GyroX("3101", BLERead);  
BLEShortCharacteristic GyroY("3102", BLERead);
BLEShortCharacteristic GyroZ("3103", BLERead);  

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
int initializeBLE();
void sendDataBLE();

void setup() {
  if(debug){
    Serial.begin(115200);
  }

  BHY2.begin();
  accel.begin();
  gyro.begin();

  initializeBLE();
}

void loop() {
  BLEDevice central = BLE.central();
  static auto lastCheck = millis();
  BHY2.update();

  if (millis() - lastCheck >= distanceData){
    lastCheck = millis();
    
    if(debug){
      Serial.print("Accelerometer: " + accel.toString());
      Serial.print("Gyroscope: " + gyro.toString());
      Serial.println();
    }

    sendDataBLE();

  }

  delay(1);
}

//Function definition
int initializeBLE(){

  if(!BLE.begin()) {
    return 0;
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
  
  return 1;
}

void sendDataBLE(){
    AccX.writeValue(accel.x());
    AccY.writeValue(accel.y());
    AccZ.writeValue(accel.z());

    GyroX.writeValue(gyro.x());
    GyroY.writeValue(gyro.y());
    GyroZ.writeValue(gyro.z());
}
