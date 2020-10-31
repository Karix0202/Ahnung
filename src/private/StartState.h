#ifndef START_STATE_H
#define START_STATE_H

#include "State.h"
#include <LiquidCrystal_I2C.h>
#include "Time.h"
#include <Arduino.h>

class StartState : public State
{
public:
    void Setup() override;
    void Loop() override;

    StartState(LiquidCrystal_I2C* _lcd, int* _managerState, int _bHours, int _bMins, int _bOk);
private:
    /**
     * Number between 0 and 2
     * 0 set up start time
     * 1 set up end time
     * 2 set up current time
    **/
    int ownState = 0;

    int* managerState;

    int bHours;
    bool bHoursState = LOW;

    int bMins;
    bool bMinutesState = LOW;

    int bOk;
    bool bOkState = LOW;

    Time tStart;
    Time tEnd;
    Time tNow;

    void Reset();
    void Display(Time hour, String caption);
};

#endif