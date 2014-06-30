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

// definitions (types, structures, driver functions)

#ifndef ARDUMOWER_H
#define ARDUMOWER_H

#include <Arduino.h>
#include "drivers.h"
#include "perimeter.h"
#include "imu.h"
#include "gps.h"

#define VER 0x0932


// sensors
enum {
  SEN_PERIM_LEFT,        // 0..MAX_PERIMETER
  SEN_PERIM_RIGHT,       // 0..MAX_PERIMETER
  SEN_PERIM_LEFT_EXTRA,  // 0..MAX_PERIMETER
  SEN_PERIM_RIGHT_EXTRA, // 0..MAX_PERIMETER
  SEN_LAWN_FRONT,        
  SEN_LAWN_BACK,         
  SEN_BAT_VOLTAGE,       // Volt * 100
  SEN_CHG_CURRENT,       // Ampere * 100
  SEN_CHG_VOLTAGE,       // Volt * 100
  SEN_MOTOR_LEFT,        // 0..MAX_MOTOR_CURRENT
  SEN_MOTOR_RIGHT,       // 0..MAX_MOTOR_CURRENT
  SEN_MOTOR_MOW,         // 0..MAX_MOW_CURRENT
  SEN_BUMPER_LEFT,       // LOW = pressed
  SEN_BUMPER_RIGHT,      // LOW = pressed
  SEN_SONAR_CENTER,      // 0..SONAR_TRIGGER_DISTANCE
  SEN_SONAR_LEFT,        // 0..SONAR_TRIGGER_DISTANCE
  SEN_SONAR_RIGHT,       // 0..SONAR_TRIGGER_DISTANCE
  SEN_BUTTON,            // LOW = pressed
  SEN_IMU,             
  SEN_MOTOR_MOW_RPM,
  SEN_RTC,
};

// actuators
enum {
  ACT_MOTOR_LEFT,
  ACT_MOTOR_RIGHT,
  ACT_MOTOR_MOW,
  ACT_BUZZER,
  ACT_LED,
  ACT_USER_SW1,
  ACT_USER_SW2,
  ACT_USER_SW3,    
  ACT_RTC,
};

// error types
enum {
  ERR_MOW_SENSE,
  ERR_IMU_COMM,
  ERR_IMU_TILT,
  ERR_RTC_COMM,
  ERR_RTC_DATA,
  ERR_PERIMETER_TIMEOUT,
  ERR_ENUM_COUNT,  
};  


// ---------- automata states -----------------------
enum { 
  STATE_OFF,          // off
  STATE_REMOTE,       // model remote control (R/C)
  STATE_FORWARD,      // drive forward
  STATE_ROLL,         // drive roll right/left  
  STATE_REVERSE,      // drive reverse
  STATE_CIRCLE,       // drive circle  
  STATE_ERROR,        // error
  STATE_PERI_FIND,    // perimeter find 
  STATE_PERI_TRACK,   // perimeter track
  STATE_PERI_ROLL,    // perimeter roll
  STATE_PERI_REV,     // perimeter reverse
  STATE_CHARGE,       // charge
  STATE_CHARGE_REV,   // charge reverse
  STATE_CHARGE_ROLL,  // charge roll
  STATE_CHARGE_FORW,  // charge forward
  STATE_MANUAL,       // manual navigation  
  STATE_ROLL_WAIT,    // drive roll right/left
};

// roll types
enum { LEFT, RIGHT };

// mow patterns
enum { MOW_RANDOM, MOW_LANES, MOW_BIDIR };

// console mode
enum { CONSOLE_SENSOR_COUNTERS, CONSOLE_SENSOR_VALUES, CONSOLE_PERIMETER };



// ---------- timers --------------------------------------
struct ttimer_t {
  boolean active;
  timehm_t startTime;
  timehm_t stopTime;
  byte daysOfWeek;
};

typedef struct ttimer_t ttimer_t;

#define MAX_TIMERS 3


// --------- config interface  -----------------------
extern double motorAccel;
extern double motorMowAccel;
extern double motorBiDirSpeedRatio1;
extern double motorBiDirSpeedRatio2;
extern int motorSpeedMax;
extern double motorPowerMax;
extern int motorRightSenseADC;
extern int motorLeftSenseADC;
extern double motorSenseRightScale;
extern double motorSenseLeftScale;
extern int motorRollTimeMax;
extern int motorReverseTime;
extern long motorForwTimeMax;
extern int motorMowSpeedMax;
extern double motorMowPowerMax;
extern int motorMowSenseADC;
extern char motorMowModulate;
extern int motorMowRPM;
extern double motorMowSenseScale;
extern char bumperUse;
extern char sonarUse;
extern int  sonarTriggerBelow;
extern char perimeterUse;
extern int  perimeterTrackRollTime;
extern int  perimeterTrackRevTime;
extern char lawnSensorUse;
extern char imuUse;
extern char imuCorrectDir;
extern char remoteUse;
extern char batMonitor;
extern double batGoHomeIfBelow;
extern double batSwitchOffIfBelow;
extern double batFactor;
extern int batSenseZero;
extern int batADC;
extern double batFull;
extern int  chgSenseZero;
extern double chgFactor;
extern int stationRevTime;
extern int stationRollTime;
extern int stationForwTime;
extern char odometryUse;
extern double odometryTicksPerCm;
extern double odometryWheelBaseCm;
extern int odometryLeft;
extern int odometryRight;
extern double odometryX;
extern double odometryY;
extern char buttonUse;
extern pid_params_t imuDirPid;
extern pid_params_t imuRollPid;
extern pid_params_t perimeterPid;
extern pid_params_t motorMowPid;
extern char userSwitch1;
extern char userSwitch2;
extern char userSwitch3;
extern char timerUse;

extern char configName[];
int readSensor(char type);
void setActuator(char type, int value);

// ---------- Ardumower interface --------------------

extern byte appVer[4];
extern byte errorCounterMax[];
extern unsigned long stateStartTime;
extern int loopsPerSec;  // main loops per second
extern byte consoleMode;
extern char *mowPatternName[];
extern byte mowPatternCurr;
extern char* stateName[];
extern ttimer_t timer[];
extern datetime_t datetime;
extern byte stateCurr; 
extern double imuYaw;  // yaw angle (radiant)
extern double imuPitch; // pitch angle (radiant)
extern double imuRoll; // roll angle (radiant)
extern double imuRollHeading; 
extern short imuComX;
extern short imuComY;
extern short imuComZ;
extern point_float_t accMin;
extern point_float_t accMax;
extern boolean motorMowEnable;
extern int motorMowSpeed;
extern double motorMowPWM;
extern int motorLeftSpeed; // set speed
extern int motorRightSpeed;
extern double motorLeftPWM; // current speed
extern double motorRightPWM;  
extern double batVoltage;  // battery voltage (Volt)
extern double batCapacity; // battery capacity (Ah)
extern double chgVoltage;  // charge voltage (Volt)
extern double chgCurrent;  // charge current  (Ampere)
extern int motorLeftSenseCounter;  // motor current counter
extern int motorRightSenseCounter;
extern int motorMowSenseCounter;
extern unsigned int sonarDistCounter;
extern int bumperLeftCounter;
extern int bumperRightCounter;
extern int perimeterCounter;
extern int lawnSensorCounter;
extern boolean bumperLeft;
extern boolean bumperRight;
extern unsigned int sonarDistCenter;
extern unsigned int sonarDistRight ;
extern unsigned int sonarDistLeft ; 
extern int perimeterLeft;
extern int perimeterLeftCounter;
extern int perimeterRight;
extern boolean lawnSensor;
extern double lawnSensorFront;
extern double lawnSensorBack;
extern double motorLeftSenseCurrent ;  
extern double motorRightSenseCurrent;
extern double motorLeftSense ;      // motor power (range 0..MAX_MOTOR_POWER)
extern double motorRightSense ;
extern int motorMowRpm ;            // motor rpm (range 0..MOW_RPM)
extern double motorMowSenseCurrent;
extern double motorMowSense ;       // motor power (range 0..MAX_MOW_POWER)
extern byte errorCounterIMUComm;
extern byte errorCounterIMUTilt;
extern byte errorCounterRTCComm;
extern byte errorCounterRTCData;
extern byte errorCounterPerimeterComm;
extern IMU imu;
extern GPS gps;

void setNextState(byte stateNew, byte dir);
void printInfo(Stream &s);
// model remote control (RC)
void setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState, 
  boolean remoteMowState, boolean remoteSwitchState);
// mower motor RPM
void setMotorMowRPMState(boolean motorMowRpmState);
// odometry
void setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, boolean odometryLeftState2 = 0, boolean odometryRightState2 = 0);
// user settings
void deleteUserSettings();
void saveUserSettings();
void setUserSwitches();
void beep(int numberOfBeeps, boolean shortbeep);
void addErrorCounter(byte errType);

#endif // ARDUMOWER_H


