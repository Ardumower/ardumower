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
    int activeBehaviorIdx;
    Arbitrator();
    virtual void addBehavior(Behavior *behavior);
    virtual void run();
};





#endif

