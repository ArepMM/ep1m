#include    "freq-phase-converter.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
FreqPhaseConverter::FreqPhaseConverter(QObject *parent) : Device(parent)
  , U_in(0.0)
  , U_out(0.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
FreqPhaseConverter::~FreqPhaseConverter()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FreqPhaseConverter::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    U_out = U_in;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FreqPhaseConverter::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FreqPhaseConverter::load_config(CfgReader &cfg)
{
    Q_UNUSED(cfg)
}
