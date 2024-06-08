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
    if (getKeyState(KEY_Z))
        tumblers[BUTTON_RB].set();
    else
        tumblers[BUTTON_RB].reset();    

    // Если активна РБС на внешнем пульте
    if (control_signals.analogSignal[CS_RBS].is_active)
    {
        // реагируем на состояние РБС на внешнем пульте
        if (static_cast<bool>(control_signals.analogSignal[CS_RBS].cur_value))
            tumblers[BUTTON_RBS].set();
        else
            tumblers[BUTTON_RBS].reset();
    }
    else // иначе
    {
        // обрабатываем клавиши
        if (getKeyState(KEY_M))
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
}
