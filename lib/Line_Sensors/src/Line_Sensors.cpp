#include <Line_Sensors.h>

LineSensors::LineSensors()
{
    // Constructor implementation
    for (uint8_t i = 0; i < 3; i++)
    {
        pinMode(_sensorPins[i], INPUT);
    }
}

void LineSensors::update()
{
    // Implementation for updating sensor readings
    readSensors();
}

void LineSensors::readSensors()
{
    // Implementation for reading sensor values
    for (uint8_t i = 0; i < 3; i++)
    {
        _sensorReadings[i] = digitalRead(_sensorPins[i]);
    }
}

bool LineSensors::isLineDetected()
{
    // Implementation for checking if a line is detected
    for (uint8_t i = 0; i < 3; i++)
    {
        if (_sensorReadings[i] == HIGH)
        {
            return true; // Line detected
        }
    }
    return false; // No line detected
}

const bool* LineSensors::getReadings()
{
    // Implementation for getting sensor readings
    static bool readings[3];
    for (uint8_t i = 0; i < 3; i++)
    {
        readings[i] = (_sensorReadings[i] == HIGH);
    }
    return readings;
}