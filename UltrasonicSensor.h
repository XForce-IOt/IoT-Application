#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

class UltrasonicSensor {
  private:
    int trigPin;
    int echoPin;

  public:
    UltrasonicSensor(int trigPin, int echoPin);
    long measureDistance();
};

#endif