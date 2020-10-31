#include "private/Hour.h"

void Hour::AddMin()
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

void Hour::AddHour()
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

void Hour::Reset()
{
    mins = 0;
    hours = 0;
}