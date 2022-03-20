#ifndef STATE_LIFT_VACANT_H
#define STATE_LIFT_VACANT_H 

#include "include/statemachine/abstract_state.h"

namespace Phoenix {

namespace Lift {

class Entering;
class Departing;
class Abort;

class Vacant : public State
{

public:
    Vacant()
    {
    }

public:
    
    Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const State* previous = nullptr, 
        const State* next = nullptr
        ) const
    {
        if(abort || *sensors.at("lift"))
        {
            return TransitionTo<Abort>();
        } 
        else if (previous && previous->departing() && !abort && !stop)
        {
            return TransitionTo<Entering>();
        }

        return Transition();

    }

public:
   void act()
   {

   }

   bool occupied() const
   {
       return false;
   }

   bool is_moving() const
   {
       return false;
   }

   

};

} // Lift

} // Phoenix





#endif // SSTATE_LIFT_INITIALIZE_H_