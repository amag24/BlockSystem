#include "sensor.h"

Sensor::Sensor(int mpin, int tpin) : _mpin(mpin), _tpin(tpin)
{
    pinMode(_tpin, OUTPUT);
}

float Sensor::sense()
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
    int count = 0;
    while (digitalRead(_mpin) == 0) {
        end = std::chrono::system_clock::now();
        count++;
    }
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}


