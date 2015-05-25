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
    unsigned long loopCounter;
    StopBehavior stopBehavior;
    StandbyBehavior standbyBehavior;
    DriveForwardBehavior driveForwardBehavior;  
    HitObstacleBehavior  hitObstacleBehavior;
    ChargerConnectedBehavior  chargerConnectedBehavior;
    Arbitrator arbitrator;  
    RobotControl();    
    virtual void run();
    virtual void setup();
    virtual void loop();
  private:
    
};

extern RobotControl Robot;  

  
#endif

