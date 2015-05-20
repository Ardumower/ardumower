#include "behavior.h"
#include "motorcontrol.h"
#include "buzzer.h"
#include "robot.h"


DriveForwardBehavior::DriveForwardBehavior() : Behavior() {
  name = "DriveForwardBehavior";
}

bool DriveForwardBehavior::takeControl(){
  return true;
}

void DriveForwardBehavior::action(){  
  suppressed = false;

  // forward
  MotorCtrl.setSpeedRpm(+10, +10); 
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    Robot.run();   
  }
}


// ----------------------------------------------------------

HitObstacleBehavior::HitObstacleBehavior()  : Behavior(){
  name = "HitObstacleBehavior";
}

bool HitObstacleBehavior::takeControl(){
  return ((MotorCtrl.motorRightStalled) || (MotorCtrl.motorLeftStalled));
}

void HitObstacleBehavior::action(){  
  suppressed = false;    
  MotorCtrl.resetStalled();
  bool rotateRight = MotorCtrl.motorLeftStalled;
  if (!Buzzer.isPlaying()) Buzzer.play(BC_LONG_SHORT_SHORT);                  
  
  // reverse
  MotorCtrl.travelLineDistance(-30, 10);             
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ) {
    Robot.run();   
  }
  
  // rotate
  if (rotateRight){
    MotorCtrl.rotate(-PI/2, 10);               
  } else {
    MotorCtrl.rotate(+PI/2, 10);                   
  } 
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    Robot.run();   
  }
}




