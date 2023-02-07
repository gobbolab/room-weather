#ifndef RW_Sensor_h
#define RW_Sensor_h

#include "Arduino.h"
#include "RW_Values.h"
#include "RW_Helper.h"

class RW_Sensor
{
  public:
    RW_Sensor(int address);
    virtual void Read(RW_Values * values);
    virtual String GetPrometheusMetrics(String location, RW_Values * values);
    bool Found();
  protected:
    bool _sensorFound;
  private:
    int _address;
};
#endif