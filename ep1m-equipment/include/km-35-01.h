#ifndef     KM_35_01_H
#define     KM_35_01_H

#include    "device.h"

//------------------------------------------------------------------------------
//  Контроллер машиниста электровоза ЭП1м(п)
//------------------------------------------------------------------------------
class TracController : public Device
{
public:

    TracController(QObject *parent = Q_NULLPTR);

    ~TracController();

    bool isZero() const
    {
        return mode_pos == 0;
    }

    bool isTraction() const
    {
        return mode_pos == 1;
    }

    bool isBrake()
    {
        return mode_pos == -1;
    }

    void setFwdKeyState(bool key_state) { fwd_key_state = key_state; }

    void setBwdKeyState(bool key_state) { bwd_key_state = key_state; }

    float getReversHandlePos() const { return static_cast<float>(revers_pos); }

private:

    /// Позиция, определяющая состояние схемы
    /// (0 - схема разобрана, 1 - подготовка тяги, 2 - подготовка рекуперации)
    int mode_pos;

    bool fwd_key_state;
    bool old_fwd_key_state;

    bool bwd_key_state;
    bool old_bwd_key_state;

    int revers_pos;

    QString reversSoundName;

    bool old_traction_key;

    bool old_brake_key;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;

    void processDiscretePositions(bool key_state, bool old_key_state, int dir);
};

#endif // KM_35_01_H
