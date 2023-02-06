#ifndef RW_SGP30_h
#define RW_SGP30_h

#include "Sensor.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

class RW_SGP30 : public Sensor
{
  public:
    RW_SGP30();
    void Read(SensorValues * values);
    String GetPrometheusMetrics(String location, SensorValues * values);
  private:
    Adafruit_SGP30 sgp;
};
#endif