#ifndef RW_Wifi_h
#define RW_Wifi_h

#include <WiFi.h>

class RW_Wifi
{
  public:
    RW_Wifi(char ssid[], char password[]);
    void Serve(String metrics);
  private:
    WiFiServer *_server;
    void StartWiFi(char ssid[], char password[]);
    void PrintWifiStatus();
};

#endif