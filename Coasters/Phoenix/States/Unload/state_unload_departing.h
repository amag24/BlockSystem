#ifndef STATE_UNLOAD_DEPARTING_H
#define STATE_UNLOAD_DEPARTING_H

#include "state_unload_occupied.h"

namespace Phoenix
{

namespace Unload
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
        std::cout << "Unload Departing" << std::endl;
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
        else if (!*sensors.at("unload"))
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

} // Unload

} // Phoenix

#endif // STATE_UNLOAD_DEPARTING_H
