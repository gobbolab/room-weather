#include "Sensor.h"

Sensor::Sensor(int address) {
    _address = address;
}

bool Sensor::Found() {
    return _sensorFound;
}

void Sensor::Read(SensorValues * values) {

}

String Sensor::GetPrometheusMetrics(String location, SensorValues * values) {
    return "";
}