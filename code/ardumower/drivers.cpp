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
#include "config.h"
#include "pinman.h"
#include "i2c.h"
//#include "ardumower.h"
#include <Wire.h>  


char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

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

int time2minutes(timehm_t time){
  return (time.hour * 60 + time.minute);
}

void minutes2time(int minutes, timehm_t &time){
  time.hour   = minutes / 60;
  time.minute = minutes % 60;
}

String time2str(timehm_t time){
  String s = String(time.hour/10);
  s += (time.hour%10);
  s += ":";
  s += (time.minute/10);
  s += (time.minute%10);
  return s;
}
   
String date2str(date_t date){
  String s = dayOfWeek[date.dayOfWeek];
  s += " ";
  s += date.day / 10;
  s += date.day % 10;
  s += ".";
  s += date.month / 10;
  s += date.month % 10;
  s += ".";  
  s += date.year; 
  return s;
}   
            

// L298N motor driver
// IN2/C(10)/PinPWM   IN1/D(12)/PinDir
// H                  L     Forward
// L                  H     Reverse    
void setL298N(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;  
    PinMan.analogWrite(pinPWM, ((byte)speed));
  } else {
    digitalWrite(pinDir, LOW) ;  
    PinMan.analogWrite(pinPWM, ((byte)speed));
  }
}

// DFRobot Romeo All in one V1.1 motor driver
// D5/D6 PinPWM       D4/D7 PinDir
// H                  L     Forward
// H                  H     Reverse    
void setRomeoMotor(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;  
    PinMan.analogWrite(pinPWM, abs(speed));
  } else {
    digitalWrite(pinDir, LOW) ;  
    PinMan.analogWrite(pinPWM, abs(speed));
  }
}

// L9958 motor driver
// PinPWM             PinDir
// H                  H     Forward
// H                  L     Reverse    
void setL9958(int pinDir, int pinPWM, int speed){
  if (speed > 0){
    digitalWrite(pinDir, HIGH) ;  
    PinMan.analogWrite(pinPWM, abs(speed));
  } else {
    digitalWrite(pinDir, LOW) ;  
    PinMan.analogWrite(pinPWM, abs(speed));
  }
}

// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;
    PinMan.analogWrite(pinPWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    PinMan.analogWrite(pinPWM, ((byte)speed));
  }
}

// ---- sensor drivers --------------------------------------------------------------

// HC-SR04 ultrasonic sensor driver
unsigned int readHCSR04(int triggerPin, int echoPin){
  unsigned int uS;  
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  uS = pulseIn(echoPin, HIGH, MAX_ECHO_TIME + 1000);  
  if (uS > MAX_ECHO_TIME) uS = NO_ECHO;
  else if (uS < MIN_ECHO_TIME) uS = NO_ECHO;
  return uS;
}

// URM-37 ultrasonic sensor driver
unsigned int readURM37(int triggerPin, int echoPin){
  unsigned int uS;  
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  uS = pulseIn(echoPin, LOW, MAX_ECHO_TIME + 1000);  
  if (uS > MAX_ECHO_TIME) uS = NO_ECHO;
  return uS;
}

// DS1307 real time driver
boolean readDS1307(datetime_t &dt){
  byte buf[8];  
  if (I2CreadFrom(DS1307_ADDRESS, 0x00, 8, buf, 3) != 8) {
    Console.println("DS1307 comm error");    
    //addErrorCounter(ERR_RTC_COMM);
    return false;
  }      
  if (   ((buf[0] >> 7) != 0) || ((buf[1] >> 7) != 0) || ((buf[2] >> 7) != 0) || ((buf[3] >> 3) != 0) 
      || ((buf[4] >> 6) != 0) || ((buf[5] >> 5) != 0) || ((buf[7] & B01101100) != 0) ) {    
    Console.println("DS1307 data1 error");    
    //addErrorCounter(ERR_RTC_DATA);
    return false;
  }
  datetime_t r;
  r.time.minute    = 10*((buf[1] >>4) & B00000111) + (buf[1] & B00001111);
  r.time.hour      = 10*((buf[2] >>4) & B00000111) + (buf[2] & B00001111);
  r.date.dayOfWeek = (buf[3] & B00000111) - 1;
  r.date.day       = 10*((buf[4] >>4) & B00000011) + (buf[4] & B00001111);
  r.date.month     = 10*((buf[5] >>4) & B00000001) + (buf[5] & B00001111);
  r.date.year      = 10*((buf[6] >>4) & B00001111) + (buf[6] & B00001111);
  if (    (r.time.minute > 59) || (r.time.hour > 23) || (r.date.dayOfWeek > 6)  
       || (r.date.month > 12)  || (r.date.day > 31)  || (r.date.day < 1)         
       || (r.date.month < 1)   || (r.date.year > 99) ){
    Console.println("DS1307 data2 error");    
    //addErrorCounter(ERR_RTC_DATA);
    return false;
  }  
  r.date.year      += 2000;
  dt = r;
  return true;
}

boolean setDS1307(datetime_t &dt){
  byte buf[7];
  if (I2CreadFrom(DS1307_ADDRESS, 0x00, 7, buf, 3) != 7){
    Console.println("DS1307 comm error");    
    //addErrorCounter(ERR_RTC_COMM);
    return false;
  }
  buf[0] = buf[0] & B01111111; // enable clock
  buf[1] = ((dt.time.minute / 10) << 4) | (dt.time.minute % 10);
  buf[2] = ((dt.time.hour   / 10) << 4) | (dt.time.hour   % 10);
  buf[3] = dt.date.dayOfWeek + 1;
  buf[4] = ((dt.date.day    / 10) << 4) | (dt.date.day    % 10);
  buf[5] = ((dt.date.month  / 10) << 4) | (dt.date.month  % 10);
  buf[6] = ((dt.date.year % 100  / 10) << 4) | (dt.date.year % 10);
  I2CwriteToBuf(DS1307_ADDRESS, 0x00, 7, buf);
  return true;
}


// measure lawn sensor capacity 
int measureLawnCapacity(int pinSend, int pinReceive){
  int t=0;    
  digitalWrite(pinSend, HIGH);    
  while (digitalRead(pinReceive)==LOW) t++;        
  digitalWrite(pinSend, LOW);  
  //t = pulseIn(pinReceive, HIGH);
  //Console.println(t);       
  return t;
}


// Returns the day of week (0=Sunday, 6=Saturday) for a given date
int getDayOfWeek(int month, int day, int year, int CalendarSystem)
{
     // CalendarSystem = 1 for Gregorian Calendar, 0 for Julian Calendar
     if (month < 3)
     {
           month = month + 12;
           year = year - 1;
     }
     return (
             day
             + (2 * month)
             + int(6 * (month + 1) / 10)
             + year
             + int(year / 4)
             - int(year / 100)
             + int(year / 400)
             + CalendarSystem
            ) % 7;
}

/*
// --- eereadwrite -------------------------------------------------
int eereadwriteString(boolean readflag, int &ee, String& value)
{
  unsigned int i;
  if (readflag) {
    value = "";
    char ch = EEPROM.read(ee++);
    while (ch) {
      value += ch;
      ch = EEPROM.read(ee++);
    }
  } else {
    for(i=0; i<value.length(); i++) {
      EEPROM.write(ee++, value.charAt(i));
    }
    EEPROM.write(ee++, 0);
  }
}
*/
