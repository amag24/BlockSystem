#ifndef STATE_BRAKE_DEPARTING_H
#define STATE_BRAKE_DEPARTING_H

#include "state_brake_occupied.h"

namespace Phoenix
{

namespace Brake
{

class Leaving;
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
        std::cout << "Brake Departing" << std::endl;
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
        else if (!*sensors.at("brake"))
        {
            return std::unique_ptr<Transition>(new TransitionTo<Leaving>());
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

} // Brake

} // Phoenix

#endif // STATE_BRAKE_DEPARTING_H
