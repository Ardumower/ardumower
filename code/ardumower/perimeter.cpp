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


#include "perimeter.h"
#include <Arduino.h>
#include <limits.h>
#include "adcman.h"
#include "drivers.h"
#include "config.h"

//#define pinLED 13                  

  
#if defined (SIGCODE_1)	
  int8_t sigcode[] = { 1, 1,-1,-1, 1,-1, 1,-1,-1,1, -1, 1, 1,-1,-1, 1,-1,-1, 1,-1,-1, 1, 1,-1 };
#elif defined (SIGCODE_2)   
  int8_t sigcode[] = { 1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1 };
#elif defined (SIGCODE_3)   
  int8_t sigcode[] = { 1, 1,-1,-1, 1,-1, 1, 1,-1, 1, 1,-1,-1, 1, 1,-1, 1,-1,-1, 1,-1,-1, 1,-1 };
#endif


Perimeter::Perimeter(){      
  // generate differential signal out of sender signal	
  int8_t lastValue = sigcode[sizeof sigcode-1];
  for (int i=0; i < sizeof sigcode; i++){
    int8_t value = sigcode[i];
    if (value == lastValue) sigcode[i] = 0;
      else sigcode[i] = value;
    lastValue = value;
  }  
	swapCoilPolarity = false;
  timedOutIfBelowSmag = 300;
  timeOutSecIfNotInside = 8;
  callCounter = 0;
  mag[0] = mag[1] = 0;
  smoothMag[0] = smoothMag[1] = 0;
  filterQuality[0] = filterQuality[1] = 0;
  signalCounter[0] = signalCounter[1] = 0;  
  lastInsideTime[0] = lastInsideTime[1] = 0;    
}

void Perimeter::setPins(byte idx0Pin, byte idx1Pin){
  idxPin[0] = idx0Pin;
  idxPin[1] = idx1Pin;  

  switch (ADCMan.sampleRate){
    case SRATE_9615: subSample = 1; break;
    case SRATE_19231: subSample = 2; break;
    case SRATE_38462: subSample = 4; break;
  }
  
  // use max. 255 samples and multiple of signalsize
  int adcSampleCount = sizeof sigcode * subSample;
  ADCMan.setCapture(idx0Pin, ((int)255 / adcSampleCount) * adcSampleCount, true); 
  ADCMan.setCapture(idx1Pin, ((int)255 / adcSampleCount) * adcSampleCount, true); 
 // ADCMan.setCapture(idx0Pin, adcSampleCount*2, true); 
 // ADCMan.setCapture(idx1Pin, adcSampleCount*2, true); 
  
  Console.print(F("matchSignal size="));
  Console.println(sizeof sigcode);  
  Console.print(F("subSample="));  
  Console.println((int)subSample);    
  Console.print(F("capture size="));
  Console.println(ADCMan.getCaptureSize(idx0Pin));  
	// print signal	 
  for (int i=0; i < sizeof sigcode; i++){
    Console.print(sigcode[i]);
    Console.print(F("\t"));
  }
  Console.println();
}

void Perimeter::speedTest(){
  int loops = 0;
  unsigned long endTime = millis() + 1000;
  while (millis() < endTime){
    matchedFilter(0);
    loops++;
  }
  Console.print(F("speedTest="));
  Console.println(loops);
}

const int8_t* Perimeter::getRawSignalSample(byte idx) {
  return rawSignalSample[idx];
}

int Perimeter::getMagnitude(byte idx){  
  if (ADCMan.isCaptureComplete(idxPin[idx])) {
    // Keep a sample of the raw signal
    memset(rawSignalSample[idx], 0, RAW_SIGNAL_SAMPLE_SIZE);
    memcpy(rawSignalSample[idx], ADCMan.getCapture(idxPin[idx]), min(ADCMan.getCaptureSize(idxPin[0]), RAW_SIGNAL_SAMPLE_SIZE));
    // Process signal
    matchedFilter(idx);
  }
  return mag[idx];
}

int Perimeter::getSmoothMagnitude(byte idx){  
  return smoothMag[idx];
}

void Perimeter::printADCMinMax(int8_t *samples){
  int8_t vmax = SCHAR_MIN;
  int8_t vmin = SCHAR_MAX;
  for (byte i=0; i < ADCMan.getCaptureSize(idxPin[0]); i++){
    vmax = max(vmax, samples[i]);
    vmin = min(vmin, samples[i]);
  }
  Console.print(F("perimter min,max="));
  Console.print((int)vmin);
  Console.print(F(","));
  Console.println((int)vmax);  
}

// perimeter V2 uses a digital matched filter
void Perimeter::matchedFilter(byte idx){
  int16_t sampleCount = ADCMan.getCaptureSize(idxPin[0]);
  int8_t *samples = ADCMan.getCapture(idxPin[idx]);    
  if (callCounter == 100) {
    // statistics only
    callCounter = 0;
    signalMin[idx] = 9999;
    signalMax[idx] = -9999;
    signalAvg[idx] = 0;  
    for (int i=0; i < sampleCount; i++){
      int8_t v = samples[i];
      signalAvg[idx] += v;
      signalMin[idx] = min(signalMin[idx], v);
      signalMax[idx] = max(signalMax[idx], v);
    }
    signalAvg[idx] = ((double)signalAvg[idx]) / ((double)(sampleCount));
  }
  // magnitude for tracking (fast but inaccurate)    
  int16_t sigcode_size = sizeof sigcode;  
  mag[idx] = corrFilter(sigcode, subSample, sigcode_size, samples, sampleCount-sigcode_size*subSample, filterQuality[idx]);
  if (swapCoilPolarity) mag[idx] *= -1;        
  // smoothed magnitude used for signal-off detection
  smoothMag[idx] = 0.99 * smoothMag[idx] + 0.01 * ((float)abs(mag[idx]));

  // perimeter inside/outside detection
  if (mag[idx] > 0){
    signalCounter[idx] = min(signalCounter[idx]+1, 3);    
  } else {
    signalCounter[idx] = max(signalCounter[idx]-1, -3);    
  }
  if (signalCounter[idx] < 0){
    lastInsideTime[idx] = millis();
  } 
    
  ADCMan.restart(idxPin[idx]);    
  if (idx == 0) callCounter++;
}

int16_t Perimeter::getSignalMin(byte idx){
  return signalMin[idx];
}

int16_t Perimeter::getSignalMax(byte idx){
  return signalMax[idx];
}

int16_t Perimeter::getSignalAvg(byte idx){
  return signalAvg[idx];
}


float Perimeter::getFilterQuality(byte idx){
  return filterQuality[idx];
}

boolean Perimeter::isInside(byte idx){
  if (abs(mag[idx]) > 1000) {
    // Large signal, the in/out detection is reliable.
    // Using mag yields very fast in/out transition reporting.
    return (mag[idx]<0);
  } else {
    // Low signal, use filtered value for increased reliability
    return (signalCounter[idx] < 0);
  }
}


boolean Perimeter::signalTimedOut(byte idx){
  if (getSmoothMagnitude(idx) < timedOutIfBelowSmag) return true;
  if (millis() - lastInsideTime[idx] > timeOutSecIfNotInside * 1000) return true;
  return false;
}


// digital matched filter (cross correlation)
// http://en.wikipedia.org/wiki/Cross-correlation
// H[] holds the double sided filter coeffs, M = H.length (number of points in FIR)
// subsample is the number of times for each filter coeff to repeat 
// ip[] holds input data (length > nPts + M )
// nPts is the length of the required output data 

int16_t Perimeter::corrFilter(int8_t *H, int8_t subsample, int16_t M, int8_t *ip, int16_t nPts, float &quality){  
  int16_t sumMax = 0; // max correlation sum
  int16_t sumMin = 0; // min correlation sum
  int16_t Ms = M * subsample; // number of filter coeffs including subsampling

  // compute sum of absolute filter coeffs
  int16_t Hsum = 0;
  for (int16_t i=0; i<M; i++) Hsum += abs(H[i]); 
  Hsum *= subsample;

  // compute correlation
  // for each input value
  for (int16_t j=0; j<nPts; j++)
  {
      int16_t sum = 0;      
      int8_t *Hi = H;
      int8_t ss = 0;
      int8_t *ipi = ip;      
      // for each filter coeffs
      for (int16_t i=0; i<Ms; i++)
      {        
        sum += ((int16_t)(*Hi)) * ((int16_t)(*ipi));
        ss++;
        if (ss == subsample) {
          ss=0;
          Hi++; // next filter coeffs
        }
        ipi++;
      }      
      if (sum > sumMax) sumMax = sum;
      if (sum < sumMin) sumMin = sum;
      ip++;
  }      
  // normalize to 4095
  sumMin = ((float)sumMin) / ((float)(Hsum*127)) * 4095.0;
  sumMax = ((float)sumMax) / ((float)(Hsum*127)) * 4095.0;
  
  // compute ratio min/max 
  if (sumMax > -sumMin) {
    quality = ((float)sumMax) / ((float)-sumMin);
    return sumMax;
  } else {
    quality = ((float)-sumMin) / ((float)sumMax);
    return sumMin;
  }  
}




