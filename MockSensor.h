#ifndef MockSensor_h
#define MockSensor_h

#include "Sensor.h"

class MockSensor : public Sensor
{
  public:
    MockSensor(int address);
    void Read();
    String GetValue();
  private:
    int _address;
    int _value;
};
#endif