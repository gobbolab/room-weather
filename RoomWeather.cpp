#include "RoomWeather.h"
#include "Arduino.h"

RoomWeather::RoomWeather(String location) {
    _location = location;
}

RoomWeather::RoomWeather(String location, char ssid[], char password[]) {
    _location = location;
    Connect(ssid, password);
}

void RoomWeather::Detect() {
    _mockSensor = new MockSensor(1);
    _htu31d = new RW_HTU31D();
}

void RoomWeather::Scan() {
    _mockSensor->Read();
    _htu31d->Read();
}

String RoomWeather::GetMockSensorValue() {
    return _mockSensor->GetValue();
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
            String metrics = GetTemperatureMetrics();

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/plain");
            client.println("Connection: close");
            client.println();
        //   client.println("<!DOCTYPE HTML>");
        //   client.println("<html>");
            client.print(metrics);
        //   client.println("</html>");
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

String RoomWeather::GetTemperatureMetrics() {
    String name = "rw_temperature";
    String fLabel = GetLocationLabel() + ", " + "unit=\"fahrenheit\"";
    String cLabel = GetLocationLabel() + ", " + "unit=\"celcius\"";

    String metrics = ToProm(GetHtu31dTempFahrenheit(), name, fLabel);
    metrics += "\n" + ToProm(GetHtu31dTempCelcius(), name, cLabel);
    return metrics;
}

String RoomWeather::GetLocationLabel() {
    return "location=\"" + _location + "\"";
}

String RoomWeather::ToProm(String value, String name, String label) {
    return name + "{" + label + "}" + " " + value;
}
