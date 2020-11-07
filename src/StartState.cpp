#include "private/StartState.h"
#include <Arduino.h>
#include "private/Time.h"
#include <LiquidCrystal_I2C.h>
#include "private/State.h"
bool wasDis = false;
StartState::StartState(LiquidCrystal_I2C* _lcd, int* _managerState, int _bHours, int _bMins, 
               int _bOk, Time* _tStart, Time* _tEnd,
               Time* _tNow) : State(_lcd)
{
    managerState = _managerState;
    bHours = _bHours;
    bMins = _bMins;
    bOk = _bOk;
    tStart = _tStart;
    tEnd = _tEnd;
    tNow = _tNow;
}

void StartState::Setup()
{
    pinMode(bHours, INPUT);
    pinMode(bMins, INPUT);
    pinMode(bOk, INPUT);
    isDisplayed = false;
    Serial.begin(9600);
}

void StartState::Loop()
{
    bOkState = digitalRead(bOk);
    if (bOkState)
    {
        ownState++;
        lcd->clear();
        delay(125);
    }
    
    switch (ownState)
    {
    case 0:
        Display(tStart, "Start");
        SetTime(tStart);
        break;

    case 1:
        Display(tEnd, "Koniec");
        SetTime(tEnd);
        break;

    case 2:
        Display(tNow, "Czas teraz");
        SetTime(tNow);
        break;
    
    default:
        (*managerState)++;
        break;
    }
    
}

void StartState::Display(Time* time, String caption)
{
    lcd->home();
    lcd->print(caption);

    lcd->setCursor(11, 1);
    lcd->print(time->ToString());
}

void StartState::SetTime(Time* time)
{
    bHoursState = digitalRead(bHours);
    if (bHoursState)
    {
        time->AddHour();
        delay(125);
    }

    bMinsState = digitalRead(bMins);
    if (bMinsState)
    {
        time->AddMin();
        delay(125);
    }
}

void StartState::ResetState()
{
    lcd->clear();
    ownState = 0;
}