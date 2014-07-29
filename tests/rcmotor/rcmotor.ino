
/* Arduino Mega:
   steer motor by a model R/C 
  ( Motortreiber ansteuern mit Funke)
 */

#include <Arduino.h>


#define pinRemoteSteer 11          // remote control steering 
#define pinMotorDir 33 
#define pinMotorPWM 3


unsigned long remoteSteerLastTime = 0;
int remoteSteer = 0;  // range -100..100
boolean remoteSteerLastState = LOW;
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

// L9958 motor driver
// PinPWM             PinDir
// H                  H     Forward
// H                  L     Reverse    
void setL9958(int pinDir, int pinPWM, int speed){
  if (speed > 0){
    digitalWrite(pinDir, HIGH) ;  
    analogWrite(pinPWM, abs(speed));
  } else {
    digitalWrite(pinDir, LOW) ;  
    analogWrite(pinPWM, abs(speed));
  }
}

int rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;
  return value;
}

// RC remote control driver
void setRemotePPMState(unsigned long timeMicros, boolean remoteSteerState){
  if (remoteSteerState != remoteSteerLastState) {    
    remoteSteerLastState = remoteSteerState;
    if (remoteSteerState) remoteSteerLastTime = timeMicros; else remoteSteer = rcValue(timeMicros - remoteSteerLastTime);
  }
}

// remote control (RC) ppm signal change interrupt
ISR(PCINT0_vect)
{   
  unsigned long timeMicros = micros();
  boolean remoteSteerState = digitalRead(pinRemoteSteer);
  setRemotePPMState(timeMicros, remoteSteerState);    
}

void setup(){
  // enable signal change interrupt on pin11 (PCINT5)
  // Diese Zeilen sind fuer Arduino Mega - fuere andere Arduinos anpassen (Handbuch)
  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT5);
  pinMode(pinMotorPWM, OUTPUT);
  pinMode(pinMotorDir, OUTPUT);   
  Serial.begin(19200);
}

void loop(){
  // Motortreiber ansteuern mit aktueller Stellung der Funke
  int speed = ((double)remoteSteer) * 2.5f;

  // for L9958 motor driver
  //setL9958(pinMotorDir, pinMotorPWM, speed );
  
  // for L298N motor driver
  setL298N(pinMotorDir, pinMotorPWM, speed);
  
  delay(15);
  if (millis() >= nextInfoTime){
    nextInfoTime = millis() + 500;
    Serial.print("remoteSteer=");
    Serial.print(remoteSteer);
    Serial.print("  speed=");
    Serial.println(speed);
  }
}

