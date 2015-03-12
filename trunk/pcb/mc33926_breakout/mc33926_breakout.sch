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
LIBS:mc33926_breakout_conn
LIBS:mc33926_ic
LIBS:mc33926_breakout-cache
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
L MC33926_IC U?
U 1 1 550205D0
P 5450 2400
F 0 "U?" H 5450 3650 60  0000 C CNN
F 1 "MC33926_IC" H 5500 1200 60  0000 C CNN
F 2 "" H 5250 2850 60  0000 C CNN
F 3 "" H 5250 2850 60  0000 C CNN
	1    5450 2400
	1    0    0    -1  
$EndComp
$Comp
L MC33926_IC U?
U 1 1 55020638
P 5450 5950
F 0 "U?" H 5450 7200 60  0000 C CNN
F 1 "MC33926_IC" H 5500 4750 60  0000 C CNN
F 2 "" H 5250 6400 60  0000 C CNN
F 3 "" H 5250 6400 60  0000 C CNN
	1    5450 5950
	1    0    0    -1  
$EndComp
$Comp
L MC33926_Conn U?
U 1 1 5501F2BE
P 1900 1900
F 0 "U?" H 1850 950 60  0000 C CNN
F 1 "MC33926_Conn" H 1870 3000 60  0000 C CNN
F 2 "" H 2050 1950 60  0000 C CNN
F 3 "" H 2050 1950 60  0000 C CNN
	1    1900 1900
	-1   0    0    1   
$EndComp
Text GLabel 6250 1150 1    60   Input ~ 0
VIN
Wire Wire Line
	6250 1600 6250 1150
Text GLabel 2750 1150 2    60   Output ~ 0
VIN
$Comp
L C C?
U 1 1 5502035D
P 6250 1750
F 0 "C?" H 6300 1850 50  0000 L CNN
F 1 "33nF" H 6300 1650 50  0000 L CNN
F 2 "" H 6288 1600 30  0000 C CNN
F 3 "" H 6250 1750 60  0000 C CNN
	1    6250 1750
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5502044D
P 4400 1050
F 0 "R?" V 4480 1050 50  0000 C CNN
F 1 "10k" V 4407 1051 50  0000 C CNN
F 2 "" V 4330 1050 30  0000 C CNN
F 3 "" H 4400 1050 30  0000 C CNN
	1    4400 1050
	-1   0    0    1   
$EndComp
Text GLabel 4400 800  1    60   Input ~ 0
Vdd
$Comp
L R R?
U 1 1 5502064D
P 4000 1300
F 0 "R?" V 4080 1300 50  0000 C CNN
F 1 "1k" V 4007 1301 50  0000 C CNN
F 2 "" V 3930 1300 30  0000 C CNN
F 3 "" H 4000 1300 30  0000 C CNN
	1    4000 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4250 1300 4650 1300
Connection ~ 4400 1300
$Comp
L R R?
U 1 1 55020712
P 4400 1450
F 0 "R?" V 4480 1450 50  0000 C CNN
F 1 "1k" V 4407 1451 50  0000 C CNN
F 2 "" V 4330 1450 30  0000 C CNN
F 3 "" H 4400 1450 30  0000 C CNN
	1    4400 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4150 1450 2750 1450
Wire Wire Line
	3750 1300 2950 1300
Wire Wire Line
	2950 1300 2950 1850
Wire Wire Line
	2950 1850 2750 1850
$Comp
L R R?
U 1 1 5502094F
P 3800 1550
F 0 "R?" V 3880 1550 50  0000 C CNN
F 1 "1k" V 3807 1551 50  0000 C CNN
F 2 "" V 3730 1550 30  0000 C CNN
F 3 "" H 3800 1550 30  0000 C CNN
	1    3800 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 1550 4050 1550
Wire Wire Line
	3550 1550 2750 1550
$Comp
L R R?
U 1 1 55020A17
P 4400 1700
F 0 "R?" V 4480 1700 50  0000 C CNN
F 1 "1k" V 4407 1701 50  0000 C CNN
F 2 "" V 4330 1700 30  0000 C CNN
F 3 "" H 4400 1700 30  0000 C CNN
	1    4400 1700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 1700 4150 1700
Wire Wire Line
	3050 1700 3050 1650
Wire Wire Line
	3050 1650 2750 1650
$Comp
L R R?
U 1 1 55020AC8
P 3550 1800
F 0 "R?" V 3630 1800 50  0000 C CNN
F 1 "1k" V 3557 1801 50  0000 C CNN
F 2 "" V 3480 1800 30  0000 C CNN
F 3 "" H 3550 1800 30  0000 C CNN
	1    3550 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 1800 3800 1800
Wire Wire Line
	3300 1800 3000 1800
Wire Wire Line
	3000 1800 3000 1750
Wire Wire Line
	3000 1750 2750 1750
$Comp
L R R?
U 1 1 55020B9B
P 3950 2050
F 0 "R?" V 4030 2050 50  0000 C CNN
F 1 "1k" V 3957 2051 50  0000 C CNN
F 2 "" V 3880 2050 30  0000 C CNN
F 3 "" H 3950 2050 30  0000 C CNN
	1    3950 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 2050 4200 2050
Wire Wire Line
	4650 1950 4450 1950
Wire Wire Line
	4450 1950 4450 2050
Connection ~ 4450 2050
Wire Wire Line
	3700 2050 2750 2050
$Comp
L R R?
U 1 1 55020D39
P 3600 2200
F 0 "R?" V 3680 2200 50  0000 C CNN
F 1 "1k" V 3607 2201 50  0000 C CNN
F 2 "" V 3530 2200 30  0000 C CNN
F 3 "" H 3600 2200 30  0000 C CNN
	1    3600 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 2200 3850 2200
Wire Wire Line
	3350 2200 3100 2200
Wire Wire Line
	3100 2200 3100 2150
Wire Wire Line
	3100 2150 2750 2150
$Comp
L R R?
U 1 1 55020EDC
P 4000 2300
F 0 "R?" V 4080 2300 50  0000 C CNN
F 1 "1k" V 4007 2301 50  0000 C CNN
F 2 "" V 3930 2300 30  0000 C CNN
F 3 "" H 4000 2300 30  0000 C CNN
	1    4000 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 2300 4250 2300
Wire Wire Line
	3750 2300 3000 2300
Wire Wire Line
	3000 2300 3000 2250
Wire Wire Line
	3000 2250 2750 2250
$Comp
L R R?
U 1 1 55020FE4
P 3600 2450
F 0 "R?" V 3680 2450 50  0000 C CNN
F 1 "1k" V 3607 2451 50  0000 C CNN
F 2 "" V 3530 2450 30  0000 C CNN
F 3 "" H 3600 2450 30  0000 C CNN
	1    3600 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 2450 3850 2450
Wire Wire Line
	3350 2450 3200 2450
Wire Wire Line
	3200 2450 3200 1950
Wire Wire Line
	3200 1950 2750 1950
$EndSCHEMATC
