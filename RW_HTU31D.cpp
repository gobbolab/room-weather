#include "RW_HTU31D.h"

RW_SGP30::RW_SGP30()
    : Sensor(0) 
{
    sgp = Adafruit_HTU31D();

    if (!sgp.begin(0x40)) {
        _sensorFound = false;
        Serial.println("HTU31D sensor not found!");
    } else {
        _sensorFound = true;
        Serial.println("HTU31D sensor found!");
    }
}

void RW_SGP30::Read(){
    sensors_event_t h, t;
    sgp.getEvent(&h, &t);

    _humidity = h.relative_humidity;
    _temp = t.temperature;
}

String RW_SGP30::GetTempStringCelcius() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_temp);
}

String RW_SGP30::GetTempStringFahrenheit() {
    if(!_sensorFound) {
        return "unavailable";
    }

    float converted = (_temp * 9 / 5) + 32;

    return String(converted);
}

String RW_SGP30::GetHumidityString() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_humidity);
}