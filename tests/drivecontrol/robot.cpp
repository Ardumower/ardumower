#include <Arduino.h>
#include <Wire.h>
#include "robot.h"

RobotControl Robot;

boolean useModelRC = true;
unsigned long nextInfoTime = 0;


RobotControl::RobotControl(){     
  loopCounter = 0;
}


void RobotControl::setup(){
  Wire.begin();            
  Serial.begin(19200);
  Serial.println("SETUP");         
  
  ADCMan.setup();  
  Battery.setup();  
  MotorCtrl.setup();  
  //MotorCtrl.enableStallDetection = false;
  MotorMow.setup();
  Buzzer.setup();    
  Sonar.setup();
  Timer.setup();
  Button.setup();  
  LED.setup();
  
  LED.playSequence(LED_RED_BLINK);
  
  // low-to-high priority
  arbitrator.addBehavior(&standbyBehavior);          
  arbitrator.addBehavior(&driveForwardBehavior);  
  arbitrator.addBehavior(&hitObstacleBehavior);      
  arbitrator.addBehavior(&stopBehavior);      
  arbitrator.addBehavior(&chargerConnectedBehavior);      
  Serial.println("SETUP completed");
}


void testloop(){
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
    //ModelRC.print();
    //MotorCtrl.print();        
    //Serial.println();
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

  
// call this in ANY loop!
void RobotControl::run(){  
  //Serial.println("RobotControl::run");
  
  arbitrator.monitor();    
  ADCMan.run();
  MotorCtrl.run();    
  MotorMow.run();
  Buzzer.run();  
  LED.run();
  Button.run();
  Battery.run();
  Sonar.run();
  Timer.run();
  
  delay(50);  
}

  
  /* program flow:
     a. aribitrator.run (1) calls specific behavior.run (2)
     b. specific behavior.run periodically calls Robot.run (3)
     c. Robot.run processes MotorCtrl, BuzzerCtrl, PfodApp etc. and monitors (4) for behavior suppression (5)
     d. behavior is finsihed if finished or suppressed
     e. arbitrator.run is called again for next behavior     
      
  
     aribitrator                  behavior                   Robot
     --------------------------------------------------------------
(1) run-->|                           |                         |
          |----------------(2)--run-->|                         |
          |                           |--------------(3)--run-->|
          |                           |                         |
          |                           |                         |
          |<--monitor--(4)--------------------------------------|
          |                           |                         |
          |-----------(5)--suppress-->|                         |
          |                           X                         |
          |                                                     |
          |                                                     |
   */

// this is called over and over from the Arduino loop
void RobotControl::loop(){
  //Serial.print("RobotControl::loop ");
  //Serial.println(loopCounter);  
  arbitrator.run();      
  loopCounter++;
}



