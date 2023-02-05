#ifndef RoomWeatherWifi_h
#define RoomWeatherWifi_h

#include <WiFi.h>

class RoomWeatherWifi
{
  public:
    RoomWeatherWifi(char ssid[], char password[]);
    void Serve(String metrics);
  private:
    WiFiServer *_server;
    void StartWiFi(char ssid[], char password[]);
    void PrintWifiStatus();
};

#endif