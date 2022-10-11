#include    "ep1m.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::stepAuxMachines(double t, double dt)
{
    // Обрабатываем ПЧФ
    bool is_freq_conv_On = tumblers_panel->getTumblerState(TUMBLER_AUX_MACHINES);

    freq_phase_conv->setInputVoltage(trac_trans->getControlPowerVoltage() *
                                     static_cast<double>(is_freq_conv_On));

    freq_phase_conv->step(t, dt);

    // Управляем контакторами МВ11
    km7->setVoltage(Ucc * static_cast<double>(msud->getOutputData().mv_freq_low[MV1] &&
                                              tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN1)));
    km7->step(t, dt);

    km11->setVoltage(Ucc * static_cast<double>(msud->getOutputData().mv_freq_norm[MV1] &&
                                               tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN1)));
    km11->step(t, dt);

    // Цепь напряжения на МВ11
    bool is_MV11_on = tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN1) &&
            ( km7->getContactState(0) || km11->getContactState(0));

    motor_fan[MV1]->setU_power(freq_phase_conv->getOutputVoltage() *
                               static_cast<double>(is_MV11_on));

    // Частота питания МВ11
    double freq_MV11 = freq_phase_conv->getFrequencyLow() * static_cast<double>(km7->getContactState(0)) +
            freq_phase_conv->getFrequencyNorm() * static_cast<double>(km11->getContactState(0));

    motor_fan[MV1]->setFreq(freq_MV11);
    motor_fan[MV1]->step(t, dt);

    // Управляем контакторами МВ12
    km8->setVoltage(Ucc * static_cast<double>(msud->getOutputData().mv_freq_low[MV2] &&
                                              tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN2)));
    km8->step(t, dt);

    km12->setVoltage(Ucc * static_cast<double>(msud->getOutputData().mv_freq_norm[MV2] &&
                                               tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN2)));
    km12->step(t, dt);

    // Цепь напряжения на МВ12
    bool is_MV12_on = tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN2) &&
            ( km8->getContactState(0) || km12->getContactState(0) );

    motor_fan[MV2]->setU_power(freq_phase_conv->getOutputVoltage() *
                               static_cast<double>(is_MV12_on));

    // Частота питания МВ11
    double freq_MV12 = freq_phase_conv->getFrequencyLow() * static_cast<double>(km8->getContactState(0)) +
            freq_phase_conv->getFrequencyNorm() * static_cast<double>(km12->getContactState(0));

    motor_fan[MV2]->setFreq(freq_MV12);
    motor_fan[MV2]->step(t, dt);

    // Управляем контакторами МВ13
    km9->setVoltage(Ucc * static_cast<double>(msud->getOutputData().mv_freq_low[MV3] &&
                                              tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN3)));
    km9->step(t, dt);

    km13->setVoltage(Ucc * static_cast<double>(msud->getOutputData().mv_freq_norm[MV3] &&
                                               tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN3)));
    km13->step(t, dt);

    // Цепь напряжения на МВ13
    bool is_MV13_on = tumblers_panel->getTumblerState(TUMBLER_MOTOR_FAN3) &&
            ( km9->getContactState(0) || km13->getContactState(0) );

    motor_fan[MV3]->setU_power(freq_phase_conv->getOutputVoltage() *
                               static_cast<double>(is_MV13_on));

    // Частота питания МВ13
    double freq_MV13 = freq_phase_conv->getFrequencyLow() * static_cast<double>(km9->getContactState(0)) +
            freq_phase_conv->getFrequencyNorm() * static_cast<double>(km13->getContactState(0));

    motor_fan[MV3]->setFreq(freq_MV13);
    motor_fan[MV3]->step(t, dt);
}
