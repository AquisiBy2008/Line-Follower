#include <Arduino.h>
#include <Motors.h>
#include <Line_Sensors.h>

// LineSensors lineSensors;
// Motors motors;

// void setup() 
// {

// }

// void loop() 
// {
// }

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
}
