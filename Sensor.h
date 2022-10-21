#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor
{
  public:
    Sensor(int address);
    virtual void Read();
  protected:
    bool _sensorFound;
  private:
    int _address;
};
#endif