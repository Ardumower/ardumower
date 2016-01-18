/**
 * The 'COOL SAA1064 LIB'.
 *
 * An arduino library driving the NXP SAA1064 IC in a comfortable way.
 *
 * SAA1064 saa1064;
 * saa1064.scrollCooLSAA1064( );
 *
 * author:  Christian Scheiblich
 * email:   cscheiblich@gmail.com
 * license: Apache V 2.0, Jan 2004
 * created: 24.01.2014
 * edited:  15.02.2014
 * version: 0.93
 *
 * Necessary wiring for this library:
 *
 * 7-Segment:  a -> SAA1064: P1 and/or  P9 (pin: 10 and/or 15)
 * 7-Segment:  b -> SAA1064: P2 and/or P10 (pin:  9 and/or 16)
 * 7-Segment:  c -> SAA1064: P3 and/or P11 (pin:  8 and/or 17)
 * 7-Segment:  d -> SAA1064: P4 and/or P12 (pin:  7 and/or 18)
 * 7-Segment:  e -> SAA1064: P5 and/or P13 (pin:  6 and/or 19)
 * 7-Segment:  f -> SAA1064: P6 and/or P14 (pin:  5 and/or 20)
 * 7-Segment:  g -> SAA1064: P7 and/or P15 (pin:  4 and/or 21)
 * 7-Segment: dp -> SAA1064: P8 and/or P16 (pin:  3 and/or 22)
 *
 *             P1/P9
 *            -------
 *           |   a   |
 *    P6/P14 | f   b | P2/P10
 *           | P7/P15|
 *            -------
 *           |   g   |
 *    P5/P13 | e   c | P3/P11
 *           |   d   |
 *            -------. dp P8/P16
 *             P4/P12
 *
 * How to calculate a digits is easy due to clean mapping:
 *
 * a:  2^0 = 1
 * b:  2^1 = 2
 * c:  2^2 = 4
 * d:  2^3 = 8
 * e:  2^4 = 16
 * f:  2^5 = 32
 * g:  2^6 = 64
 * dp: 2^7 = 128
 *
 * digit '7': a + b + c  = 1 + 2 + 4 = 7
 * digit '4': b + c + f + g = 2 + 4 + 32 + 64 = 38
 * digit 'b': c + d + e + f + g = 4 + 8 + 16 + 32 + 64 = 124
 * ... see '_init( )' method in .cpp file for more!
 *
 * Pin 1: Wire it to ground (should work with IC2 address 0x70 >> 1)
 * Pin 2: Wire a 2 .. 3 nF capacitor to ground; even 10 nF works
 *
 * Pin  1: Wire to ground (should work with IC2 address 0x70 >> 1)
 * Pin  2: Wire a 2 .. 3 nF capacitor to ground; even 10 nF works
 * Pin 11: Wire to any NPN-type transistor like N2222; I used: 2N 3704 
 * Pin 12: VEE - Ground; should be 0 Volts
 * Pin 13: VCC - 5 Volts
 * Pin 14: Wire to any NPN-type transistor like N2222; I used: 2N 3704
 * Pin 23: SDA of I2C bus; I added 1k Ohm pull up resistor to VCC
 * Pin 24: SCL of I2C bus; I added 1k Ohm pull up resistor to VCC
 * 
 * Control Bytes:
 *
 * B00000000 - is send to mark that the next byte is a control byte:
 *
 * B00011000 - all segments on for test, 3 mA segment current - dark
 * B00101000 - all segments on for test, 6 mA segment current - normal
 * B01001000 - all segments on for test, 12 mA segment current - bright
 * B01000110 - static mode on, digit 1, digit 2 on, 12mA segment current
 * B01000111 - dynamic mode on, digit 1+3, digit 2+4 on, 12mA segment current
 *
 */

/**************************************80**************************************/

#ifndef cool_SAA1064_h
#define cool_SAA1064_h

/**************************************80**************************************/

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**************************************80**************************************/

class SAA1064 {

 public:

  SAA1064( void ); // constructor
  SAA1064( byte i2cAddress ); // constructor
  
  ~SAA1064( void ); // destructor
  
  void set( byte controlByte ); // to your own control byte; look at text above
  void setTest( void ); // switch all segemtns on for testing them
  void setStatic( void ); // to a default mode; static 2 digits, 18 mA
  void setDynamic( void ); // to a default mode; dynamic 4 digits, 18 mA
  
  void setDark( void ); // set to output currents 3 mA
  void setNormal( void ); // set to output currents 12 mA
  void setBright( void ); //  set to output currents 21 mA
  void setIntensity( int intensity ); // sets the intensity from 1 .. 7 - min .. max
  
  void clear( void ); // switch off all segments
  
  void say( int h4, int h3, int  h2, int h1 ); // update display by hex 0 .. 15 ( .. F ) and -1 is blank
  void say( byte b4, byte b3, byte b2, byte b1 ); // update display by bytes
  void say( int h, int digit ); // say byte on single digit: 0, 1, 2 or 3
  void say( byte b, int digit ); // say byte on single digit: 0, 1, 2 or 3
  void say( int number ); // say a number 0 .. 9999 : 42 => 42
  void sayDP( int number, int dp ); // say a number 0 .. 9999 : 42 => 42 with DP on digit 1-4
  void sayDP( int h4, int h3, int  h2, int h1, int dp ); // update display by hex 0 .. 15 ( .. F ) and -1 is blank
  void sayDP( int h, int digit, int dp ); // say byte on single digit: 0, 1, 2 or 3 , 1 = DP on 0 = DP off
  void sayDPminus( int number, int dp );
  void sayByZero( int number ); // say a number 0 .. 9999 : 42 => 0042

  void scroll( int* arrDigits, int arrDigitsLength, int milliSeconds ); // scroll right to left
  void scrollCooLSAA1064( void ); // scroll 'CooL SAA1064 8-]' from right to left
  
  void amplitude( int level ); // display an amplitude by level form 0 .. 7 
  
  void sayTime( int hour, int minute ); // displays the time
  void sayDate( int day, int month ); // displays the date
  void sayDateUS( int day, int month ); // displays the date, flipped position
  void sayYear( int year ); // say year in four digits
  void scrollTime( int hour, int minute, int second, int milliSeconds ); // scroll right to left
  void scrollDate( int day, int month, int year, int milliSeconds ); // scroll right to left

  void sayCooL( void ); // displays the word CooL
  void sayOooh( void ); // displays the word Oooh
  void sayUuuh( void ); // displays the word Uuuh
  void sayAAAh( void ); // displays the word AAAh
  void sayHAhA( void ); // displays the word HAhA
  void sayJAJA( void ); // displays the word JAJA
  void sayFoo( void ); // displays the word Foo
  void saybAr( void ); // displays the word bAr
  
  void saySmiley( void ); // displays a smiley 8-]
    
  void byteAll( void ); // bytes through all segements by a loop 
    
  void sayArrDigits( void ); // show the member _arrDigits with stored codes.
  
 private:
 
  void _init( void ); // sets the MAPPING TABLE (number to bytes) FOR the used WIRING
  
  void _set( byte controlByte ); // set a control byte and keep it in mind
  
  void _say( byte b4, byte b3, byte b2, byte b1 ); // update display by bytes

  void _say( byte b, int digit ); // say byte on single digit: 0, 1, 2 or 3

  void _splitNum2Dig( int number, int* digits ); // and returns an array of length 4; allocated before !!!

  byte _i2cAddress; // set in costructor to 0x70 >> 1
  
  byte _controlByte; // The byte the configures the SAA1064 chip
  
  byte* _arrDigits; // set in constructor
  int _arrDigitsLength; // length of 
  
}; // SAA1064

/**************************************80**************************************/

#endif // cool_SAA1064_h

/**************************************80**************************************/