#ifndef RW_SGP40_h
#define RW_SGP40_h

#include "RW_Sensor.h"
#include <Wire.h>
#include "Adafruit_SGP40.h"

class RW_SGP40 : public RW_Sensor
{
  public:
    RW_SGP40();
    bool Detect();
    void Read(RW_Values * values);
    void Print(RW_Values * values);
    String GetName();
    String GetPrometheusMetrics(String location, RW_Values * values);
  private:
    Adafruit_SGP40 sgp;
};
#endif