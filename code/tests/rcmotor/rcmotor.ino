
/* Arduino Mega:   
   -steer robot by model R/C ( Motortreiber ansteuern mit Funke)
   -read lawn sensors, plot them via SerialChart
 */

#include <Arduino.h>

// model R/C  (ppm signal)
#define pinRemoteSpeed 10          // remote control speed 
#define pinRemoteSteer 11          // remote control steering 
#define pinRemoteMow   12          // remote control mower motor

// wheel motors (PWM, Dir)
#define pinMotorLeftPWM 5          // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31         // M1_IN2 left motor Dir pin
#define pinMotorRightPWM  3        // M2_IN1 right motor PWM pin
#define pinMotorRightDir 33        // M2_IN2 right motor Dir pin

// mower motor (PWM)
#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin

// lawn sensor (digital)
#define CHANNELS 6                 // number sensor channels
int pinLawn[CHANNELS] = {A8,A9,A10,A11,A12,A13};     // lawn sensor pins
                                                             
// motor speed
#define motorSpeedMax 255
#define motorMowSpeedMax 255

// lawn sensor measurement
int lawnFreq[CHANNELS];
int lawnState[CHANNELS];

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

// lawn sensor signal change interrupt
ISR(PCINT2_vect){   
  for (int i=0; i < CHANNELS; i++){
    int state = digitalRead(pinLawn[i]);
    if (lawnState[i] != state){
      lawnState[i] = state;
      lawnFreq[i]++;
    }
  }  
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
  
  // R/C  (enable interrupts)
  pinMode(pinRemoteMow, INPUT);
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT);   
  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT4);
  PCMSK0 |= (1<<PCINT5);
  PCMSK0 |= (1<<PCINT6);
  
  // lawn sensors (enable interrupts)
  for (int i=0; i < CHANNELS; i++){
    pinMode(pinLawn[i], INPUT);
  }
  PCICR |= (1<<PCIE2);
  PCMSK2 |= (1<<PCINT16);
  PCMSK2 |= (1<<PCINT17);
  PCMSK2 |= (1<<PCINT18);
  PCMSK2 |= (1<<PCINT19);  
  PCMSK2 |= (1<<PCINT20);
  PCMSK2 |= (1<<PCINT21); 
  
  Serial.begin(19200); // setup baud rate to 19200 baud
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

  // for L298N motor driver (or similar)
  setL298N(pinMotorLeftDir, pinMotorLeftPWM, motorLeftSpeed);

  // mower motor  
  analogWrite(pinMotorMowPWM, motorMowSpeed);
  
  if (Serial.available()){
    char ch = Serial.read();
    if (ch == 'p') plot = !plot;
  }
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 300; // choose time interval here
    if (plot){ 
      // serial output for serial chart
      for (int i=0; i < CHANNELS; i++){ 
        Serial.print(lawnFreq[i]);
        Serial.print(",");      
      }
      Serial.println();
    } else {
      // serial console output
      Serial.print("steer=");
      Serial.print(remoteSteer);
      Serial.print("  speed=");
      Serial.print(remoteSpeed);
      Serial.print("  mleft=");
      Serial.print(motorLeftSpeed);
      Serial.print("  mright=");
      Serial.print(motorRightSpeed);
      Serial.print("  freq=");    
      for (int i=0; i < CHANNELS; i++){
        Serial.print(lawnFreq[i]);
        Serial.print(",");      
      }
      Serial.println();
    }
    // reset measurements to zero
    for (int i=0; i < CHANNELS; i++){
      lawnFreq[i]=0;
    }
  }
  
  delay(15);
}

