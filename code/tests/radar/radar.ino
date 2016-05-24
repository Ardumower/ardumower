/*
  test Radar sensor ZY-JIN HB200A (10.525 Ghz, 3 Mhz, 13dBm EIRP)

  Arduino A0 -- LM386 amplifier -- Radar sensor IF
 */

#include <Wire.h>
#include <Arduino.h>

#define RADAR_IF A0
//#define RADAR_IF 5
#define pinLED 13
//#define pinBuzzer 5


int vmax = 0;
int vmin = 9999;
double vavg = 0;
double vcenter = 0;
unsigned long startTime = 0;
unsigned long stopTime = 0;
unsigned long time = 0;
unsigned long offTime = 0;
unsigned long duration = 0;
bool state = LOW;
int thres = 10;

void setup() {  
  Serial.begin(19200);
  Serial.println("START");
  pinMode(RADAR_IF, INPUT);   
  pinMode(pinLED, OUTPUT);
  //pinMode(pinBuzzer, OUTPUT);  
}

void loop() {           
  /*bool newstate= digitalRead(RADAR_IF);
  if (newstate != state) {
    state = newstate;
    duration++;
    Serial.println(duration);
  }
  
  //duration = pulseIn(RADAR_IF, HIGH, 20000);*/
  
  int v = analogRead(RADAR_IF);  
  double vdiff = fabs(vavg-v);
  vavg = 0.99 * vavg + 0.01 * ((double)v);
  vmax = max(vmax*0.99, v);
  vmin = min(vmin*1.01, v);
  vcenter = vmin + (vmax - vmin) / 2;
  if (v > vavg + thres) {
    startTime = millis();
  }
  else if ((v < vavg - thres) && (startTime != 0)) {                  
      stopTime = millis();
      time = stopTime - startTime;      
      startTime = 0;
      //vmax = 0;
      //vmin = 9999;      
  }
  
  if (time != 0) {
    digitalWrite(pinLED, HIGH);      
    offTime = millis() + 1000;    
    Serial.print("vdiff=");
    Serial.print(vdiff);
    Serial.print("  vcenter=");
    Serial.print(vcenter);
    Serial.print("  vmax=");
    Serial.print(vmax);
    Serial.print("  vmin=" );
    Serial.print(vmin);
    Serial.print("  time=" );
    Serial.print(time);
    Serial.println();                
    //if (time == 0) tone(pinBuzzer, time);
    //  else noTone(pinBuzzer);             
    time = 0;
  } 
  if (millis() > offTime){
    digitalWrite(pinLED, LOW);      
  }
  delay(1);
}


