#ifndef RWHelper_h
#define RWHelper_h

#include "Arduino.h"
#include "RW_Values.h"

#define METRIC_TEMP "metric=\"temperature\""
#define METRIC_HUMIDITY "metric=\"humidity\""
#define METRIC_ABSOLUTE_HUMIDITY "metric=\"absolute_humidity\""
#define METRIC_VOC "metric=\"voc\""
#define METRIC_CO2 "metric=\"co2\""
#define UNIT_FAHRENHEIT "unit=\"fahrenheit\""
#define UNIT_CELSIUS "unit=\"celsius\""
#define UNIT_PERCENT "unit=\"percent\""
#define UNIT_GRAM_PER_M3 "unit\"gram_per_m3\""
#define UNIT_PPM "unit=\"ppm\""
#define UNIT_PPB "unit=\"ppb\""

class RW_Helper
{
  public:
    static bool Htu31dFound;
    static bool Sgp30Found;
    static String ToPrometheusMetric(String name, float value, String location, String metric, String unit);
    static float CelsiusToFahrenheit(float temperature);
    static float CalculateAbsoluteHumidity(float relative_humidity, float temperature);
};
#endif