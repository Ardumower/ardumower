
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
  //imu.calibAcc();
  //imu.calibCom();
}

void loop()  {           
  imu.update();
  if (millis() >= nextTime){
    nextTime = millis() + 200;    
    Serial.print(imu.getCallCounter());  
    Serial.print("\t");  
    Serial.print(imu.ypr.yaw/PI*180.0);  
    Serial.print("\t");  
    Serial.print(imu.ypr.pitch/PI*180.0);    
    Serial.print("\t");  
    Serial.print(imu.ypr.roll/PI*180.0);    
    Serial.print("\t");          
    Serial.print(imu.comYaw/PI*180.0);            
    Serial.print("\t");          
    Serial.print(imu.gyro.z);                
    /*Serial.print(imu.com.x);        
    Serial.print(",");          
    Serial.print(imu.com.y);        
    Serial.print(",");          
    Serial.print(imu.com.z);            */
    Serial.println();  
  }
}




