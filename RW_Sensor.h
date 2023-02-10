#ifndef RW_Sensor_h
#define RW_Sensor_h

#include "Arduino.h"
#include "RW_Values.h"
#include "RW_Helper.h"

class RW_Sensor
{
  public:
    RW_Sensor();
    virtual bool Detect();
    virtual void Read(RW_Values * values);
    virtual String GetName();
    virtual String GetPrometheusMetrics(String location, RW_Values * values);
    bool Found();
  protected:
    bool _sensorFound;
};
#endif