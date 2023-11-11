#ifndef Configuration_H_
#define Configuration_H_

// We define here all the configuration needed using define:
#define debugStatus 1 //if defined as 1 is activated, if defined as 0 is of
#define distanceBetweenSet 10//milliseconds 
#define dataPerSet 1 // saving data is really slow with a lot of information
#define distanceData 10 //milliseconds
#define maxDataSetDimension 150 //[Less than 150] Split all set in set that has that dimension (small delay since it save data between two)

#define userRoot "fs"
#define save_File_Name "out.csv"
#define chunkSize 42

//It doesn not send the same data twice, but keep it saved.
#define sendTime 10 //time between two different file sending
#define dataToSend 1 // total data to send in evry instance, if it's more than total remaing data it send all the data

#endif //Configuration_H_