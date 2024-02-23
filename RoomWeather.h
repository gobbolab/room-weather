#ifndef RoomWeather_h
#define RoomWeather_h

#define SUPPORTED_SENSOR_COUNT 3
#define RW_HTU31D_INDEX 0
#define RW_SGP30_INDEX 1
#define RW_PMSA003I_INDEX 2

#include "RW_Wifi.h"
#include "RW_HTU31D.h"
#include "RW_SGP30.h"
#include "RW_PMSA003I.h"
#include "RW_Values.h"

class RoomWeather
{
  public:
    RW_Values* Values;
    RoomWeather(String location);
    RoomWeather(String location, char ssid[], char password[]);
    void Detect();
    void Read();
    void Read(int interval);
    void Print();
    void Print(int index);
    void ServeMetrics();
  private:
    RW_Wifi *_wifi;
    RW_Sensor* _sensors[SUPPORTED_SENSOR_COUNT];
    String _location;
    unsigned long _lastReadTime;
    void Load();
    void DetectSensor(RW_Sensor * sensor);
    void DoRead();
    String BuildMetrics();
};

#endif
