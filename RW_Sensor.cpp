#include "RW_Sensor.h"

RW_Sensor::RW_Sensor(int address) {
    _address = address;
}

bool RW_Sensor::Found() {
    return _sensorFound;
}

void RW_Sensor::Read(RW_Values * values) {

}

String RW_Sensor::GetPrometheusMetrics(String location, RW_Values * values) {
    return "";
}