#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include "State.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "Time.h"
#include <DS3231.h>

class MainState : public State
{
public:
    void Setup() override;
    void Loop() override;

    MainState(LiquidCrystal_I2C* _lcd, int _bSwitch);

private:
    int bSwitch; // switch pin, is ON or OFF
    int bSwitchState = LOW;

    int relay; // 250V/10A relay pin 

    bool isOn = false;
    void Switch();

    void Reset();

    void DisplayOnLcd();
    
    DS3231 rtc;

    void SetTime(Time* _tStart, Time* _tEnd, Time* _tNow);

    Time* tStart;
    Time* tEnd;
};

#endif