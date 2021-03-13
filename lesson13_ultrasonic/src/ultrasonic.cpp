#include <Arduino.h>

const int TrigPin = 2; 
const int EchoPin = 3;
float distance;

void setup()
{
    Serial.begin(9600);
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
}

void loop()
{
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    distance = pulseIn(EchoPin, HIGH) / 58.00;
    Serial.print("{\"d\":");
    Serial.print(distance);
    Serial.print(",\"a\":");
    Serial.print(0);
    Serial.println("}");
    delay(100);
}
