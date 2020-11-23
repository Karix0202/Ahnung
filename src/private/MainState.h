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

    MainState(LiquidCrystal_I2C* _lcd, int _bSwitch, int _relay);

    void SetTime(Time* _tStart, Time* _tEnd, Time* _tNow);
    void Reset();

private:
    int bSwitch; // switch pin, is ON or OFF
    int bSwitchState = LOW;
    void SwitchRelay();

    int relay; // 250V/10A relay pin
    int relayState = LOW;

    bool isOn = false;
    bool isOnLast = false;
    void ButtonSwitch();

    void ClearAlarms();

    void DisplayOnLcd();
    
    DS3231 rtc;

    Time* tStart;
    Time* tEnd;
};

#endif