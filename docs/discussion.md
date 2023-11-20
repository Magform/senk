# Discussion

## 1. Optimization Strategies

Within the scope of this project, prioritizing resource and energy efficiency emerged as a pivotal focus during development. To accomplish this objective, I explored and implemented several optimization techniques aimed at maximizing system efficiency. Key strategies included:

- **Initialization via Define:** Employed `#define` directives for configuration settings, enabling efficient resource allocation by excluding and initializing unused configurations, thus conserving energy and memory.

- **Simulated High-Frequency Data Acquisition:** Implemented a strategy alternating high-frequency data collection intervals with periods of inactivity. This approach ensured high-frequency data availability while conserving battery power by avoiding continuous sampling during idle periods.

- **Utilization of BLE (Bluetooth Low Energy):** Leveraged BLE technology for data transmission, facilitating efficient communication with minimal power consumption compared to traditional Bluetooth, thus enhancing energy efficiency in data transfer operations.

## 2. Energy consumption

## 3 Future plan

### 3.1 Code refactoring

Optimize and streamline the codebase with the following refactorings:

#### Doxygen documentation

### 3.2 Hardware

#### Developing a 3D-Printable Waterproof Case

Create a 3D-printable waterproof case suitable for the project's needs. The primary objective is to design a case capable of securely housing a battery while incorporating wireless recharging capabilities. By utilizing wireless recharging, we aim to enhance water resistance by eliminating the need to open the case for battery recharging.