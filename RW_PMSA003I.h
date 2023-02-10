#ifndef RW_PMSA003I_h
#define RW_PMSA003I_h

#include "RW_Sensor.h"
#include "Adafruit_PM25AQI.h"

class RW_PMSA003I : public RW_Sensor
{
  public:
    RW_PMSA003I();
    bool Detect();
    void Read(RW_Values * values);
    String GetName();
    String GetPrometheusMetrics(String location, RW_Values * values);
  private:
    Adafruit_PM25AQI _pm25;
};
#endif