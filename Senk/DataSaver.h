#ifndef DataSaver_H_
#define DataSaver_H_

#include "mbed.h"
#include <File.h>
#include <FileSystem.h>
#include <LittleFileSystem.h>

#include "Data.h"
#include "Configuration.h"

//need this line in the .ino file -> mbed::LittleFileSystem fs(userRoot);

#define MAX_LINE_LENGTH 48 // max line is like: "-00000, -00000, -00000, -00000, -00000, -00000\n\0" so 6*6+5*2+2

class DataSaver {
  private:
    mbed::BlockDevice* spif;
    mbed::LittleFileSystem fs;
    char buffer[MAX_LINE_LENGTH];
    FILE* saveFile;
    const char* saveFileName = nullptr;
  public:
    DataSaver();
    ~DataSaver();
    void initialize(const char* fileName);
    void format();
    int saveData(Data toSave);
    int saveData(Data toSave[], int length, int dataPerIteration = 1);
    int saveDataKeepOpen(Data toSave[], int length, int dataPerIteration = 1);
    void printFile();   // File content is too large to be stored in RAM, so it is printed directly to Serial Monitor
    void getData(Data* dataSet, int dataToReturn); 
};


#endif // DataSaver_H_