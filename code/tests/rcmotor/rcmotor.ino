
/* steer robot by model R/C ( Motortreiber ansteuern mit Funke)
 * requires: Arduino Due, PCB 1.3
 */

#include <Arduino.h>
#include "pinman.h"

// ------ pins---------------------------------------
#define pinMotorEnable  37         // EN motors enable
#define pinMotorLeftPWM 5          // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31         // M1_IN2 left motor Dir pin
#define pinMotorLeftSense A1       // M1_FB  left motor current sense
#define pinMotorLeftFault 25       // M1_SF  left motor fault
                                                             
#define pinMotorRightPWM  3        // M2_IN1 right motor PWM pin
#define pinMotorRightDir 33        // M2_IN2 right motor Dir pin
#define pinMotorRightSense A0      // M2_FB  right motor current sense
#define pinMotorRightFault 27      // M2_SF  right motor fault
                                    
#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin (if using MOSFET, use this pin)
#define pinMotorMowDir 29          // M1_IN2 mower motor Dir pin (if using MOSFET, keep unconnected)
#define pinMotorMowSense A3        // M1_FB  mower motor current sense  
#define pinMotorMowFault 26        // M1_SF  mower motor fault   (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowEnable 28       // EN mower motor enable      (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowRpm A11

#define pinRemoteMow 12            // remote control mower motor
#define pinRemoteSteer 11          // remote control steering 
#define pinRemoteSpeed 10          // remote control speed
#define pinRemoteSwitch 52         // remote control switch

#define pinBuzzer 53               // Buzzer

#define pinChargeRelay 50          // charge relay
                                                             
// motor speed
#define motorSpeedMax 255
#define motorMowSpeedMax 255


// R/C measurement
int remoteSteer ;  // range -100..100
int remoteSpeed ;  // range -100..100
int remoteMow ;    // range 0..100
unsigned long remoteSteerLastTime ;
unsigned long remoteSpeedLastTime ;
unsigned long remoteMowLastTime ;
unsigned long remoteSwitchLastTime ;
boolean remoteSteerLastState ;
boolean remoteSpeedLastState ;
boolean remoteMowLastState ;


boolean plot = false;    
unsigned long nextInfoTime = 0;


// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;
    PinMan.analogWrite(pinPWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    PinMan.analogWrite(pinPWM, ((byte)speed));
  }
}

int rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;
  return value;
}

// RC remote control driver
void setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState, 
  boolean remoteMowState){
  if (remoteSpeedState != remoteSpeedLastState) {    
    remoteSpeedLastState = remoteSpeedState;
    if (remoteSpeedState) remoteSpeedLastTime = timeMicros; else remoteSpeed = rcValue(timeMicros - remoteSpeedLastTime);
  }
  if (remoteSteerState != remoteSteerLastState) {    
    remoteSteerLastState = remoteSteerState;
    if (remoteSteerState) remoteSteerLastTime = timeMicros; else remoteSteer = rcValue(timeMicros - remoteSteerLastTime);
  }
  if (remoteMowState != remoteMowLastState) {    
    remoteMowLastState = remoteMowState;
    if (remoteMowState) remoteMowLastTime = timeMicros; else remoteMow = max(0, (rcValue(timeMicros - remoteMowLastTime)+100)/2);
  }  
}


// remote control (RC) ppm signal change interrupt
ISR(PCINT0_vect){   
  unsigned long timeMicros = micros();
  boolean remoteSpeedState = digitalRead(pinRemoteSpeed);
  boolean remoteSteerState = digitalRead(pinRemoteSteer);
  boolean remoteMowState = digitalRead(pinRemoteMow);    
  setRemotePPMState(timeMicros, remoteSpeedState, remoteSteerState, remoteMowState);    
}

void setup(){
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(19200); // setup baud rate 
  PinMan.begin();    

  // charging
  pinMode(pinChargeRelay, OUTPUT);
  digitalWrite(pinChargeRelay, HIGH);
  
  // left wheel motor
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);   
  pinMode(pinMotorEnable, OUTPUT);  
  digitalWrite(pinMotorEnable, HIGH);  
  
  // right wheel motor
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT); 
  
  // mower motor
  //pinMode(pinMotorMowPWM, OUTPUT);       
  
  // R/C  (enable interrupts)
  pinMode(pinRemoteMow, INPUT);
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT);        

  attachInterrupt(pinRemoteSpeed, PCINT0_vect, CHANGE);            
  attachInterrupt(pinRemoteSteer, PCINT0_vect, CHANGE);            
  attachInterrupt(pinRemoteMow, PCINT0_vect, CHANGE);     
  attachInterrupt(pinRemoteSwitch, PCINT0_vect, CHANGE);         
	
	
#ifdef __AVR__
  //-------------------------------------------------------------------------
	// Switch
	//-------------------------------------------------------------------------
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT1);

	//-------------------------------------------------------------------------
	// R/C
	//-------------------------------------------------------------------------
	PCICR |= (1<<PCIE0);
	
	PCMSK0 |= (1<<PCINT4);
	PCMSK0 |= (1<<PCINT5);
	PCMSK0 |= (1<<PCINT6);	
#endif
 	

  unsigned long endTime = millis() + 2000;
  while (millis() < endTime){
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, -127);
    setMC33926(pinMotorRightDir, pinMotorRightPWM, 127);
    delay(100);
  }
}

void loop(){
  // R/C conversion to motor speed (left/right)
  float steer = ((double)motorSpeedMax/2) * (((double)remoteSteer)/100.0);
  if (remoteSpeed < 0) steer *= -1;
  int motorLeftSpeed  = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) - steer; 
  int motorRightSpeed = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) + steer; 
  motorLeftSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorLeftSpeed));
  motorRightSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorRightSpeed));
  int motorMowSpeed = ((double)motorMowSpeedMax) * (((double)remoteMow)/100.0);        

  setMC33926(pinMotorLeftDir, pinMotorLeftPWM, motorLeftSpeed);
  setMC33926(pinMotorRightDir, pinMotorRightPWM, motorRightSpeed);

  // mower motor  
  analogWrite(pinMotorMowPWM, motorMowSpeed);
  
  if (Serial.available()){
    char ch = Serial.read();
    if (ch == 'p') plot = !plot;
  }
  if (millis() >= nextInfoTime){
      nextInfoTime = millis() + 300; // choose time interval here
      // serial console output
      Serial.print("steer=");
      Serial.print(remoteSteer);
      Serial.print("  speed=");
      Serial.print(remoteSpeed);
      Serial.print("  mleft=");
      Serial.print(motorLeftSpeed);
      Serial.print("  mright=");
      Serial.print(motorRightSpeed);      
      Serial.println();    
  }
  
  delay(15);
}

