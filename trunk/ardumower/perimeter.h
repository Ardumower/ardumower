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
perimeter receiver for Arduino sound sensors/LM386

-old version: digital filter: FFT bandpass - evaluates signal strength of certain frequency (7812 Hz) on two ADC pins (for two coils)
-new version: digital filter: matched filter - evaluates signal polarity of 'pulse3' signal on one ADC pin (for one coil)
 (for details see
    http://en.wikipedia.org/wiki/Matched_filter
    http://grauonline.de/alexwww/ardumower/filter/filter.html and bottom of this page
    http://www.ardumower.de/index.php/de/anleitungen/2013-11-23-19-50-19/induktion    )
*/

#ifndef PERIMETER_H
#define PERIMETER_H

#include <Arduino.h>

// choosen bandpass center frequency (f0) (Hz)
#define F_BANDPASS 7812
// ADC sampling rate (Hz) (has to match ADC setup further below)
#define F_SAMPLERATE 19231.0
// number of FFT bins (2^8 - see FFT call)
//#define FFTBINS 128
#define FFTBINS (48 * 5)
// bandwidth per FFT bin (75.12109375 Hz)
const double BIN_BANDWIDTH = ( F_SAMPLERATE / FFTBINS )  ;
const int BANDPASS_BIN = ( F_BANDPASS / BIN_BANDWIDTH + 0.5) ;



class PerimeterClass
{
  public:
    PerimeterClass();    
    void setPins(byte idx0Pin, byte idx1Pin);
    int getMagnitude(byte idx);    
    int getSmoothMagnitude();
    boolean isInside();
    boolean signalTimedOut();
    double getSignalMin();
    double getSignalMax();    
    double getSignalAvg();    
    int getSpectrum(int fftBin);        
    int getFilterBinCount();
    int getFilterBin();
    double getFilterBandwidth();    
  private:
    byte idxPin[2]; // channel for idx
    double peak[2];
    double mag [2]; // perimeter magnitude per channel
    double smoothMag;
    double signalMin;
    double signalMax;
    double signalAvg;
    double filterMinSmooth;
    double filterMaxSmooth;    
    int signalCounter;    
    unsigned long lastSignalTime;
    int peakBin;
    double peakV;    
    byte allmag[FFTBINS/2];
    unsigned long nextTime;
    void filterFrequencyMagnitude(byte idx);
    void matchedFilter(byte idx);
    void convFilter(int8_t *H, int16_t M, int8_t *ip, int16_t *op, int16_t nPts);
    void printResults();            
    void printADCMinMax(int8_t *samples);
    void gensignal();
};

extern PerimeterClass Perimeter;

#endif

