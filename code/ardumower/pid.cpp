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
    
  How to find out P,I,D:
    1. Increase P until system starts to oscillate
    2. Set I =0.6 * P and D = 0.125 * P 
   
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


void PID::reset(void) {
  this->eold = 0;
  this->esum = 0;
}

float PID::compute() {
  unsigned long now = micros();
  Ta = ((now - lastControlTime) / 1000000.0);
  lastControlTime = now;
  if (Ta > 1.0) Ta = 1.0;   // should only happen for the very first call

  // compute error
  float e = (w - x);	
  // integrate error
  esum += e;
  // anti wind-up	
  float iTerm = Ki * Ta * esum;	
  if (iTerm < -max_output)  {
    iTerm = -max_output;
    esum = -max_output / Ta / Ki;
  }
  if (iTerm > max_output)  {
    iTerm = max_output;			
    esum = max_output / Ta / Ki;
  }
  y = Kp * e
      + iTerm
      + Kd/Ta * (e - eold);
  eold = e;			
  // restrict output to min/max	
  if (y > y_max) y = y_max;
  if (y < y_min) y = y_min;	
  
  return y;
}


// ---------------------------------

VelocityPID::VelocityPID()
{
}
    
VelocityPID::VelocityPID(float Kp, float Ki, float Kd){
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}


float VelocityPID::compute()
{   
  unsigned long now = micros();
  Ta = ((now - lastControlTime) / 1000000.0);
  lastControlTime = now;
  if (Ta > 1.0) Ta = 1.0;   // should only happen for the very first call

  // compute error
  int16_t e = (w - x);

  // compute max/min output
  if (w < 0) { y_min = -max_output; y_max = 0; }
  if (w > 0) { y_min = 0; y_max = max_output; }     

  y = yold
      + Kp * (e - eold1)
      + Ki * Ta * e
      + Kd/Ta * (e - 2* eold1 + eold2);
     
  // restrict output to min/max 
  if (y > y_max) y = y_max;
  if (y < y_min) y = y_min; 

  // save variable for next time
  eold2 = eold1;
  eold1 = e;
  yold = y ;  
  
  return y;
}

