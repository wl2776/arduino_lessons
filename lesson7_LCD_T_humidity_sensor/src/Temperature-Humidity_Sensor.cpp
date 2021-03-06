#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const uint8_t DHTPIN = 8;
const uint8_t DHTTYPE = DHT11;
bool is_fahrenheit = false;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01);

void setup() {
    lcd.begin(16, 2);
    lcd.backlight();
    dht.begin();
    Serial.begin(9600);
    delay(2000);
}

void loop() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature(is_fahrenheit);

    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        lcd.setCursor(13, 1);
        lcd.print('.');
    }

    lcd.setCursor(0, 0);
    lcd.print(String("Temp: ") + t + String("'C"));

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(h);
    lcd.print("%");

    delay(200);
}
