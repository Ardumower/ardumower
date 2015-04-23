
// MC33926 stress-test
// 
// WARNING: FOR DEVELOPERS ONLY!!
// THIS TEST WILL DAMAGE YOUR MOTOR DRIVER IF NOT USED CORRECTLY - USE CAREFULLY! YOU HAVE BEEN WARNED!


#define MAX_SPEED 255

// ALWAYS check below that you are using the right test!
int test = 2;

int speed = MAX_SPEED;

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
unsigned long nextMotorInfoTime = 0;
unsigned long lastSetMotorSpeedTime = 0;
int state = 0;


// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed) {
  if (speed < 0) {
    digitalWrite(pinDir, HIGH) ;
    analogWrite(pinPWM, 255 - ((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    analogWrite(pinPWM, ((byte)speed));
  }
}

// sets wheel motor actuators
void setMotorSpeed(int pwmLeft, int pwmRight, boolean useAccel) {
  float TaC = ((float) (millis() - lastSetMotorSpeedTime)) / 1000.0;    // sampling time in seconds
  if (TaC > 1.0) TaC = 0;
  lastSetMotorSpeedTime = millis();
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
  motorLeftEMF = max(0, motorLeftEMF -    motorLeftEMF * fraction * TaC    +    abs(motorLeftPWM) * TaC );
  setMC33926(pinMotorLeftDir, pinMotorLeftPWM, motorLeftPWM);
}


void setup()
{
  Serial.begin(115200);

  // left wheel motor
  pinMode(pinMotorEnable, OUTPUT);
  digitalWrite(pinMotorEnable, HIGH);
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);
  pinMode(pinMotorLeftSense, INPUT);
  pinMode(pinMotorLeftFault, INPUT);

  //  Serial.println("SETUP");
  startTime = 0;
  randomSeed(analogRead(A7) + analogRead(A0) + analogRead(A1));
}


void loop()
{
  if (test == 0) {
    // 5 sec FORWARD, 10 sec STOP
    setMotorSpeed(MAX_SPEED, MAX_SPEED, false);
    delay(5000);
    setMotorSpeed(0, 0, false);
    delay(10000);
  }

  else if (test == 1){
    // 2 sec FORWARD, 2 sec REVERSE
    setMotorSpeed(speed, speed, false);
    if (millis() > startTime + 2000) {
      startTime = millis();      
      speed *= -1;
      state = random(0, 2);
    }
  } 

  else if (test == 2){
    // random FORWARD/REVERSE at random SPEED for random TIME
    setMotorSpeed(speed, speed, false);
    if (random(0,4000) == 0){
      startTime = millis();
      speed = random(-MAX_SPEED,MAX_SPEED);
      state = random(0, 2);
    }    
  }    
  
  else if (test == 3){
    // 5 sec FORWARD, 5 sec REVERSE, 10 sec STOP - 
    // WARNING: WITHOUT PROTECTION !! THIS MAY KILL YOUR MOTOR DRIVER!
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, MAX_SPEED);    
    delay(5000);
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, -MAX_SPEED);    
    delay(5000);
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, 0);    
    delay(10000);
  }
    
  if (millis() >= nextMotorInfoTime) {
     nextMotorInfoTime = millis() + 40;
      Serial.print(motorLeftEMF);
      Serial.print(",");
      Serial.print(speed);
      Serial.print(",");
      Serial.print(motorLeftPWM);
      Serial.println();  
  }

}


