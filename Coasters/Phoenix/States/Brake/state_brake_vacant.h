#ifndef STATE_BRAKE_VACANT_H
#define STATE_BRAKE_VACANT_H 

#include "statemachine/abstract_state.h"

namespace Phoenix {

namespace Brake {

class Entering;
class Departing;
class Abort;

class Vacant : public State
{

public:
    Vacant()
    {
    }
    
    void onEnter()
    {
        std::cout << "Brake Vacant" << std::endl;
    }
    

public:
    
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        if(abort || *sensors.at("brake"))
        {
            return std::unique_ptr<Transition>(new TransitionTo<Abort>());
        } 
        else if (previous && previous->departing() && !abort && !stop)
        {
            return std::unique_ptr<Transition>(new TransitionTo<Entering>());
        }

        return std::make_unique<Transition>();

    }

public:
   void act(const std::shared_ptr<Actuator> &actuator)
   {
       actuator->advance();
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

} // Brake

} // Phoenix





#endif // SSTATE_BRAKE_INITIALIZE_H_
