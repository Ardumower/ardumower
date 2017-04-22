
/* ultrasonic test - Arduino Due
 * HC-SR04 ultrasonic sensor (2cm - 400cm)
 * use Arduino IDE serial plott (CTRL+SHIFT+L) for visualization
 */

#include <Arduino.h>
#include "RunningMedian.h"


#define pinTrigger1 24
#define pinEcho1    22

#define pinTrigger2 36
#define pinEcho2    34

#define pinTrigger3 44
#define pinEcho3    42


// ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
#define MAX_ECHO_TIME 3000     
#define MIN_ECHO_TIME 150    
#define NO_ECHO 0


RunningMedian<unsigned int,20> sonar1Measurements;
RunningMedian<unsigned int,20> sonar2Measurements;
RunningMedian<unsigned int,20> sonar3Measurements;
volatile byte echoPin = pinEcho1;
volatile unsigned long startTime = 0;
volatile unsigned long echoTime = 0;
volatile unsigned long echoDuration = 0;
unsigned long timeoutTime = 0;
unsigned long nextSonarTime = 0;
int idx = 0;


// HC-SR04 ultrasonic sensor driver (2cm - 400cm)
void startHCSR04(int triggerPin, int aechoPin){
  echoPin = aechoPin;
  unsigned int uS;          
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);   
  digitalWrite(triggerPin, LOW);      
  /*// if there is no reflection, we will get 0  (NO_ECHO)
  uS = pulseIn(echoPin, HIGH, MAX_ECHO_TIME);  
  //if (uS == MAX_ECHO_TIME) uS = NO_ECHO;
  //if (uS < MIN_ECHO_TIME) uS = NO_ECHO;
  return uS;*/  
  
}

void echoSignal(){
  if (digitalRead(echoPin) == HIGH) {    
    echoTime = 0;
    startTime = micros();           
  } else {    
    echoTime = micros();            
    echoDuration = echoTime - startTime;          
  }
}


void setup()  {
  pinMode(pinTrigger1 , OUTPUT);
  pinMode(pinTrigger2 , OUTPUT);
  pinMode(pinTrigger3 , OUTPUT);
  pinMode(pinEcho1 , INPUT);  
  pinMode(pinEcho2 , INPUT);  
  pinMode(pinEcho3 , INPUT);  

  attachInterrupt(pinEcho1, echoSignal, CHANGE);
  attachInterrupt(pinEcho2, echoSignal, CHANGE);
  attachInterrupt(pinEcho3, echoSignal, CHANGE);

  Serial.begin(115200);     
  Serial.println("START");
}

void loop()  {
  int triggered = 0;
  float avg;
  unsigned int median1 = 0;
  unsigned int median2 = 0;
  unsigned int median3 = 0;
  unsigned long raw;  
  if (millis() > timeoutTime){            
    if (millis() > nextSonarTime){        
      idx = (idx + 1) % 3;
      nextSonarTime = millis() + 100;
    }
    if (idx == 0) startHCSR04(pinTrigger1, pinEcho1);        
      else if (idx == 1) startHCSR04(pinTrigger2, pinEcho2);        
      else startHCSR04(pinTrigger3, pinEcho3);        
    timeoutTime = millis() + 3;    
  }
  if (echoDuration != 0) {            
    raw = echoDuration;    
    if (raw > 4000) raw = 4000;
    if (idx == 0) sonar1Measurements.add(raw);        
      else if (idx == 1) sonar2Measurements.add(raw);        
      else sonar3Measurements.add(raw);        
    sonar1Measurements.getAverage(avg);      
    sonar1Measurements.getMedian(median1);   
    sonar2Measurements.getMedian(median2);   
    sonar3Measurements.getMedian(median3);   
    /*Serial.print(avg);    
    Serial.print(",");    */
    Serial.print(median1); 
    Serial.print(",");  
    Serial.print(median2); 
    Serial.print(",");  
    Serial.print(median3); 
    Serial.print(",");     
    //Serial.print(raw);    
    //Serial.print(",");                             
    Serial.print(5000);    
    Serial.print(",");                             
    Serial.print(0);    
    Serial.println();          
    echoDuration = 0;
  }    
  
  
}




