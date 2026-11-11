
#ifndef __LINE_SENSORS_H__
#define __LINE_SENSORS_H__

#include <Arduino.h>

class LineSensors
{
public:
    LineSensors();

    void begin();
    void calibrateWhite();
    void readSensors();

    bool isLineDetected(uint8_t sensor);

    uint16_t getReading(uint8_t sensor);
    uint16_t getThreshold(uint8_t sensor);

private:
    static const uint8_t NUM_SENSORS = 6;
    static const uint8_t IR_PIN = 3;

    uint8_t _sensorPins[NUM_SENSORS] = {
        A0, A1, A2, A3, A4, A5
    };

    uint16_t _sensorReadings[NUM_SENSORS];
    uint16_t _thresholds[NUM_SENSORS];

    bool _calibrated = false;

    static const uint8_t CALIBRATION_SAMPLES = 64;
    static const int MARGIN = 120;

    static const bool BLACK_IS_HIGH = true;
};

#endif // __LINE_SENSORS_H__
