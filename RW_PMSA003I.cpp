#include "RW_PMSA003I.h"
#include "RW_Helper.h"

RW_PMSA003I::RW_PMSA003I()
    : RW_Sensor() {
    _pm25 = Adafruit_PM25AQI();
}

bool RW_PMSA003I::Detect() {
    _sensorFound = _pm25.begin_I2C();
    RW_Helper::Pmsa003iFound = _sensorFound;
    return _sensorFound;
}

void RW_PMSA003I::Read(RW_Values * values) {
   PM25_AQI_Data data;
  
  if (! _pm25.read(&data)) {
    Serial.println("Could not read from PMSA003I");
    return;
  }

  values->Pmsa003i.Pm10Standard = data.pm10_standard;
  values->Pmsa003i.Pm25Standard = data.pm25_standard;
  values->Pmsa003i.Pm100Standard = data.pm100_standard;
  values->Pmsa003i.Pm10Env = data.pm10_env;
  values->Pmsa003i.Pm25Env = data.pm25_env;
  values->Pmsa003i.Pm100Env = data.pm100_env;
  values->Pmsa003i.Particles03um = data.particles_03um;
  values->Pmsa003i.Particles05um = data.particles_05um;
  values->Pmsa003i.Particles10um = data.particles_10um;
  values->Pmsa003i.Particles25um = data.particles_25um;
  values->Pmsa003i.Particles50um = data.particles_50um;
  values->Pmsa003i.Particles100um = data.particles_100um;
}

String RW_PMSA003I::GetName() {
    return "PMSA003I";
}

String RW_PMSA003I::GetPrometheusMetrics(String location, RW_Values * values) {
   String name = "rw_pm25aqi";

    String metrics = RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Pm10Standard, location, METRIC_PM10, UNIT_STANDARD);
    metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Pm25Standard, location, METRIC_PM25, UNIT_STANDARD) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Pm100Standard, location, METRIC_PM100, UNIT_STANDARD) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Pm10Env, location, METRIC_PM10, UNIT_ENVIRONMENTAL) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Pm25Env, location, METRIC_PM25, UNIT_ENVIRONMENTAL) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Pm100Env, location, METRIC_PM100, UNIT_ENVIRONMENTAL) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Particles03um, location, METRIC_GT_03_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Particles05um, location, METRIC_GT_05_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Particles10um, location, METRIC_GT_10_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Particles25um, location, METRIC_GT_25_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Particles50um, location, METRIC_GT_50_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Pmsa003i.Particles100um, location, METRIC_GT_100_UM_PER_LITER_AIR, UNIT_PARTICLES) + "\n";

    return metrics;
}