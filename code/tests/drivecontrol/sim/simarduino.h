// Arduino simulator

#ifndef SIMARDUINO_H
#define SIMARDUINO_H


#include <iostream>
#include <stdio.h> // for size_t
#include <string>
#include "Stream.h"



// flash string macro
#define F(x) x

// pin modes
enum {
  OUTPUT,
  INPUT,
};

// digital pin states
enum {
  LOW,
  HIGH,
};

class AConsole : public Stream
{
  public:
    virtual int available(){ return 0; }
    virtual int read(){ return 0; }
    virtual int peek(){ return 0; }
    virtual void flush(){}
    virtual size_t write(const uint8_t c){
      std::cout << c;
    }
    using Print::write; // pull in write(str) and write(buf, size) from Print
};

extern AConsole Console;


extern unsigned long millis(void);
extern unsigned long micros(void);
extern void pinMode(uint8_t pin, uint8_t mode);
extern void digitalWrite(uint8_t, uint8_t);

#endif
