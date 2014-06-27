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

#ifndef __AVR__
  #include <chip.h>
#endif
#include <Arduino.h>
#include <limits.h>
#include "adcman.h"

#define CHANNELS 10
#define NO_CHANNEL 255

volatile uint8_t calibrateChannel = NO_CHANNEL;
volatile double calibrateMin = 0;
volatile double calibrateMax = 0;
volatile short position = 0;
volatile uint8_t channel = 0;
volatile boolean busy = false;
int8_t *capture[CHANNELS]; // ADC capture buffer (ADC0-ADC7) - 8 bit signed (signed: zero = ADC/2)     
uint8_t captureSize[CHANNELS]; // ADC sample buffer size (ADC0-ADC7)
int16_t ofs[CHANNELS]; // ADC zero offset (ADC0-ADC7)
boolean captureComplete[CHANNELS]; // ADC buffer filled?
uint16_t sample[CHANNELS];   // ADC one sample (ADC0-ADC7) - 10 bit unsigned
ADCManager ADCMan;


ADCManager::ADCManager(){
  for (int i=0; i < CHANNELS; i++) {
    captureSize[i]=0;
    ofs[i]=0;
    captureComplete[i]=false;
    capture[i] = NULL;
  }
  capturedChannels = 0;
}

void ADCManager::init(){    
#ifndef __AVR__
  // free running ADC mode, f = ( adclock / 21 cycles per conversion )
  // using ADCCLK=405797 will result in a adcclock=403846 (due to adc_init internal conversion)
  // f = 19230,7619047619  Hz
  #define ADCCLK 405797      
  adc_init(ADC, SystemCoreClock, ADCCLK, ADC_STARTUP_FAST); // startup=768 clocks
  adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);  // tracking=0, settling=17, transfer=1    
  ADC->ADC_MR |= ADC_MR_FREERUN_ON;   // free running  
  NVIC_EnableIRQ(ADC_IRQn);    
#endif
  delay(500); // wait for ADCRef to settle (stable ADCRef required for later calibration)
}

void ADCManager::setCapture(byte pin, byte samplecount, boolean autoCalibrateOfs){
  int ch = pin-A0;
  captureSize[ch] = samplecount;
  capture[ch] = new int8_t[samplecount]; 
  if (autoCalibrateOfs) calibrateOfs(pin);
}

void ADCManager::calibrateOfs(byte pin){
  int ch = pin-A0;
  calibrateMin = 9999;
  calibrateMax = -9999;
  calibrateChannel = ch;  
  while (!isCaptureComplete(pin)) {
    delay(20);
    run();
  }  
  calibrateChannel = NO_CHANNEL;
  if (captureSize[ch] == 1) ofs[ch] = sample[ch];
    else {      
      double center = calibrateMin + (calibrateMax - calibrateMin) / 2.0;
      ofs[ch] = center;
    }
  Serial.print("ADC");
  Serial.print(ch);
  Serial.print("ofs=");    
  Serial.println(ofs[ch]);
}


void startADC(boolean fast){
#ifdef __AVR__
  /*  REFS0 : VCC use as a ref, IR_AUDIO : channel selection, ADEN : ADC Enable, ADSC : ADC Start, ADATE : ADC Auto Trigger Enable, ADIE : ADC Interrupt Enable,  ADPS : ADC Prescaler  */
  // free running ADC mode, f = ( 16MHz / prescaler ) / 13 cycles per conversion 
  ADMUX = _BV(REFS0) | channel; // | _BV(ADLAR); 
  if (fast)
    ADCSRA = _BV(ADSC) | _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1); //prescaler 64 : 19231 Hz 
  else // slow but accurate
    ADCSRA = _BV(ADSC) | _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // prescaler 128 : 9615 Hz
  //sei();   
#else 
  adc_enable_channel( ADC, (adc_channel_num_t)g_APinDescription[A0+channel].ulADCChannelNumber  ); 
  adc_enable_interrupt(ADC, ADC_IER_DRDY);  
  adc_start( ADC );  
#endif      
}
  
void ADCManager::startCapture(boolean fast){
  //Serial.print("starting capture ch");
  //Serial.println(channel);
  position = 0;
  busy=true;
  startADC(fast);  
}

#ifdef __AVR__
// free running ADC fills capture buffer
ISR(ADC_vect){
  volatile int16_t value = ADC;  
  if (!busy) return;
  if (position >= captureSize[channel]){
    // stop capture
    captureComplete[channel]=true;    
    busy=false;
    return;
  } 
  if (channel == calibrateChannel){  
      if (value < calibrateMin) calibrateMin = value; //0.5 * calibrateMin + 0.5 * ((double)value);
      if (value > calibrateMax) calibrateMax = value; //0.5 * calibrateMax + 0.5 * ((double)value);    
  } else {
    value -= ofs[channel];        
    capture[channel][position] =  min(SCHAR_MAX,  max(SCHAR_MIN, value / 4));   // convert to signed (zero = ADC/2)         
    //capture[channel][position] =  min(30,  max(-30, value / 4));   // convert to signed (zero = ADC/2)         
  }
  sample[channel] = value; 
  position++;
}
#else
void ADC_Handler(void){   
  if ((adc_get_status(ADC) & ADC_ISR_DRDY) == ADC_ISR_DRDY){
    volatile int16_t value = adc_get_latest_value(ADC) >> 2;     
    if (!busy) return;
    if (position >= captureSize[channel]){
      // stop capture
      captureComplete[channel]=true;    
      busy=false;
      return;
    }      
    if (channel == calibrateChannel){  
      if (value < calibrateMin) calibrateMin = value;// 0.5 * calibrateMin + 0.5 * ((double)value);
      if (value > calibrateMax) calibrateMax = value; //0.5 * calibrateMax + 0.5 * ((double)value);    
    } else {
      value -= ofs[channel];        
      capture[channel][position] =  min(SCHAR_MAX,  max(SCHAR_MIN, value / 4));   // convert to signed (zero = ADC/2)         
    }      
    sample[channel] = value;           
    position++;
  }
}
#endif

void ADCManager::stopCapture(){  
  //Serial.print("stopping capture ch");
  //Serial.println(channel);  
  position = 0;
#ifdef __AVR__  
  ADCSRA &= ~_BV(ADEN);
#else  
  adc_disable_channel(ADC, (adc_channel_num_t)g_APinDescription[A0+channel].ulADCChannelNumber );
  adc_disable_interrupt(ADC, 0xFFFFFFFF); // Disable all ADC interrupts.
#endif
}


void ADCManager::run(){
  //return;
  if (busy) {
    //Serial.print("busy pos=");
    //Serial.println(position);
    return;
  }
  if (position != 0){
    // stop free running
    stopCapture();
    capturedChannels++;
  }
  // find next channel for capturing
  for (int i=0; i < CHANNELS; i++){    
    channel++;
    if (channel == CHANNELS) channel = 0;
    if ((captureSize[channel] != 0) && (!captureComplete[channel])){        
      // found channel for sampling
      boolean fast = (captureSize[channel] != 1); // use slow but accurate sampling if one sample only
      startCapture( fast );        
      /*} 
        // one sample capture (slow but more accurate)
        delayMicroseconds(100); // required to get accurate measurement
        sample[channel] = analogRead(A0 + channel);
        captureComplete[channel]=true;    
        capturedChannels++;
      } */     
      break;
    }      
  }
}


int8_t* ADCManager::getCapture(byte pin){
  /*channel = ch;
  startCapture();
  while (busy) delay(2);
  stopCapture();*/
  return (int8_t*)capture[pin-A0];
}

boolean ADCManager::isCaptureComplete(byte pin){
  int ch = pin-A0;
  return captureComplete[ch];      
}

int ADCManager::read(byte pin){    
  int ch = pin-A0;
  captureComplete[ch]=false;    
  if (captureSize[ch] == 0) return 0;
    else if (captureSize[ch] == 1) return sample[ch];
    else return capture[ch][0];  
}

void ADCManager::restart(byte pin){
  captureComplete[pin-A0]=false;
}
        
int ADCManager::getCapturedChannels(){
  int res = capturedChannels;
  capturedChannels=0;
  return res;
}



