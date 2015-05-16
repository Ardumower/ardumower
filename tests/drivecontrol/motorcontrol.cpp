#include "motorcontrol.h"

MotorControl MotorCtrl;
volatile static boolean odometryLeftLastState;
volatile static boolean odometryRightLastState;       

volatile static unsigned long odometryLeftLastHighTime = 0;
volatile static unsigned long odometryRightLastHighTime = 0;
volatile static unsigned long odometryLeftTickTime = 0;
volatile static unsigned long odometryRightTickTime = 0;


// odometry interrupt handler
ISR(PCINT2_vect, ISR_NOBLOCK){
//  ISR(PCINT2_vect){
  unsigned long timeMicros = micros();
  boolean odometryLeftState = digitalRead(pinOdometryLeft);
  boolean odometryRightState = digitalRead(pinOdometryRight);      
  if (odometryLeftState != odometryLeftLastState){    
    if (odometryLeftState){ // pin1 makes LOW->HIGH transition
      odometryLeftTickTime = timeMicros - odometryLeftLastHighTime;
      if (MotorCtrl.motorLeftPWMCurr >=0) MotorCtrl.odometryLeft ++; else MotorCtrl.odometryLeft --;           
      odometryLeftLastHighTime = timeMicros;      
    } else {
      //odometryLeftLowTime = timeMicros;
    }
    odometryLeftLastState = odometryLeftState;
  } 
  if (odometryRightState != odometryRightLastState){
    if (odometryRightState){ // pin1 makes LOW->HIGH transition
      odometryRightTickTime = timeMicros - odometryRightLastHighTime;
      if (MotorCtrl.motorRightPWMCurr >=0) MotorCtrl.odometryRight ++; else MotorCtrl.odometryRight --;    
      odometryRightLastHighTime = timeMicros;
    } else {
      //odometryRightLowTime = timeMicros;
    }
    odometryRightLastState = odometryRightState;
  }  
}


MotorControl::MotorControl(){
  motorSpeedMaxRpm = 18;
  motorSpeedMaxPwm = 255;
    
/*  motorLeftPID.Kp       = 0.87;    // motor wheel PID controller
  motorLeftPID.Ki       = 0.29;
  motorLeftPID.Kd       = 0.25;  */
  
  motorLeftPID.Kp       = 0.87;    // motor wheel PID controller
  motorLeftPID.Ki       = 0.29;
  motorLeftPID.Kd       = 0.25;  
    
  odometryTicksPerRevolution = 20;   // encoder ticks per one full resolution
  odometryTicksPerCm = 0.5;    // encoder ticks per cm
  odometryWheelBaseCm = 14;    // wheel-to-wheel distance (cm)    
      
  enableSpeedControl = true;
  motorLeftPWMCurr = motorRightPWMCurr = 0;
  lastOdometryTime = lastMotorControlTime = 0;  
  odometryLeftTicksZeroCounter = odometryRightTicksZeroCounter = 0;
  
  TCCR3B = (TCCR3B & 0xF8) | 0x02;    // set PWM frequency 3.9 Khz (pin2,3,5)    
  
  pinMode(pinMotorEnable, OUTPUT);  
  digitalWrite(pinMotorEnable, HIGH);
  
  // left wheel motor    
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);   
  pinMode(pinMotorLeftSense, INPUT);     
  pinMode(pinMotorLeftFault, INPUT);    
  
  // right wheel motor
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT); 
  pinMode(pinMotorRightSense, INPUT);       
  pinMode(pinMotorRightFault, INPUT);  
  
  // odometry
  pinMode(pinOdometryLeft, INPUT_PULLUP);  
  pinMode(pinOdometryRight, INPUT_PULLUP);    
  
  // odometry
  PCICR |= (1<<PCIE2);
  PCMSK2 |= (1<<PCINT20);
  PCMSK2 |= (1<<PCINT22);            

  //setSpeedPWM(0, 80);
//  setSpeedPWM(127, 127);  
   setSpeedPWM(0, 0);
}


// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void MotorControl::setMC33926(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;
    analogWrite(pinPWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    analogWrite(pinPWM, ((byte)speed));
  }
}

void MotorControl::run(){
  readOdometry();
  if (enableSpeedControl) speedControl();
}  

void MotorControl::readOdometry(){
  unsigned long TaC = millis() - lastOdometryTime;    // sampling time in millis
  lastOdometryTime = millis();  
  if (TaC > 1000) TaC = 1;      
  static int lastOdoLeft = 0;
  static int lastOdoRight = 0;
  int odoLeft = odometryLeft;
  int odoRight = odometryRight;
  unsigned long leftTime = odometryLeftTickTime;
  unsigned long rightTime = odometryRightTickTime;  
  int ticksLeft = odoLeft - lastOdoLeft;
  int ticksRight = odoRight - lastOdoRight;
  lastOdoLeft = odoLeft;
  lastOdoRight = odoRight;    
  double left_cm = ((double)ticksLeft) / ((double)odometryTicksPerCm);
  double right_cm = ((double)ticksRight) / ((double)odometryTicksPerCm);  
  double avg_cm  = (left_cm + right_cm) / 2.0;
  double wheel_theta = (left_cm - right_cm) / ((double)odometryWheelBaseCm);
  odometryTheta += wheel_theta; 

  float smooth = 0.9;  
  // 1 rpm = 20 ticks per minute, micros per rpm = 6000*1000 micros / 20 ticks 
  if (ticksLeft != 0) {
    motorLeftRpmCurr  = motorLeftRpmCurr * smooth + (1.0-smooth) *  6000.0*1000.0 / ((double)odometryTicksPerRevolution) / ((double)leftTime);  
    odometryLeftTicksZeroCounter = 0;
  } else {
    odometryLeftTicksZeroCounter++;
    if (odometryLeftTicksZeroCounter > 10) motorLeftRpmCurr = 0;     // ensures rpm gets zero
  }
  if (motorLeftPWMCurr < 0) motorLeftRpmCurr *= -1;

  if (ticksRight != 0) {
    motorRightRpmCurr  = motorRightRpmCurr * smooth + (1.0-smooth) * 6000.0*1000.0 / ((double)odometryTicksPerRevolution) / ((double)rightTime);  
    odometryRightTicksZeroCounter = 0;
  } else {
    odometryRightTicksZeroCounter++;
    if (odometryRightTicksZeroCounter > 10) motorRightRpmCurr = 0;   // ensures rpm gets zero 
  }
  if (motorRightPWMCurr < 0) motorRightRpmCurr *= -1;  
   
 //motorLeftRpmCurr  = double ((( ((double)ticksLeft) / ((double)odometryTicksPerRevolution)) / ((double)(TaC))) * 60000.0); 
 //motorRightRpmCurr = double ((( ((double)ticksRight) / ((double)odometryTicksPerRevolution)) / ((double)(TaC))) * 60000.0);                    
}


void MotorControl::speedControl(){  
  unsigned long TaC = millis() - lastMotorControlTime;    // sampling time in millis
  lastMotorControlTime = millis(); 
  if (TaC > 1000) TaC = 1;     
  //float TaS = ((double)TaC) / 1000.0;
  
  static float leftRightCompensation = 0;
  //leftRightCompensation += (motorLeftRpmCurr - motorRightRpmCurr)* 2;
  
  motorLeftPID.x = motorLeftRpmCurr;                 // CURRENT
  motorLeftPID.w = motorLeftSpeedRpmSet;               // SET
  motorLeftPID.y_min = -motorSpeedMaxPwm;        // CONTROL-MIN
  motorLeftPID.y_max = motorSpeedMaxPwm;     // CONTROL-MAX
  motorLeftPID.max_output = motorSpeedMaxPwm;    // LIMIT
  motorLeftPID.compute();
  int leftSpeed = motorLeftPWMCurr + motorLeftPID.y - leftRightCompensation;    
  if (motorLeftSpeedRpmSet >= 0) leftSpeed = min( max(0, leftSpeed), motorSpeedMaxPwm);
  if (motorLeftSpeedRpmSet < 0) leftSpeed = max(-motorSpeedMaxPwm, min(0, leftSpeed));
  
  motorRightPID.Kp = motorLeftPID.Kp;
  motorRightPID.Ki = motorLeftPID.Ki;
  motorRightPID.Kd = motorLeftPID.Kd;          
  motorRightPID.x = motorRightRpmCurr;               // IST
  motorRightPID.w = motorRightSpeedRpmSet;             // SOLL
  motorRightPID.y_min = -motorSpeedMaxPwm;       // Regel-MIN
  motorRightPID.y_max = motorSpeedMaxPwm;        // Regel-MAX
  motorRightPID.max_output = motorSpeedMaxPwm;   // Begrenzung
  motorRightPID.compute();            
  int rightSpeed = motorRightPWMCurr + motorRightPID.y + leftRightCompensation;    
  if (motorRightSpeedRpmSet >= 0) rightSpeed = min( max(0, rightSpeed), motorSpeedMaxPwm);
  if (motorRightSpeedRpmSet < 0) rightSpeed = max(-motorSpeedMaxPwm, min(0, rightSpeed));
  
  if ( (motorLeftPID.x  == 0) && (motorLeftPID.w  == 0) ) leftSpeed = 0; // ensures PWM is really zero 
  if ( (motorRightPID.x == 0) && (motorRightPID.w == 0) ) rightSpeed = 0; // ensures PWM is really zero     
  setSpeedPWM( leftSpeed, rightSpeed );  
}

void MotorControl::setSpeedPWM(int leftPWM, int rightPWM){
  motorLeftPWMCurr = leftPWM;
  motorRightPWMCurr = rightPWM;
  setMC33926(pinMotorLeftDir,  pinMotorLeftPWM,  leftPWM);
  setMC33926(pinMotorRightDir, pinMotorRightPWM, rightPWM);    
}

void MotorControl::setSpeedRpm(int leftRpm, int rightRpm){
   motorLeftSpeedRpmSet = leftRpm;
   motorRightSpeedRpmSet = rightRpm;
   motorLeftSpeedRpmSet = max(-motorSpeedMaxRpm, min(motorSpeedMaxRpm, motorLeftSpeedRpmSet));
   motorRightSpeedRpmSet = max(-motorSpeedMaxRpm, min(motorSpeedMaxRpm, motorRightSpeedRpmSet));   
}



