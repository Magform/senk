#ifndef Configuration_H_
#define Configuration_H_

// Debugging settings
#define DEBUG_STATUS 1 // Set to 1 to activate debugging, 0 to deactivate



// Data configuration
#define DATA_PER_SET 10 // Total numer of data in a dataset
#define DATA_DISTANCE 1 // Milliseconds of distance between two different data
#define DISTANCE_BETWEEN_SET 1 // Milliseconds to wait between two different dataset, The time is measured from the first data of the current dataset to the last data of the previous dataset


// Debug printing function
inline void debugPrint(const char* toPrint){
  #if DEBUG_STATUS
    Serial.println(toPrint);
  #endif
}

#endif //Configuration_H_