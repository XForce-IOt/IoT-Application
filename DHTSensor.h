#ifndef DHTSensor_h
#define DHTSensor_h

#include "DHTesp.h"

class DHTSensor {
  private:
    DHTesp dht;
    int pin;

  public:
    DHTSensor(int pin);
    TempAndHumidity readValues();
};

#endif