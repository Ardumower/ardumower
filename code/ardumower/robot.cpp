/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  Copyright (c) 2013-2015 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri    
  Copyright (c) 2014-2015 by Stefan Manteuffel
  Copyright (c) 2015 by Uwe Zimprich
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

#include "robot.h"

#define MAGIC 52


#define ADDR_USER_SETTINGS 0
#define ADDR_ERR_COUNTERS 400
#define ADDR_ROBOT_STATS 800

char* stateNames[]={"OFF ", "RC  ", "FORW", "ROLL", "REV ", "CIRC", "ERR ", "PFND", "PTRK", "PROL", "PREV", "STAT", "CHARG", "STCHK",
  "STREV", "STROL", "STFOR", "MANU", "ROLW", "POUTFOR", "POUTREV", "POUTROLL"};

char *mowPatternNames[] = {"RAND", "LANE", "BIDIR"};

char* consoleModeNames[]={"sen_counters", "sen_values", "perimeter"}; 


Robot::Robot(){
  name = "Generic";
  developerActive = false;
  rc.setRobot(this);
  
  stateLast = stateCurr = stateNext = STATE_OFF; 
  stateTime = 0;
  idleTimeSec = 0;
  statsMowTimeTotalStart = false;            
  mowPatternCurr = MOW_RANDOM;
  
  odometryLeft = odometryRight = 0;
  odometryLeftLastState = odometryLeftLastState2 = odometryRightLastState = odometryRightLastState2 = LOW;
  odometryTheta = odometryX = odometryY = 0;

    
  motorRightRpmCurr = motorLeftRpmCurr = 0;
  lastMotorRpmTime = 0;
  lastSetMotorSpeedTime = 0;
  motorLeftSpeedRpmSet =  motorRightSpeedRpmSet = 0; 
  motorLeftPWMCurr = motorRightPWMCurr = 0;
  motorRightSenseADC = motorLeftSenseADC = 0;
  motorLeftSenseCurrent = motorRightSenseCurrent = 0;     
  motorLeftSense = motorRightSense = 0;
  motorLeftSenseCounter = motorRightSenseCounter = 0;  
  motorZeroSettleTime = 0;  
  motorLeftZeroTimeout = 0;
  motorRightZeroTimeout = 0;  
  rotateLeft = true;
  
  remoteSteer = remoteSpeed = remoteMow = remoteSwitch = 0;  
  remoteSteerLastTime = remoteSpeedLastTime =remoteMowLastTime =remoteSwitchLastTime = 0;
  remoteSteerLastState = remoteSpeedLastState = remoteMowLastState = remoteSwitchLastState = LOW;

  motorMowRpmCounter = 0;
  motorMowRpmLastState = LOW;
  motorMowEnable = false;
  motorMowEnableOverride = false;
  motorMowSpeedPWMSet = motorSpeedMaxRpm;
  motorMowPWMCurr = 0;
  motorMowSenseADC = 0;
  motorMowSenseCurrent  = 0;
  motorMowSense = 0;
  motorMowSenseCounter = 0;
  motorMowSenseErrorCounter = 0;
  motorMowRpmCurr = 0;
  lastMowSpeedPWM = 0;
  lastSetMotorMowSpeedTime = 0;
  nextTimeCheckCurrent = 0;
  lastTimeMotorMowStuck = 0;

  bumperLeftCounter = bumperRightCounter = 0;
  bumperLeft = bumperRight = false;          
   
   dropLeftCounter = dropRightCounter = 0;                                                                                              // Dropsensor - Absturzsensor
   dropLeft = dropRight = false;                                                                                                        // Dropsensor - Absturzsensor
  
  gpsLat = gpsLon = gpsX = gpsY = 0;
  robotIsStuckCounter = 0;

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

  sonarLeftUse = sonarRightUse = sonarCenterUse = false;
  sonarDistCenter = sonarDistRight = sonarDistLeft = 0;
  sonarDistCounter = 0;
  tempSonarDistCounter = 0;
  sonarObstacleTimeout = 0;  

  batADC = 0;
  batVoltage = 0;
  batRefFactor = 0;
  batCapacity = 0;
  lastTimeBatCapacity = 0;
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
  nextTimeCheckTilt = 0;
  nextTimeOdometry = 0;
  nextTimeOdometryInfo = 0;
  nextTimeBumper = 0;
  nextTimeDrop = 0;                                                                                                                    // Dropsensor - Absturzsensor
  nextTimeSonar = 0;
  nextTimeBattery = 0;
  nextTimeCheckBattery = 0;
  nextTimePerimeter = 0;
  nextTimeLawnSensor = 0;
  nextTimeLawnSensorCheck = 0;
  nextTimeTimer = millis() + 60000;
  nextTimeRTC = 0;
  nextTimeGPS = 0;
  nextTimeCheckIfStuck = 0;
  nextTimePfodLoop = 0;
  nextTimeRain = 0;
  lastMotorMowRpmTime = millis();
  nextTimeButton = 0;
  nextTimeErrorCounterReset = 0;    
  nextTimeErrorBeep = 0;
  nextTimeMotorControl = 0;  
  nextTimeMotorImuControl = 0;
  nextTimeMotorPerimeterControl = 0;
  nextTimeMotorMowControl = 0;
  nextTimeRotationChange = 0;

  nextTimeRobotStats = 0;
  statsMowTimeMinutesTripCounter = 0;
  statsBatteryChargingCounter = 0;
}

  
char* Robot::stateName(){
  return stateNames[stateCurr];
}

char *Robot::mowPatternName(){
  return mowPatternNames[mowPatternCurr];
}

void Robot::loadSaveRobotStats(boolean readflag){
  if (readflag) Console.println(F("loadSaveRobotStats: read"));
    else Console.println(F("loadSaveRobotStats: write"));
  int addr = ADDR_ROBOT_STATS;
  short magic = 0;
  if (!readflag) magic = MAGIC;  
  eereadwrite(readflag, addr, magic); // magic
  if ((readflag) && (magic != MAGIC)) {
    Console.println(F("PLEASE CHECK IF YOUR ROBOT STATS ARE CORRECT"));
  }
  eereadwrite(readflag, addr, statsMowTimeMinutesTrip); 
  eereadwrite(readflag, addr, statsMowTimeMinutesTotal);
  eereadwrite(readflag, addr, statsBatteryChargingCounterTotal);
  eereadwrite(readflag, addr, statsBatteryChargingCapacityTrip);
  eereadwrite(readflag, addr, statsBatteryChargingCapacityTotal);
  eereadwrite(readflag, addr, statsBatteryChargingCapacityAverage);
   // <----------------------------new robot stats to save goes here!----------------
  Console.print(F("loadSaveRobotStats addrstop="));
  Console.println(addr);
}

void Robot::loadSaveErrorCounters(boolean readflag){
  if (readflag) Console.println(F("loadSaveErrorCounters: read"));
    else Console.println(F("loadSaveErrorCounters: write"));
  int addr = ADDR_ERR_COUNTERS;
  short magic = 0;
  if (!readflag) magic = MAGIC;  
  eereadwrite(readflag, addr, magic); // magic
  if ((readflag) && (magic != MAGIC)) {
    Console.println(F("EEPROM ERR COUNTERS: NO EEPROM ERROR DATA"));
    Console.println(F("PLEASE CHECK AND SAVE YOUR SETTINGS"));
    addErrorCounter(ERR_EEPROM_DATA);
    setNextState(STATE_ERROR, 0);
    return;
  }
  eereadwrite(readflag, addr, errorCounterMax);  
  Console.print(F("loadSaveErrorCounters addrstop="));
  Console.println(addr);
}

void Robot::loadSaveUserSettings(boolean readflag){
  int addr = ADDR_USER_SETTINGS;
  short magic = 0;
  if (!readflag) magic = MAGIC;  
  eereadwrite(readflag, addr, magic); // magic
  if ((readflag) && (magic != MAGIC)) {
    Console.println(F("EEPROM USERDATA: NO EEPROM USER DATA"));
    Console.println(F("PLEASE CHECK AND SAVE YOUR SETTINGS"));
    addErrorCounter(ERR_EEPROM_DATA);
    setNextState(STATE_ERROR, 0);
    return;
  }
  eereadwrite(readflag, addr, developerActive);          
  eereadwrite(readflag, addr, motorAccel);    
  eereadwrite(readflag, addr, motorSpeedMaxRpm);
  eereadwrite(readflag, addr, motorSpeedMaxPwm); 
  eereadwrite(readflag, addr, motorPowerMax);
  eereadwrite(readflag, addr, motorSenseRightScale);
  eereadwrite(readflag, addr, motorSenseLeftScale);
  eereadwrite(readflag, addr, motorRollTimeMax);
  eereadwrite(readflag, addr, motorRollTimeMin);
  eereadwrite(readflag, addr, motorReverseTime);
  eereadwrite(readflag, addr, motorPowerIgnoreTime);
  eereadwrite(readflag, addr, motorForwTimeMax);
  eereadwrite(readflag, addr, motorMowSpeedMaxPwm);
  eereadwrite(readflag, addr, motorMowPowerMax);
  eereadwrite(readflag, addr, motorMowRPMSet);
  eereadwrite(readflag, addr, motorMowSenseScale);
  eereadwrite(readflag, addr, motorLeftPID.Kp);
  eereadwrite(readflag, addr, motorLeftPID.Ki);
  eereadwrite(readflag, addr, motorLeftPID.Kd);
  eereadwrite(readflag, addr, motorMowPID.Kp);
  eereadwrite(readflag, addr, motorMowPID.Ki);
  eereadwrite(readflag, addr, motorMowPID.Kd);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio1);
  eereadwrite(readflag, addr, motorBiDirSpeedRatio2);  
  eereadwrite(readflag, addr, motorLeftSwapDir);
  eereadwrite(readflag, addr, motorRightSwapDir);  
  eereadwrite(readflag, addr, bumperUse);
  eereadwrite(readflag, addr, sonarUse);
  eereadwrite(readflag, addr, sonarCenterUse);
  eereadwrite(readflag, addr, sonarLeftUse);
  eereadwrite(readflag, addr, sonarRightUse);  
  eereadwrite(readflag, addr, sonarTriggerBelow);
  eereadwrite(readflag, addr, perimeterUse);
  eereadwrite(readflag, addr, perimeter.timedOutIfBelowSmag);        
  eereadwrite(readflag, addr, perimeterTriggerTimeout);
  eereadwrite(readflag, addr, perimeterOutRollTimeMax);
  eereadwrite(readflag, addr, perimeterOutRollTimeMin);
  eereadwrite(readflag, addr, perimeterOutRevTime);
  eereadwrite(readflag, addr, perimeterTrackRollTime );
  eereadwrite(readflag, addr, perimeterTrackRevTime);
  eereadwrite(readflag, addr, perimeterPID.Kp);
  eereadwrite(readflag, addr, perimeterPID.Ki);
  eereadwrite(readflag, addr, perimeterPID.Kd);
  eereadwrite(readflag, addr, perimeter.useDifferentialPerimeterSignal);        
  eereadwrite(readflag, addr, perimeter.swapCoilPolarity);  
  eereadwrite(readflag, addr, perimeter.timeOutSecIfNotInside);  
  eereadwrite(readflag, addr, trackingBlockInnerWheelWhilePerimeterStruggling);  
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
  eereadwrite(readflag, addr, batSwitchOffIfIdle);  
  eereadwrite(readflag, addr, batFactor);
  eereadwrite(readflag, addr, batChgFactor);
  eereadwrite(readflag, addr, chgSenseZero);
  eereadwrite(readflag, addr, chgFactor);
  eereadwrite(readflag, addr, batFullCurrent);
  eereadwrite(readflag, addr, startChargingIfBelow);
  eereadwrite(readflag, addr, stationRevTime);
  eereadwrite(readflag, addr, stationRollTime);
  eereadwrite(readflag, addr, stationForwTime);
  eereadwrite(readflag, addr, stationCheckTime);
  eereadwrite(readflag, addr, odometryUse);
  eereadwrite(readflag, addr, odometryTicksPerRevolution);
  eereadwrite(readflag, addr, odometryTicksPerCm);
  eereadwrite(readflag, addr, odometryWheelBaseCm);
  eereadwrite(readflag, addr, odometryLeftSwapDir);
  eereadwrite(readflag, addr, odometryRightSwapDir);
  eereadwrite(readflag, addr, twoWayOdometrySensorUse);
  eereadwrite(readflag, addr, buttonUse);
  eereadwrite(readflag, addr, userSwitch1);
  eereadwrite(readflag, addr, userSwitch2);
  eereadwrite(readflag, addr, userSwitch3);    
  eereadwrite(readflag, addr, timerUse);
  eereadwrite(readflag, addr, timer);  
  eereadwrite(readflag, addr, rainUse);
  eereadwrite(readflag, addr, gpsUse);
  eereadwrite(readflag, addr, stuckIfGpsSpeedBelow);
  eereadwrite(readflag, addr, gpsSpeedIgnoreTime);
  eereadwrite(readflag, addr, dropUse);   
  eereadwrite(readflag, addr, statsOverride);   
  eereadwrite(readflag, addr, bluetoothUse);
  eereadwrite(readflag, addr, esp8266Use);
  eereadwriteString(readflag, addr, esp8266ConfigString);
  Console.print(F("loadSaveUserSettings addrstop="));
  Console.println(addr);
}

void Robot::loadUserSettings(){  
  Console.println(F("loadUserSettings"));  
  loadSaveUserSettings(true);
}


void Robot::printSettingSerial(){
 
  // ------- wheel motors -----------------------------
  Console.print  (F("motorAccel  : "));
  Console.println(motorAccel);
  Console.print  (F("motorSpeedMaxRpm : "));
  Console.println(motorSpeedMaxRpm);
  Console.print  (F("motorSpeedMaxPwm : ")); 
  Console.println(motorSpeedMaxPwm);
  Console.print  (F("motorPowerMax : "));    
  Console.println(motorPowerMax);
  Console.print  (F("motorSenseRightScale : ")); 
  Console.println(motorSenseRightScale);
  Console.print  (F("motorSenseLeftScale : "));
  Console.println(motorSenseLeftScale);
  Console.print  (F("motorPowerIgnoreTime : "));
  Console.println(motorPowerIgnoreTime);
  Console.print  (F("motorZeroSettleTime : "));
  Console.println(motorZeroSettleTime);
  Console.print  (F("motorRollTimeMax : "));
  Console.println(motorRollTimeMax);
  Console.print  (F("motorRollTimeMin : "));
  Console.println(motorRollTimeMin);
  Console.print  (F("motorReverseTime : "));
  Console.println(motorReverseTime);
  
  Console.print  (F("motorForwTimeMax : "));
  Console.println(motorForwTimeMax);
  
  Console.print  (F("motorBiDirSpeedRatio1 : "));
  Console.println(motorBiDirSpeedRatio1);
  
  Console.print  (F("motorBiDirSpeedRatio2 : "));
  Console.println(motorBiDirSpeedRatio2);

  Console.print  (F("motorLeftPID.Kp : "));
  Console.println(motorLeftPID.Kp);
  Console.print  (F("motorLeftPID.Ki : "));
  Console.println(motorLeftPID.Ki);
  Console.print  (F("motorLeftPID.Kd : "));
  Console.println(motorLeftPID.Kd);

  Console.print  (F("motorRightSwapDir : "));
  Console.println(motorRightSwapDir);
  Console.print  (F("motorLeftSwapDir : "));
  Console.println(motorLeftSwapDir);
  
  // ------ mower motor -------------------------------
  Console.print  (F("motorMowAccel : "));
  Console.println(motorMowAccel);
  Console.print  (F("motorMowSpeedMaxPwm : "));
  Console.println(motorMowSpeedMaxPwm);
  Console.print  (F("motorMowPowerMax : "));
  Console.println(motorMowPowerMax);
  Console.print  (F("motorMowModulate : "));
  Console.println(motorMowModulate);
  Console.print  (F("motorMowRPMSet : "));  
  Console.println(motorMowRPMSet);
  Console.print  (F("motorMowSenseScale : "));
  Console.println(motorMowSenseScale); 
  Console.print  (F("motorMowPID.Kp : "));
  Console.println(motorMowPID.Kp);
  Console.print  (F("motorMowPID.Ki : "));
  Console.println(motorMowPID.Ki);
  Console.print  (F("motorMowPID.Kd : "));
  Console.println(motorMowPID.Kd);
  
  // ------ bumper ------------------------------------
  Console.print  (F("bumperUse : "));
  Console.println(bumperUse);

  // ------ drop ------------------------------------
  Console.print  (F("dropUse : "));
  Console.println(dropUse);

  Console.print  (F("dropContact : "));
  Console.println(dropcontact);

  // ------ rain ------------------------------------
  Console.print  (F("rainUse : "));
  Console.println(rainUse);

  // ------ sonar ------------------------------------
  Console.print  (F("sonarUse : "));
  Console.println(sonarUse);
  Console.print  (F("sonarLeftUse : "));
  Console.println(sonarLeftUse);
  Console.print  (F("sonarRightUse : "));
  Console.println(sonarRightUse);
  Console.print  (F("sonarCenterUse : "));
  Console.println(sonarCenterUse);
  Console.print  (F("sonarTriggerBelow : "));
  Console.println(sonarTriggerBelow);
  
  // ------ perimeter ---------------------------------
  Console.print  (F("perimeterUse : "));
  Console.println(perimeterUse);
  Console.print  (F("perimeterTriggerTimeout : "));
  Console.println(perimeterTriggerTimeout);
  Console.print  (F("perimeterOutRollTimeMax : "));
  Console.println(perimeterOutRollTimeMax);
  Console.print  (F("perimeterOutRollTimeMin : "));
  Console.println(perimeterOutRollTimeMin);
  Console.print  (F("perimeterOutRevTime : "));
  Console.println(perimeterOutRevTime);
  Console.print  (F("perimeterTrackRollTime : "));
  Console.println(perimeterTrackRollTime);
  Console.print  (F("perimeterTrackRevTime : "));
  Console.println(perimeterTrackRevTime);
  Console.print  (F("perimeterPID.Kp : "));
  Console.println(perimeterPID.Kp);
  Console.print  (F("perimeterPID.Ki : "));
  Console.println( perimeterPID.Ki);
  Console.print  (F("perimeterPID.Kd : "));
  Console.println(perimeterPID.Kd);
  Console.print  (F("trackingPerimeterTransitionTimeOut : "));
  Console.println(trackingPerimeterTransitionTimeOut);
  Console.print  (F("trackingErrorTimeOut : "));
  Console.println(trackingErrorTimeOut);
  Console.print  (F("trackingBlockInnerWheelWhilePerimeterStruggling : "));
  Console.println(trackingBlockInnerWheelWhilePerimeterStruggling);
  
  // ------ lawn sensor --------------------------------
  Console.print  (F("lawnSensorUse : "));
  Console.println(lawnSensorUse);

  // ------  IMU (compass/accel/gyro) ----------------------
  
  Console.print  (F("imuUse : "));
  Console.println( imuUse);
  Console.print  (F("imuCorrectDir : "));
  Console.println(imuCorrectDir); 
  Console.print  (F("imuDirPID.Kp : "));
  Console.println(imuDirPID.Kp); 
  Console.print  (F("imuDirPID.Ki : "));
  Console.println(imuDirPID.Ki); 
  Console.print  (F("imuDirPID.Kd : "));
  Console.println( imuDirPID.Kd);
  Console.print  (F("imuRollPID.Kp : "));
  Console.println(imuRollPID.Kp); 
  Console.print  (F("imuRollPID.Ki : "));
  Console.println(imuRollPID.Ki); 
  Console.print  (F("imuRollPID.Kd : "));
  Console.println(imuRollPID.Kd); 

  // ------ model R/C ------------------------------------
  Console.print  (F("remoteUse : "));
  Console.println(remoteUse); 
  
  // ------ battery -------------------------------------
  
  Console.print  (F("batMonitor : "));
  Console.println( batMonitor);
  Console.print  (F("batGoHomeIfBelow : "));
  Console.println(batGoHomeIfBelow); 
  Console.print  (F("batSwitchOffIfBelow : "));
  Console.println(batSwitchOffIfBelow); 
  Console.print  (F("batSwitchOffIfIdle : "));
  Console.println(batSwitchOffIfIdle); 
  Console.print  (F("batFactor : "));
  Console.println( batFactor);
  Console.print  (F("batChgFactor : "));  
  Console.println( batChgFactor);
  Console.print  (F("batFull : "));
  Console.println( batFull);
  Console.print  (F("batChargingCurrentMax : "));
  Console.println(batChargingCurrentMax); 
  Console.print  (F("batFullCurrent : "));
  Console.println(batFullCurrent); 
  Console.print  (F("startChargingIfBelow : "));
  Console.println(startChargingIfBelow); 
  Console.print  (F("chargingTimeout : "));
  Console.println(chargingTimeout); 
  Console.print  (F("chgSelection : "));
  Console.println(chgSelection); 
  Console.print  (F("chgSenseZero : "));
  Console.println(chgSenseZero); 
  Console.print  (F("chgFactor : "));
  Console.println( chgFactor);
  Console.print  (F("chgSense : "));
  Console.println(chgSense); 
  Console.print  (F("chgChange : "));
  Console.println(chgChange); 
  Console.print  (F("chgNull : "));
  Console.println(chgNull); 
  // ------  charging station ---------------------------
  
  Console.print  (F("stationRevTime : "));
  Console.println(stationRevTime); 
  Console.print  (F("stationRollTime : "));
  Console.println(stationRollTime); 
  Console.print  (F("stationForwTime : "));
  Console.println( stationForwTime);
  Console.print  (F("stationCheckTime : "));
  Console.println(stationCheckTime); 
  // ------ odometry ------------------------------------
  
  Console.print  (F("odometryUse : "));
  Console.println( odometryUse);
  Console.print  (F("twoWayOdometrySensorUse : "));
  Console.println( twoWayOdometrySensorUse);
  Console.print  (F("odometryTicksPerRevolution : "));
  Console.println( odometryTicksPerRevolution);
  Console.print  (F("odometryTicksPerCm : "));
  Console.println( odometryTicksPerCm);
  Console.print  (F("odometryWheelBaseCm : "));
  Console.println( odometryWheelBaseCm);
  Console.print  (F("odometryRightSwapDir : "));
  Console.println(odometryRightSwapDir); 
  Console.print  (F("odometryLeftSwapDir : "));
  Console.println(odometryLeftSwapDir); 

// ----- GPS -------------------------------------------
  Console.print  (F("gpsUse : "));
  Console.println(gpsUse); 
  Console.print  (F("stuckIfGpsSpeedBelow : "));
  Console.println(stuckIfGpsSpeedBelow); 
  Console.print  (F("gpsSpeedIgnoreTime : "));
  Console.println(gpsSpeedIgnoreTime); 
  

// ----- other -----------------------------------------
  Console.print  (F("buttonUse : "));
  Console.println(buttonUse); 

// ----- user-defined switch ---------------------------
  Console.print  (F("userSwitch1 : "));
  Console.println(userSwitch1); 
  Console.print  (F("userSwitch2 : "));
  Console.println(userSwitch2); 
  Console.print  (F("userSwitch3 : "));
  Console.println(userSwitch3); 

// ----- timer -----------------------------------------
  Console.print  (F("timerUse : "));
  Console.println(timerUse); 

// -------robot stats------------------------------------
  Console.print  (F("statsMowTimeMinutesTrip : "));
  Console.println(statsMowTimeMinutesTrip);
  Console.print  (F("statsMowTimeMinutesTotal : "));
  Console.println(statsMowTimeMinutesTotal);
  Console.print  (F("statsBatteryChargingCounterTotal : "));
  Console.println(statsBatteryChargingCounterTotal);
  Console.print  (F("statsBatteryChargingCapacityTrip in mAh : "));
  Console.println(statsBatteryChargingCapacityTrip);
  Console.print  (F("statsBatteryChargingCapacityTotal in Ah : "));
  Console.println(statsBatteryChargingCapacityTotal / 1000);
  Console.print  (F("statsBatteryChargingCapacityAverage in mAh : "));
  Console.println(statsBatteryChargingCapacityAverage);
  return;

}



void Robot::saveUserSettings(){
  Console.println(F("USER SETTINGS ARE SAVED"));
  loadSaveUserSettings(false);
}

void Robot::deleteUserSettings(){
  loadSaveRobotStats(true);
  int addr = 0;
  Console.println(F("ALL USER SETTINGS ARE DELETED"));
  eewrite(addr, (short)0); // magic  
  loadSaveRobotStats(false);
}

void Robot::deleteRobotStats(){
  statsMowTimeMinutesTrip = statsMowTimeMinutesTotal = statsBatteryChargingCounterTotal =
  statsBatteryChargingCapacityTotal = statsBatteryChargingCapacityTrip = 0;
  loadSaveRobotStats(false);
  Console.println(F("ALL ROBOT STATS ARE DELETED")); 
}

void Robot::addErrorCounter(byte errType){   
  // increase error counters (both temporary and maximum error counters)
  if (errorCounter[errType] < 255) errorCounter[errType]++;
  if (errorCounterMax[errType] < 255) errorCounterMax[errType]++;    
}

void Robot::resetErrorCounters(){
  Console.println(F("resetErrorCounters"));
  for (int i=0; i < ERR_ENUM_COUNT; i++) errorCounter[i]=errorCounterMax[i]=0;
  loadSaveErrorCounters(false);
  resetMotorFault();
}

void Robot::checkErrorCounter(){
  if (millis() >= nextTimeErrorCounterReset){
    // reset all temporary error counters after 30 seconds (maximum error counters still continue to count) 
    for (int i=0; i < ERR_ENUM_COUNT; i++) errorCounter[i]=0;
    nextTimeErrorCounterReset = millis() + 30000; // 30 sec
  }  
  if (stateCurr != STATE_OFF) {
   for (int i=0; i < ERR_ENUM_COUNT; i++){
     // set to fatal error if any temporary error counter reaches 10
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
// encoder signal/Ardumower pinout etc. at http://wiki.ardumower.de/index.php?title=Odometry
// Logic is: 
//    If the pin1 change transition (odometryLeftState) is LOW -> HIGH... 
//      If the pin2 current state is HIGH :  step count forward   (odometryLeft++)
//        Otherwise :  step count reverse   (odometryLeft--)   
// odometryState:  1st left and right odometry signal
// odometryState2: 2nd left and right odometry signal (optional two-wire encoders)
void Robot::setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, boolean odometryLeftState2, boolean odometryRightState2){
  int leftStep = 1;
  int rightStep = 1;
  if (odometryLeftSwapDir) leftStep = -1;
  if (odometryRightSwapDir) rightStep = -1;
  if (odometryLeftState != odometryLeftLastState){    
    if (odometryLeftState){ // pin1 makes LOW->HIGH transition
      if (twoWayOdometrySensorUse) { 
        // pin2 = HIGH? => forward 
        if (odometryLeftState2) odometryLeft += leftStep; else odometryLeft -= leftStep;
      } 
      else { 
         if (motorLeftPWMCurr >=0) odometryLeft ++; else odometryLeft --;
      }
    }
    odometryLeftLastState = odometryLeftState;
  } 

  if (odometryRightState != odometryRightLastState){
    if (odometryRightState){ // pin1 makes LOW->HIGH transition
      if (twoWayOdometrySensorUse) {
        // pin2 = HIGH? => forward
        if (odometryRightState2) odometryRight += rightStep; else odometryRight -= rightStep;
      }     
      else {
         if (motorRightPWMCurr >=0) odometryRight ++; else odometryRight --;    
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
// - driver protection: delays polarity change until motor speed (EMV) is zero
//   http://wiki.ardumower.de/images/a/a5/Motor_polarity_switch_protection.png 
// - optional: ensures that the motors (and gears) are not switched to 0% (or 100%) too fast (motorAccel)
void Robot::setMotorPWM(int pwmLeft, int pwmRight, boolean useAccel){
  unsigned long TaC = millis() - lastSetMotorSpeedTime;    // sampling time in millis
  lastSetMotorSpeedTime = millis();  
  if (TaC > 1000) TaC = 1;

  if (useAccel){  
    // http://phrogz.net/js/framerate-independent-low-pass-filter.html 
    // smoothed += elapsedTime * ( newValue - smoothed ) / smoothing;          
    motorLeftPWMCurr += TaC * (pwmLeft - motorLeftPWMCurr) / motorAccel;
    motorRightPWMCurr += TaC * (pwmRight - motorRightPWMCurr) / motorAccel;   
  }

  // ----- driver protection (avoids driver explosion) ----------
  if ( ((pwmLeft < 0) && (motorLeftPWMCurr >= 0)) ||
       ((pwmLeft > 0) && (motorLeftPWMCurr <= 0)) ) { // changing direction should take place?
    if (motorLeftZeroTimeout != 0)
      pwmLeft = motorLeftPWMCurr - motorLeftPWMCurr *  ((float)TaC)/200.0; // reduce speed
  }
  if ( ((pwmRight < 0) && (motorRightPWMCurr >= 0)) ||
       ((pwmRight > 0) && (motorRightPWMCurr <= 0)) ) { // changing direction should take place?    
    if (motorRightZeroTimeout != 0) // reduce motor rotation? (will reduce EMF)      
      pwmRight = motorRightPWMCurr - motorRightPWMCurr *   ((float)TaC)/200.0;  // reduce speed
  }

  motorLeftPWMCurr = pwmLeft;
  motorRightPWMCurr = pwmRight;

  if (odometryUse){
    if (abs(motorLeftRpmCurr) <1) motorLeftZeroTimeout = max(0, ((int)(motorLeftZeroTimeout - TaC)) );
      else motorLeftZeroTimeout = 500;
    if (abs(motorRightRpmCurr) <1) motorRightZeroTimeout = max(0, ((int)(motorRightZeroTimeout - TaC)) );      
      else motorRightZeroTimeout = 500;
  } else {
    if (pwmLeft == 0)  motorLeftZeroTimeout = max(0, ((int)(motorLeftZeroTimeout - TaC)) );
      else motorLeftZeroTimeout = 700;  
    if (pwmRight == 0) motorRightZeroTimeout = max(0, ((int)(motorRightZeroTimeout - TaC)) );      
      else motorRightZeroTimeout = 700;  
  }

  // ---------------------------------
  if (motorLeftSwapDir)  // swap pin polarity?
    setActuator(ACT_MOTOR_LEFT, -motorLeftPWMCurr);
  else
    setActuator(ACT_MOTOR_LEFT, motorLeftPWMCurr);
  if (motorRightSwapDir)   // swap pin polarity?
    setActuator(ACT_MOTOR_RIGHT, -motorRightPWMCurr);
  else 
    setActuator(ACT_MOTOR_RIGHT, motorRightPWMCurr);
}


// sets mower motor actuator
// - ensures that the motor is not switched to 100% too fast (motorMowAccel)
// - ensures that the motor voltage is not higher than motorMowSpeedMaxPwm
void Robot::setMotorMowPWM(int pwm, boolean useAccel){
  unsigned long TaC = millis() - lastSetMotorMowSpeedTime;    // sampling time in millis
  lastSetMotorMowSpeedTime = millis();  
  if (TaC > 1000) TaC = 1;  
  // we need to ignore acceleration for PID control, and we can ignore if speed is lowered (e.g. motor is shut down)
  if ( (!useAccel) || (pwm < motorMowPWMCurr) )
    motorMowPWMCurr = pwm;
  else {
    // http://phrogz.net/js/framerate-independent-low-pass-filter.html
    // smoothed += elapsedTime * ( newValue - smoothed ) / smoothing;          
    motorMowPWMCurr += TaC * (pwm - motorMowPWMCurr) / motorMowAccel;
  }
  setActuator(ACT_MOTOR_MOW, min(motorMowSpeedMaxPwm, max(0, motorMowPWMCurr)));
}

// PID controller: roll robot to heading (requires IMU)
void Robot::motorControlImuRoll(){
  if (millis() < nextTimeMotorImuControl) return;
  nextTimeMotorImuControl = millis() + 100;

  
  // Regelbereich entspricht 80% der maximalen Drehzahl am Antriebsrad (motorSpeedMaxRpm)
  imuRollPID.x = distancePI(imu.ypr.yaw, imuRollHeading) / PI * 180.0;            
  imuRollPID.w = 0;
  imuRollPID.y_min = -motorSpeedMaxRpm/1.25;        // da der Roll generell langsamer erfolgen soll
  imuRollPID.y_max = motorSpeedMaxRpm/1.25;   // 
  imuRollPID.max_output = motorSpeedMaxRpm/1.25;    //
  imuRollPID.compute();                 

  // Regelbereich entspricht maximaler PWM am Antriebsrad (motorSpeedMaxPwm), um auch an Steigungen höchstes Drehmoment für die Solldrehzahl zu gewährleisten
  motorLeftPID.x = motorLeftRpmCurr;                 // IST 
  motorLeftPID.w = -imuRollPID.y;                // SOLL 
  motorLeftPID.y_min = -motorSpeedMaxPwm;        // Regel-MIN
  motorLeftPID.y_max = motorSpeedMaxPwm;   // Regel-MAX
  motorLeftPID.max_output = motorSpeedMaxPwm;    // Begrenzung
  motorLeftPID.compute();
  int leftSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorLeftPWMCurr + motorLeftPID.y));
  //if((motorLeftSpeedRpmSet >= 0 ) && (leftSpeed <0 )) leftSpeed = 0;
  //if((motorLeftSpeedRpmSet <= 0 ) && (leftSpeed >0 )) leftSpeed = 0;     

  // Regelbereich entspricht maximaler PWM am Antriebsrad (motorSpeedMaxPwm), um auch an Steigungen höchstes Drehmoment für die Solldrehzahl zu gewährleisten
  motorRightPID.Kp = motorLeftPID.Kp;
  motorRightPID.Ki = motorLeftPID.Ki;
  motorRightPID.Kd = motorLeftPID.Kd;
  motorRightPID.x = motorRightRpmCurr;               // IST   
  motorRightPID.w = imuRollPID.y;                // SOLL
  motorRightPID.y_min = -motorSpeedMaxPwm;       // Regel-MIN
  motorRightPID.y_max = motorSpeedMaxPwm;  // Regel-MAX 
  motorRightPID.max_output = motorSpeedMaxPwm;   // Begrenzung
  motorRightPID.compute();            
  int rightSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorRightPWMCurr + motorRightPID.y));
  //if((motorRightSpeedRpmSet >= 0 ) && (rightSpeed <0 )) rightSpeed = 0;
  //if((motorRightSpeedRpmSet <= 0 ) && (rightSpeed >0 )) rightSpeed = 0;         

  if (  ((stateCurr == STATE_OFF) || (stateCurr == STATE_STATION) || (stateCurr == STATE_ERROR)) && (millis()-stateStartTime>1000)  ){
    leftSpeed = rightSpeed = 0; // ensures PWM is zero if OFF/CHARGING
  }
  setMotorPWM( leftSpeed, rightSpeed, false );                   

}



// PID controller: track perimeter 
void Robot::motorControlPerimeter(){    
  if (millis() < nextTimeMotorPerimeterControl) return;
    nextTimeMotorPerimeterControl = millis() + 100;

  if ((millis() > stateStartTime + 5000) && (millis() > perimeterLastTransitionTime + trackingPerimeterTransitionTimeOut)){
    // robot is wheel-spinning while tracking => roll to get ground again
    if (trackingBlockInnerWheelWhilePerimeterStruggling == 0){
    if (perimeterInside) setMotorPWM( -motorSpeedMaxPwm/1.5, motorSpeedMaxPwm/1.5, false);
        else setMotorPWM( motorSpeedMaxPwm/1.5, -motorSpeedMaxPwm/1.5, false);}

    else if (trackingBlockInnerWheelWhilePerimeterStruggling == 1){
      if (perimeterInside) setMotorPWM( 0, motorSpeedMaxPwm/1.5, false);
        else setMotorPWM( motorSpeedMaxPwm/1.5, 0, false);
    }

    if (millis() > perimeterLastTransitionTime + trackingErrorTimeOut){      
      Console.println("Error: tracking error");
      addErrorCounter(ERR_TRACKING);
      //setNextState(STATE_ERROR,0);
      setNextState(STATE_PERI_FIND,0);
    }
    return;
  }   
  if (perimeterInside)
      perimeterPID.x = -1;
    else
      perimeterPID.x = 1;

  perimeterPID.w = 0;
  perimeterPID.y_min = -motorSpeedMaxPwm;
  perimeterPID.y_max = motorSpeedMaxPwm;		
  perimeterPID.max_output = motorSpeedMaxPwm;
  perimeterPID.compute();
  //setMotorPWM( motorLeftPWMCurr  +perimeterPID.y, 
  //               motorRightPWMCurr -perimeterPID.y, false);      
  setMotorPWM( max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorSpeedMaxPwm/2 - perimeterPID.y)), 
                 max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorSpeedMaxPwm/2 + perimeterPID.y)), false);      
  /*Console.print(perimeterPID.x);
  Console.print("\t");          
  Console.println(perimeterPID.y);  */
}

// PID controller: correct direction during normal driving (requires IMU)
void Robot::motorControlImuDir(){
  if (millis() < nextTimeMotorImuControl) return;
    nextTimeMotorImuControl = millis() + 100;

  int correctLeft = 0;
  int correctRight = 0;
  
  // Regelbereich entspricht maximaler Drehzahl am Antriebsrad (motorSpeedMaxRpm)
  imuDirPID.x = distancePI(imu.ypr.yaw, imuDriveHeading) / PI * 180.0;            
  imuDirPID.w = 0;
  imuDirPID.y_min = -motorSpeedMaxRpm;
  imuDirPID.y_max = motorSpeedMaxRpm;    
  imuDirPID.max_output = motorSpeedMaxRpm;
  imuDirPID.compute();                    
                 
  if (imuDirPID.y < 0) correctRight = abs(imuDirPID.y);
  if (imuDirPID.y > 0) correctLeft  = abs(imuDirPID.y);
                 
  // Korrektur erfolgt über Abbremsen des linken Antriebsrades, falls Kursabweichung nach rechts
  // Regelbereich entspricht maximaler PWM am Antriebsrad (motorSpeedMaxPwm), um auch an Steigungen höchstes Drehmoment für die Solldrehzahl zu gewährleisten
  motorLeftPID.x = motorLeftRpmCurr;                     // IST 
  motorLeftPID.w = motorLeftSpeedRpmSet - correctLeft;     // SOLL 
  motorLeftPID.y_min = -motorSpeedMaxPwm;            // Regel-MIN
  motorLeftPID.y_max = motorSpeedMaxPwm;       // Regel-MAX
  motorLeftPID.max_output = motorSpeedMaxPwm;        // Begrenzung
  motorLeftPID.compute();
  int leftSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorLeftPWMCurr + motorLeftPID.y));
  if((motorLeftSpeedRpmSet >= 0 ) && (leftSpeed <0 )) leftSpeed = 0;
  if((motorLeftSpeedRpmSet <= 0 ) && (leftSpeed >0 )) leftSpeed = 0;    

  // Korrektur erfolgt über Abbremsen des rechten Antriebsrades, falls Kursabweichung nach links 
  // Regelbereich entspricht maximaler PWM am Antriebsrad (motorSpeedMaxPwm), um auch an Steigungen höchstes Drehmoment für die Solldrehzahl zu gewährleisten
  motorRightPID.Kp = motorLeftPID.Kp;
  motorRightPID.Ki = motorLeftPID.Ki;
  motorRightPID.Kd = motorLeftPID.Kd;
  motorRightPID.x = motorRightRpmCurr;                   // IST 
  motorRightPID.w = motorRightSpeedRpmSet - correctRight;  // SOLL 
  motorRightPID.y_min = -motorSpeedMaxPwm;           // Regel-MIN
  motorRightPID.y_max = motorSpeedMaxPwm;      // Regel-MAX
  motorRightPID.max_output = motorSpeedMaxPwm;       // Begrenzung
  motorRightPID.compute();            
  int rightSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorRightPWMCurr + motorRightPID.y));
  if((motorRightSpeedRpmSet >= 0 ) && (rightSpeed <0 )) rightSpeed = 0;
  if((motorRightSpeedRpmSet <= 0 ) && (rightSpeed >0 )) rightSpeed = 0;         
  
  if (  ((stateCurr == STATE_OFF) || (stateCurr == STATE_STATION) || (stateCurr == STATE_ERROR)) && (millis()-stateStartTime>1000)  ){
    leftSpeed = rightSpeed = 0; // ensures PWM is zero if OFF/CHARGING
  }
  setMotorPWM( leftSpeed, rightSpeed, false );                   
                 
}

// check for odometry sensor faults    
void Robot::checkOdometryFaults(){
  if (!odometryUse)  return;
  bool leftErr = false;
  bool rightErr = false;
  if ((stateCurr == STATE_FORWARD) &&  (millis()-stateStartTime>8000) ) {
    // just check if odometry sensors may not be working at all
    if ( (motorLeftPWMCurr > 100) && (abs(motorLeftRpmCurr) < 1)  )  leftErr = true;
    if ( (motorRightPWMCurr > 100) && (abs(motorRightRpmCurr) < 1)  ) rightErr = true;
  }  
  if ((stateCurr == STATE_ROLL) &&  (millis()-stateStartTime>1000) ) {
    // just check if odometry sensors may be turning in the wrong direction
    if ( ((motorLeftPWMCurr > 100) && (motorLeftRpmCurr < -3)) || ((motorLeftPWMCurr < -100) && (motorLeftRpmCurr > 3)) ) leftErr = true;
    if ( ((motorRightPWMCurr > 100) && (motorRightRpmCurr < -3)) || ((motorRightPWMCurr < -100) && (motorRightRpmCurr > 3)) ) rightErr = true;
  }  
  if (leftErr){
    Console.print("Left odometry error: PWM=");
    Console.print(motorLeftPWMCurr);
    Console.print("\tRPM=");
    Console.println(motorLeftRpmCurr);
    addErrorCounter(ERR_ODOMETRY_LEFT);
    setNextState(STATE_ERROR, 0);
  }
  if (rightErr){
    Console.print("Right odometry error: PWM=");
    Console.print(motorRightPWMCurr);
    Console.print("\tRPM=");
    Console.println(motorRightRpmCurr);
    addErrorCounter(ERR_ODOMETRY_RIGHT);
    setNextState(STATE_ERROR, 0);
  }
}


void Robot::motorControl(){
  if (millis() < nextTimeMotorControl) return;
    nextTimeMotorControl = millis() + 100;
    static unsigned long nextMotorControlOutputTime = 0;
  if (odometryUse){
    // Regelbereich entspricht maximaler PWM am Antriebsrad (motorSpeedMaxPwm), um auch an Steigungen höchstes Drehmoment für die Solldrehzahl zu gewährleisten
    motorLeftPID.w = motorLeftSpeedRpmSet;               // SOLL 
    motorRightPID.w = motorRightSpeedRpmSet;             // SOLL    
    float RLdiff = motorLeftRpmCurr - motorRightRpmCurr;
    if (motorLeftSpeedRpmSet == motorRightSpeedRpmSet){
      // line motion
      motorLeftPID.w = motorLeftSpeedRpmSet - RLdiff/2;
      motorRightPID.w = motorRightSpeedRpmSet + RLdiff/2;      
    }
    motorLeftPID.x = motorLeftRpmCurr;                 // IST     
    if (millis() < stateStartTime + motorZeroSettleTime) motorLeftPID.w = 0; // get zero speed first after state change
    motorLeftPID.y_min = -motorSpeedMaxPwm;        // Regel-MIN
    motorLeftPID.y_max = motorSpeedMaxPwm;     // Regel-MAX
    motorLeftPID.max_output = motorSpeedMaxPwm;    // Begrenzung
    motorLeftPID.compute();
    int leftSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorLeftPWMCurr + motorLeftPID.y));
    // Sven reported the next two lines do make the PID controlling worse
    //if((motorLeftSpeedRpmSet >= 0 ) && (leftSpeed <0 )) leftSpeed = 0;
    //if((motorLeftSpeedRpmSet <= 0 ) && (leftSpeed >0 )) leftSpeed = 0;     

    // Regelbereich entspricht maximaler PWM am Antriebsrad (motorSpeedMaxPwm), um auch an Steigungen höchstes Drehmoment für die Solldrehzahl zu gewährleisten
    motorRightPID.Kp = motorLeftPID.Kp;
    motorRightPID.Ki = motorLeftPID.Ki;
    motorRightPID.Kd = motorLeftPID.Kd;          
    motorRightPID.x = motorRightRpmCurr;               // IST
    if (millis() < stateStartTime + motorZeroSettleTime) motorRightPID.w = 0; // get zero speed first after state change
    motorRightPID.y_min = -motorSpeedMaxPwm;       // Regel-MIN
    motorRightPID.y_max = motorSpeedMaxPwm;        // Regel-MAX
    motorRightPID.max_output = motorSpeedMaxPwm;   // Begrenzung
    motorRightPID.compute();            
    int rightSpeed = max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, motorRightPWMCurr + motorRightPID.y));
    // Sven reported the next two lines do make the PID controlling worse
    //if((motorRightSpeedRpmSet >= 0 ) && (rightSpeed <0 )) rightSpeed = 0;
    //if((motorRightSpeedRpmSet <= 0 ) && (rightSpeed >0 )) rightSpeed = 0;         

    if ( (abs(motorLeftPID.x) < 2) && (abs(motorLeftPID.w) < 0.1) ) leftSpeed = 0; // ensures PWM is really zero 
    if ( (abs(motorRightPID.x)  < 2) && (abs(motorRightPID.w) < 0.1) ) rightSpeed = 0; // ensures PWM is really zero     

    /*if (millis() >= nextMotorControlOutputTime){
      nextMotorControlOutputTime = millis() + 3000; 
      Console.print("PID x=");
      Console.print(motorLeftPID.x);
      Console.print("\tPID w=");
      Console.print(motorLeftPID.w);
      Console.print("\tPID y=");
      Console.print(motorLeftPID.y);
      Console.print("\tPWM=");
      Console.println(leftSpeed);            
    } */ 

    setMotorPWM( leftSpeed, rightSpeed, false );              
  }
  else{
    int leftSpeed = min(motorSpeedMaxPwm, max(-motorSpeedMaxPwm, map(motorLeftSpeedRpmSet, -motorSpeedMaxRpm, motorSpeedMaxRpm, -motorSpeedMaxPwm, motorSpeedMaxPwm)));
    int rightSpeed =min(motorSpeedMaxPwm, max(-motorSpeedMaxPwm, map(motorRightSpeedRpmSet, -motorSpeedMaxRpm, motorSpeedMaxRpm, -motorSpeedMaxPwm, motorSpeedMaxPwm)));
    if (millis() < stateStartTime + motorZeroSettleTime) {
      leftSpeed = rightSpeed = 0; // slow down at state start      
      if (mowPatternCurr != MOW_LANES) imuDriveHeading = imu.ypr.yaw; // set drive heading    
    }
    setMotorPWM( leftSpeed, rightSpeed, true ); 
  }  
}


// motor mow speed controller (slowly adjusts output speed to given input speed)
// input: motorMowEnable, motorMowModulate, motorMowRpmCurr
// output: motorMowPWMCurr
void Robot::motorMowControl(){
  if (millis() < nextTimeMotorMowControl) return;

    nextTimeMotorMowControl = millis() + 100;
    if (motorMowEnableOverride) motorMowEnable = false;
  double mowSpeed ;
  if (!motorMowEnable) {
    mowSpeed = 0;         
    lastMowSpeedPWM = mowSpeed;
    motorMowPID.esum=0; 
    motorMowPID.x = 0;    
    setMotorMowPWM(mowSpeed, true);
  } 
  else {
    //if ((motorMowModulate) && (motorMowRpmCurr != 0)){
      // speed sensor available
    if (motorMowModulate){


      if (mowSpeed <motorMowRPMSet ){

        mowSpeed = lastMowSpeedPWM + 200;
        if (mowSpeed >motorMowRPMSet) mowSpeed = motorMowRPMSet;
      } else if (mowSpeed >motorMowRPMSet ){
        mowSpeed = lastMowSpeedPWM - 200;
        if (mowSpeed <motorMowRPMSet) mowSpeed = motorMowRPMSet;
      }

      motorMowPID.x = 0.2* motorMowRpmCurr + 0.8 * motorMowPID.x;      
      motorMowPID.w = mowSpeed; // 3300 => 2300
      motorMowPID.y_min = -motorMowSpeedMaxPwm/2;
      motorMowPID.y_max = motorMowSpeedMaxPwm/2;		
      motorMowPID.max_output = motorMowSpeedMaxPwm/2;
      motorMowPID.compute(); 

      setMotorMowPWM(mowSpeed / 20.0 + motorMowPID.y, false);
      lastMowSpeedPWM = mowSpeed;
    } 
    else {
      if((errorCounter[ERR_MOW_SENSE] == 0) && (errorCounter[ERR_STUCK] == 0)){
      // no speed sensor available      
      mowSpeed = motorMowSpeedPWMSet;
      setMotorMowPWM(mowSpeed, true);
      }
    }
  }  
}

void Robot::resetIdleTime(){
  if (idleTimeSec == BATTERY_SW_OFF){ // battery switched off?
    Console.println(F("BATTERY switching ON again"));
    setActuator(ACT_BATTERY_SW, 1);  // switch on battery again (if connected via USB)
  }
  idleTimeSec = 0;
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
  setMotorPWM(0, 0, false);
  loadSaveErrorCounters(true);
  loadUserSettings();
  if (!statsOverride) loadSaveRobotStats(true);
  else loadSaveRobotStats(false);
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
  #ifdef USE_DEVELOPER_TEST
    Console.println("Warning: USE_DEVELOPER_TEST activated");
  #endif
  Console.print(F("Config: "));
  Console.println(name);  
  Console.println(F("press..."));
  Console.println(F("  d for menu"));    
  Console.println(F("  v to change console output (sensor counters, values, perimeter etc.)"));    
  Console.println(consoleModeNames[consoleMode]);
} 


void Robot::printRemote(){
  Console.print(F("RC "));    
  Console.print(remoteSwitch);  
  Console.print(",");      
  Console.print(remoteSteer);
  Console.print(",");    
  Console.print(remoteSpeed);    
  Console.print(",");        
  Console.println(remoteMow);            
}

void Robot::printOdometry(){
  Console.print(F("ODO,"));
  Console.print(odometryX);
  Console.print(",");
  Console.println(odometryY);  
  Console.print(F("ODO,"));
  Console.print(odometryX);
  Console.print(",");
  Console.println(odometryY);  
}

void Robot::printInfo(Stream &s){
  
  /*Console.print(millis()/1000);
  Console.print(",");
  Console.print(motorMowRPMSet);
  Console.print(",");
  Console.print(motorMowRpmCurr);
  Console.print(",");
  Console.println(motorMowPWMCurr);
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
    Streamprint(s, "sig min %4d max %4d avg %4d mag %5d qty %3d",
      (int)perimeter.getSignalMin(0), (int)perimeter.getSignalMax(0), (int)perimeter.getSignalAvg(0),
      perimeterMag, (int)(perimeter.getFilterQuality(0)*100.0));
    Streamprint(s, "  in %2d  cnt %4d  on %1d\r\n",  
      (int)perimeterInside, perimeterCounter, (int)(!perimeter.signalTimedOut(0)) );      
  } else {  
    if (odometryUse) Streamprint(s, "odo %4d %4d ", (int)odometryLeft, (int)odometryRight);   
    Streamprint(s, "spd %4d %4d %4d ", (int)motorLeftSpeedRpmSet, (int)motorRightSpeedRpmSet, (int)motorMowRpmCurr);
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
  Console.println(F(" MAIN MENU:"));
  Console.println(F("1=test motors"));
  Console.println(F("2=test odometry"));
  Console.println(F("3=communications menu"));
  Console.println(F("5=calibrate IMU acc next side"));
  Console.println(F("6=calibrate IMU com start/stop"));  
  Console.println(F("7=delete IMU calib"));
  Console.println(F("8=ADC calib (perimeter sender, charger must be off)"));  
  Console.println(F("9=save user settings"));  
  Console.println(F("l=load factory settings"));  
  Console.println(F("r=delete robot stats"));  
  Console.println(F("x=read settings"));  
  Console.println(F("e=delete all errors"));  
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
  motorLeftPWMCurr = motorSpeedMaxPwm/2; motorRightPWMCurr = motorSpeedMaxPwm/2;  
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
  while (true){ 
    resetIdleTime();
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
          motorLeftPWMCurr = motorSpeedMaxPwm/2; motorRightPWMCurr = motorSpeedMaxPwm/2;  
          setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
      }
      if (ch == 'r') {
          motorLeftPWMCurr = -motorSpeedMaxPwm/2; motorRightPWMCurr = -motorSpeedMaxPwm/2;  
          setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
      } 
      if (ch == 'z') {
          odometryLeft = 0; odometryRight = 0;
      }            
    }
  };
  motorLeftPWMCurr = 0; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);          
}

void Robot::testMotors(){
  motorLeftPWMCurr = 0; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);

  Console.println(F("testing left motor (forward) half speed..."));
  delay(1000);  
  motorLeftPWMCurr = motorSpeedMaxPwm/2; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
  delayInfo(5000);
  motorLeftPWMCurr = 0; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);

  Console.println(F("testing left motor (reverse) full speed..."));
  delay(1000); 
  motorLeftPWMCurr = -motorSpeedMaxPwm; motorRightPWMCurr = 0; 
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
  delayInfo(5000);  
  motorLeftPWMCurr = 0; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);

  Console.println(F("testing right motor (forward) half speed..."));
  delay(1000);  
  motorLeftPWMCurr = 0; motorRightPWMCurr= motorSpeedMaxPwm/2; 
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
  delayInfo(5000);
  motorLeftPWMCurr = 0; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);

  Console.println(F("testing right motor (reverse) full speed..."));
  delay(1000);    
  motorLeftPWMCurr = 0; motorRightPWMCurr = -motorSpeedMaxPwm;      
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);
  delayInfo(5000);
  motorLeftPWMCurr = 0; motorRightPWMCurr = 0;
  setMotorPWM(motorLeftPWMCurr, motorRightPWMCurr, false);    
}

void Robot::menu(){  
  char ch;  
  printMenu();  
  while(true){    
    resetIdleTime();
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
          if (bluetoothUse)
            commsMenuBT();
          else if (esp8266Use)
            commsMenuWifi();
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
          saveUserSettings();
          printMenu();
          break;
        case 'l':
          printSettingSerial();
          deleteUserSettings();
          printMenu();
          break;    
        case 'r':
          printSettingSerial();
          deleteRobotStats();
          printMenu();
          break;              
        case 'x':
          printSettingSerial();
          Console.println(F("DONE"));
          printMenu();
          break;          
        case 'e':
        resetErrorCounters();
        setNextState(STATE_OFF, 0);
        Console.println(F("ALL ERRORS ARE DELETED"));
        printMenu();
        break;          
      }      
    }
    delay(10);
  }  
}



void Robot::commsMenuBT(){
  while(true){
    Console.println();
    Console.println(F("COMMUNICATIONS MENU  == Bluetooth =="));
    Console.println(F(" 1=Select other communication method"));
    Console.println(F(" 2=setup BT module config (quick baudscan (recommended))"));
    Console.println(F(" 3=setup BT module config (extensive baudscan)"));
    Console.println(F(" 0=Main Menu"));
    Console.println();

    delay(100);
    purgeConsole();

    switch (waitCharConsole()){
    case '0':
      return;
    case '1':
      commsMenuSelect();
      return;
    case '2':
      configureBluetooth(true);
      break;
    case '3':
      configureBluetooth(false);
      break;
    }
  }
}

void Robot::commsMenuWifi(){
  while(true){
    Console.println();
    Console.println(F("COMMUNICATIONS MENU  === WIFI =="));
    Console.print(F(" Current Config: \""));
    Console.print(esp8266ConfigString);
    Console.println(F("\""));
    Console.println(F(" 1=Select other communication method"));
    Console.println(F(" 2=configure"));
    Console.println(F(" 0=Main Menu"));
    Console.println();

    delay(100);
    purgeConsole();

    switch (waitCharConsole()){
    case '0':
      return;
    case '1':
      commsMenuSelect();
      return;
    case '2':
      Console.print(F("\nEnter Connection String: "));
      delay(100);
      purgeConsole();
      esp8266ConfigString = waitStringConsole();
      break;
    }
  }
}

void Robot::commsMenuSelect(void) {
  bluetoothUse = 0;
  esp8266Use = 0;

  while (true) {
    Console.println(F("Select communication method"));
    Console.println(F(" 1=Bluetooth"));
    Console.println(F(" 2=Wifi"));

    delay(100);
    purgeConsole();

    switch(waitCharConsole()) {
    case '1': bluetoothUse = 1; return;
    case '2': esp8266Use = 1; return;
    }
  }
}

void Robot::readSerial() {
  // serial input
  if (Console.available() > 0) {     
     char ch = (char)Console.read();
     resetIdleTime();
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
         if (stateCurr == STATE_OFF || stateCurr == STATE_MANUAL) motorMowEnableOverride = false; 
         else motorMowEnableOverride = !motorMowEnableOverride;
         motorMowEnable = !motorMowEnable; // press 'm' to toggle mower motor
         break;
       case 'c':
         setNextState(STATE_STATION, 0); // press 'c' to simulate in station
         break;
       case 'a':
         setNextState(STATE_STATION_CHARGING, 0); // press 't' to simulate in station charging
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
  if ( (!buttonUse) || (millis() < nextTimeButtonCheck) ) return;
    
  nextTimeButtonCheck = millis() + 50;      
  boolean buttonPressed = (readSensor(SEN_BUTTON) == LOW);    
  if ( ((!buttonPressed) && (buttonCounter > 0)) || ((buttonPressed) && (millis() >= nextTimeButton)) ) {                
    nextTimeButton = millis() + 1000;
    if (buttonPressed){
      Console.println(F("buttonPressed"));
      // ON/OFF button pressed                                                
      beep(1);
      buttonCounter++;
      resetIdleTime();
    } 
    else { 
      // ON/OFF button released          
      if  ( ((stateCurr != STATE_OFF) || (stateCurr == STATE_ERROR)) && (stateCurr != STATE_STATION) ) {
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
//NOTE: this function should only read in sensors into variables - it should NOT change any state!

  if (millis() >= nextTimeMotorSense){    
    nextTimeMotorSense = millis() +  50;
    double accel = 0.05;
    motorRightSenseADC = readSensor(SEN_MOTOR_RIGHT);
    motorLeftSenseADC = readSensor(SEN_MOTOR_LEFT);
    motorMowSenseADC = readSensor(SEN_MOTOR_MOW);
    
    motorRightSenseCurrent = motorRightSenseCurrent * (1.0-accel) + ((double)motorRightSenseADC) * motorSenseRightScale * accel;
    motorLeftSenseCurrent = motorLeftSenseCurrent * (1.0-accel) + ((double)motorLeftSenseADC) * motorSenseLeftScale * accel;
    motorMowSenseCurrent = motorMowSenseCurrent * (1.0-accel) + ((double)motorMowSenseADC) * motorMowSenseScale * accel;
   
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
      motorMowRpmCurr = readSensor(SEN_MOTOR_MOW_RPM);    
      if ((motorMowRpmCurr == 0) && (motorMowRpmCounter != 0)){
        // rpm may be updated via interrupt
        motorMowRpmCurr = (int) ((((double)motorMowRpmCounter) / ((double)(millis() - lastMotorMowRpmTime))) * 60000.0);
        motorMowRpmCounter = 0;        
      }       
      lastMotorMowRpmTime = millis();     
      if (!ADCMan.calibrationDataAvail()) {
        Console.println(F("Error: missing ADC calibration data"));
        addErrorCounter(ERR_ADC_CALIB);
        setNextState(STATE_ERROR, 0);
      }
    }
  }  


  if ((perimeterUse) && (millis() >= nextTimePerimeter)){    
    nextTimePerimeter = millis() +  50; // 50    
    perimeterMag = readSensor(SEN_PERIM_LEFT);
    if ((perimeter.isInside(0) != perimeterInside)){      
      perimeterCounter++;
      perimeterLastTransitionTime = millis();
      perimeterInside = perimeter.isInside(0);
    }    
    if (perimeterInside < 0) setActuator(ACT_LED, HIGH);
      else setActuator(ACT_LED, LOW);      
    if ((!perimeterInside) && (perimeterTriggerTime == 0)){
      // set perimeter trigger time      
      if (millis() > stateStartTime + 2000){ // far away from perimeter?
        perimeterTriggerTime = millis() + perimeterTriggerTimeout;  
      } else {  
        perimeterTriggerTime = millis();
      }
    }
    if (perimeter.signalTimedOut(0))  {      
      if ( (stateCurr != STATE_OFF) && (stateCurr != STATE_MANUAL) && (stateCurr != STATE_STATION) 
      	&& (stateCurr != STATE_STATION_CHARGING) && (stateCurr != STATE_STATION_CHECK) 
      	&& (stateCurr != STATE_STATION_REV) && (stateCurr != STATE_STATION_ROLL) 
      	&& (stateCurr != STATE_STATION_FORW) && (stateCurr != STATE_REMOTE) && (stateCurr != STATE_PERI_OUT_FORW)
        && (stateCurr != STATE_PERI_OUT_REV) && (stateCurr != STATE_PERI_OUT_ROLL)) {
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
      Console.print(F("LAWN "));
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
    //static char senSonarTurn = SEN_SONAR_RIGHT;    
    nextTimeSonar = millis() + 250;
    
    /*switch(senSonarTurn) {
      case SEN_SONAR_RIGHT:
        if (sonarRightUse) sonarDistRight = readSensor(SEN_SONAR_RIGHT);
        senSonarTurn = SEN_SONAR_LEFT;
        break;
      case SEN_SONAR_LEFT:
        if (sonarLeftUse) sonarDistLeft = readSensor(SEN_SONAR_LEFT);
        senSonarTurn = SEN_SONAR_CENTER;
        break;
      case SEN_SONAR_CENTER:
        if (sonarCenterUse) sonarDistCenter = readSensor(SEN_SONAR_CENTER);
        senSonarTurn = SEN_SONAR_RIGHT;
        break;
      default:
        senSonarTurn = SEN_SONAR_RIGHT;
        break;
    }   
    */
    if (sonarRightUse) sonarDistRight = readSensor(SEN_SONAR_RIGHT);    
    if (sonarLeftUse) sonarDistLeft = readSensor(SEN_SONAR_LEFT);    
    if (sonarCenterUse) sonarDistCenter = readSensor(SEN_SONAR_CENTER);    
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
    nextTimeRTC = millis() + 60000;    
    readSensor(SEN_RTC);       // read RTC             
    Console.print(F("RTC date received: "));
    Console.println(date2str(datetime.date));  
  }

  
  if ((imuUse) && (millis() >= nextTimeIMU)) {
    // IMU
    readSensor(SEN_IMU);
    nextTimeIMU = millis() + 200;   // 5 hz    
    if (imu.getErrorCounter()>0) {
      addErrorCounter(ERR_IMU_COMM);
      Console.println(F("IMU comm error"));    
    }    
    if (!imu.calibrationAvail) {
      Console.println(F("Error: missing IMU calibration data"));
      addErrorCounter(ERR_IMU_CALIB);
      setNextState(STATE_ERROR, 0);
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
    double batvolt = (double)batADC * batFactor / 10;  // / 10 due to arduremote bug, can be removed after fixing
    //double chgvolt = ((double)((int)(readSensor(SEN_CHG_VOLTAGE) / 10))) / 10.0;  
    int chgADC = readSensor(SEN_CHG_VOLTAGE);
    //Console.println(chgADC);
    double chgvolt = (double)chgADC * batChgFactor / 10;  // / 10 due to arduremote bug, can be removed after fixing
    double current = ((double)((int)(readSensor(SEN_CHG_CURRENT))));  
    // low-pass filter
    double accel = 0.01;
    if (abs(batVoltage-batvolt)>5)   batVoltage = batvolt; else batVoltage = (1.0-accel) * batVoltage + accel * batvolt;
    if (abs(chgVoltage-chgvolt)>5)   chgVoltage = chgvolt; else chgVoltage = (1.0-accel) * chgVoltage + accel * chgvolt;
    // if (abs(chgCurrent-current)>0.4) chgCurrent = current; else chgCurrent = (1.0-accel) * chgCurrent + accel * current;  //Deaktiviert für Ladestromsensor berechnung 

    // Anfang Ladestromsensor zur Glättung und Mittelwertbildung
    // ********************************************************************
    //  Variabeln
    double currentmitte = current;    
    // ********************************************************************
    // Ende Ladestromsensor zur Glättung und Mittelwertbildung


   //  Anfang Ladestromsensor berechnen
   // ********************************************************************
   //  Variabeln 
    float vcc, asensor, amp;     
    float chgAMP;                                               //Sensorwert des Ladestrompin

    //Sensor Wert Ausgabe auf Seriellen Monitor oder HandyApp   wenn chgSelection =0
    if (chgSelection==0) chgCurrent = current;

    // Berechnung für Ladestromsensor ACS712 5A                 wenn chgSelection =1
    if (chgSelection==1) {  
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
    if (chgSelection==2) {
      chgAMP = currentmitte;
      asensor = (chgAMP * 5) / 1023;                          // umrechnen von messwert in Spannung (5V Reference)
      amp = asensor / (10 * 0.1);                               // Ampere berechnen RL = 10k    Is = (Vout x 1k) / (RS x RL)
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
  motorLeftSpeedRpmSet = motorRightSpeedRpmSet = 0;    
  motorMowEnable = false;                
}

// set state machine new state
// http://wiki.ardumower.de/images/f/ff/Ardumower_states.png
// called *ONCE* to set to a *NEW* state
void Robot::setNextState(byte stateNew, byte dir){
  unsigned long stateTime = millis() - stateStartTime;
  if (stateNew == stateCurr) return;
  // state correction  
  if ((stateCurr == STATE_PERI_FIND) || (stateCurr == STATE_PERI_TRACK)) {
    if (stateNew == STATE_ROLL) stateNew = STATE_PERI_ROLL;
    if (stateNew == STATE_REVERSE) stateNew = STATE_PERI_REV;    
  }  
  if (stateNew == STATE_FORWARD) {    
    if ((stateCurr == STATE_STATION_REV) ||(stateCurr == STATE_STATION_ROLL) || (stateCurr == STATE_STATION_CHECK) ) return;  
    if ((stateCurr == STATE_STATION) || (stateCurr == STATE_STATION_CHARGING)) {
      stateNew = STATE_STATION_CHECK;   
      setActuator(ACT_CHGRELAY, 0);         
      motorMowEnable = false;
    } 
  }  
  // evaluate new state
  stateNext = stateNew;
  rollDir = dir;
  if (stateNew == STATE_STATION_REV){
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = -motorSpeedMaxRpm;                    
    stateEndTime = millis() + stationRevTime + motorZeroSettleTime;                     
  } else if (stateNew == STATE_STATION_ROLL){
    motorLeftSpeedRpmSet = motorSpeedMaxRpm;
    motorRightSpeedRpmSet = -motorSpeedMaxRpm;						      
    stateEndTime = millis() + stationRollTime + motorZeroSettleTime;                     
  } else if (stateNew == STATE_STATION_FORW){
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = motorSpeedMaxRpm;      
    motorMowEnable = true;    
    stateEndTime = millis() + stationForwTime + motorZeroSettleTime;                     
  } else if (stateNew == STATE_STATION_CHECK){
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = -motorSpeedMaxRpm/2; 
    stateEndTime = millis() + stationCheckTime + motorZeroSettleTime; 
  
  } else if (stateNew == STATE_PERI_ROLL) {    
    stateEndTime = millis() + perimeterTrackRollTime + motorZeroSettleTime;                     
    if (dir == RIGHT){
	motorLeftSpeedRpmSet = motorSpeedMaxRpm/2;
	motorRightSpeedRpmSet = -motorLeftSpeedRpmSet;						
      } else {
	motorRightSpeedRpmSet = motorSpeedMaxRpm/2;
	motorLeftSpeedRpmSet = -motorRightSpeedRpmSet;	
      }
  } if (stateNew == STATE_PERI_REV) {
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = -motorSpeedMaxRpm/2;                    
    stateEndTime = millis() + perimeterTrackRevTime + motorZeroSettleTime;                     
  }
  else if (stateNew == STATE_PERI_OUT_FORW){
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = motorSpeedMaxRpm;      
    stateEndTime = millis() + perimeterOutRevTime + motorZeroSettleTime + 1000;   
  }
  else if (stateNew == STATE_PERI_OUT_REV){
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = -motorSpeedMaxRpm/1.25;                    
    stateEndTime = millis() + perimeterOutRevTime + motorZeroSettleTime; 
  }
  else if (stateNew == STATE_PERI_OUT_ROLL){
    stateEndTime = millis() + random(perimeterOutRollTimeMin,perimeterOutRollTimeMax) + motorZeroSettleTime;
      if (dir == RIGHT){
    motorLeftSpeedRpmSet = motorSpeedMaxRpm/1.25;
    motorRightSpeedRpmSet = -motorLeftSpeedRpmSet;           
      } else {
    motorRightSpeedRpmSet = motorSpeedMaxRpm/1.25;
    motorLeftSpeedRpmSet = -motorRightSpeedRpmSet; 
      }
  }
  else if (stateNew == STATE_FORWARD){      
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = motorSpeedMaxRpm;  
    statsMowTimeTotalStart = true;            
  } 
  else if (stateNew == STATE_REVERSE)  {
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = -motorSpeedMaxRpm/1.25;                    
    stateEndTime = millis() + motorReverseTime + motorZeroSettleTime;
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
      stateEndTime = millis() + random(motorRollTimeMin,motorRollTimeMax) + motorZeroSettleTime;
      if (dir == RIGHT){
	motorLeftSpeedRpmSet = motorSpeedMaxRpm/1.25;
	motorRightSpeedRpmSet = -motorLeftSpeedRpmSet;						
      } else {
	motorRightSpeedRpmSet = motorSpeedMaxRpm/1.25;
	motorLeftSpeedRpmSet = -motorRightSpeedRpmSet

  ;	
      }      
  }  
  if (stateNew == STATE_REMOTE){
    motorMowEnable = true;
    //motorMowModulate = false;              
  } 
  if (stateNew == STATE_STATION){
    setMotorPWM(0,0,false);
    setActuator(ACT_CHGRELAY, 0); 
    setDefaults(); 
    statsMowTimeTotalStart = false;  // stop stats mowTime counter
    loadSaveRobotStats(false);        //save robot stats
       
  }
  if (stateNew == STATE_STATION_CHARGING){
    setActuator(ACT_CHGRELAY, 1); 
    setDefaults();        
  }
  if (stateNew == STATE_OFF){
    setActuator(ACT_CHGRELAY, 0);
    setDefaults();   
    statsMowTimeTotalStart = false; // stop stats mowTime counter
    loadSaveRobotStats(false);      //save robot stats
  }  
  if (stateNew == STATE_ERROR){
    motorMowEnable = false;    
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = 0; 
    setActuator(ACT_CHGRELAY, 0);
    statsMowTimeTotalStart = false;  
    //loadSaveRobotStats(false);   
  }
  if (stateNew == STATE_PERI_FIND){
    // find perimeter  => drive half speed      
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = motorSpeedMaxRpm / 1.5;    
    //motorMowEnable = false;     // FIXME: should be an option?
  }
  if (stateNew == STATE_PERI_TRACK){        
    //motorMowEnable = false;     // FIXME: should be an option?
    setActuator(ACT_CHGRELAY, 0);
    perimeterPID.reset();
    //beep(6);
  }   
  if (stateNew != STATE_REMOTE){
    motorMowSpeedPWMSet = motorMowSpeedMaxPwm;
  }
 
  sonarObstacleTimeout = 0;
  // state has changed    
  stateStartTime = millis();
  stateLast = stateCurr;
  stateCurr = stateNext;    
  perimeterTriggerTime=0;
  printInfo(Console);          
}

// check battery voltage and decide what to do
void Robot::checkBattery(){
if (millis() < nextTimeCheckBattery) return;
	nextTimeCheckBattery = millis() + 1000;  
  if (batMonitor){
    if ((batVoltage < batSwitchOffIfBelow) && (stateCurr !=STATE_ERROR) && (stateCurr !=STATE_OFF) && (stateCurr !=STATE_STATION) && (stateCurr !=STATE_STATION_CHARGING))  {
      Console.println(F("triggered batSwitchOffIfBelow"));
      addErrorCounter(ERR_BATTERY);
      beep(2, true);      
      setNextState(STATE_OFF, 0);
    }
    else if ((batVoltage < batGoHomeIfBelow) && (stateCurr != STATE_OFF) 
         && (stateCurr != STATE_MANUAL) && (stateCurr != STATE_STATION) 
         && (stateCurr != STATE_STATION_CHARGING) && (stateCurr != STATE_REMOTE) 
         && (stateCurr != STATE_ERROR) && (stateCurr != STATE_PERI_TRACK)
         && (perimeterUse)) {    //UNTESTED please verify
      Console.println(F("triggered batGoHomeIfBelow"));
      beep(2, true);      
      setNextState(STATE_PERI_FIND, 0);
    }
  }
  // check if idle and robot battery can be switched off  
  if ( (stateCurr == STATE_OFF) || (stateCurr == STATE_ERROR) ) {      
    if (idleTimeSec != BATTERY_SW_OFF){ // battery already switched off?
      idleTimeSec ++; // add one second idle time
      if (idleTimeSec > batSwitchOffIfIdle * 60) {        
        Console.println(F("triggered batSwitchOffIfIdle"));      
        beep(1, true);      
        loadSaveErrorCounters(false); // saves error counters
        loadSaveRobotStats(false);    // saves robot stats
        idleTimeSec = BATTERY_SW_OFF; // flag to remember that battery is switched off
        Console.println(F("BATTERY switching OFF"));
        setActuator(ACT_BATTERY_SW, 0);  // switch off battery               
      }
    }
  } else {
    resetIdleTime();          
  }
}


void Robot::receiveGPSTime(){
  if (gpsUse) {
    unsigned long chars = 0;
    unsigned short good_sentences = 0;
    unsigned short failed_cs = 0;
    gps.stats(&chars, &good_sentences, &failed_cs);    
    if (good_sentences == 0) {
      // no GPS sentences received so far
      Console.println(F("GPS communication error!"));      
      addErrorCounter(ERR_GPS_COMM);
      // next line commented out as GPS communication may not be available if GPS signal is poor
      //setNextState(STATE_ERROR, 0);
    }
    Console.print(F("GPS sentences: "));    
    Console.println(good_sentences);    
    Console.print(F("GPS satellites in view: "));          
    Console.println(gps.satellites());          
    if (gps.satellites() == 255) {
      // no GPS satellites received so far
      addErrorCounter(ERR_GPS_DATA);          
    }
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age; 
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    if (age != GPS::GPS_INVALID_AGE)
    {
      Console.print(F("GPS date received: "));
      Console.println(date2str(datetime.date));  
      datetime.date.dayOfWeek = getDayOfWeek(month, day, year, 1);      
      datetime.date.day = day;
      datetime.date.month = month;
      datetime.date.year = year;
      datetime.time.hour = hour;
      datetime.time.minute = minute;
      if (timerUse){
        // set RTC using GPS data
        Console.print(F("RTC date set: "));
        Console.println(date2str(datetime.date));  
        setActuator(ACT_RTC, 0);            
      }
    }      
  }
}

// check robot stats
void Robot::checkRobotStats(){
  if (millis() < nextTimeRobotStats) return;
      nextTimeRobotStats = millis() + 60000;

//----------------stats mow time------------------------------------------------------
  statsMowTimeHoursTotal = double(statsMowTimeMinutesTotal)/60; 
  if (statsMowTimeTotalStart) {
        statsMowTimeMinutesTripCounter++;
        statsMowTimeMinutesTrip = statsMowTimeMinutesTripCounter;
        statsMowTimeMinutesTotal++;
  } 
  else 
    if (statsMowTimeMinutesTripCounter != 0){
        statsMowTimeMinutesTripCounter = 0;

    }

//---------------stats Battery---------------------------------------------------------
  if ((stateCurr == STATE_STATION_CHARGING) && (stateTime >= 60000)){ // count only if mower is charged longer then 60sec
    statsBatteryChargingCounter++; // temporary counter
    if (statsBatteryChargingCounter == 1) statsBatteryChargingCounterTotal +=1; 
    statsBatteryChargingCapacityTrip = batCapacity;
    statsBatteryChargingCapacityTotal += (batCapacity - lastTimeBatCapacity); // summ up only the difference between actual batCapacity and last batCapacity
    lastTimeBatCapacity = batCapacity;
  }
  else{                         // resets values to 0 when mower is not charging
    statsBatteryChargingCounter = 0; 
    batCapacity = 0;
  }

  if(isnan(statsBatteryChargingCapacityTrip)) statsBatteryChargingCapacityTrip = 0;
  if(isnan(statsBatteryChargingCounterTotal)) statsBatteryChargingCounterTotal = 0; // for first run ensures that the counter is 0
  if(isnan(statsBatteryChargingCapacityTotal)) statsBatteryChargingCapacityTotal = 0; // for first run ensures that the counter is 0
  if(statsBatteryChargingCapacityTotal <= 0 || statsBatteryChargingCounterTotal == 0) statsBatteryChargingCapacityAverage = 0; // make sure that there is no dividing by zero
    else statsBatteryChargingCapacityAverage = statsBatteryChargingCapacityTotal / statsBatteryChargingCounterTotal;


//----------------new stats goes here------------------------------------------------------
}

// check timer
void Robot::checkTimer(){
  if (millis() < nextTimeTimer) return;
  nextTimeTimer = millis() + 60000;
  srand(time2minutes(datetime.time)); // initializes the pseudo-random number generator for c++ rand()
  randomSeed(time2minutes(datetime.time)); // initializes the pseudo-random number generator for arduino random()
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
            if ((stateCurr == STATE_STATION) || (stateCurr == STATE_OFF)){
              Console.println(F("timer start triggered"));
              motorMowEnable = true;
              setNextState(STATE_FORWARD, 0);
            } 
          }           
        }
      if ((stopTimerTriggered) && (timer[i].active)){
      if (stateCurr == STATE_FORWARD){
        Console.println(F("timer stop triggered"));
        if (perimeterUse){
        setNextState(STATE_PERI_FIND, 0);
      }
        else setNextState(STATE_OFF,0);
      } 
    }
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
  if (millis() < nextTimeCheckCurrent) return;
  nextTimeCheckCurrent = millis() + 100;

  if (motorMowSense >= motorMowPowerMax){
      motorMowSenseCounter++;
  }
  else{ 
      errorCounterMax[ERR_MOW_SENSE] = 0;
      motorMowSenseCounter = 0;
      if (millis() >= lastTimeMotorMowStuck + 30000){ // wait 30 seconds before switching on again
        errorCounter[ERR_MOW_SENSE] = 0;
        motorMowEnable = true;
      }
  }


  if (motorMowSenseCounter >= 30){ //ignore motorMowPower for 3 seconds
      motorMowEnable = false;
      Console.println("Error: Motor mow current");
      addErrorCounter(ERR_MOW_SENSE);
      lastTimeMotorMowStuck = millis();
     // if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
     //else reverseOrBidir(RIGHT); 
  }       

    
  if (motorLeftSense >=motorPowerMax){  
    // left wheel motor overpowered    
    if (     ((stateCurr == STATE_FORWARD) || (stateCurr == STATE_PERI_FIND)  || (stateCurr == STATE_PERI_TRACK)) 
          && (millis() > stateStartTime + motorPowerIgnoreTime)){    				  
      //beep(1);
      motorLeftSenseCounter++;
      setMotorPWM( 0, 0, false );  
      reverseOrBidir(RIGHT);
    } else if    ((stateCurr == STATE_REVERSE) && (millis() > stateStartTime + motorPowerIgnoreTime)){
      motorLeftSenseCounter++;
      setMotorPWM( 0, 0, false );  
      //   reverseOrBidir(RIGHT);
      setNextState(STATE_ROLL,RIGHT);				          
    } else if ((stateCurr == STATE_ROLL) && (millis() > stateStartTime + motorPowerIgnoreTime)){
      motorLeftSenseCounter++;
      setMotorPWM( 0, 0, false );  
      setNextState(STATE_FORWARD, 0);
    }    
  }
  else if (motorRightSense >= motorPowerMax){       
     // right wheel motor overpowered
     if ( ((stateCurr == STATE_FORWARD) || (stateCurr == STATE_PERI_FIND)) && (millis() > stateStartTime + motorPowerIgnoreTime)){    				  
       //beep(1);
       motorRightSenseCounter++;
       setMotorPWM( 0, 0, false );  
       reverseOrBidir(RIGHT);
     } else if ((stateCurr == STATE_REVERSE) && (millis() > stateStartTime + motorPowerIgnoreTime)){
       motorRightSenseCounter++;
       setMotorPWM( 0, 0, false );  
       setNextState(STATE_ROLL,LEFT);				          
     } else if ((stateCurr == STATE_ROLL) && (millis() > stateStartTime + motorPowerIgnoreTime)){
       motorRightSenseCounter++;
       setMotorPWM( 0, 0, false );  
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
  if (millis() >= nextTimeRotationChange){
      nextTimeRotationChange = millis() + 60000;
      rotateLeft = !rotateLeft;
    }

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
    if (stateCurr == STATE_FORWARD) {
      if (perimeterTriggerTime != 0) {
        if (millis() >= perimeterTriggerTime){        
          perimeterTriggerTime = 0;
          //if ((rand() % 2) == 0){  
          if(rotateLeft){  
          setNextState(STATE_PERI_OUT_REV, LEFT);
          } else {
          setNextState(STATE_PERI_OUT_REV, RIGHT);
          }
        }
      }
    } 
    else if ((stateCurr == STATE_ROLL)) {
      if (perimeterTriggerTime != 0) {
        if (millis() >= perimeterTriggerTime){ 
          perimeterTriggerTime = 0;
          setMotorPWM( 0, 0, false );
          //if ((rand() % 2) == 0){
          if (rotateLeft){    
          setNextState(STATE_PERI_OUT_FORW, LEFT);
          } else {
          setNextState(STATE_PERI_OUT_FORW, RIGHT);
          }  
        }
      }
    }
  }
}

// check perimeter while finding it
void Robot::checkPerimeterFind(){
  if (stateCurr == STATE_PERI_FIND){
    if (perimeterInside) {
      // inside
      if (motorLeftSpeedRpmSet != motorRightSpeedRpmSet){      
        // we just made an 'outside=>inside' rotation, now track
        setNextState(STATE_PERI_TRACK, 0);    
      }
    } else {
      // we are outside, now roll to get inside
      motorRightSpeedRpmSet = -motorSpeedMaxRpm / 1.5;
      motorLeftSpeedRpmSet  = motorSpeedMaxRpm / 1.5;
    }
  }
}

 
// check lawn 
void Robot::checkLawn(){
  if (!lawnSensorUse) return;
  if ( (lawnSensor) && (millis() > stateStartTime + 3000) ) {      
    if (rollDir == RIGHT) reverseOrBidir(LEFT); // toggle roll dir
       else reverseOrBidir(RIGHT);        
  } else lawnSensor = false;
}

void Robot::checkRain(){
  if (!rainUse) return;
  if (rain){
    Console.println(F("RAIN"));
    if (perimeterUse) setNextState(STATE_PERI_FIND, 0);    
      else setNextState(STATE_OFF, 0);    
  }
}

// check sonar
void Robot::checkSonar(){
  if(!sonarUse) return;
  if (millis() < nextTimeCheckSonar) return;
  nextTimeCheckSonar = millis() + 200;
  if ((mowPatternCurr == MOW_BIDIR) && (millis() < stateStartTime + 4000)) return;

  // slow down motor wheel speed near obstacles   
  if (     (stateCurr == STATE_FORWARD) 
          || (  (mowPatternCurr == MOW_BIDIR) && ((stateCurr == STATE_FORWARD) || (stateCurr == STATE_REVERSE))  )  
     ){
        if (sonarObstacleTimeout == 0) {
          if (     ((NO_ECHO != sonarDistCenter) && (sonarDistCenter < sonarTriggerBelow*2)) 
               ||  ((NO_ECHO != sonarDistRight) && (sonarDistRight < sonarTriggerBelow*2)) 
               ||  ((NO_ECHO != sonarDistLeft) && (sonarDistLeft < sonarTriggerBelow*2))  ) {    
              tempSonarDistCounter++;
            if (tempSonarDistCounter >= 5){
             // Console.println("sonar slow down");
              motorLeftSpeedRpmSet /= 1.5;
              motorRightSpeedRpmSet /= 1.5;
              sonarObstacleTimeout = millis() + 3000;
            }
          } else tempSonarDistCounter = 0;
        } else if ((sonarObstacleTimeout != 0) && (millis() > sonarObstacleTimeout)) {
          //Console.println("no sonar");
          sonarObstacleTimeout = 0;
          tempSonarDistCounter = 0;
          motorLeftSpeedRpmSet *= 1.5;
          motorRightSpeedRpmSet *= 1.5;
        }
    }  
  
  if ((sonarDistCenter != NO_ECHO) && (sonarDistCenter < sonarTriggerBelow)) {
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
  if(!imuUse) return;
  if (millis() < nextTimeCheckTilt) return;
  nextTimeCheckTilt = millis() + 200; // 5Hz same as nextTimeImu

  int pitchAngle = (imu.ypr.pitch/PI*180.0);
  int rollAngle  = (imu.ypr.roll/PI*180.0);
  if ( (stateCurr != STATE_OFF) && (stateCurr != STATE_ERROR) && (stateCurr != STATE_STATION) ){
    if ( (abs(pitchAngle) > 40) || (abs(rollAngle) > 40) ){
      Console.println(F("Error: IMU tilt"));
      addErrorCounter(ERR_IMU_TILT);
      setNextState(STATE_ERROR,0);
    }
  }
  if (stateCurr == STATE_ERROR){
    //if ( (abs(pitchAngle) < 40) && (abs(rollAngle) < 40) ) setNextState(STATE_FORWARD,0);
  }
}

// check if mower is stuck ToDo: take HDOP into consideration if gpsSpeed is reliable
void Robot::checkIfStuck(){
  if (millis() < nextTimeCheckIfStuck) return;
  nextTimeCheckIfStuck = millis() + 300;
  if ((gpsUse) && (gps.hdop() < 500))  {
  //float gpsSpeedRead = gps.f_speed_kmph();
  float gpsSpeed = gps.f_speed_kmph();
  if (gpsSpeedIgnoreTime >= motorReverseTime) gpsSpeedIgnoreTime = motorReverseTime - 500;
  // low-pass filter
   // double accel = 0.1;
   // float gpsSpeed = (1.0-accel) * gpsSpeed + accel * gpsSpeedRead;
   // Console.println(gpsSpeed);
     // Console.println(robotIsStuckCounter);
     // Console.println(errorCounter[ERR_STUCK]);
  if ((stateCurr != STATE_MANUAL) && (stateCurr != STATE_REMOTE) && (gpsSpeed <= stuckIfGpsSpeedBelow)    // checks if mower is stuck and counts up
      && ((motorLeftRpmCurr && motorRightRpmCurr) != 0) && (millis() > stateStartTime + gpsSpeedIgnoreTime) ){
      robotIsStuckCounter++;
  }

    else {                         // if mower gets unstuck it resets errorCounterMax to zero and reenabling motorMow
        robotIsStuckCounter = 0;    // resets temporary counter to zero
    if ( (errorCounter[ERR_STUCK] == 0) && (stateCurr != STATE_OFF) && (stateCurr != STATE_MANUAL) && (stateCurr != STATE_STATION) 
        && (stateCurr != STATE_STATION_CHARGING) && (stateCurr != STATE_STATION_CHECK) 
        && (stateCurr != STATE_STATION_REV) && (stateCurr != STATE_STATION_ROLL) 
        && (stateCurr != STATE_REMOTE) && (stateCurr != STATE_ERROR)) {
        motorMowEnable = true;
        errorCounterMax[ERR_STUCK] = 0;
  }
    return;
  }

  if (robotIsStuckCounter >= 5){    
    motorMowEnable = false;
    if (errorCounterMax[ERR_STUCK] >= 3){   // robot is definately stuck and unable to move
    Console.println(F("Error: Mower is stuck"));
    addErrorCounter(ERR_STUCK);
    setNextState(STATE_ERROR,0);    //mower is switched into ERROR
    //robotIsStuckCounter = 0;
    }
      else if (errorCounter[ERR_STUCK] < 3) {   // mower tries 3 times to get unstuck
        if (stateCurr == STATE_FORWARD){
      motorMowEnable = false;
      addErrorCounter(ERR_STUCK);             
      setMotorPWM( 0, 0, false );  
      reverseOrBidir(RIGHT);
    }
    else if (stateCurr == STATE_ROLL){
      motorMowEnable = false;
      addErrorCounter(ERR_STUCK);             
      setMotorPWM( 0, 0, false );  
      setNextState (STATE_FORWARD,0);
    }
    }
  }
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
  if ((!odometryUse) || (millis() < nextTimeOdometry)) return;    
    nextTimeOdometry = millis() + 300;

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
  
  motorLeftRpmCurr  = double ((( ((double)ticksLeft) / ((double)odometryTicksPerRevolution)) / ((double)(millis() - lastMotorRpmTime))) * 60000.0); 
  motorRightRpmCurr = double ((( ((double)ticksRight) / ((double)odometryTicksPerRevolution)) / ((double)(millis() - lastMotorRpmTime))) * 60000.0);                
  lastMotorRpmTime = millis();
               
  if (imuUse){
    odometryX += avg_cm * sin(imu.ypr.yaw); 
    odometryY += avg_cm * cos(imu.ypr.yaw); 
  } else {
    // FIXME: theta should be old theta, not new theta?
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


void Robot::purgeConsole() {
  while (Console.available())
    Console.read();
}

char Robot::waitCharConsole() {
  while (Console.available() == 0);
  return (char)Console.read();
}

String Robot::waitStringConsole() {
  String s = "";
  char ch;
  while (true) {
    ch = waitCharConsole();
    if (ch=='\n' || ch=='\r')
      break;
    else
      s += ch;
  };
  return s;
}

void Robot::loop()  {
  stateTime = millis() - stateStartTime;
  int steer;
  ADCMan.run();
  readSerial();   
  if (rc.readSerial()) resetIdleTime();
  readSensors(); 
  checkBattery(); 
  checkIfStuck();
  checkRobotStats();
  calcOdometry();
  checkOdometryFaults();    
  checkButton(); 
  motorMowControl(); 
  checkTilt(); 
  
  if (imuUse) imu.update();  

  if (gpsUse) { 
    gps.feed();
    processGPSData();    
  }

  if (millis() >= nextTimePfodLoop){
    nextTimePfodLoop = millis() + 200;
    rc.run();        
  }
   

  if (millis() >= nextTimeInfo) {        
    nextTimeInfo = millis() + 1000; 
    printInfo(Console);    
    ledState = ~ledState;    
    /*if (ledState) setActuator(ACT_LED, HIGH);
      else setActuator(ACT_LED, LOW);        */
    //checkErrorCounter();  
    if (stateCurr == STATE_REMOTE) printRemote();    
    loopsPerSec = loopsPerSecCounter;
    if (loopsPerSec > 0) loopsTa = 1000.0 / ((double)loopsPerSec);    
    loopsPerSecCounter = 0;    
  }   


      
   // state machine - things to do *PERMANENTLY* for current state
   // robot state machine
   // http://wiki.ardumower.de/images/f/ff/Ardumower_states.png
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
      //checkTimer();   // deactivated due to safety issues. when mower is off it should stay off. timer is only active when mower is n STATE_STATION.
      if (batMonitor && (millis()-stateStartTime>2000)){
        if ((chgVoltage > 5.0)  && (batVoltage > 8)){
          beep(2, true);      
          setNextState(STATE_STATION, 0);
        }
      }
      imuDriveHeading = imu.ypr.yaw;
      break;
    case STATE_REMOTE:
      // remote control mode (RC)
      //if (remoteSwitch > 50) setNextState(STATE_FORWARD, 0);
      steer = ((double)motorSpeedMaxRpm/2) * (((double)remoteSteer)/100.0);
      if (remoteSpeed < 0) steer *= -1;
      motorLeftSpeedRpmSet  = ((double)motorSpeedMaxRpm) * (((double)remoteSpeed)/100.0) - steer; 
      motorRightSpeedRpmSet = ((double)motorSpeedMaxRpm) * (((double)remoteSpeed)/100.0) + steer; 
      motorLeftSpeedRpmSet = max(-motorSpeedMaxRpm, min(motorSpeedMaxRpm, motorLeftSpeedRpmSet));
      motorRightSpeedRpmSet = max(-motorSpeedMaxRpm, min(motorSpeedMaxRpm, motorRightSpeedRpmSet));
      motorMowSpeedPWMSet = ((double)motorMowSpeedMaxPwm) * (((double)remoteMow)/100.0);      
      break;
    case STATE_MANUAL:
      break;
    case STATE_FORWARD:
      // driving forward            
      if (mowPatternCurr == MOW_BIDIR){
        double ratio = motorBiDirSpeedRatio1;
        if (stateTime > 4000) ratio = motorBiDirSpeedRatio2;
        if (rollDir == RIGHT) motorRightSpeedRpmSet = ((double)motorLeftSpeedRpmSet) * ratio;
          else motorLeftSpeedRpmSet = ((double)motorRightSpeedRpmSet) * ratio;                            
      }             
      checkErrorCounter();    
      checkTimer();
      checkRain();
      checkCurrent();            
      checkBumpers();
      checkDrop();                                                                                                                            // Dropsensor - Absturzsensor
      checkSonar();             
      checkPerimeterBoundary(); 
      checkLawn();      
      checkTimeout();      
      break;
    case STATE_ROLL:
      checkCurrent();            
      checkBumpers();
      checkDrop();                                                                                                                            // Dropsensor - Absturzsensor
      //checkSonar();             
      checkPerimeterBoundary(); 
      checkLawn();
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
        //checkSonar();             
        checkPerimeterBoundary();      
        checkLawn();    
        
      if (mowPatternCurr == MOW_BIDIR){
        double ratio = motorBiDirSpeedRatio1;
        if (stateTime > 4000) ratio = motorBiDirSpeedRatio2;
        if (rollDir == RIGHT) motorRightSpeedRpmSet = ((double)motorLeftSpeedRpmSet) * ratio;
          else motorLeftSpeedRpmSet = ((double)motorRightSpeedRpmSet) * ratio;                                
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
      if (motorLeftSpeedRpmSet == motorRightSpeedRpmSet){ // do not check during 'outside=>inside' rotation              
        checkCurrent();
        checkBumpersPerimeter();
        checkSonar();                           
      }  
      checkPerimeterFind();      
      checkTimeout();                    
      break;
    case STATE_PERI_TRACK:
      // track perimeter
      checkCurrent();                  
      checkBumpersPerimeter();
      //checkSonar();                   
      if (batMonitor){
        if (chgVoltage > 5.0){ 
          setNextState(STATE_STATION, 0);
        }
      }
      break;
    case STATE_STATION:
      // waiting until auto-start by user or timer triggered
      if (batMonitor){
        if ((chgVoltage > 5.0) && (batVoltage > 8)){
          if (batVoltage < startChargingIfBelow && (millis()-stateStartTime>2000)){
            setNextState(STATE_STATION_CHARGING,0);
          } else checkTimer();  
        } else setNextState(STATE_OFF,0);
      }  else checkTimer();
      break;     
    case STATE_STATION_CHARGING:
      // waiting until charging completed    
      if (batMonitor){
        if ((chgCurrent < batFullCurrent) && (millis()-stateStartTime>2000)) setNextState(STATE_STATION,0); 
          else if (millis()-stateStartTime > chargingTimeout) {
            addErrorCounter(ERR_BATTERY);
            setNextState(STATE_ERROR, 0);
          }
      } 
      break;  
    case STATE_PERI_OUT_FORW:  
      checkPerimeterBoundary();                 
      //if (millis() >= stateEndTime) setNextState(STATE_PERI_OUT_ROLL, rollDir);  
      if (perimeterInside || (millis() >= stateEndTime)) setNextState(STATE_PERI_OUT_ROLL, rollDir); 
      break;
    case STATE_PERI_OUT_REV: 
      checkPerimeterBoundary();      
     // if (millis() >= stateEndTime) setNextState(STATE_PERI_OUT_ROLL, rollDir);   
      if (perimeterInside || (millis() >= stateEndTime)) setNextState (STATE_PERI_OUT_ROLL, rollDir); 
      break;
    case STATE_PERI_OUT_ROLL: 
      if (millis() >= stateEndTime) setNextState(STATE_FORWARD,0);                
      break;

    case STATE_STATION_CHECK:
      // check for charging voltage disappearing before leaving charging station
      if (millis() >= stateEndTime){
        if (chgVoltage > 5) {
          addErrorCounter(ERR_CHARGER);
          setNextState(STATE_ERROR, 0);
        } else setNextState(STATE_STATION_REV, 0);
      }      
      break;
    case STATE_STATION_REV:
      // charging: drive reverse 
      if (millis() >= stateEndTime) setNextState(STATE_STATION_ROLL, 0);				             
      break;
    case STATE_STATION_ROLL:
      // charging: roll 
      if (millis() >= stateEndTime) setNextState(STATE_STATION_FORW,0);				
      break;
    case STATE_STATION_FORW:
      // forward (charge station)    
      if (millis() >= stateEndTime) setNextState(STATE_FORWARD,0);				        
      break;      
  } // end switch  
      

  // next line deactivated (issue with RC failsafe)
  //if ((useRemoteRC) && (remoteSwitch < -50)) setNextState(STATE_REMOTE, 0);

  
    // decide which motor control to use
    if ( ((mowPatternCurr == MOW_LANES) && (stateCurr == STATE_ROLL)) || (stateCurr == STATE_ROLL_WAIT) ) motorControlImuRoll();
      else if (stateCurr == STATE_PERI_TRACK) motorControlPerimeter();
      else if (  (stateCurr == STATE_FORWARD)
       //&&  (mowPatternCurr == MOW_RANDOM)
       && (imuUse) 
       && (imuCorrectDir || (mowPatternCurr == MOW_LANES))        
       ) motorControlImuDir();                                   //&& (millis() > stateStartTime + 3000)
      else motorControl();  
  
  if (stateCurr != STATE_REMOTE) motorMowSpeedPWMSet = motorMowSpeedMaxPwm;
    
    
  bumperRight = false;
  bumperLeft = false;     
  
  dropRight = false;                                                                                                                             // Dropsensor - Absturzsensor
  dropLeft = false;                                                                                                                              // Dropsensor - Absturzsensor
                             
 loopsPerSecCounter++;
  }







