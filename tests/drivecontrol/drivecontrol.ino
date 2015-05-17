// differential wheels drive controller experiments 
// Requires: Ardumower Mini, Arduino Mega


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
#include "adcman.h"
#include "buzzer.h"
#include "led.h"
#include "motorcontrol.h"
#include "modelrc.h"


boolean useModelRC = true;
unsigned long nextInfoTime = 0;


void setup(){
  Wire.begin();            
  Serial.begin(19200);
  Serial.println("SETUP");       
  LED.playSequence(LED_RED_BLINK);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);  
}

void loop(){  
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
    Serial.print("R/C: ");
    Serial.print(ModelRC.remoteSpeed);
    Serial.print("\t");
    Serial.print(ModelRC.remoteSteer);
    Serial.print("\t");
    Serial.print("  TICKS: ");    
    Serial.print(MotorCtrl.odometryLeftTicks);    
    Serial.print("\t");    
    Serial.print(MotorCtrl.odometryRightTicks);    
    Serial.print("  THETA,DIST: ");    
    Serial.print(MotorCtrl.odometryThetaRadCurr/PI*180.0);        
    Serial.print("\t");    
    Serial.print(MotorCtrl.odometryDistanceCmCurr);       
    Serial.print(" ## ");    
    Serial.print(MotorCtrl.angleToTargetRad/PI*180.0);    
    Serial.print("\t");        
    Serial.print(MotorCtrl.distanceToTargetCm);        
    Serial.print("\t");    
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
    if (ch == 'm') { 
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
      Serial.println("rpm=10,10");      
      MotorCtrl.setSpeedRpm(10, 10); 
    }    
    if (ch == '4') {
      useModelRC = false;
      Serial.println("rpm=-5,+5");
      MotorCtrl.setSpeedRpm(-5, +5); 
    }    
    if (ch == '5') {
      useModelRC = false;
      Serial.println("rpm=+5,-5");
      MotorCtrl.setSpeedRpm(+5, -5); 
    }    
    if (ch == '6') {
      useModelRC = false;
      Serial.println("theta=+45deg");
      MotorCtrl.rotate(PI/2, 5); 
    }    
    if (ch == '7') {
      useModelRC = false;
      Serial.println("theta=-45deg"); 
      MotorCtrl.rotate(-PI/2, 5); 
    }    
    if (ch == '8') {
      useModelRC = false;
      Serial.println("distance=+30cm"); 
      MotorCtrl.travelLineDistance(30, 5); 
    }    
    if (ch == '9') {
      useModelRC = false;
      Serial.println("distance=-30cm"); 
      MotorCtrl.travelLineDistance(-30, 5); 
    }           
  }  
  
  if (useModelRC) ModelRC.run();
  MotorCtrl.run();
  Buzzer.run();  
  LED.run();
  delay(50);
  
  //if (!Buzzer.isPlaying()) Buzzer.play(BC_LONG_SHORT_SHORT);
}



