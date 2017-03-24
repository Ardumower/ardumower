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
      if ((batSwitchOffIfIdle != 0) && (idleTimeSec > batSwitchOffIfIdle * 60)) {        
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


