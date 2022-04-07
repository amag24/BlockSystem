#ifndef STATE_STATION_HOLDING_H
#define STATE_STATION_HOLDING_H

#include "state_station_occupied.h"

namespace Phoenix {

namespace Station {

class Abort;
class Departing;

class Holding : public Occupied
{

public:
    Holding()
    {
    }
    
    Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        if (abort || !*sensors.at("station"))
        {
            return TransitionTo<Abort>();
        }
        else if (next && !next->occupied() && !stop)
        {
            return TransitionTo<Departing>();
        }

        return Transition();
    }

public:
   void act(const std::shared_ptr<Actuator> &actuator)
   {
       actuator->stop();
   }

   bool is_moving() const 
   {
       return false;
   }

};

} // Station

} // Phoenix

#endif // STATE_STATION_HOLDING_H