#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#if DEBUG
#include <avr8-stub.h>
#endif

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01); //, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void setup()
{
#if DEBUG
    debug_init();
#endif
    lcd.begin(16, 2);

    lcd.setCursor(2, 0);  //go to start of 2nd line
    lcd.print("Hello, world!");
    lcd.setCursor(4, 1);  //go to start of 2nd line
    lcd.print("Wl2776");
}

void loop()
{
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);

  lcd.backlight();
  delay(1000);
  lcd.noBacklight();
  delay(1000);    
}
