#include "DataSaver.h"
#include "Configuration.h"

DataSaver::DataSaver(): fs(userRoot){}

void DataSaver::begin(const char* saveFileNameP){
  spif = mbed::BlockDevice::get_default_instance();
  spif->init();

  int err = fs.mount(spif);
  if (err) {
    err = fs.reformat(spif);
    if(debug){
      Serial.print("Error mounting file system: ");
      Serial.println(err);
    }
    while(true){;}
  }

  char* tmpSaveFileName = new char[strlen(userRoot) + strlen(saveFileNameP) + 3];
  strcpy(tmpSaveFileName, "/");
  strcat(tmpSaveFileName, userRoot);
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
    if(debug){
      Serial.print("Error opening ");
      Serial.print(saveFileName);
      Serial.println(" for writing.");
    }
    return -1;
  }

  const char* CSVtoSave = toSave.toCSV();
  int result = fprintf(saveFile, CSVtoSave);
  if(result < 0){
    if(debug){
      Serial.println("Error writing data to the file.");
    }
    fclose(saveFile);
    free((void*)CSVtoSave);
    return -1;
  }

  result = fclose(saveFile);
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
}

void DataSaver::printData(){
  saveFile = fopen(saveFileName, "r");
  if(saveFile){
    fseek(saveFile, 0, SEEK_END);
    long fileSize = ftell(saveFile);
    rewind(saveFile);

    // Allocate a buffer to hold a chunk of data
    char *buffer = (char *)malloc(chunkSize);
    if(buffer){
      size_t bytes_read;
      while ((bytes_read = fread(buffer, 1, chunkSize, saveFile)) > 0) {
        Serial.print(buffer);
        memset(buffer, 0, chunkSize);
      }
      free(buffer);
    }else{
      if(debug){
        Serial.println("Memory allocation of buffer for data reading failed.");
      }
    }
    fclose(saveFile);
  }else{
    if(debug){
      Serial.println("Error opening file for reading.");
    }
  }
}