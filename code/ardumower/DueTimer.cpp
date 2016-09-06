/*
  DueTimer.cpp - Implementation of Timers defined on DueTimer.h
  For instructions, go to https://github.com/ivanseidel/DueTimer

  Created by Ivan Seidel Gomes, March, 2013.
  Modified by Philipp Klaus, June 2013.
  Thanks to stimmer (from Arduino forum), for coding the "timer soul" (Register stuff)
  Released into the public domain.
*/

#include <Arduino.h>
#if defined(_SAM3XA_)
#include "DueTimer.h"

const DueTimer::Timer DueTimer::Timers[NUM_TIMERS] = {
	{TC0,0,TC0_IRQn},
	{TC0,1,TC1_IRQn},
	{TC0,2,TC2_IRQn},
	{TC1,0,TC3_IRQn},
	{TC1,1,TC4_IRQn},
	{TC1,2,TC5_IRQn},
	{TC2,0,TC6_IRQn},
	{TC2,1,TC7_IRQn},
	{TC2,2,TC8_IRQn},
};

// Fix for compatibility with Servo library
#ifdef USING_SERVO_LIB
	// Set callbacks as used, allowing DueTimer::getAvailable() to work
	void (*DueTimer::callbacks[NUM_TIMERS])() = {
		(void (*)()) 1, // Timer 0 - Occupied
		(void (*)()) 0, // Timer 1
		(void (*)()) 1, // Timer 2 - Occupied
		(void (*)()) 1, // Timer 3 - Occupied
		(void (*)()) 1, // Timer 4 - Occupied
		(void (*)()) 1, // Timer 5 - Occupied
		(void (*)()) 0, // Timer 6
		(void (*)()) 0, // Timer 7
		(void (*)()) 0  // Timer 8
	};
#else
	void (*DueTimer::callbacks[NUM_TIMERS])() = {};
#endif
double DueTimer::_frequency[NUM_TIMERS] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

/*
	Initializing all timers, so you can use them like this: Timer0.start();
*/
DueTimer Timer(0);

DueTimer Timer1(1);
// Fix for compatibility with Servo library
#ifndef USING_SERVO_LIB
	DueTimer Timer0(0);
	DueTimer Timer2(2);
	DueTimer Timer3(3);
	DueTimer Timer4(4);
	DueTimer Timer5(5);
#endif
DueTimer Timer6(6);
DueTimer Timer7(7);
DueTimer Timer8(8);

DueTimer::DueTimer(unsigned short _timer) : timer(_timer){
	/*
		The constructor of the class DueTimer 
	*/
}

DueTimer DueTimer::getAvailable(void){
	/*
		Return the first timer with no callback set
	*/

	for(int i = 0; i < NUM_TIMERS; i++){
		if(!callbacks[i])
			return DueTimer(i);
	}
	// Default, return Timer0;
	return DueTimer(0);
}

DueTimer& DueTimer::attachInterrupt(void (*isr)()){
	/*
		Links the function passed as argument to the timer of the object
	*/

	callbacks[timer] = isr;

	return *this;
}

DueTimer& DueTimer::detachInterrupt(void){
	/*
		Links the function passed as argument to the timer of the object
	*/

	stop(); // Stop the currently running timer

	callbacks[timer] = NULL;

	return *this;
}

DueTimer& DueTimer::start(long microseconds){
	/*
		Start the timer
		If a period is set, then sets the period and start the timer
	*/

	if(microseconds > 0)
		setPeriod(microseconds);
	
	if(_frequency[timer] <= 0)
		setFrequency(1);

	NVIC_ClearPendingIRQ(Timers[timer].irq);
	NVIC_EnableIRQ(Timers[timer].irq);
	
	TC_Start(Timers[timer].tc, Timers[timer].channel);

	return *this;
}

DueTimer& DueTimer::stop(void){
	/*
		Stop the timer
	*/

	NVIC_DisableIRQ(Timers[timer].irq);
	
	TC_Stop(Timers[timer].tc, Timers[timer].channel);

	return *this;
}

uint8_t DueTimer::bestClock(double frequency, uint32_t& retRC){
	/*
		Pick the best Clock, thanks to Ogle Basil Hall!

		Timer		Definition
		TIMER_CLOCK1	MCK /  2
		TIMER_CLOCK2	MCK /  8
		TIMER_CLOCK3	MCK / 32
		TIMER_CLOCK4	MCK /128
	*/
	const struct {
		uint8_t flag;
		uint8_t divisor;
	} clockConfig[] = {
		{ TC_CMR_TCCLKS_TIMER_CLOCK1,   2 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK2,   8 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK3,  32 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK4, 128 }
	};
	float ticks;
	float error;
	int clkId = 3;
	int bestClock = 3;
	float bestError = 9.999e99;
	do
	{
		ticks = (float) VARIANT_MCK / frequency / (float) clockConfig[clkId].divisor;
		// error = abs(ticks - round(ticks));
		error = clockConfig[clkId].divisor * abs(ticks - round(ticks));	// Error comparison needs scaling
		if (error < bestError)
		{
			bestClock = clkId;
			bestError = error;
		}
	} while (clkId-- > 0);
	ticks = (float) VARIANT_MCK / frequency / (float) clockConfig[bestClock].divisor;
	retRC = (uint32_t) round(ticks);
	return clockConfig[bestClock].flag;
}


DueTimer& DueTimer::setFrequency(double frequency){
	/*
		Set the timer frequency (in Hz)
	*/

	// Prevent negative frequencies
	if(frequency <= 0) { frequency = 1; }

	// Remember the frequency — see below how the exact frequency is reported instead
	//_frequency[timer] = frequency;

	// Get current timer configuration
	Timer t = Timers[timer];

	uint32_t rc = 0;
	uint8_t clock;

	// Tell the Power Management Controller to disable 
	// the write protection of the (Timer/Counter) registers:
	pmc_set_writeprotect(false);

	// Enable clock for the timer
	pmc_enable_periph_clk((uint32_t)t.irq);

	// Find the best clock for the wanted frequency
	clock = bestClock(frequency, rc);

	switch (clock) {
	  case TC_CMR_TCCLKS_TIMER_CLOCK1:
	    _frequency[timer] = (double)VARIANT_MCK / 2.0 / (double)rc;
	    break;
	  case TC_CMR_TCCLKS_TIMER_CLOCK2:
	    _frequency[timer] = (double)VARIANT_MCK / 8.0 / (double)rc;
	    break;
	  case TC_CMR_TCCLKS_TIMER_CLOCK3:
	    _frequency[timer] = (double)VARIANT_MCK / 32.0 / (double)rc;
	    break;
	  default: // TC_CMR_TCCLKS_TIMER_CLOCK4
	    _frequency[timer] = (double)VARIANT_MCK / 128.0 / (double)rc;
	    break;
	}

	// Set up the Timer in waveform mode which creates a PWM
	// in UP mode with automatic trigger on RC Compare
	// and sets it up with the determined internal clock as clock input.
	TC_Configure(t.tc, t.channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | clock);
	// Reset counter and fire interrupt when RC value is matched:
	TC_SetRC(t.tc, t.channel, rc);
	// Enable the RC Compare Interrupt...
	t.tc->TC_CHANNEL[t.channel].TC_IER=TC_IER_CPCS;
	// ... and disable all others.
	t.tc->TC_CHANNEL[t.channel].TC_IDR=~TC_IER_CPCS;

	return *this;
}

DueTimer& DueTimer::setPeriod(unsigned long microseconds){
	/*
		Set the period of the timer (in microseconds)
	*/

	// Convert period in microseconds to frequency in Hz
	double frequency = 1000000.0 / microseconds;	
	setFrequency(frequency);
	return *this;
}

double DueTimer::getFrequency(void) const {
	/*
		Get current time frequency
	*/

	return _frequency[timer];
}

long DueTimer::getPeriod(void) const {
	/*
		Get current time period
	*/

	return 1.0/getFrequency()*1000000;
}


/*
	Implementation of the timer callbacks defined in 
	arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/sam3xa/include/sam3x8e.h
*/
// Fix for compatibility with Servo library
#ifndef USING_SERVO_LIB
void TC0_Handler(void){
	TC_GetStatus(TC0, 0);
	DueTimer::callbacks[0]();
}
#endif
void TC1_Handler(void){
	TC_GetStatus(TC0, 1);
	DueTimer::callbacks[1]();
}
// Fix for compatibility with Servo library
#ifndef USING_SERVO_LIB
void TC2_Handler(void){
	TC_GetStatus(TC0, 2);
	DueTimer::callbacks[2]();
}
void TC3_Handler(void){
	TC_GetStatus(TC1, 0);
	DueTimer::callbacks[3]();
}
void TC4_Handler(void){
	TC_GetStatus(TC1, 1);
	DueTimer::callbacks[4]();
}
void TC5_Handler(void){
	TC_GetStatus(TC1, 2);
	DueTimer::callbacks[5]();
}
#endif
void TC6_Handler(void){
	TC_GetStatus(TC2, 0);
	DueTimer::callbacks[6]();
}
void TC7_Handler(void){
	TC_GetStatus(TC2, 1);
	DueTimer::callbacks[7]();
}
void TC8_Handler(void){
	TC_GetStatus(TC2, 2);
	DueTimer::callbacks[8]();
}
#endif
