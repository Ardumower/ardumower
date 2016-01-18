#ifndef Utils_h
#define Utils_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include <Time.h>

#define intDisable()      ({ uint8_t sreg = SREG; cli(); sreg; })
#define intRestore(sreg)  SREG = sreg 

namespace Utils {	
	void Log(char*s);
	void LogLn(char*s);
	void Log(int i,char format);
	void LogLn(int i,char format);
	void Log(int i);
	void LogLn(int i);
	void BlinkDebug(uint8_t state);
}

#endif
