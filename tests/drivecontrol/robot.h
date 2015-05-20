#ifndef ROBOT_H
#define ROBOT_H

// Ardumower robot 

#include <Arduino.h>
#include "drivers.h"
#include "adcman.h"
#include "buzzer.h"
#include "led.h"
#include "motorcontrol.h"
#include "modelrc.h"
#include "behavior.h"
#include "arbitrator.h"


class RobotControl
{
  public:
    DriveForwardBehavior driveForwardBehavior;  
    HitObstacleBehavior  hitObstacleBehavior;
    Arbitrator arbitrator;  
    RobotControl();    
    virtual void loop();
    virtual void setup();
  private:
    
};


extern RobotControl Robot;  

  
#endif

