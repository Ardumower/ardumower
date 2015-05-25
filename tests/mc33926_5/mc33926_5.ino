// MC33926 mower motor blocking test 
// current versus fault measurement (CSV output for Excel etc.)

#include "RunningMedian.h"
#include "TimerThree.h"

#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin (if using MOSFET, use this pin)
#define pinMotorMowDir 29          // M1_IN2 mower motor Dir pin (if using MOSFET, keep unconnected)
#define pinMotorMowSense A3        // M1_FB  mower motor current sense  
#define pinMotorMowFault 26        // M1_SF  mower motor fault   (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowEnable 28       // EN mower motor enable      (if using MOSFET/L298N, keep unconnected)


RunningMedian<int,50> measurements;


// MC33926 motor driver
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setMC33926(int pinDir, int pinPWM, int speed) {
  //speed *= 4;
  if (speed < 0) {
    digitalWrite(pinDir, HIGH) ;
    analogWrite(pinPWM, 255 - ((byte)abs(speed)));
    //Timer3.setPwmDuty(pinPWM, 1023 - abs(speed));
  } else {
    digitalWrite(pinDir, LOW) ;
    analogWrite(pinPWM, ((byte)speed));
    //Timer3.setPwmDuty(pinPWM, speed);
  }
}


void setup()
{
  Serial.begin(19200);
   
  // mower motor
  pinMode(pinMotorMowDir, OUTPUT); 
  pinMode(pinMotorMowPWM, OUTPUT);     
  pinMode(pinMotorMowSense, INPUT);     
  pinMode(pinMotorMowEnable, OUTPUT);
  digitalWrite(pinMotorMowEnable, HIGH);  
  pinMode(pinMotorMowFault, INPUT);      
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
    
  // http://sobisource.com/arduino-mega-pwm-pin-and-frequency-timer-control/
  // http://www.atmel.com/images/doc2549.pdf
  TCCR3B = (TCCR3B & 0xF8) | 0x02;    // set PWM frequency 3.9 Khz (pin2,3,5)   
  
  //Timer3.initialize(50);
  //Timer3.pwm(pinMotorLeftPWM, 511);                  
  
  Serial.println("SETUP");
  for (int i=5; i >= 0; i--){    
    Serial.println(i);    
    delay(1000);
  }
}


void loop()
{
  int speed = 255;
  Serial.println("time,pwm,sense,fault");
  unsigned long lastticks = 0;
  unsigned long overCurrentStartTime = 0;
  for (int step=0; step <= 1000; step++){    
    setMC33926(pinMotorMowDir, pinMotorMowPWM, speed);    
    // 5V / 1024 ADC counts,  525 mV per A  => 107.52 counts per A
    int sense = ((float)analogRead(pinMotorMowSense)) / 107.52 * 1000.0;   
    int fault = digitalRead(pinMotorMowFault);          
    unsigned long time = millis();    
    Serial.print(time/1000.0);    
    Serial.print(",");    
    Serial.print(speed);
    Serial.print(",");    
    Serial.print(sense);
    Serial.print(",");    
    Serial.print(fault);
    Serial.println();        
    if (sense > 5000) {
      if (millis() - overCurrentStartTime > 500){
        setMC33926(pinMotorMowDir, pinMotorMowPWM, 0);            
        delay(5000);
        overCurrentStartTime = millis();
      }
    } else overCurrentStartTime = millis();
    //delay(5);
  }   
  setMC33926(pinMotorMowDir, pinMotorMowPWM, 0);
  while (true);
}



