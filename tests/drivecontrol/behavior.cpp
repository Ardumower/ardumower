#include "behavior.h"
#include "motorcontrol.h"
#include "buzzer.h"
#include "button.h"
#include "robot.h"
#include "modelrc.h"



StandbyBehavior::StandbyBehavior() : Behavior() {
  name = "StandbyBehavior";
}

bool StandbyBehavior::takeControl(){
  return  true;
}

void StandbyBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();
  LED.playSequence(LED_GREEN_ON);    
  while ( !suppressed ) {    
    Robot.run();   
  }  
}

// ----------------------------------------------------------

ModelRCBehavior::ModelRCBehavior() : Behavior() {
  name = "ModelRCBehavior";
}

bool ModelRCBehavior::takeControl(){
  return (Robot.mode == MODE_MODEL_RC);
}

void ModelRCBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();
  Button.resetBeepCounter();    
  while ( (!suppressed) && (Robot.mode == MODE_MODEL_RC) )  {    
    ModelRC.run();
    Robot.run();   
  }  
}


// ----------------------------------------------------------

UserInteractionBehavior::UserInteractionBehavior() : Behavior() {
  name = "UserInteractionBehavior";
}

bool UserInteractionBehavior::takeControl(){
  return ( Button.pressed );
}

void UserInteractionBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();  
  while ( !suppressed ){
    int bc = Button.beepCounter;
    if (bc != 0){
      switch (bc){
        case 1: 
          if (Robot.mode == MODE_STANDBY) 
            Robot.setMode(MODE_AUTO);           
          else  
            Robot.setMode(MODE_STANDBY);             
          break;
        case 3: 
          Robot.setMode(MODE_MODEL_RC);           
          break;
      }
      Button.resetBeepCounter();
      break;
    }
    Robot.run();   
  }
}

// ----------------------------------------------------------

DriveForwardBehavior::DriveForwardBehavior() : Behavior() {
  name = "DriveForwardBehavior";
}

bool DriveForwardBehavior::takeControl(){
  return (Robot.mode == MODE_AUTO);
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
  return (  (Robot.mode == MODE_AUTO) 
         && (MotorCtrl.motion != MOTION_STOP) 
         && (MotorCtrl.motorRightStalled) || (MotorCtrl.motorLeftStalled) || (Sonar.triggeredLeft()) );
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
  // wait until motion stop
  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    Robot.run();   
  }
}

// ----------------------------------------------------------

ChargerConnectedBehavior::ChargerConnectedBehavior() : Behavior() {
  name = "ChargerConnectedBehavior";
}

bool ChargerConnectedBehavior::takeControl(){
  return ( Battery.isCharging() );
}

void ChargerConnectedBehavior::action(){  
  suppressed = false;
  
  MotorCtrl.stopImmediately();
  Buzzer.play(BC_SHORT_SHORT_SHORT);                  

  // wait until some other behavior was activated
  while ( (!suppressed ) && (Battery.isCharging()) ) {
    Robot.run();       
  }
}


// ----------------------------------------------------------

FatalErrorBehavior::FatalErrorBehavior() : Behavior() {
  name = "FatalErrorBehavior";
}

bool FatalErrorBehavior::takeControl(){
  return   (   (Robot.mode == MODE_AUTO) 
            && (MotorCtrl.motorLeftError || MotorCtrl.motorRightError || MotorMow.motorError  )
           );
}

void FatalErrorBehavior::action(){  
  suppressed = false;
  
  Robot.setMode(MODE_ERROR);
  MotorCtrl.stopImmediately();
  Buzzer.play(BC_SHORT_SHORT_SHORT);                  
  LED.playSequence(LED_RED_BLINK);  

  // wait until some other behavior was activated
  while ( (!suppressed )&& (Robot.mode == MODE_ERROR) ) {
    Robot.run();       
  }
  
  MotorCtrl.resetFault();
  MotorMow.resetFault();  
}


