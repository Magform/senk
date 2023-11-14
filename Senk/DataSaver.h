#ifndef DataSaver_H_
#define DataSaver_H_

#include "mbed.h"
#include <File.h>
#include <FileSystem.h>
#include <LittleFileSystem.h>

#include "Data.h"
#include "Configuration.h"

//need this line in the .ino file -> mbed::LittleFileSystem fs(userRoot);

class DataSaver {
  private:
    mbed::BlockDevice* spif;
    mbed::LittleFileSystem fs;
    FILE* saveFile;
    const char* saveFileName = nullptr;
  public:
    DataSaver();
    ~DataSaver();
    void initialize(const char* fileName);
    void format();
    int saveData(Data toSave);
    int saveData(Data toSave[], int length);
    void printFile();   // File content is too large to be stored in RAM, so it is printed directly to Serial Monitor
    Data* getData(int dataToReturn); 
};


#endif // DataSaver_H_