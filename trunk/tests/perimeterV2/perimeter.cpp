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


#include "perimeter.h"
#include <Arduino.h>
#include <limits.h>
#include "adcman.h"
#include "drivers.h"

//#define pinLED 13                  

int signalsize = 0;
int8_t matchSignal[100];

// http://grauonline.de/alexwww/ardumower/filter/filter.html
// "pulse3" signal                   
void Perimeter::gensignal(){
  //Console.println("gensignal");
  // http://grauonline.de/alexwww/ardumower/filter/filter.html    
  // "pseudonoise4_pw" signal
  //int8_t pncode[] = { 1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1 };
  // "pseudonoise5_pw" signal
  int8_t pncode[] = { 1,1,1,-1,-1,-1,1,1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1 };
  int step=0;
  byte width = 1;
  int8_t state = -1;
  byte signalidx = 0;
  memset(matchSignal, 0, sizeof matchSignal);    
  while (true){
    width--;
    if (width == 0){    
      if (step == sizeof pncode) break;        
      state *= -1;      
      if (pncode[step] == 1) {
        width = 2;    
      } else {
        width = 1;    
      } 
      step ++;          
    }
    matchSignal[signalidx] = state;    
    ///Console.println(state);    
    signalidx++;
    signalsize++;
    if (signalsize >= sizeof matchSignal){
      Console.println("increase signal size!");
      while (true);
    }    
  }   
  //while (true);
}
                   

Perimeter::Perimeter(){    
  callCounter = 0;
  mag[0] = mag[1] = 0;
  smoothMag = 0;
  signalCounter = 0;  
  filterMinSmooth = 0;
  filterMaxSmooth = 0;
  //signalsize = sizeof matchSignal;
  gensignal();  
}

void Perimeter::setPins(byte idx0Pin, byte idx1Pin){
  idxPin[0] = idx0Pin;
  idxPin[1] = idx1Pin;  
  ADCMan.setCapture(idx0Pin, SAMPLES, 1);
  
  Console.print("matchSignal size=");
  Console.println(signalsize);  
}

void Perimeter::speedTest(){
  int loops = 0;
  unsigned long endTime = millis() + 1000;
  while (millis() < endTime){
    matchedFilter(0);
    loops++;
  }
  Console.print("speedTest=");
  Console.println(loops);
}

int Perimeter::getMagnitude(byte idx){  
  if (ADCMan.isCaptureComplete(idxPin[idx])) {
    matchedFilter(idx);
  }
  return mag[idx];
}

int Perimeter::getSmoothMagnitude(){  
  return smoothMag;
}

void Perimeter::printADCMinMax(int8_t *samples){
  int8_t vmax = SCHAR_MIN;
  int8_t vmin = SCHAR_MAX;
  for (byte i=0; i < SAMPLES; i++){
    vmax = max(vmax, samples[i]);
    vmin = min(vmin, samples[i]);
  }
  Console.print("perimter min,max=");
  Console.print((int)vmin);
  Console.print(",");
  Console.println((int)vmax);  
}

// perimeter V2 uses a digital matched filter
void Perimeter::matchedFilter(byte idx){
  int8_t *samples = ADCMan.getCapture(idxPin[idx]);    
  if (callCounter == 100) {
    // statistics only
    callCounter = 0;
    signalMin = 9999;
    signalMax = -9999;
    signalAvg = 0;  
    for (int i=0; i < SAMPLES; i++){
      int8_t v = samples[i];
      signalAvg += v;
      signalMin = min(signalMin, v);
      signalMax = max(signalMax, v);
    }
    signalAvg = ((double)signalAvg) / ((double)SAMPLES);
  }
  // magnitude for tracking (fast but inaccurate)  
  mag[idx] = convFilter(matchSignal, signalsize, samples, SAMPLES-signalsize);      
  smoothMag = 0.99 * smoothMag + 0.01 * ((float)mag[idx]);

  // perimeter inside/outside detection
  if (mag[idx] > 0){
    signalCounter = min(signalCounter + 1, 3);    
  } else {
    signalCounter = max(signalCounter - 1, -3);    
  }
    
  ADCMan.restart(idxPin[idx]);    
  callCounter++;
}

int16_t Perimeter::getSignalMin(){
  return signalMin;
}

int16_t Perimeter::getSignalMax(){
  return signalMax;
}

int16_t Perimeter::getSignalAvg(){
  return signalAvg;
}

boolean Perimeter::isInside(){
  return (signalCounter < 0);  
}

boolean Perimeter::signalTimedOut(){
  return (smoothMag > 0);
}


// digital filter (cross correlation)
// http://en.wikipedia.org/wiki/Cross-correlation
// H[] holds the double sided filter coeffs, M = H.length (number of points in FIR)
// ip[] holds input data (length > nPts + M )
// nPts is the length of the required output data 
// subSmp is the subsampling rate subSmp=8 means output every 8th sample

int16_t Perimeter::convFilter(int8_t *H, int16_t M, int8_t *ip, int16_t nPts){  
  int16_t sumMax = 0;
  int16_t sumMin = 0;
  for (int16_t j=0; j<nPts; j++)
  {
      int16_t sum = 0;      
      int8_t *Hi = H;
      int8_t *ipi = ip;      
      for (int16_t i=0; i<M; i++)
      {
        sum += ((int16_t)(*Hi)) * ((int16_t)(*ipi));
        Hi++;
        ipi++;
      }      
      if (sum > sumMax) sumMax = sum;
      if (sum < sumMin) sumMin = sum;
      ip++;
  }
  if (sumMax > abs(sumMin)) return sumMax;
    else return sumMin;  
}




