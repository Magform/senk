#include "DataSaver.h"
#include "Configuration.h"

DataSaver::DataSaver(): fs(USER_ROOT){}

void DataSaver::begin(const char* saveFileNameP){
  spif = mbed::BlockDevice::get_default_instance();
  spif->init();

  int err = fs.mount(spif);
  while (err) {
    err = fs.reformat(spif);
    debugPrint("Error mounting file system");
  }

  char* tmpSaveFileName = new char[strlen(USER_ROOT) + strlen(saveFileNameP) + 3];
  strcpy(tmpSaveFileName, "/");
  strcat(tmpSaveFileName, USER_ROOT);
  strcat(tmpSaveFileName, "/");
  strcat(tmpSaveFileName, saveFileNameP);
  saveFileName = tmpSaveFileName;
}

DataSaver::~DataSaver() {
  delete[] saveFileName;
}


int DataSaver::saveData(Data toSave) {
  saveFile = fopen(saveFileName, "a");
  if(saveFile == NULL){
    debugPrint("Error opening the file for writing");
    return -1;
  }
  const char* CSVtoSave = toSave.toCSV();
  int result = fprintf(saveFile, CSVtoSave);
  fprintf(saveFile, "\n");
  if(result < 0){
    debugPrint("Error writing data to the file.");
    fclose(saveFile);
    free((void*)CSVtoSave);
    return -1;
  }

  result = fclose(saveFile);
  debugPrint("Data saved to file");
  free((void*)CSVtoSave);
  return 0;
}

int DataSaver::saveData(Data toSave[], int size){
  for(int i=0; i<size; i++){
    saveData(toSave[i]);
  }
}

void DataSaver::fileDelete(){
  fs.reformat(spif);
  debugPrint("Storage formatted");
}

void DataSaver::printData(){
  saveFile = fopen(saveFileName, "r");
  if(saveFile){
    fseek(saveFile, 0, SEEK_END);
    long fileSize = ftell(saveFile);
    rewind(saveFile);

    // Allocate a buffer to hold a chunk of data
    char *buffer = (char *)malloc(CHUNK_SIZE);
    if(buffer){
      size_t bytes_read;
      while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, saveFile)) > 0) {
        Serial.print(buffer);
        memset(buffer, 0, CHUNK_SIZE);
      }
      free(buffer);
    }else{
      debugPrint("Buffer allocation failed");
    }
    fclose(saveFile);
  }else{
    debugPrint("File opening for reading failed");
  }
}

Data* DataSaver::getData(int dataToReturn){
  saveFile = fopen(saveFileName, "r");
  if(saveFile){
    Data* toReturn = new Data[dataToReturn];
    fseek(saveFile, 0, SEEK_END);
    long fileSize = ftell(saveFile);
    rewind(saveFile);
    int maxSize = 5 * 6 + 5 + 5 + 2; // max 5 characters for each number, 60 characters
    char *buffer = (char *)malloc(maxSize);
    if(buffer){
      size_t bytes_read;
      static int preRead = 0; 
      fseek(saveFile, preRead, SEEK_SET);
      for(int i=0; i<dataToReturn; i++){
        if ((bytes_read = fread(buffer, 1, maxSize, saveFile)) > 0) {
          char* newlinePosition = std::strchr(buffer, '\n');
          if (newlinePosition != nullptr) {
            size_t length = newlinePosition - buffer;
            preRead += length+1;
            char* line = new char[length + 1];
            std::strncpy(line, buffer, length);
            line[length] = '\0'; // Null-terminate the substring
            toReturn[i] = Data(line);
            debugPrint("Data ready");
            delete[] line;
          } else {
            debugPrint("No more data: file ended");
          }
          fseek(saveFile, preRead, SEEK_SET);
          memset(buffer, 0, maxSize);
        }
      }
      free(buffer);
    }else{
      debugPrint("Memory allocation of buffer for data reading failed.");
    }
    fclose(saveFile);
    return toReturn;
  }else{
    debugPrint("Error opening file for reading.");
  }
}