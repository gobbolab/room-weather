#ifndef RW_SGP30_h
#define RW_SGP30_h

#include "RW_Sensor.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

class RW_SGP30 : public RW_Sensor
{
  public:
    RW_SGP30();
    bool Detect();
    void Read(RW_Values * values);
    void Print(RW_Values * values);
    String GetName();
    String GetPrometheusMetrics(String location, RW_Values * values);
  private:
    Adafruit_SGP30 sgp;
};
#endif