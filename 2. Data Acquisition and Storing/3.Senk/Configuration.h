#ifndef Configuration_H_
#define Configuration_H_

// Debugging settings
#define DEBUG_STATUS 1 // Set to 1 to activate debugging, 0 to deactivate


// Data configuration
#define DATA_PER_SET 400 // Total numer of data in a dataset [Max 200]
#define DATA_DISTANCE 1 // Milliseconds of distance between two different data
#define DISTANCE_BETWEEN_SET 1 // Milliseconds to wait between two different dataset, The time is measured from the first data of the current dataset to the last data of the previous dataset
#define MAX_DATASET_DIMENSION 300 // Since a dataset is stored in ram a dataset bigger than 150 cannot stay in RAM so to use bigger dataset we split it in dataset of the dimension chosed here and, based on other configuration, saved to local storage or send it usign BLE

// Data saving configuration
#define USER_ROOT "fs" // Root directory containing the file to save to
#define DELETE_FILE 1 // Set to 1 to delete all files and only keep new data
#define SAVE_FILE_NAME "out.csv" // Name of the file containing all saved data
#define PRINT_FILE 1//print the whole file after every dataset saved

// Debug printing function
inline void debugPrint(const char* toPrint){
  #if DEBUG_STATUS
    Serial.println(toPrint);
  #endif
}

#endif //Configuration_H_