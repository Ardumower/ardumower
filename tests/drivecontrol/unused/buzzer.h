#ifndef BUZZER_H
#define BUZZER_H

// Ardumower buzzer (play 'beep codes')

#include <Arduino.h>


// beep types ('tones')
enum {
  BEEP_MUTE,
  BEEP_SHORT,
  BEEP_LONG
};

// beep codes ('melodies')
enum {
  BC_SILENCE,
  BC_SHORT,
  BC_SHORT_SHORT,
  BC_SHORT_SHORT_SHORT,
  BC_LONG,  
  BC_LONG_SHORT_SHORT,
  BC_LONG_LONG,    
  BC_LONG_SHORT_LONG,
};

class BuzzerControl
{
  public:
    BuzzerControl();
    // play a 'melody' (non-blocking)
    void play(int beepCode);    
    bool isPlaying();
    void setup();
    void run();
  private:
    unsigned long nextBeepTime;
    int beepCodeToneIdx;
    int beepCodeIdx;
};


extern BuzzerControl Buzzer;  

  
#endif

