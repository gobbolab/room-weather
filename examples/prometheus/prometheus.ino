#include "RoomWeather.h"

char ssid[] = "your_wifi_ssid";
char pass[] = "your_wifi_password";

RoomWeather *rw;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }

  Serial.println("Serial started.");

  rw = new RoomWeather("location_of_your_sensors", ssid, pass);
  rw->Detect();
}

void loop() {
  rw->Read(1000);
  rw->ServeMetrics();
}