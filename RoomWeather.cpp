#include "RoomWeather.h"
#include "Arduino.h"

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
    _htu31d = new RW_SGP30();
}

void RoomWeather::Scan() {
    _htu31d->Read();
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
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

String RoomWeather::BuildMetrics() {
    String metrics = "";

    metrics += GetTemperatureMetrics();

    return metrics;
}

String RoomWeather::GetTemperatureMetrics() {
    String name = "rw_temperature";
    String fLabel = GetLocationLabel() + ", " + "unit=\"fahrenheit\"";
    String cLabel = GetLocationLabel() + ", " + "unit=\"celcius\"";

    String metrics = ToProm(GetHtu31dTempFahrenheit(), name, fLabel);
    metrics += "\n" + ToProm(GetHtu31dTempCelcius(), name, cLabel) + "\n";
    return metrics;
}

String RoomWeather::GetLocationLabel() {
    return "location=\"" + _location + "\"";
}

String RoomWeather::ToProm(String value, String name, String label) {
    return name + "{" + label + "}" + " " + value;
}
