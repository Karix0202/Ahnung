#include "private/StateManager.h"
#include <LiquidCrystal_I2C.h>

StateManager::StateManager(LiquidCrystal_I2C* _lcd, int _bHours, int _bMins, int _bOk)
{
    startState = new StartState(_lcd, &state, _bHours, _bMins, _bOk);
}

void StateManager::Setup()
{
    startState->Setup();
}

void StateManager::Loop()
{
    switch (state)
    {
    case 0:
        startState->Loop();
        break;
    
    default:
        break;
    }
}