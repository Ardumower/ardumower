#include "flashmem.h"
#include "drivers.h"
#include "config.h"

#ifdef __AVR__
  #include <EEPROM.h>
#else
#endif  

// size we use (actual size is 4K)
#define EEPROM_SIZE 1024

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
	for (int i=0; i < EEPROM_SIZE; i++){ // test 1024 addresses
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
  Console.print(F("EEPROM dump (for backup): "));
  Console.print(EEPROM_SIZE);
  Console.println(F(" bytes (excluding checksum)"));
  byte sum = 0;
  char tmp[16];        
  for (int i=0; i < EEPROM_SIZE; i++){    
    byte v = read(i);        
    sprintf(tmp, "%.2X,", v);
    Console.print(tmp);        
    sum += v;
  }
  sprintf(tmp, "%.2X", sum);
  Console.print(tmp);    
  Console.println();
}


void FlashClass::restore(){
  Console.println(F("EEPROM restore: please send EEPROM backup string..."));
  String s = "";
  // wait until serial FIFO is empty
  while (Console.available()) {
    while (Console.available()) Console.read();              
    delay(500);
  }
  while (!Console.available());    
  s = Console.readString();    
  //Console.print(F("received data: ")); 
  //Console.println(s);
  // find out number of bytes received
  int count = 0;  
  for (int i=0; i < s.length(); i++) {
    if ( (s[i] == ' ') || (s[i] == '\r') ||  (s[i] == '\n') ) break;
    count++;
  }
  int sz = (count-2)/3;
  Console.print(F("bytes received (excluding checksum): "));    
  Console.println(sz);      
  if (sz < 4) {
    Console.println(F("error: not enough data"));
    return;
  }
  // calculate checksum
  Console.print(F("calculated checksum: "));
  byte calcsum = 0;  
  for (int i=0; i < sz; i++) {
    String c = s.substring(i*3,i*3+3);    
    byte v = strtol(c.c_str(), NULL, 16);  
    calcsum += v;
  }
  Console.print(calcsum);        
  // verify checksum
  Console.print(F("  received checksum: "));    
  String c = s.substring(sz*3,sz*3+3);  
  long sum = strtol(c.c_str(), NULL, 16);  
  Console.println(sum);
  if (sum != calcsum) {
    Console.println(F("error: checksum incorrect"));    
    return;
  }
  // save data to EEPROM
  Console.print(F("saving data to EEPROM..."));
  for (int i=0; i < sz; i++) {
    String c = s.substring(i*3,i*3+3);    
    byte v = strtol(c.c_str(), NULL, 16);  
    write(i, v);
  }
  Console.println(F("DONE! please restart system"));
}


boolean FlashClass::write(uint32_t address, byte value) {  
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




