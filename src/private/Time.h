#ifndef HOUR_H
#define HOUR_H

#include <Arduino.h>

class Time
{
private:
    int hours = 0;
    int mins = 0;
public:
    void AddMin();
    void AddHour();
    void Reset();
    String ToString();
};

#endif