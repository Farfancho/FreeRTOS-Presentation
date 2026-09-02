#include <Arduino.h>

#define BUILTIN_LED 2

void ledTask(void *parameter) {
    while (true) {
        digitalWrite(BUILTIN_LED, HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));

        digitalWrite(BUILTIN_LED, LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void serialTask(void *parameter) {
    while (true) {
        Serial.println("Hello!");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);

    xTaskCreate(
        ledTask,        // función
        "LED Task",     // nombre
        2048,           // stack
        NULL,           // parámetros
        1,              // prioridad
        NULL            // handle
    );

    xTaskCreate(
        serialTask,
        "Serial Task",
        2048,
        NULL,
        1,
        NULL
    );
}

void loop() {
}