/*
  test Radar sensor ZY-JIN HB200A (10.525 Ghz, 3 Mhz, 13dBm EIRP)

  Arduino A0 -- Radar sensor IF
 */

#include <Wire.h>
#include <Arduino.h>

#define RADAR_IF A0
#define pinLED 13

int vmax = 0;
int vmin = 9999;
double vcenter = 0;
unsigned long startTime = 0;
unsigned long stopTime = 0;
unsigned long time = 0;
unsigned long nextInfoTime = 0;

void setup() {  
  Serial.begin(19200);
  Serial.println("START");
  pinMode(RADAR_IF, INPUT);   
  pinMode(pinLED, OUTPUT);
}

void loop() {         
  int v = analogRead(RADAR_IF);  
  vmax = max(vmax, v);
  vmin = min(vmin, v);
  vcenter = vmin + (vmax - vmin) / 2;
  if (startTime == 0){
    if (v > vcenter+1) {
      startTime = millis();
    }
  } else {
    if (v < vcenter-1) {
      stopTime = millis();
      time = stopTime - startTime;
      startTime = 0;
    }
  }
  if (millis() > nextInfoTime){
    nextInfoTime = millis() + 1000;
    if (time > 0) digitalWrite(pinLED, HIGH);
      else digitalWrite(pinLED, LOW);
    Serial.print("vcenter ");
    Serial.print(vcenter);
    Serial.print("  vmax ");
    Serial.print(vmax);
    Serial.print("  vmin " );
    Serial.print(vmin);
    Serial.print("  time " );
    Serial.print(time);
    Serial.println();    
    time = 0;
    vmax = 0;
    vmin = 9999;
  }
  delay(1);
}


