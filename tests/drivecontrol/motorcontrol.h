#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// differential drive motor controller - requires motors with 1-way encoder (odometry)
// how to use:
//
//  MotorCtrl.travelLineDistance(-30, 5);
//  void loop(){
//    MotorCtrl.run();
//  }


#include "pid.h"


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
    char motion; // motion to perform

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
    float leftRightCompensation; // left-right speed compensation

    // motor current
    float motorEfficiencyMin; // minimum motor efficiency (stall detection)
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
    unsigned long odometryLeftTickTime;
    unsigned long odometryRightTickTime;
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
    bool enableErrorDetection; // enable error detection?
    MotorControl();
    virtual void setup();
    virtual void run();
    virtual void setSpeedRpm(int leftRpm, int rightRpm);
    virtual void setSpeedPWM(int leftPWM, int rightPWM);
    virtual void stopImmediately();
    virtual void travelLineSpeedRpm(int speedRpm);
    virtual void travelLineDistance(int distanceCm, int speedRpm);
    // rotate (+counter-clock / -clock-wise)
    virtual void rotate(float angleRad, int speedRpm);
    virtual bool hasStopped();
    virtual void resetStalled();
    virtual void resetFault();
    virtual void print();
    virtual void printCSV(bool includeHeader);
private:
    unsigned long lastMotorRunTime;
    unsigned long nextMotorPrintTime;
    unsigned long lastMotorControlTime;
    unsigned long lastOdometryTime;
    unsigned long lastMotorCurrentTime;
    virtual void readOdometry();
    virtual void speedControl();
    virtual void setDriverPWM(int leftMotorPWM, int rightMotorPWM);
    virtual void readCurrent();
    virtual void checkFault();
};





#endif



