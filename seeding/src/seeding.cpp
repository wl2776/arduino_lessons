/* wiring

A0 --- middle potentiometer
A4 --- LCD SDA
A5 --- LCD SCL
D2 --- button
D8 --- DHT11

*/

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Bounce2.h>

const uint8_t DHT_pin = 8;
const uint8_t DHTTYPE = DHT11;
const bool is_fahrenheit = false;

const int AD_pin = A0 ;

const int button_pin = 2;     // номер входа, подключенный к кнопке
const int led_pin =  13;      // номер выхода светодиода

DHT dht(DHT_pin, DHTTYPE);
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01);
Bounce2::Button button = Bounce2::Button();

unsigned long DHT_last_millis, AD_last_millis, AD_activity_millis;
bool reading_pot = false;
int temperature_threshold = 25;
int prev_value = 0;


void setup() {
    pinMode(AD_pin, INPUT);
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);

    lcd.begin(16, 2);
    lcd.backlight();
    dht.begin();
    Serial.begin(9600);
    delay(2000);

    button.attach(button_pin, INPUT_PULLUP);
    button.interval(5);
    button.setPressedState(HIGH); 

    DHT_last_millis = AD_last_millis = millis();
}

void loop() {
    if (!reading_pot && millis() - DHT_last_millis > 200) {
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
        lcd.print(String("T: ") + t + String("'C (") + temperature_threshold + String(")"));

        lcd.setCursor(0, 1);
        lcd.print("Hum: ");
        lcd.print(h);
        lcd.print("%");
        DHT_last_millis = millis();
    }

    if (reading_pot && millis() - AD_last_millis > 200) {
        int value = analogRead(AD_pin);
        int temperature = map(value, 0, 1023, 20, 40);

        lcd.setCursor(0, 0);
        lcd.print(String("Set temp: ") + temperature + String("\'C"));

        AD_last_millis = millis();
        if (prev_value != value) {
            prev_value = value;
            AD_activity_millis = millis();
            temperature_threshold = temperature;
        }
        if (millis() - AD_activity_millis > 30000) {
            reading_pot = false;
            lcd.clear();
        }
    }

    button.update();
    if (button.pressed()) {
        reading_pot = !reading_pot;
        lcd.clear();
        if (reading_pot) {
            AD_activity_millis = millis();
        }
    }
    int button_state = digitalRead(button_pin);
    digitalWrite(led_pin, button_state);
 }
