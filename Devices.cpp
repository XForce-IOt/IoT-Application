#include "Devices.h"

Devices::Devices() {}

void Devices::begin(int dhtPin, int trigPin, int echoPin, int potPin, int ledPin) {
    dhtSensor = new DHTSensor(dhtPin);
    ultrasonicSensor = new UltrasonicSensor(trigPin, echoPin);
    pulseSensor = new PulseSensor(potPin, ledPin);
    Serial.println("Devices initialized");
}

void Devices::updateSensors() {
    TempAndHumidity values = dhtSensor->readValues(); // Cambia a -> para acceso con puntero
    if (!isnan(values.temperature)) {
        temperature = values.temperature;
        humidity = values.humidity;
    } else {
        Serial.println("Failed to read from DHT sensor!");
    }
}

float Devices::readTemperature() {
    return temperature;  // Devolver la temperatura
}

float Devices::readHumidity() {
    return humidity; // Devolver la humedad
}

long Devices::readDistance() {
    return ultrasonicSensor->measureDistance();
}

float Devices::readPulseVoltage() {
    return pulseSensor->readVoltage();
}
