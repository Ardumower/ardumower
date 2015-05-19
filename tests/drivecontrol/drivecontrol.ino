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
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);  
  ADCMan.init();  
  MotorCtrl.init();
  
  LED.playSequence(LED_RED_BLINK);
}

void loop(){  
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
    ModelRC.print();
    MotorCtrl.print();    
    
    Serial.println();
  } 

  if (Serial.available() > 0){
    char ch = (char)Serial.read();      
    if (ch == 'm') { 
      MotorCtrl.enableSpeedControl = true;
      useModelRC = true;
      Serial.println("useModelRC");
    }            
    if (ch == 'o') { 
      MotorCtrl.enableSpeedControl = false;
      useModelRC = false;
      Serial.println("pwm=127,127");      
      MotorCtrl.setSpeedPWM(127, 127); 
    }        
    if (ch == 'p') { 
      MotorCtrl.enableSpeedControl = false;
      useModelRC = false;
      Serial.println("pwm=255,255");      
      MotorCtrl.setSpeedPWM(255, 255); 
    }    
    if (ch == '1') { 
      MotorCtrl.enableSpeedControl = true;      
      useModelRC = false;
      Serial.println("rpm=0,0");
      MotorCtrl.setSpeedRpm(0, 0); 
      MotorCtrl.resetStalled();          
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
  
  if ((MotorCtrl.motorRightError) || (MotorCtrl.motorLeftError)){
    Serial.println("ERROR");    
    if (!Buzzer.isPlaying()) Buzzer.play(BC_SHORT_SHORT_SHORT);    
  }

  ADCMan.run();
  MotorCtrl.run();    
  Buzzer.run();  
  LED.run();
  
  if ((MotorCtrl.motorRightStalled) || (MotorCtrl.motorLeftStalled)){
    if (!Buzzer.isPlaying()) Buzzer.play(BC_LONG_SHORT_SHORT);            
    if (useModelRC) {
      if ( (abs(ModelRC.remoteSpeed) < 5) && (abs(ModelRC.remoteSteer) < 5) ) {
        MotorCtrl.resetStalled();    
      }
    }          
  }
  
  if (useModelRC) {
    ModelRC.run();
  }  
  
  delay(50);
  
}



