#include "behavior.h"
#include "motorcontrol.h"
#include "buzzer.h"


DriveForwardBehavior::DriveForwardBehavior() : Behavior() {
  name = "DriveForwardBehavior";
}

bool DriveForwardBehavior::takeControl(){
  return true;
}

bool DriveForwardBehavior::actionCompleted(){  
  MotorCtrl.setSpeedRpm(+10, +10); 
  return false;
}


// ----------------------------------------------------------

HitObstacleBehavior::HitObstacleBehavior()  : Behavior(){
  name = "HitObstacleBehavior";
}

bool HitObstacleBehavior::takeControl(){
  return ((MotorCtrl.motorRightStalled) || (MotorCtrl.motorLeftStalled));
}

bool HitObstacleBehavior::actionCompleted(){  
  if (MotorCtrl.motorRightStalled)  {
    if (!Buzzer.isPlaying()) Buzzer.play(BC_LONG_SHORT_SHORT);                
    MotorCtrl.resetStalled();   
    MotorCtrl.rotate(-PI/2, 10);     
  } else if (MotorCtrl.motorLeftStalled){
    if (!Buzzer.isPlaying()) Buzzer.play(BC_LONG_SHORT_LONG);                
    MotorCtrl.resetStalled();              
    MotorCtrl.rotate(+PI/2, 10); 
  } 
  return (MotorCtrl.motion == MOTION_STOP);
}




