#ifndef Configuration_H_
#define Configuration_H_

// Debugging settings
#define DEBUG_STATUS 1 // Set to 1 to activate debugging, 0 to deactivate

// Data configuration
#define DATA_PER_SET 500 // Total numer of data in a dataset
#define DATA_DISTANCE 1 // Milliseconds of distance between two different data
#define DISTANCE_BETWEEN_SET 600000 // Milliseconds to wait between two different dataset, The time is measured from the first data of the current dataset to the last data of the previous dataset
#define MAX_DATASET_DIMENSION 150 // Since a dataset is stored in ram a dataset bigger than 150 cannot stay in RAM so to use bigger dataset we split it in dataset of the dimension chosed here and, based on other configuration, saved to local storage or send it usign BLE


#define SERVICE_UUID "11111111-0001-1111-1111-111111111111" // UUID for the main service used in the BLE communication
#define ACCELEROMETER_UUID "11111111-0001-1111-1111-111111111111" // UUID for the BLE characteristic representing accelerometer data
#define GYROSCOPE_UUID "11111111-0002-1111-1111-111111111111" // UUID for the BLE characteristic representing gyroscope data


// Debug printing function
inline void debugPrint(const char* toPrint){
  #if DEBUG_STATUS
    Serial.println(toPrint);
  #endif
}

#endif //Configuration_H_