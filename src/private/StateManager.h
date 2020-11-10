#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include "StartState.h"
#include "Time.h"
#include <Arduino.h>
#include "MainState.h"

class StateManager
{
private:
    /**
     * Number between 0 and 1
     * 0 means start state
     * 1 means main state
    **/
    int state = 0;

    Time tStart;
    Time tEnd;
    Time tNow;
    bool wasTimeSet = false;

    StartState* startState;
    MainState* mainState;

    int bReset;
    int bResetState = LOW;

    void Reset();

public:
    StateManager(LiquidCrystal_I2C* _lcd, int _bReset, int _bHours, int _bMins,
                 int _bOk, int _bSwitch);

    void Setup();
    void Loop();

    void StateUp();
    MainState* GetMainState();
};

#endif