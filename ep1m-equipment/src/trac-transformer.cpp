#include    "trac-transformer.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TractionTransformer::TractionTransformer(QObject *parent) : Device(parent)
  , U1(0.0)
  , Kcc(0.38 / 25.0)
  , U2cc(0.0)
  , U2f(0.0)
  , K1_4(0.35 / 25.0)
  , K2_4(0.70 / 25.0)
  , Kf(1.2 / 25.0)
  , Ut1(0.0)
  , Ut2(0.0)
  , Ut3(0.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TractionTransformer::~TractionTransformer()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionTransformer::ode_system(const state_vector_t &Y,
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
void TractionTransformer::stepDiscrete(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    if (qAbs(U1) >= 19000.0)
        emit soundPlay("Trac_Transformer");
    else
        emit soundStop("Trac_Transformer");

    U2cc = Kcc * U1;
    U2f = Kf * U1;
    Ut1 = K1_4 * U1;
    Ut2 = K1_4 * U1;
    Ut3 = K2_4 * U1;
}
