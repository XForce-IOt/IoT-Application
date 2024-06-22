#ifndef PulseSensor_h
#define PulseSensor_h

#include "Arduino.h"

class PulseSensor {
private:
    int potPin;  // Pin del potenciómetro
    int ledPin;  // Pin del LED

public:
    PulseSensor(int potPin, int ledPin);
    float readVoltage();      // Lee el voltaje del potenciómetro
    void updateLed();         // Actualiza el brillo del LED basado en el voltaje
};

#endif
