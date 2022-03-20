#ifndef STATE_BRAKE_ABORT_H
#define STATE_BRAKE_ABORT_H

#include "include/statemachine/abstract_state.h"

namespace Phoenix {

namespace Brake {

class Abort : public State
{

public:
    Abort()
    {
    }

public:
    Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors,
        const bool abort,
        const bool stop,
        const State *previous = nullptr,
        const State *next = nullptr) const
    {
        return Transition(); //locked here until finished
    }

public:
    void act()
    {
        // stop motion
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

} // Brake

} // Phoenix

#endif // STATE_BRAKE_ABORT_H