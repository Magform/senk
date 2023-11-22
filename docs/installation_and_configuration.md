# Installation and Configuration

Follow these steps to set up and configure the **Senk** project on your device:

## Prerequisites

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

## Installation

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

## Configuration

The Senk project provides a range of configuration options, allowing you to customize its functionality based on your specific needs.\\
To make adjustments, locate the `Configuration.h` file in the project's root directory. \\
Options:

### Debugging Settings

- **DEBUG_STATUS:**
  - Set to `1` to activate debugging, `0` to deactivate.

### Data Configuration

Before configuring the data part, it's beneficial to understand how datasets function in Senk. \\
You can learn more about datasets [here](https://senk.nicolasferraresso.dev/#/implementation_analysis?id=dataset-management).

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

### Data Saving Configuration

- **DATA_SAVER_STATUS:**
  - Set to `1` to enable saving data to local storage, `0` to disable.

- **USER_ROOT:**
  - Specifies the root directory where the file will be saved. It is essential for this path to begin with "fs" to ensure proper file system navigation and storage functionality.

- **DELETE_FILE:**
  - Set to `1` to delete all files and only keep new data.

- **SAVE_FILE_NAME:**
  - Name of the file containing all saved data.

### Data Transmission configuration

- **SEND_DATASET:**
  - Set to `1` to send every dataset to Bluetooth after acquisition.

- **SEND_DATASET_THREAD:**
  - Set to 1, initiates a dedicated thread for transmitting every dataset to Bluetooth after acquisition.
  - Not functional if SEND_DATASET is enabled.
  - Although slightly more energy-consuming than SEND_DATASET, it significantly reduces the delay between two distinct dataset parts when the dataset size exceeds `MAX_DATASET_DIMENSION`.

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
  