# Room Weather

Room Weather is an Arduino library that aims to provide plug and play support for monitoring air quality using STEMMA QT I2C sensors.

Supported sensors simply need to be plugged into the I2C bus of the Arduino to access their readings.

The hope is to provide a simple system for monitoring air quality in houses, workshops 3d printer enclosures etc. using off the shelf components and simple connectors.

# Usage

See example `sensor.ino` sketch for a full usage example.

## Creating a Room Weather Instance

In it's simplest form a Room Weather instance can be created simply by specifying a location.

```
RoomWeather *rw = new RoomWeather("office");
```

Alternatively, Room Weather can connect to WiFi which gives it the ability to export sensor data as Prometheus metrics.

```
char[] ssid = "your_ssid";
char[] password = "your_password";
RoomWeather *rw = new RoomWeather("office", ssid, password);
```

You can also specify a specific IP address.

```
char[] ssid = "your_ssid";
char[] password = "your_password";
String ip = "192.168.86.106";
String netmask = "255.255.255.0";
String gateway = "192.168.86.1";
RoomWeather *rw = new RoomWeather("office", ssid, password, ip, netmask, gateway);
```

## Detecting Sensors

Calling `Detect` will trigger Room Weather to automatically detect any supported sensors connected on I2C.

```
RoomWeather *rw = new RoomWeather("office", "wifi_ssid", "wifipassword");
rw->Detect();
```

## Reading Sensor Values
Calling `Scan` will trigger Room Weather to read the values of all detected sensors.

```
rw->Scan();
```

## Prometheus Export

Sensor data can automatically be exposed in Prometheus metric format on boards that have WiFi enabled.

```
RoomWeather *rw;

void setup() {
  rw = new RoomWeather("office", "wifi_ssid", "wifipassword");
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

```
String celcius = rw->GetHtu31dTempCelcius();
String fahrenheit = rw->GetHtu31dTempFahrenheit();
String humidity = rw->GetHtu31dHumidity();
```

# Configuring Sample Sketch

To run the included `sensor.ino` sketch, you must create a file called `RoomWeatherConfig.h` in your include path.

The file should define the following:

```
#define RW_SECRET_SSID "your_wifi_ssid"
#define RW_SECRET_PASS "your_wifi_password"
#define RW_LOCATION "location_or_name_of_room_weather_instance"
#define RW_SUBMASK "your_subnet_mask"
#define RW_GATEWAY "your_default_gateway"
```