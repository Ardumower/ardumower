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
  
  if (durationSinceLastSendState > RMCS_interval_state && RMCS_interval_state != 0){
    rmcsInfoLastSendState = now;
    rmcsSendState(s);											   
	}

  if (durationSinceLastSendMotorCurrent > RMCS_interval_motor_current && RMCS_interval_motor_current != 0){
    rmcsInfoLastSendMotorCurrent = now;
    rmcsSendMotorCurrent(s);	
	}

  if (durationSinceLastSendSonar > RMCS_interval_sonar and sonarUse && RMCS_interval_sonar != 0){
    rmcsInfoLastSendSonar = now;
    rmcsSendSonar(s);
	}	
  if (durationSinceLastSendBumper > RMCS_interval_bumper and bumperUse && RMCS_interval_bumper != 0){
    rmcsInfoLastSendBumper = now;
    rmcsSendBumper(s);
	}	

  if (durationSinceLastSendOdometry > RMCS_interval_odometry and odometryUse && RMCS_interval_bumper != 0){
    rmcsInfoLastSendOdometry = now;
    rmcsSendOdometry(s);
	}	

  if (durationSinceLastSendGPS > RMCS_interval_gps and gpsUse && RMCS_interval_gps != 0){
     rmcsInfoLastSendGPS = now;
     rmcsSendGPS(s);
   }
 

  if (durationSinceLastSendPeri > RMCS_interval_perimeter and perimeterUse && RMCS_interval_perimeter != 0){
    rmcsInfoLastSendPeri = now;
    rmcsSendPerimeter(s);
	}

 
  if (durationSinceLastSendDrop > RMCS_interval_drop and dropUse && RMCS_interval_drop != 0){
     rmcsInfoLastSendDrop = now;
     rmcsSendDrop(s);
   }  

 
  if (durationSinceLastSendIMU > RMCS_interval_imu and imuUse && RMCS_interval_imu != 0){
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

void Robot::rmcsSendOFF(Stream &s){
  
    // ROBOT OFF, shutdown Raspberry PI 
    Streamprint(s, "$RMOFF,%6u,", (millis()-stateStartTime)/1000);             
    Streamprint(s, "\r\n");
}

void Robot::rmcsSendConfig(Stream &s){
  Streamprint(s, "$RMCFG, 1, 1"); // Protocol Version and min protocol version
  Streamprint(s, "%2d, ", 1); // Docking Station available
  Streamprint(s, "%2d, ", perimeterUse); // Peri fromt left available
  Streamprint(s, "%2d, ", 0); // Peri front right available
  Streamprint(s, "%2d, ", 0); // peri fron center available
  Streamprint(s, "%2d, ", 0); // peri rear left available
  Streamprint(s, "%2d, ", 0); // peri rear right available
  Streamprint(s, "%2d, ", 0); // peri rear center available
  Streamprint(s, "%2d, ", imuUse); // IMU compass available
  Streamprint(s, "%2d, ", imuUse); // IMU pith roll available
  Streamprint(s, "%2d, ", odometryUse); // Odometry available
  Streamprint(s, "%2d, ", gpsUse); // GPS available
  if (sonarUse == false)
  {
      Streamprint(s, "%2d, ", 0); // sonar left available
      Streamprint(s, "%2d, ", 0); // sonar right available
      Streamprint(s, "%2d, ", 0); // sonar center available 
  }
  else
  {

      Streamprint(s, "%2d, ", sonarLeftUse); // sonar left available
      Streamprint(s, "%2d, ", sonarRightUse); // sonar right available
      Streamprint(s, "%2d, ", sonarCenterUse); // sonar center available 
  }

  Streamprint(s, "%2d, ", dropUse); // drop left available 
  Streamprint(s, "%2d, ", dropUse); // drop right available 
  Streamprint(s, "%2d, ", bumperUse); // bumper available 
  Streamprint(s, "%2d, ", lawnSensorUse); // lawn sensor available
  Streamprint(s, "%2d, ", freeWheelUse); // free Wheel available 
  Streamprint(s, "%2d, ", rainUse); // rain sensor available  
  Streamprint(s, "\r\n");
}

void Robot::processRMCSCommand(String command){
  
  // Split command into different sequences
  String commandParts[10];
  boolean commandPartsFound = true;
  int indexEndOfCommandPart = 0;
  int indexArrayCommandParts = 0;

  String event;
  int frequency = 0;
  boolean enableTrigger = true;
  
  
  // Read command
  String commandType = command.substring(1,6);
  String commandData = command.substring(7);

  // Split payload by comma
  while (commandPartsFound == true)
  {
    indexEndOfCommandPart = commandData.indexOf(',');

    // Check if comma is found. If not, save the rest of command to array
    if (indexEndOfCommandPart == -1)
    {
      commandPartsFound = false;
      commandParts[indexArrayCommandParts] = commandData;
    }
    // comma found, split part of command into array
    else
    {
      commandParts[indexArrayCommandParts] = commandData.substring(0, indexEndOfCommandPart);
      commandData = commandData.substring(indexEndOfCommandPart +1);
      indexArrayCommandParts++;
    }
  }
   // Perform RMCS Command
    // Request or configure event
    if (commandType == "RMREQ") {

      // determine type of event
      event = commandParts[0];
      frequency = commandParts[1].toInt();
      enableTrigger = commandParts[2];

      // heck frequency allowed
      if (frequency < -1 || frequency > 10)
      {
        return;
      }

      if (event == "STA")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendState(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_state = 1000 / frequency;
          }
          else{
            RMCS_interval_state = 0;
          }
        }
      }
      
      if (event == "CFG")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendConfig(Console);
        }       
      }
           
      if (event == "MOT")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendMotorCurrent(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_motor_current = 1000 / frequency;
          }
          else{
            RMCS_interval_motor_current = 0;
          }
          rmcsTriggerMotor = enableTrigger;
        }        
      }
           
      if (event == "SON")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendSonar(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_sonar = 1000 / frequency;
          }
          else{
            RMCS_interval_sonar = 0;
          }
          rmcsTriggerSonar = enableTrigger;
        }        
      }
      

      if (event == "BUM")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendBumper(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_bumper = 1000 / frequency;
          }
          else{
            RMCS_interval_bumper = 0;
          }
          rmcsTriggerBumper = enableTrigger;
        }        
      }        
      
           
      if (event == "ODO")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendOdometry(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_odometry = 1000 / frequency;
          }
          else{
            RMCS_interval_odometry = 0;
          }
          rmcsTriggerOdometry = enableTrigger;
        }        
      }
      
           
      if (event == "GPS")
      {
       // trigger once
        if (frequency == -1)
        {
           rmcsSendGPS(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_gps = 1000 / frequency;
          }
          else{
            RMCS_interval_gps = 0;
          }
          rmcsTriggerGPS = enableTrigger;
        }        
      }
      
           
      if (event == "PER")
      {
       // trigger once
        if (frequency == -1)
        {
           rmcsSendPerimeter(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_perimeter = 1000 / frequency;
          }
          else{
            RMCS_interval_perimeter = 0;
          }
          rmcsTriggerPerimeter = enableTrigger;
        }        
      }
      
           
      if (event == "DRO")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendDrop(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_drop = 1000 / frequency;
          }
          else{
            RMCS_interval_drop = 0;
          }
          rmcsTriggerDrop = enableTrigger;
        }        
      }
      
           
      if (event == "IMU")
      {
        // trigger once
        if (frequency == -1)
        {
           rmcsSendIMU(Console);
        }
        else{
          if (frequency > 0)
          {
             RMCS_interval_imu = 1000 / frequency;
          }
          else{
            RMCS_interval_imu = 0;
          }
          rmcsTriggerIMU = enableTrigger;
        }        
      }      
    }

    
    // Set mowing state
    if (commandType == "RMMOW"){
      
      switch (commandParts[0][0]){
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
      
          setNextState(STATE_MANUAL, 0); 
          // enable mow motor?
          if (commandParts[0] == "1")
          {
            motorMowEnable = true;
          }else{
            motorMowEnable = false;
          }

          // set left motor
          int leftPWM = commandParts[1].toInt();
          if (leftPWM > -255 && leftPWM < 256 && leftPWM != 0)
          {
            motorLeftSpeedRpmSet  = motorSpeedMaxRpm / leftPWM;
          }else{
            motorLeftSpeedRpmSet = 0;
          }

          // set right motor
          int rightPWM = commandParts[2].toInt();
          if (rightPWM > -255 && rightPWM < 256 && rightPWM != 0)
          {
            motorRightSpeedRpmSet  = motorSpeedMaxRpm / rightPWM;
          }else{
            motorRightSpeedRpmSet = 0;
          }          
    }
      
    // Keep ongoing action
    if (commandType == "RMKOA"){
      
    }
      
}

