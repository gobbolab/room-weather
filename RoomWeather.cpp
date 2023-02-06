#include "RoomWeather.h"
#include "Arduino.h"

#define METRIC_TEMP "metric=\"temperature\""
#define METRIC_HUMIDITY "metric=\"humidity\""
#define METRIC_VOC "metric=\"voc\""
#define METRIC_CO2 "metric=\"co2\""
#define UNIT_FAHRENHEIT "unit=\"fahrenheit\""
#define UNIT_CELSIUS "unit=\"celsius\""
#define UNIT_PERCENT "unit=\"percent\""
#define UNIT_PPM "unit=\"ppm\""
#define UNIT_PPB "unit=\"ppb\""

RoomWeather::RoomWeather(String location) {
    _location = location;
    Values = new SensorValues();
}

RoomWeather::RoomWeather(String location, char ssid[], char password[]) {
    _location = location;
    _wifi = new RoomWeatherWifi(ssid, password);
    Values = new SensorValues();
}

void RoomWeather::Detect() {
    _sensors[0] = new RW_HTU31D();
    _sensors[1] = new RW_SGP30();
}

void RoomWeather::Read() {
    for(int i = 0; i < SUPPORTED_SENSOR_COUNT; i++) {
        if(!_sensors[i]->Found()) {
            continue;
        }

        _sensors[i]->Read(Values);
    }
}

String RoomWeather::BuildMetrics() {
    String metrics = "";

    for(int i = 0; i < SUPPORTED_SENSOR_COUNT; i++) {
        if(!_sensors[i]->Found()) {
            continue;
        }

        metrics += _sensors[i]->GetPrometheusMetrics(_location, Values);
    }

    return metrics;
}

void RoomWeather::ServeMetrics() {
    if(!_wifi) {
        Serial.println("Attempted to serve metrics over wifi, but wifi is not connected.");
        return;
    }

    _wifi->Serve(BuildMetrics());
}
