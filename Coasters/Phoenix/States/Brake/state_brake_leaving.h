#ifndef STATE_BRAKE_LEAVING_H
#define STATE_BRAKE_LEAVING_H

#include "state_brake_occupied.h"

namespace Phoenix {

namespace Brake {

class Abort;
class Vacant;

class Leaving : public Occupied
{

public:
    Leaving()
    {
    }
    
    void onEnter()
    {
        std::cout << "Brake Leaving" << std::endl;
    }
    
 
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        if(abort || *sensors.at("brake")){
            return std::unique_ptr<Transition>(new TransitionTo<Abort>());
        }
        //Check if next block has accepted the train
        if (next && next->occupied() && (next->departing() || !next->is_moving()))
        {
            return std::unique_ptr<Transition>(new TransitionTo<Vacant>());
        }
        return std::make_unique<Transition>();
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

} // Brake

} // Phoenix

#endif // STATE_BRAKE_LEAVING_H
