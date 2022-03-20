#ifndef STATE_LIFT_OCCUPIED_H
#define STATE_LIFT_OCCUPIED_H

#include "include/statemachine/abstract_state.h"

namespace Phoenix {

namespace Lift {

class Occupied : public State
{

public:
   bool occupied() const override
   {
       return true;
   }
};

} // Lift

} // Phoenix

// Initialize
// Abort
// Vacant
//      Entering
// Occupied
//      Approaching
//      Holding
//      Departing




#endif // STATE_LIFT_OCCUPIED_H