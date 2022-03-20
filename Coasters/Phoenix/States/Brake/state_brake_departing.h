#ifndef STATE_BRAKE_DEPARTING_H
#define STATE_BRAKE_DEPARTING_H

#include "state_brake_occupied.h"

namespace Phoenix
{

namespace Brake
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

    Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors,
        const bool abort,
        const bool stop,
        const State *previous = nullptr,
        const State *next = nullptr) const
    {
        if (abort || (next && next->occupied()))
        {
            return TransitionTo<Abort>();
        }
        else if (stop)
        {
            return TransitionTo<Holding>();
        }
        else if (!*sensors.at("brake"))
        {
            return TransitionTo<Vacant>();
        }

        return Transition();
    }

public:
    void act()
    {
        // move train
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