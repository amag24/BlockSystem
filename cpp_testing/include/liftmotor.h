#ifndef LIFT_MOTOR_H
#define LIFT_MOTOR_H

#include <RCSwitch.h>


class LiftMotor
{

public:
    LiftMotor(const int &pin): m_transmitter()
    {
        m_transmitter.enableTransmit(pin);
        m_transmitter.setProtocol(1);
        m_transmitter.setPulseLength(185);
        m_transmitter.setRepeatTransmit(10);
    }

public:
    
    void stop() 
    {
        m_transmitter.send(70972, 24);
    }
    
    void advance()
    {
        m_transmitter.send(70963, 24);
    }

private:
    RCSwitch m_transmitter;
};

#endif //LIFT_MOTOR_H
