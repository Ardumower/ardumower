#ifndef ROBOT_H
#define ROBOT_H

// Ardumower robot 

#include <Arduino.h>
#include "config.h"
#include "drivers.h"
#include "adcman.h"
#include "buzzer.h"
#include "button.h"
#include "led.h"
#include "sonar.h"
#include "perimeter.h"
#include "timer.h"
#include "battery.h"
#include "motorcontrol.h"
#include "motormow.h"
#include "modelrc.h"
#include "behavior.h"
#include "arbitrator.h"




class RobotControl
{
  public:
    unsigned long loopCounter;   // Arduino loop counter
    ModelRCBehavior modelRCBehavior;
    UserInteractionBehavior userInteractionBehavior;
    StandbyBehavior standbyBehavior;
    DriveForwardBehavior driveForwardBehavior;  
    HitObstacleBehavior  hitObstacleBehavior;
    HitPerimeterBehavior  hitPerimeterBehavior;    
    ChargingBehavior  chargingBehavior;
    FatalErrorBehavior fatalErrorBehavior;
    TrackingBehavior trackingBehavior;
    Arbitrator arbitrator;      
    RobotControl();    
    unsigned long nextPrintTime;
    virtual void setAutoMode(); // activate auto mode
    virtual void setModelRCMode(); // activate model R/C mode    
    virtual void setStandbyMode(); // set robot to standby/idle mode
    virtual void run();
    virtual void setup();
    virtual void loop();
    virtual void print();
    virtual void motorPIDTest();
  private:    
    void checkKey();
};

extern RobotControl Robot;  

  
#endif

