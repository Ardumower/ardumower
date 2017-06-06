// pin manager
// replacement for Arduino wiring, allowing us to change PWM frequency

#ifndef PINMAN_H
#define PINMAN_H

#include <Arduino.h>

class PinManager {
  public:  
    void begin();
	  void analogWrite( uint32_t ulPin, uint32_t ulValue ) ;  
		void setDebounce(int pin, int usecs);  // reject spikes shorter than usecs on pin
};

extern PinManager PinMan;

#endif 

