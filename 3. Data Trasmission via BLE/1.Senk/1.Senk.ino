#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"

#include "Configuration.h"
#include "BLECommunication.h"

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

void takeDataSetAndSend();

BLECommunication BLECom;

void setup() {
  Serial.begin(115200);
  debugPrint("Initializing ");

  BHY2.begin();
  accel.begin();
  gyro.begin();

  BLECom.initialize();

  debugPrint(" done!");
}

void loop(){
  static auto lastSet = millis() - DISTANCE_BETWEEN_SET;
  BHY2.update();
  
  if (millis() - lastSet >= DISTANCE_BETWEEN_SET){
    takeDataSetAndSend();
    lastSet = millis();
  }

  delay(1);
}

//Function definition

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSetAndSend(){
  for(int i = 0; i<DATA_PER_SET; i++){
    BHY2.update();
    short aX = accel.x();
    short aY = accel.y();
    short aZ = accel.z();
    short gX = gyro.x(); 
    short gY = gyro.y();
    short gZ = gyro.z();
    #if DEBUG_STATUS
    Serial.print("Accelerometer (X, Y, Z): (");
    Serial.print(aX);
    Serial.print(", ");
    Serial.print(aY);
    Serial.print(", ");
    Serial.print(aZ);
    Serial.print("); Gyroscope (X, Y, Z): (");
    Serial.print(gX);
    Serial.print(", ");
    Serial.print(gY);
    Serial.print(", ");
    Serial.print(gZ);
    Serial.println(")");
    #endif
    BLECom.send(aX, aY, aZ, gX, gY, gZ);
    delay(DATA_DISTANCE);
  }
}
