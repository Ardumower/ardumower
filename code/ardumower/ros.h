// Linux ROS interface

static byte rosIdx = 0;
static String rosString;
static String rosProt;
static String rosCmd;
static String rosPar1;
static String rosPar2;
static String rosPar3;
static String rosPar4;
static String rosPar5;
static String rosPar6;

void Robot::rosSerial() {
  // serial input    
  while (Console.available() > 0){    
    char ch = Console.read();
    if ((ch == '\r') || (ch == '\n')){                  
      if (rosProt == "$ROS") {        
        if (rosCmd == "M1"){
          // motors  
          int left = rosPar1.toInt();
          int right = rosPar2.toInt();
          int mow = rosPar3.toInt();
          //Console.print("motors: ");
          //Console.print(left);
          //Console.print(",");
          //Console.print(right);                 
          //Console.print(",");
          //Console.println(mow);                 
          motorLeftSpeedRpmSet  = left;
          motorRightSpeedRpmSet = right;    
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
    nextTimeROS = millis() + 1000;
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
    Console.println();
  }
  if (millis() >= rosTimeout){
    motorLeftSpeedRpmSet  = 0;
    motorRightSpeedRpmSet = 0;    
    motorMowSpeedPWMSet = 0;
  }
}

