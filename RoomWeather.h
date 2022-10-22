#ifndef RoomWeather_h
#define RoomWeather_h

#include <WiFi.h>
#include "MockSensor.h"
#include "RW_HTU31D.h"

class RoomWeather
{
  public:
    RoomWeather();
    RoomWeather(char ssid[], char password[]);
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
    void Connect(char ssid[], char password[]);
    String ToProm(String value, String name, String label);

};

#endif