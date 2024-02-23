#ifndef RWHelper_h
#define RWHelper_h

#include "Arduino.h"
#include "RW_Values.h"

#define METRIC_TEMP "metric=\"temperature\""
#define METRIC_HUMIDITY "metric=\"humidity\""
#define METRIC_ABSOLUTE_HUMIDITY "metric=\"absolute_humidity\""
#define METRIC_VOC "metric=\"voc\""
#define METRIC_CO2 "metric=\"co2\""
#define METRIC_PM10 "matric=\"pm1.0\""
#define METRIC_PM25 "matric=\"pm2.5\""
#define METRIC_PM100 "matric=\"pm10\""
#define METRIC_GT_03_UM_PER_LITER_AIR "matric=\"gt_0.3_um_per_0.1_liter_air\""
#define METRIC_GT_05_UM_PER_LITER_AIR "matric=\"gt_0.5_um_per_0.1_liter_air\""
#define METRIC_GT_10_UM_PER_LITER_AIR "matric=\"gt_1_um_per_0.1_liter_air\""
#define METRIC_GT_25_UM_PER_LITER_AIR "matric=\"gt_2.5_um_per_0.1_liter_air\""
#define METRIC_GT_50_UM_PER_LITER_AIR "matric=\"gt_5_um_per_0.1_liter_air\""
#define METRIC_GT_100_UM_PER_LITER_AIR "matric=\"gt_10_um_per_0.1_liter_air\""
#define UNIT_FAHRENHEIT "unit=\"fahrenheit\""
#define UNIT_CELSIUS "unit=\"celsius\""
#define UNIT_PERCENT "unit=\"percent\""
#define UNIT_GRAM_PER_M3 "unit=\"gram_per_m3\""
#define UNIT_PPM "unit=\"ppm\""
#define UNIT_PPB "unit=\"ppb\""
#define UNIT_STANDARD "unit=\"standard\""
#define UNIT_ENVIRONMENTAL "unit=\"environmental\""
#define UNIT_PARTICLES "unit=\"particles\""

class RW_Helper
{
  public:
    static bool Htu31dFound;
    static bool Sgp30Found;
    static bool Pmsa003iFound;
    static String ToPrometheusMetric(String name, float value, String location, String metric, String unit);
    static float CelsiusToFahrenheit(float temperature);
    static float CalculateAbsoluteHumidity(float relative_humidity, float temperature);
    static bool HasTimeElapsed(unsigned long timeStamp, int period);
};
#endif