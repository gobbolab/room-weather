#ifndef RoomWeather_h
#define RoomWeather_h

#include "MockSensor.h"
#include "RW_HTU31D.h"

class RoomWeather
{
  public:
    RoomWeather();
    void Detect();
    void Scan();
    String GetMockSensorValue();
    String GetHtu31dTempCelcius();
    String GetHtu31dTempFahrenheit();
    String GetHtu31dHumidity();
  private:
    MockSensor *_mockSensor;
    RW_HTU31D * _htu31d;

};

#endif