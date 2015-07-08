
// differential wheels drive controller experiments 
// Requires: Ardumower Mini, Arduino Mega


#include <Arduino.h>
#include <Wire.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
  #include "due.h"
#endif

#include "robot.h"


void setup(){
  Robot.setup();  
  //Console.begin(19200);
  //Console.println("setup()");  
}


void loop(){  
  Robot.loop();
  //Console.println("loop()");
  //delay(1000);
}



