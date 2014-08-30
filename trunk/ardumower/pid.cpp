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
*/

#include "pid.h"


PID::PID()
{
}
    
PID::PID(float Kp, float Ki, float Kd){
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}


float PID::compute()
{		
  unsigned long now = micros();
  Ta = ((now - lastControlTime) / 1000000.0);
  lastControlTime = now;
  if (Ta > 0.5) Ta = 0;   // should only happen for the very first call

  // compute error
  int16_t e = (w - x);	
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
  
  return y;
}




