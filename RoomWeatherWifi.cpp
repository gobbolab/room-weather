#include "RoomWeatherWifi.h"

RoomWeatherWifi::RoomWeatherWifi(char ssid[], char password[]) {
    StartWiFi(ssid, password);
}

void RoomWeatherWifi::StartWiFi(char ssid[], char password[]) {
    Serial.print("Attempting to connect to wifi");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");  
    }

    _server = new WiFiServer(80);
    _server->begin();

    PrintWifiStatus();
}

void RoomWeatherWifi::Serve(String metrics) {
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
            client.print(metrics);
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

void RoomWeatherWifi::PrintWifiStatus() {
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
