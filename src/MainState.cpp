#include "private/MainState.h"
#include "private/State.h"
#include <Arduino.h>

MainState::MainState(LiquidCrystal_I2C* _lcd, int _bSwitch) : State(_lcd)
{
   lcd = _lcd;
   bSwitch = _bSwitch; 
}

void MainState::Setup()
{
    pinMode(bSwitch, INPUT);
}

void MainState::Loop()
{
    Switch();    
    DisplayOnLcd();
}

void MainState::Switch()
{
    bSwitchState = digitalRead(bSwitch);
    if (bSwitchState) 
    {
        isOn = !isOn;
        delay(125);
    }
}

void MainState::Reset()
{
    isOn = false;
}

void MainState::DisplayOnLcd()
{
   lcd->home();
   lcd->print("Stan: " + (isOn) ? "On" : "Off");
}