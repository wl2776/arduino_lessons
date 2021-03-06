#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Bounce2.h>

const uint8_t DHTPIN = 8;
const uint8_t DHTTYPE = DHT11;

const int buttonPin = 2;     // номер входа, подключенный к кнопке
const int ledPin =  13;      // номер выхода светодиода

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01);
Bounce2::Button button = Bounce2::Button();

bool is_fahrenheit = false;
unsigned long last_millis;

void setup() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    button.attach(buttonPin, INPUT); // USE EXTERNAL PULL-UP
    // DEBOUNCE INTERVAL IN MILLISECONDS
    button.interval(5);

    // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
    button.setPressedState(LOW); 

    lcd.begin(16, 2);
    lcd.backlight();
    dht.begin();
    Serial.begin(9600);
    delay(2000);
    last_millis = millis();
}

void loop() {
    if (millis() - last_millis > 200) {
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
        last_millis = millis();
    }

    button.update();
    if (button.pressed()) {
        is_fahrenheit = !is_fahrenheit;
    }
    int button_state = digitalRead(buttonPin);
    digitalWrite(ledPin, button_state);
}
