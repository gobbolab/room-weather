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
    String GetTempStringCelcius(); //exposed functions
    String GetVOCstringPPB();
    String GetCO2stringPPM();
    // String GetH2string(); //for later functionality
    // String GetETHANOLstring();
    // String getAbsoluteHumidity();
  private:
    Adafruit_SGP30 sgp;
    float _tvoc;  //private returns from the adafruit library
    float _eco2;
    // float _h2;
    // float _ethanol;
    //float _absHumidity;
};
#endif