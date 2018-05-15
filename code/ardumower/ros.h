// Linux ROS interface


void Robot::rosSerial() {
  // serial input  
  if (Console.available() > 0) {     
     String prot = Console.readStringUntil(',');
     if (prot == "$ROS") {
       String cmd = Console.readStringUntil(',');       
       if (cmd == "M1"){
         // motors  
         int left = Console.parseInt();
         int right = Console.parseInt();
         int mow = Console.parseInt();
         //Console.print("motors: ");
         //Console.print(left);
         //Console.print(",");
         //Console.print(right);                 
         //Console.print(",");
         //Console.println(mow);                 
         motorLeftSpeedRpmSet  = left;
         motorRightSpeedRpmSet = right;    
         motorMowSpeedPWMSet = mow;
         rosTimeout = millis() + 5000;
       } else if (cmd == "P1"){
         motorLeftPID.Kp = Console.parseFloat();
         motorLeftPID.Ki = Console.parseFloat();
         motorLeftPID.Kd = Console.parseFloat();
       }
     }                 
  }    
  if (millis () >= nextTimeROS){
    nextTimeROS = millis() + 200;
    Console.print("$ROS,I1,");
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
    Console.println();
  }
  if (millis() >= rosTimeout){
    motorLeftSpeedRpmSet  = 0;
    motorRightSpeedRpmSet = 0;    
    motorMowSpeedPWMSet = 0;
  }
}

