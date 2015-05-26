#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <Arduino.h>


// abstract superclass
class Behavior
{
  public:    
    String name;
    bool suppressed;
    Behavior() { suppressed = false; }
    virtual void suppress() { suppressed = true; }
    virtual bool takeControl() {}
    virtual void action() {}    
};

class ModelRCBehavior : public Behavior
{
  public: 
    ModelRCBehavior();
    virtual bool takeControl();
    virtual void action();       
};

class StandbyBehavior : public Behavior
{
  public:        
    StandbyBehavior();
    virtual bool takeControl();
    virtual void action();      
};

class UserStopBehavior : public Behavior
{
  public:        
    UserStopBehavior();
    virtual bool takeControl();
    virtual void action();      
};


class DriveForwardBehavior : public Behavior
{
  public:    
    DriveForwardBehavior();
    virtual bool takeControl();    
    virtual void action();    
};

class HitObstacleBehavior : public Behavior
{
  public:        
    HitObstacleBehavior();
    virtual bool takeControl();
    virtual void action();    
};

class ChargerConnectedBehavior : public Behavior
{
  public:        
    ChargerConnectedBehavior();
    virtual bool takeControl();
    virtual void action();    
};


class FatalErrorBehavior : public Behavior
{
  public:        
    FatalErrorBehavior();
    virtual bool takeControl();
    virtual void action();    
};




#endif

