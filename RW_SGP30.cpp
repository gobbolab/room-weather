#include "RW_SGP30.h"

RW_SGP30::RW_SGP30()
    : Sensor(0) 
{
    sgp = Adafruit_SGP30();

    if (!sgp.begin(0x58)) {
        _sensorFound = false;
        Serial.println("SGP30 sensor not found!");
    } else {
        _sensorFound = true;
        Serial.println("SGP30 sensor found!");
    }
}

void RW_SGP30::Read(){
    if(! sgp.IAQmeasure()){//IAQmeasure takes no parameters and how do I return the values to the variables using it?
        Serial.println("SGP30 measurement failed");
        return;
    } 

    _tvoc = sgp.TVOC;
    _eco2 = sgp.eCO2;
}

String RW_SGP30::GetVOCStringPPB() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_tvoc);
}

String RW_SGP30::GetCO2StringPPM() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_eco2);
}