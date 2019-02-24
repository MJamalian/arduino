#include <arduino.h>
#include <LM35.h>
#include <Ultrasonic.h>

#define TRIG_PIN 12
#define ECHO_PIN 13

LM35 temp(A0);
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

String inData ;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    inData = String(temp.cel());
    inData += 'M';
    inData += String(ultrasonic.Ranging(CM));
    inData += '\0';
    Serial.print(inData);
    
}
