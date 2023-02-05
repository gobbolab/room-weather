#ifndef RW_SGP30_h
#define RW_SGP30_h

#include "Sensor.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

class RW_SGP30 : public Sensor
{
  public:
    RW_SGP30();
    void Read();
    String GetVOCStringPPB();//exposed functions
    String GetCO2StringPPM();
  private:
    Adafruit_SGP30 sgp;
    float _tvoc;  //private returns from the adafruit library
    float _eco2;
};
#endif