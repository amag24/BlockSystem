#ifndef ABSTRACT_STATE_H
#define ABSTRACT_STATE_H

#include <functional>
#include <unordered_map>
#include <memory>
#include <iostream>

#include "transition.h"
#include "sensor.h"
#include "actuator.h"


class State
{

public:
    State()
    {
    }

    virtual ~State()
    {
    }

public:
    virtual void onEnter()
    {
    }

    virtual void onExit()
    {
    }
    
    virtual std::unique_ptr<Transition> getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const std::shared_ptr<const State> previous, 
        const std::shared_ptr<const State> next
        ) const
    {
        return std::make_unique<Transition>();
    }

public:
   virtual void act(const std::shared_ptr<Actuator> &actuator)
   {
       actuator->stop();
   }

   virtual bool occupied() const = 0; 

   virtual bool is_moving() const = 0;

   virtual bool shouldAbort() const 
   {
       return false;
   }

   virtual bool departing() const
   {
       return false;
   }

};

#endif // ABSTRACT_STATE_H
