#ifndef FLASHMEM_H
#define FLASHMEM_H

#include <Arduino.h>


class FlashClass
{
  public:
    boolean verboseOutput;
    FlashClass();
    byte read(uint32_t address);
    byte* readAddress(uint32_t address);
    boolean write(uint32_t address, byte value);
    boolean write(uint32_t address, byte *data, uint32_t dataLength);    
    void dump();
    void restore();
		void test();
};


extern FlashClass Flash;


template <class T> int eewrite(int &ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          Flash.write(ee++, *p++);
    return i;
}

template <class T> int eeread(int &ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = Flash.read(ee++);
    return i;
}

template <class T> int eereadwrite(boolean readflag, int &ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
    { 
       if (readflag) *p++ = Flash.read(ee++);
         else Flash.write(ee++, *p++);
    }
    return i;
}


int eereadwriteString(boolean readflag, int &ee, String& value);


#endif

