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
#include <DHT.h>

#define DHTPIN   8
#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01);

void setup() {
    lcd.begin(16, 2);
    lcd.backlight();
    dht.begin();
    delay(2000);
}

void loop() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
        lcd.setCursor(13, 1);
        lcd.print('.');
    }

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("'C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(h);
    lcd.print("%");

    delay(2000);
}
