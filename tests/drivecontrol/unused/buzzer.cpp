#include "buzzer.h"
#include "drivers.h"
#include "config.h"

BuzzerControl Buzzer;


// beep code data
byte beepCodesTable[][6]={    
  {BEEP_MUTE,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},  
  {BEEP_SHORT, BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},  
  {BEEP_SHORT, BEEP_MUTE, BEEP_SHORT, BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},  
  {BEEP_SHORT, BEEP_MUTE, BEEP_SHORT, BEEP_MUTE, BEEP_SHORT, BEEP_MUTE},  
  {BEEP_LONG,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},  
  {BEEP_LONG,  BEEP_MUTE, BEEP_SHORT, BEEP_MUTE, BEEP_SHORT, BEEP_MUTE},    
  {BEEP_LONG,  BEEP_MUTE, BEEP_LONG,  BEEP_MUTE, BEEP_MUTE,  BEEP_MUTE},    
  {BEEP_LONG,  BEEP_MUTE, BEEP_SHORT, BEEP_MUTE, BEEP_LONG,  BEEP_MUTE},  
};



BuzzerControl::BuzzerControl(){  
  nextBeepTime = 0;
  beepCodeToneIdx = 6;
  beepCodeIdx = BC_SILENCE; 
}

void BuzzerControl::setup(){
  Console.println(F("BuzzerControl::setup"));  
  pinMode(pinBuzzer, OUTPUT);
}

// call this in main loop
void BuzzerControl::run(){
  if (millis() < nextBeepTime) return;
  if (beepCodeToneIdx >= 6) return;  
  switch (beepCodesTable[beepCodeIdx][beepCodeToneIdx]){
    case BEEP_MUTE: 
      noTone(pinBuzzer); 
      nextBeepTime = millis() + 400;  
      if (beepCodeToneIdx == 5) nextBeepTime = millis() + 1500;  
      break;
    case BEEP_SHORT:
      tone(pinBuzzer, 440);
      nextBeepTime = millis() + 100;  
      break; 
    case BEEP_LONG:
      tone(pinBuzzer, 440);
      nextBeepTime = millis() + 700;  
      break;
  }
  beepCodeToneIdx++;
}

// play a 'melody' (non-blocking)
void BuzzerControl::play(int beepCode){
  beepCodeIdx = beepCode;
  beepCodeToneIdx = 0;
  nextBeepTime = 0;
}

bool BuzzerControl::isPlaying(){
  return ((millis() < nextBeepTime) || (beepCodeToneIdx < 6));
}


