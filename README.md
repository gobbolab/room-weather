# Room Weather

Room Weather is an Arduino library that aims to provide plug and play support for monitoring air quality using STEMMA QT I2C sensors.

Supported sensors simply need to be plugged into the I2C bus of the Arduino to access their readings.

The hope is to provide a simple system for monitoring air quality in houses, workshops, 3d printer enclosures etc. using off the shelf components and simple connectors.

This library will work with any Arduino board, but we specifically reccomend the [Adafruit ESP32 Feather V2](https://www.adafruit.com/product/5400). This board comes with ESP32 wifi, enabling automatic export of sensor data in Prometheus metrics format. The integrated STEMMA QT connector allows for quick solderless connections to sensors.

# Supported Sensors
- [HTU31D Temp & Humidity](https://www.adafruit.com/product/4832)
- [SGP30 VOC & C02](https://www.adafruit.com/product/3709)
- [SGP40 VOC Index](https://www.adafruit.com/product/4829)
- [PMSA003I Air Quality](https://www.adafruit.com/product/4632)


# Usage

See [examples folder](https://github.com/gobbolab/room-weather/tree/main/examples) for full usage examples.

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

## Detecting Sensors

Calling `Detect` will trigger Room Weather to automatically detect any supported sensors connected on I2C.

```
rw->Detect();
```

## Reading Sensor Values
Calling `Read` will trigger Room Weather to read the values of all detected sensors immediately.

```
rw->Read();
```

Alternatively, you can pass an interval in milliseconds to `Read` which will cause the sensors to be read to only if the time since the last read is greater than the given interval.

```
rw->Read(1000);
```

This means you can call `Read` in your main loop in a non blocking fashion, knowing that sensors values are updated only at the interval you specify.
This prevents issues caused by bombarding the sensors with reads as fast as the Adruino can call `loop`.

## Accessing Values
The values obtained from the most recent call to `Read` are available in `Values` property.

For example:
```
rw->Values.Htu31d.Humidity
```

More information about accessing specific sensor values can be found in the [Sensor Utilization Section](https://github.com/gobbolab/room-weather#sensor-utilization)

## Printing Sensor Values
Calling `Print` will print detected sensor data to the serial monitor.
`Print` assumes that `Serial.begin` has already been called.

```
rw->Print();
```

Calling `Print` and passing an index will print the values of the specified sensor.

```
rw->Print(RW_SGP30_INDEX);
```

### Sensor Index Constants
- RW_HTU31D_INDEX
- RW_SGP30_INDEX
- RW_SGP40_INDEX
- RW_PMSA003I_INDEX

## Prometheus Export

Sensor data can automatically be exposed in Prometheus metric format on boards that have WiFi enabled.
This makes it very easy to get data from your RoomWeather devices into services such as Grafana which allow you to setup dashboards, graphs and automation around this data.

```
RoomWeather *rw;

void setup() {
  rw = new RoomWeather("office", "wifi_ssid", "wifipassword");
  rw->Detect();
}

void loop() {
  rw->Read();

  // ServeMetrics will handle any incoming http request and respond with available sensor 
  // data in prometheus metric format
  rw->ServeMetrics();
}
```

You can verify metrics are available using a web browser on your local network.
In the address bar of your browser enter: `http://<IP_OF_ROOM_WEATHER_DEVICE>/metrics`
For example: `http://192.168.86.133/metrics`

# Sensor Utilization

## HTU31D Temp & Humidity

### Values

```
rw->Values.Htu31d.Humidity;
rw->Values.Htu31d.AsboluteHumidity;
rw->Values.Htu31d.TemperatureCelsius;
rw->Values.Htu31d.TemperatureFahrenheit;
```

### Features

* Fahrenheit temperature is made available by converting the sensor's celsius reading.
* Absolute humitidy is made available by a calculation using the sensor's humidity and temperature readings.

## SGP30 VOC & C02

### Values

```
rw->Values.Sgp30.CO2;
rw->values.Sgp30.VOC;
```

## SGP40 VOC Index

### Values

```
rw->Values.Sgp40.Raw;
rw->values.Sgp40.VOCIndex;
```

### Features

* If HTU31D has been detected, it's humidity and temperature values will be automatically provided to SGP40 for more accurate readings.

## PMSA003I Air Quality

### Values

```
rw->values->Pmsa003i.Pm10Standard;
rw->values->Pmsa003i.Pm25Standard;
rw->values->Pmsa003i.Pm100Standard;
rw->values->Pmsa003i.Pm10Env;
rw->values->Pmsa003i.Pm25Env;
rw->values->Pmsa003i.Pm100Env;
rw->values->Pmsa003i.Particles03um;
rw->values->Pmsa003i.Particles05um;
rw->values->Pmsa003i.Particles10um;
rw->values->Pmsa003i.Particles25um;
rw->values->Pmsa003i.Particles50um;
rw->values->Pmsa003i.Particles100um;
```

# Arduino Library Registry
Arduino Library Registry logs for this library can be found [here](https://downloads.arduino.cc/libraries/logs/github.com/gobbolab/room-weather/).