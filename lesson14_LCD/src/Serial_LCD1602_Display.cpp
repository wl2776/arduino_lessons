#include <Arduino.h>
#include <LiquidTWI2.h>
#if DEBUG
#include <avr8-stub.h>
#endif

LiquidTWI2 lcd(0x27);

void setup()
{
#if DEBUG
    debug_init();
#endif
    lcd.setMCPType(LTI_TYPE_MCP23008);
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

  lcd.setBacklight(HIGH);
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);    
}
