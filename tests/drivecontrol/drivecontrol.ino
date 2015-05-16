// differential wheels drive controller experiments 
// Requires: Ardumower Mini, Arduino Mega

#include <Arduino.h>
#include <Wire.h>
#include "motorcontrol.h"
#include "modelrc.h"


boolean useModelRC = true;
unsigned long nextInfoTime = 0;


void setup(){
  Wire.begin();            
  Serial.begin(19200);
  Serial.println("SETUP");       
}

void loop(){  
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
    Serial.print("R/C: ");
    Serial.print(ModelRC.remoteSpeed);
    Serial.print("\t");
    Serial.print(ModelRC.remoteSteer);
    Serial.print("\t");
    Serial.print("  ODO: ");    
    Serial.print(MotorCtrl.odometryLeft);
    Serial.print("\t");    
    Serial.print(MotorCtrl.odometryRight);    
    Serial.print("  SET: ");    
    Serial.print(MotorCtrl.motorLeftSpeedRpmSet);
    Serial.print("\t");
    Serial.print(MotorCtrl.motorRightSpeedRpmSet);        
    Serial.print("  CUR: ");    
    Serial.print(MotorCtrl.motorLeftRpmCurr);
    Serial.print("\t");
    Serial.print(MotorCtrl.motorRightRpmCurr);        
    Serial.print("  ERR: ");    
    Serial.print(MotorCtrl.motorLeftPID.eold);
    Serial.print("\t");
    Serial.print(MotorCtrl.motorRightPID.eold);            
    Serial.print("  PWM: ");    
    Serial.print(MotorCtrl.motorLeftPWMCurr);
    Serial.print("\t");
    Serial.print(MotorCtrl.motorRightPWMCurr);        
    
    Serial.println();
  } 

  if (Serial.available() > 0){
    char ch = (char)Serial.read();      
    if (ch == 'r') { 
      MotorCtrl.enableSpeedControl = true;
      useModelRC = true;
      Serial.println("useModelRC");
    }            
    if (ch == 'p') { 
      MotorCtrl.enableSpeedControl = false;
      useModelRC = false;
      Serial.println("pwm=127,127");      
      MotorCtrl.setSpeedPWM(127, 127); 
    }    
    if (ch == '1') { 
      MotorCtrl.enableSpeedControl = true;      
      useModelRC = false;
      Serial.println("rpm=0,0");
      MotorCtrl.setSpeedRpm(0, 0); 
    }        
    if (ch == '2') {
      MotorCtrl.enableSpeedControl = true;      
      useModelRC = false;
      Serial.println("rpm=5,5");
      MotorCtrl.setSpeedRpm(5, 5); 
    }    
    if (ch == '3') {
      useModelRC = false;
      Serial.print("rpm=10,10");
      Serial.println(useModelRC);      
      MotorCtrl.setSpeedRpm(10, 10); 
    }    
    
  }
  
  
  if (useModelRC) ModelRC.run();
  MotorCtrl.run();
  delay(50);
}



