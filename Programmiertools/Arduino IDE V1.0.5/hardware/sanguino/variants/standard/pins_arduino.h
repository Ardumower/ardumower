#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

// version 1.0.1 dated 15 March 2014
// Added by Siddharth Sharangpani (sid@bhashatech.com)
// Added support for Atmega16A and Atmega32A
// also fixed a minor bug for Sanguino analog pins order
// order was correct, text descriptor nomenclature was incorrect
// if you spot any bug fixes please do drop me a mail with the fixes.


// ATMEL ATMEGA644P / SANGUINO / ATMEGA1284P/ ATMEGA16A / ATMEGA32A
//
//                   +---\/---+
//  INT0 (D 0) PB0  1|        |40  PA0 (AI 0 / D31)
//  INT1 (D 1) PB1  2|        |39  PA1 (AI 1 / D30)
//  INT2 (D 2) PB2  3|        |38  PA2 (AI 2 / D29)
//   PWM (D 3) PB3  4|        |37  PA3 (AI 3 / D28)
//   PWM (D 4) PB4  5|        |36  PA4 (AI 4 / D27)
//  MOSI (D 5) PB5  6|        |35  PA5 (AI 5 / D26)
//  MISO (D 6) PB6  7|        |34  PA6 (AI 6 / D25)
//   SCK (D 7) PB7  8|        |33  PA7 (AI 7 / D24)
//             RST  9|        |32  AREF
//             VCC 10|        |31  GND 
//             GND 11|        |30  AVCC
//           XTAL2 12|        |29  PC7 (D 23)
//           XTAL1 13|        |28  PC6 (D 22)
//  RX0 (D 8)  PD0 14|        |27  PC5 (D 21) TDI
//  TX0 (D 9)  PD1 15|        |26  PC4 (D 20) TDO
//  RX1 (D 10) PD2 16|        |25  PC3 (D 19) TMS
//  TX1 (D 11) PD3 17|        |24  PC2 (D 18) TCK
//  PWM (D 12) PD4 18|        |23  PC1 (D 17) SDA
//  PWM (D 13) PD5 19|        |22  PC0 (D 16) SCL
//  PWM (D 14) PD6 20|        |21  PD7 (D 15) PWM
//                   +--------+
//


/*
   PCINT15-8: D7-0  : bit 1
   PCINT31-24: D15-8  : bit 3
   PCINT23-16: D23-16 : bit 2
   PCINT7-0: D31-24   : bit 0
   */

#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 24 : -1)

#define digitalPinHasPWM(p)         ((p) == 4 || (p) == 5 || (p) == 6 || (p) == 7 || (p) == 11 || (p) == 12 || (p) == 14 || (p) == 15)

static const uint8_t SS   = 12;
static const uint8_t MOSI = 13;
static const uint8_t MISO = 14;
static const uint8_t SCK  = 15;

static const uint8_t SDA = 17;
static const uint8_t SCL = 16;
static const uint8_t LED = 12;

static const uint8_t A7 = 31;
static const uint8_t A6 = 30;
static const uint8_t A5 = 29;
static const uint8_t A4 = 28;
static const uint8_t A3 = 27;
static const uint8_t A2 = 26;
static const uint8_t A1 = 25;
static const uint8_t A0 = 24;

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 1 : (((p) <= 15) ? 3 : (((p) <= 23) ? 2 : 0)))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) ((p) % 8)

#ifdef ARDUINO_MAIN

#define PA 1
#define PB 2
#define PC 3
#define PD 4

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
	PD, /* 0 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB, /* 8 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PC, /* 16 */
	PC,
	PC,
	PC,
	PC,
	PC,
   	PC,
	PC,
	PA, /* 24 */
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA  /* 31 */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 16, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(7), /* 24, port A */
	_BV(6),
	_BV(5),
	_BV(4),
	_BV(3),
	_BV(2),
	_BV(1),
	_BV(0)
};

#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644P__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
	NOT_ON_TIMER, 	/* 0  - PD0 */
	NOT_ON_TIMER, 	/* 1  - PD1 */
	NOT_ON_TIMER, 	/* 2  - PD2 */
	NOT_ON_TIMER, 	/* 3  - PD3 */
	TIMER1B,     	/* 4  - PD4 */
	TIMER1A,     	/* 5  - PD5 */
	TIMER2B,     	/* 6  - PD6 */
	TIMER2A,     	/* 7  - PD7 */
	NOT_ON_TIMER, 	/* 8  - PB0 */
	NOT_ON_TIMER, 	/* 9  - PB1 */
	NOT_ON_TIMER, 	/* 10 - PB2 */
	TIMER0A,     	/* 11 - PB3 */
	TIMER0B, 		/* 12 - PB4 */
	NOT_ON_TIMER, 	/* 13 - PB5 */
	TIMER3A, 		/* 14 - PB6 */
	TIMER3B,		/* 15 - PB7 */
	NOT_ON_TIMER, 	/* 16 - PC0 */
	NOT_ON_TIMER,   /* 17 - PC1 */
	NOT_ON_TIMER,   /* 18 - PC2 */
	NOT_ON_TIMER,   /* 19 - PC3 */
	NOT_ON_TIMER,   /* 20 - PC4 */
	NOT_ON_TIMER,   /* 21 - PC5 */
	NOT_ON_TIMER,   /* 22 - PC6 */
	NOT_ON_TIMER,   /* 23 - PC7 */
	NOT_ON_TIMER,   /* 24 - PA7 */
	NOT_ON_TIMER,   /* 25 - PA6 */
	NOT_ON_TIMER,   /* 26 - PA5 */
	NOT_ON_TIMER,   /* 27 - PA4 */
	NOT_ON_TIMER,   /* 28 - PA3 */
	NOT_ON_TIMER,   /* 29 - PA2 */
	NOT_ON_TIMER,   /* 30 - PA1 */
	NOT_ON_TIMER   /* 31 - PA0 */
};
#else if defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
const uint8_t PROGMEM digital_pin_to_timer_PGM[32] = {
	NOT_ON_TIMER,  // PD0 ** D0
	NOT_ON_TIMER,  // PD1 ** D1
	NOT_ON_TIMER,  // PD2 ** D2
	NOT_ON_TIMER,  // PD3 ** D3
	TIMER1B,	   // PD4 ** D4
	TIMER1A,	   // PD5 ** D5
	NOT_ON_TIMER,  // PD6 ** D6
	TIMER2,		   // PD7 ** D7
	NOT_ON_TIMER,  // PB0 ** D8
	NOT_ON_TIMER,  // PB1 ** D9
	NOT_ON_TIMER,  // PB2 ** D10
	TIMER0A,	   // PB3 ** D11
	NOT_ON_TIMER,  // PB4 ** D12
	NOT_ON_TIMER,  // PB5 ** D13
	NOT_ON_TIMER,  // PB6 ** D14
	NOT_ON_TIMER,  // PB7 ** D15
	NOT_ON_TIMER,  // PC0 ** D16
	NOT_ON_TIMER,  // PC1 ** D17
	NOT_ON_TIMER,  // PC2 ** D18
	NOT_ON_TIMER,  // PC3 ** D19
	NOT_ON_TIMER,  // PC4 ** D20
	NOT_ON_TIMER,  // PC5 ** D21
	NOT_ON_TIMER,  // PC6 ** D22
	NOT_ON_TIMER,  // PC7 ** D23
	NOT_ON_TIMER,  // PA7 ** A0 D31
	NOT_ON_TIMER,  // PA6 ** A1 D30
	NOT_ON_TIMER,  // PA5 ** A2 D29
	NOT_ON_TIMER,  // PA4 ** A3 D28
	NOT_ON_TIMER,  // PA3 ** A4 D27
	NOT_ON_TIMER,  // PA2 ** A5 D26
	NOT_ON_TIMER,  // PA1 ** A6 D25
	NOT_ON_TIMER,  // PA0 ** A7 D24
};

#endif


#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h
// vim:ai:cin:sts=2 sw=2 ft=cpp
