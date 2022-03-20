#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include <chrono>

class Sensor
{

public:
    Sensor(int mpin, int tpin);

public:
    void sense();

    float statusDuration();
    

    explicit operator bool() const
    {
        return _detected;
    }

private:
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    float _time_since_switch = 0.0;
    bool _detected = false;
    int _mpin;
    int _tpin;
};

#endif // SENSOR_H