/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri   
 
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

#define MAGIC 26

char* stateNames[]={"OFF ", "RC  ", "FORW", "ROLL", "REV ", "CIRC", "ERR ", "PFND", "PTRK", "PROL", "PREV", "CHRG", 
  "CREV", "CROL", "CFOR", "MANU", "ROLW" };
  
char *mowPatternNames[] = {"RAND", "LANE", "BIDIR"};

char* consoleModeNames[]={"sen_counters", "sen_values", "perimeter"}; 


Robot::Robot(){
  name = "Generic";
  rc.setRobot(this);
  
  stateLast = stateCurr = stateNext = STATE_OFF; 
  stateTime = 0;
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
  lastMowSpeed = 0;

  bumperLeftCounter = bumperRightCounter = 0;
  bumperLeft = bumperRight = false;          
   
   dropLeftCounter = dropRightCounter = 0;                                                                                              // Dropsensor - Absturzsensor
   dropLeft = dropRight = false;                                                                                                        // Dropsensor - Absturzsensor
  
  gpsLat = gpsLon = gpsX = gpsY = 0;

  imuDriveHeading = 0;
  imuRollHeading = 0;
  imuRollDir = LEFT;  
  
  perimeterMag = 0;
  perimeterInside = true;
  perimeterCounter = 0;  
  perimeterLastTransitionTime = 0;
  perimeterTriggerTime = 0;
  
  lawnSensorCounter = 0;
  lawnSensor = false;
  lawnSensorFront = lawnSensorFrontOld = lawnSensorBack = lawnSensorBackOld = 0;  
  
  rain = false;
  rainCounter = 0;

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
  nextTimeDrop = 0;                                                                                                                    // Dropsensor - Absturzsensor
  nextTimeSonar = 0;
  nextTimeBattery = 0;
  nextTimePerimeter = 0;
  nextTimeLawnSensor = 0;
  nextTimeLawnSensorCheck = 0;
  nextTimeTimer = 0;
  nextTimeRTC = 0;
  nextTimeGPS = 0;
  nextTimePfodLoop = 0;
  nextTimeRain = 0;
  lastMotorMowRpmTime = millis();
  nextTimeButton = 0;
  nextTimeErrorCounterReset = 0;    
  nextTimeErrorBeep = 0;
  nextTimeMotorControl = 0;  
  nextTimeMotorMowControl = 0;
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
  eereadwrite(readflag, addr, motorMowPID.Kp);
  eereadwrite(readflag, addr, motorMowPID.Ki);
  eereadwrite(readflag, addr, motorMowPID.Kd);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio1);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio2);  
  eereadwrite(readflag, addr, bumperUse);
  eereadwrite(readflag, addr, sonarUse);
  eereadwrite(readflag, addr, sonarTriggerBelow);
  eereadwrite(readflag, addr, perimeterUse);
  eereadwrite(readflag, addr, perimeter.timedOutIfBelowSmag);        
  eereadwrite(readflag, addr, perimeterTriggerTimeout);
  eereadwrite(readflag, addr, perimeterTrackRollTime );
  eereadwrite(readflag, addr, perimeterTrackRevTime);
  eereadwrite(readflag, addr, perimeterPID.Kp);
  eereadwrite(readflag, addr, perimeterPID.Ki);
  eereadwrite(readflag, addr, perimeterPID.Kd);    
  eereadwrite(readflag, addr, lawnSensorUse);
  eereadwrite(readflag, addr, imuUse);
  eereadwrite(readflag, addr, imuCorrectDir);
  eereadwrite(readflag, addr, imuDirPID.Kp);
  eereadwrite(readflag, addr, imuDirPID.Ki);
  eereadwrite(readflag, addr, imuDirPID.Kd);  
  eereadwrite(readflag, addr, imuRollPID.Kp);    
  eereadwrite(readflag, addr, imuRollPID.Ki);    
  eereadwrite(readflag, addr, imuRollPID.Kd);      
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
  eereadwrite(readflag, addr, rainUse);
  eereadwrite(readflag, addr, gpsUse);
  // eereadwrite(readflag, addr, dropUse);                                                                                        // Dropsensor - Absturzsensor (nicht getestet)
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
void Robot::printSettingSerial(){
 
  // ------- wheel motors -----------------------------
  Console.print  ("motorAccel  : ");
  Console.println( motorAccel);
  Console.print  ("motorSpeedMax : ");
  Console.println(motorSpeedMax);
  Console.print  ("motorSpeedMaxPwm : "); 
  Console.println(motorSpeedMaxPwm);
  Console.print  ("motorPowerMax : ");    
  Console.println(motorPowerMax);
  Console.print  ("motorSenseRightScale : "); 
  Console.println(motorSenseRightScale);
  Console.print  ("motorSenseLeftScale : ");
  Console.println(motorSenseLeftScale);
  Console.print  ("motorRollTimeMax : ");
  Console.println(motorRollTimeMax);
  Console.print  ("motorReverseTime : ");
  Console.println(motorReverseTime);
  
  Console.print  ("motorForwTimeMax : ");
  Console.println(motorForwTimeMax);
  
  Console.print  ("motorBiDirSpeedRatio1 : ");
  Console.println(motorBiDirSpeedRatio1);
  
  Console.print  ("motorBiDirSpeedRatio2 : ");
  Console.println(motorBiDirSpeedRatio2);
  
  // ------ mower motor -------------------------------
  Console.print  ("motorMowAccel : ");
  Console.println(motorMowAccel);
  Console.print  ("motorMowSpeedMax : ");
  Console.println(motorMowSpeedMax);
  Console.print  ("motorMowPowerMax : ");
  Console.println(motorMowPowerMax);
  Console.print  ("motorMowModulate : ");
  Console.println(motorMowModulate);
  Console.print  ("motorMowRPM : ");  
  Console.println(motorMowRPM);
  Console.print  ("motorMowSenseScale : ");
  Console.println(motorMowSenseScale); 
  Console.print  ("motorMowPID.Kp : ");
  Console.println(motorMowPID.Kp);
  Console.print  ("motorMowPID.Ki : ");
  Console.println(motorMowPID.Ki);
  Console.print  ("motorMowPID.Kd : ");
  Console.println(motorMowPID.Kd);
  
  // ------ sonar ------------------------------------
  Console.print  ("sonarUse : ");
  Console.println(sonarUse);
  Console.print  ("sonarTriggerBelow : ");
  Console.println(sonarTriggerBelow);
  
  // ------ perimeter ---------------------------------
  Console.print  ("perimeterUse : ");
  Console.println(perimeterUse);
  Console.print  ("perimeterTriggerTimeout : ");
  Console.println(perimeterTriggerTimeout);
  Console.print  ("perimeterTrackRollTime : ");
  Console.println(perimeterTrackRollTime);
  Console.print  ("perimeterTrackRevTime : ");
  Console.println(perimeterTrackRevTime);
  Console.print  ("perimeterPID.Kp : ");
  Console.println(perimeterPID.Kp);
  Console.print  ("perimeterPID.Ki : ");
  Console.println( perimeterPID.Ki);
  Console.print  ("perimeterPID.Kd : ");
  Console.println(perimeterPID.Kd);
    
  // ------  IMU (compass/accel/gyro) ----------------------
  
  Console.print  ("imuUse : ");
  Console.println( imuUse);
  Console.print  ("imuCorrectDir : ");
  Console.println(imuCorrectDir); 
  Console.print  ("imuDirPID.Kp : ");
  Console.println(imuDirPID.Kp); 
  Console.print  ("imuDirPID.Ki : ");
  Console.println(imuDirPID.Ki); 
  Console.print  ("imuDirPID.Kd : ");
  Console.println( imuDirPID.Kd);
  Console.print  ("imuRollPID.Kp : ");
  Console.println(imuRollPID.Kp); 
  Console.print  ("imuRollPID.Ki : ");
  Console.println(imuRollPID.Ki); 
  Console.print  ("imuRollPID.Kd : ");
  Console.println(imuRollPID.Kd); 
  
  // ------ battery -------------------------------------
  
  Console.print  ("batMonitor : ");
  Console.println( batMonitor);
  Console.print  ("batGoHomeIfBelow : ");
  Console.println(batGoHomeIfBelow); 
  Console.print  ("batSwitchOffIfBelow : ");
  Console.println(batSwitchOffIfBelow); 
  Console.print  ("batFactor : ");
  Console.println( batFactor);
  Console.print  ("batChgFactor : ");  
  Console.println( batChgFactor);
  Console.print  ("batSenseZero : ");
  Console.println(batSenseZero); 
  Console.print  ("batFull : ");
  Console.println( batFull);
  Console.print  ("chgSenseZero : ");
  Console.println(chgSenseZero); 
  Console.print  ("chgFactor : ");
  Console.println( chgFactor);
  // ------  charging station ---------------------------
  
  Console.print  ("stationRevTime : ");
  Console.println(stationRevTime); 
  Console.print  ("stationRollTime : ");
  Console.println(stationRollTime); 
  Console.print  ("stationForwTime : ");
  Console.println( stationForwTime);
  // ------ odometry ------------------------------------
  
  Console.print  ("odometryUse : ");
  Console.println( odometryUse);
  Console.print  ("twoWayOdometrySensorUse : ");
  Console.println( twoWayOdometrySensorUse);
  Console.print  ("odometryTicksPerRevolution : ");
  Console.println( odometryTicksPerRevolution);
  Console.print  ("odometryTicksPerCm : ");
  Console.println( odometryTicksPerCm);
  Console.print  ("odometryWheelBaseCm : ");
  Console.println( odometryWheelBaseCm);

  return;
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


// ---- motor RPM (interrupt) --------------------------------------------------------------
// mower motor RPM driver
void Robot::setMotorMowRPMState(boolean motorMowRpmState){
  if (motorMowRpmState != motorMowRpmLastState) {    
    motorMowRpmLastState = motorMowRpmState;
    if (motorMowRpmLastState) motorMowRpmCounter++;   
  }
}


// ---- odometry (interrupt) --------------------------------------------------------
// Determines the rotation count and direction of the odometry encoders. Called in the odometry pins interrupt.
// Logic is: 
//    If the pin1 change transition (odometryLeftState) is LOW -> HIGH... 
//      If the pin2 current state is LOW :  step count forward   (odometryLeft++)
//        Otherwise :  step count reverse   (odometryLeft--)   
// odometryState:  1st left and right odometry signal
// odometryState2: 2nd left and right odometry signal (optional two-wire encoders)
void Robot::setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, boolean odometryLeftState2, boolean odometryRightState2){
  if (odometryLeftState != odometryLeftLastState){    
    if (odometryLeftState){
      if (twoWayOdometrySensorUse) {
        if (!odometryLeftState2) odometryLeft++; else odometryLeft--;
      } 
      else { 
         if (motorLeftPWM >0) odometryLeft++; else odometryLeft--;
      }
    }
    odometryLeftLastState = odometryLeftState;
  } 

  if (odometryRightState != odometryRightLastState){
    if (odometryRightState){
      if (twoWayOdometrySensorUse) {
        if (!odometryRightState2) odometryRight++; else odometryRight--;
      }     
      else {
         if (motorRightPWM >0) odometryRight++; else odometryRight--;    
      }
    }
    odometryRightLastState = odometryRightState;
  }  
  if (twoWayOdometrySensorUse) {
    if (odometryRightState2 != odometryRightLastState2){
      odometryRightLastState2 = odometryRightState2;    
    }  
    if (odometryLeftState2 != odometryLeftLastState2){
      odometryLeftLastState2 = odometryLeftState2;    
    }
  }    
}


// ---- RC (interrupt) --------------------------------------------------------------
// RC remote control helper
// convert ppm time (us) to percent (-100..+100)
// ppmtime: zero stick pos: 1500 uS 		
//          right stick pos: 2000 uS 		
//          left stick pos: 1000 uS
int Robot::rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;  //  ensures exact zero position
  return value;
}

// RC remote control driver
// 1. save time (uS) and RC channel states (HI/LO) 		
// 2. if new state is LO, evaluate ppm time for channel
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
  imuRollPID.x = distancePI(imu.ypr.yaw, imuRollHeading) / PI * 180.0;            
  //Console.println(imuRollPID.x);    
  imuRollPID.w = 0;
  imuRollPID.y_min = -motorSpeedMax;
  imuRollPID.y_max = motorSpeedMax;		
  imuRollPID.max_output = motorSpeedMax;
  imuRollPID.compute();						      
  setMotorSpeed( -imuRollPID.y, 
                +imuRollPID.y,  false);    
}


// PID controller: track perimeter 
void Robot::motorControlPerimeter(){      
  if ((millis() > stateStartTime + 5000) && (millis() > perimeterLastTransitionTime + 5000)){
    // robot is wheel-spinning while tracking => roll to get ground again
    if (perimeterMag < 0) setMotorSpeed( -motorSpeedMaxPwm/1.5, motorSpeedMaxPwm/1.5, false);
      else setMotorSpeed( motorSpeedMaxPwm/1.5, -motorSpeedMaxPwm/1.5, false);
    if (millis() > perimeterLastTransitionTime + 10000){      
      Console.println("Error: tracking error");
      addErrorCounter(ERR_TRACKING);
      //setNextState(STATE_ERROR,0);
      setNextState(STATE_PERI_FIND,0);
    }
    return;
  }   
  if (perimeterMag < 0) perimeterPID.x = -1;
    else if (perimeterMag > 0) perimeterPID.x = 1; 
    else perimeterPID.x = 0;
  perimeterPID.w = 0;
  /*perimeterPID.Kp= 50;
  perimeterPID.Ki= 10;
  perimeterPID.Kd= 10;*/
  perimeterPID.y_min = -motorSpeedMaxPwm;
  perimeterPID.y_max = motorSpeedMaxPwm;		
  perimeterPID.max_output = motorSpeedMaxPwm;
  perimeterPID.compute();
  //setMotorSpeed( motorLeftPWM  +perimeterPID.y, 
  //               motorRightPWM -perimeterPID.y, false);      
  setMotorSpeed( max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorSpeedMaxPwm/2 - perimeterPID.y)), 
                 max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorSpeedMaxPwm/2 + perimeterPID.y)), false);      
  /*Console.print(perimeterPID.x);
  Console.print("\t");          
  Console.println(perimeterPID.y);  */
}

// PID controller: correct direction during normal driving (requires IMU)
void Robot::motorControlImuDir(){
  int leftSpeed = motorLeftSpeed;    
  int rightSpeed = motorRightSpeed;
  imuDirPID.x = distancePI(imu.ypr.yaw, imuDriveHeading) / PI * 180.0;            
  //Console.println(imuDirPID.x);    
  imuDirPID.w = 0;
  imuDirPID.y_min = -motorSpeedMax;
  imuDirPID.y_max = motorSpeedMax;		
  imuDirPID.max_output = motorSpeedMax;
  imuDirPID.compute();	  					      
  setMotorSpeed( leftSpeed -imuDirPID.y, 
                 rightSpeed +imuDirPID.y, false );
}


void Robot::motorControl(){
  //double TA = ((double)(millis() - lastMotorControlTime)) / 1000.0;  
  // normal drive
  if (odometryUse){
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
  
    if (  ((stateCurr == STATE_OFF) || (stateCurr == STATE_CHARGE) || (stateCurr == STATE_ERROR)) && (millis()-stateStartTime>1000)  ){
      leftSpeed = rightSpeed = 0; // ensures PWM is zero if OFF/CHARGING
    }
    setMotorSpeed( leftSpeed, rightSpeed, false );  
  }
  else{
    int leftSpeed = min(motorSpeedMaxPwm, max(-motorSpeedMaxPwm, map(motorLeftSpeed, -motorSpeedMax, motorSpeedMax, -motorSpeedMaxPwm, motorSpeedMaxPwm)));
    int rightSpeed =min(motorSpeedMaxPwm, max(-motorSpeedMaxPwm, map(motorRightSpeed, -motorSpeedMax, motorSpeedMax, -motorSpeedMaxPwm, motorSpeedMaxPwm)));
    if (millis() < stateStartTime + 1000) {				
      leftSpeed = rightSpeed = 0; // slow down at state start      
      if (mowPatternCurr != MOW_LANES) imuDriveHeading = imu.ypr.yaw; // set drive heading    
    }
    setMotorSpeed( leftSpeed, rightSpeed, true );    
  }  
}


// motor mow speed controller (slowly adjusts output speed to given input speed)
// input: motorMowEnable, motorMowModulate, motorMowRpm
// output: motorMowPWM
void Robot::motorMowControl(){
  double mowSpeed ;
  if (!motorMowEnable) {
    mowSpeed = 0;         
    lastMowSpeed = mowSpeed;
    motorMowPID.esum=0; 
    motorMowPID.x = 0;    
    setMotorMowSpeed(mowSpeed, true);
  } 
  else {
    //if ((motorMowModulate) && (motorMowRpm != 0)){
      // speed sensor available
    if (motorMowModulate){


      if (mowSpeed <motorMowRPM ){

        mowSpeed = lastMowSpeed + 200;
        if (mowSpeed >motorMowRPM) mowSpeed = motorMowRPM;
      } else if (mowSpeed >motorMowRPM ){
        mowSpeed = lastMowSpeed - 200;
        if (mowSpeed <motorMowRPM) mowSpeed = motorMowRPM;
      }

      motorMowPID.x = 0.2* motorMowRpm + 0.8 * motorMowPID.x;      
      motorMowPID.w = mowSpeed; // 3300 => 2300
      motorMowPID.y_min = -motorMowSpeedMax/2;
      motorMowPID.y_max = motorMowSpeedMax/2;		
      motorMowPID.max_output = motorMowSpeedMax/2;
      motorMowPID.compute(); 

      setMotorMowSpeed(mowSpeed / 20.0 + motorMowPID.y, false);
      lastMowSpeed = mowSpeed;
    } else {
      // no speed sensor available      
      mowSpeed = motorMowSpeed;
      setMotorMowSpeed(mowSpeed, true);
    }
  }  
}

void Robot::beep(int numberOfBeeps, boolean shortbeep = false){
  for (int i=0; i < numberOfBeeps; i++){
    setActuator(ACT_BUZZER, 4200); 
    if (shortbeep) delay(50);
      else delay(500);
    setActuator(ACT_BUZZER, 0); 
    if (shortbeep) delay(250);
      else delay(500);
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
  beep(1);  
  Console.println(F("START"));  
  Console.print(F("Ardumower "));
  Console.println(VER);
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

  if (consoleMode == CONSOLE_OFF) {
  } else {
  Streamprint(s, "t%6u ", (millis()-stateStartTime)/1000);  
  Streamprint(s, "l%3u ", loopsPerSec);  
  //Streamprint(s, "r%4u ", freeRam());  
  Streamprint(s, "v%1d ", consoleMode);			    
  Streamprint(s, "%4s ", stateNames[stateCurr]);			    
  if (consoleMode == CONSOLE_PERIMETER){
    Streamprint(s, "sig min %4d max %4d avg %4d  mag %5d",
      (int)perimeter.getSignalMin(), (int)perimeter.getSignalMax(), (int)perimeter.getSignalAvg(),
      perimeterMag);
    Streamprint(s, "  in %2d  cnt %4d  on %1d\r\n",  
      (int)perimeterInside, perimeterCounter, (int)(!perimeter.signalTimedOut()) );      
  } else {  
    if (odometryUse) Streamprint(s, "odo %4d %4d ", (int)odometryLeft, (int)odometryRight);   
    Streamprint(s, "spd %4d %4d %4d ", (int)motorLeftSpeed, (int)motorRightSpeed, (int)motorMowRpm);
    if (consoleMode == CONSOLE_SENSOR_VALUES){
      // sensor values
      Streamprint(s, "sen %4d %4d %4d ", (int)motorLeftSense, (int)motorRightSense, (int)motorMowSense);
      Streamprint(s, "bum %4d %4d ", bumperLeft, bumperRight);
      Streamprint(s, "dro %4d %4d ", dropLeft, dropRight);                                                                                      // Dropsensor - Absturzsensor
      Streamprint(s, "son %4d %4d %4d ", sonarDistLeft, sonarDistCenter, sonarDistRight);
      Streamprint(s, "yaw %3d ", (int)(imu.ypr.yaw/PI*180.0));  
      Streamprint(s, "pit %3d ", (int)(imu.ypr.pitch/PI*180.0));
      Streamprint(s, "rol %3d ", (int)(imu.ypr.roll/PI*180.0));
      if (perimeterUse) Streamprint(s, "per %3d ", (int)perimeterInside);              
      if (lawnSensorUse) Streamprint(s, "lawn %3d %3d ", (int)lawnSensorFront, (int)lawnSensorBack);
    } else {
      // sensor counters
      Streamprint(s, "sen %4d %4d %4d ", motorLeftSenseCounter, motorRightSenseCounter, motorMowSenseCounter);
      Streamprint(s, "bum %4d %4d ", bumperLeftCounter, bumperRightCounter);
      Streamprint(s, "dro %4d %4d ", dropLeftCounter, dropRightCounter);                                                                      // Dropsensor - Absturzsensor
      Streamprint(s, "son %3d ", sonarDistCounter);
      Streamprint(s, "yaw %3d ", (int)(imu.ypr.yaw/PI*180.0));        
      Streamprint(s, "pit %3d ", (int)(imu.ypr.pitch/PI*180.0));
      Streamprint(s, "rol %3d ", (int)(imu.ypr.roll/PI*180.0));
      //Streamprint(s, "per %3d ", perimeterLeft);          
      if (perimeterUse) Streamprint(s, "per %3d ", perimeterCounter);                  
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
}

void Robot::printMenu(){  
  Console.println();
  Console.println(F("1=test motors"));
  Console.println(F("2=test odometry"));
  Console.println(F("3=setup BT module config (quick baudscan/recommended)"));
  Console.println(F("4=setup BT module config (extensive baudscan)"));
  Console.println(F("5=calibrate IMU acc next side"));
  Console.println(F("6=calibrate IMU com start/stop"));  
  Console.println(F("7=delete IMU calib"));
  Console.println(F("8=ADC calib"));  
  Console.println(F("9=load factory settings"));  
  Console.println(F("x=read settings"));  
  Console.println(F("0=exit"));  
  Console.println();
}

void Robot::delayInfo(int ms){
  unsigned long endtime = millis() +ms;
  while (millis() < endtime){
    readSensors();
    printInfo(Console);
    delay(1000);
  }
}

void Robot::testOdometry(){
  char ch;
  int lastLeft = 0;
  int lastRight = 0;
  motorLeftPWM = motorSpeedMaxPwm/5; motorRightPWM = motorSpeedMaxPwm/5;  
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);
  while (true){ 
    if ((odometryLeft != lastLeft) || (odometryRight != lastRight)) {
      Console.print(F("Press'f' forward, 'r' reverse, 'z' reset  "));
      Console.print(F("left="));
      Console.print(odometryLeft);
      Console.print(F("  right="));
      Console.println(odometryRight);              
      lastLeft = odometryLeft;
      lastRight = odometryRight;
    }
    delay(100);
    if (Console.available() > 0){
      ch = (char)Console.read();      
      if (ch == '0') break;
      if (ch == 'f') {
          motorLeftPWM = motorSpeedMaxPwm/5; motorRightPWM = motorSpeedMaxPwm/5;  
          setMotorSpeed(motorLeftPWM, motorRightPWM, false);
      }
      if (ch == 'r') {
          motorLeftPWM = -motorSpeedMaxPwm/5; motorRightPWM = -motorSpeedMaxPwm/5;  
          setMotorSpeed(motorLeftPWM, motorRightPWM, false);
      } 
      if (ch == 'z') {
          odometryLeft = 0; odometryRight = 0;
      }            
    }
  };
  motorLeftPWM = 0; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);          
}

void Robot::testMotors(){
  motorLeftPWM = 0; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);

  Console.println(F("testing left motor (forward) half speed..."));
  delay(1000);  
  motorLeftPWM = motorSpeedMaxPwm/2; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);
  delayInfo(5000);
  motorLeftPWM = 0; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);

  Console.println(F("testing left motor (reverse) full speed..."));
  delay(1000); 
  motorLeftPWM = -motorSpeedMaxPwm; motorRightPWM = 0; 
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);
  delayInfo(5000);  
  motorLeftPWM = 0; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);

  Console.println(F("testing right motor (forward) half speed..."));
  delay(1000);  
  motorLeftPWM = 0; motorRightPWM= motorSpeedMaxPwm/2; 
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);
  delayInfo(5000);
  motorLeftPWM = 0; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);

  Console.println(F("testing right motor (reverse) full speed..."));
  delay(1000);    
  motorLeftPWM = 0; motorRightPWM = -motorSpeedMaxPwm;      
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);
  delayInfo(5000);
  motorLeftPWM = 0; motorRightPWM = 0;
  setMotorSpeed(motorLeftPWM, motorRightPWM, false);  
}

void Robot::menu(){  
  char ch;  
  printMenu();  
  while(true){    
    imu.update();
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
          imu.calibAccNextAxis();
          printMenu();
          break;
        case '6':
          imu.calibComStartStop();          
          break;          
        case '7':
          imu.deleteCalib();
          printMenu();
          break;
        case '8':
          ADCMan.calibrate();
          break;
        case '9':
          deleteUserSettings();
          break;          
        case 'x':
          printSettingSerial();
          Console.println("fertig");
          break;          
      }      
    }
    delay(10);
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
         consoleMode = (consoleMode +1) % 4;
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
        case 'j':                                                                                                                    // Dropsensor - Absturzsensor
         dropLeft = true; // press 'j' to simulate left drop                                                                         // Dropsensor - Absturzsensor
         dropLeftCounter++;                                                                                                          // Dropsensor - Absturzsensor
        break;                                                                                                                       // Dropsensor - Absturzsensor
       case 'k':                                                                                                                     // Dropsensor - Absturzsensor
        dropRight = true; // press 'k' to simulate right drop                                                                        // Dropsensor - Absturzsensor
        dropRightCounter++;                                                                                                          // Dropsensor - Absturzsensor
        break;                                                                                                                       // Dropsensor - Absturzsensor
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
        // start normal without perimeter
        //motorMowEnable = false;        
        perimeterUse = false;
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
        /*if ((perimeterUse) && (!perimeter.isInside())){
          Console.println("start inside perimeter!");
          addErrorCounter(ERR_PERIMETER_TIMEOUT);
          setNextState(STATE_ERROR, 0);                          
        } else {*/
          // start normal with mowing        
          motorMowEnable = true;
          //motorMowModulate = true;                     
          mowPatternCurr = MOW_RANDOM;   
          setNextState(STATE_FORWARD, 0);                
        //}
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
    perimeterMag = readSensor(SEN_PERIM_LEFT);
    if ((perimeter.isInside() != perimeterInside)){      
      perimeterCounter++;
      perimeterLastTransitionTime = millis();
      perimeterInside = perimeter.isInside();
    }    
    if (perimeterInside) setActuator(ACT_LED, HIGH);    
      else setActuator(ACT_LED, LOW);      
    if ((!perimeterInside) && (perimeterTriggerTime == 0)){
      // set perimeter trigger time      
      if (millis() > stateStartTime + 2000){ // far away from perimeter?
        perimeterTriggerTime = millis() + perimeterTriggerTimeout;  
      } else {  
        perimeterTriggerTime = millis();
      }
    }
    if (perimeter.signalTimedOut())  {      
      if (stateCurr == STATE_FORWARD) {
        Console.println("Error: perimeter too far away");
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
     if ((dropUse) && (millis() >= nextTimeDrop)){                                                                          // Dropsensor - Absturzsensor
    nextTimeDrop = millis() + 100;                                                                                          // Dropsensor - Absturzsensor
    if (readSensor(SEN_DROP_LEFT) == dropcontact) {                                                                         // Dropsensor - Absturzsensor
      dropLeftCounter++;                                                                                                    // Dropsensor - Absturzsensor
      dropLeft=true;                                                                                                        // Dropsensor - Absturzsensor
    }                                                                                                                       // Dropsensor - Absturzsensor
 
  if (readSensor(SEN_DROP_RIGHT) == dropcontact) {                                                                          // Dropsensor - Absturzsensor
      dropRightCounter++;                                                                                                   // Dropsensor - Absturzsensor
      dropRight=true;                                                                                                       // Dropsensor - Absturzsensor
    } 
  }    
  
  if ((timerUse) && (millis() >= nextTimeRTC)) {
    // read RTC
    nextTimeRTC = millis() + 1000;    
    readSensor(SEN_RTC);                
  }
  
  if ((imuUse) && (millis() >= nextTimeIMU)) {
    // IMU
    readSensor(SEN_IMU);
    nextTimeIMU = millis() + 200;   // 5 hz
    if (imu.getErrorCounter()>0) {
      addErrorCounter(ERR_IMU_COMM);
      Console.println("IMU comm error");    
    }    
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
    double chgvolt = (((double)chgADC) - batSenseZero) * batChgFactor;
    double current = ((double)((int)(readSensor(SEN_CHG_CURRENT))));  
    // low-pass filter
    double accel = 0.01;
    if (abs(batVoltage-batvolt)>5)   batVoltage = batvolt; else batVoltage = (1.0-accel) * batVoltage + accel * batvolt;
    if (abs(chgVoltage-chgvolt)>5)   chgVoltage = chgvolt; else chgVoltage = (1.0-accel) * chgVoltage + accel * chgvolt;
    // if (abs(chgCurrent-current)>0.4) chgCurrent = current; else chgCurrent = (1.0-accel) * chgCurrent + accel * current;  //Deaktiviert für Ladestromsensor berechnung 

    // Anfang Ladestromsensor zur Glättung und Mittelwertbildung
    // ********************************************************************
    //  Variabeln
    double currentmitte;
    
    currentmitte = current;
    
    // ********************************************************************
    // Ende Ladestromsensor zur Glättung und Mittelwertbildung


   //  Anfang Ladestromsensor berechnen
   // ********************************************************************
   //  Variabeln 
    float vcc, asensor, amp;     
    float chgAMP;                                               //Sensorwert des Ladestrompin

    //Sensor Wert Ausgabe auf Seriellen Monitor oder HandyApp   wenn chgSelection =0
    if ((chgSelection)==0) chgCurrent = current;

    // Berechnung für Ladestromsensor ACS712 5A                 wenn chgSelection =1
    if ((chgSelection)==1) {

    chgAMP = currentmitte;                                     //Sensorwert übergabe vom Ladestrompin
    vcc = (float) 3.30 / chgSenseZero * 1023.0;                // Versorgungsspannung ermitteln!  chgSenseZero=511  ->Die Genauigkeit kann erhöt werden wenn der 3.3V Pin an ein Analogen Pin eingelesen wird. Dann ist vcc = (float) 3.30 / analogRead(X) * 1023.0;
    asensor = (float) chgAMP * vcc / 1023.0;                   // Messwert auslesen
    asensor = (float) asensor - (vcc/chgNull);                 // Nulldurchgang (vcc/2) abziehen
    chgSense = (float) chgSense - ((5.00-vcc)*chgFactor);      // Korrekturfactor für Vcc!  chgFactor=39
    amp = (float) asensor /chgSense *1000 ;                    // Ampere berechnen
    if (chgChange ==1) amp = amp / -1;                         //Lade Strom Messwertumkehr von - nach +
    if (amp<0.0) chgCurrent = 0; else chgCurrent = amp;        // Messwertrückgabe in chgCurrent   (Wenn Messwert kleiner als 0 dann Messwert =0 anssonsten messwertau8sgabe in Ampere)
    }
    
    // Berechnung für Ladestromsensor INA169 board              wenn chgSelection =2
    if ((chgSelection)==2) {
    chgAMP = currentmitte;
    asensor = ((chgAMP * 5) / 1023);                          // umrechnen von messwert in Spannung (5V Reference)
    amp = asensor / (10 * 0,1);                               // Ampere berechnen RL = 10k    Is = (Vout x 1k) / (RS x RL)
    if (amp<0.0) chgCurrent = 0; else chgCurrent = amp;       // Messwertrückgabe in chgCurrent   (Wenn Messwert kleiner als 0 dann Messwert =0 ansonsten Messwertaußsgabe in Ampere)
    }  
    
    
    //  Ladestromsensor berechnen ********** Ende
    // ********************************************************************

    //batVoltage = batVolt
    //chgVoltage = chgvolt;
    //chgCurrent = current;        
  }      
  if ((rainUse) && (millis() >= nextTimeRain)) {
    // read rain sensor
    nextTimeRain = millis() + 5000;
    rain = (readSensor(SEN_RAIN) != 0);  
    if (rain) rainCounter++;
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
  if (stateCurr == STATE_PERI_FIND){
    if (stateNew == STATE_ROLL) stateNew = STATE_PERI_ROLL;
    if (stateNew == STATE_REVERSE) stateNew = STATE_PERI_REV;    
  }  
  if (stateNew == STATE_FORWARD) {    
    if ((stateCurr == STATE_CHARGE_REV) ||(stateCurr == STATE_CHARGE_ROLL)) return;  
    if (stateCurr == STATE_CHARGE) {
      stateNew = STATE_CHARGE_REV;   
      setActuator(ACT_CHGRELAY, 0);         
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
    setActuator(ACT_CHGRELAY, 1); 
    setDefaults();        
  }
  if (stateNew == STATE_OFF){
    setActuator(ACT_CHGRELAY, 0);
    setDefaults();        
  }  
  if (stateNew == STATE_ERROR){
    motorMowEnable = false;    
    motorLeftSpeed = motorRightSpeed = 0;    
  }
  if (stateNew == STATE_PERI_FIND){
    // find perimeter  => drive half speed      
    motorLeftSpeed = motorRightSpeed = motorSpeedMax / 1.5;    
    //motorMowEnable = false;     // FIXME: should be an option?
  }
  if (stateNew == STATE_PERI_TRACK){        
    //motorMowEnable = false;     // FIXME: should be an option?
    setActuator(ACT_CHGRELAY, 0);
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
  perimeterTriggerTime=0;
  printInfo(Console);          
}

// check (low) battery
void Robot::checkBattery(){
  if (batMonitor){
    if ((batVoltage < batGoHomeIfBelow) && (stateCurr !=STATE_OFF)) {    // evl Fehlerhaft nicht getestet - Bei Batterieunterspannung aus ausgeschalteten Perimeter stoppt der Mover nicht sondern sucht den Perimeter. Änderung elv nach       if ((batVoltage < batGoHomeIfBelow) && (stateCurr !=STATE_OFF) && (perimeterUse = 1)) {
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
    // FIXME: doesn't work well with high gras :-/
    /*if (millis() > stateStartTime + motorReverseTime){
      motorMowSenseErrorCounter++;
      if (motorMowSenseErrorCounter > 15){
        Console.println("Error: Motor mow current");
        addErrorCounter(ERR_MOW_SENSE);
        setNextState(STATE_ERROR, 0);
        return;
      }
    }*/
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
      else reverseOrBidir(RIGHT);        
  }  
    
  if (motorLeftSense >=motorPowerMax){  
    // left wheel motor overpowered    
    if ((stateCurr == STATE_FORWARD) && (millis() > stateStartTime + motorReverseTime)){    				  
      //beep(1);
      motorLeftSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      reverseOrBidir(RIGHT);
    } else if ((stateCurr == STATE_REVERSE) && (millis() > stateStartTime + motorReverseTime)){
      motorLeftSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      //   reverseOrBidir(RIGHT);
      setNextState(STATE_ROLL,RIGHT);				          
    } else if ((stateCurr == STATE_ROLL) && (millis() > stateStartTime + motorReverseTime)){
      motorLeftSenseCounter++;
      setMotorSpeed( 0, 0, false );  
      setNextState(STATE_FORWARD, 0);
    }    
  }
  else if (motorRightSense >= motorPowerMax){       
     // right wheel motor overpowered
     if ((stateCurr == STATE_FORWARD) && (millis() > stateStartTime + motorReverseTime)){    				  
       //beep(1);
       motorRightSenseCounter++;
       setMotorSpeed( 0, 0, false );  
       reverseOrBidir(RIGHT);
     } else if ((stateCurr == STATE_REVERSE) && (millis() > stateStartTime + motorReverseTime)){
       motorRightSenseCounter++;
       setMotorSpeed( 0, 0, false );  
       setNextState(STATE_ROLL,LEFT);				          
     } else if ((stateCurr == STATE_ROLL) && (millis() > stateStartTime + motorReverseTime)){
       motorRightSenseCounter++;
       setMotorSpeed( 0, 0, false );  
       setNextState(STATE_FORWARD, 0);
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

// check drop                                                                                                                       // Dropsensor - Absturzsensor
void Robot::checkDrop(){                                                                                                            // Dropsensor - Absturzsensor
  if ((mowPatternCurr == MOW_BIDIR) && (millis() < stateStartTime + 4000)) return;                                                  // Dropsensor - Absturzsensor

  if ((dropLeft || dropRight)) {                                                                                                    // Dropsensor - Absturzsensor  
      if (dropLeft) {                                                                                                               // Dropsensor - Absturzsensor
        reverseOrBidir(RIGHT);                                                                                                      // Dropsensor - Absturzsensor     
      } else {                                                                                                                      // Dropsensor - Absturzsensor
        reverseOrBidir(LEFT);                                                                                                       // Dropsensor - Absturzsensor
      }                                                                                                                             // Dropsensor - Absturzsensor
  }                                                                                                                                 // Dropsensor - Absturzsensor
}                                                                                                                                   // Dropsensor - Absturzsensor

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
    if (!perimeterInside) {
      if ((rand() % 2) == 0){      
        reverseOrBidir(LEFT);
      } else {
        reverseOrBidir(RIGHT);
      }     
    }
  } else {  
    if (stateCurr == STATE_FORWARD){
      if (perimeterTriggerTime != 0) {
        if (millis() >= perimeterTriggerTime){        
          perimeterTriggerTime = 0;
          if ((rand() % 2) == 0){      
            reverseOrBidir(LEFT);
          } else {
            reverseOrBidir(RIGHT);
          }
        }
      }
    } 
  }
}

// check perimeter while finding it
void Robot::checkPerimeterFind(){
  if (stateCurr == STATE_PERI_FIND){
    if (perimeter.isInside()) {
      // inside
      if (motorLeftSpeed != motorRightSpeed){      
        // we just made an 'outside=>inside' rotation, now track
        setNextState(STATE_PERI_TRACK, 0);    
      }
    } else {
      // we are outside, now roll to get inside
      motorRightSpeed = -motorSpeedMax / 1.5;
      motorLeftSpeed  = motorSpeedMax / 1.5;
    }
  }
}

 
// check lawn 
void Robot::checkLawn(){
  if ( (lawnSensor) && (millis() > stateStartTime + 3000) ) {      
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
       else reverseOrBidir(RIGHT);        
  } else lawnSensor = false;
}

void Robot::checkRain(){
  if (rain){
    Console.println("RAIN");
    if (perimeterUse) setNextState(STATE_PERI_FIND, 0);    
      else setNextState(STATE_OFF, 0);    
  }
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
  int pitchAngle = (imu.ypr.pitch/PI*180.0);
  int rollAngle  = (imu.ypr.roll/PI*180.0);
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

void Robot::processGPSData()
{
  if (millis() < nextTimeGPS) return;
  nextTimeGPS = millis() + 1000;
  float nlat, nlon;
  unsigned long age;
  gps.f_get_position(&nlat, &nlon, &age);
  if (nlat == GPS::GPS_INVALID_F_ANGLE ) return;
  if (gpsLon == 0){
    gpsLon = nlon;  // this is xy (0,0)
    gpsLat = nlat;
    return;
  }
  gpsX = (float)gps.distance_between(nlat,  gpsLon,  gpsLat, gpsLon);
  gpsY = (float)gps.distance_between(gpsLat, nlon,   gpsLat, gpsLon);
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
    odometryX += avg_cm * sin(imu.ypr.yaw); 
    odometryY += avg_cm * cos(imu.ypr.yaw); 
  } else {
    odometryX += avg_cm * sin(odometryTheta); 
    odometryY += avg_cm * cos(odometryTheta); 
 }
}

void Robot::checkTimeout(){
  if (stateTime > motorForwTimeMax){ 
    // timeout 
    motorMowSenseErrorCounter = 0;
    if (rollDir == RIGHT) setNextState(STATE_REVERSE, LEFT); // toggle roll dir
      else setNextState(STATE_REVERSE, RIGHT);
  }
}


void Robot::loop()  {     
  stateTime = millis() - stateStartTime;
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
    if(imuUse) checkTilt(); 
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
      if (batMonitor && (millis()-stateStartTime>2000)){
        if ((chgVoltage > 5.0 ) && (batVoltage < (batFull-1.0)) ){
          beep(2, true);      
          setNextState(STATE_CHARGE, 0);
        }
      }
      imuDriveHeading = imu.ypr.yaw;
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
      checkRain();
      checkCurrent();            
      checkBumpers();
      checkDrop();                                                                                                                            // Dropsensor - Absturzsensor
      checkSonar();             
      checkBattery();
      checkPerimeterBoundary();      
      if (lawnSensorUse) checkLawn();      
      checkTimeout();      
      break;
    case STATE_ROLL:
      checkCurrent();            
      checkBumpers();
      checkDrop();                                                                                                                            // Dropsensor - Absturzsensor
      checkSonar();             
      checkBattery();
      checkPerimeterBoundary();      
      if (lawnSensorUse) checkLawn();
      // making a roll (left/right)            
      if (mowPatternCurr == MOW_LANES){
        if (abs(distancePI(imu.ypr.yaw, imuRollHeading)) < PI/36) setNextState(STATE_FORWARD,0);				        
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
        checkDrop();                                                                                                                            // Dropsensor - Absturzsensor
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
      if (motorLeftSpeed == motorRightSpeed){ // do not check during 'outside=>inside' rotation              
        checkCurrent();
        checkBumpersPerimeter();
        checkSonar();                           
      }  
      checkPerimeterFind();      
      checkTimeout();                    
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
      if (batMonitor)
      {
        if (chgCurrent < 1.0 && (millis()-stateStartTime>2000)) checkTimer();       // Check Timer when charged 
      } 
      else checkTimer();

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

  if (millis() >= nextTimeMotorControl) {            
    nextTimeMotorControl = millis() + 100;
    // decide which motor control to use
    if ( ((mowPatternCurr == MOW_LANES) && (stateCurr == STATE_ROLL)) || (stateCurr == STATE_ROLL_WAIT) ) motorControlImuRoll();
      else if (stateCurr == STATE_PERI_TRACK) motorControlPerimeter();
      else if (  (stateCurr == STATE_FORWARD)
       &&  (mowPatternCurr == MOW_RANDOM)
       && (imuUse) 
       && (imuCorrectDir || (mowPatternCurr == MOW_LANES))        
       && (millis() > stateStartTime + 3000) ) motorControlImuDir();
      else motorControl();  
  }
  
  if (stateCurr != STATE_REMOTE) motorMowSpeed = motorMowSpeedMax;
  if (millis() >= nextTimeMotorMowControl){
    nextTimeMotorMowControl = millis() + 500;
    motorMowControl();  
  }
    
  ADCMan.run();
  if (imuUse) imu.update();
  if (gpsUse) { 
    gps.feed();
    processGPSData();    
  }
    
  bumperRight = false;
  bumperLeft = false;     
  
  dropRight = false;                                                                                                                             // Dropsensor - Absturzsensor
  dropLeft = false;                                                                                                                              // Dropsensor - Absturzsensor
  
  delay(5);                           
  loopsPerSecCounter++;
  
}







