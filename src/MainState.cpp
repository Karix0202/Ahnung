#include "private/MainState.h"
#include "private/State.h"
#include <Arduino.h>

MainState::MainState(LiquidCrystal_I2C* _lcd, int _bSwitch, int _relay) : State(_lcd)
{
   lcd = _lcd;
   bSwitch = _bSwitch;
   relay = _relay;
}

void MainState::Setup()
{
    pinMode(bSwitch, INPUT);
    pinMode(relay, OUTPUT);
    rtc.begin();
    ClearAlarms();
}

void MainState::Loop()
{
    // turn on relay
    if (rtc.isAlarm1())
    {
        isOn = true;
        SwitchRelay();
        DisplayOnLcd();
        isOnLast = true;
    }

    // turn off relay
    if (rtc.isAlarm2())
    {
        isOn = false;
        SwitchRelay();
        DisplayOnLcd();
        isOnLast = false;
    }
    
    ButtonSwitch();
    DisplayOnLcd();
}

void MainState::ButtonSwitch()
{
    bSwitchState = digitalRead(bSwitch);
    if (bSwitchState) 
    {
        isOnLast = isOn;
        isOn = !isOn;
        SwitchRelay();
        delay(150);
    }
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

    // dont care about date. Hour, min, sec are the only important variables
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

void MainState::SwitchRelay()
{
    digitalWrite(relay, isOn);
}