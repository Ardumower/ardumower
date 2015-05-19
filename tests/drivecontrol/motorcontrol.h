#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// differential drive motor controller
// requires: 
//   - 2 brushed gear motors with 1-way encoder (odometry)
//   - MC33926 motor driver
//
// how to use:
//
//  MotorCtrl.travelLineDistance(-30, 5);
//  void loop(){
//    MotorCtrl.run();
//  }


#include <Arduino.h>
#include "pid.h"

// Warning: if you change pinout, interrupt pin configuration need to be changed too!

#define pinMotorEnable  37         // EN motors enable

#define pinMotorLeftPWM 5          // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31         // M1_IN2 left motor Dir pin
#define pinMotorLeftSense A1       // M1_FB  left motor current sense
#define pinMotorLeftFault 25       // M1_SF  left motor fault
                                                             
#define pinMotorRightPWM  3        // M2_IN1 right motor PWM pin
#define pinMotorRightDir 33        // M2_IN2 right motor Dir pin
#define pinMotorRightSense A0      // M2_FB  right motor current sense
#define pinMotorRightFault 27      // M2_SF  right motor fault

#define pinOdometryLeft A12      // left odometry sensor
#define pinOdometryRight A14     // right odometry sensor  


enum {
  MOTION_SPEED,
  MOTION_LINE_SPEED,  
  MOTION_LINE_DISTANCE,
  MOTION_ROTATE_ANGLE,
  MOTION_STOP,
};


class MotorControl
{
  public:
    byte motion; // motion to perform
  
    // gear motors
    bool motorRightSwapDir     ;    // inverse right motor direction? 
    bool motorLeftSwapDir      ;    // inverse left motor direction?         
    bool motorLeftError;            // left motor error?
    bool motorRightError;          // right  motor error?
    bool motorLeftStalled;        // left motor stalled?
    bool motorRightStalled;        // right motor stalled?    
    float motorVoltageDC;  // known operating voltage (DC)
    int motorLeftSpeedRpmSet ; // set speed
    int motorRightSpeedRpmSet ;
    float motorLeftRpmCurr ; // left wheel rpm    
    float motorRightRpmCurr ; // right wheel rpm        
    int motorSpeedMaxRpm   ;   // motor wheel max RPM   
    int motorSpeedMaxPwm  ;  // motor wheel max Pwm  (8-bit PWM=255, 10-bit PWM=1023)     
    PID motorLeftPID;              // motor left wheel PID controller
    PID motorRightPID;              // motor right wheel PID controll    
    float motorLeftPWMCurr ; // current motor pwm
    float motorRightPWMCurr ;      
    
    // motor current
    int motorRightSenseADC ; // ADC value
    int motorLeftSenseADC ;
    float motorLeftSenseCurrent ;  // current (mA)
    float motorRightSenseCurrent ;
    float motorLeftSenseGradient; // current gradient
    float motorRightSenseGradient; // current gradient    
    float motorLeftEfficiency; //  efficiency (output rotation/input power)
    float motorRightEfficiency; //  efficiency (output rotation/input power)    
    float motorLeftSensePower ;   // power (W)     
    float motorRightSensePower ;    
    float motorSenseRightScale ; // motor right sense scale (mA=(ADC-zero)*scale)
    float motorSenseLeftScale ; // motor left sense scale  (mA=(ADC-zero)*scale)    
  
    // odometry
    int odometryLeftTicks ;   // left wheel counter
    int odometryRightTicks ;  // right wheel counter    
    int odometryLeftTicksZeroCounter; // counts number of times ticks did not change
    int odometryRightTicksZeroCounter;        
    int odometryTicksPerRevolution ;   // encoder ticks per one full resolution
    float odometryTicksPerCm ;  // encoder ticks per cm
    float odometryWheelBaseCm ;    // wheel-to-wheel distance (cm)    
    float odometryThetaRadCurr; // current theta angle (radiant)
    float odometryXcmCurr;   // current X map position (cm)
    float odometryYcmCurr;   // current Y map position (cm)        
    float odometryDistanceCmCurr; // distance traveled (cm)    
    float odometryThetaRadSet; // set angle (radiant)
    int odometryDistanceCmSet;  // set distance (cm)
    float distanceToTargetCm; // distance to target (cm)
    float angleToTargetRad; // angle to target (rad)
        
    bool enableSpeedControl; // enable speed controller?
    bool enableStallDetection; // enable stall detection?
    MotorControl();
    void init();
    void run();    
    void setSpeedRpm(int leftRpm, int rightRpm);    
    void setSpeedPWM(int leftPWM, int rightPWM);    
    void stopImmediately();
    void travelLineSpeedRpm(int speedRpm);    
    void travelLineDistance(int distanceCm, int speedRpm);
    void rotate(float angleRad, int speedRpm);
    bool hasStopped();    
    void resetStalled();
    void print();
    void printCSV(bool includeHeader);
private:    
    unsigned long lastMotorRunTime;
    unsigned long lastMotorControlTime;
    unsigned long lastOdometryTime;    
    unsigned long lastMotorCurrentTime;        
    void readOdometry();
    void speedControl();
    void setMC33926(int pinDir, int pinPWM, int speed);    
    void readCurrent();
    void checkMotorFault();
};


extern MotorControl MotorCtrl;

#endif



