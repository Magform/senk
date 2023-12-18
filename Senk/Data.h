#ifndef Data_H_
#define Data_H_

#include <Arduino.h>

/**
 * @class Data
 * @brief Represents a set of sensor data containing accelerometer and gyroscope readings.
 */
class Data {
  private:
    short accelerometerX; ///< Accelerometer X-axis value
    short accelerometerY; ///< Accelerometer Y-axis value
    short accelerometerZ; ///< Accelerometer Z-axis value
    short gyroscopeX;     ///< Gyroscope X-axis value
    short gyroscopeY;     ///< Gyroscope Y-axis value
    short gyroscopeZ;     ///< Gyroscope Z-axis value

  public:
    /**
     * @brief Default constructor.
     * Initializes all sensor readings to -32768.
     */
    Data();

    /**
     * @brief Constructor to initialize sensor readings with specific values.
     * 
     * @param accelX Accelerometer X-axis value.
     * @param accelY Accelerometer Y-axis value.
     * @param accelZ Accelerometer Z-axis value.
     * @param gyroX Gyroscope X-axis value.
     * @param gyroY Gyroscope Y-axis value.
     * @param gyroZ Gyroscope Z-axis value.
     */
    Data(short accelX, short accelY, short accelZ, short gyroX, short gyroY, short gyroZ);

    /**
     * @brief Constructor to initialize sensor readings from a CSV string.
     * 
     * @param csv CSV-formatted string containing sensor readings.
     */
    Data(char* csv);

    // Getter methods for sensor readings
    short getAccelerometerX() const; ///< Getter for accelerometer X-axis value.
    short getAccelerometerY() const; ///< Getter for accelerometer Y-axis value.
    short getAccelerometerZ() const; ///< Getter for accelerometer Z-axis value.
    short getGyroscopeX() const;     ///< Getter for gyroscope X-axis value.
    short getGyroscopeY() const;     ///< Getter for gyroscope Y-axis value.
    short getGyroscopeZ() const;     ///< Getter for gyroscope Z-axis value.

    /**
     * @brief Converts the sensor readings to a string format.
     * 
     * @return A pointer to a character array containing the sensor readings in a formatted string.
     */
    const char* toString() const;

    /**
     * @brief Converts the sensor readings to a CSV-formatted string.
     * 
     * @return A pointer to a character array containing the sensor readings in CSV format.
     */
    const char* toCSV() const;
};

#endif // Data_H_
