
/* odometry test  (Arduino Due, PCB1.3)
 */

#include <Arduino.h>
#include "pinman.h"


#define pinBuzzer 53               // Buzzer

#define pinOdometryLeft DAC0     // left odometry sensor
#define pinOdometryRight CANRX   // right odometry sensor  


int odometryLeft ;   // left wheel counter
int odometryRight ;  // right wheel counter


volatile long oldOdoPins_A = 0;
volatile long oldOdoPins_B = 0;
  
ISR(PCINT2_vect)
{
    const long actPins_A = REG_PIOA_PDSR;             // read PIO A
    const long actPins_B = REG_PIOB_PDSR;                               // read PIO B
    const long setPins_A = (oldOdoPins_A ^ actPins_A);
    const long setPins_B = (oldOdoPins_B ^ actPins_B);
        
    //Right
    if (setPins_A & 0b00000000000000000000000000000010)     // pin right has changed 
    {      
      odometryRight++;      
      oldOdoPins_A = actPins_A;
    }
    
    //Left
    if (setPins_B & 0b00000000000000001000000000000000)           // pin left has changed
    {            
      odometryLeft++;                 
      oldOdoPins_B = actPins_B;
    }     
}



void setup()  {
  PinMan.begin();
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(19200);    
  Serial.println("START");  
  
  // odometry
  //pinMode(pinOdometryLeft, INPUT_PULLUP);  
  //pinMode(pinOdometryRight, INPUT_PULLUP);
  pinMode(pinOdometryLeft, INPUT);  
  pinMode(pinOdometryRight, INPUT);  
  
  attachInterrupt(pinOdometryLeft, PCINT2_vect, CHANGE);    
  attachInterrupt(pinOdometryRight, PCINT2_vect, CHANGE);  
  //PinMan.setDebounce(pinOdometryLeft, 100);  // reject spikes shorter than usecs on pin
  //PinMan.setDebounce(pinOdometryRight, 100);  // reject spikes shorter than usecs on pin         
}

void loop()  {  
  Serial.print(odometryLeft);    
  Serial.print(",");    
  Serial.print(odometryRight);    
  Serial.println();    
  
  delay(500);
}





