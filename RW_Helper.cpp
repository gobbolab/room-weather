#include "RW_Helper.h"

String RW_Helper::ToPrometheusMetric(String name, float value, String location, String metric, String unit) {
    String locationLabel = "location=\"" + location + "\"";
    String label = locationLabel + ", " + metric + ", " + unit;
    return name + "{" + label + "} " + String(value);
}