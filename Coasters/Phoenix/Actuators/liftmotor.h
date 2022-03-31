#ifndef LIFT_MOTOR_H
#define LIFT_MOTOR_H

#include <RCSwitch.h>
#include "actuator.h"


class LiftMotor :  public Actuator 
{

public:
    LiftMotor(const int &pin): Actuator(), m_transmitter()
    {
        m_transmitter.enableTransmit(pin);
        m_transmitter.setProtocol(1);
        m_transmitter.setPulseLength(185);
        m_transmitter.setRepeatTransmit(3);
    }

public:
    
    void stop() const override
    {
        m_transmitter.send(70972, 24);
    }
    
    void advance() const override
    {
        m_transmitter.send(70963, 24);
    }

private:
    RCSwitch m_transmitter;
};

#endif //LIFT_MOTOR_H