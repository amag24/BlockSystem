#ifndef STATE_STATION_VACANT_H
#define STATE_STATION_VACANT_H 

#include "statemachine/abstract_state.h"

namespace Phoenix {

namespace Station {

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
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        if(abort || *sensors.at("station"))
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
   void act(const std::shared_ptr<Actuator> &actuator)
   {
       actuator->stop();
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

} // Station

} // Phoenix





#endif // SSTATE_STATION_INITIALIZE_H_