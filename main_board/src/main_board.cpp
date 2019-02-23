#include <arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial myserial(2,3);
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);

String incomingString, incomingString2;

void setup(){
    Serial.begin(9600);
    myserial.begin(9600);
    lcd.begin(16, 4);
}


void loop(){
    if(Serial.available()){
        char incomingByte = (char)Serial.read();
        if (incomingByte == '\0'){
            int M_position = incomingString.indexOf('M');
            lcd.setCursor(0, 1);
            lcd.print(incomingString.substring(0, M_position));
            lcd.setCursor(0, 2);
            lcd.print(incomingString.substring(M_position + 1));
            incomingString = "";
        }
        else{
            incomingString += incomingByte;
        }
    }
    if(myserial.available()){
        char incomingByte2 = (char)myserial.read();
        if (incomingByte2 == '\0'){
            lcd.setCursor(0, 0);
            lcd.print("hello");
            incomingString2 = "";
        }
        else{
            incomingString2 += incomingByte2;
        }
    }
}
