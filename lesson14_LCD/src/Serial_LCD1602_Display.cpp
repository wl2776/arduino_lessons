#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define BACKLIGHT_PIN   15
//LiquidCrystal_I2C lcd(0x27, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27);

// Create a set of new characters
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
    lcd.begin(16,2);
    //int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
//    for ( int i = 0; i < charBitmapSize; i++ )
    //{
        //lcd.createChar ( i, (uint8_t *)charBitmap[i] );
//    }

    lcd.home();
    lcd.print("H");
    //lcd.setCursor( 0, 1 );        // go to the next line
    //lcd.print(" FORUM - fm   ");
}

void loop()
{
  ///lcd.home ();
    //lcd.print("H");
    //// Do a little animation by writing to the same location
    //for ( int i = 0; i < 2; i++ )
    //{
        //for ( int j = 0; j < 16; j++ )
        //{
            //lcd.print (1);
        //}
        //lcd.setCursor ( 0, i );
    //}
//    delay (200);
}


