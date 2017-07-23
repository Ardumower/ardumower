#include "flashmem.h"
#include "drivers.h"
#include "config.h"

#ifdef __AVR__
  #include <EEPROM.h>
#else
#endif  


FlashClass Flash;


int eereadwriteString(boolean readflag, int &ee, String& value)
{
  unsigned int i;
  if (readflag) {
    value = "";
    char ch = Flash.read(ee++);
    while (ch) {
      value += ch;
      ch = Flash.read(ee++);
    }
  } else {
    for(i=0; i<value.length(); i++) {
      Flash.write(ee++, value.charAt(i));
    }
    Flash.write(ee++, 0);
  }
}


FlashClass::FlashClass() {
  verboseOutput = false;
#ifdef __AVR__  
#else
#endif
}


void FlashClass::test(){	  
	Console.println(F("EEPROM test - Please wait..."));
	bool success = true;
	for (int i=0; i < 1024; i++){ // test 1024 addresses
	  byte temp = read(i);	// read original value
    write(i, ((byte)i));  // write test value
	  byte v = read(i); // get test value
  	write(i, temp); // write back original value
	  if (v != ((byte)i)){ // incorrect read or write or both
	    Console.println(F("EEPROM error - RTC module missing?"));
			success = false;
			break;
		}		
	}
	if (success) Console.println(F("success!"));	
}

byte FlashClass::read(uint32_t address) {
#ifdef __AVR__  
  return EEPROM.read(address);
#else
	return readAT24C32(address);
#endif
}

byte* FlashClass::readAddress(uint32_t address) {
#ifdef __AVR__  
  byte d = EEPROM.read(address);
  return &d;
#else
	byte d = readAT24C32(address);
  return &d;
#endif
}

void FlashClass::dump(){
  Console.println(F("EEPROM dump"));
  for (int i=0; i < 1024; i++){
    byte v = read(i);
    if (v != 0){
      Console.print(i);
      Console.print(F("="));
      Console.print(v);
      Console.print(F(", "));
    }
  }
  Console.println();
}

boolean FlashClass::write(uint32_t address, byte value) {
  if (verboseOutput){
    Console.print(F("!76,"));
    Console.print(address);
    Console.print(F(","));
    Console.print(value);  
    Console.println();
  }
#ifdef __AVR__  
  EEPROM.write(address, value);
  return true;
#else  
	writeAT24C32(address, value);
  return true;
#endif  
}


boolean FlashClass::write(uint32_t address, byte *data, uint32_t dataLength) {
  for (int i=0; i < dataLength; i++){
    write(address + i, data[i]);
  }
  return true;
}




