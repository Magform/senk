#include "DataSaver.h"
#include "Configuration.h"

DataSaver::DataSaver(): fs(USER_ROOT){}

void DataSaver::initialize(const char* fileName){
  spif = mbed::BlockDevice::get_default_instance();
  spif->init();

  int err = fs.mount(spif);
  while (err) {
    err = fs.reformat(spif);
    debugPrint("Error mounting file system, tring to format it");
  }

  char* tmpSaveFileName = new char[strlen(USER_ROOT) + strlen(fileName) + 3];
  strcpy(tmpSaveFileName, "/");
  strcat(tmpSaveFileName, USER_ROOT);
  strcat(tmpSaveFileName, "/");
  strcat(tmpSaveFileName, fileName);
  saveFileName = tmpSaveFileName;
}

DataSaver::~DataSaver() {
  delete[] saveFileName;
  delete[] buffer;
}



int DataSaver::saveData(Data toSave) {
  FILE* saveFile = fopen(saveFileName, "a");
  if (saveFile == NULL) {
    debugPrint("Error opening the file for writing");
    return -1;
  }

  const char* CSVtoSave = toSave.toCSV();
  int len = snprintf(buffer, MAX_LINE_LENGTH, "%s\n", CSVtoSave);
  if (len >= MAX_LINE_LENGTH) {
    debugPrint("Data exceeds buffer size");
    fclose(saveFile);
    free((void*)CSVtoSave); 
    return -1;
  }

  fwrite(buffer, 1, len, saveFile);

  fclose(saveFile);
  debugPrint("Data saved to file");
  free((void*)CSVtoSave); 
  return 0;
}

void DataSaver::saveData(Data toSave[], int length){
  for(int i=0; i<length; i++){
    saveData(toSave[i]);
  }
}

void DataSaver::format(){
  fs.reformat(spif);
  debugPrint("Storage formatted");
}

void DataSaver::printFile() {
  saveFile = fopen(saveFileName, "r");
  if (saveFile) {
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, MAX_LINE_LENGTH-1, saveFile)) > 0) {
      buffer[bytesRead] = '\0'; // Null-terminate the chunk
      Serial.print(buffer);
      memset(buffer, 0, MAX_LINE_LENGTH); // Clear the buffer for the next read
    }
    fclose(saveFile);
  } else {
    debugPrint("File opening for reading failed");
  }
}

void DataSaver::getData(Data* dataSet, int dataToReturn) {
  saveFile = fopen(saveFileName, "r");
  if (saveFile) {
    fseek(saveFile, 0, SEEK_END);
    long fileSize = ftell(saveFile);
    
    size_t bytesRead;
    static long preRead = 0;

    for (int i = 0; i < dataToReturn; ++i) {
      fseek(saveFile, preRead, SEEK_SET);
      bytesRead = fread(buffer, 1, MAX_LINE_LENGTH - 1, saveFile);
      if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        char* newlinePosition = std::strchr(buffer, '\n');
        if (newlinePosition != nullptr) {
          size_t length = newlinePosition - buffer;
          preRead += length + 1;
          char* line = new char[length + 1];
          std::strncpy(line, buffer, length);
          line[length] = '\0'; // Null-terminate the substring
          Serial.println(line);
          dataSet[i] = Data(line); // Store a pointer to the Data object in dataSet[i]
          debugPrint("Data ready");
          delete[] line;
          memset(buffer, 0, MAX_LINE_LENGTH); // Clear the buffer for the next read
        } else {
          debugPrint("No more data: file ended");
        }
      }
    }

    fclose(saveFile);
  } else {
    debugPrint("Error opening file for reading.");
  }
}

