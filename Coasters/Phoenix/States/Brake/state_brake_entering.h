#ifndef STATE_BRAKE_ENTERING_H
#define STATE_BRAKE_ENTERING_H

#include "state_brake_vacant.h"

namespace Phoenix {

namespace Brake {

class Approaching;

class Entering : public Vacant 
{

public:
    Entering()
    {
    }
    
    void onEnter() override
    {
        std::cout << "Brake Entering" << std::endl;
    }
    
 
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const override
    {

        if(abort || *sensors.at("brake"))
        {
            return std::unique_ptr<Transition>(new TransitionTo<Abort>()); // we should not see the train if previous block does too
        }
        else if (stop)
        {
            return std::unique_ptr<Transition>(new TransitionTo<Vacant>());
        } 
        else if (!previous->departing())
        {
            return std::unique_ptr<Transition>(new TransitionTo<Approaching>());
        }
        
        return std::make_unique<Transition>();
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

} // Brake

} // Phoenix




#endif // STATE_BRAKE_ENTERING_H
