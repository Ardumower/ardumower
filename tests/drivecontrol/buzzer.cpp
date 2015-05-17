#include "buzzer.h"

BuzzerControl Buzzer;


BuzzerControl::BuzzerControl(){  
  nextBeepTime = 0;
  beepCodeToneIdx = 0;
  beepCodeIdx = BC_SILENCE; 
}

// call this in main loop
void BuzzerControl::run(){
  if (millis() < nextBeepTime) return;
  if (beepCodeToneIdx >= 4) return;
  nextBeepTime = millis() + 500;
  beepCodeToneIdx++;
  switch (beepCodesTable[beepCodeIdx][beepCodeToneIdx]){
    case BEEP_MUTE: 
      noTone(pinBuzzer); 
      break;
    case BEEP_SHORT:
      tone(pinBuzzer, 440);
      break; 
    case BEEP_LONG:
      tone(pinBuzzer, 440);
      nextBeepTime = millis() + 1000;  
      break;
  }
}

// play a 'melody' (non-blocking)
void BuzzerControl::beep(int code){
  beepCodeIdx = code;
  beepCodeToneIdx = 0;
  nextBeepTime = 0;
}



