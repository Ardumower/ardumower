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
perimeter v2 receiver for Arduino sound sensors/LM386 using digital filter: matched filter - evaluates signal polarity of 'pulse3' signal on one ADC pin (for one coil)
 (for details see    http://wiki.ardumower.de/index.php?title=Perimeter_wire )

How to use it (example):    
  1. initialize ADC:        ADCMan.init(); 
  2. set perimeter pins:    Perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);  
  3. read perimeter:        int value = Perimeter.getMagnitude(0);  
    
*/

#ifndef PERIMETER_H
#define PERIMETER_H

#include <Arduino.h>



class Perimeter
{
  public:
    Perimeter();
    // set ADC pins
    void setPins(byte idx0Pin, byte idx1Pin);    
    // get perimeter magnitude
    int getMagnitude(byte idx);    
    int getSmoothMagnitude();
    // inside perimeter (true) or outside (false)?  
    boolean isInside();
    // perimeter signal timed out? (e.g. due to broken wire)
    boolean signalTimedOut();
    int16_t getSignalMin();
    int16_t getSignalMax();    
    int16_t getSignalAvg();
    float getFilterQuality(); 
    void speedTest();
    int16_t timedOutIfBelowSmag;
  private:
    unsigned long lastInsideTime;
    byte type; // which perimeter version to use
    byte idxPin[2]; // channel for idx
    int callCounter;
    int16_t mag [2]; // perimeter magnitude per channel
    float smoothMag;
    float filterQuality;
    int16_t signalMin;
    int16_t signalMax;
    int16_t signalAvg;    
    int signalCounter;    
    void matchedFilter(byte idx);
    int16_t corrFilter(int8_t *H, int16_t M, int8_t *ip, int16_t nPts, float &quality);
    void printADCMinMax(int8_t *samples);
    void gensignal();
};


#endif

