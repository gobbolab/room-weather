#ifndef RW_HTU31D_h
#define RW_HTU31D_h

#include "Sensor.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

class RW_SGP30 : public Sensor
{
  public:
    RW_SGP30();
    void Read();
    String GetTempStringCelcius();
    String GetTempStringFahrenheit();
    String GetHumidityString();
  private:
    Adafruit_SGP30 sgp;
    float _temp;
    float _humidity;
};
#endif