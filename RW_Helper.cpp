#include "RW_Helper.h"

bool RW_Helper::Htu31dFound = false;
bool RW_Helper::Sgp30Found = false;

String RW_Helper::ToPrometheusMetric(String name, float value, String location, String metric, String unit) {
    String locationLabel = "location=\"" + location + "\"";
    String label = locationLabel + ", " + metric + ", " + unit;
    return name + "{" + label + "} " + String(value);
}

float RW_Helper::CelsiusToFahrenheit(float temperature) {
    return (temperature * 9 / 5) + 32;
 }

float RW_Helper::CalculateAbsoluteHumidity(float relative_humidity, float temperature) {
    return 216.7f * ((relative_humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature));
}