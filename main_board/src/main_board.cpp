#include <arduino.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

AltSoftSerial myserial;
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);

String incomingString;

union TEMP
{
  float f;
  byte b[4];
};

TEMP float_in;

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
            lcd.print("temp: ");
            lcd.print(incomingString.substring(0, M_position));
            lcd.setCursor(0, 2);
            lcd.print("dist: ");
            lcd.print(incomingString.substring(M_position + 1));
            incomingString = "";
        }
        else{
            incomingString += incomingByte;
        }
    }
    if(myserial.available()){
        myserial.readBytes(float_in.b, 4);
        lcd.setCursor(0, 0);
        lcd.print("UT_out: ");
        lcd.print(float_in.f);
    }
}
