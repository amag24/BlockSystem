#include "sensor.h"

Sensor::Sensor(int mpin, int tpin) : _mpin(mpin), _tpin(tpin)
{
    pinMode(_tpin, OUTPUT);
}

void Sensor::sense()
{
    pinMode(_mpin, OUTPUT);
    digitalWrite(_mpin, 0);
    digitalWrite(_tpin, 0);
    delay(0.0005);
    pinMode(_mpin, INPUT);
    delay(0.0005);
    digitalWrite(_tpin, 1);
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    while (digitalRead(mpin) == 0) end = std::chrono::system_clock::now();
    std::cout << duration_cast<std::chrono::milliseconds>(end - start).count()<<std::endl;
}

float Sensor::statusDuration()
{
        return _time_since_switch;
}
