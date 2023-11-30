#ifndef Configuration_H_
#define Configuration_H_

// Debugging settings
#define DEBUG_STATUS 1 // Set to 1 to activate debugging, 0 to deactivate


// Data configuration
#define DATA_PER_SET 10 // Total numer of data in a dataset
#define DATA_DISTANCE 10 // Milliseconds of distance between two different data
#define DISTANCE_BETWEEN_SET 10000 // Milliseconds to wait between two different dataset, The time is measured from the first data of the current dataset to the last data of the previous dataset
#define MAX_DATASET_DIMENSION 150 // Since a dataset is stored in ram a dataset bigger than 150 cannot stay in RAM so to use bigger dataset we split it in dataset of the dimension chosed here and, based on other configuration, saved to local storage or send it usign BLE

// Data saving configuration
#define DATA_SAVER 0 // Set to 1 to enable saving data to local storage, 0 to disable
#define DATA_SAVER_KEEP_OPEN 0 //Set to 1 to enable saving data to local storage without colosing the file every writing, need DATA_SAVER to be turned off
#define DATA_PER_ITERATION 15 // Defines the maximum number of lines written per cicle, bigger number means fast but also more RAM expesnive (max value is 15)
#define USER_ROOT "fs" // Root directory containing the file to save to
#define DELETE_FILE 1 // Set to 1 to delete all files and only keep new data
#define SAVE_FILE_NAME "out.csv" // Name of the file containing all saved data

// Data sending configuration
#define SEND_DATASET 0 // Set to 1 to send every dataset to Bluetooth after acquisition
#define SEND_DATASET_THREAD 0 // Set to 1 to use another thread to send every dataset to Bluetooth after acquisition, does not work if SEND_DATASET is enable

#define DATA_SENDER 0 // Read data from file and send it (Requires DATA_SAVER_STATUS to work), sends all data only once
#define DATA_TO_SCAN 0  // Total lines to scan and send in each file scan, if it's more than the remaining data, it sends all remaining data
#define SCAN_TIME 0 // Time between two different file scans, if new data is found, it will be sent

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