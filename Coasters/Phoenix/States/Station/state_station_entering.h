#ifndef STATE_STATION_ENTERING_H
#define STATE_STATION_ENTERING_H

#include "state_station_vacant.h"

namespace Phoenix {

namespace Station {

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
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const override
    {

        if(abort || *sensors.at("station"))
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
    void act(const std::shared_ptr<Actuator> &actuator) override
    {
        actuator->advance();
    }

    bool is_moving() const
    {
        return true;
    }
};

} // Station

} // Phoenix




#endif // STATE_STATION_ENTERING_H