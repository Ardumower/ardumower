#include "led.h"
#include "drivers.h"
#include "config.h"

LEDControl LED;


LEDControl::LEDControl(){
  nextLEDTime = 0;
  ledSequenceIdx = LED_OFF;
  onState = 0;   
}

void LEDControl::setup(){
  Console.println(F("LEDControl::setup"));
  pinMode(pinLED, OUTPUT);
  pinMode(pinLEDDuoRed, OUTPUT);
  pinMode(pinLEDDuoGreen, OUTPUT); 
}

void LEDControl::run(){
  if (millis() < nextLEDTime) return;  
  nextLEDTime = millis() + 500;      
  switch (ledSequenceIdx){
    case LED_OFF: 
      digitalWrite(pinLED, LOW);    
      digitalWrite(pinLEDDuoRed, LOW);
      digitalWrite(pinLEDDuoGreen, LOW);
      break;
    case LED_GREEN_ON:
      digitalWrite(pinLED, HIGH);    
      digitalWrite(pinLEDDuoRed, LOW);
      digitalWrite(pinLEDDuoGreen, HIGH);
      break;          
    case LED_ORANGE_ON:
      digitalWrite(pinLEDDuoRed, HIGH);
      digitalWrite(pinLEDDuoGreen, HIGH);
      break;        
    case LED_ORANGE_BLINK:
      onState = !onState;
      digitalWrite(pinLEDDuoRed, onState);
      digitalWrite(pinLEDDuoGreen, onState);      
      break;      
    case LED_RED_BLINK:
      onState = !onState;
      digitalWrite(pinLED, onState);                  
      digitalWrite(pinLEDDuoRed, onState);
      digitalWrite(pinLEDDuoGreen, LOW);            
      break;      
    case LED_RED_ON:
      digitalWrite(pinLEDDuoRed, HIGH);
      digitalWrite(pinLEDDuoGreen, LOW);      
      break;    
  };  
}

void LEDControl::playSequence(int sequenceIdx){
  ledSequenceIdx = sequenceIdx;
  nextLEDTime = 0;  
}


