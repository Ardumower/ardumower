

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
#include "pid.h"
#include "imu.h"
#include "adcman.h"
#include "perimeter.h"
#include "gps.h"
#include "pfod.h"

//#include "QueueList.h"
//#include <limits.h>


/*
  Generic robot class - subclass to implement concrete hardware!

*/

// code version 
#define VER "590"
 

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
  SEN_DROP_LEFT,       // LOW = pressed                                                                                                  // Dropsensor - Absturzsensor
  SEN_DROP_RIGHT,      // LOW = pressed                                                                                                  // Dropsensor - Absturzsensor
  
  SEN_SONAR_CENTER,      // 0..SONAR_TRIGGER_DISTANCE
  SEN_SONAR_LEFT,        // 0..SONAR_TRIGGER_DISTANCE
  SEN_SONAR_RIGHT,       // 0..SONAR_TRIGGER_DISTANCE
  SEN_BUTTON,            // LOW = pressed
  SEN_IMU,             
  SEN_MOTOR_MOW_RPM,
  SEN_RTC,
  SEN_RAIN,
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
  ACT_CHGRELAY,
};

// error types
enum {
  ERR_MOW_SENSE,
  ERR_IMU_COMM,
  ERR_IMU_TILT,
  ERR_RTC_COMM,
  ERR_RTC_DATA,
  ERR_PERIMETER_TIMEOUT,
  ERR_TRACKING,  
  ERR_ENUM_COUNT,  
};  

// finate state machine states
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
  STATE_STATION,       // in station
  STATE_STATION_CHARGING,       // in station charging
  STATE_STATION_CHECK, //checks if station is present
  STATE_STATION_REV,   // charge reverse
  STATE_STATION_ROLL,  // charge roll
  STATE_STATION_FORW,  // charge forward
  STATE_MANUAL,       // manual navigation  
  STATE_ROLL_WAIT,    // drive roll right/left
};

// roll types
enum { LEFT, RIGHT };

// mow patterns
enum { MOW_RANDOM, MOW_LANES, MOW_BIDIR };

// console mode
enum { CONSOLE_SENSOR_COUNTERS, CONSOLE_SENSOR_VALUES, CONSOLE_PERIMETER, CONSOLE_OFF };


#define MAX_TIMERS 5


class Robot
{
  public:    
    String name;
    // --------- state machine --------------------------
    byte stateCurr;
    byte stateLast;
    byte stateNext;    
    unsigned long stateTime;
    char* stateName();
    unsigned long stateStartTime;
    unsigned long stateEndTime;
    // --------- timer ----------------------------------
    ttimer_t timer[MAX_TIMERS];
    datetime_t datetime;
    char timerUse          ;       // use timer?
    unsigned long nextTimeTimer ;        
    // -------- mow pattern -----------------------------    
    byte mowPatternCurr;
    char *mowPatternName();
    // -------- gps state -------------------------------
    GPS gps;
    char gpsUse            ;       // use GPS?        
    float gpsLat;
    float gpsLon;
    float gpsX ;   // X position (m)
    float gpsY ;   // Y position (m)
    unsigned long nextTimeGPS ;
    // -------- odometry state --------------------------
    char odometryUse       ;       // use odometry?
    char twoWayOdometrySensorUse;  // use optional two-wire odometry sensor?
    int odometryTicksPerRevolution ;   // encoder ticks per one full resolution
    float odometryTicksPerCm ;  // encoder ticks per cm
    float odometryWheelBaseCm ;    // wheel-to-wheel distance (cm)
    bool odometryRightSwapDir;       // inverse right encoder direction?
    bool odometryLeftSwapDir;       // inverse left encoder direction?        
    int odometryLeft ;   // left wheel counter
    int odometryRight ;  // right wheel counter
    boolean odometryLeftLastState;
    boolean odometryLeftLastState2;
    boolean odometryRightLastState;
    boolean odometryRightLastState2;
    float odometryTheta; // theta angle (radiant)
    float odometryX ;   // X map position (cm)
    float odometryY ;   // Y map position (cm)    
    int motorLeftRpm ; // left wheel rpm
    unsigned long lastMotorRpmTime ;     
    int motorRightRpm ; // right wheel rpm    
    unsigned long nextTimeOdometry ;
    unsigned long nextTimeOdometryInfo ; 
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
    unsigned long nextTimeRTC ;
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
    PID motorLeftPID;              // motor left wheel PID controller
    PID motorRightPID;              // motor right wheel PID controller
    float motorSenseRightScale ; // motor right sense scale (mA=(ADC-zero)/scale)
    float motorSenseLeftScale ; // motor left sense scale  (mA=(ADC-zero)/scale)
    int motorRollTimeMax ;  // max. roll time (ms)
    int motorReverseTime ;  // max. reverse time (ms)
    long motorForwTimeMax; // max. forward time (ms) / timeout
    float motorBiDirSpeedRatio1 ;   // bidir mow pattern speed ratio 1
    float motorBiDirSpeedRatio2 ;   // bidir mow pattern speed ratio 2
    bool motorRightSwapDir     ;    // inverse right motor direction? 
    bool motorLeftSwapDir      ;    // inverse left motor direction?  
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
    int motorPowerIgnoreTime; 
    int motorZeroSettleTime;     // how long (ms) to wait for motor to settle at zero speed
    int motorLeftSenseCounter ;  // motor current counter
    int motorRightSenseCounter ;
    unsigned long nextTimeMotorSense ;
    unsigned long lastSetMotorSpeedTime;
    unsigned long motorLeftZeroTimeout;
    unsigned long motorRightZeroTimeout;
    // -------- mower motor state -----------------------
    // mower motor sppeed; range 0..motorMowSpeedMax
    float motorMowAccel       ;  // motor mower acceleration (warning: do not set too high)
    int motorMowSpeedMax ;    // motor mower max PWM
    float motorMowPowerMax ;     // motor mower max power (Watt)
    char motorMowModulate  ;      // motor mower cutter modulation?
    int motorMowRPM        ;   // motor mower RPM (only for cutter modulation)
    float motorMowSenseScale ; // motor mower sense scale (mA=(ADC-zero)/scale)
    PID motorMowPID ;    // motor mower RPM PID controller    
    int motorMowSpeed;
    float motorMowPWM ;         // current speed
    int motorMowSenseADC ; 
    float motorMowSenseCurrent ;
    float motorMowSense ;       // motor power (range 0..MAX_MOW_POWER)
    int motorMowSenseCounter ;
    int motorMowSenseErrorCounter ;
    int motorMowRpm ;            // motor rpm (range 0..MOW_RPM)
    unsigned long lastMotorMowRpmTime;    
    unsigned long nextTimeMotorControl;
    unsigned long nextTimeMotorMowControl;
    int lastMowSpeed;
    // --------- bumper state ---------------------------
    // bumper state (true = pressed)
    char bumperUse       ;      // has bumpers?     
    int bumperLeftCounter ;
    boolean bumperLeft ;          
    int bumperRightCounter ;
    boolean bumperRight ;
    unsigned long nextTimeBumper ;
    // --------- drop state ---------------------------
    // bumper state (true = pressed)                                                                                                  // Dropsensor - Absturzsensor vorhanden ?
    char dropUse       ;      // has drops?                                                                                           // Dropsensor - Absturzsensor Zähler links
    int dropLeftCounter ;                                                                                                             // Dropsensor - Absturzsensor
    boolean dropLeft ;                                                                                                                // Dropsensor - Absturzsensor links betätigt ?
    int dropRightCounter ;                                                                                                            // Dropsensor - Absturzsensor
    boolean dropRight ;                                                                                                               // Dropsensor - Absturzsensor rechts betätigt ?
    unsigned long nextTimeDrop ;                                                                                                      // Dropsensor - Absturzsensor
    char dropcontact ; // contact 0-openers 1-closers                                                                                 // Dropsensor Kontakt 0 für Öffner - 1 Schließer
    // ------- IMU state --------------------------------
    IMU imu;
    char imuUse            ;       // use IMU? 
    char imuCorrectDir     ;       // correct direction by compass?
    PID imuDirPID  ;    // direction PID controller
    PID imuRollPID ;    // roll PID controller        
    float imuDriveHeading ;       // drive heading (IMU)
    float imuRollHeading ;      // roll heading  (IMU)
    byte   imuRollDir;
    //point_float_t accMin;
    //point_float_t accMax;
    unsigned long nextTimeIMU ;
    // ------- perimeter state --------------------------
    Perimeter perimeter;
    char perimeterUse       ;      // use perimeter?
    char perimeterUseDiffSignal;   // use differential signal?
    int perimeterTrackRollTime ;   // perimter tracking roll time (ms)
    int perimeterTrackRevTime  ;   // perimter tracking reverse time (ms)
    PID perimeterPID ;             // perimeter PID controller
    int perimeterMag ;             // perimeter magnitude
    boolean perimeterInside ;      // is inside perimeter?
    unsigned long perimeterTriggerTime; // time to trigger perimeter transition (timeout)
    int perimeterTriggerTimeout;   // perimeter trigger timeout (ms)
    unsigned long perimeterLastTransitionTime;
    int perimeterCounter ;         // counts perimeter transitions
    unsigned long nextTimePerimeter ;
    int trackingPerimeterTransitionTimeOut;
    int trackingErrorTimeOut;    
    char trackingBlockInnerWheelWhilePerimeterStruggling;
    //  --------- lawn state ----------------------------
    char lawnSensorUse     ;       // use capacitive Sensor
    int lawnSensorCounter;
    boolean lawnSensor;  // lawn capacity sensor state (true = no lawn detected)
    float lawnSensorFront ;  // front lawn sensor capacity (time)
    float lawnSensorFrontOld ;
    float lawnSensorBack ;   // back lawn sensor capacity (time)
    float lawnSensorBackOld ;
    unsigned long nextTimeLawnSensor ;
    unsigned long nextTimeLawnSensorCheck ;
    // --------- rain -----------------------------------
    boolean rain;
    boolean rainUse;
    int rainCounter; 
    unsigned long nextTimeRain ;   
    // --------- sonar ----------------------------------
    // ultra sonic sensor distance-to-obstacle (cm)
    char sonarUse          ;      // use ultra sonic sensor?
    int sonarTriggerBelow ;    // ultrasonic sensor trigger distance
    unsigned int sonarDistCenter ;
    unsigned int sonarDistRight ;
    unsigned int sonarDistLeft ; 
    unsigned int sonarDistCounter ;
    unsigned long sonarObstacleTimeout ;
    unsigned long nextTimeSonar ;
    // --------- pfodApp ----------------------------------
    RemoteControl rc; // pfodApp
    unsigned long nextTimePfodLoop ;    
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
    float batChgFactor       ;     // battery conversion factor    
    float batFull         ;      // battery reference Voltage (fully charged)
    float batFullCurrent   ; // current flowing when battery is fully charged
    float startChargingIfBelow; // start charging if battery Voltage is below
    unsigned long chargingTimeout; // safety timer for charging
    int batADC;
    float chgSenseZero    ;       // charge current sense zero point
    float chgFactor       ;     // charge current conversion factor
    float chgSense        ;       // mV/A empfindlichkeit des Ladestromsensors in mV/A (Für ACS712 5A = 185)
    char chgChange        ;       // messwertumkehr von - nach +         1oder 0
    float batVoltage ;  // battery voltage (Volt)
    byte chgSelection     ;       // Senor Auswahl
    float batRefFactor ;
    float batCapacity ; // battery capacity (mAh)
    float chgVoltage ;  // charge voltage (Volt)
    float chgCurrent ;  // charge current  (Ampere)
    int chgNull;        // Nulldurchgang Ladestromsensor
    int stationRevTime     ;    // charge station reverse time (ms)
    int stationRollTime    ;    // charge station roll time (ms)
    int stationForwTime    ;    // charge station forward time (ms)
    int stationCheckTime   ;    // charge station reverse check time (ms)
    unsigned long nextTimeBattery ;    
    // --------- error counters --------------------------
    byte errorCounterMax[ERR_ENUM_COUNT];
    byte errorCounter[ERR_ENUM_COUNT];    
    // --------- other ----------------------------------
    int loopsPerSec ;  // main loops per second
    float loopsTa ;   // main loop-time factor (milliseconds)
    int loopsPerSecCounter ;
    byte buttonCounter ;
    byte ledState ;
    byte consoleMode ;
    unsigned long nextTimeButtonCheck ;    
    unsigned long nextTimeInfo ;                    
    byte rollDir;
    unsigned long nextTimeButton ;
    unsigned long nextTimeErrorCounterReset;    
    unsigned long nextTimeErrorBeep ;  
    // ---------------------------------------
    Robot();
    // robot setup
    virtual void setup();
    // robot main loop
    virtual void loop();        
    
    // call this from R/C control interrupt
    virtual void setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState, 
      boolean remoteMowState, boolean remoteSwitchState);    
    // call this from odometry interrupt
    virtual void setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, 
      boolean odometryLeftState2, boolean odometryRightState2);
    // call this from hall sensor interrupt
    virtual void setMotorMowRPMState(boolean motorMowRpmState);

    // state machine
    virtual void setNextState(byte stateNew, byte dir);    
    
    // motor
    virtual void setMotorSpeed(int pwmLeft, int pwmRight, boolean useAccel);    
    virtual void setMotorMowSpeed(int pwm, boolean useAccel);
    
    // GPS
    virtual void processGPSData();
    
    // read hardware sensor (HAL)
    virtual int readSensor(char type){}    
    
    // set hardware actuator (HAL)
    virtual void setActuator(char type, int value){}    
    
    // settings
    virtual void deleteUserSettings();        
    virtual void saveUserSettings();
    
    // other
    virtual void beep(int numberOfBeeps, boolean shortbeep);    
    virtual void printInfo(Stream &s);        
    virtual void setUserSwitches();        
protected:
    // convert ppm time to RC slider value
    virtual int rcValue(int ppmTime);
    virtual void loadSaveUserSettings(boolean readflag);
    virtual void loadUserSettings();
    virtual void addErrorCounter(byte errType);
    virtual void checkErrorCounter();
    virtual void printSettingSerial();
    
    // read sensors
    virtual void readSensors();            
    
    // read serial
    virtual void readSerial();    
    
    // check sensor
    virtual void checkButton();
    virtual void checkBattery();
    virtual void checkTimer();
    virtual void checkCurrent();
    virtual void checkBumpers();
    virtual void checkDrop();                                                                                                             // Dropsensor - Absturzsensor
    virtual void checkBumpersPerimeter();
    virtual void checkPerimeterBoundary();
    virtual void checkPerimeterFind();
    virtual void checkLawn();
    virtual void checkSonar();
    virtual void checkTilt();
    virtual void checkRain();
    virtual void checkTimeout();
    
    // motor controllers
    virtual void motorControl();    
    virtual void motorControlImuRoll();
    virtual void motorControlPerimeter();
    virtual void motorControlImuDir();
    virtual void motorMowControl();
    
    // date & time
    virtual void setDefaultTime();
    
    // set reverse
    virtual void reverseOrBidir(byte aRollDir);    
    
    // other
    virtual void printRemote();
    virtual void printOdometry();
    virtual void printMenu();    
    virtual void delayInfo(int ms);    
    virtual void testOdometry();
    virtual void testMotors();
    virtual void setDefaults();    
    virtual void receiveGPSTime();
    virtual void calcOdometry();
    virtual void menu();
    virtual void configureBluetooth(boolean quick){};
};    



#endif


