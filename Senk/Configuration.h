#ifndef Configuration_H_
#define Configuration_H_

#define DEBUG_STATUS 1 //if defined as 1 is activated, if defined as 0 is of

#define DISTANCE_BETWEEN_SET 999999 //milliseconds to wait between two different dataset, time is taken at the last data of the last dataset
#define DATA_PER_SET 1 //total numer of data that a dataset have
#define DATA_DISTANCE 1 //milliseconds of distance between two different data
#define MAX_DATASET_DIMENSION 150 //Since a dataset is stored in ram a dataset bigger than 150 cannot stay in RAM so to avoid this u can set this to 150 or less and all the dataset will be splitted in dataset of this quantity that is taken really fast, between two of there we send it on BLE if enable or save it to storage if enable

#define DATA_SAVER_STATUS 0 //1 to turn it on 0 to turn it off data saving to local storage
#define USER_ROOT "fs" //root directory containg the file to save to
#define DELETE_FILE 1 //delete all the file to have only new data
#define SAVE_FILE_NAME "out.csv" // Name of the file containgi all the save
#define CHUNK_SIZE 42 //Dimension of every chunk (used when printing the file), bigger means faster but also more memory expensive

#define SEND_DATASET 0 // if turned on it send every dataset to the bluetooth after taken

//It doesn not send the same data twice, but keep it saved.
#define DATA_SENDER 0 //Read data from file and send it (Need DATA_SAVER_STATUS enable to work), it send all data only one time
#define SCAN_TIME 10 //time between two different file scan, if there is new data it will send it
#define DATA_TO_SCAN 1 // total file line to scan and send in evry file scan, if it's more than total remaing data to send it sand all the data, if is near the real total file length is more efficent


inline void debugPrint(const char* toPrint){
  #if DEBUG_STATUS
    Serial.println(toPrint);
  #endif
}

#endif //Configuration_H_