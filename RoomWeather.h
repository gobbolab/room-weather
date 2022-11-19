#ifndef RoomWeather_h
#define RoomWeather_h

#include <WiFi.h>
#include "MockSensor.h"
#include "RW_HTU31D.h"

class RoomWeather
{
  public:
    RoomWeather(String location);
    RoomWeather(String location, char ssid[], char password[]);
    RoomWeather(String location, char ssid[], char password[], String ip, String submask, String gateway);
    void Detect();
    void Scan();
    String GetMockSensorValue();
    String GetHtu31dTempCelcius();
    String GetHtu31dTempFahrenheit();
    String GetHtu31dHumidity();
    void PrintWifiStatus();
    void Serve();
  private:
    WiFiServer *_server;
    MockSensor *_mockSensor;
    RW_HTU31D * _htu31d;
    String _location;
    void Connect(char ssid[], char password[]);
    void Connect(char ssid[], char password[], String ipStr, String submaskStr, String gatewayStr);
    void StartWiFi(char ssid[], char password[]);
    String BuildMetrics();
    String GetTemperatureMetrics();
    String GetLocationLabel();
    String ToProm(String value, String name, String label);
};

#endif