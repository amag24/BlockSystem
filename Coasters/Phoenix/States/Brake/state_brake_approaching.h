#ifndef STATE_BRAKE_APPROACHING_H
#define STATE_BRAKE_APPROACHING_H

#include "state_brake_occupied.h"

namespace Phoenix {

namespace Brake {

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
        const State* previous = nullptr, 
        const State* next = nullptr
        ) const
    {
        if(abort){
            return TransitionTo<Abort>();
        }
        else if(*sensors.at("brake"))
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
   void act()
   {
       //move train
   }

   bool is_moving() const
   {
       return true;
   }

};

} // Brake

} // Phoenix

#endif // STATE_BRAKE_APPROACHING_H