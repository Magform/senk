#ifndef BLEConnection_H_
#define BLEConnection_H_

#include <ArduinoBLE.h>
#include <rtos.h>

#include "Data.h"

/**
 * @class BLECommunication
 * @brief Handles communication over BLE (Bluetooth Low Energy).
 */
class BLECommunication {
  private:
    BLEService DataSend;             ///< BLE service for sending data.
    BLECharacteristic Accelerometer; ///< BLE characteristic for accelerometer data.
    BLECharacteristic Gyroscope;     ///< BLE characteristic for gyroscope data.

  public:
    /**
     * @brief Default constructor.
     */
    BLECommunication();

    /**
     * @brief Initializes the BLE communication.
     * @return 0 if successful, -1 otherwise.
     */
    int initialize();

    /**
     * @brief Sends accelerometer and gyroscope data over BLE.
     * 
     * @param aX Accelerometer X-axis value.
     * @param aY Accelerometer Y-axis value.
     * @param aZ Accelerometer Z-axis value.
     * @param gX Gyroscope X-axis value.
     * @param gY Gyroscope Y-axis value.
     * @param gZ Gyroscope Z-axis value.
     * @return 0 if successful, -1 otherwise.
     */
    int send(short aX, short aY, short aZ, short gX, short gY, short gZ);

    /**
     * @brief Sends data object over BLE.
     * 
     * @param toSend Data object to be sent.
     * @return 0 if successful, -1 otherwise.
     */
    int send(Data toSend);

    /**
     * @brief Sends an array of data objects over BLE.
     * 
     * @param dataSet Array of data objects to be sent.
     * @param length Length of the data set array.
     */
    void send(const Data dataSet[], int length);

    /**
     * @brief Sends an array of data objects over BLE using semaphores for synchronization, meant to run in another thread.
     * 
     * @param dataSet Array of data objects to be sent.
     * @param length Pointer to the length of the data set array.
     * @param dataAviable Semaphore indicating data availability.
     * @param dataSent Semaphore indicating that data has been sent.
     */
    void send(const Data dataSet[], int* length, rtos::Semaphore *dataAviable, rtos::Semaphore *dataSent);
};

#endif // BLEConnection_H_
