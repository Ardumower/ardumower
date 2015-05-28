#include <Arduino.h>
#include <Wire.h>
#include "robot.h"

RobotControl Robot;



RobotControl::RobotControl(){     
  loopCounter = 0;
  nextPrintTime = 0;
}


void RobotControl::setup(){
  Wire.begin();            
  Console.begin(BAUDRATE);
  Console.println(F("-----SETUP-----"));         

  Button.setup();    
  ADCMan.setup();  
  Battery.setup();    
  Buzzer.setup();    
  LED.setup();  
  Timer.setup();  
  MotorCtrl.setup();  
  MotorMow.setup();
  ModelRC.setup();
  Sonar.setup();  
  Perimeter.setup();

  Config.setup();
  
  // low-to-high priority  
  arbitrator.addBehavior(&standbyBehavior);          
  arbitrator.addBehavior(&driveForwardBehavior);  
  arbitrator.addBehavior(&trackingBehavior);    
  arbitrator.addBehavior(&hitObstacleBehavior);      
  arbitrator.addBehavior(&hitPerimeterBehavior);        
  arbitrator.addBehavior(&modelRCBehavior);     
  arbitrator.addBehavior(&fatalErrorBehavior);  
  arbitrator.addBehavior(&chargingBehavior);          
  arbitrator.addBehavior(&userInteractionBehavior);            
  
  setStandbyMode();
  
  Console.println(F("-----SETUP completed-----"));
  #ifdef SIMULATE
    Console.println(F("SIMULATION active!"));
    if (!Buzzer.isPlaying()) Buzzer.play(BC_SHORT_SHORT_SHORT);      
  #endif
  if (!Buzzer.isPlaying()) Buzzer.play(BC_SHORT);      
}


void RobotControl::setAutoMode(){
  Console.println(F("RobotControl::setAutoMode"));
  Robot.driveForwardBehavior.enable(true);          
  Robot.hitObstacleBehavior.enable(true);          
  Robot.hitPerimeterBehavior.enable(true);            
  Robot.trackingBehavior.enable(true);  
  Robot.modelRCBehavior.enable(false);            
}
 
void RobotControl::setModelRCMode(){
  Console.println(F("RobotControl::setModelRCMode"));
  Robot.modelRCBehavior.enable(true);    
  Robot.driveForwardBehavior.enable(false);          
  Robot.hitObstacleBehavior.enable(false);            
  Robot.hitPerimeterBehavior.enable(false);              
  Robot.trackingBehavior.enable(false);
}
 
void RobotControl::setStandbyMode(){
  Console.println(F("RobotControl::setStandbyMode"));  
  Robot.modelRCBehavior.enable(false);    
  Robot.driveForwardBehavior.enable(false);          
  Robot.hitObstacleBehavior.enable(false);                        
  Robot.hitPerimeterBehavior.enable(false);              
  Robot.trackingBehavior.enable(false);  
}


void RobotControl::checkKey(){
  while (Console.available() > 0){    
    char ch = (char)Console.read();          
    switch (ch){
      // simulate button press
      case '1': Button.setBeepCount(1); break;       
      case '2': Button.setBeepCount(2); break;             
      case '3': Button.setBeepCount(3); break;             
      case '4': Button.setBeepCount(4); break;             
      case '5': Button.setBeepCount(5); break;                   
      case 'm': 
        MotorCtrl.enableSpeedControl = false;
        MotorCtrl.setSpeedPWM(127, 127);  
        break;
      case 's': 
        // simulate sonar trigger
        Sonar.sonarDistLeft = Sonar.sonarTriggerBelow-1; 
        break;
      case 'e': 
        // simulate motor error
        MotorCtrl.motorLeftError = true;  
        break;
      case 'h':
        // simulate low battery voltage
        Battery.batVoltage = 18;
        break;
      case 'b': 
        // simulate charger connection
        if (Battery.chgVoltage > 5){
          Battery.chgVoltage = 0; 
          Battery.batVoltage = 24;           
        } else { 
          Battery.chgVoltage = 27; 
          Battery.batVoltage = 24;           
        }          
        break;
      case 't':
        // force tracking behavior
        arbitrator.setNextBehavior(&trackingBehavior);
        break;
    }
  }        
}


void RobotControl::print(){  
  Console.print("loopsPerSec=");
  Console.print(((double)loopCounter)/10.0);  
  Console.print("  behavior=");
  if (arbitrator.activeBehavior){
    Console.print(arbitrator.activeBehavior->name);
  }
  Console.println();
  loopCounter = 0;
}
  
// call this in ANY loop!
void RobotControl::run(){  
  //Console.println(F("RobotControl::run"));
    
  arbitrator.monitor();        
  ADCMan.run();
  MotorCtrl.run();    
  MotorMow.run();
  Buzzer.run();  
  LED.run();
  Button.run();
  checkKey();  
  Battery.run();
  Sonar.run();
  Timer.run();
  
  if (millis() >= nextPrintTime){
    nextPrintTime = millis() + 10000;
    print();
  }
  
  //delay(50);  
  loopCounter++;
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
  //Console.print(F("RobotControl::loop "));
  //Console.println(loopCounter);  
  arbitrator.run();      
}



/*
void testloop(){
  boolean useModelRC = true;
  unsigned long nextInfoTime = 0;
  
  
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
    //ModelRC.print();
    //MotorCtrl.print();        
    //Console.println();
  } 

  if (Console.available() > 0){
    char ch = (char)Console.read();      
    if (ch == 'm') { 
      MotorCtrl.enableSpeedControl = true;
      useModelRC = true;
      Console.println(F("useModelRC"));
    }            
    if (ch == 'o') { 
      MotorCtrl.enableSpeedControl = false;
      useModelRC = false;
      Console.println(F("pwm=127,127"));      
      MotorCtrl.setSpeedPWM(127, 127); 
    }        
    if (ch == 'p') { 
      MotorCtrl.enableSpeedControl = false;
      useModelRC = false;
      Console.println(F("pwm=255,255"));      
      MotorCtrl.setSpeedPWM(255, 255); 
    }    
    if (ch == '1') { 
      MotorCtrl.enableSpeedControl = true;      
      useModelRC = false;
      Console.println(F("rpm=0,0"));
      MotorCtrl.setSpeedRpm(0, 0); 
      MotorCtrl.resetStalled();          
    }        
    if (ch == '2') {
      MotorCtrl.enableSpeedControl = true;      
      useModelRC = false;
      Console.println(F("rpm=5,5"));
      MotorCtrl.setSpeedRpm(5, 5); 
    }    
    if (ch == '3') {
      useModelRC = false;
      Console.println(F("rpm=10,10"));      
      MotorCtrl.setSpeedRpm(10, 10); 
    }    
    if (ch == '4') {
      useModelRC = false;
      Console.println(F("rpm=-5,+5"));
      MotorCtrl.setSpeedRpm(-5, +5); 
    }    
    if (ch == '5') {
      useModelRC = false;
      Console.println(F("rpm=+5,-5"));
      MotorCtrl.setSpeedRpm(+5, -5); 
    }    
    if (ch == '6') {
      useModelRC = false;
      Console.println(F("theta=+45deg"));
      MotorCtrl.rotate(PI/2, 5); 
    }    
    if (ch == '7') {
      useModelRC = false;
      Console.println(F("theta=-45deg")); 
      MotorCtrl.rotate(-PI/2, 5); 
    }    
    if (ch == '8') {
      useModelRC = false;
      Console.println(F("distance=+30cm")); 
      MotorCtrl.travelLineDistance(30, 5); 
    }    
    if (ch == '9') {
      useModelRC = false;
      Console.println(F("distance=-30cm")); 
      MotorCtrl.travelLineDistance(-30, 5); 
    }           
  }  
  
  if ((MotorCtrl.motorRightError) || (MotorCtrl.motorLeftError)){
    Console.println(F("ERROR"));    
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

*/


