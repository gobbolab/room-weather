#ifndef RW_PM25AQI_h
#define RW_PM25AQI_h

#include "RW_Sensor.h"
#include "Adafruit_PM25AQI.h"

class RW_PM25AQI : public RW_Sensor
{
  public:
    RW_PM25AQI();
    void Read(RW_Values * values);
    String GetPrometheusMetrics(String location, RW_Values * values);
  private:
    Adafruit_PM25AQI _pm25;
};
#endif