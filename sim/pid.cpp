/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  
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


#include "pid.h"
#include <stdint.h>
#include <stdio.h>


PID::PID()
{
  lastControlTime = 0;
}

PID::PID(float Kp, float Ki, float Kd){
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}


float PID::compute(float timeNow)
{
  Ta = (timeNow - lastControlTime);
  lastControlTime = timeNow;
  if (Ta > 1.0) {
    Ta = 1.0;   // should only happen for the very first call
    printf("PID: corrected Ta\n");
  }

  // compute error
  float e = (w - x);
  // integrate error
  esum += e;
  // anti wind-up
  if (esum < -max_output)  esum = -max_output;
  if (esum > max_output)  esum = max_output;
  y = Kp * e
      + Ki * Ta * esum
      + Kd/Ta * (e - eold);
  eold = e;
  // restrict output to min/max
  if (y > y_max) y = y_max;
  if (y < y_min) y = y_min;

  // printf("Ta=%3.1f  e=%3.1f  y=%3.1f\n", Ta, e, y);
  return y;
}




