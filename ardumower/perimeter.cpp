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
#include "fix_fft.h"
#include "adcman.h"

PerimeterClass Perimeter;

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
                   
void PerimeterClass::gensignal(){
  //Serial.println("gensignal");
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
    ///Serial.println(state);    
    signalidx++;
    signalsize++;
    if (signalsize >= sizeof matchSignal){
      Serial.println("increase signal size!");
      while (true);
    }    
  }   
  //while (true);
}
                   

PerimeterClass::PerimeterClass(){    
  nextTime = 0;
  mag[0] = mag[1] = 0;
  smoothMag = 0;
  peakBin = 0;
  peakV = 0;  
  signalCounter = 0;  
  filterMinSmooth = 0;
  filterMaxSmooth = 0;
  memset(peak, 0, sizeof peak);          
  memset(allmag, 0, sizeof allmag);          
  //signalsize = sizeof matchSignal;
  gensignal();  
  Serial.print("matchSignal size=");
  Serial.println(signalsize);
  lastSignalTime = millis();
}

void PerimeterClass::setPins(byte idx0Pin, byte idx1Pin){
  idxPin[0] = idx0Pin;
  idxPin[1] = idx1Pin;
  ADCMan.setCapture(idx0Pin, FFTBINS, 1);
  ADCMan.setCapture(idx1Pin, FFTBINS, 1);  
}

int PerimeterClass::getMagnitude(byte idx){  
  if (ADCMan.isCaptureComplete(idxPin[idx])) {
    matchedFilter(idx);
    //filterFrequencyMagnitude(idx);    
  }
  return mag[idx];
}

int PerimeterClass::getSmoothMagnitude(){  
  return smoothMag;
}

int PerimeterClass::getSpectrum(int fftBin){
  if (fftBin >= FFTBINS) return 0;
  int v = allmag[fftBin];
  allmag[fftBin] = 0;
  return v;
}

void PerimeterClass::printADCMinMax(int8_t *samples){
  int8_t vmax = SCHAR_MIN;
  int8_t vmin = SCHAR_MAX;
  for (byte i=0; i < FFTBINS; i++){
    vmax = max(vmax, samples[i]);
    vmin = min(vmin, samples[i]);
  }
  Serial.print("perimter min,max=");
  Serial.print((int)vmin);
  Serial.print(",");
  Serial.println((int)vmax);  
}

void PerimeterClass::matchedFilter(byte idx){
  //double Ta = millis() - lastMeasureTime;
  //lastMeasureTime = millis();   
  int16_t out[FFTBINS];
  memset(out, 0, sizeof out);      
  int8_t *samples = ADCMan.getCapture(idxPin[idx]);    
  signalMin = 9999;
  signalMax = -9999;
  signalAvg = 0;
  for (int i=0; i < FFTBINS; i++){
    int8_t v = samples[i];
    signalAvg += ((double)v) / ((double)FFTBINS);
    signalMin = min(signalMin, v);
    signalMax = max(signalMax, v);
  }
  memset(out, 0, sizeof out);  
  convFilter(matchSignal, signalsize, samples, out, FFTBINS-signalsize);    
  double filterMin = 0;
  double filterMax = 0;
  double filterAvg = 0;
  double filterSum = 0;
  for (int i=0; i < FFTBINS; i++){    
    double v = out[i];      
    filterMin = min(filterMin, v);
    filterMax = max(filterMax, v);
    filterSum += v;  
  }
  //filterMaxSmooth = 0.95 * filterMaxSmooth + 0.05 * filterMax;
  //filterMinSmooth = 0.95 * filterMinSmooth + 0.05 * filterMin;  
  filterAvg = ((double)filterSum) / ((double)FFTBINS);  
  
  double filterVar = 0;
  for (int i=0; i < FFTBINS; i++){    
    filterVar += abs(out[i] - filterAvg) / FFTBINS;  
  } 
  
  // magnitude for tracking (fast but inaccurate)
  if (abs(filterMax) > abs(filterMin)) mag[idx] = filterMax;  
    else mag[idx] = filterMin;  
  smoothMag = 0.99 * smoothMag + 0.01 * mag[idx];
  //Serial.println(var);

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

double PerimeterClass::getSignalMin(){
  return signalMin;
}

double PerimeterClass::getSignalMax(){
  return signalMax;
}

double PerimeterClass::getSignalAvg(){
  return signalAvg;
}

boolean PerimeterClass::isInside(){
  return (signalCounter < 0);  
}

boolean PerimeterClass::signalTimedOut(){
  return (millis() > lastSignalTime + 5000);
}

void PerimeterClass::filterFrequencyMagnitude(byte idx){
  mag[idx] = 0;          
  int8_t im[FFTBINS];
  memset(im, 0, sizeof im);      
  int8_t *samples = ADCMan.getCapture(idxPin[idx]);    
  //if (idx == 0) printADCMinMax(samples);
  fix_fft(samples, im, 7, 0);              
  //digitalWrite(pinLED, LOW);    
  for (byte i=0; i < FFTBINS/2; i++){      
    int v = sqrt(samples[i] * samples[i] + im[i] * im[i]);      
    allmag[i] = max(allmag[i], v);
    if (i > 0) { // ignore 50 Hz band
     // find overall frequencies peak (peak)
      if (v > peakV){
        peakV = v;
        peakBin = i;
      }
    }
    if (i == BANDPASS_BIN) { 
      // bandpass  
      //analogWrite(LED, min(255, v));
      mag[idx] = max(mag[idx], v);        
      //mag[channel] += v;                
      peak[idx] = max(peak[idx], v);                         
      //if (v > 20) digitalWrite(pinLED, HIGH);          
    }            
  }     
  //if (idx ==0) Serial.println(mag[idx]);
  ADCMan.restart(idxPin[idx]);
  if (millis() >= nextTime){      
    nextTime = millis() + 1000;
    int sum = peak[0] + peak[1];
    //printResults();
    peak[0]=0;
    peak[1]=0;
    peakV = 0;
    peakBin = 0;      
  }     
}

int PerimeterClass::getFilterBinCount(){
  return FFTBINS/2;
}

int PerimeterClass::getFilterBin(){
  return BANDPASS_BIN;
}
  
double PerimeterClass::getFilterBandwidth(){
  return BIN_BANDWIDTH;
}


void PerimeterClass::printResults(){
  Serial.print(" fpeak=");
  Serial.print((int)(peakBin * BIN_BANDWIDTH));
  Serial.print(" fmin=");
  Serial.print((int)(BANDPASS_BIN * BIN_BANDWIDTH));
  Serial.print(" fmax=");
  Serial.print( ((int)((BANDPASS_BIN+1) * BIN_BANDWIDTH)) -1);
  Serial.print(" sum=");
  int sum = peak[0] + peak[1];
  Serial.print(sum);
  Serial.print("  peak0=");
  Serial.print(peak[0]);
  Serial.print("  peak1=");
  Serial.print(peak[1]);            
  Serial.println();    
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
void PerimeterClass::convFilter(int8_t *H, int16_t M, int8_t *ip, int16_t *op, int16_t nPts){  
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




