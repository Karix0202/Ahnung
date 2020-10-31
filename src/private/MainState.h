#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include "State.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "Time.h"

class MainState : public State
{
public:
    void Setup() override;
    void Loop() override;

    MainState(LiquidCrystal_I2C* _lcd, int _bSwitch);

private:
    int bSwitch;
    int bSwitchState = LOW;
};

#endif