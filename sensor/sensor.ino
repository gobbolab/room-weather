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

  Serial.println("Serial started.");

  rw = new RoomWeather(RW_LOCATION, ssid, pass);
  rw->Detect();
}

void loop() {
  rw->Read();
  rw->ServeMetrics();
}