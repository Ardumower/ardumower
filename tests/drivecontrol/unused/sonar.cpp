#include "sonar.h"
#include "drivers.h"
#include "config.h"


SonarControl Sonar;


#define NO_ECHO 0
// ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
#define MAX_ECHO_TIME 3000
//#define MIN_ECHO_TIME 350                  
#define MIN_ECHO_TIME 0


SonarControl::SonarControl(){  
  nextSonarTime = 0;
  enableLeft = false;
  enableRight = false;
  enableCenter = false;
  sonarTriggerBelow = 900;    // ultrasonic sensor trigger distance
  sonarDistCenter = sonarDistLeft = sonarDistRight = 0;
  sonarDistCounter  = 0;             
}

void SonarControl::setup(){
  Console.println(F("SonarControl::setup"));
  // sonar
  pinMode(pinSonarCenterTrigger, OUTPUT); 
  pinMode(pinSonarCenterEcho, INPUT); 
  pinMode(pinSonarLeftTrigger, OUTPUT); 
  pinMode(pinSonarLeftEcho, INPUT); 
  pinMode(pinSonarRightTrigger, OUTPUT); 
  pinMode(pinSonarRightEcho, INPUT); 
}

bool SonarControl::triggeredLeft(){
  return ((sonarDistLeft != NO_ECHO) &&  (sonarDistLeft < sonarTriggerBelow));
}

bool SonarControl::triggeredRight(){
  return ((sonarDistRight != NO_ECHO) &&  (sonarDistRight < sonarTriggerBelow));
}

bool SonarControl::triggeredCenter(){
  return ((sonarDistCenter != NO_ECHO) &&  (sonarDistCenter < sonarTriggerBelow));
}

// call this in main loop
void SonarControl::run(){
  if (millis() < nextSonarTime) return; 
  nextSonarTime = millis() + 1000;
  
  if (enableRight)  sonarDistRight  = readHCSR04(pinSonarRightTrigger,  pinSonarRightEcho);
  if (enableLeft)   sonarDistLeft   = readHCSR04(pinSonarLeftTrigger,   pinSonarLeftEcho);
  if (enableCenter) sonarDistCenter = readHCSR04(pinSonarCenterTrigger, pinSonarCenterEcho);
  
  if ( (triggeredRight()) || (triggeredLeft()) || (triggeredCenter()) ){    
    sonarDistCounter++;    
    print();    
  }   
}


// HC-SR04 ultrasonic sensor driver
unsigned int SonarControl::readHCSR04(int triggerPin, int echoPin){
  unsigned int uS;  
  digitalWrite(triggerPin, LOW);   
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  // ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
  uS = pulseIn(echoPin, HIGH, MAX_ECHO_TIME + 1000);  
  if (uS > MAX_ECHO_TIME) uS = NO_ECHO;
    else if (uS < MIN_ECHO_TIME) uS = NO_ECHO;
  return uS;
}

void SonarControl::print(){
  Console.print(F("sonar L,C,R="));
  Console.print(sonarDistLeft);
  Console.print(sonarDistCenter);
  Console.print(sonarDistRight);  
  Console.println();
}  

  
