#ifndef STATE_LIFT_DEPARTING_H
#define STATE_LIFT_DEPARTING_H

#include "state_lift_occupied.h"

namespace Phoenix
{

namespace Lift
{

class Vacant;
class Abort;
class Holding;

class Departing : public Occupied
{

public:
    Departing()
    {
    }
    
    void onEnter()
    {
        std::cout << "Lift Departing" << std::endl;
    }

    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors,
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous,
        const std::shared_ptr<const State> next) const
    {
        if (abort || (next && next->occupied()))
        {
            return std::unique_ptr<Transition>(new TransitionTo<Abort>());
        }
        else if (stop)
        {
            return std::unique_ptr<Transition>(new TransitionTo<Holding>());
        }
        else if (!*sensors.at("lift") && sensors.at("lift")->statusDuration() > 1000)
        {
            return std::unique_ptr<Transition>(new TransitionTo<Vacant>());
        }

        return std::make_unique<Transition>();
    }

public:
    void act(const std::shared_ptr<Actuator> &actuator)
    {
        actuator->advance();
    }

    bool is_moving() const
    {
        return true;
    }

    bool departing() const
    {
        return true;
    }
};

} // Lift

} // Phoenix

#endif // STATE_LIFT_DEPARTING_H
