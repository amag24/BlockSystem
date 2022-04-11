#ifndef STATE_BRAKE_HOLDING_H
#define STATE_BRAKE_HOLDING_H

#include "state_brake_occupied.h"

namespace Phoenix {

namespace Brake {

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
        std::cout << "Brake Holding" << std::endl;
    }
    
    
    std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        if (abort || !*sensors.at("brake"))
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

} // Brake

} // Phoenix

#endif // STATE_BRAKE_HOLDING_H
