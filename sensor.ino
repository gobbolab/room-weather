#include "RoomWeather.h"
#include "RoomWeatherConfig.h"

char ssid[] = RW_SECRET_SSID;
char pass[] = RW_SECRET_PASS;

RoomWeather *rw;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }

  rw = new RoomWeather(RW_LOCATION, ssid, pass, RW_IP, RW_SUBMASK, RW_GATEWAY);
  rw->Detect();
}

void loop() {
  rw->Scan();
  rw->Serve();
}