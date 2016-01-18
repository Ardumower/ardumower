#include "Utils.h"

namespace Utils {
	
#define DEBUG_BLINK_PIN 13	     // Connected to debug led
//#define VERBOSE_DEBUG 1	     // Verbose

	void LogLn(char*s)
	{
	#ifdef VERBOSE_DEBUG
		Serial.println(s);
	#endif
	}

	void Log(char*s)
	{
	#ifdef VERBOSE_DEBUG
	  Serial.print(s);
	#endif
	}
	void Log(int i,char format)
	{
	#ifdef VERBOSE_DEBUG
	  Serial.print(i, format);
	#endif
	}

	void LogLn(int i,char format)
	{
	#ifdef VERBOSE_DEBUG
	  Serial.println(i, format);
	#endif
	}

	void Log(int i)
	{
	#ifdef VERBOSE_DEBUG
	  Serial.print(i);
	#endif
	}

	void LogLn(int i)
	{
	#ifdef VERBOSE_DEBUG
	  Serial.println(i);
	#endif
	}
       
    void BlinkDebug(uint8_t state) {
    #ifdef DEBUG_BLINK_PIN
        digitalWrite(DEBUG_BLINK_PIN, state);
    #endif
	}
	
}
