// battery code

// check battery voltage and decide what to do
void Robot::checkBattery(){
  if (millis() < nextTimeCheckBattery) return;
	nextTimeCheckBattery = millis() + 1000;  
  if (batVoltage < 4.0){      
    Console.println(F("BATTERY NOT FOUND - PLEASE SWITCH ON BATTERY!")); 
  }
    
  if (batMonitor){
    if ((batVoltage < batSwitchOffIfBelow) && (idleTimeSec != BATTERY_SW_OFF)) {      
			Console.print(F("Battery warning: triggered batSwitchOffIfBelow "));
			Console.print(batVoltage);
			Console.print(F("<"));
			Console.println(batSwitchOffIfBelow);
      addErrorCounter(ERR_BATTERY);      
			delay(2000); // avois corrupting EEPROM while this is also called when power is turned OFF
			beep(2, true);      
			loadSaveErrorCounters(false); // saves error counters
      loadSaveRobotStats(false);    // saves robot stats
      idleTimeSec = BATTERY_SW_OFF; // flag to remember that battery is switched off
      Console.println(F("BATTERY switching OFF"));
      setActuator(ACT_BATTERY_SW, 0);  // switch off battery                     
    }
    else if ((batVoltage < batGoHomeIfBelow) && (stateCurr == STATE_FORWARD) 
			&& (perimeterUse)) {    //UNTESTED please verify
      Console.print(F("triggered batGoHomeIfBelow "));
			Console.print(batVoltage);
			Console.print(F("<"));
			Console.println(batGoHomeIfBelow);
      beep(2, true);      
      setNextState(STATE_PERI_FIND, 0);
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
}


