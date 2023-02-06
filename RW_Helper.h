#ifndef RWHelper_h
#define RWHelper_h

#include "Arduino.h"
#include "RW_Values.h"

#define METRIC_TEMP "metric=\"temperature\""
#define METRIC_HUMIDITY "metric=\"humidity\""
#define METRIC_VOC "metric=\"voc\""
#define METRIC_CO2 "metric=\"co2\""
#define UNIT_FAHRENHEIT "unit=\"fahrenheit\""
#define UNIT_CELSIUS "unit=\"celsius\""
#define UNIT_PERCENT "unit=\"percent\""
#define UNIT_PPM "unit=\"ppm\""
#define UNIT_PPB "unit=\"ppb\""

class RW_Helper
{
  public:
    static String ToPrometheusMetric(String name, float value, String location, String metric, String unit);
};
#endif