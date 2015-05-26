/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri
  
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

// utility functions

#ifndef DRIVERS_H
#define DRIVERS_H

#include <Arduino.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>  
  #define Console Serial
  #define Bluetooth Serial2
#else 
  // Arduino Due
  #include "due.h"
   // Due has two serial ports: Native (SerialUSB) and Programming (Serial) - we want to use 'SerialUSB' for 'Console'
  #define Console SerialUSB
  #define Bluetooth Serial2  
#endif


// ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
#define MAX_ECHO_TIME 3000         
#define NO_ECHO 0

// I2C addresses
#define STEPPER_ADDRESS 0xBB


// ---- other ----------------------------------


// returns sign of variable (-1, 0, +1)
template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

// ---------- EEPROM helpers ----------------------------------

template <class T> int eewrite(int &ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int eeread(int &ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

template <class T> int eereadwrite(boolean readflag, int &ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
    { 
       if (readflag) *p++ = EEPROM.read(ee++);
         else EEPROM.write(ee++, *p++);
    }
    return i;
}


// ---------- driver functions ----------------------------------

int freeRam();
  
// print helpers
void StreamPrint_progmem(Print &out,PGM_P format,...);
#define Serialprint(format, ...) StreamPrint_progmem(Serial,PSTR(format),##__VA_ARGS__)
#define Streamprint(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)
String verToString(int v);


String versionToStr(byte v[]);

// I2C helpers
void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val);
void I2CwriteTo(uint8_t device, uint8_t address, int num, uint8_t buff[]);
int I2CreadFrom(uint8_t device, uint8_t address, uint8_t num, uint8_t buff[], int retryCount = 0);

// rescale to -PI..+PI
double scalePI(double v);

// computes minimum distance between x radiant (current-value) and w radiant (set-value)
double distancePI(double x, double w);


#endif 



