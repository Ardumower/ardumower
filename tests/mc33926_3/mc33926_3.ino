
int speed = 0;

#define MAX_SPEED 127

#define pinMotorEnable  37         // EN motors enable
#define pinMotorLeftPWM 5           // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 6          // M1_IN2 left motor Dir pin
//#define pinMotorLeftPWM 3           // M1_IN1 left motor PWM pin
//#define pinMotorLeftDir 33          // M1_IN2 left motor Dir pin
#define pinMotorLeftSense A1       // M1_FB  left motor current sense
#define pinMotorLeftFault 25       // M1_SF  left motor fault

float motorLeftPWM = 0;
float motorLeftEMF = 0;
float motorRightPWM = 0;

unsigned long startTime;
unsigned long lastSetMotorSpeedControlTime = 0;
int state = 0;


// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed){
  if (speed < 0){
    digitalWrite(pinDir, HIGH) ;
    analogWrite(pinPWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    analogWrite(pinPWM, ((byte)speed));
  }
}

// sets wheel motor actuators
void setMotorSpeed(int pwmLeft, int pwmRight, boolean useAccel){
  float TaC = ((float) (millis() - lastSetMotorSpeedControlTime)) / 1000.0;    // sampling time in seconds
  if (TaC > 1.0) TaC = 0;    
  lastSetMotorSpeedControlTime = millis();  
  if ( ((pwmLeft < 0) && (motorLeftPWM >= 0)) ||
       ((pwmLeft > 0) && (motorLeftPWM <= 0)) ) {
    // changing direction should take place          
    if ( motorLeftEMF > 0.1) {
      // reduce motor rotation (will reduce EMF)       
      pwmLeft = motorLeftPWM - (motorLeftPWM * 2.0 * TaC); // reduce by 200% in one second
    } 
  }
  motorLeftPWM = pwmLeft;
  motorRightPWM = pwmRight;  
  // compute electromotive force (sort of PWM low pass filter)
  // added force:        pwm * sampling time
  // force reduced by:   fraction * sampling time
  float fraction = 5.0;
  motorLeftEMF = max(0, motorLeftEMF -    motorLeftEMF*fraction* TaC    +    abs(motorLeftPWM)*TaC );   
  Serial.println(motorLeftEMF);
  setMC33926(pinMotorLeftDir, pinMotorLeftPWM, motorLeftPWM);    
}


void setup()
{
  Serial.begin(19200);  

  // left wheel motor
  pinMode(pinMotorEnable, OUTPUT);  
  digitalWrite(pinMotorEnable, HIGH);
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);   
  pinMode(pinMotorLeftSense, INPUT);     
  pinMode(pinMotorLeftFault, INPUT);    
  
  Serial.println("SETUP");  
  startTime = 0;
  randomSeed(analogRead(A7)+analogRead(A0)+analogRead(A1));
}


void loop()
{  
  if (state == 0){
    //Serial.println("FORW");               
    setMotorSpeed(speed, speed, false);
    //if (millis() > startTime + 2000) {    
    if (random(0,255) == 0){
      startTime = millis();
      speed = random(0,MAX_SPEED);
      state = random(0,2);
    }
  }  
    
  if (state == 1){
    //Serial.println("REV");            
    //setMotorSpeed(0, 0, false);
    setMotorSpeed(-speed, -speed, false); 
    //    if (millis() > startTime + 2000) {
    if (random(0,255) == 0){      
      startTime = millis();
      speed = random(0,MAX_SPEED);
      state = random(0,2);
    }
  } 
}


