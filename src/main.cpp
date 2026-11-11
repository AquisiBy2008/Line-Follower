#include <Arduino.h>
#include <Motors.h>
#include <Line_Sensors.h>

LineSensors lineSensors;
Motors motors;

const uint32_t PRINT_INTERVAL = 500; // Interval for printing data in milliseconds
uint32_t lastPrintTime = 0;

bool lineDetected = false;
bool leftSensor = false;
bool rightSensor = false;
bool lastRightSensor = false;
bool lastLeftSensor = false;

uint8_t pwmLeft; // PWM value for left motor
uint8_t pwmRight; // PWM value for right motor
uint8_t pwmTest = 180;

void printData();

void setup() 
{
    Serial.begin(9600);
    Serial.println("Line Follower Robot Initialized");
    lastPrintTime = millis();
}

void loop() 
{
    lineSensors.update(); // Update sensor readings
    lineDetected = lineSensors.isLineDetected(); // Check if a line is detected
    leftSensor = lineSensors.getSensorReading(0); // Get reading from left sensor
    rightSensor = lineSensors.getSensorReading(1); // Get reading from right sensor

    if (leftSensor && !rightSensor)
    {
        //Izquierda
        pwmLeft = motors.calculateSpeed(pwmTest, 1, 0.0, false); // Calculate speed for left motor
        pwmRight = motors.calculateSpeed(pwmTest, 1, 0.0, true); // Calculate speed for right motor
        motors.setMotor(1, -pwmLeft);
        motors.setMotor(2, pwmRight + 50);
    }
    else if (!leftSensor && rightSensor)
    {
        //Derecha
        pwmLeft = motors.calculateSpeed(pwmTest, 1, 0.0, true); // Calculate speed for left motor
        pwmRight = motors.calculateSpeed(pwmTest, 1, 0.0, false); // Calculate speed for right motor
        motors.setMotor(1, pwmLeft +50);
        motors.setMotor(2, -pwmRight);
    }
    else if (!leftSensor && !rightSensor)
    {
        if (lastLeftSensor && !rightSensor)
        {
            //Izquierda
            pwmLeft = motors.calculateSpeed(pwmTest, 1, 0.0, false); // Calculate speed for left motor
            pwmRight = motors.calculateSpeed(pwmTest, 1, 0.0, true); // Calculate speed for right motor
            motors.setMotor(1, -pwmLeft);
            motors.setMotor(2, pwmRight + 50);
        }
        else if (lastRightSensor && !leftSensor)
        {
            //Derecha
            pwmLeft = motors.calculateSpeed(pwmTest, 1, 0.0, true); // Calculate speed for left motor
            pwmRight = motors.calculateSpeed(pwmTest, 1, 0.0, false); // Calculate speed for right motor
            motors.setMotor(1, pwmLeft + 50);
            motors.setMotor(2, -pwmRight);
        }

    }
    else
    {
        motors.stop();
    }

    // Derecha
    // pwmLeft = motors.calculateSpeed(pwmTest, 1, 0.0, true); // Calculate speed for left motor
    // pwmRight = motors.calculateSpeed(pwmTest, 1, 0.0, false); // Calculate speed for right motor
    // motors.setMotor(1, pwmLeft);
    // motors.setMotor(2, pwmRight);

    if (leftSensor != 0 && rightSensor != 0)
    {
        lastLeftSensor = leftSensor;
        lastRightSensor = rightSensor;
    }

    if (millis() - lastPrintTime >= PRINT_INTERVAL)
    {
        printData(); // Print data to Serial Monitor
        lastPrintTime = millis();
    }
}

void printData()
{
    Serial.print("-------------------------------\n");
    Serial.print("LeftSensor: ");
    Serial.print(leftSensor);
    Serial.print(" | RightSensor: ");
    Serial.println(rightSensor);
    Serial.print("lastLeftSensor: ");
    Serial.print(lastLeftSensor);
    Serial.print(" | lastRightSensor: ");
    Serial.println(lastRightSensor);
}