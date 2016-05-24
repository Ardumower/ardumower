
/* odometry test  (Arduino Mega)
 */

#include <Arduino.h>


#define pinOdometryLeft A12      // left odometry sensor
#define pinOdometryLeft2 A13     // left odometry sensor (optional two-wire)
#define pinOdometryRight A14     // right odometry sensor 
#define pinOdometryRight2 A15    // right odometry sensor (optional two-wire)  

bool twoWayOdometrySensorUse = 0;
bool odometryRightSwapDir = 0;       // inverse right encoder direction?
bool odometryLeftSwapDir = 0;       // inverse left encoder direction?        

int odometryLeft ;   // left wheel counter
int odometryRight ;  // right wheel counter

int motorLeftPWMCurr = 255;
int motorRightPWMCurr = 255;

boolean odometryLeftLastState;
boolean odometryLeftLastState2;
boolean odometryRightLastState;
boolean odometryRightLastState2;
    


// Determines the rotation count and direction of the odometry encoders. Called in the odometry pins interrupt.
// encoder signal/Ardumower pinout etc. at http://wiki.ardumower.de/index.php?title=Odometry
// Logic is: 
//    If the pin1 change transition (odometryLeftState) is LOW -> HIGH... 
//      If the pin2 current state is HIGH :  step count forward   (odometryLeft++)
//        Otherwise :  step count reverse   (odometryLeft--)   
// odometryState:  1st left and right odometry signal
// odometryState2: 2nd left and right odometry signal (optional two-wire encoders)
void setOdometryState(unsigned long timeMicros, boolean odometryLeftState, boolean odometryRightState, boolean odometryLeftState2, boolean odometryRightState2){
  int leftStep = 1;
  int rightStep = 1;
  if (odometryLeftSwapDir) leftStep = -1;
  if (odometryRightSwapDir) rightStep = -1;
  if (odometryLeftState != odometryLeftLastState){    
    if (odometryLeftState){ // pin1 makes LOW->HIGH transition
      if (twoWayOdometrySensorUse) { 
        // pin2 = HIGH? => forward 
        if (odometryLeftState2) odometryLeft += leftStep; else odometryLeft -= leftStep;
      } 
      else { 
         if (motorLeftPWMCurr >=0) odometryLeft ++; else odometryLeft --;
      }
    }
    odometryLeftLastState = odometryLeftState;
  } 

  if (odometryRightState != odometryRightLastState){
    if (odometryRightState){ // pin1 makes LOW->HIGH transition
      if (twoWayOdometrySensorUse) {
        // pin2 = HIGH? => forward
        if (odometryRightState2) odometryRight += rightStep; else odometryRight -= rightStep;
      }     
      else {
         if (motorRightPWMCurr >=0) odometryRight ++; else odometryRight --;    
      }
    }
    odometryRightLastState = odometryRightState;
  }  
  if (twoWayOdometrySensorUse) {
    if (odometryRightState2 != odometryRightLastState2){
      odometryRightLastState2 = odometryRightState2;    
    }  
    if (odometryLeftState2 != odometryLeftLastState2){
      odometryLeftLastState2 = odometryLeftState2;    
    }
  }    
}



// odometry signal change interrupt
ISR(PCINT2_vect, ISR_NOBLOCK){
  unsigned long timeMicros = micros();
  boolean odometryLeftState = digitalRead(pinOdometryLeft);
  boolean odometryLeftState2 = digitalRead(pinOdometryLeft2);
  boolean odometryRightState = digitalRead(pinOdometryRight);  
  boolean odometryRightState2 = digitalRead(pinOdometryRight2);  
  setOdometryState(timeMicros, odometryLeftState, odometryRightState, odometryLeftState2, odometryRightState2);   
}


void setup()  {
  Serial.begin(19200);  
  Serial.println("START");  
  
  // odometry
  pinMode(pinOdometryLeft, INPUT_PULLUP);  
  pinMode(pinOdometryLeft2, INPUT_PULLUP);    
  pinMode(pinOdometryRight, INPUT_PULLUP);
  pinMode(pinOdometryRight2, INPUT_PULLUP);    
  
  
  // enable odometry interrupts
  PCICR |= (1<<PCIE2);
  PCMSK2 |= (1<<PCINT20);
  PCMSK2 |= (1<<PCINT21);  
  PCMSK2 |= (1<<PCINT22);
  PCMSK2 |= (1<<PCINT23);                
}


void loop()  {
  
  Serial.print(odometryLeft);    
  Serial.print(",");    
  Serial.print(odometryRight);    
  Serial.println();    
  
  delay(500);
}





