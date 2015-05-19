#ifndef MODELRC_H
#define MODELRC_H

// model R/C receiver

#include <Arduino.h>

// Warning: If you change pinout, interrupt configuration need to be changed too!
#define pinRemoteSteer 11          // remote control steering 
#define pinRemoteSpeed 10          // remote control speed


class ModelReceiver
{
  public:
    int remoteSteer ;  // range -100..100
    int remoteSpeed ;  // range -100..100      
    ModelReceiver();    
    void run();
    void print();
};

extern ModelReceiver ModelRC;

#endif


