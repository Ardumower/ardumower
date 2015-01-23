
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

#define pinPerimeterLeft A5        // perimeter pin
#define pinPerimeterRight A4       // leave open
#define pinLED 13

// #define USE_DEVELOPER_TEST 1

Perimeter perimeter;
unsigned long nextTime = 0;
int counter = 0;
boolean inside = true;
int mode = 0;


void setup()  {  
  Wire.begin();
  Console.begin(19200);  
  pinMode(pinLED, OUTPUT);

  delay(100);
  Console.println("START");        
  
  ADCMan.init();
  perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);          
  
  perimeter.speedTest();
}


void printConsole(){
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
    Console.print("qty ");        
    Console.print((int)(perimeter.getFilterQuality()*100.0));
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


// https://code.google.com/p/serialchart/
void printSerialChart(){
  if (!ADCMan.isCaptureComplete(pinPerimeterLeft)) return;
  int8_t *samples = ADCMan.getCapture(pinPerimeterLeft);      
  int sz = ADCMan.getCaptureSize(pinPerimeterLeft);      
  int mag = perimeter.getMagnitude(0);              
  int qty = perimeter.getFilterQuality()*100.0;      
  for (int i=0; i < sz; i++){
    for (int w=0; w < 10; w++){
      if (i==0){
        Console.print(qty);
      } else Console.print("0");
      Console.print(",");
      Console.println(samples[i]);
    }
  }
  delay(5000);
}

void loop()  {     
      
  ADCMan.run();  
  
  if (Console.available() > 0){
    char ch = (char)Console.read();      
    if (ch == 'v') mode = !mode;
    if (ch == 'c') {
      Console.println("calibrating ADC (power off sender for this!)...");
      Console.flush();
      delay(5000);
      ADCMan.calibrate();
    }
  }
  
  if (millis() >= nextTime){
    nextTime = millis() + 50;
    if (perimeter.isInside() != inside){
      inside = perimeter.isInside();
      counter++;      
    }
    if (perimeter.isInside()) digitalWrite(pinLED, HIGH);    
      else digitalWrite(pinLED, LOW);    

    if (mode == 0){
      printConsole();
    } else {
      printSerialChart();
    }
  }
}



