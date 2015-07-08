#ifndef BUTTON_H
#define BUTTON_H

// Ardumower ON/start button 



class ButtonControl
{
  public:    
    bool pressed;
    int beepCounter;
    ButtonControl();    
    void run();
    void setup();        
    void resetBeepCounter();
    void setBeepCount(int count);
  private:     
    int tempBeepCounter;
    unsigned long nextButtonTime;    
};


extern ButtonControl Button;  

  
#endif

