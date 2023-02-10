#include "RW_PM25AQI.h"
#include "RW_Helper.h"

RW_PM25AQI::RW_PM25AQI() {
    _pm25 = Adafruit_PM25AQI();

    // if (!_pm25.begin_I2C()) {
    //     _sensorFound = false;
    //     Serial.println("PM25AQI sensor not found!");
    // } else {
    //     _sensorFound = true;
    //     Serial.println("PM25AQI sensor found!");
    // }

}

bool RW_PM25AQI::Detect() {
    if(_pm25.begin_I2C()) {
        _sensorFound = true;
    }

    RW_Helper::Pm25AqiFound = _sensorFound;
    return _sensorFound;
}

void RW_PM25AQI::Read(RW_Values * values) {
   PM25_AQI_Data data;
  
  if (! _pm25.read(&data)) {
    Serial.println("Could not read from PM25AQI");
    return;
  }

  values->Pm25Aqi.Pm10Standard = data.pm10_standard;
  values->Pm25Aqi.Pm25Standard = data.pm25_standard;
  values->Pm25Aqi.Pm100Standard = data.pm100_standard;
  values->Pm25Aqi.Pm10Env = data.pm10_env;
  values->Pm25Aqi.Pm25Env = data.pm25_env;
  values->Pm25Aqi.Pm100Env = data.pm100_env;
  values->Pm25Aqi.Particles03um = data.particles_03um;
  values->Pm25Aqi.Particles05um = data.particles_05um;
  values->Pm25Aqi.Particles10um = data.particles_10um;
  values->Pm25Aqi.Particles25um = data.particles_25um;
  values->Pm25Aqi.Particles50um = data.particles_50um;
  values->Pm25Aqi.Particles100um = data.particles_100um;
}

String RW_PM25AQI::GetName() {
    return "PM25AQI";
}

String RW_PM25AQI::GetPrometheusMetrics(String location, RW_Values * values) {
   String name = "rw_pm25aqi";

    String metrics = RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Pm10Standard, location, METRIC_PM10, UNIT_STANDARD);
    metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Pm25Standard, location, METRIC_PM25, UNIT_STANDARD) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Pm100Standard, location, METRIC_PM100, UNIT_STANDARD) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Pm10Env, location, METRIC_PM10, UNIT_ENVIRONMENTAL) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Pm25Env, location, METRIC_PM25, UNIT_ENVIRONMENTAL) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Pm100Env, location, METRIC_PM100, UNIT_ENVIRONMENTAL) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Particles03um, location, METRIC_GT_03_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Particles05um, location, METRIC_GT_05_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Particles10um, location, METRIC_GT_10_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Particles25um, location, METRIC_GT_25_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Particles50um, location, METRIC_GT_50_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pm25Aqi.Particles100um, location, METRIC_GT_100_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n";

    return metrics;
}