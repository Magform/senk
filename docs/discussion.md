# Discussion

## 1. Optimization Strategies

Within the scope of this project, prioritizing resource and energy efficiency emerged as a pivotal focus during development. To accomplish this objective, I explored and implemented several optimization techniques aimed at maximizing system efficiency. Key strategies included:

- **Initialization via Define:** Employed `#define` directives for configuration settings, enabling efficient resource allocation by excluding and initializing unused configurations, thus conserving energy and memory.

- **Simulated High-Frequency Data Acquisition:** Implemented a strategy alternating high-frequency data collection intervals with periods of inactivity. This approach ensured high-frequency data availability while conserving battery power by avoiding continuous sampling during idle periods.

- **Utilization of BLE (Bluetooth Low Energy):** Leveraged BLE technology for data transmission, facilitating efficient communication with minimal power consumption compared to traditional Bluetooth, thus enhancing energy efficiency in data transfer operations.

- **Utilization of Multiple Threads:** Employed multiple threads to continuously capture data between parts of the same dataset, ensuring minimal delay and ensuring consistent data flow throughout the application.

## 2. Power consumption

For a more comprehensive explanation of the tests carried out and the results identified, see the section [power consumption](https://senk.nicolasferraresso.dev/#/power_consumption)

### DataSet Size and Intervals

- **Larger Datasets:** Demonstrated higher power consumption due to prolonged active periods during data reading.
- **Data Point Intervals:** Higher intervals showed increased power consumption due to extended working time for data reading.
- **Set Intervals:** Larger intervals consistently resulted in lower power consumption due to increased sleeping times between data set processing.

### Data Saver Settings

- **Data Saver:** Showcased significant power differences based on varying `DATA_PER_ITERATION` values.
- **Data Saver Keep Open:** Energy efficiency improved a lot compared to `DATA_SAVER`, especially with lower `DATA_PER_ITERATION``, reducing the total file opening and file closing operation.

### Data Transmission Methods

- **Send DataSet:** Slightly increased power consumption, primarily influenced by the volume of data to be sent.
- **Send DataSet Thread:** Marginal differences in power consumption compared to non-thread transmission, but notable fluctuations observed in practice tests.
- **Data Sender:** Increased power consumption due to additional processing involved in writing and reading data from internal storage.

### Scanning and Transmission Parameters

- **Data_to_Scan:** Significant power consumption variation based on scanning for actual versus non-existent data.
- **Scan Time:** Adjusting scan times showcased a trade-off between intervals and data read, impacting power efficiency and risking data loss if reading time exceeds sleeping time.

### Overall Observations

- **Optimization Balance:** Optimizing file handling processes and transmission methods is critical for power efficiency.
- **System Dynamics:** Understanding the interplay of intervals, dataset size, and transmission settings aids in maximizing performance while conserving energy.

These observations underscore the importance of meticulous system configuration to strike an optimal balance between performance and energy consumption across various operational scenarios.

## 3 Future plan

### 3.1 Code refactoring

Optimize and streamline the codebase with the following refactorings:

#### Doxygen documentation

### 3.2 Hardware

#### Developing a 3D-Printable Waterproof Case

Create a 3D-printable waterproof case suitable for the project's needs. The primary objective is to design a case capable of securely housing a battery while incorporating wireless recharging capabilities. By utilizing wireless recharging, we aim to enhance water resistance by eliminating the need to open the case for battery recharging.
