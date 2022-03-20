#ifndef STATE_BRAKE_HOLDING_H
#define STATE_BRAKE_HOLDING_H

#include "state_brake_occupied.h"

namespace Phoenix {

namespace Brake {

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
        const State* previous = nullptr, 
        const State* next = nullptr
        ) const
    {
        if (abort || !*sensors.at("brake"))
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
   void act()
   {
       //stop train
   }

   bool is_moving() const 
   {
       return false;
   }

};

} // Brake

} // Phoenix

#endif // STATE_BRAKE_HOLDING_H