#ifndef ARBITRATOR_H
#define ARBITRATOR_H

#include <Arduino.h>
#include "behavior.h"


#define MAX_BEHAVIORS 20


class Arbitrator
{
  public:
    int behaviorCount;    
    Behavior *activeBehavior;
    Behavior *nextBehavior;    
    int activeBehaviorIdx;
    int nextBehaviorIdx;    
    Arbitrator();
    virtual void addBehavior(Behavior *behavior);
    virtual void run();
    virtual void monitor();
};





#endif

