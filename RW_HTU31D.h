#ifndef RW_HTU31D_h
#define RW_HTU31D_h

#include "Sensor.h"
#include <Wire.h>
#include "Adafruit_HTU31D.h"

class RW_HTU31D : public Sensor
{
  public:
    RW_HTU31D();
    void Read(RW_Values * values);
    String GetPrometheusMetrics(String location, RW_Values * values);
  private:
    Adafruit_HTU31D _htu;
};
#endif