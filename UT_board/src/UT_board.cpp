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



void setup(){
    Serial.begin(9600);
    Wire.begin();
    delay(100);
    Wire.beginTransmission(UT_address);
    Wire.write(power_reg);
    Wire.write(1);
    Wire.endTransmission();
}

void loop(){

    TEMP temp_x;
    TEMP temp_y;

    x0 = i2c_readRegisterByte(UT_address, X0_address);
    x1 = i2c_readRegisterByte(UT_address, X1_address);
    x2 = i2c_readRegisterByte(UT_address, X2_address);
    x3 = i2c_readRegisterByte(UT_address, X3_address);
    y0 = i2c_readRegisterByte(UT_address, Y0_address);
    y1 = i2c_readRegisterByte(UT_address, Y1_address);
    y2 = i2c_readRegisterByte(UT_address, Y2_address);
    y3 = i2c_readRegisterByte(UT_address, Y3_address);

    temp_x.b[0] = x3;
    temp_x.b[1] = x2;
    temp_x.b[2] = x1;
    temp_x.b[3] = x0;

    temp_y.b[0] = y3;
    temp_y.b[1] = y2;
    temp_y.b[2] = y1;
    temp_y.b[3] = y0;

    Serial.println(temp_x.f);
    Serial.println(temp_y.f);


    delay(100);

}
