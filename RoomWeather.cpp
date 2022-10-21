#include "Arduino.h"
#include "RoomWeather.h"

RoomWeather::RoomWeather() {
}

void RoomWeather::Detect() {
    _mockSensor = new MockSensor(1);
    _htu31d = new RW_HTU31D();
}

void RoomWeather::Scan() {
    _mockSensor->Read();
    _htu31d->Read();
}

String RoomWeather::GetMockSensorValue() {
    return _mockSensor->GetValue();
}

String RoomWeather::GetHtu31dTempCelcius() {
    return _htu31d->GetTempStringCelcius();
}

String RoomWeather::GetHtu31dTempFahrenheit() {
    return _htu31d->GetTempStringFahrenheit();
}

String RoomWeather::GetHtu31dHumidity() {
    return _htu31d->GetHumidityString();
}
