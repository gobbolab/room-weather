#include "RoomWeather.h"
#include "RoomWeatherSecrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

RoomWeather *rw;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }

  rw = new RoomWeather("workshop", ssid, pass);
  rw->Detect();
}

void loop() {
  rw->Scan();
  rw->Serve();
}