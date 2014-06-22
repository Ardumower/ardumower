/*
 Arduino robot mower
 Copyright (c) 2013-2014 by Alexander Grau
 Copyright (c) 2013-2014 by Sven Gennat
 
  Code nützlich? Dann unterstütze das Projekt indem Du den Ardumower Shop besuchst...
  Code usefull? Just support this project by visiting the Ardumower Shop...
 
 * This program is 'Donationware', private-use only (please ask for a commercial-use); 
 * you can redistribute it and/or modify it under the terms of this license published on our website. 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * license for more details. 
  
 changes:
  v0.1      04.06.2013  first prototype (wheel/mower motors, bumper, compass, ultrasonic, state machine, PID)
  v0.2.1    08.07.2013  first working prototype
  v0.2.2    09.07.2013  perimeter tracking 
  v0.3      10.07.2013  find and drive into perimeter 
  v0.3.1    11.07.2013  mower motor 
  v0.3.2    15.07.2013  ultrasonic sensor 
  v0.3.3    16.07.2013  detection of wheel slippage, charge current
  v0.4      18.07.2013  config files
  v0.4.2    22.07.2013  blade modulation 
  v0.5      27.07.2013  RC remote control  
  v0.5.1    28.07.2013  RC remote control activatable via RC  
  v0.5.2    03.08.2013  bugfixes
  v0.6.1    20.08.2013  initial support for pfod app
  v0.6.4    21.08.2013  support for DFRduino board (romeo11.h), and Robomow RL500 (rmrl500.h) (bugfixed)
  v0.6.6    25.08.2013  IMU (fusion of compass, accel, gyro) (experimental)
  v0.6.9    11.09.2013  pfod-app progress, initial support for odometry
  v0.7      15.09.2013  charging station drive-in/drive-out
  v0.7.1    28.09.2013  improved pfod-app (manual navigation)
  v0.7.3    07.10.2013  improved IMU (new algorithm), now requires Nano (IMU)
  v0.7.7    16.10.2013  drive-by-lanes (very experimental)
  v0.8.2    20.10.2013  cleanup, bugfixes - improved pfodApp  (info, pid, settings)
  v0.8.6    25.10.2013  saving user settings, bugfixes, lawn sensor support for Mega board, all settings via pfodApp
  v0.8.8    28.10.2013  pfodApp menu restructured, new config param names, user switches
  v0.9.1.1  18.11.2013  bugfixes, initial timer menu
  v0.9.1.2  28.11.2013  battery plot, odometry plot 
  v0.9.1.3  30.01.2014  stepper motor support (requires stepper Nano)
  v0.9.1.5  15.02.2014  pfodApp support for IMU v0.5.0 (new ArduMag calibration method)
  v0.9.1.6  19.02.2014  Bluetooth config programmer for BT-03,04,05,06
  v0.9.1.7  20.02.2014  IMU plotting
  v0.9.1.9  22.02.2014  Error counters, Sensor counters plotting  
  v0.9.2.1  25.02.2014  Perimeter spectrum plotting, improved error handling
  v0.9.2.2  03.03.2014  Version numbers (pfodApp), improved error handling
  v0.9.2.3  03.03.2014  capacity bugfix
  v0.9.2.4  12.04.2014  motor EMF handling (new config param 'motorAccel'), sonar timeout
  v0.9.2.5  14.04.2014  support for two-wire odometry encoders
  V0.9.2.6  15.04.2014  bidir/4WD support (Ambrogio L50 mow pattern)
  v0.9.2.7  22.04.2014  added motor mower acceleration (motorMowAccel), motor testing bugfix, sonar right/left timeout
  v0.9.2.8  02.05.2014  bidir mow pattern: bumper bugfix, pfodApp motor sense slider adjustments
  v0.9.2.9  06.05.2014  acceleration sensor plots, sonar plots, motor plots
  v0.9.3.0  08.05.2014  bugfixes
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

#include <Wire.h>  
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else
  // Arduino Due
  #include "due.h"
#endif
//#include <Servo.h>  // for RC brushless contoller
#include "ardumower.h"
#include "adcman.h"
#include "drivers.h"
#include "perimeter.h"
//#include <limits.h>

// ------ choose ONLY ONE robot configuration --------------------------------------------------

#include "config.h"  // Ardumower Chassis Kit 1.0
//#include "config_aml50.h"   // Ambrogio L50    (Alexander's Mega test platform)

#ifdef USE_PFOD
  #include "pfod.h"
  #include "bt.h"  
#endif

// --------- timers -------------------------------
ttimer_t timer[MAX_TIMERS] = {0};
datetime_t datetime;
// --------- finate state machine --------------------
char* stateName[]={"OFF ", "RC  ", "FORW", "ROLL", "REV ", "CIRC", "ERR ", "PFND", "PTRK", "PROL", "PREV", "CHRG", 
  "CREV", "CROL", "CFOR", "MANU", "ROLW" };
byte stateNext = STATE_OFF;
byte stateCurr = STATE_OFF; 
byte stateLast = STATE_OFF;
unsigned long stateStartTime;
unsigned long stateEndTime;
// -------- mow pattern -----------------------------
char *mowPatternName[] = {"RAND", "LANE", "BIDIR"};
byte mowPatternCurr = MOW_RANDOM;
// -------- odometry state --------------------------
int odometryLeft = 0;   // left wheel counter
int odometryRight = 0;  // right wheel counter
boolean odometryLeftLastState = LOW;
boolean odometryLeftLastState2 = LOW;
boolean odometryRightLastState = LOW;
boolean odometryRightLastState2 = LOW;
double odometryTheta = 0; // theta angle (radiant)
double odometryX = 0;   // X map position (cm)
double odometryY = 0;   // Y map position (cm)
// -------- RC remote control state -----------------
int remoteSteer = 0;  // range -100..100
int remoteSpeed = 0;  // range -100..100
int remoteMow = 0;    // range 0..100
int remoteSwitch = 0; // range 0..100
unsigned long remoteSteerLastTime = 0;
unsigned long remoteSpeedLastTime = 0;
unsigned long remoteMowLastTime = 0;
unsigned long remoteSwitchLastTime = 0;
boolean remoteSteerLastState = LOW;
boolean remoteSpeedLastState = LOW;
boolean remoteMowLastState = LOW;
boolean remoteSwitchLastState = LOW;
// -------- mower motor state -----------------------
int motorMowRpmCounter = 0;  // mower motor speed state
boolean motorMowRpmLastState = LOW;
boolean motorMowEnable = false;
// --------- wheel motor state ----------------------------
// wheel motor speed ( <0 backward, >0 forward); range -motorSpeedMax..motorSpeedMax
int motorLeftSpeed = 0; // set speed
int motorRightSpeed = 0;
double motorLeftPWM = 0; // current speed
double motorRightPWM = 0;  
double motorLeftSense = 0;      // motor current (range 0..MAX_MOTOR_CURRENT)
double motorRightSense = 0;
int motorLeftSenseCounter = 0;  // motor current counter
int motorRightSenseCounter = 0;
// -------- mower motor state -----------------------
// mower motor sppeed; range 0..motorMowSpeedMax
int motorMowSpeed = motorSpeedMax;
double motorMowPWM = 0;         // current speed
double motorMowSense = 0;       // motor current (range 0..MAX_MOW_CURRENT)
int motorMowSenseCounter = 0;
int motorMowSenseErrorCounter = 0;
int motorMowRpm = 0;            // motor rpm (range 0..MOW_RPM)
// --------- bumper state ---------------------------
// bumper state (true = pressed)
int bumperLeftCounter = 0;
boolean bumperLeft = false;          
int bumperRightCounter = 0;
boolean bumperRight = false;
// ------- IMU state --------------------------------
double imuYaw = 0;    // compass course (radiant)
double imuPitch = 0;  // tilt angle (radiant)
double imuRoll = 0;   // tilt angle (radiant)
double imuDriveHeading = 0;       // drive heading (IMU)
double imuRollHeading = 0;      // roll heading  (IMU)
byte   imuRollDir = LEFT;
short imuComX = 0;  // raw compass values (uncalibrated)
short imuComY = 0;
short imuComZ = 0;
point_float_t accMin = {0,0,0};
point_float_t accMax = {0,0,0};
IMU imu;
GPS gps;
// ------- perimeter state --------------------------
int perimeterLeft = 0;
int perimeterRight = 0;
boolean perimeterLeftState = true;
int perimeterLeftCounter = 0;
//  --------- lawn state ----------------------------
int lawnSensorCounter = 0;
boolean lawnSensor = false;  // lawn capacity sensor state (true = no lawn detected)
double lawnSensorFront = 0;  // front lawn sensor capacity (time)
double lawnSensorFrontOld = 0;
double lawnSensorBack = 0;   // back lawn sensor capacity (time)
double lawnSensorBackOld = 0;
// --------- sonar ----------------------------------
// ultra sonic sensor distance-to-obstacle (cm)
unsigned int sonarDistCenter = 0;
unsigned int sonarDistRight = 0;
unsigned int sonarDistLeft = 0; 
unsigned int sonarDistCounter = 0;
unsigned long sonarObstacleTimeout = 0;
// --------- charging -------------------------------
double batVoltage = 0;  // battery voltage (Volt)
double batRefFactor = 0;
double batCapacity = 0; // battery capacity (mAh)
double chgVoltage = 0;  // charge voltage (Volt)
double chgCurrent = 0;  // charge current  (Ampere)
// ------------ PID controllers ----------------------------
//                       Ta,   w, x, esum, eold, y, y_min, y_max, max_pwm, Kp,    Ki,   Kd
pidc_t imuDirPID      =   {0.0, 0, 0, 0,    0,    0, 0,     0,     0,       0,     0,    0  };
pidc_t imuRollPID     =   {0.0, 0, 0, 0,    0,    0, 0,     0,     0,       0,     0,    0  };
//pidc_t perimeterPID   =   {0.0, 0, 0, 0,    0,    0, 0,     0,     0,       0,     0,    0  };
pidc_t motorMowPID    =   {0.0, 0, 0, 0,    0,    0, 0,     0,     0,       0,     0,    0  };  
// --------- error counters --------------------------
byte errorCounterMax[ERR_ENUM_COUNT] = {0};
byte errorCounter[ERR_ENUM_COUNT] = {0};
// --------- other ----------------------------------
int loopsPerSec = 0;  // main loops per second
double loopsTa = 5.0;   // main loop-time factor (milliseconds)
int loopsPerSecCounter = 0;
byte buttonCounter = 0;
byte ledState = 0;
char* consoleModeName[]={"sen_counters", "sen_values", "perimeter"}; 
byte consoleMode = CONSOLE_SENSOR_COUNTERS; 
unsigned long nextTimeButtonCheck = 0;
unsigned long nextTimeInfo = 0;
unsigned long nextTimeMotorSense = 0;
unsigned long nextTimeIMU = 0;
unsigned long nextTimeOdometry = 0;
unsigned long nextTimeOdometryInfo = 0;
unsigned long nextTimeBumper = 0;
unsigned long nextTimeSonar = 0;
unsigned long nextTimeBattery = 0;
unsigned long nextTimePerimeter = 0;
unsigned long nextTimeLawnSensor = 0;
unsigned long nextTimeLawnSensorCheck = 0;
unsigned long nextTimeTimer = 0;
unsigned long nextTimeRTC = 0;
unsigned long nextTimePfodLoop = 0;
unsigned long lastMotorControlTime = millis();
unsigned long lastMotorMowControlTime = millis();
unsigned long lastMotorMowRpmTime = millis();
byte rollDir;
unsigned long nextTimeButton = 0;
unsigned long nextTimeErrorCounterReset = 0;    
unsigned long nextTimeErrorBeep = 0;

// ---- odometry (interrupt) --------------------------------------------------------
// odometryState:  1st left and right odometry signal
// odometryState2: 2nd left and right odometry signal (optional two-wire encoders)
void setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, boolean odometryLeftState2, boolean odometryRightState2){
  if (odometryLeftState != odometryLeftLastState){    
    if (odometryLeftState){
      if (!odometryLeftState2) odometryLeft++; else odometryLeft--; 
    }
    odometryLeftLastState = odometryLeftState;
  } 
  if (odometryRightState != odometryRightLastState){
    if (odometryRightState){
      if (!odometryRightState2) odometryRight++; else odometryRight--;     
    }
    odometryRightLastState = odometryRightState;
  }  
  if (odometryRightState2 != odometryRightLastState2){
    odometryRightLastState2 = odometryRightState2;    
  }  
  if (odometryLeftState2 != odometryLeftLastState2){
    odometryLeftLastState2 = odometryLeftState2;    
  }   
}

// ---- RC (interrupt) --------------------------------------------------------------
// RC remote control helper
int rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;
  return value;
}

// RC remote control driver
void setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState, 
  boolean remoteMowState, boolean remoteSwitchState){
  if (remoteSpeedState != remoteSpeedLastState) {    
    remoteSpeedLastState = remoteSpeedState;
    if (remoteSpeedState) remoteSpeedLastTime = timeMicros; else remoteSpeed = rcValue(timeMicros - remoteSpeedLastTime);
  }
  if (remoteSteerState != remoteSteerLastState) {    
    remoteSteerLastState = remoteSteerState;
    if (remoteSteerState) remoteSteerLastTime = timeMicros; else remoteSteer = rcValue(timeMicros - remoteSteerLastTime);
  }
  if (remoteMowState != remoteMowLastState) {    
    remoteMowLastState = remoteMowState;
    if (remoteMowState) remoteMowLastTime = timeMicros; else remoteMow = max(0, (rcValue(timeMicros - remoteMowLastTime)+100)/2);
  }  
  if (remoteSwitchState != remoteSwitchLastState) {    
    remoteSwitchLastState = remoteSwitchState;
    if (remoteSwitchState) remoteSwitchLastTime = timeMicros; else remoteSwitch = rcValue(timeMicros - remoteSwitchLastTime);
  }  
}

// ---- motor RPM (interrupt) --------------------------------------------------------------
// mower motor RPM driver
void setMotorMowRPMState(boolean motorMowRpmState){
  if (motorMowRpmState != motorMowRpmLastState) {    
    motorMowRpmLastState = motorMowRpmState;
    if (motorMowRpmLastState) motorMowRpmCounter++;   
  }
}

// --- user settings ---------------------------------------------------------------------

#define MAGIC 16

void deleteUserSettings(){
  int addr = 0;
  eewrite(addr, (short)0); // magic  
}

void loadSaveUserSettings(boolean readflag){
  int addr = 0;
  short magic = MAGIC;
  eereadwrite(readflag, addr, magic); // magic
  eereadwrite(readflag, addr, motorAccel);    
  eereadwrite(readflag, addr, motorSpeedMax);
  eereadwrite(readflag, addr, motorPowerMax);
  eereadwrite(readflag, addr, motorSenseRightZero);
  eereadwrite(readflag, addr, motorSenseLeftZero);
  eereadwrite(readflag, addr, motorRollTimeMax);
  eereadwrite(readflag, addr, motorReverseTime);
  eereadwrite(readflag, addr, motorForwTimeMax);
  eereadwrite(readflag, addr, motorMowSpeedMax);
  eereadwrite(readflag, addr, motorMowPowerMax);
  eereadwrite(readflag, addr, motorMowRPM);
  eereadwrite(readflag, addr, motorMowSenseZero);
  eereadwrite(readflag, addr, motorMowPid);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio1);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio2);  
  eereadwrite(readflag, addr, bumperUse);
  eereadwrite(readflag, addr, sonarUse);
  eereadwrite(readflag, addr, sonarTriggerBelow);
  eereadwrite(readflag, addr, perimeterUse);
  eereadwrite(readflag, addr, perimeterTrackRollTime );
  eereadwrite(readflag, addr, perimeterTrackRevTime);
  eereadwrite(readflag, addr, perimeterPid);
  eereadwrite(readflag, addr, lawnSensorUse);
  eereadwrite(readflag, addr, imuUse);
  eereadwrite(readflag, addr, imuCorrectDir);
  eereadwrite(readflag, addr, imuDirPid);
  eereadwrite(readflag, addr, imuRollPid);    
  eereadwrite(readflag, addr, remoteUse);
  eereadwrite(readflag, addr, batMonitor);
  eereadwrite(readflag, addr, batGoHomeIfBelow);
  eereadwrite(readflag, addr, batSwitchOffIfBelow);  
  eereadwrite(readflag, addr, batFactor);
  eereadwrite(readflag, addr, batSenseZero);
  eereadwrite(readflag, addr, chgSenseZero);
  eereadwrite(readflag, addr, chgFactor);
  eereadwrite(readflag, addr, stationRevTime);
  eereadwrite(readflag, addr, stationRollTime);
  eereadwrite(readflag, addr, stationForwTime);
  eereadwrite(readflag, addr, odometryUse);
  eereadwrite(readflag, addr, odometryTicksPerCm);
  eereadwrite(readflag, addr, odometryWheelBaseCm);
  eereadwrite(readflag, addr, buttonUse);
  eereadwrite(readflag, addr, userSwitch1);
  eereadwrite(readflag, addr, userSwitch2);
  eereadwrite(readflag, addr, userSwitch3);    
  eereadwrite(readflag, addr, timerUse);
  eereadwrite(readflag, addr, timer);  
}

void loadUserSettings(){
  short magic = 0;
  int addr = 0;
  eeread(addr, magic);
  if (magic != MAGIC) return;
  loadSaveUserSettings(true);
}

void saveUserSettings(){
  loadSaveUserSettings(false);
}

// ---- general functionality -----------------------------------------------------

void addErrorCounter(byte errType){   
  if (errorCounter[errType] < 255) errorCounter[errType]++;
  if (errorCounterMax[errType] < 255) errorCounterMax[errType]++;    
}

void checkErrorCounter(){
  if (millis() >= nextTimeErrorCounterReset){
    for (int i=0; i < ERR_ENUM_COUNT; i++) errorCounter[i]=0;
    nextTimeErrorCounterReset = millis() + 30000; // 30 sec
  }  
  if (stateCurr != STATE_OFF) {
   for (int i=0; i < ERR_ENUM_COUNT; i++){
     if (errorCounter[i] > 10) setNextState(STATE_ERROR, 0);
    }
  }
}

// sets wheel motor actuators
// - ensures that the motors (and gears) are not switched to 0% (or 100%) too fast (motorAccel)
// - ensures that motors voltage is not higher than motorSpeedMax
void setMotorSpeed(int pwmLeft, int pwmRight, boolean useAccel){
  // FIXME: we might need to ingore acceleration for PID controllers 
  if (!useAccel){
    motorLeftPWM = pwmLeft;
    motorRightPWM = pwmRight;
  } else {
    double accel = motorAccel * loopsTa;       
    motorLeftPWM = (1.0 - accel) * motorLeftPWM + accel * ((double)pwmLeft);    
    motorRightPWM = (1.0 - accel) * motorRightPWM + accel * ((double)pwmRight);  
  }
  setActuator(ACT_MOTOR_LEFT, min(motorSpeedMax, max(-motorSpeedMax, motorLeftPWM)));
  setActuator(ACT_MOTOR_RIGHT, min(motorSpeedMax, max(-motorSpeedMax, motorRightPWM)));
}

// sets mower motor actuator
// - ensures that the motor is not switched to 100% too fast (motorMowAccel)
// - ensures that the motor voltage is not higher than motorMowSpeedMax
void setMotorMowSpeed(int pwm, boolean useAccel){
  // we need to ignore acceleration for PID control, and we can ignore if speed is lowered (e.g. motor is shut down)
  if ( (!useAccel) || (pwm < motorMowPWM) )
    motorMowPWM = pwm;
  else {
    double accel = motorMowAccel * loopsTa;
    motorMowPWM = (1.0 - accel) * motorMowPWM + accel * ((double)pwm);
  }
  setActuator(ACT_MOTOR_MOW, min(motorMowSpeedMax, max(0, motorMowPWM)));
}

// PID controller: roll robot to heading (requires IMU)
void motorControlImuRoll(){
  imuRollPID.Ta = ((double)(millis() - lastMotorControlTime)) / 1000.0; 			  
  if (imuRollPID.Ta > 0.5) imuRollPID.Ta = 0; // should only happen for the very first call
  imuRollPID.x = distancePI(imuYaw, imuRollHeading) / PI * 180.0;            
  //Serial.println(imuRollPID.x);    
  imuRollPID.Kp = imuRollPid.Kp;
  imuRollPID.Ki = imuRollPid.Ki;
  imuRollPID.Kd = imuRollPid.Kd;
  imuRollPID.w = 0;
  imuRollPID.y_min = -motorSpeedMax;
  imuRollPID.y_max = motorSpeedMax;		
  imuRollPID.max_pwm = motorSpeedMax;
  PIDControl(&imuRollPID);						      
  lastMotorControlTime = millis();
  setMotorSpeed( -imuRollPID.y, 
                +imuRollPID.y,  false);    
}


// PID controller: track perimeter 
void motorControlPerimeter(){  
  //perimeterPID.Ta = ((double)(millis() - lastMotorControlTime)) / 1000.0; 			  
  //if (perimeterPID.Ta > 0.5) perimeterPID.Ta = 0; // should only happen for the very first call
  int  lms = motorLeftPWM;
  int  rms = motorRightPWM;
  if (perimeterLeft < 0) {
    rms += 80.0;
    lms -= 10.0;
  }
  else
  {
    rms -= 10.0;
    lms += 80.0;
  }

  if (rms > 255) rms = 255;
  if (lms > 255) lms = 255;
  if (rms < -100) rms = -100;
  if (lms < -100) lms = -100;  
  setMotorSpeed( lms,  rms, false);      

  /*perimeterPID.Kp = perimeterPid.Kp;
  perimeterPID.Ki = perimeterPid.Ki;
  perimeterPID.Kd = perimeterPid.Kd;
  //perimeterPID.x = perimeterLeft-perimeterRight;    
  if (perimeterLeft < 0) perimeterPID.x = -1;
    else perimeterPID.x = 1; 
  perimeterPID.w = 0;
  perimeterPID.y_min = -motorSpeedMax;
  perimeterPID.y_max = motorSpeedMax;		
  perimeterPID.max_pwm = motorSpeedMax;
  PIDControl(&perimeterPID);						    
  lastMotorControlTime = millis();
  setMotorSpeed( motorLeftPWM  +perimeterPID.y, 
                 motorRightPWM -perimeterPID.y, false);      */
//  setMotorSpeed( motorSpeedMax/2 + perimeterPID.y, 
//                 motorSpeedMax/2 - perimeterPID.y, false);    
}

// PID controller: correct direction during normal driving (requires IMU)
void motorControlImuDir(){
  int leftSpeed = motorLeftSpeed;    
  int rightSpeed = motorRightSpeed;
  imuDirPID.Ta = ((double)(millis() - lastMotorControlTime)) / 1000.0; 			              
  if (imuDirPID.Ta > 0.5) imuDirPID.Ta = 0; // should only happen for the very first call
  imuDirPID.x = distancePI(imuYaw, imuDriveHeading) / PI * 180.0;            
  //Serial.println(imuDirPID.x);    
  imuDirPID.Kp = imuDirPid.Kp;
  imuDirPID.Ki = imuDirPid.Ki;
  imuDirPID.Kd = imuDirPid.Kd;  
  imuDirPID.w = 0;
  imuDirPID.y_min = -motorSpeedMax;
  imuDirPID.y_max = motorSpeedMax;		
  imuDirPID.max_pwm = motorSpeedMax;
  PIDControl(&imuDirPID);	  					      
  lastMotorControlTime = millis();  
  setMotorSpeed( leftSpeed -imuDirPID.y, 
                 rightSpeed +imuDirPID.y, false );
}


void motorControl(){
  //double TA = ((double)(millis() - lastMotorControlTime)) / 1000.0;  
  // normal drive  
  int leftSpeed = motorLeftSpeed;    
  int rightSpeed = motorRightSpeed;
  if (millis() < stateStartTime + 1000) {				
    leftSpeed = rightSpeed = 0; // slow down at state start      
    if (mowPatternCurr != MOW_LANES) imuDriveHeading = imuYaw; // set drive heading    
  }
  setMotorSpeed( leftSpeed, rightSpeed, true );    
}


// motor mow speed controller (slowly adjusts output speed to given input speed)
// input: motorMowEnable, motorMowModulate, motorMowRpm
// output: motorMowPWM
void motorMowControl(){
  double mowSpeed = 0;
  if (!motorMowEnable) {
    mowSpeed = 0;         
    setMotorMowSpeed(mowSpeed, true);
  } 
  else {
    if ((motorMowModulate) && (motorMowRpm != 0)){
      // speed sensor available
      if ((millis() - lastMotorMowControlTime) < 500) return;
      motorMowPID.Ta = ((double)(millis() - lastMotorMowControlTime)) / 1000.0; 			      
      if (motorMowPID.Ta > 0.5) motorMowPID.Ta = 0; // should only happen for the very first call
      motorMowPID.Kp = motorMowPid.Kp;
      motorMowPID.Ki = motorMowPid.Ki;    
      motorMowPID.Kd = motorMowPid.Kd;    
      motorMowPID.x = motorMowRpm;      
      motorMowPID.w = motorMowRPM; // 3300 => 2300
      motorMowPID.y_min = -motorMowSpeedMax;
      motorMowPID.y_max = motorMowSpeedMax;		
      motorMowPID.max_pwm = motorMowSpeedMax;
      PIDControl(&motorMowPID);						    
      mowSpeed = motorMowPWM + motorMowPID.y;            
      setMotorMowSpeed(mowSpeed, false);
    } else {
      // no speed sensor available      
      mowSpeed = motorMowSpeed;
      setMotorMowSpeed(mowSpeed, true);
    }
  }  
  lastMotorMowControlTime = millis();        
}

void beep(int numberOfBeeps, boolean shortbeep = false){
  for (int i=0; i < numberOfBeeps; i++){
    setActuator(ACT_BUZZER, 1200); 
    if (shortbeep) delay(50);
      else delay(500);
    setActuator(ACT_BUZZER, 0); 
  }
}

// set user-defined switches
void setUserSwitches(){
  setActuator(ACT_USER_SW1, userSwitch1);   
  setActuator(ACT_USER_SW2, userSwitch2);     
  setActuator(ACT_USER_SW3, userSwitch3);     
}

void setDefaultTime(){
  datetime.time.hour = 12;
  datetime.time.minute = 0;
  datetime.date.dayOfWeek = 0;
  datetime.date.day = 1;
  datetime.date.month = 1;
  datetime.date.year = 2013;
  timer[0].active = false;
  timer[0].daysOfWeek= B01111110;
  timer[0].startTime.hour = 9;
  timer[0].stopTime.hour = 11;
}

void setup()  {     
  Wire.begin();          
  Serial.begin(BAUDRATE);       
    
  #ifdef USE_PFOD
    initSerialPfod(PFOD_BAUDRATE);  
  #endif
  setDefaultTime();
  
  config();  
  // http://sobisource.com/arduino-mega-pwm-pin-and-frequency-timer-control/
  #ifdef __AVR__
    TCCR3B = (TCCR3B & 0xF8) | 1;    // set PWM frequency 31 Khz (pin2,3,5) 
  #endif
  setMotorSpeed(0, 0, false);
  loadUserSettings();
  setUserSwitches();
  
  imu.init();
  gps.init();
    
  if (!buttonUse){
    // robot has no ON/OFF button => start immediately
    setNextState(STATE_FORWARD,0);
  }  
    
  stateStartTime = millis();  
  setActuator(ACT_BUZZER, 1200);
  delay(100);
  setActuator(ACT_BUZZER, 0);
  delay(900);  
  Serial.println(F("START"));  
  Serial.print(F("Ardumower v"));
  Serial.println(verToString(VER));
  Serial.println(F("press..."));
  Serial.println(F("  d for menu"));    
  Serial.println(F("  v to change console output (sensor counters, values, perimeter etc.)"));    
  Serial.println(consoleModeName[consoleMode]);
} 


void printRemote(){
  Serial.print("RC ");    
  Serial.print(remoteSwitch);  
  Serial.print(",");      
  Serial.print(remoteSteer);
  Serial.print(",");    
  Serial.print(remoteSpeed);    
  Serial.print(",");        
  Serial.println(remoteMow);            
}

void printOdometry(){
  Serial2.print("ODO,");
  Serial2.print(odometryX);
  Serial2.print(",");
  Serial2.println(odometryY);  
  Serial.print("ODO,");
  Serial.print(odometryX);
  Serial.print(",");
  Serial.println(odometryY);  
}

void printInfo(Stream &s){
  /*Serial.print(millis()/1000);
  Serial.print(",");
  Serial.print(motorMowRPM);
  Serial.print(",");
  Serial.print(motorMowRpm);
  Serial.print(",");
  Serial.println(motorMowPWM);
  return;*/
  //Serial.println(time2str(datetime.time));
  Streamprint(s, "t%6u ", (millis()-stateStartTime)/1000);  
  Streamprint(s, "l%3u ", loopsPerSec);  
  //Streamprint(s, "r%4u ", freeRam());  
  Streamprint(s, "v%1d ", consoleMode);			    
  Streamprint(s, "%4s ", stateName[stateCurr]);			    
  if (consoleMode == CONSOLE_PERIMETER){
    Streamprint(s, "sig min %4d max %4d avg %4d  mag %5d  in %2d  cnt %4d  on %2d\r\n", 
      (int)Perimeter.getSignalMin(), (int)Perimeter.getSignalMax(), (int)Perimeter.getSignalAvg(),
      perimeterLeft, (int)perimeterLeftState, perimeterLeftCounter, (int)!Perimeter.signalTimedOut());
  } else {  
    if (odometryUse) Streamprint(s, "odo %4d %4d ", (int)odometryLeft, (int)odometryRight);   
    Streamprint(s, "spd %4d %4d %4d ", (int)motorLeftSpeed, (int)motorRightSpeed, (int)motorMowRpm);
    if (consoleMode == CONSOLE_SENSOR_VALUES){
      // sensor values
      Streamprint(s, "sen %4d %4d %4d ", (int)motorLeftSense, (int)motorRightSense, (int)motorMowSense);
      Streamprint(s, "bum %4d %4d ", bumperLeft, bumperRight);
      Streamprint(s, "son %4d %4d %4d ", sonarDistLeft, sonarDistCenter, sonarDistRight);
      Streamprint(s, "pit %3d ", (int)(imuPitch/PI*180.0));
      Streamprint(s, "rol %3d ", (int)(imuRoll/PI*180.0));
      Streamprint(s, "yaw %3d ", (int)(imuYaw/PI*180.0));  
      if (perimeterUse) Streamprint(s, "per %3d ", (int)perimeterLeftState);              
      if (lawnSensorUse) Streamprint(s, "lawn %3d %3d ", (int)lawnSensorFront, (int)lawnSensorBack);
    } else {
      // sensor counters
      Streamprint(s, "sen %4d %4d %4d ", motorLeftSenseCounter, motorRightSenseCounter, motorMowSenseCounter);
      Streamprint(s, "bum %4d %4d ", bumperLeftCounter, bumperRightCounter);
      Streamprint(s, "son %3d ", sonarDistCounter);
      Streamprint(s, "pit %3d ", (int)(imuPitch/PI*180.0));
      Streamprint(s, "rol %3d ", (int)(imuRoll/PI*180.0));
      Streamprint(s, "yaw %3d ", (int)(imuYaw/PI*180.0));  
      //Streamprint(s, "per %3d ", perimeterLeft);          
      if (perimeterUse) Streamprint(s, "per %3d ", perimeterLeftCounter);                  
      if (lawnSensorUse) Streamprint(s, "lawn %3d ", lawnSensorCounter);
      if (gpsUse) Streamprint(s, "gps %2d ", (int)gps.satellites());
    }  
    Streamprint(s, "bat %2d.%01d ", (int)batVoltage, (int)((batVoltage *10) - ((int)batVoltage*10)) );       
    Streamprint(s, "chg %2d.%01d %2d.%01d ", 
      (int)chgVoltage, (int)((chgVoltage *10) - ((int)chgVoltage*10)),
      (int)chgCurrent, (int)((abs(chgCurrent) *10) - ((int)abs(chgCurrent)*10))    
    );    
    Streamprint(s, "imu%3d ", imu.getCallCounter());  
    Streamprint(s, "adc%3d ", ADCMan.getCapturedChannels());  
    Streamprint(s, "%s\r\n", configName);
  }
}

void printMenu(){  
  Serial.println();
  Serial.println("1=test motors");
  Serial.println("2=test odometry");
  Serial.println("3=setup BT module config (quick baudscan/recommended)");
  Serial.println("4=setup BT module config (extensive baudscan)");
  Serial.println("0=exit");  
  Serial.println();
}

void delayInfo(int ms){
  unsigned long endtime = millis() +ms;
  while (millis() < endtime){
    readSensors();
    motorControl();
    printInfo(Serial);
    delay(1000);
  }
}

void testOdometry(){
  char ch;
  int lastLeft = 0;
  int lastRight = 0;
  setMotorSpeed(motorSpeedMax/5, motorSpeedMax/5, false);
  while (true){ 
    if ((odometryLeft != lastLeft) || (odometryRight != lastRight)) {
      Serial.print("left=");
      Serial.print(odometryLeft);
      Serial.print("  right=");
      Serial.println(odometryRight);              
      lastLeft = odometryLeft;
      lastRight = odometryRight;
    }
    delay(100);
    if (Serial.available() > 0){
      ch = (char)Serial.read();      
      if (ch == '0') break;
    }
  };
  setMotorSpeed(0, 0, false);            
}

void testMotors(){
  Serial.println("testing left motor (forward) half speed...");    
  setMotorSpeed(motorSpeedMax/2, 0, false);
  delayInfo(5000);
  setMotorSpeed(0, 0, false);
  Serial.println("testing left motor (reverse) full speed...");
  delay(1000);          
  setMotorSpeed(-motorSpeedMax, 0, false);
  delayInfo(5000);          
  Serial.println("testing right motor (forward) half speed...");
  setMotorSpeed(0, motorSpeedMax/2, false);
  delayInfo(5000);
  setMotorSpeed(0, 0, false);
  Serial.println("testing right motor (reverse) full speed...");
  delay(1000);          
  setMotorSpeed(0, -motorSpeedMax, false);
  delayInfo(5000);
  setMotorSpeed(0, 0, false);            
}

void menu(){  
  char ch;
  BluetoothConfig bt;
  printMenu();  
  while(true){    
    if (Serial.available() > 0) {
      ch = (char)Serial.read();            
      switch (ch){
        case '0': 
          return;           
        case '1':         
          testMotors();
          printMenu();
          break;        
        case '2':
          testOdometry();
          printMenu();
          break;
        case '3':
          bt.setParams("Ardumower", 1234, PFOD_BAUDRATE, true);
          printMenu();
          break;
        case '4':          
          bt.setParams("Ardumower", 1234, PFOD_BAUDRATE, false);
          printMenu();
          break;
      }      
    }
    delay(100);
  }  
}

void readSerial() {
  // serial input
  if (Serial.available() > 0) {
     char ch = (char)Serial.read();
     switch (ch){
       case 'd': 
         menu(); // menu
         break;
       case 'v': 
         consoleMode = (consoleMode +1) % 3;
         Serial.println(consoleModeName[consoleMode]);
         break; 
       case 'h':
         setNextState(STATE_PERI_FIND, 0); // press 'h' to drive home
         break; 
       case 't':
         setNextState(STATE_PERI_TRACK, 0); // press 'p' to track perimeter
         break;
       case 'l':
         bumperLeft = true; // press 'l' to simulate left bumper
         bumperLeftCounter++;
         break; 
       case 'r':
         bumperRight = true; // press 'r' to simulate right bumper
         bumperRightCounter++;
         break; 
       case 's':
         lawnSensor = true; // press 's' to simulate lawn sensor
         lawnSensorCounter++;
         break; 
       case 'm':
         motorMowEnable = !motorMowEnable; // press 'm' to toggle mower motor
         break;
       case 'c':
         setNextState(STATE_CHARGE, 0); // press 'c' to simulate charging
         break;
       case '+':
         setNextState(STATE_ROLL_WAIT, 0); // press '+' to rotate 90 degrees (IMU)
         imuRollHeading = scalePI(imuRollHeading + PI/2);
         break;
       case '-':
         setNextState(STATE_ROLL_WAIT, 0); // press '+' to rotate 90 degrees (IMU)
         imuRollHeading = scalePI(imuRollHeading - PI/2);
         break;
       case 'i':
         // press 'i' to toggle imuUse
         imuUse = !imuUse;
         break;
       case '3':
         setNextState(STATE_REMOTE,0); // press '3' to activate model RC         
         break;          
       case '0':
         // press '0' for OFF
         setNextState(STATE_OFF,0);                             
         break;
       case '1':       
         // press '1' for Automode         
         motorMowEnable = true;
         //motorMowModulate = false;                                           
         setNextState(STATE_FORWARD,0);          
         break; 
     }
  }    
}

void checkButton(){
  boolean buttonPressed = (readSensor(SEN_BUTTON) == LOW);    
  if ( ((!buttonPressed) && (buttonCounter > 0)) || ((buttonPressed) && (millis() >= nextTimeButton)) ) {                
    nextTimeButton = millis() + 1000;
    if (buttonPressed){
      // ON/OFF button pressed                                                
      beep(1);
      buttonCounter++;
    } 
    else { 
      // ON/OFF button released          
      if ((stateCurr != STATE_OFF) || (stateCurr == STATE_ERROR)) {
        setNextState(STATE_OFF, 0);
      } else if (buttonCounter == 2){
        motorMowEnable = true;
        mowPatternCurr = MOW_BIDIR;
        setNextState(STATE_FORWARD, 0);                
      } else if (buttonCounter == 3){      
        // start remote control mode
        setNextState(STATE_REMOTE, 0);
      } else if (buttonCounter == 4){
        // start normal without mowing
        motorMowEnable = false;        
        setNextState(STATE_FORWARD,0);           
      } else if (buttonCounter == 7){
        // start normal with mowing in lanes
        motorMowEnable = true;
        //motorMowModulate = true;
        mowPatternCurr = MOW_LANES;
        setNextState(STATE_FORWARD, 0);                
      } else if (buttonCounter == 6){
        // track perimeter
        setNextState(STATE_PERI_TRACK, 0);        
      } else if (buttonCounter == 5){
        // drive home
        setNextState(STATE_PERI_FIND, 0);        
      } else if (buttonCounter == 1){
        // start normal with mowing        
        motorMowEnable = true;
        //motorMowModulate = true;                     
        mowPatternCurr = MOW_RANDOM;   
        setNextState(STATE_FORWARD, 0);                
      } 
      
      buttonCounter = 0;                 
    }       
  }
}

void readSensors(){
  if ((odometryUse) && (millis() >= nextTimeOdometry)) {        
    nextTimeOdometry = millis() + 50;    
    calcOdometry();
  }    
  if (millis() >= nextTimeMotorSense){    
    nextTimeMotorSense = millis() +  50;
    double accel = 0.05;
    motorRightSense = motorRightSense * (1.0-accel) + ((double)abs(readSensor(SEN_MOTOR_RIGHT))) * accel;   
    motorLeftSense  = motorLeftSense  * (1.0-accel) + ((double)abs(readSensor(SEN_MOTOR_LEFT))) * accel;    
    motorMowSense   = motorMowSense   * (1.0-accel) + ((double)abs(readSensor(SEN_MOTOR_MOW))) * accel;
   
    if (batVoltage > 8){
    motorRightSense = motorRightSense * batVoltage /100; 
    motorLeftSense  = motorLeftSense  * batVoltage /100;
    motorMowSense   = motorMowSense   * batVoltage /100;
    }
    else{
    motorRightSense = motorRightSense * batFull /100; 
    motorLeftSense  = motorLeftSense  * batFull /100;
    motorMowSense   = motorMowSense   * batFull /100;
    }
  
    if ((millis() - lastMotorMowRpmTime) >= 500){                  
      motorMowRpm = readSensor(SEN_MOTOR_MOW_RPM);    
      if ((motorMowRpm == 0) && (motorMowRpmCounter != 0)){
        // rpm may be updated via interrupt
        motorMowRpm = (int) ((((double)motorMowRpmCounter) / ((double)(millis() - lastMotorMowRpmTime))) * 60000.0);
        motorMowRpmCounter = 0;        
      }       
      lastMotorMowRpmTime = millis();     
    }
  }   
  if ((perimeterUse) && (millis() >= nextTimePerimeter)){    
    nextTimePerimeter = millis() +  50; // 50
    //perimeterRight = readSensor(SEN_PERIM_RIGHT) + readSensor(SEN_PERIM_RIGHT_EXTRA);
    perimeterLeft = readSensor(SEN_PERIM_LEFT) + readSensor(SEN_PERIM_LEFT_EXTRA);        
    if ((!Perimeter.isInside()) && (perimeterLeftState)){      
      perimeterLeftCounter++;
    }
    perimeterLeftState = Perimeter.isInside();
    if (perimeterLeftState) digitalWrite(pinLED, HIGH);    
      else digitalWrite(pinLED, LOW);      
    if (Perimeter.signalTimedOut()){
      if ( (stateCurr != STATE_OFF) && (stateCurr != STATE_ERROR) && (stateCurr != STATE_CHARGE) ){
        Serial.println("Error: Perimeter timeout");
        addErrorCounter(ERR_PERIMETER_TIMEOUT);
        setNextState(STATE_ERROR,0);
      }
    }
  } 
  if ((lawnSensorUse) && (millis() >= nextTimeLawnSensor)){    
    nextTimeLawnSensor = millis() + 100;               
    double accel = 0.03;
    lawnSensorFront = (1.0-accel) * lawnSensorFront + accel * ((double)readSensor(SEN_LAWN_FRONT));
    lawnSensorBack  = (1.0-accel) * lawnSensorBack  + accel * ((double)readSensor(SEN_LAWN_BACK));        
  }
 if ((lawnSensorUse) && (millis() >= nextTimeLawnSensorCheck)){          
    nextTimeLawnSensorCheck = millis() + 2000;               
    double deltaFront = lawnSensorFront/lawnSensorFrontOld * 100.0;    
    double deltaBack = lawnSensorBack/lawnSensorBackOld * 100.0;        
    if ((deltaFront <= 95) || (deltaBack <= 95)){
      Serial.print("LAWN ");
      Serial.print(deltaFront);
      Serial.print(",");
      Serial.println(deltaBack);
      lawnSensorCounter++;
      lawnSensor=true;
    }
    lawnSensorFrontOld = lawnSensorFront;
    lawnSensorBackOld  = lawnSensorBack;
  }
  if ((sonarUse) && (millis() >= nextTimeSonar)){
    nextTimeSonar = millis() + 500;   
    sonarDistRight = readSensor(SEN_SONAR_RIGHT);    
    sonarDistLeft = readSensor(SEN_SONAR_LEFT);    
    sonarDistCenter = readSensor(SEN_SONAR_CENTER);    
  }
  if (millis() >= nextTimeBumper){    
    nextTimeBumper = millis() + 100;               
    if (bumperUse){
      if (readSensor(SEN_BUMPER_LEFT) == 0) {
        bumperLeftCounter++;
        bumperLeft=true;
      }
      if (readSensor(SEN_BUMPER_RIGHT) == 0) {
        bumperRightCounter++;
        bumperRight=true;
      } 
    }
  }    
  if ((timerUse) && (millis() >= nextTimeRTC)) {
    // read RTC
    nextTimeRTC = millis() + 1000;
    readSensor(SEN_RTC);            
  }
  
  if ((imuUse) && (millis() >= nextTimeIMU)) {
    // read compass
    nextTimeIMU = millis() + 20;   // 200
    //readSensor(SEN_IMU);                
    float ypr[3];
    imu.getEulerRad(ypr);
    if (imu.getErrorCounter()>0) {
      addErrorCounter(ERR_IMU_COMM);
      Serial.println("IMU comm error");    
    }
    imuYaw=ypr[0]; imuPitch=ypr[1]; imuRoll=ypr[2]; 
    //imuComX=comxyz[0]; imuComY=comxyz[1]; imuComZ=comxyz[2];
  }  
  if (millis() >= nextTimeBattery){
    // read battery
    nextTimeBattery = millis() + 100;       
    if ((abs(chgCurrent) > 0.04) && (chgVoltage > 5)){
      // charging
      batCapacity += (chgCurrent / 36.0);
    }
    // convert to double  
    double batvolt = ((double)((int)(readSensor(SEN_BAT_VOLTAGE) / 10))) / 10.0;
    double chgvolt = ((double)((int)(readSensor(SEN_CHG_VOLTAGE) / 10))) / 10.0;  
    double current = ((double)((int)(readSensor(SEN_CHG_CURRENT) / 10))) / 10.0;  
    // low-pass filter
    double accel = 0.01;
    if (abs(batVoltage-batvolt)>5)   batVoltage = batvolt; else batVoltage = (1.0-accel) * batVoltage + accel * batvolt;
    if (abs(chgVoltage-chgvolt)>5)   chgVoltage = chgvolt; else chgVoltage = (1.0-accel) * chgVoltage + accel * chgvolt;
    if (abs(chgCurrent-current)>0.4) chgCurrent = current; else chgCurrent = (1.0-accel) * chgCurrent + accel * current;  
    //batVoltage = batVolt
    //chgVoltage = chgvolt;
    //chgCurrent = current;        
  }    
}

void setDefaults(){
  motorLeftSpeed = motorRightSpeed = 0;    
  motorMowEnable = false;                
}


// called *ONCE* to set to a *NEW* state
void setNextState(byte stateNew, byte dir){
  unsigned long stateTime = millis() - stateStartTime;
  if (stateNew == stateCurr) return;
  // state correction  
  if (stateNew == STATE_FORWARD) {    
    if ((stateCurr == STATE_CHARGE_REV) ||(stateCurr == STATE_CHARGE_ROLL)) return;  
    if (stateCurr == STATE_CHARGE) {
      stateNew = STATE_CHARGE_REV;   
      motorMowEnable = false;
    } 
  }  
  // evaluate new state
  stateNext = stateNew;
  rollDir = dir;
  if (stateNew == STATE_CHARGE_REV){
    motorLeftSpeed = motorRightSpeed = -motorSpeedMax;                    
    stateEndTime = millis() + stationRevTime;                     
  } else if (stateNew == STATE_CHARGE_ROLL){
    motorLeftSpeed = motorSpeedMax;
    motorRightSpeed = -motorLeftSpeed;						      
    stateEndTime = millis() + stationRollTime;                     
  } else if (stateNew == STATE_CHARGE_FORW){
    motorLeftSpeed = motorRightSpeed = motorSpeedMax;      
    motorMowEnable = true;    
    stateEndTime = millis() + stationForwTime;                     
  } 
  else if (stateNew == STATE_PERI_ROLL) {    
    stateEndTime = millis() + perimeterTrackRollTime;                     
    if (dir == RIGHT){
	motorLeftSpeed = motorSpeedMax/2;
	motorRightSpeed = -motorLeftSpeed;						
      } else {
	motorRightSpeed = motorSpeedMax/2;
	motorLeftSpeed = -motorRightSpeed;	
      }
  } if (stateNew == STATE_PERI_REV) {
    motorLeftSpeed = motorRightSpeed = -motorSpeedMax/2;                    
    stateEndTime = millis() + perimeterTrackRevTime;                     
  }
  else if (stateNew == STATE_FORWARD){      
    motorLeftSpeed = motorRightSpeed = motorSpeedMax;              
  } 
  else if (stateNew == STATE_REVERSE)  {
    motorLeftSpeed = motorRightSpeed = -motorSpeedMax;                    
    stateEndTime = millis() + motorReverseTime;                     
  }   
  else if (stateNew == STATE_ROLL) {                  
      imuDriveHeading = scalePI(imuDriveHeading + PI); // toggle heading 180 degree (IMU)
      if (imuRollDir == LEFT){
        imuRollHeading = scalePI(imuDriveHeading - PI/20);        
        imuRollDir = RIGHT;
      } else {
        imuRollHeading = scalePI(imuDriveHeading + PI/20);        
        imuRollDir = LEFT;
      }      
      stateEndTime = millis() + rand() % motorRollTimeMax/2 + motorRollTimeMax/2;               
      if (dir == RIGHT){
	motorLeftSpeed = motorSpeedMax;
	motorRightSpeed = -motorLeftSpeed;						
      } else {
	motorRightSpeed = motorSpeedMax;
	motorLeftSpeed = -motorRightSpeed;	
      }      
  }  
  if (stateNew == STATE_REMOTE){
    motorMowEnable = true;
    //motorMowModulate = false;              
  } 
  if (stateNew == STATE_CHARGE){
    setDefaults();        
  }
  if (stateNew == STATE_OFF){
    setDefaults();        
  }  
  if (stateNew == STATE_ERROR){
    motorMowEnable = false;    
    motorLeftSpeed = motorRightSpeed = 0;    
  }
  if (stateNew == STATE_PERI_FIND){
    // find perimeter  => drive half speed      
    motorLeftSpeed = motorRightSpeed = motorSpeedMax / 2;    
    motorMowEnable = false;    
  }
  if (stateNew == STATE_PERI_TRACK){        
    motorMowEnable = false;    
    //beep(6);
  }   
  if (stateNew != STATE_REMOTE){
    motorMowSpeed = motorMowSpeedMax;
  }
 
  sonarObstacleTimeout = 0;
  // state has changed    
  stateStartTime = millis();
  stateLast = stateCurr;
  stateCurr = stateNext;    
  printInfo(Serial);          
}

// check (low) battery
void checkBattery(){
  if (batMonitor){
    if ((batVoltage < batGoHomeIfBelow) && (stateCurr !=STATE_OFF)) {
      beep(2, true);      
      setNextState(STATE_PERI_FIND, 0);
    } else if (batVoltage < batSwitchOffIfBelow) {
      beep(2, true);      
      setNextState(STATE_OFF, 0);
    }
  }
}

// check timer
void checkTimer(){
  if (millis() < nextTimeTimer) return;
  nextTimeTimer = millis() + 60000;
  if (gpsUse){
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age; 
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    if (age != GPS::GPS_INVALID_AGE)
    {
      datetime.date.dayOfWeek = getDayOfWeek(month, day, year, 1);      
      datetime.date.day = day;
      datetime.date.month = month;
      datetime.date.year = year;
      datetime.time.hour = hour;
      datetime.time.minute = minute;
      setActuator(ACT_RTC, 0);            
    }      
  }
  boolean stopTimerTriggered = true;
  if (timerUse){    
    for (int i=0; i < MAX_TIMERS; i++){
      if (timer[i].active){
        if  ( (timer[i].daysOfWeek & (1 << datetime.date.dayOfWeek)) != 0) {
          int startmin = time2minutes(timer[i].startTime);
          int stopmin =  time2minutes(timer[i].stopTime);
          int currmin =  time2minutes(datetime.time);
          if ((currmin >= startmin) && (currmin < stopmin)){
            // start timer triggered
            stopTimerTriggered = false;
            if (stateCurr == STATE_OFF){
              Serial.println("timer start triggered");
              motorMowEnable = true;
              setNextState(STATE_FORWARD, 0);
            } 
          }           
        }
      }
    }
    if (stopTimerTriggered){
      if (stateCurr == STATE_FORWARD){
        Serial.println("timer stop triggered");
        setNextState(STATE_PERI_FIND, 0);
      } 
    }
  }
}

void reverseOrBidir(byte aRollDir){
  if (mowPatternCurr == MOW_BIDIR){
    if (stateCurr == STATE_FORWARD) {      
      setNextState(STATE_REVERSE, RIGHT);     
    } else if (stateCurr == STATE_REVERSE) {
      setNextState(STATE_FORWARD, LEFT);
    }
  } else setNextState(STATE_REVERSE, aRollDir);
}

// check motor current
void checkCurrent(){
  if (motorMowSense >= motorMowPowerMax){
    setActuator(ACT_MOTOR_MOW, 0);
    motorMowSenseCounter++;
    motorMowSenseErrorCounter++;
    if (motorMowSenseErrorCounter > 3){
      Serial.println("Error: Motor mow current");
      addErrorCounter(ERR_MOW_SENSE);
      setNextState(STATE_ERROR, 0);
      return;
    }
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
      else reverseOrBidir(RIGHT);        
  }  
    
  if (motorLeftSense >=motorPowerMax){      
    if (millis() > stateStartTime + 3000) {				  
      //beep(1);
      motorLeftSenseCounter++;
      reverseOrBidir(RIGHT);
    }
  } else if (motorRightSense >= motorPowerMax){       
     if (millis() > stateStartTime + 3000) {
       //beep(1);				         
       motorRightSenseCounter++;
       reverseOrBidir(LEFT);
     }
  }  
}

// check bumpers
void checkBumpers(){
  if ((mowPatternCurr == MOW_BIDIR) && (millis() < stateStartTime + 4000)) return;

  if ((bumperLeft || bumperRight)) {    
      if (bumperLeft) {
        reverseOrBidir(RIGHT);          
      } else {
        reverseOrBidir(LEFT);
      }    
  }  
}

// check bumpers while tracking perimeter
void checkBumpersPerimeter(){
  if ((bumperLeft || bumperRight)) {    
    if ((bumperLeft) || (stateCurr == STATE_PERI_TRACK)) {
      setNextState(STATE_PERI_REV, RIGHT);          
    } else {
      setNextState(STATE_PERI_REV, LEFT);
    }
  }
}

// check perimeter as a boundary
void checkPerimeterBoundary(){
  if (mowPatternCurr == MOW_BIDIR){
    if ((millis() < stateStartTime + 3000)) return;    
    if (!perimeterLeftState) {
      if ((rand() % 2) == 0){      
        reverseOrBidir(LEFT);
      } else {
        reverseOrBidir(RIGHT);
      }     
    }
  } else {  
    if (stateCurr == STATE_FORWARD){
      //if ((millis() < stateStartTime + 2500)) return;    
      if (!perimeterLeftState) {
      //  if ((rand() % 2) == 0){      
          reverseOrBidir(LEFT);
      //  }// else {
        //  reverseOrBidir(RIGHT);
      //  }
      }
    } 
  }
}

// check perimeter while finding it
void checkPerimeterFind(){
  if (stateCurr == STATE_PERI_FIND){
    if (perimeterLeft > 0) setNextState(STATE_PERI_TRACK, 0);    
  }
}

 
// check lawn 
void checkLawn(){
  if ( (lawnSensor) && (millis() > stateStartTime + 3000) ) {      
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
       else reverseOrBidir(RIGHT);        
  } else lawnSensor = false;
}


// check sonar
void checkSonar(){
  if ((mowPatternCurr == MOW_BIDIR) && (millis() < stateStartTime + 4000)) return;
  
  // slow down motor wheel speed near obstacles   
  if (     (stateCurr == STATE_FORWARD) 
          || (  (mowPatternCurr == MOW_BIDIR) && ((stateCurr == STATE_FORWARD) || (stateCurr == STATE_REVERSE))  )  
     ){
        if (sonarObstacleTimeout == 0) {
          if (     ((NO_ECHO != sonarDistCenter) && (sonarDistCenter < sonarTriggerBelow*2)) 
               ||  ((NO_ECHO != sonarDistRight) && (sonarDistRight < sonarTriggerBelow*2)) 
               ||  ((NO_ECHO != sonarDistLeft) && (sonarDistLeft < sonarTriggerBelow*2))  ) {    
              //Serial.println("sonar slow down");
              motorLeftSpeed /= 2;
              motorRightSpeed /= 2;
              sonarObstacleTimeout = millis() + 7000;
          }
        } else if ((sonarObstacleTimeout != 0) && (millis() > sonarObstacleTimeout)) {
          //Serial.println("no sonar");
          sonarObstacleTimeout = 0;
          motorLeftSpeed *= 2;
          motorRightSpeed *= 2;
        }
    }  
  
  if ((sonarDistCenter != NO_ECHO) && (sonarDistCenter < sonarTriggerBelow)){
    sonarDistCounter++;     
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
      else reverseOrBidir(RIGHT);    
  }
  if ((sonarDistRight != NO_ECHO) && (sonarDistRight < sonarTriggerBelow)){
    sonarDistCounter++;     
    reverseOrBidir(LEFT);
  }
  if ((sonarDistLeft != NO_ECHO) && (sonarDistLeft < sonarTriggerBelow)){
    sonarDistCounter++;     
    reverseOrBidir(RIGHT);
  }
}


// check IMU (tilt)
void checkTilt(){
  int pitchAngle = (imuPitch/PI*180.0);
  int rollAngle  = (imuRoll/PI*180.0);
  if ( (stateCurr != STATE_OFF) && (stateCurr != STATE_ERROR) && (stateCurr != STATE_CHARGE) ){
    if ( (abs(pitchAngle) > 40) || (abs(rollAngle) > 40) ){
      Serial.println("Error: IMU tilt");
      addErrorCounter(ERR_IMU_TILT);
      setNextState(STATE_ERROR,0);
    }
  }
  if (stateCurr == STATE_ERROR){
    //if ( (abs(pitchAngle) < 40) && (abs(rollAngle) < 40) ) setNextState(STATE_FORWARD,0);
  }
}


// calculate map position by odometry sensors
void calcOdometry(){
  static int lastOdoLeft = 0;
  static int lastOdoRight = 0;
  int odoLeft = odometryLeft;
  int odoRight = odometryRight;
  int ticksLeft = odoLeft - lastOdoLeft;
  int ticksRight = odoRight - lastOdoRight;
  lastOdoLeft = odoLeft;
  lastOdoRight = odoRight;    
  double left_cm = ((double)ticksLeft) / ((double)odometryTicksPerCm);
  double right_cm = ((double)ticksRight) / ((double)odometryTicksPerCm);  
  double avg_cm  = (left_cm + right_cm) / 2.0;
  double wheel_theta = (left_cm - right_cm) / ((double)odometryWheelBaseCm);
  odometryTheta += wheel_theta;
  //odometryTheta -= (double)((int)(odometryTheta/(2*PI)))*2*PI;
  //if (odometryTheta < -PI) odometryTheta += 2*PI; 
  //  else if (odometryTheta > PI) odometryTheta -= 2*PI;
  if (imuUse){
    odometryX += avg_cm * sin(imuYaw); 
    odometryY += avg_cm * cos(imuYaw); 
  } else {
    odometryX += avg_cm * sin(odometryTheta); 
    odometryY += avg_cm * cos(odometryTheta); 
 }
}


void loop()  {     
  unsigned long stateTime = millis() - stateStartTime;
  int steer;
  
  readSerial(); 
  #ifdef USE_PFOD
    readSerialPfod();    
  #endif
  readSensors();    

  if ((odometryUse) && (millis() >= nextTimeOdometryInfo)){
    nextTimeOdometryInfo = millis() + 300;
    //printOdometry();        
  }
  
  if (millis() >= nextTimePfodLoop){
    nextTimePfodLoop = millis() + 200;
    pfodLoop();        
  }
      
  if (millis() >= nextTimeInfo) {        
    nextTimeInfo = millis() + 1000;    
    ledState = ~ledState;    
    /*if (ledState) setActuator(ACT_LED, HIGH);
      else setActuator(ACT_LED, LOW);        */
    printInfo(Serial);            
    checkTilt(); 
    //checkErrorCounter();    
    //pfodLoop();    
    if (stateCurr == STATE_REMOTE) printRemote();    
    loopsPerSec = loopsPerSecCounter;
    if (loopsPerSec > 0) loopsTa = 1000.0 / ((double)loopsPerSec);    
    loopsPerSecCounter = 0;    
  }
      
  // state machine - things to do *PERMANENTLY* for current state
  switch (stateCurr) {
    case STATE_ERROR:
      // fatal-error
      if (millis() >= nextTimeErrorBeep){
        nextTimeErrorBeep = millis() + 300;
        beep(1, true);
      }
      //delay(100);                        
      break;
    case STATE_OFF:
      // robot is turned off      
      checkTimer();
      checkBattery();
      if (batMonitor){
        if (chgVoltage > 5.0){
          beep(2, true);      
          setNextState(STATE_CHARGE, 0);
        }
      }
      imuDriveHeading = imuYaw;
      break;
    case STATE_REMOTE:
      // remote control mode (RC)
      //if (remoteSwitch > 50) setNextState(STATE_FORWARD, 0);
      steer = ((double)motorSpeedMax/2) * (((double)remoteSteer)/100.0);
      if (remoteSpeed < 0) steer *= -1;
      motorLeftSpeed  = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) - steer; 
      motorRightSpeed = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) + steer; 
      motorLeftSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorLeftSpeed));
      motorRightSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorRightSpeed));
      motorMowSpeed = ((double)motorMowSpeedMax) * (((double)remoteMow)/100.0);      
      break;
    case STATE_MANUAL:
      break;
    case STATE_FORWARD:
      // driving forward            
      if (mowPatternCurr == MOW_BIDIR){
        double ratio = motorBiDirSpeedRatio1;
        if (stateTime > 4000) ratio = motorBiDirSpeedRatio2;
        if (rollDir == RIGHT) motorRightSpeed = ((double)motorLeftSpeed) * ratio;
          else motorLeftSpeed = ((double)motorRightSpeed) * ratio;                            
      }       
      checkErrorCounter();    
      checkTimer();
      checkCurrent();            
      checkBumpers();
      checkSonar();             
      checkBattery();
      checkPerimeterBoundary();      
      if (lawnSensorUse) checkLawn();      
      if (stateTime > motorForwTimeMax){ 
        // timeout 
        motorMowSenseErrorCounter = 0;
        if (rollDir == RIGHT) setNextState(STATE_REVERSE, LEFT); // toggle roll dir
          else setNextState(STATE_REVERSE, RIGHT);
      }
      break;
    case STATE_ROLL:
      // making a roll (left/right)            
      if (mowPatternCurr == MOW_LANES){
        if (abs(distancePI(imuYaw, imuRollHeading)) < PI/36) setNextState(STATE_FORWARD,0);				        
      } else {
        if (millis() >= stateEndTime) {
          setNextState(STATE_FORWARD,0);				          
        }        
      }
      break;
    case STATE_ROLL_WAIT:
      // making a roll (left/right)            
      //if (abs(distancePI(imuYaw, imuRollHeading)) < PI/36) setNextState(STATE_OFF,0);				
      break;
    case STATE_CIRCLE:
      // driving circles
      break;      
    case STATE_REVERSE:
      // driving reverse      
      if (mowPatternCurr == MOW_BIDIR){
        double ratio = motorBiDirSpeedRatio1;
        if (stateTime > 4000) ratio = motorBiDirSpeedRatio2;
        if (rollDir == RIGHT) motorRightSpeed = ((double)motorLeftSpeed) * ratio;
          else motorLeftSpeed = ((double)motorRightSpeed) * ratio;                              
        checkErrorCounter();    
        checkTimer();
        checkCurrent();            
        checkBumpers();
        checkSonar();             
        checkBattery();
        checkPerimeterBoundary();      
        if (lawnSensorUse) checkLawn();      
        if (stateTime > motorForwTimeMax){ 
          // timeout 
          if (rollDir == RIGHT) setNextState(STATE_FORWARD, LEFT); // toggle roll dir
            else setNextState(STATE_FORWARD, RIGHT);
        }        
      } else {        
        if (millis() >= stateEndTime) {
          setNextState(STATE_ROLL, rollDir);				                         
        }
      }
      break;
    case STATE_PERI_ROLL:
      // perimeter tracking roll
      if (millis() >= stateEndTime) setNextState(STATE_PERI_FIND,0);				
      break;
    case STATE_PERI_REV:
      // perimeter tracking reverse
      if (millis() >= stateEndTime) setNextState(STATE_PERI_ROLL, rollDir);				               
      break;
    case STATE_PERI_FIND:
      // find perimeter
      //checkCurrent();            
      checkBumpersPerimeter();
      checkSonar();                   
      checkPerimeterFind();
      break;
    case STATE_PERI_TRACK:
      // track perimeter
      //checkCurrent();                  
      checkBumpersPerimeter();
      //checkSonar();                   
      if (batMonitor){
        if (chgVoltage > 5.0){ 
          setNextState(STATE_CHARGE, 0);
        }
      }
      break;
    case STATE_CHARGE:
      // waiting until charging completed      
      break;      
    case STATE_CHARGE_REV:
      // charging: drive reverse 
      if (millis() >= stateEndTime) setNextState(STATE_CHARGE_ROLL, 0);				             
      break;
    case STATE_CHARGE_ROLL:
      // charging: roll 
      if (millis() >= stateEndTime) setNextState(STATE_CHARGE_FORW,0);				
      break;
    case STATE_CHARGE_FORW:
      // forward (charge station)    
      if (millis() >= stateEndTime) setNextState(STATE_FORWARD,0);				        
      break;      
  } // end switch  
      

  // next line deactivated (issue with RC failsafe)
  //if ((useRemoteRC) && (remoteSwitch < -50)) setNextState(STATE_REMOTE, 0);

  if (millis() >= nextTimeButtonCheck) {        
    nextTimeButtonCheck = millis() + 50;      
    if (buttonUse) checkButton();  
  }
    
  // decide which motor control to use
  if ( ((mowPatternCurr == MOW_LANES) && (stateCurr == STATE_ROLL)) || (stateCurr == STATE_ROLL_WAIT) ) motorControlImuRoll();
    else if (stateCurr == STATE_PERI_TRACK) motorControlPerimeter();
    else if (  (stateCurr == STATE_FORWARD)
     &&  (mowPatternCurr == MOW_RANDOM)
     && (imuUse) 
     && (imuCorrectDir || (mowPatternCurr == MOW_LANES))        
     && (millis() > stateStartTime + 3000) ) motorControlImuDir();
    else motorControl();  

  if (stateCurr != STATE_REMOTE) motorMowSpeed = motorMowSpeedMax;
  motorMowControl();  
  ADCMan.run();
  if (gpsUse) gps.run();
    
  bumperRight = false;
  bumperLeft = false;     
  
  delay(5);                              
  loopsPerSecCounter++;
  
}





