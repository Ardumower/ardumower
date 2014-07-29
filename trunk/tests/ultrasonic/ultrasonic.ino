
/* ultrasonic test
 */

#include <Arduino.h>


#ifndef __AVR__
  #define Serial SerialUSB
#endif


#define pinTrigger 5
#define pinEcho    6


// HC-SR04 ultrasonic sensor driver
unsigned int readHCSR04(int triggerPin, int echoPin){
  unsigned int uS;  
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  uS = pulseIn(echoPin, HIGH);  
  return uS;
}


void setup()  {
  Serial.begin(19200);
  while (!Serial) ; // required if using Due native port  
  Serial.println("START");  
}

void loop()  {
  int x = readHCSR04(pinTrigger, pinEcho);
  Serial.println(x);
  delay(200);
}




