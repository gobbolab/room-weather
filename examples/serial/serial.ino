#include "RoomWeather.h"

RoomWeather *rw;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }

  Serial.println("Serial started.");

  rw = new RoomWeather("bedroom");

  rw->Detect();
  rw->Read();
  rw->Print();
}

void loop() {
  
}