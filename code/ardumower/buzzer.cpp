#include "buzzer.h"
#include "config.h"
#include <Arduino.h>
#ifndef __AVR__
  #include "DueTimer.h"
#endif


BuzzerClass Buzzer;


#ifndef __AVR__
static boolean tone_pin_state = false;

void toneHandler(){  
  digitalWrite(pinBuzzer, tone_pin_state= !tone_pin_state);  
}
#endif 



void BuzzerClass::sound(SoundSelect idx, bool async){
  soundIdx = idx;
  toneIdx = 0;
  nextToneTime = millis();
  if (!async){
    while (nextToneTime != 0){
      run();
    }
  }
}

void BuzzerClass::run(){  
  if (nextToneTime == 0) return;
  unsigned long m = millis();
  if (m < nextToneTime) return;
  switch (soundIdx){
    case SND_READY:
      switch (toneIdx){
        case 0: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 100; break;
        case 1: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 100; break;
        case 2:                                nextToneTime = 0;       break;
      }
      break;
    case SND_PROGRESS:
      switch (toneIdx){
        case 0: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 5;  break;
        case 1: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 5;  break;
        case 2:                                nextToneTime = 0;      break;
      }
      break;
    case SND_OVERCURRENT:
      switch (toneIdx){
        case 0: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 50;  break;
        case 1: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 200; break;
        case 2: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 50;  break;
        case 3: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 200; break;
        case 4:                                nextToneTime = 0;       break;
      }
      break;
    case SND_TILT:
      switch (toneIdx){
        case 0: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 100; break;
        case 1: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 200; break;
        case 2: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 100; break;
        case 3: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 200; break;
        case 4:                                nextToneTime = 0;       break;
      }
      break;
    case SND_PERIMETER_TIMEOUT:
      switch (toneIdx){
        case 0: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 500; break;
        case 1: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 200; break;
        case 2: digitalWrite(pinBuzzer, HIGH); nextToneTime = m + 500; break;
        case 3: digitalWrite(pinBuzzer, LOW);  nextToneTime = m + 200; break;
        case 4:                                nextToneTime = 0;       break;
      }
      break;      
  }
  toneIdx++;
}

void BuzzerClass::begin()
{
   pinMode(pinBuzzer, OUTPUT);                
   digitalWrite(pinBuzzer, LOW);
   toneIdx=0;
   nextToneTime=0;   
}


void BuzzerClass::tone( uint16_t  freq )
{
#ifdef __AVR__   
   ::tone(pinBuzzer, freq);  
#else  
  pinMode(pinBuzzer, OUTPUT);
  Timer1.attachInterrupt(toneHandler).setFrequency(freq).start(); 
#endif     
}


void BuzzerClass::noTone(){
#ifdef __AVR__   
   ::noTone(pinBuzzer);
#else
  Timer1.stop();
  //pinMode(pinBuzzer, INPUT);  
  digitalWrite(pinBuzzer, LOW);
#endif     
}



