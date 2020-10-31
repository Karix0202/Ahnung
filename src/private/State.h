#ifndef STATE_H
#define STATE_H

#include <LiquidCrystal_I2C.h>
/**
 * Base class to states
**/
class State
{
public:
    virtual void Setup();
    virtual void Loop();

    State(LiquidCrystal_I2C* _lcd)
    {
        lcd = _lcd;
    }
protected:
    LiquidCrystal_I2C* lcd;
};

#endif