#include <Arduino.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include "private/StateManager.h"

#define B_HOURS 2
#define B_MINS 3
#define B_OK 4
#define B_RESET 5

LiquidCrystal_I2C* lcd;
StateManager stateManager = new StateManager(); 

void setup() 
{
	lcd->init();
	lcd->backlight();
}

void loop() 
{

}