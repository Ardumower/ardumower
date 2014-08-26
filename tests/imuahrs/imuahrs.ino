
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


#include "imu.h"


IMU imu;
unsigned long nextTime = 0;


void setup()  {  
  Wire.begin();
  Serial.begin(19200);  

  delay(100);
  Serial.println("START");        
  imu.init();  
}

void loop()  {           
  imu.update();
  if (millis() >= nextTime){
    nextTime = millis() + 200;    
    if (Serial.available() > 0){
      char ch = (char)Serial.read();  
      if (ch == 'a') imu.calibAcc();    
      if (ch == 'c') imu.calibCom();
    }              
    Serial.print("calls=");  
    Serial.print(imu.getCallCounter());  
    Serial.print("\tyaw=");  
    Serial.print(imu.ypr.yaw/PI*180.0);  
    Serial.print("\tpitch=");  
    Serial.print(imu.ypr.pitch/PI*180.0);    
    Serial.print("\troll=");  
    Serial.print(imu.ypr.roll/PI*180.0);    
    Serial.print("\tcom=");          
    Serial.print(imu.comYaw/PI*180.0);            
    Serial.print("\tcom180=");          
    Serial.print(imu.scalePI(imu.comYaw+PI)/PI*180.0);            
    Serial.print("\tgyroZ=");          
    Serial.print(imu.gyro.z);                
    /*Serial.print(imu.com.x);        
    Serial.print(",");          
    Serial.print(imu.com.y);        
    Serial.print(",");          
    Serial.print(imu.com.z);            */
    Serial.println();  
  }
}




