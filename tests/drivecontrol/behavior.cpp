#include "behavior.h"
#include "motorcontrol.h"
#include "buzzer.h"
#include "button.h"
#include "robot.h"



StandbyBehavior::StandbyBehavior() : Behavior() {
  name = "StandbyBehavior";
}

bool StandbyBehavior::takeControl(){
  return  true;
}

void StandbyBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();
  while ( !suppressed ) {    
    Robot.run();   
  }  
}

// ----------------------------------------------------------

StopBehavior::StopBehavior() : Behavior() {
  name = "StopBehavior";
}

bool StopBehavior::takeControl(){
  return ( (Button.beepCounter == 1) && (MotorCtrl.motion != MOTION_STOP) );
}

void StopBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();  
  Button.resetBeepCounter();  
}

// ----------------------------------------------------------

DriveForwardBehavior::DriveForwardBehavior() : Behavior() {
  name = "DriveForwardBehavior";
}

bool DriveForwardBehavior::takeControl(){
  return (Button.beepCounter == 1);
}

void DriveForwardBehavior::action(){  
  suppressed = false;
  Button.resetBeepCounter();

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

// ----------------------------------------------------------

ChargerConnectedBehavior::ChargerConnectedBehavior() : Behavior() {
  name = "ChargerConnectedBehavior";
}

bool ChargerConnectedBehavior::takeControl(){
  return Battery.chargerConnected();
}

void ChargerConnectedBehavior::action(){  
  suppressed = false;
  
  MotorCtrl.stopImmediately();
  Buzzer.play(BC_SHORT_SHORT_SHORT);                  
  Battery.enableChargingRelay(true);

  // wait until charging completed  
  while ( !suppressed ){
    Robot.run();   
  }
}



