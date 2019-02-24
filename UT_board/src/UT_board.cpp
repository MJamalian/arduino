#include <arduino.h>
#include <wire.h>

#define X0_address 0xa
#define X1_address 0xb
#define X2_address 0xc
#define X3_address 0xd
#define Y0_address 0x28
#define Y1_address 0x29
#define Y2_address 0x2a
#define Y3_address 0x2b
#define power_reg 0x0

uint8_t UT_address = 110;
byte x0, x1, x2, x3, y0, y1, y2, y3;
String inData;

byte i2c_readRegisterByte (uint8_t deviceAddress, uint8_t registerAddress) {
    byte registerData;
    Wire.beginTransmission(deviceAddress);
    Wire.write(registerAddress);
    Wire.endTransmission();
    Wire.requestFrom(deviceAddress,  1);
    registerData = Wire.read();
    return registerData;
}

union TEMP
{
  float f;
  byte b[4];
};

TEMP sigma;

void setup(){
    Serial.begin(9600);
    Wire.begin();
    delay(100);
    Wire.beginTransmission(UT_address);
    Wire.write(power_reg);
    Wire.write(1);
    Wire.endTransmission();
    sigma.f = 0;
}

void loop(){

    TEMP temp_x;
    TEMP temp_y;


    temp_x.b[0] = i2c_readRegisterByte(UT_address, X0_address);
    temp_x.b[1] = i2c_readRegisterByte(UT_address, X1_address);
    temp_x.b[2] = i2c_readRegisterByte(UT_address, X2_address);
    temp_x.b[3] = i2c_readRegisterByte(UT_address, X3_address);
    temp_y.b[0] = i2c_readRegisterByte(UT_address, Y0_address);
    temp_y.b[1] = i2c_readRegisterByte(UT_address, Y1_address);
    temp_y.b[2] = i2c_readRegisterByte(UT_address, Y2_address);
    temp_y.b[3] = i2c_readRegisterByte(UT_address, Y3_address);

    sigma.f += temp_x.f * temp_x.f + temp_y.f * temp_y.f ;

    for (size_t i = 0; i < 4; i++) {
        Serial.write(sigma.b[i]);
    }

    delay(100);

}
