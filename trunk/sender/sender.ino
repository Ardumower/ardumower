/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
  Perimeter sender v2   (for details see   http://wiki.ardumower.de/index.php?title=Perimeter_wire  )  
 
 */

#include "TimerOne.h"
#include "EEPROM.h"
#include "RunningMedian.h"

// MC33926 motor driver
#define pinIN1       9  // M1_IN1         (if using old L298N driver, connect this pin to L298N-IN1)
#define pinIN2       8  // M1_IN2
#define pinPWM      11  // M1_PWM / nD2   (if using old L298N driver, connect this pin to L298N-IN2)
#define pinFault    12  // M1_nSF
#define pinFeedback A0  // M1_FB
#define pinEnable    3  // EN

#define pinPot      A1  // 100k potentiometer (current control)   
#define USE_POT      1  // use potentiometer for current control?

#define pinChargeCurrent     A2     // ACS712-05 current sensor OUT
#define USE_CHG_CURRENT       1     // use charging current sensor?
#define CHG_CURRENT_MIN   0.009     // must be at least 9 mA for charging detection

#define PERI_CURRENT_MIN    0.1     // must be at least 100 mA for perimeter detection

#define  pinLED 13  // ON: perimeter closed, OFF: perimeter open, BLINK: robot is charging


// Ardumower code version - the revision keyword will be updated automatically by SVN
// http://svnbook.red-bean.com/en/1.7/svn.advanced.props.special.keywords.html
#define VER "$Rev$"

// --------------------------------------

volatile int step = 0;
volatile byte state = 0;
volatile byte wait = 1;


double duty = 0.1;    // 10%
int dutyPWM = 0;
double chargeCurrent = 0;
double periCurrent = 0; 
int faults = 0;
boolean isCharging = false;
boolean stateLED = false;
unsigned int chargeADCZero = 511;
RunningMedian<unsigned int,16> periCurrentMeasurements;
RunningMedian<unsigned int,96> chargeCurrentMeasurements;

unsigned long nextTimeControl = 0;
unsigned long nextTimeInfo = 0;
unsigned long nextTimeToggleLED = 0;


// must be multiple of 2 !
// http://grauonline.de/alexwww/ardumower/filter/filter.html    
// "pseudonoise4_pw" signal
int8_t pncode[] = { 1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1 };
// "pseudonoise5_pw" signal
//int8_t pncode[] = { 1,1,1,-1,-1,-1,1,1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,-1 };


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

void readEEPROM(){
  if (EEPROM.read(0) == 42){
    // EEPROM data available
    chargeADCZero = (EEPROM.read(1) << 8) | EEPROM.read(2);
  } else Serial.println("no EEPROM data found, using default calibration");
  Serial.print("chargeADCZero=");
  Serial.println(chargeADCZero);  
}


void calibrateChargeCurrentSensor(){
  Serial.println("calibrateChargeCurrentSensor (note: robot must be outside charging station!)");
  RunningMedian<unsigned int,32> measurements;
  for (unsigned int i=0; i < measurements.getSize(); i++) {
    unsigned int m = analogRead(pinChargeCurrent);
    //Serial.println(m);
    measurements.add( m );
    delay(50);
  }
  float v;
  measurements.getAverage(v);  
  chargeADCZero = v;
  EEPROM.write(0, 42);
  EEPROM.write(1, chargeADCZero >> 8);
  EEPROM.write(2, chargeADCZero & 255);  
  Serial.println("calibration done");
  readEEPROM();
} 


  
void setup() {  
  pinMode(pinIN1, OUTPUT);    
  pinMode(pinIN2, OUTPUT);  
  pinMode(pinEnable, OUTPUT);
  pinMode(pinPWM, OUTPUT);  
  pinMode(pinFeedback, INPUT);    
  pinMode(pinFault, INPUT);      
  pinMode(pinPot, INPUT);      
  pinMode(pinChargeCurrent, INPUT);
  
  digitalWrite(pinEnable, HIGH);   
    
  //int T = 1000.0*1000.0/(7800*2);
  // sample rate 19230,76923076923 / 2 => 9615.38
  int T = 1000.0*1000.0/(19230.76923076923/2.0);
  Serial.begin(19200);
  
  Serial.println("START");
  Serial.print("Ardumower ");
  Serial.println(VER);
  Serial.println("press...");
  Serial.println("  1  for current sensor calibration");  
  Serial.println();
  
  readEEPROM();
  Serial.print("T=");
  Serial.println(T);    
  Serial.print("f=");
  Serial.println(1000.0*1000.0/T);    
  Timer1.initialize(T);         // initialize timer1, and set period
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

void checkKey(){
  if (Serial.available() > 0) {
      char ch = (char)Serial.read();            
      Serial.print("received key=");
      Serial.println(ch);
      while (Serial.available()) Serial.read();
      switch (ch){
        case '1': 
          calibrateChargeCurrentSensor();           
          break;
      }
  }             
}

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
    dutyPWM = ((int)(duty * 255.0));
    if (isCharging){
      // switch off perimeter 
      digitalWrite(pinEnable, LOW);            
    } else {
      // switch on perimeter
      digitalWrite(pinEnable, HIGH);                 
      //analogWrite(pinPWM, 255);
      analogWrite(pinPWM, dutyPWM);
      if ( (dutyPWM == 255) && (digitalRead(pinFault) == LOW) ) {
        duty = 0;
        analogWrite(pinPWM, duty);
        fault();    
      }    
    }
  }

  if (millis() >= nextTimeInfo){                
    nextTimeInfo = millis() + 500;                
    checkKey();        

    //unsigned int v = 0;
    float v = 0;
    // determine charging current (Ampere)        
    if (USE_CHG_CURRENT) {                
      chargeCurrentMeasurements.getAverage(v);
      chargeCurrent = ((double)(((int)v)  - ((int)chargeADCZero))) / 1023.0 * 5.0 / 0.5;  // 500 mV per amp  
      isCharging = (abs(chargeCurrent) >= CHG_CURRENT_MIN); // must be at least 9 mA for charging detection
    }  
    
    // determine perimeter current (Ampere)
    periCurrentMeasurements.getAverage(v);    
    periCurrent = ((double)v) / 1023.0 * 5.0 / 0.525;   // 525 mV per amp    
        
    Serial.print("time=");
    Serial.print(millis()/1000);    
    Serial.print("\tchgCurrent=");
    Serial.print(chargeCurrent, 3);
    Serial.print("\tisCharging=");
    Serial.print(isCharging);    
    Serial.print("\tperiCurrent=");
    Serial.print(periCurrent);
    Serial.print("\tduty=");
    Serial.print(duty);
    Serial.print("\tdutyPWM=");        
    Serial.print(dutyPWM);        
    Serial.print("\tfaults=");
    Serial.print(faults);        
    Serial.println();
    
    if (USE_POT){
      // read potentiometer
      duty = ((float)map(analogRead(pinPot),  0,1023,   0,1000))  /1000.0;
    }              
  }
    
  periCurrentMeasurements.add( analogRead(pinFeedback) );    

  if (USE_CHG_CURRENT){
    // determine charging current (Ampere)         
    chargeCurrentMeasurements.add( analogRead( pinChargeCurrent) );
  }
   
  // LED status 
  if (isCharging) {    
    // charging
    if (millis() >= nextTimeToggleLED){
      nextTimeToggleLED = millis() + 500;
      stateLED = !stateLED;
    }
  } else {
    // not charging => indicate perimeter wire state (OFF=broken)
    stateLED = (periCurrent >= PERI_CURRENT_MIN);
  }
  digitalWrite(pinLED, stateLED);   


}






