/*
The MIT License (MIT)

Copyright (c) 2020 asukiaaa

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MPU9250.h"
#include <math.h>

#define AK8963_ADDRESS  0x0C
#define AK8963_RA_HXL   0x03
#define AK8963_RA_CNTL1 0x0A
#define AK8963_RA_ASAX  0x10

#define MPU9250_ADDR_ACCELCONFIG  0x1C
#define MPU9250_ADDR_INT_PIN_CFG  0x37
#define MPU9250_ADDR_ACCEL_XOUT_H 0x3B
#define MPU9250_ADDR_GYRO_XOUT_H  0x43
#define MPU9250_ADDR_PWR_MGMT_1   0x6B
#define MPU9250_ADDR_WHOAMI       0x75

uint8_t MPU9250::i2cRead(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  myWire->beginTransmission(Address);
  myWire->write(Register);
  uint8_t result = myWire->endTransmission();
  if (result != 0) {
    return result;
  }

  myWire->requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (myWire->available()) {
    uint8_t d = myWire->read();
    if (index < Nbytes) {
      Data[index++] = d;
    }
  }
  return 0;
}

uint8_t MPU9250::i2cWriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  myWire->beginTransmission(Address);
  myWire->write(Register);
  myWire->write(Data);
  return myWire->endTransmission();
}

MPU9250::MPU9250(uint8_t address):
  address(address) {
  accelRange = 0;
  gyroRange  = 0;
  magXOffset = 0;
  magYOffset = 0;
  magZOffset = 0;
  myWire = NULL;
}

void MPU9250::setWire(TwoWire* wire) {
  myWire = wire;
}

uint8_t MPU9250::readId(uint8_t *id) {
  return i2cRead(address, MPU9250_ADDR_WHOAMI, 1, id);
}

void MPU9250::beginWireIfNull() {
  if (myWire == NULL) {
    myWire = &Wire;
    myWire->begin();
  }
}

void MPU9250::beginAccel(uint8_t mode) {
  beginWireIfNull();
  switch(mode) {
  case ACC_FULL_SCALE_2_G:
    accelRange = 2.0;
    break;
  case ACC_FULL_SCALE_4_G:
    accelRange = 4.0;
    break;
  case ACC_FULL_SCALE_8_G:
    accelRange = 8.0;
    break;
  case ACC_FULL_SCALE_16_G:
    accelRange = 16.0;
    break;
  default:
    return; // Return without writing invalid mode
  }
  i2cWriteByte(address, MPU9250_ADDR_ACCELCONFIG, mode);
  delay(10);
}

void MPU9250::magReadAdjustValues() {
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(MAG_MODE_FUSEROM);
  uint8_t buff[3];
  i2cRead(AK8963_ADDRESS, AK8963_RA_ASAX, 3, buff);
  magXAdjust = buff[0];
  magYAdjust = buff[1];
  magZAdjust = buff[2];
}

void MPU9250::beginMag(uint8_t mode) {
  beginWireIfNull();
  magWakeup();
  magEnableSlaveMode();

  magReadAdjustValues();
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(mode);
  delay(10);
}

void MPU9250::magSetMode(uint8_t mode) {
  i2cWriteByte(AK8963_ADDRESS, AK8963_RA_CNTL1, mode);
  delay(10);
}

void MPU9250::magWakeup() {
  unsigned char bits;
  i2cRead(address, MPU9250_ADDR_PWR_MGMT_1, 1, &bits);
  bits &= ~B01110000; // Turn off SLEEP, STANDBY, CYCLE
  i2cWriteByte(address, MPU9250_ADDR_PWR_MGMT_1, bits);
  delay(10);
}

void MPU9250::magEnableSlaveMode() {
  unsigned char bits;
  i2cRead(address, MPU9250_ADDR_INT_PIN_CFG, 1, &bits);
  bits |= B00000010; // Activate BYPASS_EN
  i2cWriteByte(address, MPU9250_ADDR_INT_PIN_CFG, bits);
  delay(10);
}

const float Pi = 3.14159;

float MPU9250::magHorizDirection() {
  return atan2(magX(), magY()) * 180 / Pi;
}

uint8_t MPU9250::magUpdate() {
  return i2cRead(AK8963_ADDRESS, AK8963_RA_HXL, 7, magBuff);
}

int16_t MPU9250::magGet(uint8_t highIndex, uint8_t lowIndex) {
  return (((int16_t) magBuff[highIndex]) << 8) | magBuff[lowIndex];
}

float adjustMagValue(int16_t value, uint8_t adjust) {
  return ((float) value * (((((float) adjust - 128) * 0.5) / 128) + 1));
}

float MPU9250::magX() {
  return adjustMagValue(magGet(1, 0), magXAdjust) + magXOffset;
}

float MPU9250::magY() {
  return adjustMagValue(magGet(3, 2), magYAdjust) + magYOffset;
}

float MPU9250::magZ() {
  return adjustMagValue(magGet(5, 4), magZAdjust) + magZOffset;
}

uint8_t MPU9250::accelUpdate() {
  return i2cRead(address, MPU9250_ADDR_ACCEL_XOUT_H, 6, accelBuff);
}

float MPU9250::accelGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = ((int16_t) accelBuff[highIndex]) << 8 | accelBuff[lowIndex];
  return ((float) -v) * accelRange / (float) 0x8000; // (float) 0x8000 == 32768.0
}

float MPU9250::accelX() {
  return accelGet(0, 1);
}

float MPU9250::accelY() {
  return accelGet(2, 3);
}

float MPU9250::accelZ() {
  return accelGet(4, 5);
}

float MPU9250::accelSqrt() {
  return sqrt(pow(accelGet(0, 1), 2) +
              pow(accelGet(2, 3), 2) +
              pow(accelGet(4, 5), 2));
}

void MPU9250::beginGyro(uint8_t mode) {
  beginWireIfNull();
  switch (mode) {
  case GYRO_FULL_SCALE_250_DPS:
    gyroRange = 250.0;
    break;
  case GYRO_FULL_SCALE_500_DPS:
    gyroRange = 500.0;
    break;
  case GYRO_FULL_SCALE_1000_DPS:
    gyroRange = 1000.0;
    break;
  case GYRO_FULL_SCALE_2000_DPS:
    gyroRange = 2000.0;
    break;
  default:
    return; // Return without writing invalid mode
  }
  i2cWriteByte(address, 27, mode);
  delay(10);
}

uint8_t MPU9250::gyroUpdate() {
  return i2cRead(address, MPU9250_ADDR_GYRO_XOUT_H, 6, gyroBuff);
}

float MPU9250::gyroGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = ((int16_t) gyroBuff[highIndex]) << 8 | gyroBuff[lowIndex];
  return ((float) -v) * gyroRange / (float) 0x8000;
}

float MPU9250::gyroX() {
  return gyroGet(0, 1);
}

float MPU9250::gyroY() {
  return gyroGet(2, 3);
}

float MPU9250::gyroZ() {
  return gyroGet(4, 5);
}
