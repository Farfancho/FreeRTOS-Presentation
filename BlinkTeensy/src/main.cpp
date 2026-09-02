#include <Arduino.h>

#define BUILTIN_LED 13

unsigned long previousMillis = 0;
const unsigned long interval = 500;

bool ledState = LOW;

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        ledState = !ledState;
        digitalWrite(BUILTIN_LED, ledState);

        Serial.println("Hello!");
    }
}