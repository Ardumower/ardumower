
/* odometry and PID test 
   requires: * Arduino Due
						 * PCB1.3    (use odo divider 2)
				     * Ardumower Mini 
 */

#include <Arduino.h>
#include "pinman.h"
#include "pid.h"


#define ticksPerRevolution 10

// ------ pins---------------------------------------
#define pinMotorEnable  37         // EN motors enable
#define pinMotorLeftPWM 5          // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31         // M1_IN2 left motor Dir pin
#define pinMotorLeftSense A1       // M1_FB  left motor current sense
#define pinMotorLeftFault 25       // M1_SF  left motor fault
                                                             
#define pinMotorRightPWM  3        // M2_IN1 right motor PWM pin
#define pinMotorRightDir 33        // M2_IN2 right motor Dir pin
#define pinMotorRightSense A0      // M2_FB  right motor current sense
#define pinMotorRightFault 27      // M2_SF  right motor fault
                                    
#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin (if using MOSFET, use this pin)
#define pinMotorMowDir 29          // M1_IN2 mower motor Dir pin (if using MOSFET, keep unconnected)
#define pinMotorMowSense A3        // M1_FB  mower motor current sense  
#define pinMotorMowFault 26        // M1_SF  mower motor fault   (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowEnable 28       // EN mower motor enable      (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowRpm A11

#define pinBuzzer 53               // Buzzer

#define pinOdometryLeft DAC0     // left odometry sensor
#define pinOdometryRight CANRX   // right odometry sensor  


// ---------------------------------------

boolean computeViaTickTime = false;
boolean pidControl = true;
int pwmMax = 127;
double speedRpmSet= 50;


int odometryLeft =0;   // left wheel counter
int odometryRight =0;  // right wheel counter

int lastOdometryLeft =0;   // left wheel counter
int lastOdometryRight =0;  // right wheel counter

static unsigned long lastOdoTriggerTimeLeft = 0;
static unsigned long lastOdoTriggerTimeRight = 0;
static unsigned long odoTriggerTimeLeft = 0;
static unsigned long odoTriggerTimeRight = 0;

double motorLeftRpmCurr = 0;
double motorRightRpmCurr = 0;

PID motorLeftPID; 
PID motorRightPID;

double motorLeftPWMCurr = 0;
double motorRightPWMCurr = 0;

unsigned long nextControlTime = 0;
unsigned long nextInfoTime = 0;
unsigned long lastMotorRpmTime = 0;

  
void OdometryRightInt(){
  if (motorRightPWMCurr >=0) odometryRight++;      
    else odometryRight--;      
  unsigned long time = millis();
  if (lastOdoTriggerTimeRight != 0) odoTriggerTimeRight = time - lastOdoTriggerTimeRight;
  lastOdoTriggerTimeRight = time;
}

void OdometryLeftInt(){
  if (motorLeftPWMCurr >=0) odometryLeft++;      
    else odometryLeft--;       
  unsigned long time = millis();
  if (lastOdoTriggerTimeLeft != 0) odoTriggerTimeLeft = time - lastOdoTriggerTimeLeft;
  lastOdoTriggerTimeLeft = time;
}



// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;
    PinMan.analogWrite(pinPWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    PinMan.analogWrite(pinPWM, ((byte)speed));
  }
}


void setup()  {
  PinMan.begin();
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(19200);    
  Serial.println("START");  
  
  // left wheel motor
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);   
  pinMode(pinMotorEnable, OUTPUT);  
  digitalWrite(pinMotorEnable, HIGH);  
  
  // right wheel motor
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT);   
  
  // odometry
  pinMode(pinOdometryLeft, INPUT_PULLUP);  
  pinMode(pinOdometryRight, INPUT_PULLUP);
  //pinMode(pinOdometryLeft, INPUT);  
  //pinMode(pinOdometryRight, INPUT);  
  
  attachInterrupt(pinOdometryLeft, OdometryLeftInt, RISING);    
  attachInterrupt(pinOdometryRight, OdometryRightInt, RISING);  
  PinMan.setDebounce(pinOdometryLeft, 100);  // reject spikes shorter than usecs on pin
  PinMan.setDebounce(pinOdometryRight, 100);  // reject spikes shorter than usecs on pin         

  motorLeftPID.Kp       = 0.2;    // motor wheel PID controller
  motorLeftPID.Ki       = 0.0;
  motorLeftPID.Kd       = 0.0;
  motorRightPID.Kp       = motorLeftPID.Kp;
  motorRightPID.Ki       = motorLeftPID.Ki;
  motorRightPID.Kd       = motorLeftPID.Kd;  
  
  motorLeftPID.reset();
  motorRightPID.reset();
}

void loop()  {    

  if (millis() > nextControlTime) {
    nextControlTime = millis() + 100;    
    float smooth = 0.0;
    float rpm;

    // ---- left motor  ----
    if (computeViaTickTime){
      if ((millis() > lastOdoTriggerTimeLeft + 100) || (odoTriggerTimeLeft == 0)) {
        rpm = 0;
      } else {    
        rpm = 60.0 / ((float)ticksPerRevolution) / (((float)odoTriggerTimeLeft)/1000.0);  
      }
    } else {      
      int ticksLeft = odometryLeft - lastOdometryLeft;
      lastOdometryLeft= odometryLeft;
      rpm = double ((( ((double)ticksLeft) / ((double)ticksPerRevolution)) / ((double)(millis() - lastMotorRpmTime))) * 60000.0);         
    }
    motorLeftRpmCurr = smooth * motorLeftRpmCurr + (1.0-smooth) * rpm;

    // ---- right motor  ----
    if (computeViaTickTime){
      if ((millis() > lastOdoTriggerTimeRight + 100) || (odoTriggerTimeRight == 0)) { 
        rpm = 0;
      } else {
        rpm = 60.0 / ((float)ticksPerRevolution) / (((float)odoTriggerTimeRight)/1000.0);  
      }      
    } else {
      int ticksRight = odometryRight - lastOdometryRight;
      lastOdometryRight= odometryRight;
      rpm = double ((( ((double)ticksRight) / ((double)ticksPerRevolution)) / ((double)(millis() - lastMotorRpmTime))) * 60000.0);                    
    }
    motorRightRpmCurr = smooth * motorRightRpmCurr + (1.0-smooth) * rpm;
    
    lastMotorRpmTime = millis();
      
    motorLeftPID.x = motorLeftRpmCurr;
    motorLeftPID.w  = speedRpmSet;
    motorLeftPID.y_min = -pwmMax;
    motorLeftPID.y_max = pwmMax;
    motorLeftPID.max_output = pwmMax;
    motorLeftPID.compute();
    motorLeftPWMCurr += motorLeftPID.y;
    if (speedRpmSet >= 0) motorLeftPWMCurr = min( max(0, (int)motorLeftPWMCurr), pwmMax);
    if (speedRpmSet < 0) motorLeftPWMCurr = max(-pwmMax, min(0, (int)motorLeftPWMCurr));

    motorRightPID.x = motorRightRpmCurr;
    motorRightPID.w  = speedRpmSet;
    motorRightPID.y_min = -pwmMax;
    motorRightPID.y_max = pwmMax;
    motorRightPID.max_output = pwmMax;
    motorRightPID.compute();
    motorRightPWMCurr += motorRightPID.y;   
    if (speedRpmSet >= 0) motorRightPWMCurr = min( max(0, (int)motorRightPWMCurr), pwmMax);
    if (speedRpmSet < 0) motorRightPWMCurr = max(-pwmMax, min(0, (int)motorRightPWMCurr));   


    if (!pidControl) {
      motorLeftPWMCurr = motorRightPWMCurr = 50;
    }
    
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, motorLeftPWMCurr);
    setMC33926(pinMotorRightDir, pinMotorRightPWM, motorRightPWMCurr);  
  }

  if (Serial.available()){
    char ch = Serial.read();
    if (ch == '0') speedRpmSet = 0;
    if (ch == '1') speedRpmSet = 50;
    if (ch == '2') speedRpmSet = -50;    
  }

  if (millis() > nextInfoTime){
    nextInfoTime = millis() + 200;
    Serial.print("odo ");    
    Serial.print(odometryLeft);    
    Serial.print(",");    
    Serial.print(odometryRight);    
    Serial.print("  rpm ");    
    Serial.print(motorLeftRpmCurr);
    Serial.print(",");        
    Serial.print(motorRightRpmCurr);    
    Serial.println();       
  }
  
  
}





