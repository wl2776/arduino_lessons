#include <Arduino.h>

#define RGB_RED 11
#define RGB_GREEN 10
#define RGB_BLUE 9

void setup()
{
    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);
}

void loop()
{
    int color_change_delay = 10;
    for (int i=255; i>0 ;i--)
    {
        analogWrite(RGB_RED, i);
        analogWrite(RGB_GREEN, 255);
        analogWrite(RGB_BLUE, 255);
        delay(color_change_delay);
    }
    delay(500);
    //turn the RGB LED red smoth
    for (int i=255; i>0; i--)
    {
        analogWrite(RGB_RED, 255);
        analogWrite(RGB_GREEN, i);
        analogWrite(RGB_BLUE, 255);
        delay(color_change_delay);
    }
    delay(500);
    //turn the RGB LED green smoth
    for (int i=255; i>0; i--)
    {
        analogWrite(RGB_RED, 255);
        analogWrite(RGB_GREEN, 255);
        analogWrite(RGB_BLUE, i);
        delay(color_change_delay);
    }
    delay(500);
    //turn the RGB LED blue smoth
}

