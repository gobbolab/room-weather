#ifndef RW_Values_h
#define RW_Values_h

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

class RW_Values {
    public:
        Htu31dValues Htu31d;
        Sgp30Values Sgp30;

};

#endif