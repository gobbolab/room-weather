#include "RW_SGP40.h"
#include "RW_Helper.h"

RW_SGP40::RW_SGP40()
    : RW_Sensor() {
    sgp = Adafruit_SGP40();
}

bool RW_SGP40::Detect() {
    _sensorFound = sgp.begin();
    RW_Helper::Sgp40Found = _sensorFound;
    return _sensorFound;
}

void RW_SGP40::Read(RW_Values * values){
    // if (RW_Helper::Htu31dFound) { 
    //     sgp.setHumidity(values->Htu31d.AbsoluteHumidity);
    // }

    // if(! sgp.IAQmeasure()){
    //     Serial.println("SGP30 measurement failed");
    //     return;
    // } 

    // values->Sgp30.CO2 = sgp.eCO2;
    // values->Sgp30.VOC = sgp.TVOC;
}

void RW_SGP40::Print(RW_Values * values)
{
    Serial.println("----- SGP40 -----");
    // Serial.println("VOC: " + String(values->Sgp30.VOC) + "\n" + "CO2: " + String(values->Sgp30.CO2) + "\n");
}

String RW_SGP40::GetName() {
    return "SGP40";
}

String RW_SGP40::GetPrometheusMetrics(String location, RW_Values * values) {
    String name = "RW_SGP40";

    // String metrics = RW_Helper::ToPrometheusMetric(name, values->Sgp30.VOC, location, METRIC_VOC, UNIT_PPB);
    // metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Sgp30.CO2, location, METRIC_CO2, UNIT_PPM) + "\n";
    // return metrics;
    return "";
}