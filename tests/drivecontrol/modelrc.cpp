#include "modelrc.h"
#include "motorcontrol.h"
#include "config.h"
#include "drivers.h"

ModelReceiver ModelRC;

static unsigned long remoteSteerLastTime ;
static unsigned long remoteSpeedLastTime ;
static boolean remoteSteerLastState ;
static boolean remoteSpeedLastState ;        


// ---- RC (interrupt) --------------------------------------------------------------
// RC remote control helper
// convert ppm time (us) to percent (-100..+100)
// ppmtime: zero stick pos: 1500 uS 		
//          right stick pos: 2000 uS 		
//          left stick pos: 1000 uS
int rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;  //  ensures exact zero position
  return value;
}


// remote control (RC) ppm signal change interrupt
ISR(PCINT0_vect){   
  unsigned long timeMicros = micros();
  boolean remoteSpeedState = digitalRead(pinRemoteSpeed);
  boolean remoteSteerState = digitalRead(pinRemoteSteer);  
  if (remoteSpeedState != remoteSpeedLastState) {    
    remoteSpeedLastState = remoteSpeedState;
    if (remoteSpeedState) remoteSpeedLastTime = timeMicros; else ModelRC.remoteSpeed = rcValue(timeMicros - remoteSpeedLastTime);
  }
  if (remoteSteerState != remoteSteerLastState) {    
    remoteSteerLastState = remoteSteerState;
    if (remoteSteerState) remoteSteerLastTime = timeMicros; else ModelRC.remoteSteer = rcValue(timeMicros - remoteSteerLastTime);
  }  
}

void ModelReceiver::setup(){
  Console.println(F("ModelReceiver::setup"));
  // R/C
  pinMode(pinRemoteMow, INPUT);
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT); 
  pinMode(pinRemoteSwitch, INPUT);       
}

ModelReceiver::ModelReceiver(){
  enable=false;
  // configure R/C interrupts
  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT4);
  PCMSK0 |= (1<<PCINT5);      
}

void ModelReceiver::run(){
  if (!enable) return;
  // control motor by R/C receiver
  int steer = ((double)MotorCtrl.motorSpeedMaxRpm/2) * (((double)remoteSteer)/100.0);
  if (remoteSpeed < 0) steer *= -1;
    
  int motorLeftSpeedRpmSet  = ((double)MotorCtrl.motorSpeedMaxRpm) * (((double)remoteSpeed)/100.0) - steer; 
  int motorRightSpeedRpmSet = ((double)MotorCtrl.motorSpeedMaxRpm) * (((double)remoteSpeed)/100.0) + steer; 
  MotorCtrl.setSpeedRpm(motorLeftSpeedRpmSet, motorRightSpeedRpmSet);  
}

void ModelReceiver::print(){
    Console.print(F("RC:"));
    Console.print(ModelRC.remoteSpeed);
    Console.print(",");
    Console.print(ModelRC.remoteSteer);
}


  
