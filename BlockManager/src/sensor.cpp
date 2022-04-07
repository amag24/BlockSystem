#include "sensor.h"

Sensor::Sensor(int mpin, int tpin, float threshold) : _mpin(mpin), _tpin(tpin), _threshold(threshold), _detected(false), last_change(std::chrono::system_clock::now())
{
    pinMode(_tpin, OUTPUT);
}

void Sensor::sense()
{
    //Reset
    pinMode(_mpin, OUTPUT);
    digitalWrite(_mpin, 0);
    digitalWrite(_tpin, 0);
    delay(0.0005);
    pinMode(_mpin, INPUT);
    delay(0.0005);

    //Fire pulse
    digitalWrite(_tpin, 1);
    _start = std::chrono::system_clock::now();
    while (!digitalRead(_mpin)){} //Wait to recieve signal 

    end = std::chrono::system_clock::now();
    bool new_detection = duration_cast<std::chrono::milliseconds>(end - _start).count() * 0.02;

    if (new_detection != _detected) {_last_change = end}
    _detected = new_detection;
}

float Sensor::statusDuration() const
{
    return duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _last_change.load()).count();
}
