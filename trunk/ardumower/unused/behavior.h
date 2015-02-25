/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  
  Private-use only! (you need to ask for a commercial-use)
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  Private-use only! (you need to ask for a commercial-use)

*/

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <Arduino.h>
//#include "robot.h"

class Robot;

// abstract superclass
class Behavior
{
  public:    
    unsigned long behaviorTime;
    boolean enabled;
    Robot *robot;    
    Behavior();    
    Behavior(Robot *aRobot);
    // enabled?
    virtual boolean isEnabled(){ return true; }
    // should behavior become active?
    virtual boolean isActive() = 0;
    // act on behavior - keep running time as short as possible!
    virtual void act() = 0;
    // returns a description
    virtual String toString() = 0;
};


// manual control behavior
class ManualBehavior : public Behavior
{
  public:    
    ManualBehavior(Robot *aRobot);
    virtual boolean isActive();
    virtual void act();
    virtual String toString();    
};


// obstacle avoidance behavior
class ObstacleBehavior : public Behavior
{
  public:    
    ObstacleBehavior(Robot *aRobot);
    virtual boolean isActive();
    virtual void act();
    virtual String toString();    
};


// mowing behavior (straight line)
class MowBehavior  : public Behavior
{
  public:    
    MowBehavior(Robot *aRobot);
    virtual boolean isActive();
    virtual void act();
    virtual String toString();    
};


// perimeter tracking behavior
class TrackBehavior  : public Behavior
{
  public:    
    TrackBehavior(Robot *aRobot);
    virtual boolean isActive();
    virtual void act();
    virtual String toString();
};



#endif

