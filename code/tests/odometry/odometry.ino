
/* odometry test  (Arduino Due, PCB1.3)
 */

#include <Arduino.h>
#include "pinman.h"


#define pinBuzzer 53               // Buzzer

#define pinOdometryLeft DAC0     // left odometry sensor
#define pinOdometryRight CANRX   // right odometry sensor  


int odometryLeft ;   // left wheel counter
int odometryRight ;  // right wheel counter

int lastOdometryLeft = 0 ;   
int lastOdometryRight = 0;  

volatile long oldOdoPins_A = 0;
volatile long oldOdoPins_B = 0;
  
void OdometryRightInt(){
  odometryRight++;      
}

void OdometryLeftInt(){
  odometryLeft++;                          
}


void setup()  {
  PinMan.begin();
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(19200);    
  Serial.println("START");  
  
  // odometry
  pinMode(pinOdometryLeft, INPUT_PULLUP);  
  pinMode(pinOdometryRight, INPUT_PULLUP);
  //pinMode(pinOdometryLeft, INPUT);  
  //pinMode(pinOdometryRight, INPUT);  
  
  attachInterrupt(pinOdometryLeft, OdometryLeftInt, RISING);    
  attachInterrupt(pinOdometryRight, OdometryRightInt, RISING);  
  PinMan.setDebounce(pinOdometryLeft, 100);  // reject spikes shorter than usecs on pin
  PinMan.setDebounce(pinOdometryRight, 100);  // reject spikes shorter than usecs on pin         
}

void loop()  {  
  if ( (odometryLeft != lastOdometryLeft) || (odometryRight != lastOdometryRight) ){    
    Serial.print(odometryLeft);    
    Serial.print(",");    
    Serial.print(odometryRight);    
    Serial.println();       
    lastOdometryLeft = odometryLeft;
    lastOdometryRight = odometryRight;    
  }  
  delay(50);
}





