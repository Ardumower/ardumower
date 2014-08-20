
/* Perimeter v2 test
   Arduino Mega
 */

#include <Arduino.h>
#include <Wire.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
  #include "due.h"
#endif

#include "adcman.h"
#include "perimeter.h"


#define pinPerimeterRight A4       // perimeter
#define pinPerimeterLeft A5
#define pinLED 13

Perimeter perimeter;
unsigned long nextTime = 0;
int counter = 0;
boolean inside = true;


void setup()  {  
  Wire.begin();
  Serial.begin(19200);  
  pinMode(pinLED, OUTPUT);

  delay(100);
  Serial.println("START");        
  
  ADCMan.init();
  perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);        
}

void loop()  {     
      
  ADCMan.run();  
  
  if (millis() >= nextTime){
    nextTime = millis() + 50;
    if (perimeter.isInside() != inside){
      inside = perimeter.isInside();
      counter++;      
    }
    if (perimeter.isInside()) digitalWrite(pinLED, HIGH);    
      else digitalWrite(pinLED, LOW);    
    
    Serial.print("cnt ");
    Serial.print(counter);
    Serial.print("\t");    
    Serial.print("min ");
    Serial.print((int)perimeter.getSignalMin());
    Serial.print("\t");
    Serial.print("max ");
    Serial.print((int)perimeter.getSignalMax());
    Serial.print("\t");
    Serial.print("avg ");
    Serial.print((int)perimeter.getSignalAvg());    
    Serial.print("\t\t");
    Serial.print("mag ");
    Serial.print((int)perimeter.getMagnitude(0));        
    Serial.print("\t");
    Serial.print("\t");    
    Serial.print("smag ");    
    Serial.print((int)perimeter.getSmoothMagnitude());                
    Serial.print("\t");
    Serial.print("\t");
    Serial.print("in ");
    Serial.print((int)perimeter.isInside());            
    Serial.print("\t");
    Serial.print("on ");
    Serial.print((int)(!perimeter.signalTimedOut()));            
    Serial.print("\t");
    Serial.print("adc ");
    Serial.print((int)(ADCMan.getCapturedChannels()));            
    Serial.println();
  }
}



