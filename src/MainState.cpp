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
   rtc.begin();
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
        isOnLast = isOn;
        isOn = !isOn;
        delay(150);
    }
    DisplayOnLcd();
}

void MainState::Reset()
{
    isOn = false;
    isOnLast = false;
}

void MainState::DisplayOnLcd()
{
    lcd->home();
    if (isOn != isOnLast)
    {
        lcd->clear();
        isOnLast = isOn;
    } 
    String sIsOn = (isOn) ? "ON" : "OFF";
    lcd->print("Stan: " + sIsOn);
    lcd->setCursor(0, 1);
    RTCDateTime now = rtc.getDateTime();
    lcd->print(Time::RtcDateTimeToString(now));
}

void MainState::SetTime(Time* _tStart, Time* _tEnd, Time* _tNow)
{
    tStart = _tStart;
    tEnd = _tEnd;

    // dont care about date so i set it up to todays, hour, min, sec are the only important variables
    rtc.setDateTime(2020, 11, 5, _tNow->GetHours(), _tNow->GetMins(), _tNow->GetSeconds());     
}