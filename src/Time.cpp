#include "private/Time.h"

void Time::AddMin()
{
    if (mins + 1 == 60)
    {
        AddHour();
        mins = 0;
    }
    else
    {
        mins++;
    }
}

void Time::AddHour()
{
    if (hours + 1 == 25)
    {
        hours = 0;
    }
    else
    {
        hours++;
    }
}

void Time::Reset()
{
    mins = 0;
    hours = 0;
}