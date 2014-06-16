/*
Arduino ADC manager (ADC0-ADC9)
- interrupt-based (free-running) ADC capturing (for certain sample count) (8 bit signed - zero = VCC/2)
- ordinary ADC sampling (one-time sampling) (10 bit unsigned)
- WARNING: never use any 'analogRead()' in your code when using this class!

*/

#ifndef ADCMAN_H
#define ADCMAN_H

#include <Arduino.h>

#define ADC_MAX_CAPTURE_SIZE 128

class ADCManager
{
  public:
    ADCManager();
    // call this in setup
    void init();
    // configure sampling for pin:
    // samplecount = 1: 10 bit sampling (unsigned)
    // samplecount > 1: 8 bit sampling (signed - zero = VCC/2)
    void setCapture(byte pin, byte samplecount, boolean autoCalibrateOfs);    
    // get buffer with samples for pin
    int8_t* getCapture(byte pin);        
    // restart sampling for pin
    void restart(byte pin);    
    // samplecount=1: get one sample for pin
    // samplecount>1: get first sample for pin
    int read(byte pin);
    boolean isCaptureComplete(byte pin);
    // statistics only
    int getCapturedChannels();
    // get the manager running, starts sampling next pin
    void run();    
  private:
    int capturedChannels;
    boolean channelReady[10]; // ready for capture?
    void calibrateOfs(byte pin);
    void startCapture(boolean fast);
    void stopCapture();    
};

extern ADCManager ADCMan;


#endif


