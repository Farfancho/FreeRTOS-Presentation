#include <Arduino.h>


#define BUILTIN_LED 13

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);

    digitalWrite(BUILTIN_LED, LOW);
    delay(500);

    Serial.println("Hello!");
}
