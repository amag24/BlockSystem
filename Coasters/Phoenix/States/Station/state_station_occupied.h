#ifndef STATE_STATION_OCCUPIED_H
#define STATE_STATION_OCCUPIED_H

#include "include/statemachine/abstract_state.h"

namespace Phoenix {

namespace Station {

class Occupied : public State
{

public:
   bool occupied() const override
   {
       return true;
   }
};

} // Station

} // Phoenix

// Initialize
// Abort
// Vacant
//      Entering
// Occupied
//      Approaching
//      Holding
//      Departing




#endif // STATE_STATION_OCCUPIED_H