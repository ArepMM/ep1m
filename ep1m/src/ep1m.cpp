#include    "ep1m.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EP1m::EP1m(QObject *parent) : Vehicle (parent)
  , tumblers_panel(Q_NULLPTR)
  , msud(Q_NULLPTR)
  , Ucc(0.0)
  , battery(Q_NULLPTR)
  , power_supply(Q_NULLPTR)
  , Icc(0.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EP1m::~EP1m()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::initialization()
{
    // Инициализация питания цепей управления
    initControlPower();

    // Инициализация АЗВ
    initAZV();

    // Инициализация пульта управления в кабине
    initPanel();

    // Инициализация микропроцессорной системы управления и диагностики (МСУД)
    initMSUD();

    // Инициализация озвучки
    initSounds();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::step(double t, double dt)
{
    // Работа подсистемы питания цепей управления
    stepControlPower(t, dt);

    // Работа приборов управления в кабине
    stepPanel(t, dt);

    // Работа микропроцессорной системы управления и диагностики
    stepMSUD(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_VEHICLE(EP1m)
