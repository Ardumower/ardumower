#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <Arduino.h>
#include "drivers.h"

// subsumption architecture
// external resources:
//   http://www.convict.lu/Jeunes/Subsumption.htm
//   http://www.lejos.org/nxt/nxj/tutorial/Behaviors/BehaviorProgramming.htm
//   http://www.ibm.com/developerworks/library/j-robots/


// abstract superclass
class Behavior
{
  public:    
    String name;
    bool suppressed;
    bool enabled;
    Behavior() { suppressed = false; enabled = true; }
    virtual void enable(bool flag){ 
      if (enabled == flag) return;
      enabled = flag; 
      Console.print(F("ENABLE "));
      Console.print(name);
      Console.print(" ");
      Console.println(enabled);      
    }
    virtual void suppress() { suppressed = true; }
    virtual bool takeControl() {}
    virtual void action() {}    
};

// Model R/C control 
class ModelRCBehavior : public Behavior
{
  public: 
    ModelRCBehavior();
    virtual bool takeControl();
    virtual void action();       
};

// robot is idle (not driving around or charging)
class StandbyBehavior : public Behavior
{
  public:        
    StandbyBehavior();
    virtual bool takeControl();
    virtual void action();      
};

// user is interacting with robot (via button)
class UserInteractionBehavior : public Behavior
{
  public:        
    UserInteractionBehavior();
    virtual bool takeControl();
    virtual void action();      
};

// robot is mowing and driving forward
class DriveForwardBehavior : public Behavior
{
  public:    
    DriveForwardBehavior();
    virtual bool takeControl();    
    virtual void action();    
};

// robot hit obstacle
class HitObstacleBehavior : public Behavior
{
  public:        
    HitObstacleBehavior();
    virtual bool takeControl();
    virtual void action();    
};

// robot hit perimeter
class HitPerimeterBehavior : public Behavior
{
  public:        
    HitPerimeterBehavior();
    virtual bool takeControl();
    virtual void action();    
};

// robot is perimeter tracking
class TrackingBehavior : public Behavior
{
  public:        
    TrackingBehavior();
    virtual bool takeControl();
    virtual void action();    
};

// robot is charging
class ChargingBehavior : public Behavior
{
  public:        
    ChargingBehavior();
    virtual bool takeControl();
    virtual void action();    
};


// fatal error appeared
class FatalErrorBehavior : public Behavior
{
  public:        
    FatalErrorBehavior();
    virtual bool takeControl();
    virtual void action();    
};




#endif

