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

// drivers (motor driver, sensor drivers, etc.)

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
#define DS1307_ADDRESS B1101000


// ---------- date time --------------------------------------

extern char *dayOfWeek[];

struct timehm_t {
  byte hour;
  byte minute;  
};

typedef struct timehm_t timehm_t;

struct date_t {
  byte dayOfWeek;
  byte day;
  byte month;
  short year;  
};

typedef struct date_t date_t;

struct datetime_t {
  timehm_t time;
  date_t date;
};

typedef struct datetime_t datetime_t;

// ---------- timers --------------------------------------
struct ttimer_t {
  boolean active;
  timehm_t startTime;
  timehm_t stopTime;
  byte daysOfWeek;
};

typedef struct ttimer_t ttimer_t;


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

// time helpers
void minutes2time(int minutes, timehm_t &time);
int time2minutes(timehm_t time);
String time2str(timehm_t time);
String date2str(date_t date);

String versionToStr(byte v[]);

// I2C helpers
void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val);
int I2CreadFrom(uint8_t device, uint8_t address, uint8_t num, uint8_t buff[], int retryCount = 0);

// rescale to -PI..+PI
double scalePI(double v);

// computes minimum distance between x radiant (current-value) and w radiant (set-value)
double distancePI(double x, double w);

// ultrasonic sensor
unsigned int readHCSR04(int triggerPin, int echoPin);
unsigned int readURM37(int triggerPin, int echoPin);

// motor drivers
void setPwmFrequency(int pin, int divisor);
void setL298N(int pinDir, int pinPWM, int speed);
void setL9958(int pinDir, int pinPWM, int speed);
void setRomeoMotor(int pinDir, int pinPWM, int speed);
void setMC33926(int pinDir, int pinPWM, int speed);

// lawn sensor
int measureLawnCapacity(int pinSend, int pinReceive);

// real time drivers
boolean readDS1307(datetime_t &dt);
boolean setDS1307(datetime_t &dt);


// Returns the day of week (0=Sunday, 6=Saturday) for a given date
int getDayOfWeek(int month, int day, int year, int CalendarSystem);

#endif 



