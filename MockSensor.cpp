#include "MockSensor.h"

MockSensor::MockSensor(int address)
    : Sensor(address) 
{
}

void MockSensor::Read(){
    int num = random(0, 100);
    _value = num;
}

String MockSensor::GetValue() {
    return String(_value);
}