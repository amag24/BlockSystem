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
    
    void onEnter()
    {
        std::cout << "Unload Holding" << std::endl;
    }
    
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        if (abort || !*sensors.at("unload"))
        {
            return std::unique_ptr<Transition>(new TransitionTo<Abort>());
        }
        else if (next && !next->occupied() && !stop)
        {
            return std::unique_ptr<Transition>(new TransitionTo<Departing>());
        }

        return std::make_unique<Transition>();
    }

public:
   void act(const std::shared_ptr<Actuator> &actuator)
   {
       actuator->stop();
   }

   bool is_moving() const 
   {
       return false;
   }

};

} // Unload

} // Phoenix

#endif // STATE_UNLOAD_HOLDING_H
