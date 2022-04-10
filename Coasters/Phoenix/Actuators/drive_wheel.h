#ifndef DRIVE_WHEEL_H
#define DRIVE_WHEEL_H

#include <wiringPi.h>
#include "actuator.h"
#include "pca9685.h"

class DriveWheel :  public Actuator 
{

public:
    DriveWheel(const int &pin, const int &hz = 50, const int &pin_base = 300, const int &max_pwm = 4096): 
    Actuator(), _pin(pin), _hz(hz), _pin_base(pin_base), _max_pwm(max_pwm)
    {
    }

public:
    
    void stop() const override
    {
        pwmWrite(_pin_base + _pin), calcTicks(1.5));
    }
    
    void advance() const override
    {
        pwmWrite(_pin_base + _pin), calcTicks(1.1));
    }
private:
    //Calculate the number of ticks the signal should be high for the required amount of time
    int calcTicks(float impulseMs)
    {
        return (int)(_max_pwm * _hz *impulseMs/1000 + 0.5f);
    }

private:
    const int _pin;
    const int _hz;
    const int _pin_base;
    const int _max_pwm;
};

#endif //DRIVE_WHEEL_H