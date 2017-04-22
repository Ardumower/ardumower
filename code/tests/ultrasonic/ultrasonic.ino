
/* ultrasonic test - Arduino Due
 */

#include <Arduino.h>
#include "RunningMedian.h"


#define pinTrigger 24
#define pinEcho    22


// ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
#define MAX_ECHO_TIME 3000     
#define MIN_ECHO_TIME 150    
#define NO_ECHO 0


RunningMedian<unsigned int,50> sonarMeasurements;
volatile unsigned long startTime = 0;
volatile unsigned long echoTime = 0;
volatile unsigned long echoDuration = 0;
unsigned long timeoutTime = 0;


// HC-SR04 ultrasonic sensor driver
void startHCSR04(int triggerPin, int echoPin){
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
  if (digitalRead(pinEcho) == HIGH) {    
    echoTime = 0;
    startTime = micros();           
  } else {    
    echoTime = micros();            
    echoDuration = echoTime - startTime;          
  }
}


void setup()  {
  pinMode(pinTrigger , OUTPUT);
  pinMode(pinEcho , INPUT);  

  attachInterrupt(pinEcho, echoSignal, CHANGE);

  Serial.begin(115200);  
  Serial.println("START");  
  Serial.println("raw,avg,median,triggered");      
}

void loop()  {
  int triggered = 0;
  float avg;
  unsigned int median;
  unsigned long raw;
  if (millis() > timeoutTime){    
    startHCSR04(pinTrigger, pinEcho);        
    timeoutTime = millis() + 10;
  }
  if (echoDuration != 0) {            
    raw = echoDuration;
    sonarMeasurements.add(raw);        
    sonarMeasurements.getAverage(avg);      
    sonarMeasurements.getMedian(median);   
    Serial.print(avg);    
    Serial.print(",");    
    Serial.print(median); 
    Serial.print(",");                             
    Serial.print(raw);    
    Serial.println();          
    echoDuration = 0;
  }    
  
  
}




