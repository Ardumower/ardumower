/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  
  Private-use only! (you need to ask for a commercial-use)
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  Private-use only! (you need to ask for a commercial-use)

*/


#ifndef __AVR__

// Arduino Due compatibility wrappers , Atmel SAM3X8E ARM Cortex-M3 (Due),  (SAM3X/A series)
// datasheet:  http://www.atmel.com/images/doc11057.pdf

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

