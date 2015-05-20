#ifndef BUTTON_H
#define BUTTON_H

// Ardumower ON/start button 

#include <Arduino.h>

#define pinButton 51               // digital ON/OFF button



class ButtonControl
{
  public:    
    int beepCounter;
    ButtonControl();    
    void run();
    void setup();    
    bool pressed();    
    void resetBeepCounter();
  private:    
    int tempBeepCounter;
    unsigned long nextButtonTime;    
};


extern ButtonControl Button;  

  
#endif

