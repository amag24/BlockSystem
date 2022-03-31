#ifndef ABSTRACT_STATE_H
#define ABSTRACT_STATE_H

#include <functional>
#include <unordered_map>
#include <memory>

#include "transition.h"
#include "include/sensor.h"
#include "include/actuator.h"


class State
{

public:
    State()
    {
    }

public:
    virtual void onEnter()
    {
    }

    virtual void onExit()
    {
    }
    
    virtual Transition getTransition(
        const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, 
        const bool abort,
        const bool stop,
        const State* previous = nullptr, 
        const State* next = nullptr
        ) const
    {
        return Transition();
    }

public:
   virtual void act()
   {

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