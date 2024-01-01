#ifndef DataSaver_H_
#define DataSaver_H_

#include "mbed.h"
#include <File.h>
#include <FileSystem.h>
#include <LittleFileSystem.h>

#include "Data.h"
#include "Configuration.h"

#define MAX_LINE_LENGTH 48 // Maximum line length is like: "-00000, -00000, -00000, -00000, -00000, -00000\n\0" so 6*6+5*2+2

/**
 * @class DataSaver
 * @brief Handles saving and retrieving data to and from a file using mbed's LittleFileSystem.
 * 
 * Manages the functionality to save and retrieve Data objects to/from a file using mbed's LittleFileSystem.
 * mbed's LittleFileSystem need to be initiliazied usining mbed::LittleFileSystem fs(userRoot); in the main file.
 */
class DataSaver {
  private:
    mbed::BlockDevice* spif;              ///< Pointer to the BlockDevice used for storage.
    mbed::LittleFileSystem fs;            ///< LittleFileSystem instance for file management.
    char buffer[MAX_LINE_LENGTH];         ///< Buffer for storing data lines to be written to the file.
    FILE* saveFile;                       ///< File pointer to the opened file.
    const char* saveFileName = nullptr;   ///< Name of the file to be saved.

  public:
    /**
     * @brief Default constructor.
     */
    DataSaver();

    /**
     * @brief Destructor.
     */
    ~DataSaver();

    /**
     * @brief Initializes the DataSaver with a specified file name.
     * 
     * @param fileName Name of the file to be used for saving data.
     */
    void initialize(const char* fileName);

    /**
     * @brief Formats the file system.
     */
    void format();

    /**
     * @brief Saves a single Data object to the file.
     * 
     * @param toSave Data object to be saved.
     * @return 0 if successful, -1 otherwise.
     */
    int saveData(Data toSave);

    /**
     * @brief Saves an array of Data objects to the file with an option for batch processing.
     * 
     * @param toSave Array of Data objects to be saved.
     * @param length Length of the array.
     * @param dataPerIteration Number of data points to save in each iteration.
     * @return 0 if successful, -1 otherwise.
     */
    int saveData(Data toSave[], int length, int dataPerIteration = 1);

    /**
     * @brief Saves an array of Data objects to the file, keeping it open throughout the whole process.
     * 
     * @param toSave Array of Data objects to be saved.
     * @param length Length of the array.
     * @param dataPerIteration Number of data points to save in each iteration.
     * @return 0 if successful, -1 otherwise.
     */
    int saveDataKeepOpen(Data toSave[], int length, int dataPerIteration = 1);

    /**
     * @brief Prints the file content to the Serial Monitor.
     * 
     * File content is too large to be stored in RAM, so it is printed directly to Serial Monitor.
     */
    void printFile();

    /**
     * @brief Retrives data from file, does not retrives previously retrived data.
     * 
     * @param dataSet Pointer to the array where retrieved data will be stored.
     * @param dataToReturn Max number of data points to retrieve.
     */
    void getData(Data* dataSet, int dataToReturn);
};

#endif // DataSaver_H_
