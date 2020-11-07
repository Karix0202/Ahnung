#ifndef HOUR_H
#define HOUR_H

#include <Arduino.h>
#include <DS3231.h>

class Time
{
private:
    int hours = 0;
    int mins = 0;
    int seconds = 0;
public:
    void AddMin();
    void AddHour();
    void Reset();
    String ToString();

    static String RtcDateTimeToString(RTCDateTime rtcDateTime);

    int GetHours() { return hours; };
    int GetMins() { return mins; };
    int GetSeconds() { return seconds; };
};

#endif