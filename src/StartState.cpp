#include "private/StartState.h"
#include <Arduino.h>
#include "private/Time.h"
#include <LiquidCrystal_I2C.h>
#include "private/State.h"

StartState::StartState(LiquidCrystal_I2C* _lcd, int* _managerState, int _bHours, int _bMins, int _bOk) : State(_lcd)
{
    managerState = _managerState;
    bHours = bHours;
    bMins = _bMins;
    bOk = _bOk;
}

void StartState::Setup()
{
    pinMode(bHours, INPUT);
    pinMode(bMins, INPUT);
    pinMode(bOk, INPUT);
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

void StartState::Reset()
{
    lcd->clear();

    tStart.Reset();
    tEnd.Reset();
    tNow.Reset();

    ownState = 0;
}

void StartState::Display(Time time, String caption)
{
    lcd->home();
    lcd->print(caption);

    lcd->setCursor(11, 2);
    lcd->print(time.ToString());
}

void StartState::SetTime(Time& time)
{
    bHoursState = digitalRead(bHours);
    if (bHoursState)
    {
        time.AddHour();
        delay(125);
    }

    bMinsState = digitalRead(bMins);
    if (bMinsState)
    {
        time.AddMin();
        delay(125);
    }
}