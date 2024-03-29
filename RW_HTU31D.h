#ifndef RW_HTU31D_h
#define RW_HTU31D_h

#include "RW_Sensor.h"
#include <Wire.h>
#include "Adafruit_HTU31D.h"

class RW_HTU31D : public RW_Sensor
{
  public:
    RW_HTU31D();
    bool Detect();
    void Read(RW_Values * values);
    void Print(RW_Values * values);
    String GetName();
    String GetPrometheusMetrics(String location, RW_Values * values);
  private:
    Adafruit_HTU31D _htu;
};
#endif