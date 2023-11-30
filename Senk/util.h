#ifndef UTIL_H_
#define UTIL_H_

#include <Arduino.h>
#include <Nicla_System.h>
#include <Arduino_BHY2.h>
#include <mbed.h>
#include <rtos.h>
#include <platform/Callback.h>
#include "Configuration.h"
#include "Data.h"

inline void takeDataSet(Data dataSet[], int length, SensorXYZ *accel, SensorXYZ *gyro) {
  long time = -DATA_DISTANCE;
  for (int i = 0; i < length; i++) {
    BHY2.update();
    if(millis() - time >= DATA_DISTANCE){
      dataSet[i] = Data(accel->x(), accel->y(), accel->z(), gyro->x(), gyro->y(), gyro->z());
      time = millis();
      #if DEBUG_STATUS
      static long oldTime = 0;
      long timeDiff = time - oldTime;
      oldTime = millis();
      Serial.print("Data between last data: ");
      Serial.print(timeDiff);
      Serial.print(" -> ");
      const char* toPrint = dataSet[i].toString();
      Serial.println(toPrint);
      delete[] toPrint;
      #endif
    }else{i--;}
  }
}

#if SEND_DATASET || SEND_DATASET_THREAD || DATA_SENDER
#include "BLECommunication.h"
inline void sendDataToBLE(Data dataSet[], int length, BLECommunication* BLECom) {
  #if SEND_DATASET
  BLECom->send(dataSet, length);
  #endif

  #if !SEND_DATASET && SEND_DATASET_THREAD
  static rtos::Semaphore dataAviableForBLE(0);
  static rtos::Semaphore dataSentForBLE(1);
  static rtos::Thread BLEsending;
  static int toSend;

  dataSentForBLE.acquire();
  toSend = length;
  dataAviableForBLE.release();
  BLEsending.start(mbed::callback([&BLECom, &dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE]() {
    BLECom->send(dataSet, &toSend, &dataAviableForBLE, &dataSentForBLE);
  }));
  #endif
}
#endif

#if DATA_SAVER || DATA_SAVER_KEEP_OPEN
#include "DataSaver.h"
inline void sendDataToSaver(Data dataSet[], int length, DataSaver* dataSaver) {
  #if DATA_SAVER
  dataSaver->saveData(dataSet, length);
  #endif

  #if DATA_SAVER_KEEP_OPEN && !DATA_SAVER
  dataSaver->saveDataKeepOpen(dataSet, length, DATA_PER_ITERATION);
  #endif
}
#endif


#endif // UTIL_H_