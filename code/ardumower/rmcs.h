// robot mower communication standard

void Robot::rmcsPrintInfo(Stream &s){
  
  // Period since last send
  unsigned long now = millis();
  unsigned long durationSinceLastSendState = now - rmcsInfoLastSendState;
  unsigned long durationSinceLastSendMotorCurrent = now - rmcsInfoLastSendMotorCurrent;
  unsigned long durationSinceLastSendSonar = now - rmcsInfoLastSendSonar;
  unsigned long durationSinceLastSendBumper = now - rmcsInfoLastSendBumper;
  unsigned long durationSinceLastSendOdometry = now - rmcsInfoLastSendOdometry;
  unsigned long durationSinceLastSendPeri = now - rmcsInfoLastSendPeri;
  unsigned long durationSinceLastSendGPS = now - rmcsInfoLastSendGPS;
  unsigned long durationSinceLastSendDrop = now - rmcsInfoLastSendDrop;
  unsigned long durationSinceLastSendIMU = now - rmcsInfoLastSendIMU;
    
  if (consoleMode == CONSOLE_OFF) {
  } else {
  
  if (durationSinceLastSendState > RMCS_interval_state){
    rmcsInfoLastSendState = now;
    rmcsSendState(s);											   
	}

  if (durationSinceLastSendMotorCurrent > RMCS_interval_motor_current){
    rmcsInfoLastSendMotorCurrent = now;
    rmcsSendMotorCurrent(s);	
	}

  if (durationSinceLastSendSonar > RMCS_interval_sonar and sonarUse){
    rmcsInfoLastSendSonar = now;
    rmcsSendSonar(s);
	}	
  if (durationSinceLastSendBumper > RMCS_interval_bumper and bumperUse){
    rmcsInfoLastSendBumper = now;
    rmcsSendBumper(s);
	}	

  if (durationSinceLastSendOdometry > RMCS_interval_odometry and odometryUse){
    rmcsInfoLastSendOdometry = now;
    rmcsSendOdometry(s);
	}	

  if (durationSinceLastSendGPS > RMCS_interval_gps and gpsUse){
     rmcsInfoLastSendGPS = now;
     rmcsSendGPS(s);
   }
 

  if (durationSinceLastSendPeri > RMCS_interval_perimeter and perimeterUse){
    rmcsInfoLastSendPeri = now;
    rmcsSendPerimeter(s);
	}

 
  if (durationSinceLastSendDrop > RMCS_interval_drop and dropUse){
     rmcsInfoLastSendDrop = now;
     rmcsSendDrop(s);
   }  

 
  if (durationSinceLastSendIMU > RMCS_interval_imu and imuUse){
     rmcsInfoLastSendIMU = now;
     rmcsSendIMU(s);
   }  
 }
}


void Robot::rmcsSendState(Stream &s){

    // ROBOT State, Timestamp, state, error code, battery, charging
    Streamprint(s, "$RMSTA,%6u,",((millis()-stateStartTime)/1000));
    Streamprint(s, "%4s,", stateNames[stateCurr]);
    Streamprint(s, "%4s,", "E000");
    Streamprint(s, "%2d.%01d,",(int)batVoltage, (int)((batVoltage *10) - ((int)batVoltage*10)));
    Streamprint(s, "%2d.%01d,",(int)chgVoltage, (int)((chgVoltage *10) - ((int)chgVoltage*10)));
    Streamprint(s, "%2d.%01d",(int)chgCurrent, (int)((abs(chgCurrent) *10) - ((int)abs(chgCurrent)*10))  ); 
    Streamprint(s, "\r\n"); 
}

void Robot::rmcsSendMotorCurrent(Stream &s){
  
    // ROBOT motor current, Timestamp, Motor left A, Motor right A, Motor Mow A, Motor left trigger, motor right trigger, motor mow trigger
    Streamprint(s, "$RMMOT,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "%4d ,",(int)motorLeftSense);                         
    Streamprint(s, "%4d ,",(int)motorRightSense);                   
    Streamprint(s, "%4d ,",(int)motorMowSense);
    Streamprint(s, "%4d ,",motorLeftSenseCounter);                
    Streamprint(s, "%4d ,",motorRightSenseCounter);           
    Streamprint(s, "%4d ",motorMowSenseCounter);  
    Streamprint(s, "\r\n");   
}

void Robot::rmcsSendSonar(Stream &s){
  
    // ROBOT sonar sensor data, Timestamp, sonar left dist, sonar right dist, sonar center dist, sonar left trigger, sonar right trigger, sonar center trigger
    Streamprint(s, "$RMSON,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "%4d ,",sonarDistLeft);                         
    Streamprint(s, "%4d ,",sonarDistRight);                   
    Streamprint(s, "%4d ,",sonarDistCenter);
    Streamprint(s, "%4d ,",sonarDistCounter);                
    Streamprint(s, "%4d ,",sonarDistCounter);           
    Streamprint(s, "%4d ",sonarDistCounter); 
    Streamprint(s, "\r\n"); 
}

void Robot::rmcsSendBumper(Stream &s){
  
    // ROBOT bumper data, Timestamp, bumper left value, bumper right value, bumper center value, bumper left trigger, bumper right trigger, bumper center trigger
    Streamprint(s, "$RMBUM,%6u,", (millis()-stateStartTime)/1000);                      
    Streamprint(s, "%4d ,",bumperLeftCounter);                   
    Streamprint(s, "%4d ,",bumperRightCounter);
    Streamprint(s, "%4d ,",0);                
    Streamprint(s, "%4d ,",bumperLeft);           
    Streamprint(s, "%4d ,",bumperRight); 
    Streamprint(s, "%4d ",0);
    Streamprint(s, "\r\n"); 
}

void Robot::rmcsSendOdometry(Stream &s){
      
  // ROBOT odometry data, Timestamp, odometry left value, odometry right value
    Streamprint(s, "$RMODO,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "%4d ,",odometryLeft);                         
    Streamprint(s, "%4d ",odometryRight);                   
    Streamprint(s, "\r\n"); 
}

void Robot::rmcsSendGPS(Stream &s){
  
    // ROBOT GPS data, Timestamp, latitude, longitude
    Streamprint(s, "$RMGPS,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "%4d ,",(int)gpsLat);                         
    Streamprint(s, "%4d ,",(int)gpsLon);                    
    Streamprint(s, "\r\n");
}

void Robot::rmcsSendPerimeter(Stream &s){
      
  // ROBOT Perimeter data, Timestamp, perimeter value, perimeter in/out, perimeter counter
    Streamprint(s, "$RMPER,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "%4d ,",perimeterMag);                         
    Streamprint(s, "%4d ,",perimeterInside);   
    Streamprint(s, "%4d ",perimeterCounter);                    
    Streamprint(s, "\r\n"); 
}


void Robot::rmcsSendDrop(Stream &s){
  
    // ROBOT Drop sensor, Timestamp, drop left counter, drop right counter, drop left triggered, drop right triggered
    Streamprint(s, "$RMDRP,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "%4d ,",dropLeftCounter);                         
    Streamprint(s, "%4d ,",dropRightCounter);
    Streamprint(s, "%4d ,",dropLeft);
    Streamprint(s, "%4d ,",dropRight);                    
    Streamprint(s, "\r\n");
}

void Robot::rmcsSendIMU(Stream &s){
  
    // ROBOT IMU sensor, Timestamp, compass heading, pitch degree, roll degree, triggered 
    Streamprint(s, "$RMIMU,%6u,", (millis()-stateStartTime)/1000);
    Streamprint(s, "yaw %3d ", (int)(imu.ypr.yaw/PI*180.0));        
    Streamprint(s, "pit %3d ", (int)(imu.ypr.pitch/PI*180.0));
    Streamprint(s, "rol %3d ", (int)(imu.ypr.roll/PI*180.0));
    Streamprint(s, "%4d ,",tilt);                    
    Streamprint(s, "\r\n");
}


void Robot::processRMCSCommand(String command){

  // Read command
  String commandType = command.substring(1,5);
  String commandData = command.substring(5);


    // Request or configure event
    if (commandType == "RMREQ") {
    }

    // Configure sensor trigger
    if (commandType == "RMTRG" ){
    }
    
    // Set mowing state
    if (commandType == "RMMOW"){
      
      switch (commandData[1]){
        case '0':
           setNextState(STATE_OFF, 0);
           break;

         case '1':
            setNextState(STATE_FORWARD, 0);
            break;

         case '2':
            setNextState(STATE_PERI_FIND, 0);
            break;
      }     
    }
      
    // Move robot
    if (commandType == "RMMOV") {
      
    }
      
    // Keep ongoing action
    if (commandType == "RMKOA"){
      
    }
      
}

