# Senk

> Accelerometer and Gyroscope Sensor

## Introduction

**Senk** is a project centered around leveraging the capabilities of a Nicla Sense ME to create a highly configurable device equipped with both an accelerometer and a gyroscope sensor.

### Objectives

The primary objectives of this project include:

- **Sensor Integration:** Utilize the accelerometer and gyroscope sensors provided by Nicla Sense ME.
  
- **Configurability:** Design the device to be highly configurable using a simple configuration file, allowing for versatile applications.

- **Energy Efficiency:** Implement energy-efficient practices to optimize power consumption. With high customization, we aim to minimize unnecessary power usage.

- **Data Handling:** Enable the device to store sensor data in its internal memory and facilitate data transmission via Bluetooth Low Energy.

## Implementation Analysis

### Hardware Configuration

#### Arduino Nicla Sense Me

The foundation of the entire system relies on the Arduino [Nicla Sense Me](https://docs.arduino.cc/hardware/nicla-sense-me). This versatile platform integrates various sensors and communication modules crucial for the project.

##### BHI260AP - 16-Bit 6-Axis IMU

The cornerstone sensor, BHI260AP, serves as a 16-bit 6-axis Inertial Measurement Unit (IMU), encompassing a 3-axis accelerometer and a 3-axis gyroscope. This pivotal component captures essential acceleration and gyroscope data from the surrounding environment.

##### 2MB QSPI Flash Memory

The 2MB QSPI flash memory plays a vital role in storing system data. However, it's essential to note that the write speed of this memory is relatively slow.

##### Bluetooth 5.0 Low Energy (BLE)

To optimize energy consumption, the project strategically utilizes Bluetooth Low Energy (BLE) for data communication. This efficient protocol ensures seamless transmission of data acquired by the system, prioritizing energy efficiency in the overall implementation.

### Software

#### System Overview

##### High modularaty

The system is designed to provide high modularity without sacrificing performance and energy efficiency. To achieve this, we utilize `#define` directives to configure various settings. When a configuration is turned off, all associated resources that would be utilized if it were activated are excluded and uninitialized.\\
This approach effectively saves energy and memory that would otherwise be unnecessarily wasted.

##### DataSet Management

To enhance modularity and save more energy, the system organizes data into datasets. Specifically, data is collected every `DISTANCE_BETWEEN_SET` seconds, with `DATA_PER_SET` data points captured at intervals of `DATA_DISTANCE` from each other.\\
This dataset approach allows for high-frequency data acquisition without continuous sampling, resulting in significant battery savings.

##### BLE Data Acquisition

Data is shared via BLE, specifically through the creation of a `DataSend` service with a UUID specified in the configuration file. Within this service, two characteristics, namely `Accelerometer` and `Gyroscope`, are established. Both characteristics have UUIDs that can be configured through the settings file (for more information, refer to [here]()).

Both characteristics transmit an array of short values representing XYZ data. It is important to note that the data is transmitted in little-endian format.\\
For example, if our gyroscope sends something like 0xFFFF0F000200, the corresponding axes values are X: -1, Y: 15, Z: 2.\\
If needed, a conversion script is available [here]() to translate the transmitted data into axis values.\\

#### Class overview

##### Senk [main]

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

##### Data

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

##### DataSaver

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

##### BLECommunication

The `BLECommunication` class serves as the central manager for Bluetooth Low Energy (BLE) communication, enabling the transmission of sensor data within the system. This class encapsulates crucial functions to handle initialization, data transmission, and BLE characteristic management.

1. **Constructors:**
   - `BLECommunication()`: Initializes the BLE service and characteristics. Details can be found in the [BLE Data Acquisition](#ble-data-acquisition) section below.
2. **Initialization:**
   - `initialize()`: Initializes the communication system by setting up the BLE service, characteristics, and device name. This method initiates the BLE functionality.
3. **Communication:**
    - `send(short aX, short aY, short aZ, short gX, short gY, short gZ)`: Sends a single set of accelerometer and gyroscope data via BLE. This function validates and transmits the provided data.
    - `send(Data toSend)`: Sends a single data entry using BLE. This method takes a `Data` object containing accelerometer and gyroscope values and transmits it.
    - `send(Data toSend[], int length)`: Sends an array of data entries using BLE. This method facilitates the transmission of multiple `Data` entries in succession.

## Installation and Configuration

Follow these steps to set up and configure the **Senk** project on your device:

### Prerequisites

1. **Hardware Setup:**
   - Ensure you have the Nicla Sense ME properly connected to your device.

2. **Arduino IDE:**
   - Install the Arduino IDE on your development machine if not already installed.

3. **Required Libraries:**
    - Make sure to have the following libraries installed in your Arduino IDE. You can install them using the Library Manager in the Arduino IDE.
        - Nicla_System
        - Arduino_BHY2
        - LittleFileSystem
        - ArduinoBLE
        - mbed
        - File
        - FileSystem

### Installation

1. **Download the Project:**
   - Clone or download the [Senk project from the repository](https://github.com/Magform/senk).

2. **Open Project in Arduino IDE:**
   - Open the Arduino IDE.
   - Load the Senk project by selecting the Senk.ino file.

3. **Configure the Arduino IDE:**
   - Ensure you have the necessary board and port selected in the Arduino IDE.

4. **Configure senk:**
   - Customize Senk according to your preferences by following the [configuration guide](#configuration).

5. **Upload the Code:**
   - Upload the Senk code to your Nicla Sense ME.

### Configuration

The Senk project provides a range of configuration options, allowing you to customize its functionality based on your specific needs.\\
To make adjustments, locate the `Configuration.h` file in the project's root directory. \\
Options:

#### Debugging Settings

- **DEBUG_STATUS:**
  - Set to `1` to activate debugging, `0` to deactivate.

#### Data Configuration

Before configuring the data part, it's beneficial to understand how datasets function in Senk. \\
You can learn more about datasets [here](link-to-your-dataset-explanation).

- **DATA_PER_SET:**
  - Total number of data in a dataset.
  - For better performace is suggested to keep this lower than `MAX_DATASET_DIMENSION`

- **DATA_DISTANCE:**
  - Milliseconds of distance between two different data.
  - Frist data is always taken at the startup

- **DISTANCE_BETWEEN_SET:**
  - Milliseconds to wait between two different datasets. Measured from the first data of the current dataset to the last data of the previous dataset.

- **MAX_DATASET_DIMENSION:**
  - If a dataset surpasses a certain size, it cannot fit entirely into RAM. To accommodate larger datasets, we automatically break them into manageable parts based on the dimension specified here.
  - After processing each part of the complete dataset, the data is dynamically managed – either stored in local storage or transmitted using Bluetooth Low Energy (BLE), contingent on your configuration settings.
  - It's crucial to acknowledge that this segmentation process introduces a minor slowdown, especially when saving data to local storage. Take this into consideration while optimizing for swift data processing.
  - Note: When using all functionalities simultaneously, it is racommended to set this value equal or less than 150.
  - Adjusting this value becomes crucial when aiming for optimal performance.

#### Data Saving Configuration

- **DATA_SAVER_STATUS:**
  - Set to `1` to enable saving data to local storage, `0` to disable.

- **USER_ROOT:**
  - Specifies the root directory where the file will be saved. It is essential for this path to begin with "fs" to ensure proper file system navigation and storage functionality.

- **DELETE_FILE:**
  - Set to `1` to delete all files and only keep new data.

- **SAVE_FILE_NAME:**
  - Name of the file containing all saved data.

#### Data Transmission configuration

- **SEND_DATASET:**
  - Set to `1` to send every dataset to Bluetooth after acquisition.

- **DATA_SENDER:**
  - This option enables reading data from the file and sending it through Bluetooth. It functions only when `DATA_SAVER_STATUS` is enabled. The program scans and sends all available data once during its execution.

- **DATA_TO_SCAN:**
  - Specifies the total lines to read and send in each file scan. If this value exceeds the remaining data to scan, the sender transmits all remaining data.
  - Be cautious, as setting it larger than necessary may result in slower performance. It is recommended to keep this value optimized for efficient processing.

- **SCAN_TIME:**
  - Sets the interval between two consecutive file scans.
  - The specified time is taken after the completion of the previous scan.
  - If new data is added during this interval, it will be sent.

- **SERVICE_UUID:**
  - UUID for the main service used in the BLE communication

- **ACCELEROMETER_UUID:**
  - UUID for the BLE characteristic representing accelerometer data

- **GYROSCOPE_UUID:**
  - UUID for the BLE characteristic representing gyroscope
  
## Useful Links

### Project Website

Visit the official SENK website for additional resources and information: [SENK Website](senk.nicolasferraresso.dev)

### GitHub Repository

Access the project's source code and contribute on GitHub: [SENK GitHub Repository](https://github.com/Magform/senk)
