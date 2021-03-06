#include "private/Time.h"
#include <Arduino.h>

void Time::AddMin()
{
    if (mins + 1 == 60) mins = 0;
    else mins++;
}

void Time::AddHour()
{
    if (hours + 1 == 25) hours = 0;
    else hours++;
}

void Time::Reset()
{
    mins = 0;
    hours = 0;
}

String Time::ToString()
{
    String sMins = (mins < 10) ? "0" + String(mins) : String(mins);
    String sHours = (hours < 10) ? "0" + String(hours) : String(hours);

    return sHours + ":" + sMins;
}
String Time::RtcDateTimeToString(RTCDateTime rtcDateTime) 
{
    String sMins = (rtcDateTime.minute < 10) ? "0" + String(rtcDateTime.minute) : String(rtcDateTime.minute);
    String sHours = (rtcDateTime.hour < 10) ? "0" + String(rtcDateTime.hour) : String(rtcDateTime.hour);

    return sHours + ":" + sMins;
}