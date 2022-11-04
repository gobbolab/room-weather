# Room Weather

Room Weather is an Arduino library that aims to provide plug and play support for monitoring air quality using STEMMA QT I2C sensors.

Supported sensors simply need to be plugged into the I2C bus of the Arduino to access their readings.

The hope is to provide a simple system for monitoring air quality in houses, workshops 3d printer enclosures etc. using off the shelf components and simple connectors.

# Usage

```
RoomWeather *rw;

void setup() {
  // Start serial
  Serial.begin(115200);

  while (!Serial) {
    ; 
  }

  // Create a new room weather object
  rw = new RoomWeather("office");

  // Call detect to identify available sensors
  rw->Detect();
}

void loop() {
  // Call scan to read values of all available sensors
  rw->Scan();

  // Print sensor data
  Serial.println(rw->GetHtu31dTempCelcius());
}
```

# Prometheus Export

Sensor data can automatically be exposed in Prometheus metric format on boards that have WiFi enabled.

```
RoomWeather *rw;

void setup() {
  rw = new RoomWeather("office", "officewifi", "wifipassword");
  rw->Detect();
}

void loop() {
  rw->Scan();

  // Serve will handle any incoming http request and respond with available sensor 
  // data in prometheus metric format
  rw->Serve();
}
```

# Supported Sensors

[HTU31D Temp & Humidity](https://www.adafruit.com/product/4832)

# Config

To run the included `sensor.ino` sketch, you must create a file called `RoomWeatherConfig.h` in your include path.

The file should define the following:

```
#define RW_SECRET_SSID "your_wifi_ssid"
#define RW_SECRET_PASS "your_wifi_password"
#define RW_LOCATION "location_or_name_of_room_weather_instance"
```