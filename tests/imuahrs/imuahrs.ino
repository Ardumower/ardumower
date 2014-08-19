
/* IMU AHRS fixed point test
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

//#include "ahrs.h"
#include "imu.h"

//AHRS ahrs;
IMU imu;
unsigned long nextTime = 0;
float ypr[3];

void setup()  {  
  Wire.begin();
  Serial.begin(19200);  

  delay(100);
  Serial.println("START");        
  imu.init();
  //imu.calibAcc();
}

void loop()  {     
  /*ahrs.update( 
             0.02, 0.01, 0.01,             
             0.02, 0.01,  0.02, 
             0.04, 0.03,    0.01,
             0.1
             );      */
  /*delay(1000);  
  Serial.print((double)(ahrs.q0), 8);
  Serial.print("\t");
  Serial.print((double)(ahrs.q1), 8);
  Serial.print("\t");
  Serial.print((double)(ahrs.q2), 8);
  Serial.print("\t");
  Serial.print((double)(ahrs.q3), 8);  
  Serial.println();*/
        
      
  imu.update();
  if (millis() >= nextTime){
    nextTime = millis() + 500;
    imu.getEulerRad(ypr);
    Serial.print(imu.getCallCounter());  
    Serial.print("\t");  
    Serial.print(ypr[0]/PI*180.0);  
    Serial.print("\t");  
    Serial.print(ypr[1]/PI*180.0);    
    Serial.print("\t");  
    Serial.print(ypr[2]/PI*180.0);    
    Serial.println();  
  }
}




