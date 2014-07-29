/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
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

  
 changes:
  v0.1      04.06.2013  first prototype (wheel/mower motors, bumper, compass, ultrasonic, state machine, PID)
  v0.9.3.5  23.05.2014  Arduino Due support, new wiring scheme for both Mega and Due(!) NOTE: Requires Arduino IDE 1.5.6-r2 or higher
  v0.9.3.6  24.05.2014  pinMotorLeftPWM changed, GPS time support  
  

Operation modes (press button for x beeps):
1 beeps : normal mowing                           OK, tested
2 beeps : normal mowing (bidir)                   broken
3 beeps : drive by remote control (RC)            should work, not tested
4 beeps : drive without mowing                    should work, not tested
5 beeps : find perimeter and track it             OK, tested
6 beeps : track perimeter (debug-feature)         OK, tested 
7 beeps : normal mowing (lane-by-lane)            broken


For additional circuits for button, buzzer etc. (DIY version), see www.ardumower.de  
  
 */
#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
//  #include "due.h"
#endif


// ------ choose ONLY ONE robot configuration --------------------------------------------------

#include "mower.h"  // Ardumower Chassis Kit 1.0
//#include "sim.h"  // Ardumower Chassis Kit 1.0 (simbad simulator) - maybe future :)


void setup()  {     
  robot.setup();
} 

void loop()  {     
  robot.loop();    
}




