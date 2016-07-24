
/* IMU AHRS test
   Arduino Mega
 */

#include <Arduino.h>
#include <Wire.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
  #include "due.h"
#endif

#include "drivers.h"
#include "imu.h"


#define pinBuzzer 53

IMU imu;
unsigned long nextTime = 0;

void printMenu(){  
  Console.println("Press a for acc calibration next axis");        
  Console.println("Press c for com calibration start/stop");           
  delay(1000);
}

void setup()  {  
  Wire.begin();
  Console.begin(19200);  

  delay(100);
  Console.println("START");        
  imu.init(pinBuzzer);  
  printMenu();
}

void loop()  {           
  imu.update();
  if (millis() >= nextTime){
    nextTime = millis() + 200;    
    if (Console.available() > 0){
      char ch = (char)Console.read();  
      if (ch == 'a') imu.calibAccNextAxis();
      else if (ch == 'c') imu.calibComStartStop();
    }              
    if (imu.state == IMU_RUN){
      Console.print("calls=");        
      Console.print(imu.getCallCounter());  
      Console.print("\tcomMag=");
      Console.print(sqrt(sq(imu.com.x)+sq(imu.com.y)+sq(imu.com.z)));
      Console.print("\tyaw=");  
      Console.print(imu.ypr.yaw/PI*180.0);  
      Console.print("\tpitch=");  
      Console.print(imu.ypr.pitch/PI*180.0);    
      Console.print("\troll=");  
      Console.print(imu.ypr.roll/PI*180.0);    
      Console.print("\tcom=");          
      Console.print(imu.comYaw/PI*180.0);            
      Console.print("\tcom180=");          
      Console.print(imu.scalePI(imu.comYaw+PI)/PI*180.0);            
      Console.print("\tgyroZ=");          
      Console.print(imu.gyro.z);                
      Console.print("\taccZ=");          
      Console.print(imu.acc.z);                      
      /*Console.print(imu.com.x);        
      Console.print(",");          
      Console.print(imu.com.y);        
      Console.print(",");          
      Console.print(imu.com.z);            */
      Console.println();  
    } 
  }
}




