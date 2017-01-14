EESchema Schematic File Version 2
LIBS:ina169_breakout-rescue
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
EELAYER 26 0
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
P 2850 4100
F 0 "J1" H 2850 4600 60  0000 C CNN
F 1 "INA169_Breakout_Conn" H 2850 3650 60  0000 C CNN
F 2 "ina169_breakout:ina169_breakout_footprint" H 3000 4300 60  0001 C CNN
F 3 "" H 3000 4300 60  0000 C CNN
	1    2850 4100
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-ina169_breakout R2
U 1 1 54E30D69
P 4200 2900
F 0 "R2" V 4110 2890 50  0000 C CNN
F 1 "10K 1%" V 4207 2901 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4130 2900 30  0001 C CNN
F 3 "" H 4200 2900 30  0000 C CNN
	1    4200 2900
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-ina169_breakout R1
U 1 1 54E30DE5
P 5450 3250
F 0 "R1" V 5530 3250 50  0000 C CNN
F 1 "0.1 1% 2W" V 5457 3251 50  0000 C CNN
F 2 "Resistors_SMD:R_2512" V 5380 3250 30  0001 C CNN
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
$Comp
L C-RESCUE-ina169_breakout C1
U 1 1 54E30F8E
P 6250 3400
F 0 "C1" H 6300 3500 50  0000 L CNN
F 1 "0.1uF" H 6300 3300 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 6288 3250 30  0001 C CNN
F 3 "" H 6250 3400 60  0000 C CNN
	1    6250 3400
	1    0    0    -1  
$EndComp
$Comp
L INA169_IC U1
U 1 1 54E31222
P 5440 2450
F 0 "U1" H 5440 2750 60  0000 C CNN
F 1 "INA169_IC" H 5440 2150 60  0000 C CNN
F 2 "ina169_breakout:ina169_ic_sot23-5" H 5440 2150 60  0001 C CNN
F 3 "" H 5440 2150 60  0000 C CNN
	1    5440 2450
	1    0    0    -1  
$EndComp
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
Text Notes 5850 3500 2    60   ~ 0
Rshunt (RS)\nSMD CRM2512-FX-R100ELF
Text Notes 4450 3350 1    60   ~ 0
Load resistor (RL)\nSMD-0603 10K
Text Notes 2550 2750 0    60   ~ 0
INA169 DC Current Sensor \nVCC/Vin: 2.7-60V\nMax Current: 5.0A (1V/Amp)\nVout=RL/10K*I(Amps)
Text Notes 6500 3400 0    60   ~ 0
SMD 12 X7R-G1206 100N
Text Notes 5200 2900 0    60   ~ 0
SOT23-5
Text Notes 6550 2850 0    60   ~ 0
http://de.wikipedia.org/wiki/Chip-Bauform
$Comp
L R-RESCUE-ina169_breakout R3
U 1 1 550174AC
P 4200 3700
F 0 "R3" V 4110 3690 50  0000 C CNN
F 1 "10K 1%" V 4207 3701 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4130 3700 30  0001 C CNN
F 3 "" H 4200 3700 30  0000 C CNN
	1    4200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2400 4000 4500
Wire Wire Line
	4890 2400 4000 2400
Connection ~ 4000 4000
Wire Wire Line
	5940 2300 6250 2300
Wire Wire Line
	6250 2050 6250 3200
Wire Wire Line
	6250 3600 6250 4500
Wire Wire Line
	3200 4000 4200 4000
Wire Wire Line
	4100 2500 4890 2500
Wire Wire Line
	5940 2500 5950 2500
Connection ~ 5950 3250
Wire Wire Line
	3900 2300 4890 2300
Wire Wire Line
	6250 2050 3800 2050
Wire Wire Line
	3800 2050 3800 3900
Wire Wire Line
	3800 3900 3200 3900
Connection ~ 6250 2300
Wire Wire Line
	4270 3250 5200 3250
Wire Wire Line
	5950 3250 5700 3250
Wire Wire Line
	5950 4100 3200 4100
Wire Wire Line
	5950 2500 5950 4100
Wire Wire Line
	3900 2300 3900 4300
Wire Wire Line
	3900 4300 3200 4300
Wire Wire Line
	4100 4200 3200 4200
Wire Wire Line
	4100 2500 4100 4200
Wire Wire Line
	4270 2500 4270 3250
Connection ~ 4270 2500
Wire Wire Line
	4200 3150 4200 3450
Wire Wire Line
	4200 4000 4200 3950
Wire Wire Line
	4200 2650 4200 2300
Connection ~ 4200 2300
$EndSCHEMATC
