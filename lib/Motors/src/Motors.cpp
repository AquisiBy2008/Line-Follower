#include <Motors.h>

Motors::Motors()
{
    // Constructor implementation
    for (uint8_t i = 0; i < 2; i++)
    {
        pinMode(_pwmPins[i], OUTPUT);
        pinMode(_inaPins[i], OUTPUT);
        pinMode(_inbPins[i], OUTPUT);
    }
}

void Motors::setMotor(uint8_t motor, int16_t speed)
{
    // Implementation for setting motor speed
    digitalWrite(_inaPins[motor - 1], speed > 0 ? HIGH : LOW);
    digitalWrite(_inbPins[motor - 1], speed < 0 ? HIGH : LOW);
    analogWrite(_pwmPins[motor - 1], abs(speed));
}

void Motors::move()
{
    // Implementation for moving the robot
    setMotor(1, 255);
    setMotor(2, 255);
}

void Motors::rotate()
{
    // Implementation for rotating the robot
    setMotor(1, 255);
    setMotor(2, -255);
}

void Motors::stop()
{
    // Implementation for stopping the robot
    setMotor(1, 0);
    setMotor(2, 0);
}