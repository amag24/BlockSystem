#ifndef TRANSITION_H
#define TRANSITION_H

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
    virtual State* newState() const override
    {
        return new DesiredState();
    }

    virtual explicit operator bool() const override
    {
        return true;
    }
    
};
    

#endif // TRANSITION_H