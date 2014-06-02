/*
  Perimeter sender - using 'pseudonoise4_pw' signal  (for details see   http://grauonline.de/alexwww/ardumower/filter/filter.html  )
  
  for schematics, see bottom of this page:  http://www.ardumower.de/index.php/de/anleitungen/2013-11-23-19-50-19/induktion                                                                                 
                                                                                
 */

#include "TimerOne.h"

#define pinIN1       9  // M1_IN1
#define pinIN2       8  // M1_IN2
#define pinPWM      11  // M1_PWM / nD2
#define pinFault    12  // M1_nSF
#define pinFeedback A0  // M1_FB
#define pinEnable    3  // EN

#define  pinLED 13

volatile int step = 0;
volatile byte state = 0;
volatile byte wait = 1;


// must be multiple of 2 !
char pncode[] = { 1,1,-1,-1,-1,1,-1,-1,1,1,-1, 1,-1,1,1,-1 };


void timerCallback(){       
  wait--;
  if (wait == 0){  
    //if (step == 0) state = 0;    
    state = ~state;
    if (state) {      
      digitalWrite(pinIN1, LOW);                           
      digitalWrite(pinIN2, HIGH);                                 
      //digitalWrite(pinEnable, HIGH);                           
      //delayMicroseconds(200);      
    } else {      
      digitalWrite(pinIN1, HIGH);                           
      digitalWrite(pinIN2, LOW);                                 
      //digitalWrite(pinEnable, LOW);                           
      //delayMicroseconds(200);
      //digitalWrite(pinEnable, LOW);                           
    }    
    if (pncode[step] == 1) {
      wait = 2;    
    } else {
      wait = 1;    
    } 
    step ++;    
    if (step == sizeof pncode) {      
      step = 0;      
    }
  } else {
    //digitalWrite(pinIN1, HIGH);                           
    //digitalWrite(pinIN2, LOW);                               
  }  
}

  
void setup() {  
  pinMode(pinIN1, OUTPUT);    
  pinMode(pinIN2, OUTPUT);  
  pinMode(pinEnable, OUTPUT);
  pinMode(pinPWM, OUTPUT);  
  pinMode(pinFeedback, INPUT);    
  pinMode(pinFault, INPUT);      
  
  digitalWrite(pinEnable, HIGH);
    
  //int T = 1000.0*1000.0/(7800*2);
  // sample rate 19230,76923076923
  int T = 1000.0*1000.0/(19230.76923076923/2.0);
  Serial.begin(19200);
  Serial.println("START");
  Serial.print("T=");
  Serial.println(T);    
  Serial.print("f=");
  Serial.println(1000.0*1000.0/T);    
  Timer1.initialize(T);         // initialize timer1, and set 128µsecond period (7812Hz)    
  //Timer1.pwm(pinPWM, 256);  
  Timer1.attachInterrupt(timerCallback);  
  //digitalWrite(pinIN1, HIGH);
  //digitalWrite(pinIN2, LOW);  
  //tone(pinPWM, 7800);

  // http://playground.arduino.cc/Main/TimerPWMCheatsheet
  // timer 2 pwm freq 31 khz  
  //cli();
  TCCR2B = TCCR2B & 0b11111000 | 0x01;
  //TIMSK2 |= (1 << OCIE2A);     // Enable Output Compare Match A Interrupt  
  //OCR2A = 255;                 // Set compared value
  //sei();
}

double minduty = 0.05; // 5%
double maxduty = 1.0; // 100%
double duty = 0.1;    // 10%
int dutyPWM = 0;
double I = 0; // ampere
double Ipeak = 0; // ampere
int faults = 0;

unsigned long nextTimeControl = 0;
unsigned long nextTimeInfo = 0;

// Interrupt service run when Timer/Counter2 reaches OCR2A
//ISR(TIMER2_COMPA_vect) {
//  if (digitalRead(pinFault) == LOW) fault = true; 
  //if (digitalRead(pinPWM) == HIGH) fault = true; 
  //fault = true;

void fault(){
  Serial.println("MC_FAULT");
  for (int i=0; i < 10; i++){
    digitalWrite(pinLED, HIGH);
    delay(50);
    digitalWrite(pinLED, LOW);
    delay(50);
  }  
  faults++;                          
}

void loop(){    
  if (millis() >= nextTimeControl){                
    nextTimeControl = millis() + 100;
    // far away: fast control
    if (I > 0.3) duty = max(minduty, duty - 0.1);  
    if (I > 0.2) duty = max(minduty, duty - 0.01);  
      else if (I < 0.1) duty = min(maxduty, duty + 0.01);
      // nearby: slow control
      else if (I < 0.12) duty = min(maxduty, duty + 0.001);
      else if (I > 0.16) duty = max(minduty, duty - 0.001);          
    dutyPWM = (int) (duty / 1.0 * 255.0);
    //analogWrite(pinPWM, 255);
    analogWrite(pinPWM, dutyPWM);
    if ( (dutyPWM == 255) && (digitalRead(pinFault) == LOW) ) {
      duty = 0;
      analogWrite(pinPWM, duty);
      fault();    
    }    
  }

  if (millis() >= nextTimeInfo){                
    nextTimeInfo = millis() + 500;    
    Serial.print("time=");
    Serial.print(millis()/1000);    
    Serial.print("\tIpeak=");    
    Serial.print(Ipeak);
    Serial.print("\tI=");
    Serial.print(I);
    Serial.print("\tduty=");
    Serial.print(duty);
    Serial.print("\tdutyPWM=");        
    Serial.print((int)dutyPWM);        
    Serial.print("\tduty/I=");
    double dutyI = duty / I;
    Serial.print(dutyI);    
    Serial.print("\tfaults=");
    Serial.println(faults);        
  }
  
  delay(10);
    
  // 525 mV per amp
  double curr = ((double)analogRead(pinFeedback)) / 1023.0 * 5.0 / 0.525;  
  //   currPeak = max(0, currPeak - 0.001);
  Ipeak = max(Ipeak, I);  
  I = 0.9 * I + 0.1 * curr;
  
}







