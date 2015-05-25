#include "button.h"
#include "drivers.h"
#include "config.h"
#include "buzzer.h"

ButtonControl Button;


ButtonControl::ButtonControl(){  
  nextButtonTime = 0;
  beepCounter = tempBeepCounter = 0;  
}

void ButtonControl::setup(){
  // button
  Console.println(F("ButtonControl::setup"));
  pinMode(pinButton, INPUT);
  pinMode(pinButton, INPUT_PULLUP);  
}

void ButtonControl::resetBeepCounter(){
  beepCounter = 0;
}

bool ButtonControl::pressed(){
  return (digitalRead(pinButton) == LOW);
}

void ButtonControl::setBeepCount(int count){
  nextButtonTime = millis() + 2000;      
  beepCounter = count;
  Console.print(F("BUTTON beeps "));
  Console.println(beepCounter);
  tempBeepCounter = 0;    
}

// call this in main loop
void ButtonControl::run(){    
  boolean buttonPressed = pressed();
  
  if ( (!buttonPressed) && (tempBeepCounter > 0) ){
    setBeepCount(tempBeepCounter);
  }  
  if (millis() >= nextButtonTime){    
    if (buttonPressed) {
      nextButtonTime = millis() + 1000;      
      Buzzer.play(BC_SHORT);
      tempBeepCounter++;       
    } else {            
      beepCounter = 0;    
    }
  }
}




