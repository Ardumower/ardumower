#ifndef MODELRC_H
#define MODELRC_H

// model R/C receiver

#include <Arduino.h>


class ModelReceiver 
{
  public:
    bool enable;
    int remoteSteer ;  // range -100..100
    int remoteSpeed ;  // range -100..100      
    ModelReceiver();    
    void setup();
    void run();
    void print();
};

extern ModelReceiver ModelRC;

#endif


