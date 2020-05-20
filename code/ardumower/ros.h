// Linux ROS interface
// NOTE: use high baud rates for this serial interface (in mower.h, configure CONSOLE_BAUDRATE to 115200 baud)

void Robot::rosSerial() {
  // serial input    
  while (Console.available() > 0){    
    char ch = Console.read();
    if ((ch == '\r') || (ch == '\n')){                  
      if (rosProt == "$ROS") {        
        if (rosCmd == "M1"){
          // motor speed: linear (m/s), angular (rad/s)
          float linear = rosPar1.toFloat();
          float angular = rosPar2.toFloat();
          int mow = rosPar3.toInt();
          //Console.print("motors: ");
          //Console.print(left);
          //Console.print(",");
          //Console.print(right);                 
          //Console.print(",");
          //Console.println(mow);  
          float rspeed = linear + angular * (odometryWheelBaseCm/100.0 /2);          
          float lspeed = linear * 2.0 - rspeed;          
          motorRightSpeedRpmSet =  rspeed / (PI*(wheelDiameter/1000.0)) * 60.0;
          motorLeftSpeedRpmSet = lspeed / (PI*(wheelDiameter/1000.0)) * 60.0;
          motorMowSpeedPWMSet = mow;
          rosTimeout = millis() + 3000;
        } else if (rosCmd == "P1"){
          motorLeftPID.Kp = rosPar1.toFloat();
          motorLeftPID.Ki = rosPar2.toFloat();
          motorLeftPID.Kd = rosPar3.toFloat();
        }
      }
      rosIdx = 0;
      rosProt = "";
      rosCmd = "";
      rosPar1 = "";
      rosPar2 = "";
      rosPar3 = "";
      rosPar4 = "";
      rosPar5 = "";
      rosPar6 = "";
    } else if (ch == ','){
       rosIdx++;
    } else {
       switch (rosIdx){
         case 0: rosProt += ch; break;
         case 1: rosCmd += ch; break;
         case 2: rosPar1 += ch; break;
         case 3: rosPar2 += ch; break;
         case 4: rosPar3 += ch; break;
         case 5: rosPar4 += ch; break;
         case 6: rosPar5 += ch; break;
         case 7: rosPar6 += ch; break;
       }
    }
  }
          
  if (millis () >= nextTimeROS){
    nextTimeROS = millis() + 200;
    Console.print("$ROS,I1,");
    Console.print(loopsPerSec);    
    Console.print(",");
    Console.print(batVoltage);    
    Console.print(",");
    Console.print(chgVoltage);
    Console.print(",");
    Console.print(chgCurrent);    
    Console.print(",");
    Console.print(odometryLeft);
    Console.print(",");
    Console.print(odometryRight);
    Console.print(",");
    Console.print(motorLeftSense);
    Console.print(",");
    Console.print(motorRightSense);
    Console.print(",");
    Console.print(motorMowSense);        
    Console.print(",");
    Console.print(imu.ypr.yaw);    
    Console.print(",");
    Console.print(imu.ypr.pitch);    
    Console.print(",");
    Console.print(imu.ypr.roll);    
    Console.print(",");
    Console.print(odometryX/100.0);    
    Console.print(",");  
    Console.print(odometryY/100.0);        
    Console.print(",");  
    Console.print(odometryTheta);
    Console.print(",");  
    Console.print(bumperLeft);
    Console.print(",");  
    Console.print(bumperRight);
    Console.print(",");  
    Console.print(freeWheelIsMoving);    
    Console.print(",");  
    Console.print(perimeterInside);      
    Console.print(",");  
    Console.print(perimeterMag);          
    Console.println();
  }
  if (millis() >= rosTimeout){
    motorLeftSpeedRpmSet  = 0;
    motorRightSpeedRpmSet = 0;    
    motorMowSpeedPWMSet = 0;
  }
}

