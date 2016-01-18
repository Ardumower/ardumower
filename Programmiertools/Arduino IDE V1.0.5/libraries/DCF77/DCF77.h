#ifndef DCF77_h
#define DCF77_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include <Time.h>

#define MIN_TIME 1334102400     // Date: 11-4-2012
#define MAX_TIME 4102444800     // Date:  1-1-2100

#define DCFRejectionTime 700	// Pulse-to-Pulse rejection time. 
#define DCFRejectPulseWidth 50  // Minimal pulse width
#define DCFSplitTime 180		// Specifications distinguishes pulse width 100 ms and 200 ms. In practice we see 130 ms and 230
#define DCFSyncTime 1500		// Specifications defines 2000 ms pulse for end of sequence

class DCF77 {
private:

	//Private variables
	bool initialized;	
	static int dCF77Pin;
	static int dCFinterrupt;
	static byte pulseStart;

	// DCF77 and internal timestamps
	static time_t previousUpdatedTime;
	static time_t latestupdatedTime;           	
	static  time_t processingTimestamp;
	static  time_t previousProcessingTimestamp;		
	static unsigned char CEST;
	// DCF time format structure
	struct DCF77Buffer {
	  //unsigned long long prefix		:21;
	  unsigned long long prefix		:17;
	  unsigned long long CEST		:1; // CEST 
	  unsigned long long CET		:1; // CET 
	  unsigned long long unused		:2; // unused bits
	  unsigned long long Min		:7;	// minutes
	  unsigned long long P1			:1;	// parity minutes
	  unsigned long long Hour		:6;	// hours
	  unsigned long long P2			:1;	// parity hours
	  unsigned long long Day		:6;	// day
	  unsigned long long Weekday	:3;	// day of week
	  unsigned long long Month		:5;	// month
	  unsigned long long Year		:8;	// year (5 -> 2005)
	  unsigned long long P3			:1;	// parity
	};
	
	
	// DCF Parity format structure
	struct ParityFlags{
		unsigned char parityFlag	:1;
		unsigned char parityMin		:1;
		unsigned char parityHour	:1;
		unsigned char parityDate	:1;
	} static flags;

	// Parameters shared between interupt loop and main loop
	static volatile bool FilledBufferAvailable;
	static volatile unsigned long long filledBuffer;
	static volatile time_t filledTimestamp;

	// DCF Buffers and indicators
	static int  bufferPosition;
	static unsigned long long runningBuffer;
	static unsigned long long processingBuffer;

	// Pulse flanks
	static   int leadingEdge;
	static   int trailingEdge;
	static   int PreviousLeadingEdge;
	static   bool Up;
	
	//Private functions
	void static initialize(void);
	void static bufferinit(void);
	void static finalizeBuffer(void);
	static bool receivedTimeUpdate(void);
	void static storePreviousTime(void);
	void static calculateBufferParities(void);
	bool static processBuffer(void);
	void static appendSignal(unsigned char signal);

public:	
	// Public Functions
	DCF77(int DCF77Pin, int DCFinterrupt, bool OnRisingFlank=true); 
	
	static time_t getTime(void);
	static time_t getUTCTime(void);
	static void Start(void);
	static void Stop(void);
	static void int0handler();
 };

#endif

