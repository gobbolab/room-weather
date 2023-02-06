#include "Sensor.h"

Sensor::Sensor(int address) {
    _address = address;
}

bool Sensor::Found() {
    return _sensorFound;
}

void Sensor::Read(RW_Values * values) {

}

String Sensor::GetPrometheusMetrics(String location, RW_Values * values) {
    return "";
}