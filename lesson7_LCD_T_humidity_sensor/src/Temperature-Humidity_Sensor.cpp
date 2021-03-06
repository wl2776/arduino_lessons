/***********************************************************************
 *       __                                                          _
 *      / /        _____  __    __  _          _   (_)   ________   | |
 *     / /____   / _____) \ \  / / | |   __   | |  | |  (  ______)  | |_____
 *    / / ___/  | |_____   \ \/ /  | |  /  \  | |  | |  | |______   |  ___  |
 *   / /\ \     | |_____|   \  /   | | / /\ \ | |  | |  (_______ )  | |   | |
 *  / /  \ \__  | |_____    / /    | |/ /  \ \| |  | |   ______| |  | |   | |
 * /_/    \___\  \______)  /_/      \__/    \__/   |_|  (________)  |_|   |_|
 *   
 *                                        
 * KeyWay Tech firmware
 *
 * Copyright (C) 2015-2020 
 *
 * This program is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, in version 3.
 * learn more you can see <http://www.gnu.org/licenses/>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. 
 *
 *
 * [Title]    Temperature-Humidity Sensor
 * [Diagram] 
 *         Arduino PIN 5   ===================  lcd1602 pin 3
 *         Arduino PIN 4   ===================  lcd1602 pin 4
 *         Arduino PIN 8   ===================  Temperature-Humidity Sensor Dout
 */
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "dht11.h"

#define  DHT11PIN   8
dht11 DHT11;

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01);

void setup() {
    pinMode(DHT11PIN, INPUT);
    lcd.begin(16, 2);
    lcd.backlight();
}

void loop() {
    int chk = DHT11.read(DHT11PIN);
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print((float)DHT11.temperature);
    lcd.print("'C");

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print("Hum: ");
    lcd.print((float)DHT11.humidity, 2);
    lcd.print("%");
    delay(200);
}
