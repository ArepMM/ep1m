#include    "ep1m.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::initSafetyDevices()
{
    klub_BEL = new KLUB();
    klub_BEL->setMaxVelocity(140.0);
}