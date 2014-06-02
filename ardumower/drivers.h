// Arduino robot mower
// Copyright (c) 2013 by Alexander Grau
// Copyright (c) 2013 by Sven Gennat
//
// drivers (motor driver, sensor drivers, etc.)

#ifndef DRIVERS_H
#define DRIVERS_H

#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
  #include "due.h"
#endif
#include <Arduino.h>

// ultrasonic sensor max echo time
#define MAX_ECHO_TIME 50000        
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

// ---------- PID controller ---------------------------------
struct pidc_t {
	double Ta;	
	int16_t w;
	int16_t x;
	int16_t esum;
	int16_t eold;
	int16_t y;
	int16_t y_min;	
	int16_t y_max;	
	int16_t max_pwm;  // 1023
	double Kp;//8.0  // Verstaerkungsfaktor Regelabweichung 		
	double Ki;//0.0 	// Faktor fuer Integral Regelabweichung	
	double Kd;//0.01 // Faktor fuer Ableitung Regelabweichung		
};

typedef struct pidc_t pidc_t;

struct pid_params_t {
	double Kp;    // Verstaerkungsfaktor Regelabweichung 		
	double Ki;    // Faktor fuer Integral Regelabweichung	
	double Kd;    // Faktor fuer Ableitung Regelabweichung		  
};

typedef struct pid_params_t pid_params_t;


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
void I2CwriteTo(int device, byte address, byte val);
int I2CreadFrom(int device, byte address, int num, byte buff[], int retryCount = 0);

// rescale to -PI..+PI
double scalePI(double v);

// computes minimum distance between x radiant (current-value) and w radiant (set-value)
double distancePI(double x, double w);


// PID controller
void PIDControl(pidc_t *pid);

// ultrasonic sensor
unsigned int readHCSR04(int triggerPin, int echoPin);
unsigned int readURM37(int triggerPin, int echoPin);

// motor drivers
void setPwmFrequency(int pin, int divisor);
void setL298N(int pinDir, int pinPWM, int speed);
void setL9958(int pinDir, int pinPWM, int speed);
void setRomeoMotor(int pinDir, int pinPWM, int speed);

// lawn sensor
int measureLawnCapacity(int pinSend, int pinReceive);

// real time drivers
boolean readDS1307(datetime_t &dt);
boolean setDS1307(datetime_t &dt);


// Returns the day of week (0=Sunday, 6=Saturday) for a given date
int getDayOfWeek(int month, int day, int year, int CalendarSystem);

#endif 



