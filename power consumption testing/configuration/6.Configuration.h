#ifndef Configuration_H_
#define Configuration_H_

#define DEBUG_STATUS 0

#define DATA_PER_SET 10000
#define DATA_DISTANCE 1
#define DISTANCE_BETWEEN_SET 10000
#define MAX_DATASET_DIMENSION 150

#define DATA_SAVER 0 
#define DATA_SAVER_KEEP_OPEN 0
#define DATA_PER_ITERATION 15
#define USER_ROOT "fs"
#define DELETE_FILE 1
#define SAVE_FILE_NAME "out.csv"

#define SEND_DATASET 0
#define SEND_DATASET_THREAD 0

#define DATA_SENDER 0
#define DATA_TO_SCAN 0
#define SCAN_TIME 0

#define SERVICE_UUID "11111111-0001-1111-1111-111111111111"
#define ACCELEROMETER_UUID "11111111-0001-1111-1111-111111111111"
#define GYROSCOPE_UUID "11111111-0002-1111-1111-111111111111"


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