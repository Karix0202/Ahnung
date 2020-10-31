#include "private/StateManager.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

StateManager::StateManager(LiquidCrystal_I2C* _lcd, int _bReset, int _bHours, int _bMins, int _bOk, int _bSwitch)
{
    startState = new StartState(_lcd, &state, _bHours, _bMins, _bOk, &tStart, &tEnd, &tNow);
}

void StateManager::Setup()
{
    startState->Setup();
}

void StateManager::Loop()
{
    bResetState = digitalRead(bReset);
    if (bResetState)
    {
        Reset();
        delay(125);
    }

    switch (state)
    {
    case 0:
        startState->Loop();
        break;
    
    default:
        break;
    }
}

void StateManager::Reset()
{
    tStart.Reset();
    tEnd.Reset();
    tNow.Reset();
    state = 0;
    startState->ResetState();
}