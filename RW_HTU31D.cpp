#include "RW_HTU31D.h"
#include "RW_Helper.h"

RW_HTU31D::RW_HTU31D()
    : RW_Sensor() {
    _htu = Adafruit_HTU31D();
}

bool RW_HTU31D::Detect() {
    _sensorFound = _htu.begin(0x40);
    RW_Helper::Htu31dFound = _sensorFound;
    return _sensorFound;
}

void RW_HTU31D::Read(RW_Values * values) {
    sensors_event_t h, t;
    _htu.getEvent(&h, &t);

    values->Htu31d.Humidity = h.relative_humidity; 
    values->Htu31d.TemperatureCelsius = t.temperature;
    values->Htu31d.TemperatureFahrenheit = RW_Helper::CelsiusToFahrenheit(t.temperature);
    values->Htu31d.AbsoluteHumidity = RW_Helper::CalculateAbsoluteHumidity(h.relative_humidity, t.temperature);
}

void RW_HTU31D::Print(RW_Values * values)
{
    Serial.println("----- HTU31D -----");
    Serial.println("Humidity: " + String(values->Htu31d.AbsoluteHumidity) + "\n" 
    + "Temperature (Celsius): " + String(values->Htu31d.TemperatureCelsius) + "\n"
    + "Temperature (Fahrenheit): " + String(values->Htu31d.TemperatureFahrenheit) + "\n"
    + "Absolute Humidity: " + String(values->Htu31d.AbsoluteHumidity) + "\n");
}

String RW_HTU31D::GetName() {
    return "HTU31D";
}

String RW_HTU31D::GetPrometheusMetrics(String location, RW_Values * values) {
    String name = "rw_htu31d";

    String metrics = RW_Helper::ToPrometheusMetric(name, values->Htu31d.TemperatureFahrenheit, location, METRIC_TEMP, UNIT_FAHRENHEIT);
    metrics += "\n" + RW_Helper::ToPrometheusMetric(name, values->Htu31d.TemperatureCelsius, location, METRIC_TEMP, UNIT_CELSIUS) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Htu31d.Humidity, location, METRIC_HUMIDITY, UNIT_PERCENT) + "\n"
    + RW_Helper::ToPrometheusMetric(name, values->Htu31d.AbsoluteHumidity, location, METRIC_ABSOLUTE_HUMIDITY, UNIT_GRAM_PER_M3) + "\n";
    return metrics;
}