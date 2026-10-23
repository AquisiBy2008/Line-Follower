#ifndef __MOTORS_H__
#define __MOTORS_H__

#include "Arduino.h"

class Motors
{
public:
    Motors();
    void setMotor(uint8_t motor, int16_t speed);
    void move();
    void rotate();
    void stop();
private:
    uint8_t _pwmPins[2] = {5, 10}; // PWM pins for motor control
    uint8_t _inaPins[2] = {6, 9}; // INA pins for motor direction control
    uint8_t _inbPins[2] = {7, 8}; // INB pins for motor direction control
};

#endif // __MOTORS_H__