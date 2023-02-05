#include "RoomWeather.h"
#include "Arduino.h"

#define METRIC_TEMP "metric=\"temperature\""
#define METRIC_HUMIDITY "metric=\"humidity\""
#define METRIC_VOC "metric=\"voc\""
#define METRIC_CO2 "metric=\"co2\""
#define UNIT_FAHRENHEIT "unit=\"fahrenheit\""
#define UNIT_CELSIUS "unit=\"celsius\""
#define UNIT_PERCENT "unit=\"percent\""
#define UNIT_PPM "unit=\"ppm\""
#define UNIT_PPB "unit=\"ppb\""

RoomWeather::RoomWeather(String location) {
    _location = location;
}

RoomWeather::RoomWeather(String location, char ssid[], char password[]) {
    _location = location;
    _wifi = new RoomWeatherWifi(ssid, password);
}

void RoomWeather::Detect() {
    _htu31d = new RW_HTU31D();
    _sgp30 = new RW_SGP30();
}

void RoomWeather::Read() {
    _htu31d->Read();
    _sgp30->Read();;
}

String RoomWeather::GetHtu31dTempCelsius() {
    return _htu31d->GetTempStringCelsius();
}

String RoomWeather::GetHtu31dTempFahrenheit() {
    return _htu31d->GetTempStringFahrenheit();
}

String RoomWeather::GetHtu31dHumidity() {
    return _htu31d->GetHumidityString();
}

String RoomWeather::GetSGP30eCO2() {
    return _sgp30->GetCO2StringPPM();
}

String RoomWeather::GetSGP30VOC() {
    return _sgp30->GetVOCStringPPB();
}

String RoomWeather::BuildMetrics() {
    String metrics = "";

    metrics += GetHTU31DMetrics();
    metrics += GetSGP30Metrics();

    return metrics;
}

String RoomWeather::GetHTU31DMetrics() {
    String name = "rw_htu31d";

    String metrics = ToProm(name, GetHtu31dTempFahrenheit(), METRIC_TEMP, UNIT_FAHRENHEIT);
    metrics += "\n" + ToProm(name, GetHtu31dTempCelsius(), METRIC_TEMP, UNIT_CELSIUS) + "\n"
    + ToProm(name, GetHtu31dHumidity(), METRIC_HUMIDITY, UNIT_PERCENT) + "\n";
    return metrics;
}

String RoomWeather::GetSGP30Metrics() {
    String name = "rw_sgp30";

    String metrics = ToProm(name, GetSGP30VOC(), METRIC_VOC, UNIT_PPB);
    metrics += "\n" + ToProm(name, GetSGP30eCO2(), METRIC_CO2, UNIT_PPM) + "\n";
    return metrics;
}

String RoomWeather::GetLocationLabel() {
    return "location=\"" + _location + "\"";
}

String RoomWeather::ToProm(String name, String value, String metric, String unit) {
    String label = GetLocationLabel() + ", " + metric + ", " + unit;
    return name + "{" + label + "} " + value;
}

void RoomWeather::ServeMetrics() {
    if(!_wifi) {
        Serial.println("Attempted to serve metrics over wifi, but wifi is not connected.");
        return;
    }

    _wifi->Serve(BuildMetrics());
}
