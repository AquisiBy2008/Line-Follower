
#include <Arduino.h>
#include <LineSensors.h>

LineSensors sensors;

const unsigned long PRINT_INTERVAL = 500;
unsigned long previousMillis = 0;

void setup()
{
    Serial.begin(9600);

    sensors.begin();

    Serial.println("Coloque los sensores sobre BLANCO.");
    delay(3000);

    sensors.calibrateWhite();

    Serial.println("Calibracion finalizada.");

    for (uint8_t i = 0; i < 6; i++)
    {
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(" | Umbral: ");
        Serial.println(sensors.getThreshold(i));
    }

    Serial.println();
}

void loop()
{
    sensors.readSensors();

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= PRINT_INTERVAL)
    {
        previousMillis = currentMillis;

        Serial.println("------ SENSORES ------");

        for (uint8_t i = 0; i < 6; i++)
        {
            Serial.print("S");
            Serial.print(i + 1);

            Serial.print(" | Valor: ");
            Serial.print(sensors.getReading(i));

            Serial.print(" | Estado: ");

            if (sensors.isLineDetected(i))
            {
                Serial.println("NEGRO");
            }
            else
            {
                Serial.println("BLANCO");
            }
        }

        Serial.println("---------------------");
        Serial.println();
    }
}
