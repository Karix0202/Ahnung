#include <Arduino.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include "private/StateManager.h"

#define B_HOURS 7
#define B_MINS 3
#define B_OK 4
#define B_RESET 5

LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27, 16, 2);
StateManager* stateManager = new StateManager(lcd, B_RESET, B_HOURS, B_MINS, B_OK, B_OK);

void setup()
{
	lcd->init();
	lcd->backlight();
	stateManager->Setup();
}

void loop() 
{
	stateManager->Loop();
}