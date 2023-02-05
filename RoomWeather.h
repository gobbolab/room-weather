#ifndef RoomWeather_h
#define RoomWeather_h

#include <WiFi.h>
#include "RW_HTU31D.h"
#include "RW_SGP30.h"

class RoomWeather
{
  public:
    RoomWeather(String location);
    RoomWeather(String location, char ssid[], char password[]);
    RoomWeather(String location, char ssid[], char password[], String ip, String submask, String gateway);
    void Detect();
    void Read();
    String GetHtu31dTempCelsius();
    String GetHtu31dTempFahrenheit();
    String GetHtu31dHumidity();
    String GetSGP30eCO2();
    String GetSGP30VOC();
    void PrintWifiStatus();
    void Serve();
  private:
    WiFiServer *_server;
    RW_HTU31D * _htu31d;
    RW_SGP30 * _sgp30;
    String _location;
    void Connect(char ssid[], char password[]);
    void Connect(char ssid[], char password[], String ipStr, String submaskStr, String gatewayStr);
    void StartWiFi(char ssid[], char password[]);
    String BuildMetrics();
    String GetHTU31DMetrics();
    String GetSGP30Metrics();
    String GetLocationLabel();
    String ToProm(String name, String value, String metric, String unit);
};

#endif