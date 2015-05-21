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

#include "drivers.h"
//#include "ardumower.h"
#include <Wire.h>  


// ---- print helpers ------------------------------------------------------------

void StreamPrint_progmem(Print &out,PGM_P format,...)
{
  // program memory version of printf - copy of format string and result share a buffer
  // so as to avoid too much memory use
  char formatString[128], *ptr;
  #ifdef __AVR__
    strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem
  #else
    strncpy( formatString, format, sizeof(formatString) ); // copy in from program mem  
  #endif
  // null terminate - leave char since we might need it in worst case for result's \0
  formatString[ sizeof(formatString)-2 ]='\0';
  ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
  va_list args;
  va_start (args,format);
  vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
  va_end (args);
  formatString[ sizeof(formatString)-1 ]='\0';
  out.print(ptr);
}

String verToString(int v){
  char buf[20] = {0};
  int a = v >> 12;
  int b = (v >> 8) & 0xF;
  int c = (v >> 4) & 0xF;
  int d = v & 0xF;
  sprintf(buf, "%d.%d.%d.%d", a,b,c,d);
  return String(buf);
} 

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

// rescale to -PI..+PI
double scalePI(double v)
{
  double d = v;
  while (d < 0) d+=2*PI;
  while (d >= 2*PI) d-=2*PI;
  if (d >= PI) return (-2*PI+d); 
  else if (d < -PI) return (2*PI+d);
  else return d;  
}

// computes minimum distance between x radiant (current-value) and w radiant (set-value)
double distancePI(double x, double w)
{
  // cases:   
  // w=330 degree, x=350 degree => -20 degree
  // w=350 degree, x=10  degree => -20 degree
  // w=10  degree, x=350 degree =>  20 degree
  // w=0   degree, x=190 degree => 170 degree
  // w=190 degree, x=0   degree => -170 degree 
  double d = scalePI(w - x);
  if (d < -PI) d = d + 2*PI;
  else if (d > PI) d = d - 2*PI;  
  return d;
}

            
// ---- I2C helpers --------------------------------------------------------------
void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   Wire.write(val);        // send value to write
   Wire.endTransmission(); //end transmission
}

void I2CwriteTo(uint8_t device, uint8_t address, int num, uint8_t buff[]) {
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



