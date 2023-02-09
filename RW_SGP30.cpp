#include "RW_SGP30.h"
#include "RW_Helper.h"

RW_SGP30::RW_SGP30()
    : RW_Sensor() 
{
    sgp = Adafruit_SGP30();

    if (!sgp.begin()) {
        _sensorFound = false;
        Serial.println("SGP30 sensor not found!");
    } else {
        _sensorFound = true;
        Serial.println("SGP30 sensor found!");
    }

    RW_Helper::Sgp30Found = _sensorFound;
}

void RW_SGP30::Read(RW_Values * values){
    if (RW_Helper::Htu31dFound) { 
        sgp.setHumidity(values->Htu31d.AbsoluteHumidity);
    }

    if(! sgp.IAQmeasure()){
        Serial.println("SGP30 measurement failed");
        return;
    } 

    values->Sgp30.CO2 = sgp.eCO2;
    values->Sgp30.VOC = sgp.TVOC;
}

String RW_SGP30::GetPrometheusMetrics(String location, RW_Values * values) {
    String name = "rw_sgp30";

    String metrics = RW_Helper::ToPrometheusMetric(name, values->Sgp30.VOC, location, METRIC_VOC, UNIT_PPB);
    metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Sgp30.CO2, location, METRIC_CO2, UNIT_PPM) + "\n";
    return metrics;
}