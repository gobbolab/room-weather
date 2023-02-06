#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "SensorValues.h"
#include "RW_Helper.h"

class Sensor
{
  public:
    Sensor(int address);
    virtual void Read(SensorValues * values);
    virtual String GetPrometheusMetrics(String location, SensorValues * values);
    bool Found();
  protected:
    bool _sensorFound;
  private:
    int _address;
};
#endif