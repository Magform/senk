#include <Arduino.h>
#include "Nicla_System.h"
#include "Arduino_BHY2.h"
#include <ArduinoBLE.h>
#include <BlockDevice.h>
#include <Dir.h>
#include <File.h>
#include <FileSystem.h>
#include <LittleFileSystem.h>
#include <mbed.h>
#include <FileHandle.h>


#include "Configuration.h"
#include "Data.h"

//File system
mbed::BlockDevice* spif;
mbed::LittleFileSystem fs(userRoot);

//Bluetooth Service and characteristics
BLEService Accelerometer("2000");
BLEService Gyroscope("3000");
BLEShortCharacteristic AccX("2001", BLERead | BLENotify);
BLEShortCharacteristic AccY("2002", BLERead | BLENotify);  
BLEShortCharacteristic AccZ("2003", BLERead | BLENotify);
BLEShortCharacteristic GyroX("3001", BLERead | BLENotify);  
BLEShortCharacteristic GyroY("3002", BLERead | BLENotify);
BLEShortCharacteristic GyroZ("3003", BLERead | BLENotify);  

//Sensor to read
SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

//util function declaration
int initializeBLE();
int initializeFileSystem();
void sendDataBLE();
void takeDataSet();
void sendDataSet_BLE();
void storeData(Data toStore);
void storeDataSet();
void printStats();
void listDirsAlt();
void printFile(mbed::File& file);


Data dataSet[dataPerSet];

void setup() {
  if(debug){
    Serial.begin(115200);
    Serial.print("Initializing ");
  }

  initializeBLE();
  initializeFileSystem();
  
  BHY2.begin();
  accel.begin();
  gyro.begin();

  if(debug){
    Serial.println(" done!");
  }
}

void loop(){
  BLEDevice central = BLE.central();
  static auto lastSet = millis();
  BHY2.update();
  
  if (millis() - lastSet >= distanceBetweenSet){
    lastSet = millis();
    takeDataSet();
    storeDataSet();
    sendDataSet_BLE();
    if(debug){
      printStats();
      listDirsAlt();
    }
  }

  delay(1);
}

//Function definition

//Inizialize Bluetooth with Name, Service and all Service Characteristic
int initializeBLE(){

  if(!BLE.begin()) {
    return 0;
  }

  BLE.setLocalName("Senk");
  BLE.setAdvertisedService("Accelerometer");
  Accelerometer.addCharacteristic(AccX);
  Accelerometer.addCharacteristic(AccY);
  Accelerometer.addCharacteristic(AccZ);
  BLE.setAdvertisedService("Gyroscope");
  Gyroscope.addCharacteristic(GyroX);
  Gyroscope.addCharacteristic(GyroY);
  Gyroscope.addCharacteristic(GyroZ);
  BLE.addService(Accelerometer);
  BLE.addService(Gyroscope);
  BLE.advertise();
  
  return 1;
}

int initializeFileSystem(){
  spif = mbed::BlockDevice::get_default_instance();
  spif->init();

  // Mount the filesystem
  int err = fs.mount(spif);
  if (err) {
    err = fs.reformat(spif);
    if(debug){
      Serial.print("Error mounting file system: ");
      Serial.println(err);
    }
    while (true){
      ;
    }
  }
}

//Take data from accelerometer and gyroscope and add it to the dataset
void takeDataSet(){
  for(int i = 0; i<dataPerSet; i++){
    BHY2.update();
    dataSet[i] = Data(accel.x(), accel.y(), accel.z(), gyro.x(), gyro.y(), gyro.z());
    if(debug){
      const char* toPrint = dataSet[i].toString();
      Serial.println(toPrint);
      delete[] toPrint;
    }
    delay(distanceData);
  }
}

//Send data from dataset to BLE
void sendDataSet_BLE(){
  for(int i = 0; i<dataPerSet; i++){
    AccX.writeValue(dataSet[i].getAccelerometerX());
    AccY.writeValue(dataSet[i].getAccelerometerY());
    AccZ.writeValue(dataSet[i].getAccelerometerZ());
    GyroX.writeValue(dataSet[i].getGyroscopeX());
    GyroY.writeValue(dataSet[i].getGyroscopeY());
    GyroZ.writeValue(dataSet[i].getGyroscopeZ());
    delay(1);
  }
}

// Store data from sensors to the SPI Flash Memory
void storeData(Data toStore){
  // Open a file in append mode
  mbed::File file;
  auto err = file.open(&fs, saveFile, O_WRONLY | O_CREAT | O_APPEND);
  if (err) {
    if(debug){
      Serial.print("Error opening file for writing: ");
      Serial.println(err);
    }
    return;
  }

  auto data = toStore.toCSV();

  file.write(data.c_str(), data.length()); //error handling
  
  file.close();
}

void storeDataSet(){
  for(int i = 0; i<dataPerSet; i++){
    storeData(dataSet[i]);
  }
}

// Retrieve and print Flash Memory stats
void printStats(){
  if(debug){
    struct statvfs stats { };
    fs.statvfs(userRoot, &stats);

    auto blockSize = stats.f_bsize;

    Serial.print("Total Space [Bytes]:  ");
    Serial.println(stats.f_blocks * blockSize);
    Serial.print("Free Space [Bytes]:   ");
    Serial.println(stats.f_bfree * blockSize);
    Serial.print("Used Space [Bytes]:   ");
    Serial.println((stats.f_blocks - stats.f_bfree) * blockSize);
    Serial.println();
  }
}

//List all File and print it
void listDirsAlt(){
  if(debug){
    String baseDirName = "/";
    baseDirName += userRoot;

    Serial.print("Listing file on ");
    Serial.print(baseDirName);
    Serial.println(" Filesystem");

    // Open the root of the filesystem
    mbed::Dir dir(&fs, "/");
    dirent ent;

    // Cycle through all the directory entries
    while ((dir.read(&ent)) > 0) {
        switch (ent.d_type) {
        case DT_DIR: {
            Serial.print("Directory ");
            Serial.println(ent.d_name);
            break;
        }
        case DT_REG: {
            Serial.print("Regular File ");
            Serial.print(ent.d_name);

            // Declare and open the file in read-only mode
            mbed::File file;
            auto ret = file.open(&fs, ent.d_name);
            if (ret) {
                Serial.println("Unable to open file");
                continue;
            }
            Serial.print(" [");
            Serial.print(file.size());
            Serial.println(" bytes]");

            if (file.size() > 0) {
                // Print file with an ad-hoc function. YMMV.
                printFile(file);

                // Empty file after reading all the content. YMMV.
                file.close();
                ret = file.open(&fs, ent.d_name, O_TRUNC);
                if (ret < 0)
                    Serial.println("Unable to truncate file");
            } else {
                // Remove file if empty. YMMV.
                file.close();
                fs.remove(ent.d_name);
            }

            break;
        }
        default: {
            Serial.print("Other ");
            break;
        }
        }
    }
  }
}

void printFile(mbed::File& file){
  // Read and print file len-bytes at time
  // to preserve RAM
  constexpr size_t len { 256 };

  size_t totalLen { file.size() };

  while (totalLen > 0) {
    char buf[len] {};

    auto read = file.read(buf, len);
    totalLen -= read;
    for (const auto& c : buf)
      Serial.print(c);
  }
  Serial.println();
}