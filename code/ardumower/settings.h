// user settings (EEPROM), statistics, error counters

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
    //addErrorCounter(ERR_EEPROM_DATA);
    //setNextState(STATE_ERROR, 0);
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
    //addErrorCounter(ERR_EEPROM_DATA);
    //setNextState(STATE_ERROR, 0);
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
  eereadwrite(readflag, addr, perimeter.signalCodeNo);        
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
  eereadwrite(readflag, addr, tiltUse);
  eereadwrite(readflag, addr, sonarSlowBelow);
	eereadwrite(readflag, addr, motorMowForceOff);	
  Console.print(F("loadSaveUserSettings addrstop="));
  Console.println(addr);
}

void Robot::loadUserSettings(){  
  Console.println(F("loadUserSettings"));  
  loadSaveUserSettings(true);
}


void Robot::printSettingSerial(){
 
  // ------- wheel motors ---------------------------------------------------------
  Console.println(F("---------- wheel motors --------------------------------------"));
  Console.print  (F("motorAccel                                 : "));
  Console.println(motorAccel);
  Console.print  (F("motorSpeedMaxRpm                           : "));
  Console.println(motorSpeedMaxRpm);
  Console.print  (F("motorSpeedMaxPwm                           : ")); 
  Console.println(motorSpeedMaxPwm);
  Console.print  (F("motorPowerMax                              : "));    
  Console.println(motorPowerMax);
  Console.print  (F("motorSenseRightScale                       : ")); 
  Console.println(motorSenseRightScale);
  Console.print  (F("motorSenseLeftScale                        : "));
  Console.println(motorSenseLeftScale);
  Console.print  (F("motorPowerIgnoreTime                       : "));
  Console.println(motorPowerIgnoreTime);
  Console.print  (F("motorZeroSettleTime                        : "));
  Console.println(motorZeroSettleTime);
  Console.print  (F("motorRollTimeMax                           : "));
  Console.println(motorRollTimeMax);
  Console.print  (F("motorRollTimeMin                           : "));
  Console.println(motorRollTimeMin);
  Console.print  (F("motorReverseTime                           : "));
  Console.println(motorReverseTime);
  
  Console.print  (F("motorForwTimeMax                           : "));
  Console.println(motorForwTimeMax);
  
  Console.print  (F("motorBiDirSpeedRatio1                      : "));
  Console.println(motorBiDirSpeedRatio1);
  
  Console.print  (F("motorBiDirSpeedRatio2                      : "));
  Console.println(motorBiDirSpeedRatio2);

  Console.print  (F("motorLeftPID.Kp                            : "));
  Console.println(motorLeftPID.Kp);
  Console.print  (F("motorLeftPID.Ki                            : "));
  Console.println(motorLeftPID.Ki);
  Console.print  (F("motorLeftPID.Kd                            : "));
  Console.println(motorLeftPID.Kd);

  Console.print  (F("motorRightSwapDir                          : "));
  Console.println(motorRightSwapDir);
  Console.print  (F("motorLeftSwapDir                           : "));
  Console.println(motorLeftSwapDir);
  
  // ------ mower motor -----------------------------------------------------------
  Console.println(F("---------- mower motor ---------------------------------------"));
  Console.print  (F("motorMowForceOff                           : "));
	Console.println(motorMowForceOff);
	Console.print  (F("motorMowAccel                              : "));
  Console.println(motorMowAccel);
  Console.print  (F("motorMowSpeedMaxPwm                        : "));
  Console.println(motorMowSpeedMaxPwm);
  Console.print  (F("motorMowPowerMax                           : "));
  Console.println(motorMowPowerMax);
  Console.print  (F("motorMowModulate                           : "));
  Console.println(motorMowModulate,1);
  Console.print  (F("motorMowRPMSet                             : "));  
  Console.println(motorMowRPMSet);
  Console.print  (F("motorMowSenseScale                         : "));
  Console.println(motorMowSenseScale); 
  Console.print  (F("motorMowPID.Kp                             : "));
  Console.println(motorMowPID.Kp);
  Console.print  (F("motorMowPID.Ki                             : "));
  Console.println(motorMowPID.Ki);
  Console.print  (F("motorMowPID.Kd                             : "));
  Console.println(motorMowPID.Kd);

  // ------ motorMowModulate Interrupt --------------------------------------------
  Console.println(F("---------- motorMowModulate Interrupt ------------------------"));
  Console.print  (F("motorMowModulate Interrupt                 : "));
  #ifdef __AVR__
    Console.print(bitRead(PCMSK2, PCINT19));
  #endif
	Console.println();

  // ------ bumper ----------------------------------------------------------------
  Console.println(F("---------- bumper --------------------------------------------"));
  Console.print  (F("bumperUse                                  : "));
  Console.println(bumperUse,1);

  // ------ drop ------------------------------------------------------------------
  Console.println(F("---------- drop ----------------------------------------------"));
  Console.print  (F("dropUse                                    : "));
  Console.println(dropUse,1);

  Console.print  (F("dropContact                                : "));
  Console.println(dropcontact,1);

  // ------ rain ------------------------------------------------------------------
  Console.println(F("---------- rain ----------------------------------------------"));
  Console.print  (F("rainUse                                    : "));
  Console.println(rainUse,1);

  // ------ sonar -----------------------------------------------------------------
  Console.println(F("---------- sonar ---------------------------------------------"));
  Console.print  (F("sonarUse                                   : "));
  Console.println(sonarUse,1);
  Console.print  (F("sonarLeftUse                               : "));
  Console.println(sonarLeftUse,1);
  Console.print  (F("sonarRightUse                              : "));
  Console.println(sonarRightUse,1);
  Console.print  (F("sonarCenterUse                             : "));
  Console.println(sonarCenterUse,1);
  Console.print  (F("sonarTriggerBelow                          : "));
  Console.println(sonarTriggerBelow);
  Console.print  (F("sonarSlowBelow                             : "));
  Console.println(sonarSlowBelow);

  // ------ perimeter -------------------------------------------------------------
  Console.println(F("---------- perimeter -----------------------------------------"));
  Console.print  (F("perimeterUse                               : "));
  Console.println(perimeterUse,1);
  Console.print  (F("perimeterTriggerTimeout                    : "));
  Console.println(perimeterTriggerTimeout);
  Console.print  (F("perimeterOutRollTimeMax                    : "));
  Console.println(perimeterOutRollTimeMax);
  Console.print  (F("perimeterOutRollTimeMin                    : "));
  Console.println(perimeterOutRollTimeMin);
  Console.print  (F("perimeterOutRevTime                        : "));
  Console.println(perimeterOutRevTime);
  Console.print  (F("perimeterTrackRollTime                     : "));
  Console.println(perimeterTrackRollTime);
  Console.print  (F("perimeterTrackRevTime                      : "));
  Console.println(perimeterTrackRevTime); 
  Console.print  (F("perimeterPID.Kp                            : "));
  Console.println(perimeterPID.Kp);
  Console.print  (F("perimeterPID.Ki                            : "));
  Console.println( perimeterPID.Ki);
  Console.print  (F("perimeterPID.Kd                            : "));
  Console.println(perimeterPID.Kd);
  Console.print  (F("trackingPerimeterTransitionTimeOut         : "));
  Console.println(trackingPerimeterTransitionTimeOut);
  Console.print  (F("trackingErrorTimeOut                       : "));
  Console.println(trackingErrorTimeOut);
  Console.print  (F("trackingBlockInnerWheelWhilePerimeterStruggling : "));
  Console.println(trackingBlockInnerWheelWhilePerimeterStruggling,1);

  // ------ lawn sensor -----------------------------------------------------------
  Console.println(F("---------- lawn sensor ---------------------------------------"));
  Console.print  (F("lawnSensorUse                              : "));
  Console.println(lawnSensorUse,1);

  // ------  IMU (compass/accel/gyro) ---------------------------------------------
  Console.println(F("---------- IMU (compass/accel/gyro) --------------------------"));
  Console.print  (F("imuUse                                     : "));
  Console.println( imuUse,1);
  Console.print  (F("imuCorrectDir                              : "));
  Console.println(imuCorrectDir,1); 
  Console.print  (F("imuDirPID.Kp                               : "));
  Console.println(imuDirPID.Kp); 
  Console.print  (F("imuDirPID.Ki                               : "));
  Console.println(imuDirPID.Ki); 
  Console.print  (F("imuDirPID.Kd                               : "));
  Console.println( imuDirPID.Kd);
  Console.print  (F("imuRollPID.Kp                              : "));
  Console.println(imuRollPID.Kp); 
  Console.print  (F("imuRollPID.Ki                              : "));
  Console.println(imuRollPID.Ki); 
  Console.print  (F("imuRollPID.Kd                              : "));
  Console.println(imuRollPID.Kd); 

  // ------ model R/C -------------------------------------------------------------
  Console.println(F("---------- model R/C -----------------------------------------"));
  Console.print  (F("remoteUse                                  : "));
  Console.println(remoteUse,1); 

// ------ model R/C Interrupt -----------------------------------------------------
 Console.println(F("---------- model R/C Interrupt --------------------------------"));
  Console.print  (F("Pin 10 pinRemoteSpeed                      : "));
  #ifdef __AVR__
    Console.print(bitRead(PCMSK0, PCINT4)); // Pin 10
  #endif
	Console.println();
  Console.print  (F("Pin 11 pinRemoteSteer                      : "));
  #ifdef __AVR__
    Console.print(bitRead(PCMSK0, PCINT5)); // Pin 11
  #endif
	Console.println();
  Console.print(F("Pin 12 pinRemoteMow                        : "));
  #ifdef __AVR__
    Console.print(bitRead(PCMSK0, PCINT6)); // Pin 12
  #endif
	Console.println();
  Console.print  (F("Pin 52 pinRemoteSwitch                     : "));
  #ifdef __AVR__
    Console.print(bitRead(PCMSK0, PCINT1)); // Pin 52
  #endif
	Console.println();
  
  // ------ battery ---------------------------------------------------------------
  Console.println(F("---------- battery -------------------------------------------"));
  Console.print  (F("batMonitor                                 : "));
  Console.println( batMonitor,1);
  Console.print  (F("batGoHomeIfBelow                           : "));
  Console.println(batGoHomeIfBelow); 
  Console.print  (F("batSwitchOffIfBelow                        : "));
  Console.println(batSwitchOffIfBelow); 
  Console.print  (F("batSwitchOffIfIdle                         : "));
  Console.println(batSwitchOffIfIdle); 
  Console.print  (F("batFactor                                  : "));
  Console.println( batFactor);
  Console.print  (F("batChgFactor                               : "));  
  Console.println( batChgFactor);
  Console.print  (F("batFull                                    : "));
  Console.println( batFull);
  Console.print  (F("batChargingCurrentMax                      : "));
  Console.println(batChargingCurrentMax); 
  Console.print  (F("batFullCurrent                             : "));
  Console.println(batFullCurrent); 
  Console.print  (F("startChargingIfBelow                       : "));
  Console.println(startChargingIfBelow); 
  Console.print  (F("chargingTimeout                            : "));
  Console.println(chargingTimeout); 	
  Console.print  (F("chgFactor                                  : "));
  Console.println( chgFactor);
  
  // ------  charging station -----------------------------------------------------
  Console.println(F("---------- charging station ----------------------------------"));
  Console.print  (F("stationRevTime                             : "));
  Console.println(stationRevTime); 
  Console.print  (F("stationRollTime                            : "));
  Console.println(stationRollTime); 
  Console.print  (F("stationForwTime                            : "));
  Console.println( stationForwTime);
  Console.print  (F("stationCheckTime                           : "));
  Console.println(stationCheckTime); 
  
  // ------ odometry --------------------------------------------------------------
  Console.println(F("---------- odometry ------------------------------------------"));
  Console.print  (F("odometryUse                                : "));
  Console.println( odometryUse,1);
  Console.print  (F("twoWayOdometrySensorUse                    : "));
  Console.println( twoWayOdometrySensorUse,1);
  Console.print  (F("odometryTicksPerRevolution                 : "));
  Console.println( odometryTicksPerRevolution);
  Console.print  (F("odometryTicksPerCm                         : "));
  Console.println( odometryTicksPerCm);
  Console.print  (F("odometryWheelBaseCm                        : "));
  Console.println( odometryWheelBaseCm);  


// ------ odometry Interrupt-------------------------------------------------------
 Console.println(F("---------- Odometry Interrupt ---------------------------------"));
  Console.print  (F("oneway left                                : "));
  #ifdef __AVR__
    Console.println (bitRead(PCMSK2, PCINT20));
  #endif
  Console.print  (F("Oneway right                               : "));
  #ifdef __AVR__
    Console.println (bitRead(PCMSK2, PCINT22));
  #endif
    Console.print  (F("twoway left                                : "));
  #ifdef __AVR__
    Console.println (bitRead(PCMSK2, PCINT21));
  #endif
    Console.print  (F("twoway right                               : "));
  #ifdef __AVR__
    Console.println (bitRead(PCMSK2, PCINT23)); 
  #endif

  
// ----- GPS ----------------------------------------------------------------------
  Console.println(F("---------- GPS -----------------------------------------------"));
  Console.print  (F("gpsUse                                     : "));
  Console.println(gpsUse,1); 
  Console.print  (F("stuckIfGpsSpeedBelow                       : "));
  Console.println(stuckIfGpsSpeedBelow); 
  Console.print  (F("gpsSpeedIgnoreTime                         : "));
  Console.println(gpsSpeedIgnoreTime); 
  

// ----- other --------------------------------------------------------------------
  Console.println(F("---------- other ---------------------------------------------"));
  Console.print  (F("buttonUse                                  : "));
  Console.println(buttonUse,1); 

// ----- user-defined switch ------------------------------------------------------
  Console.println(F("---------- user-defined switch -------------------------------"));
  Console.print  (F("userSwitch1                                : "));
  Console.println(userSwitch1,1); 
  Console.print  (F("userSwitch2                                : "));
  Console.println(userSwitch2,1); 
  Console.print  (F("userSwitch3                                : "));
  Console.println(userSwitch3,1); 

// ----- timer --------------------------------------------------------------------
  Console.println(F("---------- timer ---------------------------------------------"));
  Console.print  (F("timerUse                                   : "));
  Console.println(timerUse,1); 

// ----- bluetooth ---------------------------------------------------------------
  Console.println(F("---------- bluetooth-----------------------------------------"));
  Console.print  (F("bluetoothuse                               : "));
  Console.println(bluetoothUse,1); 

// ----- esp8266 -----------------------------------------------------------------
  Console.println(F("---------- esp8266 ------------------------------------------"));
  Console.print  (F("esp8266Use                                 : "));
  Console.println(esp8266Use,1); 
  Console.print  (F("esp8266ConfigString                        : "));
  Console.println(esp8266ConfigString); 

// -------robot stats--------------------------------------------------------------
  Console.println(F("---------- robot stats ---------------------------------------"));
  Console.print  (F("statsMowTimeMinutesTrip                    : "));
  Console.println(statsMowTimeMinutesTrip);
  Console.print  (F("statsMowTimeMinutesTotal                   : "));
  Console.println(statsMowTimeMinutesTotal);
  Console.print  (F("statsBatteryChargingCounterTotal           : "));
  Console.println(statsBatteryChargingCounterTotal);
  Console.print  (F("statsBatteryChargingCapacityTrip in mAh    : "));
  Console.println(statsBatteryChargingCapacityTrip);
  Console.print  (F("statsBatteryChargingCapacityTotal in Ah    : "));
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

void Robot::printErrors(){
  if (millis() >= nextTimePrintErrors){
    nextTimePrintErrors = millis() + 5000;
    for (int i=0; i < ERR_ENUM_COUNT; i++){
      if (errorCounter[i] > 0) {       
        switch (i){
           case ERR_MOTOR_LEFT: Console.println(F("ERR_MOTOR_LEFT")); break;
           case ERR_MOTOR_RIGHT: Console.println(F("ERR_MOTOR_RIGHT")); break;
           case ERR_MOTOR_MOW: Console.println(F("ERR_MOW_SENSE")); break;
           case ERR_IMU_COMM: Console.println(F("ERR_IMU_COMM")); break;
           case ERR_IMU_TILT: Console.println(F("ERR_IMU_TILT")); break;
           case ERR_RTC_COMM:Console.println(F("ERR_RTC_COMM")); break;
           case ERR_RTC_DATA: Console.println(F("ERR_RTC_DATA")); break;
           case ERR_PERIMETER_TIMEOUT:Console.println(F("ERR_PERIMETER_TIMEOUT")); break;
           case ERR_TRACKING:Console.println(F("ERR_TRACKING")); break;
           case ERR_ODOMETRY_LEFT:Console.println(F("ERR_ODOMETRY_LEFT")); break;
           case ERR_ODOMETRY_RIGHT:Console.println(F("ERR_ODOMETRY_RIGHT")); break;
           case ERR_BATTERY:Console.println(F("ERR_BATTERY")); break;
           case ERR_CHARGER:Console.println(F("ERR_CHARGER")); break;
           case ERR_GPS_COMM:Console.println(F("ERR_GPS_COMM")); break;
           case ERR_GPS_DATA:Console.println(F("ERR_GPS_DATA")); break;
           case ERR_ADC_CALIB:Console.println(F("ERR_ADC_CALIB")); break;
           case ERR_IMU_CALIB:Console.println(F("ERR_IMU_CALIB")); break;
           case ERR_EEPROM_DATA:Console.println(F("ERR_EEPROM_DATA")); break;
           case ERR_STUCK:Console.println(F("ERR_STUCK")); break;
        }
      }
    }
  }
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
     if (errorCounter[i] > 10) {       
       setNextState(STATE_ERROR, 0);
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

