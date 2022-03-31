#ifndef STATE_UNLOAD_HOLDING_H
#define STATE_UNLOAD_HOLDING_H

#include "state_unload_occupied.h"

namespace Phoenix {

namespace Unload {

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
        if (abort || !*sensors.at("unload"))
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

} // Unload

} // Phoenix

#endif // STATE_UNLOAD_HOLDING_H