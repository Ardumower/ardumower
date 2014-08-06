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

#define MAGIC 23

char* stateNames[]={"OFF ", "RC  ", "FORW", "ROLL", "REV ", "CIRC", "ERR ", "PFND", "PTRK", "PROL", "PREV", "CHRG", 
  "CREV", "CROL", "CFOR", "MANU", "ROLW" };
  
char *mowPatternNames[] = {"RAND", "LANE", "BIDIR"};

char* consoleModeNames[]={"sen_counters", "sen_values", "perimeter"}; 


Robot::Robot(){
  name = "Generic";
  rc.setRobot(this);
  
  stateLast = stateCurr = stateNext = STATE_OFF;
  mowPatternCurr = MOW_RANDOM;
  
  odometryLeft = odometryRight = 0;
  odometryLeftLastState = odometryLeftLastState2 = odometryRightLastState = odometryRightLastState2 = LOW;
  odometryTheta = odometryX = odometryY = 0;
  
  motorLeftRpmCounter = motorRightRpmCounter = 0;  
  motorRightRpm = motorLeftRpm = 0;
  lastMotorLeftRpmTime = lastMotorRightRpmTime = 0;
  motorLeftSpeed =  motorRightSpeed = 0; 
  motorLeftPWM = motorRightPWM = 0;
  motorRightSenseADC = motorLeftSenseADC = 0;
  motorLeftSenseCurrent = motorRightSenseCurrent = 0;     
  motorLeftSense = motorRightSense = 0;
  motorLeftSenseCounter = motorRightSenseCounter = 0;  
  
  remoteSteer = remoteSpeed = remoteMow = remoteSwitch = 0;  
  remoteSteerLastTime = remoteSpeedLastTime =remoteMowLastTime =remoteSwitchLastTime = 0;
  remoteSteerLastState = remoteSpeedLastState = remoteMowLastState = remoteSwitchLastState = LOW;

  motorMowRpmCounter = 0;
  motorMowRpmLastState = LOW;
  motorMowEnable = false;
  motorMowSpeed = motorSpeedMax;
  motorMowPWM = 0;
  motorMowSenseADC = 0;
  motorMowSenseCurrent  = 0;
  motorMowSense = 0;
  motorMowSenseCounter = 0;
  motorMowSenseErrorCounter = 0;
  motorMowRpm = 0;

  bumperLeftCounter = bumperRightCounter = 0;
  bumperLeft = bumperRight = false;          

  imuYaw = imuPitch = imuRoll = 0;
  imuDriveHeading = 0;
  imuRollHeading = 0;
  imuRollDir = LEFT;  
  
  perimeterLeft =  perimeterRight = 0;
  perimeterLeftState = true;
  perimeterLeftCounter = 0;  
  
  lawnSensorCounter = 0;
  lawnSensor = false;
  lawnSensorFront = lawnSensorFrontOld = lawnSensorBack = lawnSensorBackOld = 0;  

  sonarDistCenter = sonarDistRight = sonarDistLeft = 0;
  sonarDistCounter = 0;
  sonarObstacleTimeout = 0;

  batADC = 0;
  batVoltage = 0;
  batRefFactor = 0;
  batCapacity = 0; 
  chgVoltage = 0;
  chgCurrent = 0;
    
  memset(errorCounterMax, 0, sizeof errorCounterMax);
  memset(errorCounter, 0, sizeof errorCounterMax);
    
  loopsPerSec = 0;
  loopsTa = 5.0;
  loopsPerSecCounter = 0;
  buttonCounter = 0;
  ledState = 0;

  consoleMode = CONSOLE_SENSOR_COUNTERS; 
  nextTimeButtonCheck = 0;
  nextTimeInfo = 0;
  nextTimeMotorSense = 0;
  nextTimeIMU = 0;
  nextTimeOdometry = 0;
  nextTimeOdometryInfo = 0;
  nextTimeBumper = 0;
  nextTimeSonar = 0;
  nextTimeBattery = 0;
  nextTimePerimeter = 0;
  nextTimeLawnSensor = 0;
  nextTimeLawnSensorCheck = 0;
  nextTimeTimer = 0;
  nextTimeRTC = 0;
  nextTimePfodLoop = 0;
  lastMotorControlTime = millis();
  lastMotorMowControlTime = millis();
  lastMotorMowRpmTime = millis();
  nextTimeButton = 0;
  nextTimeErrorCounterReset = 0;    
  nextTimeErrorBeep = 0;
  
}

  
char* Robot::stateName(){
  return stateNames[stateCurr];
}

char *Robot::mowPatternName(){
  return mowPatternNames[mowPatternCurr];
}

void Robot::loadSaveUserSettings(boolean readflag){
  int addr = 0;
  short magic = MAGIC;
  eereadwrite(readflag, addr, magic); // magic
  eereadwrite(readflag, addr, motorAccel);    
  eereadwrite(readflag, addr, motorSpeedMax);
  eereadwrite(readflag, addr, motorSpeedMaxPwm); 
  eereadwrite(readflag, addr, motorPowerMax);
  eereadwrite(readflag, addr, motorSenseRightScale);
  eereadwrite(readflag, addr, motorSenseLeftScale);
  eereadwrite(readflag, addr, motorRollTimeMax);
  eereadwrite(readflag, addr, motorReverseTime);
  eereadwrite(readflag, addr, motorForwTimeMax);
  eereadwrite(readflag, addr, motorMowSpeedMax);
  eereadwrite(readflag, addr, motorMowPowerMax);
  eereadwrite(readflag, addr, motorMowRPM);
  eereadwrite(readflag, addr, motorMowSenseScale);
  eereadwrite(readflag, addr, motorMowPid);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio1);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio2);  
  eereadwrite(readflag, addr, bumperUse);
  eereadwrite(readflag, addr, sonarUse);
  eereadwrite(readflag, addr, sonarTriggerBelow);
  eereadwrite(readflag, addr, perimeterUse);
  eereadwrite(readflag, addr, perimeterTrackRollTime );
  eereadwrite(readflag, addr, perimeterTrackRevTime);
  eereadwrite(readflag, addr, perimeterPid);
  eereadwrite(readflag, addr, lawnSensorUse);
  eereadwrite(readflag, addr, imuUse);
  eereadwrite(readflag, addr, imuCorrectDir);
  eereadwrite(readflag, addr, imuDirPid);
  eereadwrite(readflag, addr, imuRollPid);    
  eereadwrite(readflag, addr, remoteUse);
  eereadwrite(readflag, addr, batMonitor);
  eereadwrite(readflag, addr, batGoHomeIfBelow);
  eereadwrite(readflag, addr, batSwitchOffIfBelow);  
  eereadwrite(readflag, addr, batFactor);
  eereadwrite(readflag, addr, batSenseZero);
  eereadwrite(readflag, addr, chgSenseZero);
  eereadwrite(readflag, addr, chgFactor);
  eereadwrite(readflag, addr, stationRevTime);
  eereadwrite(readflag, addr, stationRollTime);
  eereadwrite(readflag, addr, stationForwTime);
  eereadwrite(readflag, addr, odometryUse);
  eereadwrite(readflag, addr, odometryTicksPerRevolution);
  eereadwrite(readflag, addr, odometryTicksPerCm);
  eereadwrite(readflag, addr, odometryWheelBaseCm);
  eereadwrite(readflag, addr, buttonUse);
  eereadwrite(readflag, addr, userSwitch1);
  eereadwrite(readflag, addr, userSwitch2);
  eereadwrite(readflag, addr, userSwitch3);    
  eereadwrite(readflag, addr, timerUse);
  eereadwrite(readflag, addr, timer);  
  Console.print("loadSaveUserSettings addrstop=");
  Console.println(addr);
}

void Robot::loadUserSettings(){
  short magic = 0;
  int addr = 0;
  eeread(addr, magic);
  if (magic != MAGIC) return;
  loadSaveUserSettings(true);
}


void Robot::saveUserSettings(){
  loadSaveUserSettings(false);
}

void Robot::deleteUserSettings(){
  int addr = 0;
  eewrite(addr, (short)0); // magic  
}

void Robot::addErrorCounter(byte errType){   
  if (errorCounter[errType] < 255) errorCounter[errType]++;
  if (errorCounterMax[errType] < 255) errorCounterMax[errType]++;    
}

void Robot::checkErrorCounter(){
  if (millis() >= nextTimeErrorCounterReset){
    for (int i=0; i < ERR_ENUM_COUNT; i++) errorCounter[i]=0;
    nextTimeErrorCounterReset = millis() + 30000; // 30 sec
  }  
  if (stateCurr != STATE_OFF) {
   for (int i=0; i < ERR_ENUM_COUNT; i++){
     if (errorCounter[i] > 10) setNextState(STATE_ERROR, 0);
    }
  }
}



void Robot::imuSetComCalParam(int type, int i, int j, float value){
}

void Robot::imuSaveCalib(){
}

void Robot::imuGetComRaw(point_float_t &v){
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

void Robot::imuCalibComDeviation(){
}

void Robot::initSuppresses(boolean matrix[BEHAVIOR_COUNT][BEHAVIOR_COUNT]){
  /*for (int i=0; i < BEHAVIOR_COUNT; i++){
    for (int j=0; j < BEHAVIOR_COUNT; j++){
       suppresses[i][j] = matrix[i][j];
    }
  }
  behaviorCurrIdx = 0;*/
}


void Robot::performBehavior(void) {
   /*boolean isActive[BEHAVIOR_COUNT];
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
   }*/
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

// sets mower motor actuator
// - ensures that the motor is not switched to 100% too fast (motorMowAccel)
// - ensures that the motor voltage is not higher than motorMowSpeedMax
void Robot::setMotorMowSpeed(int pwm, boolean useAccel){
  // we need to ignore acceleration for PID control, and we can ignore if speed is lowered (e.g. motor is shut down)
  if ( (!useAccel) || (pwm < motorMowPWM) )
    motorMowPWM = pwm;
  else {
    double accel = motorMowAccel * loopsTa;
    motorMowPWM = (1.0 - accel) * motorMowPWM + accel * ((double)pwm);
  }
  setActuator(ACT_MOTOR_MOW, min(motorMowSpeedMax, max(0, motorMowPWM)));
}

// PID controller: roll robot to heading (requires IMU)
void Robot::motorControlImuRoll(){
  imuRollPID.Ta = ((double)(millis() - lastMotorControlTime)) / 1000.0; 			  
  if (imuRollPID.Ta > 0.5) imuRollPID.Ta = 0; // should only happen for the very first call
  imuRollPID.x = distancePI(imuYaw, imuRollHeading) / PI * 180.0;            
  //Console.println(imuRollPID.x);    
  imuRollPID.Kp = imuRollPid.Kp;
  imuRollPID.Ki = imuRollPid.Ki;
  imuRollPID.Kd = imuRollPid.Kd;
  imuRollPID.w = 0;
  imuRollPID.y_min = -motorSpeedMax;
  imuRollPID.y_max = motorSpeedMax;		
  imuRollPID.max_output = motorSpeedMax;
  imuRollPID.compute();						      
  lastMotorControlTime = millis();
  setMotorSpeed( -imuRollPID.y, 
                +imuRollPID.y,  false);    
}


// PID controller: track perimeter 
void Robot::motorControlPerimeter(){      
  double Ta = ((double)(millis() - lastMotorControlTime)) / 1000.0; 			  
  if (Ta > 0.05) Ta = 0.05; // should only happen for the very first call
  lastMotorControlTime = millis();
  int  lms = motorLeftPWM;
  int  rms = motorRightPWM;
  if (rms < 1) rms = 1;
  if (lms < 1) lms = 1;    
  if (perimeterLeft < 0) {
    rms += 2550/rms * Ta;
    lms -= 2550/lms * Ta;
  }
  else
  {
    rms -= 2550/rms  * Ta;
    lms += 2550/lms  * Ta;
  }

  if (rms > 255) rms = 255;
  if (lms > 255) lms = 255;
  if (rms < 1) rms = 1;
  if (lms < 1) lms = 1;  
  setMotorSpeed( lms,  rms, false);      

  /*perimeterPID.Kp = perimeterPid.Kp;
  perimeterPID.Ki = perimeterPid.Ki;
  perimeterPID.Kd = perimeterPid.Kd;
  //perimeterPID.x = perimeterLeft-perimeterRight;    
  if (perimeterLeft < 0) perimeterPID.x = -1;
    else perimeterPID.x = 1; 
  perimeterPID.w = 0;
  perimeterPID.y_min = -motorSpeedMax;
  perimeterPID.y_max = motorSpeedMax;		
  perimeterPID.max_pwm = motorSpeedMax;
  PIDControl(&perimeterPID);						    
  lastMotorControlTime = millis();
  setMotorSpeed( motorLeftPWM  +perimeterPID.y, 
                 motorRightPWM -perimeterPID.y, false);      */
//  setMotorSpeed( motorSpeedMax/2 + perimeterPID.y, 
//                 motorSpeedMax/2 - perimeterPID.y, false);    
}

// PID controller: correct direction during normal driving (requires IMU)
void Robot::motorControlImuDir(){
  int leftSpeed = motorLeftSpeed;    
  int rightSpeed = motorRightSpeed;
  imuDirPID.Ta = ((double)(millis() - lastMotorControlTime)) / 1000.0; 			              
  if (imuDirPID.Ta > 0.5) imuDirPID.Ta = 0; // should only happen for the very first call
  imuDirPID.x = distancePI(imuYaw, imuDriveHeading) / PI * 180.0;            
  //Console.println(imuDirPID.x);    
  imuDirPID.Kp = imuDirPid.Kp;
  imuDirPID.Ki = imuDirPid.Ki;
  imuDirPID.Kd = imuDirPid.Kd;  
  imuDirPID.w = 0;
  imuDirPID.y_min = -motorSpeedMax;
  imuDirPID.y_max = motorSpeedMax;		
  imuDirPID.max_output = motorSpeedMax;
  imuDirPID.compute();	  					      
  lastMotorControlTime = millis();  
  setMotorSpeed( leftSpeed -imuDirPID.y, 
                 rightSpeed +imuDirPID.y, false );
}


void Robot::motorControl(){
  //double TA = ((double)(millis() - lastMotorControlTime)) / 1000.0;  
  // normal drive
  if (odometryUse){
  if ((millis() - lastMotorControlTime) < 100) return;
  int motorLeftSetpoint = motorLeftSpeed;
  int motorRightSetpoint = motorRightSpeed;
  double P = 1.0;
  if (millis() < stateStartTime + 500) {
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
  if (millis() < stateStartTime + 1000) {				
    leftSpeed = rightSpeed = 0; // slow down at state start      
    if (mowPatternCurr != MOW_LANES) imuDriveHeading = imuYaw; // set drive heading    
  }
  setMotorSpeed( leftSpeed, rightSpeed, true );    
  }
  
}


// motor mow speed controller (slowly adjusts output speed to given input speed)
// input: motorMowEnable, motorMowModulate, motorMowRpm
// output: motorMowPWM
void Robot::motorMowControl(){
  double mowSpeed = 0;
  if (!motorMowEnable) {
    mowSpeed = 0;         
    setMotorMowSpeed(mowSpeed, true);
  } 
  else {
    if ((motorMowModulate) && (motorMowRpm != 0)){
      // speed sensor available
      if ((millis() - lastMotorMowControlTime) < 500) return;
      motorMowPID.Ta = ((double)(millis() - lastMotorMowControlTime)) / 1000.0; 			      
      if (motorMowPID.Ta > 0.5) motorMowPID.Ta = 0; // should only happen for the very first call
      motorMowPID.Kp = motorMowPid.Kp;
      motorMowPID.Ki = motorMowPid.Ki;    
      motorMowPID.Kd = motorMowPid.Kd;    
      motorMowPID.x = motorMowRpm;      
      motorMowPID.w = motorMowRPM; // 3300 => 2300
      motorMowPID.y_min = -motorMowSpeedMax;
      motorMowPID.y_max = motorMowSpeedMax;		
      motorMowPID.max_output = motorMowSpeedMax;
      motorMowPID.compute(); 
      mowSpeed = motorMowPWM + motorMowPID.y;            
      setMotorMowSpeed(mowSpeed, false);
    } else {
      // no speed sensor available      
      mowSpeed = motorMowSpeed;
      setMotorMowSpeed(mowSpeed, true);
    }
  }  
  lastMotorMowControlTime = millis();        
}

void Robot::beep(int numberOfBeeps, boolean shortbeep = false){
  for (int i=0; i < numberOfBeeps; i++){
    setActuator(ACT_BUZZER, 1200); 
    if (shortbeep) delay(50);
      else delay(500);
    setActuator(ACT_BUZZER, 0); 
  }
}

// set user-defined switches
void Robot::setUserSwitches(){
  setActuator(ACT_USER_SW1, userSwitch1);   
  setActuator(ACT_USER_SW2, userSwitch2);     
  setActuator(ACT_USER_SW3, userSwitch3);     
}

void Robot::setDefaultTime(){
  datetime.time.hour = 12;
  datetime.time.minute = 0;
  datetime.date.dayOfWeek = 0;
  datetime.date.day = 1;
  datetime.date.month = 1;
  datetime.date.year = 2013;
  timer[0].active = false;
  timer[0].daysOfWeek= B01111110;
  timer[0].startTime.hour = 9;
  timer[0].stopTime.hour = 11;
}

void Robot::setup()  {     
  setDefaultTime();
  setMotorSpeed(0, 0, false);
  loadUserSettings();
  setUserSwitches();
  
  if (!buttonUse){
    // robot has no ON/OFF button => start immediately
    setNextState(STATE_FORWARD,0);
  }  
    
  stateStartTime = millis();  
  setActuator(ACT_BUZZER, 1200);
  delay(100);
  setActuator(ACT_BUZZER, 0);
  delay(900);  
  Console.println(F("START"));  
  Console.print(F("Ardumower v"));
  Console.println(verToString(VER));
  Console.println(F("press..."));
  Console.println(F("  d for menu"));    
  Console.println(F("  v to change console output (sensor counters, values, perimeter etc.)"));    
  Console.println(consoleModeNames[consoleMode]);
} 


void Robot::printRemote(){
  Console.print("RC ");    
  Console.print(remoteSwitch);  
  Console.print(",");      
  Console.print(remoteSteer);
  Console.print(",");    
  Console.print(remoteSpeed);    
  Console.print(",");        
  Console.println(remoteMow);            
}

void Robot::printOdometry(){
  Console.print("ODO,");
  Console.print(odometryX);
  Console.print(",");
  Console.println(odometryY);  
  Console.print("ODO,");
  Console.print(odometryX);
  Console.print(",");
  Console.println(odometryY);  
}

void Robot::printInfo(Stream &s){
  /*Console.print(millis()/1000);
  Console.print(",");
  Console.print(motorMowRPM);
  Console.print(",");
  Console.print(motorMowRpm);
  Console.print(",");
  Console.println(motorMowPWM);
  return;*/
  //Console.println(time2str(datetime.time));
  Streamprint(s, "t%6u ", (millis()-stateStartTime)/1000);  
  Streamprint(s, "l%3u ", loopsPerSec);  
  //Streamprint(s, "r%4u ", freeRam());  
  Streamprint(s, "v%1d ", consoleMode);			    
  Streamprint(s, "%4s ", stateNames[stateCurr]);			    
  if (consoleMode == CONSOLE_PERIMETER){
    Streamprint(s, "sig min %4d max %4d avg %4d  mag %5d",
      (int)perimeter.getSignalMin(), (int)perimeter.getSignalMax(), (int)perimeter.getSignalAvg(),
      perimeterLeft);
    Streamprint(s, "  in %2d  cnt %4d  on %1d\r\n",  
      (int)perimeterLeftState, perimeterLeftCounter, (int)(!perimeter.signalTimedOut()) );      
  } else {  
    if (odometryUse) Streamprint(s, "odo %4d %4d ", (int)odometryLeft, (int)odometryRight);   
    Streamprint(s, "spd %4d %4d %4d ", (int)motorLeftSpeed, (int)motorRightSpeed, (int)motorMowRpm);
    if (consoleMode == CONSOLE_SENSOR_VALUES){
      // sensor values
      Streamprint(s, "sen %4d %4d %4d ", (int)motorLeftSense, (int)motorRightSense, (int)motorMowSense);
      Streamprint(s, "bum %4d %4d ", bumperLeft, bumperRight);
      Streamprint(s, "son %4d %4d %4d ", sonarDistLeft, sonarDistCenter, sonarDistRight);
      Streamprint(s, "pit %3d ", (int)(imuPitch/PI*180.0));
      Streamprint(s, "rol %3d ", (int)(imuRoll/PI*180.0));
      Streamprint(s, "yaw %3d ", (int)(imuYaw/PI*180.0));  
      if (perimeterUse) Streamprint(s, "per %3d ", (int)perimeterLeftState);              
      if (lawnSensorUse) Streamprint(s, "lawn %3d %3d ", (int)lawnSensorFront, (int)lawnSensorBack);
    } else {
      // sensor counters
      Streamprint(s, "sen %4d %4d %4d ", motorLeftSenseCounter, motorRightSenseCounter, motorMowSenseCounter);
      Streamprint(s, "bum %4d %4d ", bumperLeftCounter, bumperRightCounter);
      Streamprint(s, "son %3d ", sonarDistCounter);
      Streamprint(s, "pit %3d ", (int)(imuPitch/PI*180.0));
      Streamprint(s, "rol %3d ", (int)(imuRoll/PI*180.0));
      Streamprint(s, "yaw %3d ", (int)(imuYaw/PI*180.0));  
      //Streamprint(s, "per %3d ", perimeterLeft);          
      if (perimeterUse) Streamprint(s, "per %3d ", perimeterLeftCounter);                  
      if (lawnSensorUse) Streamprint(s, "lawn %3d ", lawnSensorCounter);
      if (gpsUse) Streamprint(s, "gps %2d ", (int)gps.satellites());            
    }
    Streamprint(s, "bat %2d.%01d ", (int)batVoltage, (int)((batVoltage *10) - ((int)batVoltage*10)) );       
    Streamprint(s, "chg %2d.%01d %2d.%01d ", 
        (int)chgVoltage, (int)((chgVoltage *10) - ((int)chgVoltage*10)),
        (int)chgCurrent, (int)((abs(chgCurrent) *10) - ((int)abs(chgCurrent)*10))    
      );    
    Streamprint(s, "imu%3d ", imu.getCallCounter());  
    Streamprint(s, "adc%3d ", ADCMan.getCapturedChannels());  
    Streamprint(s, "%s\r\n", name.c_str());                  
  }
}

void Robot::printMenu(){  
  Console.println();
  Console.println(F("1=test motors"));
  Console.println(F("2=test odometry"));
  Console.println(F("3=setup BT module config (quick baudscan/recommended)"));
  Console.println(F("4=setup BT module config (extensive baudscan)"));
  Console.println(F("5=calibrate IMU acc"));
  Console.println(F("6=delete IMU calib"));
  Console.println(F("0=exit"));  
  Console.println();
}

void Robot::delayInfo(int ms){
  unsigned long endtime = millis() +ms;
  while (millis() < endtime){
    readSensors();
    motorControl();
    printInfo(Console);
    delay(1000);
  }
}

void Robot::testOdometry(){
  char ch;
  int lastLeft = 0;
  int lastRight = 0;
  setMotorSpeed(motorSpeedMax/5, motorSpeedMax/5, false);
  while (true){ 
    if ((odometryLeft != lastLeft) || (odometryRight != lastRight)) {
      Console.print("left=");
      Console.print(odometryLeft);
      Console.print("  right=");
      Console.println(odometryRight);              
      lastLeft = odometryLeft;
      lastRight = odometryRight;
    }
    delay(100);
    if (Console.available() > 0){
      ch = (char)Console.read();      
      if (ch == '0') break;
    }
  };
  setMotorSpeed(0, 0, false);            
}

void Robot::testMotors(){
  Console.println("testing left motor (forward) half speed...");    
  setMotorSpeed(motorSpeedMax/2, 0, false);
  delayInfo(5000);
  setMotorSpeed(0, 0, false);
  Console.println("testing left motor (reverse) full speed...");
  delay(1000);          
  setMotorSpeed(-motorSpeedMax, 0, false);
  delayInfo(5000);          
  Console.println("testing right motor (forward) half speed...");
  setMotorSpeed(0, motorSpeedMax/2, false);
  delayInfo(5000);
  setMotorSpeed(0, 0, false);
  Console.println("testing right motor (reverse) full speed...");
  delay(1000);          
  setMotorSpeed(0, -motorSpeedMax, false);
  delayInfo(5000);
  setMotorSpeed(0, 0, false);            
}

void Robot::menu(){  
  char ch;  
  printMenu();  
  while(true){    
    if (Console.available() > 0) {
      ch = (char)Console.read();            
      switch (ch){
        case '0': 
          return;           
        case '1':         
          testMotors();
          printMenu();
          break;        
        case '2':
          testOdometry();
          printMenu();
          break;
        case '3':
          configureBluetooth(true);          
          printMenu();
          break;
        case '4':          
          configureBluetooth(false);                    
          printMenu();
          break;
        case '5':
          imu.calibAcc();
          printMenu();
          break;
        case '6':
          imu.deleteCalib();
          printMenu();
          break;
      }      
    }
    delay(100);
  }  
}

void Robot::readSerial() {
  // serial input
  if (Console.available() > 0) {
     char ch = (char)Console.read();
     switch (ch){
       case 'd': 
         menu(); // menu
         break;
       case 'v': 
         consoleMode = (consoleMode +1) % 3;
         Console.println(consoleModeNames[consoleMode]);
         break; 
       case 'h':
         setNextState(STATE_PERI_FIND, 0); // press 'h' to drive home
         break; 
       case 't':
         setNextState(STATE_PERI_TRACK, 0); // press 'p' to track perimeter
         break;
       case 'l':
         bumperLeft = true; // press 'l' to simulate left bumper
         bumperLeftCounter++;
         break; 
       case 'r':
         bumperRight = true; // press 'r' to simulate right bumper
         bumperRightCounter++;
         break; 
       case 's':
         lawnSensor = true; // press 's' to simulate lawn sensor
         lawnSensorCounter++;
         break; 
       case 'm':
         motorMowEnable = !motorMowEnable; // press 'm' to toggle mower motor
         break;
       case 'c':
         setNextState(STATE_CHARGE, 0); // press 'c' to simulate charging
         break;
       case '+':
         setNextState(STATE_ROLL_WAIT, 0); // press '+' to rotate 90 degrees (IMU)
         imuRollHeading = scalePI(imuRollHeading + PI/2);
         break;
       case '-':
         setNextState(STATE_ROLL_WAIT, 0); // press '+' to rotate 90 degrees (IMU)
         imuRollHeading = scalePI(imuRollHeading - PI/2);
         break;
       case 'i':
         // press 'i' to toggle imuUse
         imuUse = !imuUse;
         break;
       case '3':
         setNextState(STATE_REMOTE,0); // press '3' to activate model RC         
         break;          
       case '0':
         // press '0' for OFF
         setNextState(STATE_OFF,0);                             
         break;
       case '1':       
         // press '1' for Automode         
         motorMowEnable = true;
         //motorMowModulate = false;                                           
         setNextState(STATE_FORWARD,0);          
         break; 
     }
  }    
}

void Robot::checkButton(){
  boolean buttonPressed = (readSensor(SEN_BUTTON) == LOW);    
  if ( ((!buttonPressed) && (buttonCounter > 0)) || ((buttonPressed) && (millis() >= nextTimeButton)) ) {                
    nextTimeButton = millis() + 1000;
    if (buttonPressed){
      Console.println(F("buttonPressed"));
      // ON/OFF button pressed                                                
      beep(1);
      buttonCounter++;
    } 
    else { 
      // ON/OFF button released          
      if  ( ((stateCurr != STATE_OFF) || (stateCurr == STATE_ERROR)) && (stateCurr != STATE_CHARGE) ) {
        setNextState(STATE_OFF, 0);
      } else if (buttonCounter == 2){
        motorMowEnable = true;
        mowPatternCurr = MOW_BIDIR;
        setNextState(STATE_FORWARD, 0);                
      } else if (buttonCounter == 3){      
        // start remote control mode
        setNextState(STATE_REMOTE, 0);
      } else if (buttonCounter == 4){
        // start normal without mowing
        motorMowEnable = false;        
        setNextState(STATE_FORWARD,0);           
      } else if (buttonCounter == 7){
        // start normal with mowing in lanes
        motorMowEnable = true;
        //motorMowModulate = true;
        mowPatternCurr = MOW_LANES;
        setNextState(STATE_FORWARD, 0);                
      } else if (buttonCounter == 6){
        // track perimeter
        setNextState(STATE_PERI_TRACK, 0);        
      } else if (buttonCounter == 5){
        // drive home
        setNextState(STATE_PERI_FIND, 0);        
      } else if (buttonCounter == 1){
        // start normal with mowing        
        motorMowEnable = true;
        //motorMowModulate = true;                     
        mowPatternCurr = MOW_RANDOM;   
        setNextState(STATE_FORWARD, 0);                
      } 
      
      buttonCounter = 0;                 
    }       
  }
}

void Robot::readSensors(){
  if ((odometryUse) && (millis() >= nextTimeOdometry)) {        
    nextTimeOdometry = millis() + 50;    
    calcOdometry();
  }    
  if (millis() >= nextTimeMotorSense){    
    nextTimeMotorSense = millis() +  50;
    double accel = 0.05;
    motorRightSenseADC = readSensor(SEN_MOTOR_RIGHT);
    motorLeftSenseADC = readSensor(SEN_MOTOR_LEFT);
    motorMowSenseADC = readSensor(SEN_MOTOR_MOW);
    
    if (motorRightPWM < 160) motorRightSenseCurrent = motorRightSenseCurrent * (1.0-accel) + ((double)motorRightSenseADC) * (motorSenseRightScale*1.25) * accel;
        else motorRightSenseCurrent = motorRightSenseCurrent * (1.0-accel) + ((double)motorRightSenseADC) * motorSenseRightScale * accel;
    
    if (motorLeftPWM < 160) motorLeftSenseCurrent = motorLeftSenseCurrent * (1.0-accel) + ((double)motorLeftSenseADC) * (motorSenseLeftScale*1.25) * accel;
        else motorLeftSenseCurrent = motorLeftSenseCurrent * (1.0-accel) + ((double)motorLeftSenseADC) * motorSenseLeftScale * accel;
        
    if (motorMowPWM < 160) motorMowSenseCurrent = motorMowSenseCurrent * (1.0-accel) + ((double)motorMowSenseADC) * (motorMowSenseScale*1.25) * accel;
        else motorMowSenseCurrent = motorMowSenseCurrent * (1.0-accel) + ((double)motorMowSenseADC) * motorMowSenseScale * accel;
   
    if (batVoltage > 8){
      motorRightSense = motorRightSenseCurrent * batVoltage /1000;   // conversion to power in Watt
      motorLeftSense  = motorLeftSenseCurrent  * batVoltage /1000;
      motorMowSense   = motorMowSenseCurrent   * batVoltage /1000;
    }
    else{
      motorRightSense = motorRightSenseCurrent * batFull /1000;   // conversion to power in Watt in absence of battery voltage measurement
      motorLeftSense  = motorLeftSenseCurrent  * batFull /1000;
      motorMowSense   = motorMowSenseCurrent   * batFull /1000;
    }
  
    if ((millis() - lastMotorMowRpmTime) >= 500){                  
      motorMowRpm = readSensor(SEN_MOTOR_MOW_RPM);    
      if ((motorMowRpm == 0) && (motorMowRpmCounter != 0)){
        // rpm may be updated via interrupt
        motorMowRpm = (int) ((((double)motorMowRpmCounter) / ((double)(millis() - lastMotorMowRpmTime))) * 60000.0);
        motorMowRpmCounter = 0;        
      }       
      lastMotorMowRpmTime = millis();     
    }
  }   
  if ((perimeterUse) && (millis() >= nextTimePerimeter)){    
    nextTimePerimeter = millis() +  50; // 50
    //perimeterRight = readSensor(SEN_PERIM_RIGHT) + readSensor(SEN_PERIM_RIGHT_EXTRA);
    perimeterLeft = readSensor(SEN_PERIM_LEFT) + readSensor(SEN_PERIM_LEFT_EXTRA);        
    if ((!perimeter.isInside()) && (perimeterLeftState)){      
      perimeterLeftCounter++;
    }
    perimeterLeftState = perimeter.isInside();
    if (perimeterLeftState) setActuator(ACT_LED, HIGH);    
      else setActuator(ACT_LED, LOW);      
    if (perimeter.signalTimedOut()){
      if ( (stateCurr != STATE_OFF) && (stateCurr != STATE_ERROR) && (stateCurr != STATE_CHARGE) ){
        Console.println("Error: Perimeter timeout");
        addErrorCounter(ERR_PERIMETER_TIMEOUT);
        setNextState(STATE_ERROR,0);
      }
    }
  } 
  if ((lawnSensorUse) && (millis() >= nextTimeLawnSensor)){    
    nextTimeLawnSensor = millis() + 100;               
    double accel = 0.03;
    lawnSensorFront = (1.0-accel) * lawnSensorFront + accel * ((double)readSensor(SEN_LAWN_FRONT));
    lawnSensorBack  = (1.0-accel) * lawnSensorBack  + accel * ((double)readSensor(SEN_LAWN_BACK));        
  }
 if ((lawnSensorUse) && (millis() >= nextTimeLawnSensorCheck)){          
    nextTimeLawnSensorCheck = millis() + 2000;               
    double deltaFront = lawnSensorFront/lawnSensorFrontOld * 100.0;    
    double deltaBack = lawnSensorBack/lawnSensorBackOld * 100.0;        
    if ((deltaFront <= 95) || (deltaBack <= 95)){
      Console.print("LAWN ");
      Console.print(deltaFront);
      Console.print(",");
      Console.println(deltaBack);
      lawnSensorCounter++;
      lawnSensor=true;
    }
    lawnSensorFrontOld = lawnSensorFront;
    lawnSensorBackOld  = lawnSensorBack;
  }
  if ((sonarUse) && (millis() >= nextTimeSonar)){
//    nextTimeSonar = millis() + 500;   
    nextTimeSonar = millis() + 250;   
    sonarDistRight = readSensor(SEN_SONAR_RIGHT);    
    sonarDistLeft = readSensor(SEN_SONAR_LEFT);    
    sonarDistCenter = readSensor(SEN_SONAR_CENTER);    
  }
  if ((bumperUse) && (millis() >= nextTimeBumper)){    
    nextTimeBumper = millis() + 100;               
    if (readSensor(SEN_BUMPER_LEFT) == 0) {
      bumperLeftCounter++;
      bumperLeft=true;
    }
    if (readSensor(SEN_BUMPER_RIGHT) == 0) {
      bumperRightCounter++;
      bumperRight=true;
    } 
  }    
  if ((timerUse) && (millis() >= nextTimeRTC)) {
    // read RTC
    nextTimeRTC = millis() + 1000;
    readSensor(SEN_RTC);            
  }
  
  if ((imuUse) && (millis() >= nextTimeIMU)) {
    // read compass
    nextTimeIMU = millis() + 50;   // 20 hz  (maximum: 100 hz)
    float ypr[3];
    imu.getEulerRad(ypr);
    //imu.getYawPitchRoll(ypr);
    if (imu.getErrorCounter()>0) {
      addErrorCounter(ERR_IMU_COMM);
      Console.println("IMU comm error");    
    }
    imuYaw=ypr[0]; imuPitch=ypr[1]; imuRoll=ypr[2]; 
  }  
  if (millis() >= nextTimeBattery){
    // read battery
    nextTimeBattery = millis() + 100;       
    if ((abs(chgCurrent) > 0.04) && (chgVoltage > 5)){
      // charging
      batCapacity += (chgCurrent / 36.0);
    }
    // convert to double  
    batADC = readSensor(SEN_BAT_VOLTAGE);
    double batvolt = (((double)batADC) - batSenseZero) * batFactor;
    //double chgvolt = ((double)((int)(readSensor(SEN_CHG_VOLTAGE) / 10))) / 10.0;  
    int chgADC = readSensor(SEN_CHG_VOLTAGE);
    //Console.println(chgADC);
    double chgvolt = (((double)chgADC) - batSenseZero) * batFactor;
    double current = ((double)((int)(readSensor(SEN_CHG_CURRENT) / 10))) / 10.0;  
    // low-pass filter
    double accel = 0.01;
    if (abs(batVoltage-batvolt)>5)   batVoltage = batvolt; else batVoltage = (1.0-accel) * batVoltage + accel * batvolt;
    if (abs(chgVoltage-chgvolt)>5)   chgVoltage = chgvolt; else chgVoltage = (1.0-accel) * chgVoltage + accel * chgvolt;
    if (abs(chgCurrent-current)>0.4) chgCurrent = current; else chgCurrent = (1.0-accel) * chgCurrent + accel * current;  
    //batVoltage = batVolt
    //chgVoltage = chgvolt;
    //chgCurrent = current;        
  }    
}


void Robot::setDefaults(){
  motorLeftSpeed = motorRightSpeed = 0;    
  motorMowEnable = false;                
}


// called *ONCE* to set to a *NEW* state
void Robot::setNextState(byte stateNew, byte dir){
  unsigned long stateTime = millis() - stateStartTime;
  if (stateNew == stateCurr) return;
  // state correction  
  if (stateNew == STATE_FORWARD) {    
    if ((stateCurr == STATE_CHARGE_REV) ||(stateCurr == STATE_CHARGE_ROLL)) return;  
    if (stateCurr == STATE_CHARGE) {
      stateNew = STATE_CHARGE_REV;   
      motorMowEnable = false;
    } 
  }  
  // evaluate new state
  stateNext = stateNew;
  rollDir = dir;
  if (stateNew == STATE_CHARGE_REV){
    motorLeftSpeed = motorRightSpeed = -motorSpeedMax;                    
    stateEndTime = millis() + stationRevTime;                     
  } else if (stateNew == STATE_CHARGE_ROLL){
    motorLeftSpeed = motorSpeedMax;
    motorRightSpeed = -motorLeftSpeed;						      
    stateEndTime = millis() + stationRollTime;                     
  } else if (stateNew == STATE_CHARGE_FORW){
    motorLeftSpeed = motorRightSpeed = motorSpeedMax;      
    motorMowEnable = true;    
    stateEndTime = millis() + stationForwTime;                     
  } 
  else if (stateNew == STATE_PERI_ROLL) {    
    stateEndTime = millis() + perimeterTrackRollTime;                     
    if (dir == RIGHT){
	motorLeftSpeed = motorSpeedMax/2;
	motorRightSpeed = -motorLeftSpeed;						
      } else {
	motorRightSpeed = motorSpeedMax/2;
	motorLeftSpeed = -motorRightSpeed;	
      }
  } if (stateNew == STATE_PERI_REV) {
    motorLeftSpeed = motorRightSpeed = -motorSpeedMax/2;                    
    stateEndTime = millis() + perimeterTrackRevTime;                     
  }
  else if (stateNew == STATE_FORWARD){      
    motorLeftSpeed = motorRightSpeed = motorSpeedMax;              
  } 
  else if (stateNew == STATE_REVERSE)  {
    motorLeftSpeed = motorRightSpeed = -motorSpeedMax/1.25;                    
    stateEndTime = millis() + motorReverseTime;                     
  }   
  else if (stateNew == STATE_ROLL) {                  
      imuDriveHeading = scalePI(imuDriveHeading + PI); // toggle heading 180 degree (IMU)
      if (imuRollDir == LEFT){
        imuRollHeading = scalePI(imuDriveHeading - PI/20);        
        imuRollDir = RIGHT;
      } else {
        imuRollHeading = scalePI(imuDriveHeading + PI/20);        
        imuRollDir = LEFT;
      }      
      stateEndTime = millis() + rand() % motorRollTimeMax/2 + motorRollTimeMax/2;               
      if (dir == RIGHT){
	motorLeftSpeed = motorSpeedMax/1.25;
	motorRightSpeed = -motorLeftSpeed/1.25;						
      } else {
	motorRightSpeed = motorSpeedMax/1.25;
	motorLeftSpeed = -motorRightSpeed/1.25;	
      }      
  }  
  if (stateNew == STATE_REMOTE){
    motorMowEnable = true;
    //motorMowModulate = false;              
  } 
  if (stateNew == STATE_CHARGE){
    setDefaults();        
  }
  if (stateNew == STATE_OFF){
    setDefaults();        
  }  
  if (stateNew == STATE_ERROR){
    motorMowEnable = false;    
    motorLeftSpeed = motorRightSpeed = 0;    
  }
  if (stateNew == STATE_PERI_FIND){
    // find perimeter  => drive half speed      
    motorLeftSpeed = motorRightSpeed = motorSpeedMax / 1.5;    
    motorMowEnable = false;    
  }
  if (stateNew == STATE_PERI_TRACK){        
    motorMowEnable = false;    
    //beep(6);
  }   
  if (stateNew != STATE_REMOTE){
    motorMowSpeed = motorMowSpeedMax;
  }
 
  sonarObstacleTimeout = 0;
  // state has changed    
  stateStartTime = millis();
  stateLast = stateCurr;
  stateCurr = stateNext;    
  printInfo(Console);          
}

// check (low) battery
void Robot::checkBattery(){
  if (batMonitor){
    if ((batVoltage < batGoHomeIfBelow) && (stateCurr !=STATE_OFF)) {
      Console.println(F("triggered batGoHomeIfBelow"));
      beep(2, true);      
      setNextState(STATE_PERI_FIND, 0);
    } else if ((batVoltage < batSwitchOffIfBelow) && (stateCurr !=STATE_OFF))  {
      Console.println(F("triggered batSwitchOffIfBelow"));
      beep(2, true);      
      setNextState(STATE_OFF, 0);
    }
  }
}

void Robot::receiveGPSTime(){
  if (gpsUse){
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age; 
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    if (age != GPS::GPS_INVALID_AGE)
    {
      datetime.date.dayOfWeek = getDayOfWeek(month, day, year, 1);      
      datetime.date.day = day;
      datetime.date.month = month;
      datetime.date.year = year;
      datetime.time.hour = hour;
      datetime.time.minute = minute;
      setActuator(ACT_RTC, 0);            
    }      
  }
}

// check timer
void Robot::checkTimer(){
  if (millis() < nextTimeTimer) return;
  nextTimeTimer = millis() + 60000;
  receiveGPSTime();
  boolean stopTimerTriggered = true;
  if (timerUse){    
    for (int i=0; i < MAX_TIMERS; i++){
      if (timer[i].active){
        if  ( (timer[i].daysOfWeek & (1 << datetime.date.dayOfWeek)) != 0) {
          int startmin = time2minutes(timer[i].startTime);
          int stopmin =  time2minutes(timer[i].stopTime);
          int currmin =  time2minutes(datetime.time);
          if ((currmin >= startmin) && (currmin < stopmin)){
            // start timer triggered
            stopTimerTriggered = false;
            if ((stateCurr == STATE_CHARGE) || (stateCurr == STATE_OFF)){
              Console.println("timer start triggered");
              motorMowEnable = true;
              setNextState(STATE_FORWARD, 0);
            } 
          }           
        }
      }
    }
    if (stopTimerTriggered){
      if (stateCurr == STATE_FORWARD){
        Console.println("timer stop triggered");
        setNextState(STATE_PERI_FIND, 0);
      } 
    }
  }
}

void Robot::reverseOrBidir(byte aRollDir){
  if (mowPatternCurr == MOW_BIDIR){
    if (stateCurr == STATE_FORWARD) {      
      setNextState(STATE_REVERSE, RIGHT);     
    } else if (stateCurr == STATE_REVERSE) {
      setNextState(STATE_FORWARD, LEFT);
    }
  } else setNextState(STATE_REVERSE, aRollDir);
}

// check motor current
void Robot::checkCurrent(){
  if (motorMowSense >= motorMowPowerMax){
    // mower motor overpowered    
    setActuator(ACT_MOTOR_MOW, 0);
    motorMowSenseCounter++;
    if (millis() > stateStartTime + 3000){
      motorMowSenseErrorCounter++;
      if (motorMowSenseErrorCounter > 15){
        Console.println("Error: Motor mow current");
        addErrorCounter(ERR_MOW_SENSE);
        setNextState(STATE_ERROR, 0);
        return;
      }
    }
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
      else reverseOrBidir(RIGHT);        
  }  
    
  if (motorLeftSense >=motorPowerMax){  
    // left wheel motor overpowered    
    if ((stateCurr == STATE_FORWARD) && (millis() > stateStartTime + 3000)){    				  
      //beep(1);
      motorLeftSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      reverseOrBidir(RIGHT);
    }
    else {
      if ((stateCurr == STATE_REVERSE) && (millis() > stateStartTime + 2000)){
      motorLeftSenseCounter++;
      setMotorSpeed( 0, 0, false );  
   //   reverseOrBidir(RIGHT);
      setNextState(STATE_ROLL,RIGHT);				          
      }
      else if ((stateCurr == STATE_ROLL) && (millis() > stateStartTime + 2000)){
      motorLeftSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      setNextState(STATE_FORWARD, 0);
      }
      }
  }
  else if (motorRightSense >= motorPowerMax){       
     // right wheel motor overpowered
     if ((stateCurr == STATE_FORWARD) && (millis() > stateStartTime + 3000)){    				  
      //beep(1);
      motorRightSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      reverseOrBidir(RIGHT);
    }
    else {
      if ((stateCurr == STATE_REVERSE) && (millis() > stateStartTime + 2000)){
      motorRightSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      setNextState(STATE_ROLL,LEFT);				          
      }
      else if ((stateCurr == STATE_ROLL) && (millis() > stateStartTime + 2000)){
      motorRightSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      setNextState(STATE_FORWARD, 0);
      }
      }
     }
  }  

// check bumpers
void Robot::checkBumpers(){
  if ((mowPatternCurr == MOW_BIDIR) && (millis() < stateStartTime + 4000)) return;

  if ((bumperLeft || bumperRight)) {    
      if (bumperLeft) {
        reverseOrBidir(RIGHT);          
      } else {
        reverseOrBidir(LEFT);
      }    
  }  
}

// check bumpers while tracking perimeter
void Robot::checkBumpersPerimeter(){
  if ((bumperLeft || bumperRight)) {    
    if ((bumperLeft) || (stateCurr == STATE_PERI_TRACK)) {
      setNextState(STATE_PERI_REV, RIGHT);          
    } else {
      setNextState(STATE_PERI_REV, LEFT);
    }
  }
}

// check perimeter as a boundary
void Robot::checkPerimeterBoundary(){
  if (mowPatternCurr == MOW_BIDIR){
    if ((millis() < stateStartTime + 3000)) return;    
    if (!perimeterLeftState) {
      if ((rand() % 2) == 0){      
        reverseOrBidir(LEFT);
      } else {
        reverseOrBidir(RIGHT);
      }     
    }
  } else {  
    if (stateCurr == STATE_FORWARD){
      //if ((millis() < stateStartTime + 2500)) return;    
      if (!perimeterLeftState) {
      //  if ((rand() % 2) == 0){      
          reverseOrBidir(LEFT);
      //  }// else {
        //  reverseOrBidir(RIGHT);
      //  }
      }
    } 
  }
}

// check perimeter while finding it
void Robot::checkPerimeterFind(){
  if (stateCurr == STATE_PERI_FIND){
    if (!perimeter.isInside()) setNextState(STATE_PERI_TRACK, 0);    
  }
}

 
// check lawn 
void Robot::checkLawn(){
  if ( (lawnSensor) && (millis() > stateStartTime + 3000) ) {      
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
       else reverseOrBidir(RIGHT);        
  } else lawnSensor = false;
}


// check sonar
void Robot::checkSonar(){
  if ((mowPatternCurr == MOW_BIDIR) && (millis() < stateStartTime + 4000)) return;
  
  // slow down motor wheel speed near obstacles   
  if (     (stateCurr == STATE_FORWARD) 
          || (  (mowPatternCurr == MOW_BIDIR) && ((stateCurr == STATE_FORWARD) || (stateCurr == STATE_REVERSE))  )  
     ){
        if (sonarObstacleTimeout == 0) {
          if (     ((NO_ECHO != sonarDistCenter) && (sonarDistCenter < sonarTriggerBelow*2)) 
               ||  ((NO_ECHO != sonarDistRight) && (sonarDistRight < sonarTriggerBelow*2)) 
               ||  ((NO_ECHO != sonarDistLeft) && (sonarDistLeft < sonarTriggerBelow*2))  ) {    
              //Console.println("sonar slow down");
              motorLeftSpeed /= 1.5;
              motorRightSpeed /= 1.5;
              sonarObstacleTimeout = millis() + 7000;
          }
        } else if ((sonarObstacleTimeout != 0) && (millis() > sonarObstacleTimeout)) {
          //Console.println("no sonar");
          sonarObstacleTimeout = 0;
          motorLeftSpeed *= 1.5;
          motorRightSpeed *= 1.5;
        }
    }  
  
  if ((sonarDistCenter != NO_ECHO) && (sonarDistCenter < sonarTriggerBelow)){
    sonarDistCounter++;    
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
      else reverseOrBidir(RIGHT);    
  }
  if ((sonarDistRight != NO_ECHO) && (sonarDistRight < sonarTriggerBelow)){
    sonarDistCounter++;     
    reverseOrBidir(LEFT);
  }
  if ((sonarDistLeft != NO_ECHO) && (sonarDistLeft < sonarTriggerBelow)){
    sonarDistCounter++;     
    reverseOrBidir(RIGHT);
  }
}


// check IMU (tilt)
void Robot::checkTilt(){
  int pitchAngle = (imuPitch/PI*180.0);
  int rollAngle  = (imuRoll/PI*180.0);
  if ( (stateCurr != STATE_OFF) && (stateCurr != STATE_ERROR) && (stateCurr != STATE_CHARGE) ){
    if ( (abs(pitchAngle) > 40) || (abs(rollAngle) > 40) ){
      Console.println("Error: IMU tilt");
      addErrorCounter(ERR_IMU_TILT);
      setNextState(STATE_ERROR,0);
    }
  }
  if (stateCurr == STATE_ERROR){
    //if ( (abs(pitchAngle) < 40) && (abs(rollAngle) < 40) ) setNextState(STATE_FORWARD,0);
  }
}


// calculate map position by odometry sensors
void Robot::calcOdometry(){
  static int lastOdoLeft = 0;
  static int lastOdoRight = 0;
  int odoLeft = odometryLeft;
  int odoRight = odometryRight;
  int ticksLeft = odoLeft - lastOdoLeft;
  int ticksRight = odoRight - lastOdoRight;
  lastOdoLeft = odoLeft;
  lastOdoRight = odoRight;    
  double left_cm = ((double)ticksLeft) / ((double)odometryTicksPerCm);
  double right_cm = ((double)ticksRight) / ((double)odometryTicksPerCm);  
  double avg_cm  = (left_cm + right_cm) / 2.0;
  double wheel_theta = (left_cm - right_cm) / ((double)odometryWheelBaseCm);
  odometryTheta += wheel_theta; 
  
  motorLeftRpmCounter = ticksLeft;
  motorLeftRpm = double ((((double)motorLeftRpmCounter/odometryTicksPerRevolution) / ((double)(millis() - lastMotorLeftRpmTime))) * 60000.0);
  motorLeftRpmCounter = 0;              
  lastMotorLeftRpmTime = millis();
  motorRightRpmCounter = ticksRight;
  motorRightRpm = double ((((double)motorRightRpmCounter/odometryTicksPerRevolution) / ((double)(millis() - lastMotorRightRpmTime))) * 60000.0);
  motorRightRpmCounter = 0;              
  lastMotorRightRpmTime = millis();
  
  //odometryTheta -= (double)((int)(odometryTheta/(2*PI)))*2*PI;
  //if (odometryTheta < -PI) odometryTheta += 2*PI; 
  //  else if (odometryTheta > PI) odometryTheta -= 2*PI;
  if (imuUse){
    odometryX += avg_cm * sin(imuYaw); 
    odometryY += avg_cm * cos(imuYaw); 
  } else {
    odometryX += avg_cm * sin(odometryTheta); 
    odometryY += avg_cm * cos(odometryTheta); 
 }
}


void Robot::loop()  {     
  unsigned long stateTime = millis() - stateStartTime;
  int steer;
  
  readSerial();   
  rc.readSerial();    
  readSensors();  

  if ((odometryUse) && (millis() >= nextTimeOdometryInfo)){
    nextTimeOdometryInfo = millis() + 300;
    //printOdometry();        
  }
  
  if (millis() >= nextTimePfodLoop){
    nextTimePfodLoop = millis() + 200;
    rc.run();        
  }
      
  if (millis() >= nextTimeInfo) {        
    nextTimeInfo = millis() + 1000;    
    ledState = ~ledState;    
    /*if (ledState) setActuator(ACT_LED, HIGH);
      else setActuator(ACT_LED, LOW);        */
    printInfo(Console);            
    checkTilt(); 
    //checkErrorCounter();    
    if (stateCurr == STATE_REMOTE) printRemote();    
    loopsPerSec = loopsPerSecCounter;
    if (loopsPerSec > 0) loopsTa = 1000.0 / ((double)loopsPerSec);    
    loopsPerSecCounter = 0;    
  }
      
  // state machine - things to do *PERMANENTLY* for current state
  switch (stateCurr) {
    case STATE_ERROR:
      // fatal-error
      if (millis() >= nextTimeErrorBeep){
        nextTimeErrorBeep = millis() + 300;
        beep(1, true);
      }
      //delay(100);                        
      break;
    case STATE_OFF:
      // robot is turned off      
      checkTimer();
      checkBattery();
      if (batMonitor){
        if (chgVoltage > 5.0){
          beep(2, true);      
          setNextState(STATE_CHARGE, 0);
        }
      }
      imuDriveHeading = imuYaw;
      break;
    case STATE_REMOTE:
      // remote control mode (RC)
      //if (remoteSwitch > 50) setNextState(STATE_FORWARD, 0);
      steer = ((double)motorSpeedMax/2) * (((double)remoteSteer)/100.0);
      if (remoteSpeed < 0) steer *= -1;
      motorLeftSpeed  = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) - steer; 
      motorRightSpeed = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) + steer; 
      motorLeftSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorLeftSpeed));
      motorRightSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorRightSpeed));
      motorMowSpeed = ((double)motorMowSpeedMax) * (((double)remoteMow)/100.0);      
      break;
    case STATE_MANUAL:
      break;
    case STATE_FORWARD:
      // driving forward            
      if (mowPatternCurr == MOW_BIDIR){
        double ratio = motorBiDirSpeedRatio1;
        if (stateTime > 4000) ratio = motorBiDirSpeedRatio2;
        if (rollDir == RIGHT) motorRightSpeed = ((double)motorLeftSpeed) * ratio;
          else motorLeftSpeed = ((double)motorRightSpeed) * ratio;                            
      }       
      checkErrorCounter();    
      checkTimer();
      checkCurrent();            
      checkBumpers();
      checkSonar();             
      checkBattery();
      checkPerimeterBoundary();      
      if (lawnSensorUse) checkLawn();      
      if (stateTime > motorForwTimeMax){ 
        // timeout 
        motorMowSenseErrorCounter = 0;
        if (rollDir == RIGHT) setNextState(STATE_REVERSE, LEFT); // toggle roll dir
          else setNextState(STATE_REVERSE, RIGHT);
      }
      break;
    case STATE_ROLL:
      checkCurrent();            
      checkBumpers();
      checkSonar();             
      checkBattery();
      checkPerimeterBoundary();      
      if (lawnSensorUse) checkLawn();
      // making a roll (left/right)            
      if (mowPatternCurr == MOW_LANES){
        if (abs(distancePI(imuYaw, imuRollHeading)) < PI/36) setNextState(STATE_FORWARD,0);				        
      } else {
        if (millis() >= stateEndTime) {
          setNextState(STATE_FORWARD,0);				          
        }        
      }
      break;
    case STATE_ROLL_WAIT:
      // making a roll (left/right)            
      //if (abs(distancePI(imuYaw, imuRollHeading)) < PI/36) setNextState(STATE_OFF,0);				
      break;
    case STATE_CIRCLE:
      // driving circles
      break;      
    case STATE_REVERSE:
      // driving reverse
        checkErrorCounter();    
        checkTimer();
        checkCurrent();            
        checkBumpers();
        checkSonar();             
        checkBattery();
        checkPerimeterBoundary();      
        if (lawnSensorUse) checkLawn();    
        
      if (mowPatternCurr == MOW_BIDIR){
        double ratio = motorBiDirSpeedRatio1;
        if (stateTime > 4000) ratio = motorBiDirSpeedRatio2;
        if (rollDir == RIGHT) motorRightSpeed = ((double)motorLeftSpeed) * ratio;
          else motorLeftSpeed = ((double)motorRightSpeed) * ratio;                                
        if (stateTime > motorForwTimeMax){ 
          // timeout 
          if (rollDir == RIGHT) setNextState(STATE_FORWARD, LEFT); // toggle roll dir
            else setNextState(STATE_FORWARD, RIGHT);
        }        
      } else {        
        if (millis() >= stateEndTime) {
          setNextState(STATE_ROLL, rollDir);				                         
        }
      }
      break;
    case STATE_PERI_ROLL:
      // perimeter tracking roll
      if (millis() >= stateEndTime) setNextState(STATE_PERI_FIND,0);				
      break;
    case STATE_PERI_REV:
      // perimeter tracking reverse
      if (millis() >= stateEndTime) setNextState(STATE_PERI_ROLL, rollDir);				               
      break;
    case STATE_PERI_FIND:
      // find perimeter
      checkCurrent();            
      checkBumpersPerimeter();
      checkSonar();                   
      checkPerimeterFind();
      break;
    case STATE_PERI_TRACK:
      // track perimeter
      //checkCurrent();                  
      checkBumpersPerimeter();
      //checkSonar();                   
      if (batMonitor){
        if (chgVoltage > 5.0){ 
          setNextState(STATE_CHARGE, 0);
        }
      }
      break;
    case STATE_CHARGE:
      // waiting until charging completed    
      checkTimer();       // Check Timer when on charge  
      break;      
    case STATE_CHARGE_REV:
      // charging: drive reverse 
      if (millis() >= stateEndTime) setNextState(STATE_CHARGE_ROLL, 0);				             
      break;
    case STATE_CHARGE_ROLL:
      // charging: roll 
      if (millis() >= stateEndTime) setNextState(STATE_CHARGE_FORW,0);				
      break;
    case STATE_CHARGE_FORW:
      // forward (charge station)    
      if (millis() >= stateEndTime) setNextState(STATE_FORWARD,0);				        
      break;      
  } // end switch  
      

  // next line deactivated (issue with RC failsafe)
  //if ((useRemoteRC) && (remoteSwitch < -50)) setNextState(STATE_REMOTE, 0);

  if (millis() >= nextTimeButtonCheck) {        
    nextTimeButtonCheck = millis() + 50;      
    if (buttonUse) checkButton();  
  }
    
  // decide which motor control to use
  if ( ((mowPatternCurr == MOW_LANES) && (stateCurr == STATE_ROLL)) || (stateCurr == STATE_ROLL_WAIT) ) motorControlImuRoll();
    else if (stateCurr == STATE_PERI_TRACK) motorControlPerimeter();
    else if (  (stateCurr == STATE_FORWARD)
     &&  (mowPatternCurr == MOW_RANDOM)
     && (imuUse) 
     && (imuCorrectDir || (mowPatternCurr == MOW_LANES))        
     && (millis() > stateStartTime + 3000) ) motorControlImuDir();
    else motorControl();  

  if (stateCurr != STATE_REMOTE) motorMowSpeed = motorMowSpeedMax;
  motorMowControl();  
  ADCMan.run();
  if (gpsUse) gps.run();
    
  bumperRight = false;
  bumperLeft = false;     
  
  delay(5);                           
  loopsPerSecCounter++;
  
}







