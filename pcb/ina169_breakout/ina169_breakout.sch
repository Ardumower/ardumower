EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ina169_ic
LIBS:ina169_breakout_conn
LIBS:ina169_breakout-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L INA169_Breakout_Conn J1
U 1 1 54E30C13
P 2900 4200
F 0 "J1" H 2900 4600 60  0000 C CNN
F 1 "INA169_Breakout_Conn" H 2900 3750 60  0000 C CNN
F 2 "" H 3050 4400 60  0000 C CNN
F 3 "" H 3050 4400 60  0000 C CNN
	1    2900 4200
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54E30D69
P 4450 3200
F 0 "R2" V 4530 3200 50  0000 C CNN
F 1 "100K 1%" V 4457 3201 50  0000 C CNN
F 2 "" V 4380 3200 30  0000 C CNN
F 3 "" H 4450 3200 30  0000 C CNN
	1    4450 3200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54E30DE5
P 5450 3250
F 0 "R1" V 5530 3250 50  0000 C CNN
F 1 "0.1 1% 2W" V 5457 3251 50  0000 C CNN
F 2 "" V 5380 3250 30  0000 C CNN
F 3 "" H 5450 3250 30  0000 C CNN
	1    5450 3250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 54E30E61
P 4000 4500
F 0 "#PWR01" H 4000 4250 60  0001 C CNN
F 1 "GND" H 4000 4350 60  0000 C CNN
F 2 "" H 4000 4500 60  0000 C CNN
F 3 "" H 4000 4500 60  0000 C CNN
	1    4000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2400 4000 4500
Wire Wire Line
	4850 2400 4000 2400
Connection ~ 4000 4000
$Comp
L C C1
U 1 1 54E30F8E
P 6250 3400
F 0 "C1" H 6300 3500 50  0000 L CNN
F 1 "0.1uF" H 6300 3300 50  0000 L CNN
F 2 "" H 6288 3250 30  0000 C CNN
F 3 "" H 6250 3400 60  0000 C CNN
	1    6250 3400
	1    0    0    -1  
$EndComp
$Comp
L INA169_IC U1
U 1 1 54E31222
P 5400 2450
F 0 "U1" H 5400 2750 60  0000 C CNN
F 1 "INA169_IC" H 5400 2150 60  0000 C CNN
F 2 "" H 5400 2150 60  0000 C CNN
F 3 "" H 5400 2150 60  0000 C CNN
	1    5400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2300 6250 2300
Wire Wire Line
	6250 2050 6250 3200
$Comp
L GND #PWR02
U 1 1 54E31539
P 6250 4500
F 0 "#PWR02" H 6250 4250 60  0001 C CNN
F 1 "GND" H 6250 4350 60  0000 C CNN
F 2 "" H 6250 4500 60  0000 C CNN
F 3 "" H 6250 4500 60  0000 C CNN
	1    6250 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3600 6250 4500
Wire Wire Line
	4450 4000 3200 4000
Wire Wire Line
	4100 2500 4850 2500
Wire Wire Line
	4450 3450 4450 4000
Wire Wire Line
	5900 2500 5950 2500
Wire Wire Line
	5950 2500 5950 4300
Wire Wire Line
	4450 2300 4450 2950
Wire Wire Line
	4100 2500 4100 4200
Wire Wire Line
	4100 4200 3200 4200
Connection ~ 4800 2500
Wire Wire Line
	5950 4300 3200 4300
Connection ~ 5950 3250
Wire Wire Line
	4850 2300 3900 2300
Wire Wire Line
	3900 2300 3900 4100
Wire Wire Line
	3900 4100 3200 4100
Wire Wire Line
	6250 2050 3800 2050
Wire Wire Line
	3800 2050 3800 3900
Wire Wire Line
	3800 3900 3200 3900
Connection ~ 6250 2300
Connection ~ 4450 2300
Text Notes 5700 3410 2    60   ~ 0
Rshunt (RS)
Text Notes 4350 3550 1    60   ~ 0
Load resistor (RL)
Text Notes 2550 2750 0    60   ~ 0
INA169 DC Current Sensor \nVCC/Vin: 2.7-60V\nMax Current: 5A (1V/Amp)\nVout=RL/10K*I(Amps)
Wire Wire Line
	4800 2500 4800 3250
Wire Wire Line
	4800 3250 5200 3250
Wire Wire Line
	5950 3250 5700 3250
Wire Wire Line
	3200 4400 3350 4400
Wire Wire Line
	3350 4400 3350 4200
Connection ~ 3350 4200
Wire Wire Line
	3200 4500 3450 4500
Wire Wire Line
	3450 4500 3450 4300
Connection ~ 3450 4300
$EndSCHEMATC
