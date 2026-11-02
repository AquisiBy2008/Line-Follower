#include <Arduino.h>
#include <Motors.h>
#include <Line_Sensors.h>

LineSensors lineSensors;
Motors motors;

const uint32_t PRINT_INTERVAL = 100; // Interval for printing data in milliseconds
uint32_t lastPrintTime = 0;

bool lineDetected = false;
bool leftSensor = false;
bool rightSensor = false;

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
    //motors.move(); // Move the robot forward

    if (leftSensor)
    {
        motors.setMotor(2, 255);
        motors.setMotor(1, 200);
    }
    if (rightSensor)
    {
        motors.setMotor(2, 200);
        motors.setMotor(1, 255);
    }

    if (millis() - lastPrintTime >= PRINT_INTERVAL)
    {
        printData(); // Print data to Serial Monitor
        lastPrintTime = millis();
    }
}

void printData()
{
    Serial.print("Tiempo: ");
    Serial.print(millis());
    Serial.print(" ms \n");
    Serial.print("Linea detectada: ");
    Serial.println(lineDetected ? "Sí" : "No");
}