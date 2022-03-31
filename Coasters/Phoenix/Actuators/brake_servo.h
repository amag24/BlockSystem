#ifndef BRAKE_SERVO_H
#define BRAKE_SERVO_H

#include <wiringPi.h>
#include "actuator.h"
#include "pca9685.h"

class BrakeServo :  public Actuator 
{

public:
    BrakeServo(const int &pin, const int &hz = 50): Actuator(), _pin(pin), _hz(hz)
    {
    }

public:
    
    void stop() const override
    {
        pwmWrite(_pin_base + _pin), calcTicks(1.0));
    }
    
    void advance() const override
    {
        pwmWrite(_pin_base + _pin), calcTicks(2.0));
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
    const int _pin_base = 300;
    const int _max_pwm = 4096;
};

#endif //BRAKE_SERVO_H