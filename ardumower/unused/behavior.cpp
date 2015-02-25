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

#include "behavior.h"
#include "robot.h"

Behavior::Behavior()
{
}

Behavior::Behavior(Robot *aRobot)
{
  robot = aRobot;
}

// ------------------------------------
ManualBehavior::ManualBehavior(Robot *aRobot)
{
  robot = aRobot;
}

void ManualBehavior::act(){
}

boolean ManualBehavior::isActive(){
  return false;
}

String ManualBehavior::toString(){
  return F("ManualBehavior");
}


// ------------------------------------
ObstacleBehavior::ObstacleBehavior(Robot *aRobot)
{
  robot = aRobot;
}

void ObstacleBehavior::act(){
}

boolean ObstacleBehavior::isActive(){
  return (robot->bumperLeft || robot->bumperRight);
}

String ObstacleBehavior::toString(){
  return F("ObstacleBehavior");
}

// ----------------------------------

MowBehavior::MowBehavior(Robot *aRobot)
{
  robot = aRobot;
}

void MowBehavior::act(){
}

boolean MowBehavior::isActive(){
  return true;
}

String MowBehavior::toString(){
  return F("MowBehavior");
}

// ----------------------------------

TrackBehavior::TrackBehavior(Robot *aRobot)
{
  robot = aRobot;
}

void TrackBehavior::act(){
  int  lms = robot->motorLeftPWM;
  int  rms = robot->motorRightPWM;
  if (robot->perimeterLeft < 0) {
    rms += 80.0;
    lms -= 10.0;
  }
  else
  {
    rms -= 10.0;
    lms += 80.0;
  }
  if (rms > 255) rms = 255;
  if (lms > 255) lms = 255;
  if (rms < -100) rms = -100;
  if (lms < -100) lms = -100;  
  robot->setMotorSpeed( lms,  rms, false);      
}

boolean TrackBehavior::isActive(){
  return true;
}

String TrackBehavior::toString(){
  return F("TrackBehavior");
}
// ----------------------------------



