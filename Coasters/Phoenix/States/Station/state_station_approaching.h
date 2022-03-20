#ifndef STATE_STATION_APPROACHING_H
#define STATE_STATION_APPROACHING_H

#include "state_station_occupied.h"

namespace Phoenix {

namespace Station {

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
        else if(*sensors.at("station"))
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

} // Station

} // Phoenix

#endif // STATE_STATION_APPROACHING_H