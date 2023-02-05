#include "RW_HTU31D.h"

RW_HTU31D::RW_HTU31D()
    : Sensor(0) 
{
    htu = Adafruit_HTU31D();

    if (!htu.begin(0x40)) {
        _sensorFound = false;
        Serial.println("HTU31D sensor not found!");
    } else {
        _sensorFound = true;
        Serial.println("HTU31D sensor found!");
    }
}

void RW_HTU31D::Read(){
    sensors_event_t h, t;
    htu.getEvent(&h, &t);

    _humidity = h.relative_humidity;
    _temp = t.temperature;
}

String RW_HTU31D::GetTempStringCelsius() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_temp);
}

String RW_HTU31D::GetTempStringFahrenheit() {
    if(!_sensorFound) {
        return "unavailable";
    }

    float converted = (_temp * 9 / 5) + 32;

    return String(converted);
}

String RW_HTU31D::GetHumidityString() {
    if(!_sensorFound) {
        return "unavailable";
    }

    return String(_humidity);
}