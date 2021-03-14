/* wiring

A0 --- middle potentiometer
A4 --- LCD SDA
A5 --- LCD SCL
D8 --- DHT11

*/

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const uint8_t DHTPIN = 8;
const uint8_t DHTTYPE = DHT11;
const bool is_fahrenheit = false;

const int ADPIN = A0 ;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01);

unsigned long DHT_last_millis, AD_last_millis;

void setup() {
    pinMode(ADPIN, INPUT);
    lcd.begin(16, 2);
    lcd.backlight();
    dht.begin();
    Serial.begin(9600);
    delay(2000);
    DHT_last_millis = AD_last_millis = millis();
}

void loop() {
    if (millis() - DHT_last_millis > 200) {
        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        float h = dht.readHumidity();
        float t = dht.readTemperature(is_fahrenheit);

        if (isnan(h) || isnan(t))
        {
            Serial.println(F("Failed to read from DHT sensor!"));
            lcd.setCursor(13, 1);
            lcd.print('.');
        }

        lcd.setCursor(0, 0);
        lcd.print(String("Temp: ") + t + ((is_fahrenheit) ? String("F ") : String("'C")));

        lcd.setCursor(0, 1);
        lcd.print("Hum: ");
        lcd.print(h);
        lcd.print("%");
        DHT_last_millis = millis();
    }

    if (AD_last_millis - millis() > 1000) {
        int value = analogRead(ADPIN);
        float voltage = (float)value / 1023.0f * 5;
        Serial.print("get ad pin value "); Serial.println(value);
        Serial.print("voltage = "); Serial.println(voltage);
        AD_last_millis = millis();
    }
}
