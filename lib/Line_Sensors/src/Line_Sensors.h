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
    const bool* getReadings();
private:
    uint8_t _sensorPins[3] = {11, 12, 4}; // Digital pins for line sensors
    uint16_t _sensorReadings[3]; // Array to store sensor readings
};

#endif // __LINE-SENSORS_H__