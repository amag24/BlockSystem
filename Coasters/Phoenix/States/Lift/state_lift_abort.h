#ifndef STATE_LIFT_ABORT_H
#define STATE_LIFT_ABORT_H

#include "statemachine/abstract_state.h"

namespace Phoenix {

namespace Lift {

class Abort : public State
{

public:
    Abort()
    {
    }
    
    void onEnter()
    {
        std::cout << "Lift Abort" << std::endl;
    }
    
public:
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors,
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous,
        const std::shared_ptr<const State> next) const
    {
        return std::make_unique<Transition>(); //locked here until finished
    }

public:
    void act(const std::shared_ptr<Actuator> &actuator)
    {
        std::cout << "Lift sending signal to stop" << std::endl;
        actuator->stop();
    }

    bool occupied() const
    {
        return true; // assume
    }

    bool is_moving() const
    {
        return false;
    }

    bool shouldAbort() const
    {
        return true;
    }
};

} // Lift

} // Phoenix

#endif // STATE_LIFT_ABORT_H
