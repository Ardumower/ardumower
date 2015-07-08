#include "led.h"
#include "config.h"


LEDControl::LEDControl(){
  nextLEDTime = 0;
  ledSequenceIdx = LED_SEQ_OFF;
  onState = 0;
}

void LEDControl::setup(){
  Console.println(F("LEDControl::setup"));
}

void LEDControl::run(){
  if (millis() < nextLEDTime) return;
  nextLEDTime = millis() + 500;
  switch (ledSequenceIdx){
    case LED_SEQ_OFF:
      setDriverLED(LED_ARDUINO, LOW);
      setDriverLED(LED_DUAL_RED, LOW);
      setDriverLED(LED_DUAL_GREEN, LOW);
      break;
    case LED_SEQ_GREEN_ON:
      setDriverLED(LED_ARDUINO, HIGH);
      setDriverLED(LED_DUAL_RED, LOW);
      setDriverLED(LED_DUAL_GREEN, HIGH);
      break;
    case LED_SEQ_ORANGE_ON:
      setDriverLED(LED_DUAL_RED, HIGH);
      setDriverLED(LED_DUAL_GREEN, HIGH);
      break;
    case LED_SEQ_ORANGE_BLINK:
      onState = !onState;
      setDriverLED(LED_DUAL_RED, onState);
      setDriverLED(LED_DUAL_GREEN, onState);
      break;
    case LED_SEQ_RED_BLINK:
      onState = !onState;
      setDriverLED(LED_ARDUINO, onState);
      setDriverLED(LED_DUAL_RED, onState);
      setDriverLED(LED_DUAL_GREEN, LOW);
      break;
    case LED_SEQ_RED_ON:
      setDriverLED(LED_DUAL_RED, HIGH);
      setDriverLED(LED_DUAL_GREEN, LOW);
      break;
  };
}

void LEDControl::setDriverLED(int LEDidx, bool state){
}

void LEDControl::playSequence(int sequenceIdx){
  ledSequenceIdx = sequenceIdx;
  nextLEDTime = 0;
}


