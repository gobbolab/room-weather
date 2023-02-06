#ifndef SensorValues_h
#define SensorValues_h

class Htu31dValues {
    public:
        float TemperatureCelsius;
        float TemperatureFahrenheit;
        float Humidity;
};

class Sgp30Values {
    public:
        float CO2;
        float VOC;
};

class SensorValues {
    public:
        Htu31dValues Htu31d;
        Sgp30Values Sgp30;

};

#endif