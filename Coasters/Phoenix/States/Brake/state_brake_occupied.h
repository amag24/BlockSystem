#ifndef STATE_BRAKE_OCCUPIED_H
#define STATE_BRAKE_OCCUPIED_H

#include "include/statemachine/abstract_state.h"

namespace Phoenix {

namespace Brake {

class Occupied : public State
{

public:
   bool occupied() const override
   {
       return true;
   }
};

} // Brake

} // Phoenix

// Initialize
// Abort
// Vacant
//      Entering
// Occupied
//      Approaching
//      Holding
//      Departing




#endif // STATE_BRAKE_OCCUPIED_H