#include "RoomWeather.h"
#include "Arduino.h"

#define METRIC_TEMP "metric=\"temperature\""
#define METRIC_HUMIDITY "metric=\"humidity\""
#define METRIC_VOC "metric=\"voc\""
#define METRIC_CO2 "metric=\"co2\""
#define UNIT_FAHRENHEIT "unit=\"fahrenheit\""
#define UNIT_CELSIUS "unit=\"celcius\""
#define UNIT_PPM "unit=\"ppm\""
#define UNIT_PPB "unit=\"ppb\""

RoomWeather::RoomWeather(String location) {
    _location = location;
}

RoomWeather::RoomWeather(String location, char ssid[], char password[]) {
    _location = location;
    Connect(ssid, password);
}

RoomWeather::RoomWeather(String location, char ssid[], char password[], String ip, String submask, String gateway) {
    _location = location;
    Connect(ssid, password, ip, submask, gateway);
}

void RoomWeather::Detect() {
    _htu31d = new RW_HTU31D();
    _sgp30 = new RW_SGP30();
}

void RoomWeather::Scan() {
    _htu31d->Read();
    _sgp30->Read();;
}

String RoomWeather::GetHtu31dTempCelcius() {
    return _htu31d->GetTempStringCelcius();
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

void RoomWeather::Connect(char ssid[], char password[]) {
    StartWiFi(ssid, password);
}

void RoomWeather::Connect(char ssid[], char password[], String ipStr, String submaskStr, String gatewayStr) {
    IPAddress ip;
    IPAddress submask;
    IPAddress gateway;
    IPAddress primaryDNS;
    IPAddress secondaryDNS;

    if (ip.fromString(ipStr) && submask.fromString(submaskStr) && gateway.fromString(gatewayStr)) {
        WiFi.config(ip, submask, gateway);
        Serial.println("Using specified network configuration.");
        Serial.println("IP Address: " + ipStr);
        Serial.println("Subnetmask: " + submaskStr);
        Serial.println("Gateway: " + gatewayStr);
    } else {
        Serial.println("Failed to parse network configuration, defaulting to DHCP.");
    }
    
    StartWiFi(ssid, password);
}

void RoomWeather::StartWiFi(char ssid[], char password[]) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");  
    }

    _server = new WiFiServer(80);
    _server->begin();

    PrintWifiStatus();
}

void RoomWeather::Serve() {
    WiFiClient client = _server->available();

  if (client) {
    Serial.println("new client");

    bool currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {

        char c = client.read();

        Serial.write(c);

        if (c == '\n' && currentLineIsBlank) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/plain");
            client.println("Connection: close");
            client.println();
            client.print(BuildMetrics());
            break;
        }
        
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {

          currentLineIsBlank = false;
        }
      }
    }

    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}

void RoomWeather::PrintWifiStatus() {
  Serial.print("===== WiFi Status =====");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.println("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.println("---------------");
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
    metrics += "\n" + ToProm(name, GetHtu31dTempCelcius(), METRIC_TEMP, UNIT_CELSIUS) + "\n";
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
