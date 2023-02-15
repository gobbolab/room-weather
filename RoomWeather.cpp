#include "RoomWeather.h"
#include "Arduino.h"

RoomWeather::RoomWeather(String location) {
    _location = location;
    Load();
}

RoomWeather::RoomWeather(String location, char ssid[], char password[]) {
    _location = location;
    _wifi = new RW_Wifi(ssid, password);
    Load();
}

void RoomWeather::Detect() {
    Serial.println("Detecting sensors.");
    delay(500);

    for(int i = 0; i < SUPPORTED_SENSOR_COUNT; i++) {
        DetectSensor(_sensors[i]);
    }
}

void RoomWeather::Read() {
    DoRead();
}

void RoomWeather::Read(int interval) {
    if(RW_Helper::HasTimeElapsed(_lastReadTime, 1000)) {
        DoRead();
        _lastReadTime = millis();
    }
}

void RoomWeather::Print() {
    for(int i = 0; i < SUPPORTED_SENSOR_COUNT; i++) {
        if(!_sensors[i]->Found()) {
            continue;
        }

        _sensors[i]->Print(Values);
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

void RoomWeather::Load() {
    Values = new RW_Values();

    _sensors[0] = new RW_HTU31D();
    _sensors[1] = new RW_SGP30();
    _sensors[2] = new RW_PMSA003I();

    _lastReadTime = 0;
}

void RoomWeather::DetectSensor(RW_Sensor * sensor) {
    Serial.print("Attempting to detect ");
    Serial.print(sensor->GetName());
    Serial.print("...");

    for(int tries = 0; tries < 5; tries++) {
        Serial.print(".");
        if(sensor->Detect()) {
            Serial.println(" detected!");
            return;
        }
        delay(1000);
    }

    Serial.println(" not detected!");
}

void RoomWeather::DoRead() {
    for(int i = 0; i < SUPPORTED_SENSOR_COUNT; i++) {
        if(!_sensors[i]->Found()) {
            continue;
        }

        _sensors[i]->Read(Values);
    }
}

void RoomWeather::ServeMetrics() {
    if(!_wifi) {
        Serial.println("Attempted to serve metrics over wifi, but wifi is not connected.");
        return;
    }

    _wifi->Serve(BuildMetrics());
}
