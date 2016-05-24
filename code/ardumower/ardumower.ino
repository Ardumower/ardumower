/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  Copyright (c) 2013-2015 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri    
  Copyright (c) 2014-2015 by Stefan Manteuffel
  Copyright (c) 2015 by Uwe Zimprich
  
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

  
 changes: see https://code.google.com/p/ardumower/source/list

Operation modes (press button for x beeps):
1 beeps : normal mowing                           OK, tested
2 beeps : normal mowing (bidir)                   broken
3 beeps : drive by remote control (RC)            should work, not tested
4 beeps : normal without perimeter                OK, tested
5 beeps : find perimeter and track it             OK, tested
6 beeps : track perimeter (debug-feature)         OK, tested 
7 beeps : normal mowing (lane-by-lane)            broken


For additional circuits for button, buzzer etc. (DIY version), see www.ardumower.de  
    
 */
#include <Arduino.h>
#include <Wire.h>
//#include <Servo.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
  #include "due.h"
#endif
#include "config.h"


// requires: Arduino Mega or Arduino Due
// NOTE for Arduino Due:  use native USB port for programming and console!


void setup()  {     
  robot.setup();
} 

void loop()  {     
  robot.loop();    
}




