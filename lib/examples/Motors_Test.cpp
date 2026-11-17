#include <Arduino.h>
#include <Motors.h>

// Crear objeto de motores
Motors motors;

// Configuración de velocidades
const int16_t PWM_BASE = 150;
const int16_t PWM_TURN = 100;

void setup()
{
    motors.stop();
}

void loop()
{
    // Avanzar durante 2 segundos
    motors.setMotor(1, PWM_BASE);
    motors.setMotor(2, PWM_BASE);
    delay(2000);

    // Girar hacia la izquierda
    motors.setMotor(1, PWM_TURN);
    motors.setMotor(2, PWM_BASE);
    delay(1000);

    // Girar hacia la derecha
    motors.setMotor(1, PWM_BASE);
    motors.setMotor(2, PWM_TURN);
    delay(1000);

    // Retroceder durante 2 segundos
    motors.setMotor(1, -PWM_BASE);
    motors.setMotor(2, -PWM_BASE);
    delay(2000);

    // Detener los motores
    motors.stop();
    delay(2000);
}