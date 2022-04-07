#ifndef STATE_UNLOAD_APPROACHING_H
#define STATE_UNLOAD_APPROACHING_H

#include "state_unload_occupied.h"

namespace Phoenix {

namespace Unload {

class Abort;
class Holding;
class Departing; 

class Approaching : public Occupied
{

public:
    Approaching()
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
        if(abort){
            return TransitionTo<Abort>();
        }
        else if(*sensors.at("unload"))
        {
            if (next and next->occupied())
            {
                return TransitionTo<Holding>();
            }
            else if (next and !next->occupied())
            {
                return TransitionTo<Departing>();
            }
        }
        return Transition();
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

};

} // Unload

} // Phoenix

#endif // STATE_UNLOAD_APPROACHING_H