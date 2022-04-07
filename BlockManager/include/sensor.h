#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include <chrono>
#include <atomic>

class Sensor
{

public:
    Sensor(int mpin, int tpin, float threshold = 20.0);

public:
    void sense();

    float statusDuration() const;
    

    explicit operator bool() const
    {
        return _detected.load();
    }

private:
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::atomic<std::chrono::system_clock::time_point> last_change;

    std::atomic<bool> _detected;
    
    const float _threshold;
    const int _mpin;
    const int _tpin;

};

#endif // SENSOR_H