#ifndef STATE_STATION_ABORT_H
#define STATE_STATION_ABORT_H

#include "statemachine/abstract_state.h"

namespace Phoenix {

namespace Station {

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
        const std::shared_ptr<const State> previous,
        const std::shared_ptr<const State> next) const
    {
        return Transition(); //locked here until finished
    }

public:
    void act(const std::shared_ptr<Actuator> &actuator)
    {
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

} // Station

} // Phoenix

#endif // STATE_STATION_ABORT_H