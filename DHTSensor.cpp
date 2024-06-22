#include "DHTSensor.h"

DHTSensor::DHTSensor(int pin) : pin(pin) {
  dht.setup(pin, DHTesp::DHT22); // Configuración del sensor
}

TempAndHumidity DHTSensor::readValues() {
  return dht.getTempAndHumidity(); // Leer y devolver los valores
}