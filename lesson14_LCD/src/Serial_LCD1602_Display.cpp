#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    lcd.init();                      // initialize the lcd
    lcd.backlight();
    lcd.setCursor(2, 0);  //go to start of 2nd line
    lcd.print("Hello, world!");
    lcd.setCursor(4, 1);  //go to start of 2nd line
    lcd.print("Wl2776");

    /*Serial.begin (9600); // Leonardo: wait for serial port to connect
    while (!Serial) { }
    Serial.println ();
    Serial.println ("I2C scanner. Scanning ...");
    byte count = 0;
    Wire.begin();
    for (byte i = 8; i < 120; i++) {
        Wire.beginTransmission (i);
        if (Wire.endTransmission () == 0) {
            Serial.print ("Found address: ");
            Serial.print (i, DEC);
            Serial.print (" (0x");
            Serial.print (i, HEX);
            Serial.println (")");
            count++;
            delay (1); // maybe unneeded?
        } // end of good response
    } // end of for loop
    Serial.println ("Done.");
    Serial.print ("Found ");
    Serial.print (count, DEC);
    Serial.println (" device(s).");*/
    Serial.begin(9600);
}

void loop()
{
}
