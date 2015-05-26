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
  LED.playSequence(LED_OFF);           
  MotorCtrl.stopImmediately();  
  while ( !suppressed ) {    
    Robot.run();   
  }  
}

// ----------------------------------------------------------

ModelRCBehavior::ModelRCBehavior() : Behavior() {
  name = "ModelRCBehavior";
}

bool ModelRCBehavior::takeControl(){
  return true;
}

void ModelRCBehavior::action(){  
  suppressed = false;
  MotorCtrl.stopImmediately();
  while ( !suppressed )  {    
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
  while ( !suppressed ){
    int bc = Button.beepCounter;
    if (bc != 0){
      switch (bc){
        case 1: 
          if (MotorCtrl.motion == MOTION_STOP)
            Robot.setAutoMode();
          else 
            Robot.setStandbyMode();
          break;
        case 3: 
          Robot.setModelRCMode();
          break;
      }
      Button.resetBeepCounter();
      break;
    }
    MotorCtrl.stopImmediately();  
    Robot.run();   
  }
}

// ----------------------------------------------------------

DriveForwardBehavior::DriveForwardBehavior() : Behavior() {
  name = "DriveForwardBehavior";
}

bool DriveForwardBehavior::takeControl(){
  return true;
}

void DriveForwardBehavior::action(){  
  suppressed = false;
  
  LED.playSequence(LED_GREEN_ON);             

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
  return (  (MotorCtrl.motion != MOTION_STOP) 
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

ChargingBehavior::ChargingBehavior() : Behavior() {
  name = "ChargingBehavior";
}

bool ChargingBehavior::takeControl(){
  return ( Battery.isCharging() );
}

void ChargingBehavior::action(){  
  suppressed = false;
  
  MotorCtrl.stopImmediately();
  LED.playSequence(LED_OFF);             
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
  return   (   
              (MotorCtrl.motorLeftError || MotorCtrl.motorRightError || MotorMow.motorError  )
           );
}

void FatalErrorBehavior::action(){  
  suppressed = false;
    
  MotorCtrl.stopImmediately();
  Buzzer.play(BC_SHORT_SHORT_SHORT);                  
  LED.playSequence(LED_RED_BLINK);  

  // wait until some other behavior was activated
  while ( !suppressed  ) {
    Robot.run();       
  }
  
  MotorCtrl.resetFault();
  MotorMow.resetFault();  
}


// ----------------------------------------------------------

TrackingBehavior::TrackingBehavior() : Behavior() {
  name = "TrackingBehavior";
}

bool TrackingBehavior::takeControl(){
  return ( Battery.robotShouldGoHome() );
}

void TrackingBehavior::action(){  
  suppressed = false;
  
  MotorCtrl.stopImmediately();
  LED.playSequence(LED_OFF);             
  Buzzer.play(BC_LONG_LONG);                  
  
  // find perimeter wire
  MotorCtrl.setSpeedRpm(+10, +10); 

  while ( (!suppressed) && (MotorCtrl.motion != MOTION_STOP) ){
    //if (perimeter.isOutside){
    //  MotorCtrl.stopImmediately();
    //}
    Robot.run();   
  }
  
  // track perimeter until some other behavior was activated
  while ( !suppressed )  {

    // TODO: add perimeter tracking code
    
    Robot.run();       
  }
}


