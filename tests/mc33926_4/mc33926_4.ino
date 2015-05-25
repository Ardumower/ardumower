// MC33926 pwm versus current measurement (CSV output for Excel etc.)

#include "RunningMedian.h"
#include "TimerThree.h"

#define pinMotorEnable  37         // EN motors enable
#define pinMotorLeftPWM 5           // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31          // M1_IN2 left motor Dir pin
#define pinMotorLeftSense A1       // M1_FB  left motor current sense
#define pinMotorLeftFault 25       // M1_SF  left motor fault
#define pinOdometryLeft A12      // left odometry sensor


RunningMedian<int,50> measurements;
unsigned long ticks = 0;


ISR(PCINT2_vect){
  if (digitalRead(pinOdometryLeft)) ticks++;
}



// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed) {
  speed *= 4;
  if (speed < 0) {
    digitalWrite(pinDir, HIGH) ;
    //analogWrite(pinPWM, 255 - ((byte)abs(speed)));
    Timer3.setPwmDuty(pinPWM, 1023 - abs(speed));
  } else {
    digitalWrite(pinDir, LOW) ;
    //analogWrite(pinPWM, ((byte)speed));
    Timer3.setPwmDuty(pinPWM, speed);
  }
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
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  pinMode(pinOdometryLeft, INPUT_PULLUP);
  // http://wiki.ardumower.de/images/a/ad/Ardunio_mega_pinout.png
  PCICR |= (1<<PCIE2);
  PCMSK2 |= (1<<PCINT20);
  
  // http://sobisource.com/arduino-mega-pwm-pin-and-frequency-timer-control/
  // http://www.atmel.com/images/doc2549.pdf
  //TCCR3B = (TCCR3B & 0xF8) | 0x02;    // set PWM frequency 3.9 Khz (pin2,3,5)   
  
  Timer3.initialize(50);
  Timer3.pwm(pinMotorLeftPWM, 511);                  
  
  Serial.println("SETUP");
}


void loop()
{
  Serial.println("pwm,ticks,sense");
  unsigned long lastticks = 0;
  for (int speed=0; speed <= 255; speed += 5){    
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, speed);
    delay(500);
    lastticks = ticks;         
    delay(1000);        
    unsigned long stopticks = ticks;            
    unsigned long stopTime = millis() + 1000;        
    for (int i=0; i < 10; i++){
      //while (millis() < stopTime){
      int sense = 0;
      sense = analogRead(pinMotorLeftSense);
      //measurements.clear();
      /*for (int i=0; i < 100; i++){
        sense = analogRead(pinMotorLeftSense);
       measurements.add(sense);
      }*/
      //int fault = digitalRead(pinMotorLeftFault);      
      Serial.print(speed);
      Serial.print(",");    
      Serial.print(stopticks-lastticks);
      Serial.print(",");    
      //float curr;
      //measurements.getAverage(curr);
      Serial.print(sense);
      //Serial.print(",");    
      //Serial.print(fault);
      Serial.println();        
    }    
  }   
  setMC33926(pinMotorLeftDir, pinMotorLeftPWM, 0);
  while (true);
}



