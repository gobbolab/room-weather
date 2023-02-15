#include "RW_SGP30.h"
#include "RW_Helper.h"

RW_SGP30::RW_SGP30()
    : RW_Sensor() {
    sgp = Adafruit_SGP30();
}

bool RW_SGP30::Detect() {
    _sensorFound = sgp.begin();
    RW_Helper::Sgp30Found = _sensorFound;
    return _sensorFound;
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

void RW_SGP30::Print(RW_Values * values)
{
    Serial.println("----- SGP30 -----");
    Serial.println("VOC: " + String(values->Sgp30.VOC) + "\n" + "CO2: " + String(values->Sgp30.CO2) + "\n");
}

String RW_SGP30::GetName() {
    return "SGP30";
}

String RW_SGP30::GetPrometheusMetrics(String location, RW_Values * values) {
    String name = "rw_sgp30";

    String metrics = RW_Helper::ToPrometheusMetric(name, values->Sgp30.VOC, location, METRIC_VOC, UNIT_PPB);
    metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Sgp30.CO2, location, METRIC_CO2, UNIT_PPM) + "\n";
    return metrics;
}