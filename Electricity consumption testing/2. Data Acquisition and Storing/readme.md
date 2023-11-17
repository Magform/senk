# Data Acquisition and Storage

Within this context, we have two distinct sketches:

## Data Acquisition and Storage using RAM

This sketch is designed to collect data from sensors and, when a specific flag is enabled, display this data on the serial monitor. The data is organized into datasets, with the quantity determined in the configuration file. These datasets are temporarily stored in RAM using an array of Data (a custom-defined data type)\\
The primary goal is to assess resource usage during the data acquisition and printing process while data resides in RAM.

## Data Acquisition and Storage using QSPI Flash

This sketch is designed to collect data from sensors. The data is organized into datasets, with the quantity determined in the configuration file. These datasets are temporarily stored in RAM using an array of Data (a custom-defined data type). After a complete dataset is collected, it will be saved to the microcontroller's QSPI flash memory.\\
The objective is to assess resource usage during the data acquisition and printing process while data is also saved in the internal QSPI Flash memory.\\
Problem is that saving to QSPI is *really slow* depending on how meny data we had saved and also that if we cannot store more than 50 data in a dataSet

## Data Acquisition and Storage with infinity size dataSet

This sketch is designed to collect data from sensors. The data is organized into datasets, with the quantity determined in the configuration file. These datasets are temporarily stored in RAM using an array of Data (a custom-defined data type). After a complete dataset is collected, it will be saved to the microcontroller's QSPI flash memory.\\
The objective is to assess resource usage during the data acquisition and printing process while data is also saved in the internal QSPI Flash memory.\\
Problem is that saving to QSPI is *really slow* depending on how meny data we had saved, to avoid the second problem we split the total data into multiple dataSet take in sequency so we have the problem that since after evry dataset we need to save the data is not continuos.
