// robot mower communication standard

void Robot::rmcsInfo(Stream &s){
  
  // Period since last send
  unsigned long now = millis();
  unsigned long durationSinceLastSend = now - lastSend;
  lastSend = now;
  

  if (consoleMode == CONSOLE_OFF) {
  } else {
  
  if (durationSinceLastSend > RMCS_interval_state){
  // ROBOT State, Timestamp, state, error code, battery, charging
    Streamprint(s, "$RMSTA,%6u,%4s,%4s,%2d.%01d,%2d.%01d \r\n", (millis()-stateStartTime)/1000, stateNames[stateCurr], 
														   "",
														   (int)batVoltage, 
														   (int)((batVoltage *10) - ((int)batVoltage*10)) 
														   (int)chgVoltage, 
														   (int)((chgVoltage *10) - ((int)chgVoltage*10)),
														   (int)chgCurrent, 
														   (int)((abs(chgCurrent) *10) - ((int)abs(chgCurrent)*10))  );  
	}

  if (durationSinceLastSend > RMCS_interval_motor_current){
  // ROBOT motor current, Timestamp, Motor left A, Motor right A, Motor Mow A, Motor left trigger, motor right trigger, motor mow trigger
    Streamprint(s, "$RMMOT,%6u,%4d,%4d,%4d,%4d,%4d,%4d \r\n", (millis()-stateStartTime)/1000,
												    (int)motorLeftSense, 
													(int)motorRightSense, 
													(int)motorMowSense,
													motorLeftSenseCounter, 
													motorRightSenseCounter, 
													motorMowSenseCounter													);  
	}

  if (durationSinceLastSend > RMCS_interval_sonar and sonarUse){
  // ROBOT sonar sensor data, Timestamp, sonar left dist, sonar right dist, sonar center dist, sonar left trigger, sonar right trigger, sonar center trigger
    Streamprint(s, "$RMSON,%6u,%4d,%4d,%4d,%4d,%4d,%4d \r\n", (millis()-stateStartTime)/1000,
												    sonarDistLeft, sonarDistRight, sonarDistCenter, 
													sonarDistCounter,
													sonarDistCounter,
													sonarDistCounter
													);  
	}	
  if (durationSinceLastSend > RMCS_interval_bumper and bumperUse){
  // ROBOT bumper data, Timestamp, bumper left value, bumper right value, bumper center value, bumper left trigger, bumper right trigger, bumper center trigger
    Streamprint(s, "$RMBUM,%6u,%4d,%4d,%4d,%4d,%4d,%4d \r\n", (millis()-stateStartTime)/1000,
												    bumperLeftCounter, bumperRightCounter,
													bumperLeft, bumperRight, ""
													);  
	}	

  if (durationSinceLastSend > RMCS_interval_odometry and odometryUse){
  // ROBOT odometry data, Timestamp, odometry left value, odometry right value
    Streamprint(s, "$RMODO,%6u,%4d,%4d \r\n", (millis()-stateStartTime)/1000,
										      odometryleft, odometryright );  
	}	

  if (durationSinceLastSend > RMCS_interval_perimeter and perimeterUse){
  // ROBOT Perimeter data, Timestamp, perimeter value, perimeter in/out, perimeter counter
    Streamprint(s, "$RMPER,%6u,%4d,%4d,%4d \r\n", (millis()-stateStartTime)/1000,
													perimeterMag
										            perimeterInside,
													perimeterCounter);  
	}	
	
  }
 }




