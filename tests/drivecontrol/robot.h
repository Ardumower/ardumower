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


// modes
enum { 
  MODE_STANDBY,      // standby
  MODE_MODEL_RC,     // model remote control (R/C)
  MODE_AUTO,         // auto mowing
  MODE_MANUAL,       // manual mowing
  MODE_ERROR,        // error
};




class RobotControl
{
  public:
    int mode; // current mode
    unsigned long loopCounter;   // Arduino loop counter
    ModelRCBehavior modelRCBehavior;
    UserInteractionBehavior userInteractionBehavior;
    StandbyBehavior standbyBehavior;
    DriveForwardBehavior driveForwardBehavior;  
    HitObstacleBehavior  hitObstacleBehavior;
    ChargerConnectedBehavior  chargerConnectedBehavior;
    FatalErrorBehavior fatalErrorBehavior;
    Arbitrator arbitrator;  
    RobotControl();    
    virtual void setMode(int newMode);
    virtual void run();
    virtual void setup();
    virtual void loop();
  private:
    void checkKey();
};

extern RobotControl Robot;  

  
#endif

