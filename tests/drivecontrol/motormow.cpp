#include "motormow.h"
#include "drivers.h"
#include "adcman.h"
#include "config.h"


MotorMowControl MotorMow;


MotorMowControl::MotorMowControl(){    
  motorMowAccel       = 0.1;  // motor mower acceleration (warning: do not set too high)
  motorMowSpeedMaxPwm   = 255;    // motor mower max PWM
  motorMowPowerMax = 75.0;     // motor mower max power (Watt)
  
  // MC33926 current:  5V / 1024 ADC counts,  525 mV per A  => 9.3 mA per ADC step  
  motorSenseScale  = 9.3;  // motor left sense scale  (mA=(ADC-zero) * scale)
  motorVoltageDC = 24.0;    

  motorPWMCurr = 0;    
  nextMotorMowTime = 0;           
  lastMotorCurrentTime = 0;
  motorSenseCurrent = 0;  
}

void MotorMowControl::setup(){
  Console.println("MotorMowControl::setup");
  // mower motor
  pinMode(pinMotorMowDir, OUTPUT); 
  pinMode(pinMotorMowPWM, OUTPUT);     
  pinMode(pinMotorMowSense, INPUT);           
  pinMode(pinMotorMowEnable, OUTPUT);
  digitalWrite(pinMotorMowEnable, HIGH);  
  pinMode(pinMotorMowFault, INPUT);
  
  ADCMan.setCapture(pinMotorMowSense, 1, true);
  setSpeedPWM(0);          
}

// call this in main loop
void MotorMowControl::run(){
  if (millis() < nextMotorMowTime) return;
  nextMotorMowTime = millis() + 1000;
  readCurrent();  
  checkMotorFault();  
}

void MotorMowControl::setSpeedPWM(int pwm){
  if (motorStalled) {
    if (pwm != 0) return;
  }
  if (pwm == 0) motorSensePower = 0;  

  setMC33926(pinMotorMowDir, pinMotorMowPWM, pwm);
}


void MotorMowControl::print(){
    Serial.print("  pwm:");    
    Serial.print(motorPWMCurr, 0);
    Serial.print(",");
    Serial.print("  mA:");    
    Serial.print(motorSenseCurrent, 0);
    Serial.print("  P:");    
    Serial.print(motorSensePower, 1);
}


void MotorMowControl::stopImmediately(){
  setSpeedPWM(0);  
}


bool MotorMowControl::hasStopped(){
  return (motorPWMCurr == 0);
}    

void MotorMowControl::resetStalled(){
  motorStalled = false;
  Serial.println("STALL RESET");
}


void MotorMowControl::checkMotorFault(){
  if (digitalRead(pinMotorMowFault)==LOW){
    motorError = true;
  }
}


// read motor current
void MotorMowControl::readCurrent(){
    unsigned long TaC = millis() - lastMotorCurrentTime;    // sampling time in millis
    lastMotorCurrentTime = millis();
    if (TaC > 500) TaC = 1;   
    double TaS = ((double)TaC) / 1000.0;

    // read current - NOTE: MC33926 datasheets says: accuracy is better than 20% from 0.5 to 6.0 A
    int motorSenseADC = ADCMan.read(pinMotorMowSense);                              
    
    // compute motor current (mA)
    //double smooth = 0.0;    
    double smooth = 0.5;    
    motorSenseCurrent = motorSenseCurrent * smooth + ((double)motorSenseADC) * motorSenseScale * (1.0-smooth);    
                
    // compute motor output power (W) by calculating battery voltage, pwm duty cycle and motor current
    // P_output = U_Battery * pwmDuty * I_Motor     
    smooth = 0.9;        
    motorSensePower = motorSensePower * smooth + (1.0-smooth) * (motorSenseCurrent * motorVoltageDC * ((double)abs(motorPWMCurr)/255.0)  /1000);   
        
    if (!motorStalled){
       if ( (abs(motorPWMCurr) > 0) && (motorSensePower > motorMowPowerMax) ) {
         print();         
         Serial.print("  MOW STALL");         
         Serial.println();                  
         motorStalled = true;         
         stopImmediately();                  
       }            
    }
}



// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void MotorMowControl::setMC33926(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;
    analogWrite(pinPWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    analogWrite(pinPWM, ((byte)speed));
  }
}






