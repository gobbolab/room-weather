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
    sensors_event_t voc, co2; //is this needed?
    if(! sgp.IAQmeasure()){//IAQmeasure takes no parameters and how do I return the values to the variables using it?
        Serial.println("SGP30 measurement failed");
        return;
    } 

    _tvoc = sgp.TVOC;
    _eco2 = sgp.eCO2;

    // if(! sgp.IAQmeasureRaw()){ //for later implementation
    //     Serial.println("SGP30 raw measurement failed");
    //     return;
    // } 

    // _h2 = sgp.rawH2;
    // _ethanol = sgp.rawEthanol;
}

String RW_SGP30::GetVOCstringPPB() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_tvoc);
}

String RW_SGP30::GetCO2stringPPM() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_eco2);
}

// String RW_SGP30::GetH2string() { //save for IAQmeasureRaw() implementation
//     if(!_sensorFound) {
//         return "unavailable";
//     }

//     return String(_h2);
// }

// String RW_SGP30::GetETHANOLstring() { //save for IAQmeasureRaw() implementation
//     if(!_sensorFound) {
//         return "unavailable";
//     }

//     return String(_ethanol);
// }

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
//String getAbsoluteHumidity(float temperature, float humidity) { //save this for absolute humidity implementation
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    // float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    // float _absHumidity = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    // return String(_absHumidity);
// }