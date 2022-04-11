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
    
    void onEnter()
    {
        std::cout << "Station Initialize" << std::endl;
    }
    
    virtual std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {   
        try
        {
            if(*sensors.at("station"))
            {
                return std::unique_ptr<Transition>(new TransitionTo<Holding>());
            } else {
                return std::unique_ptr<Transition>(new TransitionTo<Vacant>());
            }
        } catch(std::out_of_range& oor)
        {
            return std::make_unique<Transition>();
        }

    }

public:

   bool occupied() const
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
