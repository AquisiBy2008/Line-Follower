#ifndef __MOTORS_H__
#define __MOTORS_H__

#include "Arduino.h"

class Motors
{
public:
    Motors();
    void setMotor(uint8_t motor, int16_t speed);
    void rotate();
    void stop();
    uint8_t calculateSpeed(uint8_t pwm, float amplitude, float theta, bool sum); 
private:
    uint8_t _pwmPins[2] = {5, 10}; // PWM pins for motor control
    uint8_t _inaPins[2] = {6, 9}; // INA pins for motor direction control
    uint8_t _inbPins[2] = {7, 8}; // INB pins for motor direction control

    uint8_t speed;
};

#endif // __MOTORS_H__