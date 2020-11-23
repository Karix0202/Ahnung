#include "private/StateManager.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "private/MainState.h"

StateManager::StateManager(LiquidCrystal_I2C* _lcd, int _bReset, int _bHours, int _bMins, int _bOk, int _bSwitch, int _relay)
{
    startState = new StartState(_lcd, &state, _bHours, _bMins, _bOk, &tStart, &tEnd, &tNow);
    mainState = new MainState(_lcd, _bSwitch, _relay);
    bReset = _bReset;
}

void StateManager::Setup()
{
    startState->Setup();
    mainState->Setup();
    pinMode(bReset, INPUT);
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

    case 1:
        if (!wasTimeSet)
        {
            mainState->SetTime(&tStart, &tEnd, &tNow);
            wasTimeSet = !wasTimeSet;
        }
        mainState->Loop();
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
    wasTimeSet = false;
    startState->ResetState();
    mainState->Reset();
}

void StateManager::StateUp()
{
    state++;
}

MainState* StateManager::GetMainState()
{
    return mainState;
}