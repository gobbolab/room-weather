#ifndef RW_Values_h
#define RW_Values_h

class Htu31dValues {
    public:
        float TemperatureCelsius;
        float TemperatureFahrenheit;
        float Humidity;
        float AbsoluteHumidity;
};

class Sgp30Values {
    public:
        float CO2;
        float VOC;
};

class Pm25AqiValues {
    public:
        uint16_t Pm10Standard;
        uint16_t Pm25Standard;
        uint16_t Pm100Standard;
        uint16_t Pm10Env;
        uint16_t Pm25Env;
        uint16_t Pm100Env;
        uint16_t Particles03um;
        uint16_t Particles05um;
        uint16_t Particles10um;
        uint16_t Particles25um;
        uint16_t Particles50um;
        uint16_t Particles100um;
};

class RW_Values {
    public:
        Htu31dValues Htu31d;
        Sgp30Values Sgp30;
        Pm25AqiValues Pm25Aqi;

};

#endif