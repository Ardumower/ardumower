
// measure odometry frequency (Arduino Due / Adafruit Grand Central M4)


#define pinBuzzer 53               // Buzzer
#if defined(_SAM3XA_)              // Arduino Due
  #define CONSOLE Serial
  #define pinOdometryLeft DAC0     // left odometry sensor
  #define pinOdometryLeft2 DAC1    // left odometry sensor (optional two-wire)
  #define pinOdometryRight CANRX   // right odometry sensor  
  #define pinOdometryRight2 CANTX  // right odometry sensor (optional two-wire)  
#else                              // Adafruit Grand Central M4 
  #define CONSOLE Serial
  #define pinOdometryLeft A12      // left odometry sensor
  #define pinOdometryLeft2 A13     // left odometry sensor (optional two-wire)
  #define pinOdometryRight A14     // right odometry sensor 
  #define pinOdometryRight2 A15    // right odometry sensor (optional two-wire)  
#endif


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



enum MotorSelect {MOTOR_LEFT, MOTOR_RIGHT, MOTOR_MOW} ;
typedef enum MotorSelect MotorSelect;


int  pwmMax = 255;
int  pwmMaxMow = 255;

volatile unsigned long odoTicksLeft = 0;
volatile unsigned long odoTicksRight = 0;

bool motorRightSwapDir = false;
bool motorLeftSwapDir = false;


unsigned long nextMeasureTime = 0;


// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed) {
  //DEBUGLN(speed);
  if (speed < 0) {
    digitalWrite(pinDir, HIGH) ;
    analogWrite(pinPWM, 255 - ((byte)abs(speed)));
  } else {
    digitalWrite(pinDir, LOW) ;
    analogWrite(pinPWM, ((byte)speed));
  }
}
        

void speedPWM ( MotorSelect motor, int speedPWM )
{
  if (motor == MOTOR_MOW) {
    if (speedPWM > pwmMaxMow) speedPWM = pwmMaxMow;
    else if (speedPWM < -pwmMaxMow) speedPWM = -pwmMaxMow;
  } else {
    if (speedPWM > pwmMax) speedPWM = pwmMax;
    else if (speedPWM < -pwmMax) speedPWM = -pwmMax;
  }
  switch (motor) {
    case MOTOR_LEFT:
      if (motorLeftSwapDir) speedPWM *= -1;
      setMC33926(pinMotorLeftDir, pinMotorLeftPWM, speedPWM);
      break;
    case MOTOR_RIGHT:
      if (motorRightSwapDir) speedPWM *= -1;
      setMC33926(pinMotorRightDir, pinMotorRightPWM, speedPWM);
      break;
    case MOTOR_MOW:        
      setMC33926(pinMotorMowDir, pinMotorMowPWM, speedPWM);
      break;
  }
}


void OdometryLeftInt(){			
  odoTicksLeft++;  
}

void OdometryRightInt(){			
  odoTicksRight++;  
}




void setup(){
  digitalWrite(pinBuzzer, LOW);

  pinMode(pinMotorEnable, OUTPUT);
  digitalWrite(pinMotorEnable, HIGH);
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);
  pinMode(pinMotorLeftSense, INPUT);
  pinMode(pinMotorLeftFault, INPUT);

  // right wheel motor
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT);
  pinMode(pinMotorRightSense, INPUT);
  pinMode(pinMotorRightFault, INPUT);

  // mower motor
  pinMode(pinMotorMowDir, OUTPUT);
  pinMode(pinMotorMowPWM, OUTPUT);
  pinMode(pinMotorMowSense, INPUT);
  //pinMode(pinMotorMowRpm, INPUT);
  pinMode(pinMotorMowEnable, OUTPUT);
  digitalWrite(pinMotorMowEnable, HIGH);
  pinMode(pinMotorMowFault, INPUT);

  // odometry
  //pinMode(pinOdometryLeft, INPUT_PULLUP);
  //pinMode(pinOdometryLeft2, INPUT_PULLUP);
  //pinMode(pinOdometryRight, INPUT_PULLUP);
  //pinMode(pinOdometryRight2, INPUT_PULLUP);
	  
  // enable interrupts
  attachInterrupt(pinOdometryLeft, OdometryLeftInt, RISING);  
  attachInterrupt(pinOdometryRight, OdometryRightInt, RISING);  
  
  CONSOLE.begin(115200);
  CONSOLE.println("START");
  
  speedPWM (MOTOR_LEFT,  80);
  speedPWM (MOTOR_RIGHT,  80);
}


void loop(){
  if (millis() > nextMeasureTime){
    nextMeasureTime = millis() + 1000;
    CONSOLE.print(odoTicksLeft);
    CONSOLE.print(",");
    CONSOLE.println(odoTicksRight);
    odoTicksLeft = 0;
    odoTicksRight = 0;
  }
}


