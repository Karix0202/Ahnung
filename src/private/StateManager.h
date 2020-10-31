#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <LiquidCrystal_I2C.h>

class StateManager
{
private:
    /**
     * Number between 0 and 1
     * 0 means start state
     * 1 means main state
    **/
    int state = 0; 
public:
    StateManager(LiquidCrystal_I2C* _lcd);

    void Setup();
    void Loop();
};

#endif