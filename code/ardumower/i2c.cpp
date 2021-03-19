#include "i2c.h"
#include <Wire.h>
#include "config.h"

#if defined(__AVR_ATmega328P__)  
  // Nano pins  
  #define SDA A4
  #define SCL A5
#else
  // Mega2560/Due pins
  #define SDA 20
  #define SCL 21
#endif


/**
 * This routine turns off the I2C bus and clears it
 * on return SCA and SCL pins are tri-state inputs.
 * You need to call Wire.begin() after this to re-enable I2C
 * This routine does NOT use the Wire library at all.
 *
 * returns 0 if bus cleared
 *         1 if SCL held low.
 *         2 if SDA held low by slave clock stretch for > 2sec
 *         3 if SDA held low after 20 clocks.
 */
int I2CclearBus() {
#if defined(TWCR) && defined(TWEN)
  TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
#endif

  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);

  delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
  // up of the DS3231 module to allow it to initialize properly,
  // but is also assists in reliable programming of FioV3 boards as it gives the
  // IDE a chance to start uploaded the program
  // before existing sketch confuses the IDE by sending Serial data.

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master. 
    return 1; //I2C bus error. Could not clear SCL clock line held low
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
  // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
      return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
    return 3; // I2C bus error. Could not clear. SDA data line held low
  }

  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  return 0; // all ok
}

void I2Creset(){
  #ifdef __AVR_ATmega2560__
    Console.println(F("WARNING Mega2560: you may have to add 4k7 resistors (pull-ups) between SDA, SCL and IOREF for proper I2C bus"));  
  #endif 
  unsigned long timeout = millis() + 10000;
  while (millis() < timeout){
    int rtn = I2CclearBus(); // clear the I2C bus first before calling Wire.begin()
    if (rtn == 0) return;
    Console.println(F("I2C bus error. Could not clear (PCB not powered ON or RTC module missing or JCx jumper set for missing I2C module)"));
    if (rtn == 1) {
      Console.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      Console.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      Console.println(F("SDA data line held low"));
    }
  }
}

void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   Wire.write(val);        // send value to write
   Wire.endTransmission(); //end transmission
}

void I2CwriteToBuf(uint8_t device, uint8_t address, int num, uint8_t buff[]) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   for (int i=0; i < num; i++){
     Wire.write(buff[i]);        // send value to write
   }
   Wire.endTransmission(); //end transmission
}

int I2CreadFrom(uint8_t device, uint8_t address, uint8_t num, uint8_t buff[], int retryCount) {
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


void I2CScanner(){
  byte error, address;
  int nDevices = 0;
 
  Console.println(F("Scanning for I2C devices..."));
  for(address = 1; address < 127; address++ )
  {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
   
      if (error == 0)
      {
        Console.print(F("I2C device found at address 0x"));
        if (address<16)
          Console.print(F("0"));
        Console.print(address,HEX);
        Console.print(F(" ("));
        nDevices++;
        switch (address){          
          case 0x1E: Console.print(F("probably HMC5883L")); break;
          case 0x30: Console.print(F("probably MMC5883MA")); break;          
          case 0x50: Console.print(F("probably AT24C32")); break;
          case 0x53: Console.print(F("probably ADXL345B")); break;
          case 0x60: Console.print(F("probably CMPS11")); break;          
          case 0x68: Console.print(F("probably DS1307")); break;
          case 0x69: Console.print(F("probably MPU6050/9150 or L3G4200D")); break;          
          case 0x77: Console.print(F("probably BMP180")); break;                    
          default: Console.print(F("unknown module"));
        }
        Console.println(F(")"));
      }
      else if (error==4)
      {
        Console.print(F("Unknown error at address 0x"));
        if (address<16)
          Console.print(F("0"));
        Console.println(address,HEX);
      }    
  }
  if (nDevices == 0)
    Console.println(F("No I2C devices found\n"));
  else
    Console.println(F("done\n"));   
}


  
