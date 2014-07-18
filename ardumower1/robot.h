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

#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Wire.h>  
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else
  // Arduino Due
  #include "due.h"
#endif
//#include <Servo.h>  // for RC brushless contoller
#include "drivers.h"
#include "behavior.h"
//#include "QueueList.h"
//#include <limits.h>


/*
  Generic robot class - subclass to implement concrete hardware!

*/

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

#define BEHAVIOR_COUNT 5

// ---------- timers --------------------------------------
struct ttimer_t {
  boolean active;
  timehm_t startTime;
  timehm_t stopTime;
  byte daysOfWeek;
};

typedef struct ttimer_t ttimer_t;

#define MAX_TIMERS 5


class Robot
{
  public:
    String name;
    // --------- timer ----------------------------------
    ttimer_t timer[MAX_TIMERS];
    datetime_t datetime;
    char timerUse          ;       // use timer?        
    // -------- mow pattern -----------------------------
    char *mowPatternName[];
    byte mowPatternCurr;
    // -------- odometry state --------------------------
    char odometryUse       ;       // use odometry?
    int odometryTicksPerRevolution ;   // encoder ticks per one full resolution
    float odometryTicksPerCm ;  // encoder ticks per cm
    float odometryWheelBaseCm ;    // wheel-to-wheel distance (cm)    
    int odometryLeft ;   // left wheel counter
    int odometryRight ;  // right wheel counter
    boolean odometryLeftLastState;
    boolean odometryLeftLastState2;
    boolean odometryRightLastState;
    boolean odometryRightLastState2;
    float odometryTheta; // theta angle (radiant)
    float odometryX ;   // X map position (cm)
    float odometryY ;   // Y map position (cm)
    int motorLeftRpmCounter ; // left wheel rpm counter
    float motorLeftRpm ; // left wheel rpm
    unsigned long lastMotorLeftRpmTime ; 
    int motorRightRpmCounter ; // right wheel rpm counter
    float motorRightRpm ; // right wheel rpm
    unsigned long lastMotorRightRpmTime; 
    // -------- RC remote control state -----------------
    char remoteUse      ;       // use model remote control (R/C)?
    int remoteSteer ;  // range -100..100
    int remoteSpeed ;  // range -100..100
    int remoteMow ;    // range 0..100
    int remoteSwitch ; // range 0..100
    unsigned long remoteSteerLastTime ;
    unsigned long remoteSpeedLastTime ;
    unsigned long remoteMowLastTime ;
    unsigned long remoteSwitchLastTime ;
    boolean remoteSteerLastState ;
    boolean remoteSpeedLastState ;
    boolean remoteMowLastState ;
    boolean remoteSwitchLastState ;
    // -------- mower motor state -----------------------
    int motorMowRpmCounter ;  // mower motor speed state
    boolean motorMowRpmLastState ;
    boolean motorMowEnable ;
    // --------- wheel motor state ----------------------------
    // wheel motor speed ( <0 backward, >0 forward); range -motorSpeedMax..motorSpeedMax
    float motorAccel  ;  // motor wheel acceleration (warning: do not set too high)
    int motorSpeedMax   ;   // motor wheel max RPM
    int motorSpeedMaxPwm  ;  // motor wheel max Pwm  (8-bit PWM=255, 10-bit PWM=1023)
    float motorPowerMax   ;    // motor wheel max power (Watt)
    float motorSenseRightScale ; // motor right sense scale (mA=(ADC-zero)/scale)
    float motorSenseLeftScale ; // motor left sense scale  (mA=(ADC-zero)/scale)
    int motorRollTimeMax ;  // max. roll time (ms)
    int motorReverseTime ;  // max. reverse time (ms)
    long motorForwTimeMax; // max. forward time (ms) / timeout
    float motorBiDirSpeedRatio1 ;   // bidir mow pattern speed ratio 1
    float motorBiDirSpeedRatio2 ;   // bidir mow pattern speed ratio 2
    int motorLeftSpeed ; // set speed
    int motorRightSpeed ;
    float motorLeftPWM ; // current speed
    float motorRightPWM ;
    int motorRightSenseADC ;
    int motorLeftSenseADC ;
    float motorLeftSenseCurrent ;     
    float motorRightSenseCurrent ;
    float motorLeftSense ;      // motor power (range 0..MAX_MOTOR_POWER)
    float motorRightSense ;
    int motorLeftSenseCounter ;  // motor current counter
    int motorRightSenseCounter ;
    // -------- mower motor state -----------------------
    // mower motor sppeed; range 0..motorMowSpeedMax
    float motorMowAccel       ;  // motor mower acceleration (warning: do not set too high)
    int motorMowSpeedMax ;    // motor mower max PWM
    float motorMowPowerMax ;     // motor mower max power (Watt)
    char motorMowModulate  ;      // motor mower cutter modulation?
    int motorMowRPM        ;   // motor mower RPM (only for cutter modulation)
    float motorMowSenseScale ; // motor mower sense scale (mA=(ADC-zero)/scale)
    pid_params_t motorMowPid ;    // motor mower RPM PID controller    
    int motorMowSpeed;
    float motorMowPWM ;         // current speed
    int motorMowSenseADC ; 
    float motorMowSenseCurrent ;
    float motorMowSense ;       // motor power (range 0..MAX_MOW_POWER)
    int motorMowSenseCounter ;
    int motorMowSenseErrorCounter ;
    int motorMowRpm ;            // motor rpm (range 0..MOW_RPM)
    // --------- bumper state ---------------------------
    // bumper state (true = pressed)
    char bumperUse       ;      // has bumpers?     
    int bumperLeftCounter ;
    boolean bumperLeft ;          
    int bumperRightCounter ;
    boolean bumperRight ;
    // ------- IMU state --------------------------------
    char imuUse            ;       // use IMU? 
    char imuCorrectDir     ;       // correct direction by compass?
    pid_params_t imuDirPid  ;    // direction PID controller
    pid_params_t imuRollPid ;    // roll PID controller    
    float imuYaw ;    // compass course (radiant)
    float imuPitch ;  // tilt angle (radiant)
    float imuRoll ;   // tilt angle (radiant)
    float imuDriveHeading ;       // drive heading (IMU)
    float imuRollHeading ;      // roll heading  (IMU)
    byte   imuRollDir;
    //point_float_t accMin;
    //point_float_t accMax;
    // ------- perimeter state --------------------------
    char perimeterUse       ;      // use perimeter?
    int perimeterTrackRollTime ;   // perimter tracking roll time (ms)
    int perimeterTrackRevTime  ;   // perimter tracking reverse time (ms)
    pid_params_t perimeterPid ;    // perimeter PID controller
    int perimeterLeft ;
    int perimeterRight ;
    boolean perimeterLeftState ;
    int perimeterLeftCounter ;
    //  --------- lawn state ----------------------------
    char lawnSensorUse     ;       // use capacitive Sensor
    int lawnSensorCounter;
    boolean lawnSensor;  // lawn capacity sensor state (true = no lawn detected)
    float lawnSensorFront ;  // front lawn sensor capacity (time)
    float lawnSensorFrontOld ;
    float lawnSensorBack ;   // back lawn sensor capacity (time)
    float lawnSensorBackOld ;
    // --------- sonar ----------------------------------
    // ultra sonic sensor distance-to-obstacle (cm)
    char sonarUse          ;      // use ultra sonic sensor?
    int sonarTriggerBelow ;    // ultrasonic sensor trigger distance
    unsigned int sonarDistCenter ;
    unsigned int sonarDistRight ;
    unsigned int sonarDistLeft ; 
    unsigned int sonarDistCounter ;
    unsigned long sonarObstacleTimeout ;
    // ----- GPS -------------------------------------------
    char gpsUse            ;       // use GPS?
    // ----- other -----------------------------------------
    char buttonUse         ;       // has digital ON/OFF button?
    // ----- user-defined switch ---------------------------
    char userSwitch1       ;       // user-defined switch 1 (default value)
    char userSwitch2       ;       // user-defined switch 2 (default value)
    char userSwitch3       ;       // user-defined switch 3 (default value)
    // --------- charging -------------------------------
    char batMonitor ;              // monitor battery and charge voltage?
    float batGoHomeIfBelow ;     // drive home voltage (Volt)
    float batSwitchOffIfBelow ;  // switch off if below voltage (Volt)
    float batFactor       ;     // battery conversion factor
    float batSenseZero    ;        // battery volt sense zero point
    float batFull         ;      // battery reference Voltage (fully charged)
    float chgSenseZero    ;       // charge current sense zero point
    float chgFactor       ;     // charge current conversion factor
    int batADC ;
    float batVoltage ;  // battery voltage (Volt)
    float batRefFactor ;
    float batCapacity ; // battery capacity (mAh)
    float chgVoltage ;  // charge voltage (Volt)
    float chgCurrent ;  // charge current  (Ampere)
    int stationRevTime     ;    // charge station reverse time (ms)
    int stationRollTime    ;    // charge station roll time (ms)
    int stationForwTime    ;    // charge station forward time (ms)    
    // ------------ PID controllers ----------------------------
    pidc_t imuDirPID;
    pidc_t imuRollPID;
    pidc_t perimeterPID;
    pidc_t motorMowPID;
    // --------- error counters --------------------------
    byte errorCounterMax[ERR_ENUM_COUNT];
    byte errorCounter[ERR_ENUM_COUNT];
    // --------- behavior -------------------------------
    Behavior *behaviorCurr; // current behavior
    int behaviorCurrIdx;    // current behavior index
    Behavior *behaviors[BEHAVIOR_COUNT];  // all behaviors    
    boolean suppresses[BEHAVIOR_COUNT][BEHAVIOR_COUNT]; // suppress matrix
    // --------- other ----------------------------------
    int loopsPerSec ;  // main loops per second
    float loopsTa ;   // main loop-time factor (milliseconds)
    int loopsPerSecCounter ;
    byte buttonCounter ;
    byte ledState ;
    char* consoleModeName;
    byte consoleMode ;
    unsigned long nextTimeButtonCheck ;
    unsigned long nextTimeInfo ;
    unsigned long nextTimeMotorSense ;
    unsigned long nextTimeIMU ;
    unsigned long nextTimeOdometry ;
    unsigned long nextTimeOdometryInfo ;
    unsigned long nextTimeBumper ;
    unsigned long nextTimeSonar ;
    unsigned long nextTimeBattery ;
    unsigned long nextTimePerimeter ;
    unsigned long nextTimeLawnSensor ;
    unsigned long nextTimeLawnSensorCheck ;
    unsigned long nextTimeTimer ;
    unsigned long nextTimeRTC ;
    unsigned long nextTimePfodLoop ;
    unsigned long lastMotorControlTime ;
    unsigned long lastMotorMowControlTime;
    unsigned long lastMotorMowRpmTime;
    byte rollDir;
    unsigned long nextTimeButton ;
    unsigned long nextTimeErrorCounterReset;    
    unsigned long nextTimeErrorBeep ;  
    // ---------------------------------------
    Robot();
    virtual void setup();
    virtual void loop();        
    virtual void setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState, 
      boolean remoteMowState, boolean remoteSwitchState);    
    virtual void setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, 
      boolean odometryLeftState2, boolean odometryRightState2);
    virtual void setMotorMowRPMState(boolean motorMowRpmState);
    virtual void setMotorSpeed(int pwmLeft, int pwmRight, boolean useAccel);
    virtual void motorControl();
protected:
    // read hardware sensor
    virtual int readSensor(char type){}    
    // set hardware actuator
    virtual void setActuator(char type, int value){}
    // convert ppm time to RC slider value
    virtual int rcValue(int ppmTime);
    // initialize suppresses matrix
    virtual void initSuppresses(boolean matrix[BEHAVIOR_COUNT][BEHAVIOR_COUNT]);
    // perform robot behavior
    virtual void performBehavior(void);
};    



#endif


