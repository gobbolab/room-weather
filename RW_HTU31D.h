#ifndef RW_HTU31D_h
#define RW_HTU31D_h

#include "Sensor.h"
#include <Wire.h>
#include "Adafruit_HTU31D.h"

class RW_SGP30 : public Sensor
{
  public:
    RW_SGP30();
    void Read();
    String GetTempStringCelcius();
    String GetTempStringFahrenheit();
    String GetHumidityString();
  private:
    Adafruit_HTU31D sgp;
    float _temp;
    float _humidity;
};
#endif