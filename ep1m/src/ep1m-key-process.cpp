#include    "ep1m.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::keyProcess()
{
    // Включение/выключение шкафа питания ШП-21
    if (getKeyState(KEY_H))
    {
        if (isShift())
            tumblers[TUMBLER_POWER_SUPPLY_ON].set();
        else
            tumblers[TUMBLER_POWER_SUPPLY_ON].reset();
    }

    // Перевод реверсивной рукоятки
    if (getKeyState(KEY_W))
    {
        tumblers[SWITCH_REVERS_FWD].set();
    }
    else
    {
        tumblers[SWITCH_REVERS_FWD].reset();
    }

    if (getKeyState(KEY_S))
    {
        tumblers[SWITCH_REVERS_BWD].set();
    }
    else
    {
        tumblers[SWITCH_REVERS_BWD].reset();
    }

    // Включение блока сигнализации
    if (getKeyState(KEY_8) && !isAlt())
    {
        if (isShift())
            tumblers[TUMBLER_BS_002].set();
        else
            tumblers[TUMBLER_BS_002].reset();
    }

    // РБ
    if (getKeyState(KEY_M))
        tumblers[BUTTON_RB].set();
    else
        tumblers[BUTTON_RB].reset();

    // РБС
    /*if (getKeyState(KEY_Z))
        tumblers[BUTTON_RBS].set();
    else
        tumblers[BUTTON_RBS].reset();*/

    bool is_cp_ready = static_cast<bool>(control_signals.analogSignal[FB_READY].cur_value);

    bool is_cp_RBS = static_cast<bool>(control_signals.analogSignal[FB_RBS].cur_value);

    if (!is_cp_ready)
    {
        if (getKeyState(KEY_Z))
            tumblers[BUTTON_RBS].set();
        else
            tumblers[BUTTON_RBS].reset();
    }
    else
    {
        if (is_cp_RBS)
            tumblers[BUTTON_RBS].set();
        else
            tumblers[BUTTON_RBS].reset();
    }

    // ЭПК
    if (getKeyState(KEY_N))
    {
        if (isShift())
            tumblers[EPK_KEY].set();
        else
            tumblers[EPK_KEY].reset();
    }

    // Выбор МПК
    if (getKeyState(KEY_1) && !isAlt())
    {
        if (isShift())
            tumblers[TUMBLER_MPK].set();
        else
            tumblers[TUMBLER_MPK].reset();
    }

    // Вкл/Выкл "АВТОРЕГУЛИРОВАНИЕ"
    if (getKeyState(KEY_F))
    {
        if (isShift())
            tumblers[TUMBLER_AUTO_MODE].reset();
        else
            tumblers[TUMBLER_AUTO_MODE].set();
    }

    // Отключение ПЧФ
    if (getKeyState(KEY_2) && !isAlt())
    {
        if (isShift())
            tumblers[TUMBLER_PCHF].set();
        else
            tumblers[TUMBLER_PCHF].reset();
    }

    // Отпуск тормозов
    if (getKeyState(KEY_R))
        tumblers[BRAKE_RELEASE_BUTTON].set();
    else
        tumblers[BRAKE_RELEASE_BUTTON].reset();

    // Перекрытие заднего концевого крана
    if (getKeyState(KEY_0) && !isAlt())
    {
        if (isShift())
            anglecock_bp_bwd->open();
        else
            anglecock_bp_bwd->close();
    }

    // Перекрытие переднего концевого крана
    if (getKeyState(KEY_9) && !isAlt())
    {
        if (isShift())
            anglecock_bp_fwd->open();
        else
            anglecock_bp_fwd->close();
    }
}
