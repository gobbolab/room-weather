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
    if (RW_Helper::Htu31dFound) { 
        temperature = values->Htu31d.TemperatureCelsius;
        humidity = values->Htu31d.Humidity;

        values->Sgp40.Raw = sgp.measureRaw(t, h);
        values->Sgp40.VOCIndex = sgp.measureVocIndex(t, h);
    } 
    else {
        values->Sgp40.Raw = sgp.measureRaw();
        values->Sgp40.VOCIndex = sgp.measureVocIndex();
    }
}

void RW_SGP40::Print(RW_Values * values)
{
    Serial.println("----- SGP40 -----");
    Serial.println("Raw: " + String(values->Sgp40.Raw) + "\n" + "VOC Index: " + String(values->Sgp40.VOCIndex) + "\n");
}

String RW_SGP40::GetName() {
    return "SGP40";
}

String RW_SGP40::GetPrometheusMetrics(String location, RW_Values * values) {
    String name = "RW_SGP40";

    String metrics = RW_Helper::ToPrometheusMetric(name, values->Sgp40.Raw, location, METRIC_VOC_RAW, UNIT_NONE);
    metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Sgp40.VOCIndex, location, METRIC_VOC_INDEX, UNIT_NONE) + "\n";
    return metrics;
}