#include "RoomWeather.h"
// #include <Wire.h>
// #include "Adafruit_HTU31D.h"

Adafruit_HTU31D htu = Adafruit_HTU31D();

RoomWeather *rw;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

    delay(1000);

    rw = new RoomWeather();
    rw->Detect();

    // if (!htu.begin(0x40)) {
    //     Serial.println("Couldn't find sensor!");
    // } else {
    //     Serial.println("Sensor found!");
    // }


}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    rw->Scan();
    
    String result = rw->GetMockSensorValue();
    Serial.println(result);

    Serial.print("Temp: "); 
    Serial.print(rw->GetHtu31dTempFahrenheit());
    Serial.println(" F");
    
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    // sensors_event_t humidity, temp;
    
    // htu.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

    // Serial.print("Temp: "); 
    // Serial.print(temp.temperature);
    // Serial.println(" C");
    
    // Serial.print("Humidity: ");
    // Serial.print(humidity.relative_humidity);
    // Serial.println(" \% RH");
}