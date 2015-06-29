
/* ultrasonic test
 */

#include <Arduino.h>
#include "RunningMedian.h"


#define pinTrigger 24
#define pinEcho    22


// ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
#define MAX_ECHO_TIME 3000     
#define MIN_ECHO_TIME 150    
#define NO_ECHO 0


RunningMedian<unsigned int,4> sonarMeasurements;


// HC-SR04 ultrasonic sensor driver
unsigned int readHCSR04(int triggerPin, int echoPin){
  unsigned int uS;  
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  // if there is no reflection, we will get 0  (NO_ECHO)
  uS = pulseIn(echoPin, HIGH, MAX_ECHO_TIME);  
  //if (uS == MAX_ECHO_TIME) uS = NO_ECHO;
  //if (uS < MIN_ECHO_TIME) uS = NO_ECHO;
  return uS;
}


void setup()  {
  pinMode(pinTrigger , OUTPUT);
  pinMode(pinEcho , INPUT);  

  Serial.begin(19200);  
  Serial.println("START");  
  Serial.println("raw,avg,median,triggered");      
}

void loop()  {
  int triggered = 0;
  float avg;
  unsigned int median;
  int raw;
  raw = readHCSR04(pinTrigger, pinEcho);
  //if (x != NO_ECHO){
    sonarMeasurements.add(raw);
  //}
  sonarMeasurements.getAverage(avg);  
  //if (sonarMeasurements.getStatus() == sonarMeasurements.OK) {
    sonarMeasurements.getMedian(median); 
  //}
  
  if ( (median != NO_ECHO) && (median < 800) ) triggered = 1;
  
  for (int i=0; i < 10; i++){
    Serial.print(raw);    
    Serial.print(",");    
    Serial.print(avg);    
    Serial.print(",");    
    Serial.print(median);        
    Serial.print(",");
    Serial.print(triggered);
    Serial.println();    
  }
  delay(250);
}




