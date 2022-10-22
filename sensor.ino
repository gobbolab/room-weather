#include "RoomWeather.h"

char ssid[] = "TeamshipHQ";
char pass[] = "partoftheship720";

RoomWeather *rw;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }

  rw = new RoomWeather(ssid, pass);
  rw->Detect();
}

void loop() {
  rw->Scan();
  rw->Serve();
}