#ifndef Devices_h
#define Devices_h

#include "DHTSensor.h"
#include "UltrasonicSensor.h"
#include "PulseSensor.h"

class Devices {
  public:
    Devices();
    void begin(int dhtPin, int trigPin, int echoPin, int potPin, int ledPin);
    void updateSensors();  // Actualizar todos los sensores
    float readTemperature();
    float readHumidity();
    long readDistance();
    float readPulseVoltage();

  private:
    DHTSensor* dhtSensor;
    UltrasonicSensor* ultrasonicSensor;
    PulseSensor* pulseSensor;
    float temperature = 0.0;
    float humidity = 0.0;
};

#endif
