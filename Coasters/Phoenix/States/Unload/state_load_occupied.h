#ifndef STATE_UNLOAD_OCCUPIED_H
#define STATE_UNLOAD_OCCUPIED_H

#include "include/statemachine/abstract_state.h"

namespace Phoenix {

namespace Unload {

class Occupied : public State
{

public:
   bool occupied() const override
   {
       return true;
   }
};

} // Unload

} // Phoenix

// Initialize
// Abort
// Vacant
//      Entering
// Occupied
//      Approaching
//      Holding
//      Departing




#endif // STATE_UNLOAD_OCCUPIED_H