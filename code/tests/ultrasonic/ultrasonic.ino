
/* ultrasonic test - Arduino Due
 * HC-SR04 ultrasonic sensor (2cm - 400cm)
 * use Arduino IDE serial plott (CTRL+SHIFT+L) for visualization
 */

#include <Arduino.h>
#include "RunningMedian.h"


#define pinTrigger1 34
#define pinEcho1    36

#define pinTrigger2 24
#define pinEcho2    22

#define pinTrigger3 30
#define pinEcho3    32

#define pinBuzzer 53               // Buzzer

#define MAX_DURATION 4000

#define Serial SerialUSB


RunningMedian<unsigned int,20> sonar1Measurements;
RunningMedian<unsigned int,20> sonar2Measurements;
RunningMedian<unsigned int,20> sonar3Measurements;
volatile byte echoPin = pinEcho1;
volatile unsigned long startTime = 0;
volatile unsigned long echoTime = 0;
volatile unsigned long echoDuration = 0;
volatile byte idx = 0;
bool added = false;
unsigned long timeoutTime = 0;
unsigned long nextSonarTime = 0;
unsigned long nextPrintTime = 0;



// HC-SR04 ultrasonic sensor driver (2cm - 400cm)
void startHCSR04(int triggerPin, int aechoPin){
  echoPin = aechoPin;
  unsigned int uS;            
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);   
  digitalWrite(triggerPin, LOW);      
  /*// if there is no reflection, we will get 0  (NO_ECHO)
  uS = pulseIn(echoPin, HIGH, MAX_ECHO_TIME);  
  //if (uS == MAX_ECHO_TIME) uS = NO_ECHO;
  //if (uS < MIN_ECHO_TIME) uS = NO_ECHO;
  return uS;*/  
  
}

void echoSignal1(){
  if (idx != 0) return;
  if (digitalRead(pinEcho1) == HIGH) {    
    echoTime = 0;
    startTime = micros();           
  } else {    
    echoTime = micros();            
    echoDuration = echoTime - startTime;          
  }
}

void echoSignal2(){
  if (idx != 1) return;
  if (digitalRead(pinEcho2) == HIGH) {    
    echoTime = 0;
    startTime = micros();           
  } else {    
    echoTime = micros();            
    echoDuration = echoTime - startTime;          
  }
}
void echoSignal3(){
  if (idx != 2) return;
  if (digitalRead(pinEcho3) == HIGH) {    
    echoTime = 0;
    startTime = micros();           
  } else {    
    echoTime = micros();            
    echoDuration = echoTime - startTime;          
  }
}

void setup()  {
  pinMode(pinBuzzer, OUTPUT);
	pinMode(pinTrigger1 , OUTPUT);
  pinMode(pinTrigger2 , OUTPUT);
  pinMode(pinTrigger3 , OUTPUT);
  pinMode(pinEcho1 , INPUT);  
  pinMode(pinEcho2 , INPUT);  
  pinMode(pinEcho3 , INPUT);  

  attachInterrupt(pinEcho1, echoSignal1, CHANGE);
  attachInterrupt(pinEcho2, echoSignal2, CHANGE);
  attachInterrupt(pinEcho3, echoSignal3, CHANGE);

  Serial.begin(115200);     
  Serial.println("START");
}

void loop()  {
  float avg;
  unsigned int median1 = 0;
  unsigned int median2 = 0;
  unsigned int median3 = 0;
  unsigned long raw;  
  
  if (echoDuration != 0) {            
    added = true;
    raw = echoDuration;    
    if (raw > MAX_DURATION) raw = MAX_DURATION;
    if (idx == 0) sonar1Measurements.add(raw);        
      else if (idx == 1) sonar2Measurements.add(raw);        
      else sonar3Measurements.add(raw);        
    echoDuration = 0;
  }
      
  if (millis() > timeoutTime){                    
    if (!added) {                      
      if (idx == 0) sonar1Measurements.add(MAX_DURATION);        
        else if (idx == 1) sonar2Measurements.add(MAX_DURATION);        
        else sonar3Measurements.add(MAX_DURATION);             
    }
    //if (millis() > nextSonarTime){        
    idx = (idx + 1) % 3;
      //nextSonarTime = millis() + 100;
    //}
    echoDuration = 0;		
		if (idx == 0) startHCSR04(pinTrigger1, pinEcho1);        
      else if (idx == 1) startHCSR04(pinTrigger2, pinEcho2);        
      else startHCSR04(pinTrigger3, pinEcho3);            		
    timeoutTime = millis() + 10;    
		added = false;
  }


  if (millis() > nextPrintTime){
    nextPrintTime = millis() + 100;        
    sonar1Measurements.getAverage(avg);      
    sonar1Measurements.getLowest(median1);   
    sonar2Measurements.getLowest(median2);   
    sonar3Measurements.getLowest(median3);   
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
  }
  
  //delay(50);
  
}




