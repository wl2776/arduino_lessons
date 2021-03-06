#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#if DEBUG
#include <avr8-stub.h>
#endif

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
#if DEBUG
    debug_init();
#endif
    lcd.init();                      // initialize the lcd
    lcd.backlight();
    lcd.setCursor(2, 0);  //go to start of 2nd line
    lcd.print("Hello, world!");
    lcd.setCursor(4, 1);  //go to start of 2nd line
    lcd.print("Wl2776");
}

void loop()
{
}
