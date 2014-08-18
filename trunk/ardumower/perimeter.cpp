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
/*int8_t matchSignal[] = {  1,1,1,1,  -1,-1,-1,-1,   
                   0,0,0,0,  0,0,0,0,
                   0,0,0,0,  0,0,0,0,
                   0,0,0,0,  0,0,0,0,
                   0,0,0,0,  0,0,0,0,
                   0,0,0,0 };                   */
                   
void Perimeter::gensignal(){
  //Console.println("gensignal");
  // http://grauonline.de/alexwww/ardumower/filter/filter.html    
  // "pseudonoise4_pw" signal
  int8_t pncode[] = { 1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1 };
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
        width = 4;    
      } else {
        width = 2;    
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
  nextTime = 0;
  mag[0] = mag[1] = 0;
  smoothMag = 0;
  signalCounter = 0;  
  filterMinSmooth = 0;
  filterMaxSmooth = 0;
  //signalsize = sizeof matchSignal;
  gensignal();  
  lastSignalTime = millis();
}

void Perimeter::setPins(byte idx0Pin, byte idx1Pin){
  idxPin[0] = idx0Pin;
  idxPin[1] = idx1Pin;  
  ADCMan.setCapture(idx0Pin, SAMPLES, 1);
  
  Console.print("matchSignal size=");
  Console.println(signalsize);  
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
  //double Ta = millis() - lastMeasureTime;
  //lastMeasureTime = millis();   
  int16_t out[SAMPLES];
  memset(out, 0, sizeof out);      
  int8_t *samples = ADCMan.getCapture(idxPin[idx]);    
  signalMin = 9999;
  signalMax = -9999;
  signalAvg = 0;
  for (int i=0; i < SAMPLES; i++){
    int8_t v = samples[i];
    signalAvg += ((double)v) / ((double)SAMPLES);
    signalMin = min(signalMin, v);
    signalMax = max(signalMax, v);
  }
  memset(out, 0, sizeof out);  
  convFilter(matchSignal, signalsize, samples, out, SAMPLES-signalsize);    
  double filterMin = 0;
  double filterMax = 0;
  double filterAvg = 0;
  double filterSum = 0;
  for (int i=0; i < SAMPLES; i++){    
    double v = out[i];      
    filterMin = min(filterMin, v);
    filterMax = max(filterMax, v);
    filterSum += v;  
  }
  //filterMaxSmooth = 0.95 * filterMaxSmooth + 0.05 * filterMax;
  //filterMinSmooth = 0.95 * filterMinSmooth + 0.05 * filterMin;  
  filterAvg = ((double)filterSum) / ((double)SAMPLES);  
  
  double filterVar = 0;
  for (int i=0; i < SAMPLES; i++){    
    filterVar += abs(out[i] - filterAvg) / SAMPLES;  
  } 
  
  // magnitude for tracking (fast but inaccurate)
  if (abs(filterMax) > abs(filterMin)) mag[idx] = filterMax;  
    else mag[idx] = filterMin;  
  smoothMag = 0.99 * smoothMag + 0.01 * mag[idx];
  //Console.println(var);

  // perimeter inside/outside detection
  if (abs(filterMax) > abs(filterMin)){
    signalCounter = min(signalCounter + 1, 3);    
  } else {
    signalCounter = max(signalCounter - 1, -3);    
  }
    
  // perimeter timeout
  //if ((vmax > var*8) || (abs(vmin) > var*8)){        
  //if ((filterMin < -400) || (filterMax > 400)){        
     lastSignalTime = millis();    
  //}
       
  ADCMan.restart(idxPin[idx]);    
}

double Perimeter::getSignalMin(){
  return signalMin;
}

double Perimeter::getSignalMax(){
  return signalMax;
}

double Perimeter::getSignalAvg(){
  return signalAvg;
}

boolean Perimeter::isInside(){
  return (signalCounter < 0);  
}

boolean Perimeter::signalTimedOut(){
  //return (millis() > lastSignalTime + 5000);
  return (smoothMag > 0);
}


/* 
// digital filter (cross correlation) for periodic filter coeffs
// http://en.wikipedia.org/wiki/Cross-correlation
// H[] holds the double sided filter coeffs, M = H.length (number of points in FIR)
// ip[] holds input data (length > nPts + M )
// op[] is output buffer
// nPts is the length of the required output data 
void PerimeterClass::convFilter(int8_t *H, int16_t M, int8_t *ip, int16_t *op, int16_t nPts){  
  int16_t sum = 0;
  for (int16_t k=0; k<M; k++)
  {      
    int16_t j=k;
    sum = 0;
    while (j<nPts)
    {
      for (int16_t i=0; i<M; i++)
      {      
        sum += ((int16_t)H[i]) * ((int16_t)ip[j+i]);
      }
      j += M;
    }
    op[j] = sum;    
  }
}*/


// digital filter (cross correlation)
// http://en.wikipedia.org/wiki/Cross-correlation
// H[] holds the double sided filter coeffs, M = H.length (number of points in FIR)
// ip[] holds input data (length > nPts + M )
// op[] is output buffer
// nPts is the length of the required output data 
void Perimeter::convFilter(int8_t *H, int16_t M, int8_t *ip, int16_t *op, int16_t nPts){  
  int16_t sum = 0;
  for (int16_t j=0; j<nPts; j++)
  {
      sum = 0;
      for (int16_t i=0; i<M; i++)
      {
        //sum += H[i]*ip[subSmp*j+i];
        sum += ((int16_t)H[i]) * ((int16_t)ip[j+i]);
      }
      op[j] = sum;      
  }
}




