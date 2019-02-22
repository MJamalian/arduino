#include <arduino.h>
#include <LM35.h>
#include <Ultrasonic.h>

#define TRIG_PIN 12
#define ECHO_PIN 13

LM35 temp(A0);
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Serial.print(temp.cel());
    // Serial.print(" ");
    Serial.print(ultrasonic.Ranging(CM));
    Serial.print(" ");

    delay(1000);
}
