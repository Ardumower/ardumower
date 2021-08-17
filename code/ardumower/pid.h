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

#ifndef PID_H
#define PID_H

#include <Arduino.h>


/*
  digital PID controller
*/

class PID
{
  public:
    PID();
    PID(float Kp, float Ki, float Kd);
    void reset(void);
    float compute();
    double Ta; // sampling time	
    float w; // set value
    float x; // current value
    float esum; // error sum
    float eold; // last error
    float y;   // control output
    float y_min; // minimum control output
    float y_max; // maximum control output
    float max_output; // maximum output 
    float Kp;   // proportional control
    float Ki;   // integral control
    float Kd;   // differential control
    unsigned long lastControlTime;
};


class VelocityPID
{
  public:
    VelocityPID();
    VelocityPID(float Kp, float Ki, float Kd);
    float compute();
    double Ta; // sampling time 
    float w; // set value
    float x; // current value
    float eold1; // last error
    float eold2; // error n-2   
    int y;   // control output
    int yold;   // last control output    
    int y_min; // minimum control output
    int y_max; // maximum control output
    int max_output; // maximum output 
    float Kp;   // proportional control
    float Ki;   // integral control
    float Kd;   // differential control
    unsigned long lastControlTime;
};



#endif

