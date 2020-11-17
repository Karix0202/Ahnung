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
    ClearAlarms();
    Serial.begin(9600);
}

void MainState::Loop()
{
    // turn on relay
    if (rtc.isAlarm1()) isOn = true;
    // turn off relay
    if (rtc.isAlarm2()) isOn = false;
    
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
    ClearAlarms();
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

    ClearAlarms();

    /***
     * Alarm1 - when to set isOn to true
     * Alarm2 - when to set isOn to false
     ***/
    rtc.setAlarm1(0, tStart->GetHours(), tStart->GetMins(), 0, DS3231_MATCH_H_M_S);
    rtc.setAlarm2(0, tEnd->GetHours(), tEnd->GetMins(), DS3231_MATCH_H_M);
}

void MainState::ClearAlarms()
{
    rtc.armAlarm1(false);
    rtc.armAlarm2(false);

    rtc.clearAlarm1();
    rtc.clearAlarm2();
}