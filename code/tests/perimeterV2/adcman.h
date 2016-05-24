/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  
  Private-use only! (you need to ask for a commercial-use)
 
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
  
  Private-use only! (you need to ask for a commercial-use)
*/
/*
Problem: you have multiple analog inputs, some need only to be sampled once, other need
a fixed sample rate. 

Solution:  
Arduino ADC manager (ADC0-ADC9)
- can capture multiple pins one after the other (example ADC0: 1000 samples, ADC1: 100 samples, ADC2: 1 sample etc.)
- can capture more than one sample into buffers (fixed sample rate)
- runs in background: interrupt-based (free-running) 
- two types of ADC capture:
  1) free-running ADC capturing (for certain sample count) (8 bit signed - zero = VCC/2)
  2) ordinary ADC sampling (one-time sampling) (10 bit unsigned)
- WARNING: never use any 'analogRead()' in your code when using this class!

How to use it (example):
1. Initialize ADC:  ADCMan.init();
2. Set ADC pin:     ADCMan.setCapture(pinMotorMowSense, 1, 1);
3. Program loop:    while (true){
                      ADCMan.run();
                      if (ADCMan.isCaptureComplete(pinMotorMowSense)){
                        int value = ADCMan.read(pinMotorMowSense);
                      }
                    }
*/


#ifndef ADCMAN_H
#define ADCMAN_H


#include <Arduino.h>


// sample rates
enum {
  SRATE_9615,
  SRATE_19231,
  SRATE_38462  
};


class ADCManager
{
  public:
    ADCManager();
    // call this in setup
    void init();
    // call this to calibrate offsets of channels with autocalibrate
    void calibrate();
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
	// read the median value of samples
    int readMedian(byte pin);
    boolean isCaptureComplete(byte pin);
    // statistics only
    int getCapturedChannels();
    int16_t getADCMin(byte pin);
    int16_t getADCMax(byte pin);    
    int16_t getADCAvg(byte pin);    
    int16_t getADCOfs(byte pin);    
    // return number samples to capture
    int getCaptureSize(byte pin);
    // calibration data available?
    boolean calibrationDataAvail();
    // get the manager running, starts sampling next pin
    void run();    
    uint8_t sampleRate;
  private:
    int capturedChannels;    
    void startADC(int sampleCount);
    bool calibrationAvail;
    void calibrateOfs(byte pin);
    void startCapture(int sampleCount);
    void stopCapture();    
    boolean loadCalib();
    void loadSaveCalib(boolean readflag);
    void saveCalib();    
    void printCalib();
    void postProcess();
};

extern ADCManager ADCMan;


#endif


