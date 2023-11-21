# Implementation Analysis

## Hardware Configuration

### Arduino Nicla Sense Me

The foundation of the entire system relies on the Arduino [Nicla Sense Me](https://docs.arduino.cc/hardware/nicla-sense-me). This versatile platform integrates various sensors and communication modules crucial for the project.

#### BHI260AP - 16-Bit 6-Axis IMU

The cornerstone sensor, BHI260AP, serves as a 16-bit 6-axis Inertial Measurement Unit (IMU), encompassing a 3-axis accelerometer and a 3-axis gyroscope. This pivotal component captures essential acceleration and gyroscope data from the surrounding environment.

#### 2MB QSPI Flash Memory

The 2MB QSPI flash memory plays a vital role in storing system data. However, it's essential to note that the write speed of this memory is relatively slow.

#### Bluetooth 5.0 Low Energy (BLE)

To optimize energy consumption, the project strategically utilizes Bluetooth Low Energy (BLE) for data communication. This efficient protocol ensures seamless transmission of data acquired by the system, prioritizing energy efficiency in the overall implementation.

## Software

### System Overview

#### Configuration

The system is designed to provide high modularity without sacrificing performance and energy efficiency. To achieve this, we utilize `#define` directives to configure various settings. When a configuration is turned off, all associated resources that would be utilized if it were activated are excluded and uninitialized.\\
This approach effectively saves energy and memory that would otherwise be unnecessarily wasted.

#### DataSet Management

To enhance modularity and save more energy, the system organizes data into datasets. Specifically, data is collected every `DISTANCE_BETWEEN_SET` seconds, with `DATA_PER_SET` data points captured at intervals of `DATA_DISTANCE` from each other.\\
This dataset approach allows for high-frequency data acquisition without continuous sampling, resulting in significant battery savings.

#### BLE Data Acquisition

Data is shared via BLE, specifically through the creation of a `DataSend` service with a UUID specified in the configuration file. Within this service, two characteristics, namely `Accelerometer` and `Gyroscope`, are established. Both characteristics have UUIDs that can be configured through the settings file (for more information, refer to [here](https://senk.nicolasferraresso.dev/#/installation_and_configuration?id=data-transmission-configuration)).

Both characteristics transmit an array of short values representing XYZ data. It is important to note that the data is transmitted in little-endian format.\\
For example, if our gyroscope sends something like 0xFFFF0F000200, the corresponding axes values are X: -1, Y: 15, Z: 2.\\
If needed, a conversion script is available [here](https://github.com/Magform/senk/tree/main/util/conversion) to translate the transmitted data into axis values.\\

### Class overview

#### Senk [main]

This is the main sketch, it manages sensor data acquisition with a focus on modularity and energy efficiency.\\
Here's a brief overview of its key components and functionalities:

1. **Sensor Handling:**
   - Initializes the BHY2 sensor, accelerometer (`accel`) and gyroscope (`gyro`) to capture essential data.
2. **Conditional Initializationg:**
   - Incorporates optional modules like `DataSaver` and `BLECommunication` based on configuration settings.
3. **Setup Routine:**
   - During the setup phase, initializes essential components such as serial communication, sensors and, if enabled, data saver and BLE communication.
4. **Data Acquisition Loop:**
   - Monitors elapsed time and capture new datasets based on the configured `DISTANCE_BETWEEN_SET`.
5. **Data Transmission and Scanning:**
   - Triggers data scanning and transmission via BLE based on configured conditions.

#### Data

The `Data` class encapsulates the representation and manipulation of sensor data, providing methods to convert, retrieve, and present information. \\
Here's a concise overview of the class:

1. **Constructors:**
   - `Data()`: Initializes all sensor values default value (-32768).
   - `Data(short accelX, short accelY, short accelZ, short gyroX, short gyroY, short gyroZ)`: Initializes sensor values based on provided parameters.
   - `Data(char* csv)`: Parses a CSV string to set sensor values.
2. **Accessor Methods:**
   - `getAccelerometerX()`, `getAccelerometerY()`, `getAccelerometerZ()`: Retrieve accelerometer values.
   - `getGyroscopeX()`, `getGyroscopeY()`, `getGyroscopeZ()`: Retrieve gyroscope values.
3. **Conversion Methods:**
   - `toString()`: Generates a formatted string containing accelerometer and gyroscope values.
   - `toCSV()`: Generates a CSV-formatted string of sensor data.

#### DataSaver

The `DataSaver` class is responsible for managing the storage and retrieval of sensor data, providing functionality to save data to local storage, format storage, print file contents, and retrieve specific data sets.\\
Below is a concise overview of the class:

1. **Constructors and Destructor:**
   - `DataSaver()`: Initializes the LittleFileSystem instance with the specified user root.
   - `~DataSaver()`: Destructor to handle cleanup and memory deallocation.
2. **Initialization and Formatting:**
   - `initialize(const char* fileName)`: Initializes the storage and specifies the file name.
   - `format()`: Reformats the storage.
3. **Data Saving and Retrieval:**
   - `saveData(Data toSave)`: Saves a single data entry to the file.
   - `saveData(Data toSave[], int length)`: Saves an array of data entries to the file.
   - `getData(Data* dataSet, int dataToReturn)`: This function retrieves datasets from a file, populates the provided array `dataSet` with the retrieved data, and ensures that each dataset is retrieved only once. If there is insufficient data available in the file to meet the requested number of datasets (`dataToReturn`), the remaining portion of the `dataSet` array is filled with void-initialized data.
4. **File Operations:**
   - `printFile()`: Outputs the entire content of the file to the Serial Monitor. The file is directly printed to avoid loading its potentially large size into RAM.

#### BLECommunication

The `BLECommunication` class serves as the central manager for Bluetooth Low Energy (BLE) communication, enabling the transmission of sensor data within the system. This class encapsulates crucial functions to handle initialization, data transmission, and BLE characteristic management.

1. **Constructors:**
   - `BLECommunication()`: Initializes the BLE service and characteristics. Details can be found in the [BLE Data Acquisition](#ble-data-acquisition) section below.
2. **Initialization:**
   - `initialize()`: Initializes the communication system by setting up the BLE service, characteristics, and device name. This method initiates the BLE functionality.
3. **Communication:**
    - `send(short aX, short aY, short aZ, short gX, short gY, short gZ)`: Sends a single set of accelerometer and gyroscope data via BLE. This function validates and transmits the provided data.
    - `send(Data toSend)`: Sends a single data entry using BLE. This method takes a `Data` object containing accelerometer and gyroscope values and transmits it.
    - `send(Data toSend[], int length)`: Sends an array of data entries using BLE. This method facilitates the transmission of multiple `Data` entries in succession.