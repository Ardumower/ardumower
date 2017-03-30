#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C"{
#endif

void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val);
void I2CwriteToBuf(uint8_t device, uint8_t address, int num, uint8_t buff[]);
int I2CreadFrom(uint8_t device, uint8_t address, uint8_t num, uint8_t buff[], int retryCount = 0);
void I2Creset();

#ifdef __cplusplus
}
#endif

#endif

