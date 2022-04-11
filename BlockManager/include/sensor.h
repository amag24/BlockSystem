#ifndef SENSOR_H
#define SENSOR_H

#include <wiringPi.h>
#include <chrono>
#include <atomic>
#include <deque>
#include <iostream>
class Sensor
{

public:
    Sensor(int mpin, int tpin, float threshold = 20.0);

public:
    void sense();
    
    void printReport();
    
    float statusDuration() const;

    explicit operator bool() const
    {
        return _detected.load();
    }
    
private:
    void addReading(const float &reading);
    
private:
    std::chrono::system_clock::time_point _start = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point _end = std::chrono::system_clock::now();
    std::atomic<std::chrono::system_clock::time_point> _last_change;
    
    std::deque<float> _sensor_readings;
    std::atomic<bool> _detected;
    
    const float _threshold;
    const int _mpin;
    const int _tpin;

};

#endif // SENSOR_H
