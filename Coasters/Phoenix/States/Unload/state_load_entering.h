#ifndef STATE_UNLOAD_ENTERING_H
#define STATE_UNLOAD_ENTERING_H

#include "state_unload_vacant.h"

namespace Phoenix {

namespace Unload {

class Approaching;

class Entering : public Vacant 
{

public:
    Entering()
    {
    }
 
    Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const State* previous = nullptr, 
        const State* next = nullptr
        ) const override
    {

        if(abort || *sensors.at("unload"))
        {
            return TransitionTo<Abort>(); // we should not see the train if previous block does too
        }
        else if (stop)
        {
            return TransitionTo<Vacant>();
        } 
        else if (!previous->departing())
        {
            return TransitionTo<Approaching>();
        }
        
        return Transition();
    }

public:
    void act() override
    {
        // move
    }

    bool is_moving() const
    {
        return true;
    }
};

} // Unload

} // Phoenix




#endif // STATE_UNLOAD_ENTERING_H