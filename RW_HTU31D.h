#ifndef RW_HTU31D_h
#define RW_HTU31D_h

#include "Sensor.h"
#include <Wire.h>
#include "Adafruit_HTU31D.h"

class RW_HTU31D : public Sensor
{
  public:
    RW_HTU31D();
    void Read();
    String GetTempStringCelsius();
    String GetTempStringFahrenheit();
    String GetHumidityString();
  private:
    Adafruit_HTU31D htu;
    float _temp;
    float _humidity;
};
#endif