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

  // Prints the values of all sensors detected
  rw->Print();
  
  // Prints the values of a single sensor given a specific index
  rw->Print(RW_HTU31D_INDEX);
}

void loop() {
  
}