#include "PulseSensor.h"

PulseSensor::PulseSensor(int potPin, int ledPin) : potPin(potPin), ledPin(ledPin) {
    pinMode(potPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

float PulseSensor::readVoltage() {
    int value = analogRead(potPin);
    return (value * 3.3) / 4095.0; // Asume que el máximo es 4095 y Vmax es 3.3V
}

void PulseSensor::updateLed() {
    int value = analogRead(potPin);
    int brightness = (value * 255) / 4095; // Escala el valor a un rango de 0-255
    analogWrite(ledPin, brightness);
}
