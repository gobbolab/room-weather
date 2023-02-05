#ifndef RoomWeather_h
#define RoomWeather_h

#include <WiFi.h>
#include "RoomWeatherWifi.h"
#include "RW_HTU31D.h"
#include "RW_SGP30.h"

class RoomWeather
{
  public:
    RoomWeather(String location);
    RoomWeather(String location, char ssid[], char password[]);
    void Detect();
    void Read();
    String GetHtu31dTempCelsius();
    String GetHtu31dTempFahrenheit();
    String GetHtu31dHumidity();
    String GetSGP30eCO2();
    String GetSGP30VOC();
    void PrintWifiStatus();
    void ServeMetrics();
  private:
    RoomWeatherWifi *_wifi;
    RW_HTU31D * _htu31d;
    RW_SGP30 * _sgp30;
    String _location;
    String BuildMetrics();
    String GetHTU31DMetrics();
    String GetSGP30Metrics();
    String GetLocationLabel();
    String ToProm(String name, String value, String metric, String unit);
};

#endif