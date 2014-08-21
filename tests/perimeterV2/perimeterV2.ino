
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

#include "drivers.h"
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
  Console.begin(19200);  
  pinMode(pinLED, OUTPUT);

  delay(100);
  Console.println("START");        
  
  ADCMan.init();
  ADCMan.calibrate();
  perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);        
  
  perimeter.speedTest();
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
    
    Console.print("cnt ");
    Console.print(counter);
    Console.print("\t");    
    Console.print("min ");
    Console.print((int)perimeter.getSignalMin());
    Console.print("\t");
    Console.print("max ");
    Console.print((int)perimeter.getSignalMax());
    Console.print("\t");
    Console.print("avg ");
    Console.print((int)perimeter.getSignalAvg());    
    Console.print("\t\t");
    Console.print("mag ");
    Console.print((int)perimeter.getMagnitude(0));        
    Console.print("\t");
    Console.print("\t");    
    Console.print("smag ");    
    Console.print((int)perimeter.getSmoothMagnitude());                
    Console.print("\t");
    Console.print("\t");
    Console.print("in ");
    Console.print((int)perimeter.isInside());            
    Console.print("\t");
    Console.print("on ");
    Console.print((int)(!perimeter.signalTimedOut()));            
    Console.print("\t");
    Console.print("adc ");
    Console.print((int)(ADCMan.getCapturedChannels()));            
    Console.println();
  }
}



