#ifndef BUZZER_H
#define BUZZER_H

// Ardumower buzzer (play 'beep codes')

#include <Arduino.h>

#define pinBuzzer 53               // Buzzer


// beep type names ('tones')
enum {
  BEEP_MUTE,
  BEEP_SHORT,
  BEEP_LONG
};

// beep code names ('melodies')
enum {
  BC_SILENCE,
  BC_SHORT,
  BC_LONG,
  BC_SHORT_SHORT,
  BC_SHORT_LONG,
  BC_LONG_LONG,
};

// beep codes table (memory stored melodies)
byte beepCodesTable[][4]={  
  {BEEP_MUTE,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},
  {BEEP_SHORT, BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},
  {BEEP_LONG,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},
  {BEEP_SHORT, BEEP_MUTE, BEEP_SHORT, BEEP_MUTE},
  {BEEP_SHORT, BEEP_MUTE, BEEP_LONG,  BEEP_MUTE},
  {BEEP_LONG,  BEEP_MUTE, BEEP_LONG,  BEEP_MUTE},
};


class BuzzerControl
{
  public:
    BuzzerControl();
    // play a 'melody' (non-blocking)
    void beep(int code);
    void run();
  private:
    unsigned long nextBeepTime;
    int beepCodeToneIdx;
    int beepCodeIdx;
};


extern BuzzerControl Buzzer;  

  
#endif

