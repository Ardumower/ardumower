// ---------------------------------------------------------------------------
// Created by Francisco Malpartida on 20/08/11.
// Copyright 2011 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
// Thread Safe: No
// Extendable: Yes
//
// @file SI2CIO.h
// This file implements a basic IO library using the PCF8574 I2C IO Expander
// chip, but using software I2C.
// 
// @brief 
// Implement a basic IO library to drive the PCF8574* I2C IO Expander ASIC.
// The library implements basic IO general methods to configure IO pin direction
// read and write uint8_t operations and basic pin level routines to set or read
// a particular IO port.
//
//
// @version API 1.0.0
//
// @author F. Malpartida - fmalpartida@gmail.com
// Adapted to SoftIC2 by Adrian Piccioli - adrianpiccioli@gmail.com
// ---------------------------------------------------------------------------
#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>

/*#define SCL_PIN 6
#define SCL_PORT PORTD
#define SDA_PIN 7
#define SDA_PORT PORTD*/

//#define I2C_FASTMODE 1 
//#define I2C_SLOWMODE 1 

#define SCL_PIN 0
#define SCL_PORT PORTB
#define SDA_PIN 1
#define SDA_PORT PORTB

#if defined (__AVR__)
#include "SI2CIO.h"
#include "SoftI2CMaster.h"


// CLASS VARIABLES
// ---------------------------------------------------------------------------


// CONSTRUCTOR
// ---------------------------------------------------------------------------
SI2CIO::SI2CIO ( )
{
   _i2cAddr     = 0x0;
   _dirMask     = 0xFF;    // mark all as INPUTs
   _shadow      = 0x0;     // no values set
   _initialised = false;
}

// PUBLIC METHODS
// ---------------------------------------------------------------------------

//
// begin
int SI2CIO::begin (  uint8_t i2cAddr )
{
   // convert to 8 bit addresses for mapping as needed by the bitbang library
   _i2cAddr = ( i2cAddr << 1 );
   
   i2c_init();
      
   _initialised = i2c_start(_i2cAddr | I2C_READ);

   _shadow = i2c_read(true);
   
   i2c_stop();
   
   return ( _initialised );
}

//
// pinMode
void SI2CIO::pinMode ( uint8_t pin, uint8_t dir )
{
   if ( _initialised )
   {
      if ( OUTPUT == dir )
      {
         _dirMask &= ~( 1 << pin );
      }
      else 
      {
         _dirMask |= ( 1 << pin );
      }
   }
}

//
// portMode
void SI2CIO::portMode ( uint8_t dir )
{
   
   if ( _initialised )
   {
      if ( dir == INPUT )
      {
         _dirMask = 0xFF;
      }
      else
      {
         _dirMask = 0x00;
      }
   }
}

//
// read
uint8_t SI2CIO::read ( void )
{
   uint8_t retVal = 0;
   
   if ( _initialised )
   {
      i2c_start(_i2cAddr | I2C_READ);
 
	  retVal = (_dirMask & i2c_read(true));
	  
	  i2c_stop();
   }
   return ( retVal );
}

//
// write
int SI2CIO::write ( uint8_t value )
{
   int status = 0;
   
   if ( _initialised )
   {
      // Only write HIGH the values of the ports that have been initialised as
      // outputs updating the output shadow of the device
      _shadow = ( value & ~(_dirMask) );
   
      status = i2c_start(_i2cAddr | I2C_WRITE);
 
	  status &= i2c_write(_shadow);
      
	  i2c_stop();
   }
   return ( (status == 0) );
}

//
// digitalRead
uint8_t SI2CIO::digitalRead ( uint8_t pin )
{
   uint8_t pinVal = 0;
   
   // Check if initialised and that the pin is within range of the device
   // -------------------------------------------------------------------
   if ( ( _initialised ) && ( pin <= 7 ) )
   {
      // Remove the values which are not inputs and get the value of the pin
      pinVal = this->read() & _dirMask;
      pinVal = ( pinVal >> pin ) & 0x01; // Get the pin value
   }
   return (pinVal);
}

//
// digitalWrite
int SI2CIO::digitalWrite ( uint8_t pin, uint8_t level )
{
   uint8_t writeVal;
   int status = 0;
   
   // Check if initialised and that the pin is within range of the device
   // -------------------------------------------------------------------
   if ( ( _initialised ) && ( pin <= 7 ) )
   {
      // Only write to HIGH the port if the port has been configured as
      // an OUTPUT pin. Add the new state of the pin to the shadow
      writeVal = ( 1 << pin ) & ~_dirMask;
      if ( level == HIGH )
      {
         _shadow |= writeVal; 
      }
      else 
      {
         _shadow &= ~writeVal;
      }
      status = this->write ( _shadow );
   }
   return ( status );
}

//
// PRIVATE METHODS
// ---------------------------------------------------------------------------
#else
#error "ONLY SUPPORTED ON AVR PROCESSORS"
#endif // __AVR__