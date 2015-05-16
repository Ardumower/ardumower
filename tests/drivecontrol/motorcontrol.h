#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// differential drive motor controller

#include <Arduino.h>
#include "pid.h"


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



class MotorControl
{
  public:
    int motorLeftSpeedRpmSet ; // set speed
    int motorRightSpeedRpmSet ;

    float motorLeftRpmCurr ; // left wheel rpm    
    float motorRightRpmCurr ; // right wheel rpm    
    
    int motorSpeedMaxRpm   ;   // motor wheel max RPM   
    int motorSpeedMaxPwm  ;  // motor wheel max Pwm  (8-bit PWM=255, 10-bit PWM=1023) 
    
    PID motorLeftPID;              // motor left wheel PID controller
    PID motorRightPID;              // motor right wheel PID controll
    
    float motorLeftPWMCurr ; // current speed
    float motorRightPWMCurr ;      
  
    int odometryLeft ;   // left wheel counter
    int odometryRight ;  // right wheel counter
    
    int odometryLeftTicksZeroCounter; // counts ticks not changing 
    int odometryRightTicksZeroCounter;    
    
    int odometryTicksPerRevolution ;   // encoder ticks per one full resolution
    float odometryTicksPerCm ;  // encoder ticks per cm
    float odometryWheelBaseCm ;    // wheel-to-wheel distance (cm)
    
    float odometryTheta; // theta angle (radiant)
    float odometryX ;   // X map position (cm)
    float odometryY ;   // Y map position (cm)        
    
    unsigned long lastMotorControlTime;
    unsigned long lastOdometryTime;
    
    bool enableSpeedControl;
    MotorControl();
    void run();    
    void setSpeedRpm(int leftRpm, int rightRpm);
    void setSpeedPWM(int leftPWM, int rightPWM);    
private:    
    void readOdometry();
    void speedControl();
    void setMC33926(int pinDir, int pinPWM, int speed);    
};


extern MotorControl MotorCtrl;

#endif



