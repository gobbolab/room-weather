#ifndef RoomWeather_h
#define RoomWeather_h

#define SUPPORTED_SENSOR_COUNT 4
#define RW_HTU31D_INDEX 0
#define RW_SGP30_INDEX 1
#define RW_SGP40_INDEX 2
#define RW_PMSA003I_INDEX 3

#if defined(ESP32)
    #include "RW_Wifi.h"
#endif
#include "RW_HTU31D.h"
#include "RW_SGP30.h"
#include "RW_SGP40.h"
#include "RW_PMSA003I.h"
#include "RW_Values.h"

class RoomWeather
{
  public:
    RW_Values* Values;
    RoomWeather(String location);
    #if defined(ESP32)
      RoomWeather(String location, char ssid[], char password[]);
    #endif
    void Detect();
    void Read();
    void Read(int interval);
    void Print();
    void Print(int index);
    #if defined(ESP32)
      void ServeMetrics();
    #endif
  private:
    #if defined(ESP32)
      RW_Wifi *_wifi;
    #endif
    RW_Sensor* _sensors[SUPPORTED_SENSOR_COUNT];
    String _location;
    unsigned long _lastReadTime;
    void Load();
    void DetectSensor(RW_Sensor * sensor);
    void DoRead();
    String BuildMetrics();
};

#endif
