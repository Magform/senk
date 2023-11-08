#ifndef Configuration_H_
#define Configuration_H_

// We define here all the configuration needed using define:
#define debug 1 //if defined as 1 is activated, if defined as 0 is of
#define distanceBetweenSet 1000//milliseconds 
#define dataPerSet 10000 // 50 or less, saving data is really slow with a lot of information
#define distanceData 10 //milliseconds

#define userRoot "fs"
#define save_File_Name "out.csv"
#define chunkSize 42
#define printFile 10 //time between two different file printing 

#endif //Configuration_H_