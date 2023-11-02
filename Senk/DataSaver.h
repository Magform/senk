#ifndef DataSaver_H_
#define DataSaver_H_

#include "mbed.h"
#include <File.h>
#include <FileSystem.h>
#include <LittleFileSystem.h>

#include "Data.h"
#include "Configuration.h"

class DataSaver {
  private:
    FILE* saveFile;
    const char* saveFileName = nullptr;
    mbed::BlockDevice* spif;
    mbed::LittleFileSystem fs;
  public:
    DataSaver();
    void begin(const char* saveFileNameP);
    ~DataSaver();
    int saveData(Data toSave);
    int saveData(Data toSave[], int size);
    void printData(); //im not returning it because the data is to big to stay in the RAM so I'm direclty printing it
};


#endif // DataSaver_H_