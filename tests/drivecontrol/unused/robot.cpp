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
      case 'p':
        motorPIDTest();
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



void RobotControl::motorPIDTest(){
  unsigned long nextInfoTime = 0;
  unsigned long nextSpeedTime = 0;  
  int test = 0;

  while (true){    
    if (millis() >= nextInfoTime){
      nextInfoTime = millis() + 1000;    
      MotorCtrl.print();        
      Console.println();
    } 
  
    //if (MotorCtrl.motion == MOTION_STOP)  {
    if (MotorCtrl.hasStopped())  {
      switch(test){
        case 0:
          Console.println("=========FORWARD==========");
          MotorCtrl.travelLineDistance(9000, MotorCtrl.motorSpeedMaxRpm);             
          //MotorCtrl.setSpeedRpm(0, 0);               
          break;
        case 1:
          Console.println("=========REVERSE==========");        
          MotorCtrl.travelLineDistance(-200, MotorCtrl.motorSpeedMaxRpm);                     
          break;
        case 2:        
          Console.println("=========ROTATE==========");                
          MotorCtrl.rotate(1.5*PI, MotorCtrl.motorSpeedMaxRpm);                   
          break;
      }      
      test++;
      if (test >= 3) test = 0;
    }
    
    MotorCtrl.run();          
  
    if (Console.available() > 0){
      char ch = (char)Console.read();      
      switch (ch){
        case '1':
         MotorCtrl.motorLeftPID.Kp += 0.01;
         break;
        case 'q':
          MotorCtrl.motorLeftPID.Kp -= 0.01;
          break;
        case '2':
          MotorCtrl.motorLeftPID.Ki += 0.01;
          break;
        case 'w':
          MotorCtrl.motorLeftPID.Ki -= 0.01;
          break;
        case '3':
          MotorCtrl.motorLeftPID.Kd += 0.01;
          break;
        case 'e':
          MotorCtrl.motorLeftPID.Kd -= 0.01;
          break;
      }  
    }  
  }
}




