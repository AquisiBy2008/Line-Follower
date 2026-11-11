
#include <Arduino.h>
#include <Motors.h>
#include <LineSensors.h>

// Objetos
Motors motors;
LineSensors sensors;

// Configuración de sensores
const uint8_t NUM_SENSORS = 6;

const int16_t sensorPositions[NUM_SENSORS] = {
    -2500, -1500, -500, 500, 1500, 2500
};

// Parámetros del controlador
const int16_t PWM_BASE = 150;
const float KP = 0.025f;
const int16_t MAX_CORRECTION = 90;

// Parámetros de búsqueda
const int16_t SEARCH_PWM = 110;
const unsigned long LOST_TIMEOUT = 500;

// Intervalos
const unsigned long UPDATE_INTERVAL = 10;
const unsigned long PRINT_INTERVAL = 250;

// Variables
unsigned long previousUpdate = 0;
unsigned long previousPrint = 0;
unsigned long lastLineMillis = 0;

int16_t error = 0;
int16_t correction = 0;
int16_t pwmLeft = 0;
int16_t pwmRight = 0;

int8_t lastDirection = 0;
bool lineFound = false;
bool lineEverFound = false;

// Calcular posición de la línea
bool calculateLinePosition()
{
    int32_t weightedSum = 0;
    uint8_t activeSensors = 0;

    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        if (sensors.isLineDetected(i))
        {
            weightedSum += sensorPositions[i];
            activeSensors++;
        }
    }

    // Ningún sensor detecta negro
    if (activeSensors == 0)
    {
        return false;
    }

    error = weightedSum / activeSensors;

    // Guardar la última dirección conocida
    if (error < -100)
    {
        lastDirection = -1;
    }
    else if (error > 100)
    {
        lastDirection = 1;
    }

    return true;
}

// Control proporcional
void followLine()
{
    correction = constrain(
        (int16_t)(KP * error),
        -MAX_CORRECTION,
        MAX_CORRECTION
    );

    pwmLeft = constrain(
        PWM_BASE + correction, 0, 255
    );

    pwmRight = constrain(
        PWM_BASE - correction, 0, 255
    );

    motors.setMotor(1, pwmLeft-100);
    motors.setMotor(2, pwmRight);
}

// Buscar la línea cuando se pierde

void searchLine()
{
    // Si nunca se detectó la línea, detenerse
    if (!lineEverFound)
    {
        motors.stop();
        pwmLeft = 0;
        pwmRight = 0;
        return;
    }

    // Detenerse si supera el tiempo de búsqueda
    if (millis() - lastLineMillis > LOST_TIMEOUT)
    {
        motors.stop();
        pwmLeft = 0;
        pwmRight = 0;
        return;
    }

    if (lastDirection == -1)
    {
        // Antes giraba a la izquierda
        // Ahora buscar hacia la derecha
        pwmLeft = SEARCH_PWM;
        pwmRight = 0;
    }
    else if (lastDirection == 1)
    {
        // Antes giraba a la derecha
        // Ahora buscar hacia la izquierda
        pwmLeft = 0;
        pwmRight = SEARCH_PWM;
    }
    else
    {
        motors.stop();
        pwmLeft = 0;
        pwmRight = 0;
        return;
    }

    motors.setMotor(1, pwmLeft);
    motors.setMotor(2, pwmRight);
}


// Información de depuración
void printData()
{
    Serial.print("Sensores: ");

    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(
            sensors.isLineDetected(i) ? "1 " : "0 "
        );
    }

    Serial.print("| Error: ");
    Serial.print(error);

    Serial.print(" | PWM L: ");
    Serial.print(pwmLeft);

    Serial.print(" | PWM R: ");
    Serial.print(pwmRight);

    Serial.print(" | Linea: ");
    Serial.println(lineFound ? "SI" : "NO");
}

void setup()
{
    Serial.begin(9600);

    sensors.begin();
    motors.stop();

    Serial.println("Coloque los sensores sobre BLANCO.");
    delay(3000);

    sensors.calibrateWhite();

    Serial.println("Calibracion finalizada.");
    Serial.println("Iniciando seguimiento...");
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousUpdate >= UPDATE_INTERVAL)
    {
        previousUpdate = currentMillis;

        // Actualizar las lecturas analógicas
        sensors.readSensors();

        // Determinar posición de línea
        lineFound = calculateLinePosition();

        if (lineFound)
        {
            lineEverFound = true;
            lastLineMillis = currentMillis;

            // Aplicar control proporcional
            followLine();
        }
        else
        {
            // Ejecutar búsqueda
            searchLine();
        }
    }

    if (currentMillis - previousPrint >= PRINT_INTERVAL)
    {
        previousPrint = currentMillis;
        printData();
    }
}
