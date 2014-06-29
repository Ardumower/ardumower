/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
Arduino ADC manager (ADC0-ADC9)
- interrupt-based (free-running) ADC capturing (for certain sample count) (8 bit signed - zero = VCC/2)
- ordinary ADC sampling (one-time sampling) (10 bit unsigned)
- WARNING: never use any 'analogRead()' in your code when using this class!

How to use it (example):
1. Initialize ADC:  ADCMan.init();
2. Set ADC pin:     ADCMan.setCapture(pinMotorMowSense, 1, 1);
3. Read ADC:        int value = ADCMan.read(pinMotorMowSense);

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


