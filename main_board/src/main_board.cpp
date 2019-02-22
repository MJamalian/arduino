#include <arduino.h>
#include <LiquidCrystal.h>
int incomingByte;
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);
void setup(){
    Serial.begin(9600);
    lcd.begin(20, 4);
    lcd.print("hello world!");
}


void loop(){
    if(Serial.available()>0){
        incomingByte = Serial.read();

        Serial.print("I received: ");
        Serial.println(incomingByte);
    }


}
