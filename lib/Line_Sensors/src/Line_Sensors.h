#ifndef __LINE_SENSORS_H__
#define __LINE_SENSORS_H__

#include "Arduino.h"

class LineSensors
{
public:
    LineSensors();
    void update(); // Method to update sensor readings
    void readSensors();
    bool isLineDetected();
    uint8_t getSensorReading(uint8_t sensorIndex);
private:
    uint8_t _sensorPins[2] = {A5, A2}; // Digital pins for line sensors
    uint16_t _sensorReadings[2]; // Array to store sensor readings
};

#endif // __LINE-SENSORS_H__