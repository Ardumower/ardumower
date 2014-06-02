#ifndef __AVR__

// Arduino Due compatibility wrappers , Atmel SAM3X8E ARM Cortex-M3 (Due),  (SAM3X/A series)

#ifndef DUE_H
#define DUE_H

#include <inttypes.h>
#include <Arduino.h>


// http://forum.arduino.cc/index.php/topic,136500.0.html
void tone(uint32_t ulPin, uint32_t frequency, int32_t duration = 0);
void noTone(uint32_t ulPin);


// https://github.com/sebnil/DueFlashStorage
class DueFlash
{
  public:
    DueFlash();
    byte read(uint32_t address);
    byte* readAddress(uint32_t address);
    boolean write(uint32_t address, byte value);
    boolean write(uint32_t address, byte *data, uint32_t dataLength);    
};

extern DueFlash EEPROM;


#endif


#endif  //#ifndef __AVR__

