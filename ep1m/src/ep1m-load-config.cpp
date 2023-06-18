#include    "ep1m.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::loadConfig(QString path)
{
    CfgReader cfg;

    if (cfg.load(path))
    {
        QString secName = "Vehicle";

        cfg.getDouble(secName, "MainResLeak", main_res_leak);
        cfg.getDouble(secName, "ReductorCoeff", ip);
        cfg.getBool(secName, "isRegistratorOn", is_Registarator_on);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::load_brakes_config(QString path)
{
    CfgReader cfg;

    if (cfg.load(path))
    {
        QString secName = "BrakesState";

        double pFL = 0.0;

        if (cfg.getDouble(secName, "MainReservoirPressure", pFL))
        {
            main_reservoir->setY(0, pFL);
        }

        double k_flow = 0.0;

        if (cfg.getDouble(secName, "MainReservoirFlow", k_flow))
        {
            main_reservoir->setLeakCoeff(k_flow);
        }

        double ch_press = 0.0;

        if (cfg.getDouble(secName, "ChargingPressure", ch_press))
        {
            charge_press = ch_press;
            brake_crane->init(charge_press, pFL);
            supply_reservoir->setY(0, charge_press);
        }

        int train_crane_pos = 6;

        if (cfg.getInt(secName, "TrainCranePos", train_crane_pos))
        {
            brake_crane->setHandlePosition(train_crane_pos);
        }

        int loco_crane_pos = 0;

        if (cfg.getInt(secName, "LocoCranePos", loco_crane_pos))
        {
            loco_crane->setHandlePosition(loco_crane_pos);
        }

        int combine_crane_pos = 0;
        int brake_lock_state = 0;

        if (cfg.getInt(secName, "CombineCranePos", combine_crane_pos))
        {
            brake_lock->setCombineCranePosition(combine_crane_pos);
        }

        if (cfg.getInt(secName, "BrakeLockDevice", brake_lock_state))
        {
            brake_lock->setState(brake_lock_state);
        }
    }
}
