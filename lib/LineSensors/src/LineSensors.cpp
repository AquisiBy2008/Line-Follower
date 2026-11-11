
#include "LineSensors.h"

// Constructor
LineSensors::LineSensors()
{
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        _sensorReadings[i] = 0;
        _thresholds[i] = 0;
    }
}

// Inicializar los sensores
void LineSensors::begin()
{
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        pinMode(_sensorPins[i], INPUT);
    }

    // Encender emisores infrarrojos
    pinMode(IR_PIN, OUTPUT);
    digitalWrite(IR_PIN, HIGH);
}

// Calibración sobre blanco
void LineSensors::calibrateWhite()
{
    _calibrated = false;

    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        uint32_t sum = 0;

        for (uint8_t j = 0; j < CALIBRATION_SAMPLES; j++)
        {
            sum += analogRead(_sensorPins[i]);
        }

        uint16_t whiteAverage = sum / CALIBRATION_SAMPLES;

        if (BLACK_IS_HIGH)
        {
            _thresholds[i] = constrain(
                (int)whiteAverage + MARGIN, 0, 1023
            );
        }
        else
        {
            _thresholds[i] = constrain(
                (int)whiteAverage - MARGIN, 0, 1023
            );
        }
    }

    _calibrated = true;
}

// Actualizar lecturas analógicas
void LineSensors::readSensors()
{
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        _sensorReadings[i] = analogRead(_sensorPins[i]);
    }
}

// Obtener el estado de detección
bool LineSensors::isLineDetected(uint8_t sensor)
{
    if (sensor >= NUM_SENSORS || !_calibrated)
    {
        return false;
    }

    if (BLACK_IS_HIGH)
    {
        return _sensorReadings[sensor] > _thresholds[sensor];
    }
    else
    {
        return _sensorReadings[sensor] < _thresholds[sensor];
    }
}

// Obtener lectura analógica
uint16_t LineSensors::getReading(uint8_t sensor)
{
    if (sensor >= NUM_SENSORS)
    {
        return 0;
    }

    return _sensorReadings[sensor];
}

// Obtener umbral calibrado
uint16_t LineSensors::getThreshold(uint8_t sensor)
{
    if (sensor >= NUM_SENSORS)
    {
        return 0;
    }

    return _thresholds[sensor];
}
