/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
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
*/

#include "robot.h"


char* stateNames[]={"OFF ", "RC  ", "FORW", "ROLL", "REV ", "CIRC", "ERR ", "PFND", "PTRK", "PROL", "PREV", "CHRG", 
  "CREV", "CROL", "CFOR", "MANU", "ROLW" };
  
char *mowPatternNames[] = {"RAND", "LANE", "BIDIR"};



Robot::Robot(){
  name = "Generic";
}
  
char* Robot::stateName(){
  return stateNames[stateCurr];
}

char *Robot::mowPatternName(){
  return mowPatternNames[mowPatternCurr];
}


// set user-defined switches
void Robot::setUserSwitches(){
  setActuator(ACT_USER_SW1, userSwitch1);   
  setActuator(ACT_USER_SW2, userSwitch2);     
  setActuator(ACT_USER_SW3, userSwitch3);     
}

void Robot::saveUserSettings(){
}

void Robot::deleteUserSettings(){
}


void Robot::imuSetComCalParam(int type, int i, int j, float value){
}

void Robot::imuSaveCalib(){
}

void Robot::imuGetComRaw(point_float_t &v){
}

void Robot::beep(int numberOfBeeps, boolean shortbeep){
}

void Robot::printInfo(Stream &s){
}

// ---- motor RPM (interrupt) --------------------------------------------------------------
// mower motor RPM driver
void Robot::setMotorMowRPMState(boolean motorMowRpmState){
  if (motorMowRpmState != motorMowRpmLastState) {    
    motorMowRpmLastState = motorMowRpmState;
    if (motorMowRpmLastState) motorMowRpmCounter++;   
  }
}


// ---- odometry (interrupt) --------------------------------------------------------
// odometryState:  1st left and right odometry signal
// odometryState2: 2nd left and right odometry signal (optional two-wire encoders)
void Robot::setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, boolean odometryLeftState2, boolean odometryRightState2){
  if (odometryLeftState != odometryLeftLastState){    
    if (odometryLeftState){
      if (!odometryLeftState2) odometryLeft++; else odometryLeft--; 
    }
    odometryLeftLastState = odometryLeftState;
  } 
  if (odometryRightState != odometryRightLastState){
    if (odometryRightState){
      if (!odometryRightState2) odometryRight++; else odometryRight--;     
    }
    odometryRightLastState = odometryRightState;
  }  
  if (odometryRightState2 != odometryRightLastState2){
    odometryRightLastState2 = odometryRightState2;    
  }  
  if (odometryLeftState2 != odometryLeftLastState2){
    odometryLeftLastState2 = odometryLeftState2;    
  }   
}


// ---- RC (interrupt) --------------------------------------------------------------
// RC remote control helper
int Robot::rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;
  return value;
}

// RC remote control driver
void Robot::setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState, 
  boolean remoteMowState, boolean remoteSwitchState){
  if (remoteSpeedState != remoteSpeedLastState) {    
    remoteSpeedLastState = remoteSpeedState;
    if (remoteSpeedState) remoteSpeedLastTime = timeMicros; else remoteSpeed = rcValue(timeMicros - remoteSpeedLastTime);
  }
  if (remoteSteerState != remoteSteerLastState) {    
    remoteSteerLastState = remoteSteerState;
    if (remoteSteerState) remoteSteerLastTime = timeMicros; else remoteSteer = rcValue(timeMicros - remoteSteerLastTime);
  }
  if (remoteMowState != remoteMowLastState) {    
    remoteMowLastState = remoteMowState;
    if (remoteMowState) remoteMowLastTime = timeMicros; else remoteMow = max(0, (rcValue(timeMicros - remoteMowLastTime)+100)/2);
  }  
  if (remoteSwitchState != remoteSwitchLastState) {    
    remoteSwitchLastState = remoteSwitchState;
    if (remoteSwitchState) remoteSwitchLastTime = timeMicros; else remoteSwitch = rcValue(timeMicros - remoteSwitchLastTime);
  }  
}

// sets wheel motor actuators
// - ensures that the motors (and gears) are not switched to 0% (or 100%) too fast (motorAccel)
// - ensures that motors voltage is not higher than motorSpeedMax
void Robot::setMotorSpeed(int pwmLeft, int pwmRight, boolean useAccel){
  // FIXME: we might need to ingore acceleration for PID controllers 
  if (!useAccel){
    motorLeftPWM = pwmLeft;
    motorRightPWM = pwmRight;
  } else {
    double accel = motorAccel * loopsTa;       
    motorLeftPWM = (1.0 - accel) * motorLeftPWM + accel * ((double)pwmLeft); 
    motorRightPWM = (1.0 - accel) * motorRightPWM + accel * ((double)pwmRight);  
  }
    setActuator(ACT_MOTOR_LEFT, motorLeftPWM);
    setActuator(ACT_MOTOR_RIGHT, motorRightPWM);
}

void Robot::motorControl(){
  //double TA = ((double)(millis() - lastMotorControlTime)) / 1000.0;  
  // normal drive
  if (odometryUse){
  if ((millis() - lastMotorControlTime) < 100) return;
  int motorLeftSetpoint = motorLeftSpeed;
  int motorRightSetpoint = motorRightSpeed;
  double P = 1.0;
  if (millis() < behaviorCurr->behaviorTime  + 500) {
    motorLeftSetpoint = motorRightSetpoint = 0;
    P = 3.0;
  }
  double motorLeftSpeedE =  motorLeftSetpoint - motorLeftRpm;          
  double motorRightSpeedE = motorRightSetpoint - motorRightRpm;  
  int leftSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorLeftPWM + motorLeftSpeedE*P));
  int rightSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm,motorRightPWM + motorRightSpeedE*P));
  
  setMotorSpeed( leftSpeed, rightSpeed, false );  
  lastMotorControlTime = millis();
  }
  else{
  int leftSpeed = min(motorSpeedMaxPwm, max(-motorSpeedMaxPwm, map(motorLeftSpeed, -motorSpeedMax, motorSpeedMax, -motorSpeedMaxPwm, motorSpeedMaxPwm)));
  int rightSpeed =min(motorSpeedMaxPwm, max(-motorSpeedMaxPwm, map(motorRightSpeed, -motorSpeedMax, motorSpeedMax, -motorSpeedMaxPwm, motorSpeedMaxPwm)));
  if (millis() < behaviorCurr->behaviorTime  + 1000) {				
    leftSpeed = rightSpeed = 0; // slow down at state start      
    //if (mowPatternCurr != MOW_LANES) imuDriveHeading = imuYaw; // set drive heading    
  }
  setMotorSpeed( leftSpeed, rightSpeed, true );    
  }  
}

void Robot::setNextState(byte stateNew, byte dir){
}

void Robot::imuCalibComDeviation(){
}

void Robot::initSuppresses(boolean matrix[BEHAVIOR_COUNT][BEHAVIOR_COUNT]){
  for (int i=0; i < BEHAVIOR_COUNT; i++){
    for (int j=0; j < BEHAVIOR_COUNT; j++){
       suppresses[i][j] = matrix[i][j];
    }
  }
  behaviorCurrIdx = 0;
}


void Robot::performBehavior(void) {
   boolean isActive[BEHAVIOR_COUNT];
   for (int i = 0; i < BEHAVIOR_COUNT; i++) {
     isActive[i] = ( (behaviors[i] != NULL) && (behaviors[i]->isActive()) );
   }
   boolean ranABehavior = false;
   while (!ranABehavior) {
      boolean runCurrentBehavior =  isActive[behaviorCurrIdx];
      if (runCurrentBehavior) {
         for (int i = 0; i < BEHAVIOR_COUNT; i++) {
            if ((isActive[i]) && (suppresses[i][behaviorCurrIdx])) {
               runCurrentBehavior = false; // behavior is suppressed
               break;
            }
         }
      }

      if (runCurrentBehavior) {
         if (behaviorCurrIdx < BEHAVIOR_COUNT) {
            behaviors[behaviorCurrIdx]->act();            
         }
         ranABehavior = true;
      }

      if (BEHAVIOR_COUNT > 0) {
         behaviorCurrIdx = (behaviorCurrIdx + 1)
                  % BEHAVIOR_COUNT;
      }
   }
}



void Robot::setup(void){
}

void Robot::loop(void){
}






