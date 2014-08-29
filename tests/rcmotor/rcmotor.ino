
/* Arduino Mega:   
   -steer robot by model R/C ( Motortreiber ansteuern mit Funke)
   -read lawn sensors, plot them via SerialChart
 */

#include <Arduino.h>

// model R/C 
#define pinRemoteMow 12            // remote control mower motor
#define pinRemoteSteer 11          // remote control steering 
#define pinRemoteSpeed 10          // remote control speed

// wheel motors
#define pinMotorLeftPWM 5          // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31         // M1_IN2 left motor Dir pin
#define pinMotorRightPWM  3        // M2_IN1 right motor PWM pin
#define pinMotorRightDir 33        // M2_IN2 right motor Dir pin

// mower motor
#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin
                                                             
// motor driver
#define motorSpeedMax 255
#define motorMowSpeedMax 255

// lawn sensor
#define CHANNELS 6
int lawnFreq[CHANNELS];

// R/C
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
boolean remoteSwitchLastState ;
    
unsigned long nextInfoTime = 0;


// L298N motor driver
// IN2/C(10)/PinPWM   IN1/D(12)/PinDir
// H                  L     Forward
// L                  H     Reverse    
void setL298N(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;  
    analogWrite(pinPWM, speed);
  } else {
    digitalWrite(pinDir, LOW) ;  
    analogWrite(pinPWM, speed);
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
  // left wheel motor
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);   
  
  // right wheel motor
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT); 
  
  // mower motor
  pinMode(pinMotorMowPWM, OUTPUT);       
  
  // R/C 
  pinMode(pinRemoteMow, INPUT);
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT);   
  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT4);
  PCMSK0 |= (1<<PCINT5);
  PCMSK0 |= (1<<PCINT6);
  PCMSK0 |= (1<<PCINT1);  

  Serial.begin(19200);
}

void loop(){
  // R/C
  float steer = ((double)motorSpeedMax/2) * (((double)remoteSteer)/100.0);
  if (remoteSpeed < 0) steer *= -1;
  int motorLeftSpeed  = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) - steer; 
  int motorRightSpeed = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) + steer; 
  motorLeftSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorLeftSpeed));
  motorRightSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorRightSpeed));
  int motorMowSpeed = ((double)motorMowSpeedMax) * (((double)remoteMow)/100.0);        

  // for L298N motor driver
  setL298N(pinMotorLeftDir, pinMotorLeftPWM, motorLeftSpeed);

  // mower motor  
  analogWrite(pinMotorMowPWM, motorMowSpeed);
  
  delay(15);
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
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
}

