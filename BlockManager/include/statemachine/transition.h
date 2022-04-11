#ifndef TRANSITION_H
#define TRANSITION_H
#include <iostream>
class State;

class Transition
{

public:
    Transition()
    {
    }

    virtual ~Transition()
    {
    }
    
public:
    virtual State* newState() const
    {
        throw std::runtime_error("Called newState but no transtition was specified");
    }

    virtual explicit operator bool() const
    {
        //~ std::cout << "Not Available"<<std::endl;
        return false;
    }
    
};


template <class DesiredState>
class TransitionTo : public Transition
{
public:
    TransitionTo(): Transition()   
    {
    }

public:
    State* newState() const override
    {
        return new DesiredState();
    }

    explicit operator bool() const override
    {
        return true;
    }
    
};
    

#endif // TRANSITION_H
