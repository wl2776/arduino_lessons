#include <Arduino.h>

const int buttonPin = 2;     // номер входа, подключенный к кнопке
const int ledPin =  13;      // номер выхода светодиода

const int global_start_pin = 4; // номера пинов, подключенных к цепочке светодиодов
const int global_end_pin = 11;

const int delay_ms = 100;
int buttonState = 0;

volatile int increment = 1;

int pin = global_start_pin;
unsigned long lastUpdatedMillis = 0;

void flip_direction() {
// Попытка программно обработать дребезг кнопки
// Как сказано в http://codius.ru/articles/Arduino_Дребезг_программное_и_аппаратное_устранение,
// если обрабатываем кнопки в прерывании, то программно обработать дребезг нельзя.
// Только аппаратно, либо конденсатором, либо триггером Шмидта
    static unsigned long prev_trigger = 0;
    if(millis() - prev_trigger > 50) {
        increment = -increment;
        prev_trigger = millis();
    }
}

void next_pin() {
    pin += increment;
    if (pin < global_start_pin) {
        pin = global_end_pin;
    } else if (pin > global_end_pin) {
        pin = global_start_pin;
    }
}

void setup() {
    for(int i = global_start_pin; i <= global_end_pin; ++i) {
        pinMode(i, OUTPUT);
    }
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), flip_direction, RISING);
    lastUpdatedMillis = millis();
    Serial.begin(9600);
}

void loop()
{
    //Serial.println(millis());
    if (millis() - lastUpdatedMillis > delay_ms) {
        digitalWrite(pin, 1);
        next_pin();
        digitalWrite(pin, 0);
        lastUpdatedMillis = millis();
    }

    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }
}

