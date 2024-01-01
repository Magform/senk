#ifndef Configuration_H_
#define Configuration_H_

// FOR INFO ABOUT THE CONFIGURATION VISIT:
// https://senk.nicolasferraresso.dev/#/installation_and_configuration


// Debugging settings
#define DEBUG_STATUS 0


// Data configuration
#define DATA_PER_SET 10000
#define DATA_DISTANCE 1
#define DISTANCE_BETWEEN_SET 0 
#define MAX_DATASET_DIMENSION 10

// Data saving configuration
#define DATA_SAVER 0
#define DATA_SAVER_KEEP_OPEN 0 
#define DATA_PER_ITERATION 15
#define USER_ROOT "fs"
#define DELETE_FILE 1
#define SAVE_FILE_NAME "out.csv"

// Data sending configuration
#define SEND_DATASET 0
#define SEND_DATASET_THREAD 1

#define DATA_SENDER 0
#define DATA_TO_SCAN 0
#define SCAN_TIME 0

// Bluetooth configuration
#define SERVICE_UUID "11111111-0001-1111-1111-111111111111" // UUID for the main service used in the BLE communication
#define ACCELEROMETER_UUID "11111111-0001-1111-1111-111111111111" // UUID for the BLE characteristic representing accelerometer data
#define GYROSCOPE_UUID "11111111-0002-1111-1111-111111111111" // UUID for the BLE characteristic representing gyroscope data


// Debug printing function

#include <rtos.h>
#include <Arduino.h>
inline void debugPrint(const char* toPrint){
  #if DEBUG_STATUS
    static rtos::Semaphore serialSem(1);
    serialSem.acquire();
    Serial.println(toPrint);
    serialSem.release();
  #endif
}

#endif //Configuration_H_