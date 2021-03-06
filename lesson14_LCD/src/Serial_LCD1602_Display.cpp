#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#if DEBUG
#include <avr8-stub.h>
#endif

#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x27, 6, 5, 4);

// Creat a set of new characters
const uint8_t charBitmap[][8] = {
   { 0xc, 0x12, 0x12, 0xc, 0, 0, 0, 0 },
   { 0x6, 0x9, 0x9, 0x6, 0, 0, 0, 0 },
   { 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0, 0x0 },
   { 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0, 0x0 },
   { 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0x0 },
   { 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0x0 },
   { 0x0, 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0 },
   { 0x0, 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0x0 }
};

void setup()
{
#if DEBUG
    debug_init();
#endif
    int charBitmapSize = (sizeof(charBitmap) / sizeof(charBitmap[0]));

    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, HIGH);

    lcd.begin(16, 2); // initialize the lcd

    // for (int i = 0; i < charBitmapSize; i++)
    // {
    //     lcd.createChar(i, (uint8_t *)charBitmap[i]);
    // }

    lcd.home(); // go home
    lcd.print("Hello, ARDUINO ");
    lcd.setCursor(0, 1); // go to the next line
    lcd.print(" FORUM - fm   ");
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
