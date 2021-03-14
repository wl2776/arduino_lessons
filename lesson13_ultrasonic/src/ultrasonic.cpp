/* wiring: 

Arduino D2 ---- Ultrasonic Trig
Arduino D3 ---- Ultrasonic Echo
Arduino D13 --- Servo

*/

#include <Arduino.h>
#include <Servo.h>


const int TrigPin = 2; 
const int EchoPin = 3;
const int servo_pin = 13;
float distance;

Servo servo;

void setup()
{
    Serial.begin(115200);
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    pinMode(servo_pin, OUTPUT);
    servo.attach(servo_pin);
}

int angle = 0;
int angle_increment = 1;
void loop()
{
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    distance = pulseIn(EchoPin, HIGH) / 58.00;
    int r = servo.read();
    Serial.print("{\"d\":");
    Serial.print(distance);
    Serial.print(",\"a\":");
    Serial.print(r);
    Serial.println("}");
    servo.write(angle);
    angle += angle_increment;
    if (angle >= 170) {
        angle_increment = -1;
    } else if (angle <= 10) {
        angle_increment = 1;
    }
    delay(10);
}
