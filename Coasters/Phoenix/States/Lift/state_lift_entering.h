#ifndef STATE_LIFT_ENTERING_H
#define STATE_LIFT_ENTERING_H

#include "state_lift_vacant.h"

namespace Phoenix {

namespace Lift {

class Approaching;

class Entering : public Vacant 
{

public:
    Entering()
    {
    }
    
    void onEnter() override
    {
        std::cout << "Lift Entering" << std::endl;
    }
 
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const override
    {

        if(abort || *sensors.at("lift"))
        {
            if (!abort) {
                std::cout << "Lift throwing abort" << std::endl;
                sensors.at("unload")->printReport();
            }
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

} // Lift

} // Phoenix




#endif // STATE_LIFT_ENTERING_H
