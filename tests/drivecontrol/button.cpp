#include "button.h"
#include "drivers.h"
#include "config.h"
#include "buzzer.h"

ButtonControl Button;


ButtonControl::ButtonControl(){  
  nextButtonTime = 0;
  beepCounter = tempBeepCounter = 0;  
  pressed = false;
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

void ButtonControl::setBeepCount(int count){
  nextButtonTime = millis() + 2000;      
  beepCounter = count;
  Console.print(F("BUTTON beeps "));
  Console.println(beepCounter);
  tempBeepCounter = 0;    
  pressed = true; 
}

// call this in main loop
void ButtonControl::run(){    
  //if (pressed) Console.println(F("BUTTON pressed"));  
  pressed = (digitalRead(pinButton) == LOW);  

  if ( (!pressed) && (tempBeepCounter > 0) ){
    setBeepCount(tempBeepCounter);
  }  
  if (millis() >= nextButtonTime){    
    if (pressed) {
      nextButtonTime = millis() + 1000;      
      Buzzer.play(BC_SHORT);
      tempBeepCounter++;       
    } else {            
      beepCounter = 0;    
    }
  }
}




