#include "RW_Sensor.h"

RW_Sensor::RW_Sensor() {
    _sensorFound = false;
}

bool RW_Sensor::Found() {
    return _sensorFound;
}

bool RW_Sensor::Detect() {
    return false;
}

void RW_Sensor::Read(RW_Values * values) {
}

void RW_Sensor::Print(RW_Values * values) {
}

String RW_Sensor::GetName() {
    return "";
}

String RW_Sensor::GetPrometheusMetrics(String location, RW_Values * values) {
    return "";
}