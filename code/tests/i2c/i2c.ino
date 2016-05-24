
/* I2C test  (gyro L3G4200D)
 */

#include <Arduino.h>
#include <Wire.h>

#ifndef __AVR__
  #define Serial SerialUSB
#endif

#define ADXL345B (0x53)          // ADXL345B acceleration sensor (GY-80 PCB)
#define HMC5883L (0x1E)          // HMC5883L compass sensor (GY-80 PCB)
#define L3G4200D (0xD2 >> 1)     // L3G4200D gyro sensor (GY-80 PCB)

struct {
  uint8_t xl;
  uint8_t xh;
  uint8_t yl;
  uint8_t yh;
  uint8_t zl;
  uint8_t zh;
} gyroFifo[32];



// ---- I2C helpers --------------------------------------------------------------
void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   Wire.write(val);        // send value to write
   Wire.endTransmission(); //end transmission
}

int I2CreadFrom(uint8_t device, uint8_t address, uint8_t num, uint8_t buff[], int retryCount = 0) {
  int i = 0;
  for (int j=0; j < retryCount+1; j++){
    i=0;
    Wire.beginTransmission(device); //start transmission to device 
    Wire.write(address);        //sends address to read from
    Wire.endTransmission(); //end transmission
  
    //Wire.beginTransmission(device); //start transmission to device (initiate again)
    Wire.requestFrom(device, num);    // request 6 bytes from device
  
    while(Wire.available())    //device may send less than requested (abnormal)
    {  
      buff[i] = Wire.read(); // receive a byte
      i++;
    }
    //Wire.endTransmission(); //end transmission
    if (num == i) return i;
    if (j != retryCount) delay(3);
  }
  return i;
}


void setup()  {
  Wire.begin();
  Serial.begin(19200);
  while (!Serial) ; // required if using Due native port  
  Serial.println("START");
  
  uint8_t buf[6];
  // Normal power mode, all axes enabled, 100 Hz
  I2CwriteTo(L3G4200D, 0x20, 0b00001100);    
  // 2000 dps (degree per second)
  I2CwriteTo(L3G4200D, 0x23, 0b00100000);      
  I2CreadFrom(L3G4200D, 0x23, 1, (uint8_t*)buf);
  if (buf[0] != 0b00100000){
      Serial.println(F("gyro write error")); 
      while(true);
  }    
}

void loop()  {
  
  I2CreadFrom(L3G4200D, 0xA8, sizeof(gyroFifo[0]), (uint8_t *)gyroFifo);         // the first bit of the register address specifies we want automatic address increment
  
  double x = (int16_t) (((uint16_t)gyroFifo[0].xh) << 8 | gyroFifo[0].xl);
  
  Serial.println(x);
  

  delay(100);
}




