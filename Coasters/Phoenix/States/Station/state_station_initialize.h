#ifndef STATE_STATION_INITIALIZE_H
#define STATE_STATION_INITIALIZE_H

#include "statemachine/abstract_state.h"


namespace Phoenix {

namespace Station {

class Holding;
class Vacant;

class Initialize : public State
{

public:
    
    virtual Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const State* previous = nullptr, 
        const State* next = nullptr
        ) const
    {   
        try
        {
            if(*sensors.at("station"))
            {
                return TransitionTo<Holding>();
            } else {
                return TransitionTo<Vacant>();
            }
        } catch(std::out_of_range)
        {
            return Transition();
        }

    }

public:

   bool occupied()
   {
       return true;
   } 

   bool is_moving() const
   {
       return false;
   }

};

} // Station

} // Phoenix


#endif // STATE_STATION_INITIALIZE_H