#Makefile for ATmegaBOOT
# E.Lins, 18.7.2005
# $Id$


# program name should not be changed...
PROGRAM    = ATmegaBOOT

# enter the target CPU frequency
#AVR_FREQ   = 16000000L

MCU_TARGET = atmega644p
LDSECTION  = --section-start=.text=0x1F000

ISPFUSES    = avrdude -c $(ISPTOOL) -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
-e -u -U lock:w:0x3f:m -U efuse:w:0x$(EFUSE):m -U hfuse:w:0x$(HFUSE):m -U lfuse:w:0x$(LFUSE):m
ISPFLASH    = avrdude -c $(ISPTOOL) -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
-U flash:w:$(PROGRAM)_$(TARGET).hex -U lock:w:0x0f:m

STK500 = "C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"
STK500-1 = $(STK500) -e -d$(MCU_TARGET) -pf -vf -if$(PROGRAM)_$(TARGET).hex \
-lFF -LFF -f$(HFUSE)$(LFUSE) -EF8 -ms -q -cUSB -I200kHz -s -wt
STK500-2 = $(STK500) -d$(MCU_TARGET) -ms -q -lCF -LCF -cUSB -I200kHz -s -wt



OBJ        = $(PROGRAM).o
OPTIMIZE   = -Os

DEFS       = 
LIBS       = 

CC         = avr-gcc


# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS       = -Wl,$(LDSECTION)
#override LDFLAGS       = -Wl,-Map,$(PROGRAM).map,$(LDSECTION)

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

atmega644p: TARGET = atmega644p
atmega644p: MCU_TARGET = atmega644p
atmega644p: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=3' '-DBAUD_RATE=115200'
atmega644p: AVR_FREQ = 16000000L
atmega644p: LDSECTION  = --section-start=.text=0xF800
atmega644p: $(PROGRAM)_atmega644p.hex

atmega644p_isp: atmega644p
atmega644p_isp: TARGET = atmega644p
atmega644p_isp: MCU_TARGET = atmega644p
atmega644p_isp: HFUSE = DC
atmega644p_isp: LFUSE = FF
atmega644p_isp: EFUSE = FD
atmega644p_isp: isp



atmega1284p: TARGET = atmega1284p
atmega1284p: MCU_TARGET = atmega1284p
atmega1284p: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=3' '-DBAUD_RATE=115200'
atmega1284p: AVR_FREQ = 16000000L 
atmega1284p: LDSECTION  = --section-start=.text=0x1F000
atmega1284p: $(PROGRAM)_atmega1284p.hex

atmega1284p_isp: atmega1284p
atmega1284p_isp: TARGET = atmega1284p
atmega1284p_isp: MCU_TARGET = atmega1284p
atmega1284p_isp: HFUSE = DC
atmega1284p_isp: LFUSE = FF
atmega1284p_isp: EFUSE = FD
atmega1284p_isp: isp

atmega32: TARGET = atmega32
atmega32: MCU_TARGET = atmega32
atmega32: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=3' '-DBAUD_RATE=115200'
atmega32: AVR_FREQ ?= 16000000L
atmega32: LDSECTIONS  = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega32: $(PROGRAM)_atmega32.hex
atmega32: $(PROGRAM)_atmega32.lst

atmega32_isp: atmega32
atmega32_isp: TARGET = atmega32
atmega32_isp: MCU_TARGET = atmega32
# No OCD or JTAG, SPIEN, CKOPT (for full swing xtal), Bootsize=512B
atmega32_isp: HFUSE ?= CE
# 2.7V brownout, 16MHz Xtal, 16KCK/14CK+65ms
atemga32_isp: LFUSE ?= BF
atmega32_isp: isp


atmega16: TARGET = atmega16
atmega16: MCU_TARGET = atmega16
atmega16: CFLAGS += '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=3' '-DBAUD_RATE=115200'
atmega16: AVR_FREQ = 16000000L
atmega16: LDSECTIONS  = -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe
atmega16: $(PROGRAM)_atmega16.hex
atmega16: $(PROGRAM)_atmega16.lst

atmega16_isp: atmega16
atmega16_isp: TARGET = atmega16
atmega16_isp: MCU_TARGET = atmega16
# No OCD or JTAG, SPIEN, CKOPT (for full swing xtal), Bootsize=512B
atmega16_isp: HFUSE ?= DC
# 2.7V brownout, 16MHz Xtal, 16KCK/14CK+65ms
atmega16_isp: LFUSE ?= FF
atmega16_isp: isp








isp: $(TARGET)
	$(ISPFUSES)
	$(ISPFLASH)

isp-stk500: $(PROGRAM)_$(TARGET).hex
	$(STK500-1)
	$(STK500-2)

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@