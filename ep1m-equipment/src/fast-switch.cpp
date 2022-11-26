#include    "fast-switch.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
FastSwitch::FastSwitch(QObject *parent) : Relay(2, parent)
  , Uc(0.0)
  , is_power_On(false)
  , is_Hold(false)
  , Id(0.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
FastSwitch::~FastSwitch()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FastSwitch::preStep(state_vector_t &Y, double t)
{
    bool is_On = (is_power_On &&
            getContactState(1)) || is_Hold;

    setVoltage(Uc * static_cast<double>(is_On));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FastSwitch::load_config(CfgReader &cfg)
{
    Relay::load_config(cfg);
}
