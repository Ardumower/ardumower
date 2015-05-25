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
  Console.println("ButtonControl::setup");
  pinMode(pinButton, INPUT);
  pinMode(pinButton, INPUT_PULLUP);  
}

void ButtonControl::resetBeepCounter(){
  beepCounter = 0;
}

bool ButtonControl::pressed(){
  return (digitalRead(pinButton) == LOW);
}

// call this in main loop
void ButtonControl::run(){
  boolean buttonPressed = pressed();
  if ( (!buttonPressed) && (tempBeepCounter > 0) ){
    nextButtonTime = millis() + 2000;      
    beepCounter = tempBeepCounter;
    Console.print("BUTTON beeps ");
    Console.println(beepCounter);
    tempBeepCounter = 0;    
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




