#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include "StartState.h"

class StateManager
{
private:
    /**
     * Number between 0 and 1
     * 0 means start state
     * 1 means main state
    **/
    int state = 0;

    StartState* startState;
public:
    StateManager(LiquidCrystal_I2C* _lcd, int _bHours, int _bMins, int _bOk);

    void Setup();
    void Loop();
};

#endif