EESchema Schematic File Version 2
LIBS:arduino_shieldsNCL
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
LIBS:Walter's
LIBS:ardumower mega shield V1.00-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Ardumower shield"
Date "4 jul 2014"
Rev "A"
Comp "Walter"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_MEGA_SHIELD SHIELD1
U 1 1 5375252C
P 5150 4850
F 0 "SHIELD1" H 5200 4900 60  0001 C CNN
F 1 "ARDUINO_MEGA_SHIELD" H 5150 4850 60  0001 C CNN
F 2 "" H 5150 4850 60  0000 C CNN
F 3 "" H 5150 4850 60  0001 C CNN
F 4 "SHIELD" H 4750 7350 60  0000 C CNN "Reference"
F 5 "ARDUINO_MEGA_SHIELD" H 5050 2150 60  0000 C CNN "Value"
F 6 "" H 5150 4850 60  0000 C CNN "Datasheet"
	1    5150 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 537FB5CA
P 6950 2000
F 0 "#PWR01" H 6950 2000 30  0001 C CNN
F 1 "GND" H 6950 1930 30  0001 C CNN
F 2 "" H 6950 2000 60  0000 C CNN
F 3 "" H 6950 2000 60  0000 C CNN
	1    6950 2000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 537FB5D9
P 9950 1600
F 0 "#PWR02" H 9950 1600 30  0001 C CNN
F 1 "GND" H 9950 1530 30  0001 C CNN
F 2 "" H 9950 1600 60  0000 C CNN
F 3 "" H 9950 1600 60  0000 C CNN
	1    9950 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 537FB5E8
P 3750 3350
F 0 "#PWR03" H 3750 3350 30  0001 C CNN
F 1 "GND" H 3750 3280 30  0001 C CNN
F 2 "" H 3750 3350 60  0000 C CNN
F 3 "" H 3750 3350 60  0000 C CNN
	1    3750 3350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 537FB637
P 10150 1200
F 0 "#PWR04" H 10150 1290 20  0001 C CNN
F 1 "+5V" H 10150 1290 30  0000 C CNN
F 2 "" H 10150 1200 60  0000 C CNN
F 3 "" H 10150 1200 60  0000 C CNN
	1    10150 1200
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR05
U 1 1 537FB675
P 6750 2050
F 0 "#PWR05" H 6750 2140 20  0001 C CNN
F 1 "+5V" H 6750 2140 30  0000 C CNN
F 2 "" H 6750 2050 60  0000 C CNN
F 3 "" H 6750 2050 60  0000 C CNN
	1    6750 2050
	1    0    0    -1  
$EndComp
NoConn ~ 7100 2450
$Comp
L JUMPER JP1
U 1 1 537FB697
P 9800 750
F 0 "JP1" H 9800 900 60  0000 C CNN
F 1 "JUMPER" H 9800 670 40  0000 C CNN
F 2 "~" H 9800 750 60  0000 C CNN
F 3 "~" H 9800 750 60  0000 C CNN
	1    9800 750 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 537FB6A6
P 9450 750
F 0 "#PWR06" H 9450 710 30  0001 C CNN
F 1 "+3.3V" H 9450 860 30  0000 C CNN
F 2 "" H 9450 750 60  0000 C CNN
F 3 "" H 9450 750 60  0000 C CNN
	1    9450 750 
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 537FB6F1
P 8150 1500
F 0 "D1" H 8150 1600 50  0000 C CNN
F 1 "LED" H 8150 1400 50  0000 C CNN
F 2 "~" H 8150 1500 60  0000 C CNN
F 3 "~" H 8150 1500 60  0000 C CNN
	1    8150 1500
	-1   0    0    1   
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 537FB700
P 8500 1200
F 0 "SW1" H 8650 1310 50  0000 C CNN
F 1 "SW_PUSH" H 8500 1120 50  0000 C CNN
F 2 "~" H 8500 1200 60  0000 C CNN
F 3 "~" H 8500 1200 60  0000 C CNN
	1    8500 1200
	1    0    0    -1  
$EndComp
$Comp
L SPEAKER SP1
U 1 1 537FB76E
P 7500 900
F 0 "SP1" H 7400 1150 70  0000 C CNN
F 1 "SPEAKER" H 7400 650 70  0000 C CNN
F 2 "~" H 7500 900 60  0000 C CNN
F 3 "~" H 7500 900 60  0000 C CNN
	1    7500 900 
	-1   0    0    1   
$EndComp
Text GLabel 6750 2350 0    60   Input ~ 0
SCL
Text GLabel 6750 2200 0    60   BiDi ~ 0
SDA
Text GLabel 6200 5050 2    60   Output ~ 0
SCL
Text GLabel 6200 4900 2    60   BiDi ~ 0
SDA
$Comp
L GND #PWR07
U 1 1 5384EC59
P 7800 1150
F 0 "#PWR07" H 7800 1150 30  0001 C CNN
F 1 "GND" H 7800 1080 30  0001 C CNN
F 2 "" H 7800 1150 60  0000 C CNN
F 3 "" H 7800 1150 60  0000 C CNN
	1    7800 1150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5384EC7E
P 8700 1500
F 0 "R1" V 8780 1500 40  0000 C CNN
F 1 "470R" V 8707 1501 40  0000 C CNN
F 2 "~" V 8630 1500 30  0000 C CNN
F 3 "~" H 8700 1500 30  0000 C CNN
	1    8700 1500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5384ECBD
P 7850 1500
F 0 "#PWR08" H 7850 1500 30  0001 C CNN
F 1 "GND" H 7850 1430 30  0001 C CNN
F 2 "" H 7850 1500 60  0000 C CNN
F 3 "" H 7850 1500 60  0000 C CNN
	1    7850 1500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 5384ECE6
P 8100 1200
F 0 "#PWR09" H 8100 1200 30  0001 C CNN
F 1 "GND" H 8100 1130 30  0001 C CNN
F 2 "" H 8100 1200 60  0000 C CNN
F 3 "" H 8100 1200 60  0000 C CNN
	1    8100 1200
	0    1    1    0   
$EndComp
$Comp
L CONN_4 P1
U 1 1 5384EE13
P 11000 4350
F 0 "P1" V 10950 4350 50  0000 C CNN
F 1 "Perimeter" V 11050 4350 50  0000 C CNN
F 2 "" H 11000 4350 60  0000 C CNN
F 3 "" H 11000 4350 60  0000 C CNN
	1    11000 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5384EE31
P 10450 4500
F 0 "#PWR010" H 10450 4500 30  0001 C CNN
F 1 "GND" H 10450 4430 30  0001 C CNN
F 2 "" H 10450 4500 60  0000 C CNN
F 3 "" H 10450 4500 60  0000 C CNN
	1    10450 4500
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR011
U 1 1 5384EE5E
P 10450 4200
F 0 "#PWR011" H 10450 4290 20  0001 C CNN
F 1 "+5V" H 10450 4290 30  0000 C CNN
F 2 "" H 10450 4200 60  0000 C CNN
F 3 "" H 10450 4200 60  0000 C CNN
	1    10450 4200
	0    -1   -1   0   
$EndComp
Text GLabel 10200 4400 0    60   Output ~ 0
Left perimeter
Text GLabel 10200 4200 0    60   Output ~ 0
Right perimeter
Text GLabel 3650 4250 0    60   Input ~ 0
Left perimeter
Text GLabel 3650 4100 0    60   Input ~ 0
Right perimeter
$Comp
L GND #PWR012
U 1 1 5384F323
P 4050 5350
F 0 "#PWR012" H 4050 5350 30  0001 C CNN
F 1 "GND" H 4050 5280 30  0001 C CNN
F 2 "" H 4050 5350 60  0000 C CNN
F 3 "" H 4050 5350 60  0000 C CNN
	1    4050 5350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR013
U 1 1 5384F385
P 6200 2600
F 0 "#PWR013" H 6200 2600 30  0001 C CNN
F 1 "GND" H 6200 2530 30  0001 C CNN
F 2 "" H 6200 2600 60  0000 C CNN
F 3 "" H 6200 2600 60  0000 C CNN
	1    6200 2600
	0    -1   -1   0   
$EndComp
$Comp
L CONN_6 P2
U 1 1 5384F587
P 11000 5100
F 0 "P2" V 10950 5100 60  0000 C CNN
F 1 "Motor driver" V 11050 5100 60  0000 C CNN
F 2 "" H 11000 5100 60  0000 C CNN
F 3 "" H 11000 5100 60  0000 C CNN
	1    11000 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5384F599
P 10450 4850
F 0 "#PWR014" H 10450 4850 30  0001 C CNN
F 1 "GND" H 10450 4780 30  0001 C CNN
F 2 "" H 10450 4850 60  0000 C CNN
F 3 "" H 10450 4850 60  0000 C CNN
	1    10450 4850
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR015
U 1 1 5384F5A8
P 10450 5350
F 0 "#PWR015" H 10450 5440 20  0001 C CNN
F 1 "+5V" H 10450 5440 30  0000 C CNN
F 2 "" H 10450 5350 60  0000 C CNN
F 3 "" H 10450 5350 60  0000 C CNN
	1    10450 5350
	0    -1   -1   0   
$EndComp
Text Label 9550 4700 2    60   ~ 0
DIR1
Text GLabel 10250 5300 0    60   Input ~ 0
MotorLeftDir
Text GLabel 10250 4850 0    60   Input ~ 0
MotorRightPWM
Text GLabel 10250 5150 0    60   Input ~ 0
MotorLeftPWM
Text GLabel 10250 5000 0    60   Input ~ 0
MotorRightDir
Text GLabel 6200 5550 2    60   Input ~ 0
MotorLeftDir
Text GLabel 6950 3800 2    60   Input ~ 0
MotorRightPWM
Text GLabel 6200 3600 2    60   Input ~ 0
MotorLeftPWM
Text GLabel 6200 5850 2    60   Input ~ 0
MotorRightDir
Text GLabel 6200 6850 2    60   Input ~ 0
Buzzer
Text GLabel 7950 800  2    60   Input ~ 0
Buzzer
Text GLabel 4000 5700 0    60   Input ~ 0
Button
Text GLabel 8800 1200 2    60   Input ~ 0
Button
Text GLabel 4000 6150 0    60   Input ~ 0
Led
Text GLabel 8950 1500 2    60   Input ~ 0
Led
Text GLabel 1350 3750 2    60   Input ~ 0
MotorMow
Text GLabel 1350 3950 2    60   Input ~ 0
MotorMowSense
Text GLabel 1350 4150 2    60   Input ~ 0
MotorMowRpm
Text GLabel 4000 7200 0    60   Input ~ 0
BumperLeft
Text GLabel 6200 7050 2    60   Input ~ 0
BumperRight
Text GLabel 1250 5500 2    60   Input ~ 0
SonarCenterTrigger
Text GLabel 1250 5700 2    60   Input ~ 0
SonarCenterEcho
Text GLabel 1250 6350 2    60   Input ~ 0
SonarRightTrigger
Text GLabel 1250 6550 2    60   Input ~ 0
SonarRightEcho
Text GLabel 1250 7200 2    60   Input ~ 0
SonarLeftTrigger
Text GLabel 1250 7400 2    60   Input ~ 0
SonarLeftEcho
Text GLabel 1350 3050 2    60   Input ~ 0
Tilt
Text GLabel 1350 4700 2    60   Input ~ 0
MotorLeftSense
Text GLabel 1350 4900 2    60   Input ~ 0
MotorRightSense
Text GLabel 3650 3800 0    60   Input ~ 0
BatteryVoltage
Text GLabel 3650 4450 0    60   Input ~ 0
ChargeVoltage
Text GLabel 3650 4600 0    60   Input ~ 0
ChargeCurrent
Text GLabel 10200 6550 0    60   Input ~ 0
UserSwitch1
Text GLabel 10200 6700 0    60   Input ~ 0
UserSwitch2
Text GLabel 10200 6850 0    60   Input ~ 0
UserSwitch3
Text GLabel 3650 4900 0    60   Input ~ 0
OdometryLeft2
Text GLabel 5450 950  2    60   Input ~ 0
OdometryRight2
Text GLabel 3650 5200 0    60   Input ~ 0
OdometryRight2
Text GLabel 6200 6450 2    60   Input ~ 0
LawnFrontRecv
Text GLabel 6200 6650 2    60   Input ~ 0
LawnFrontSend
Text GLabel 6200 6200 2    60   Input ~ 0
LawnBackRecv
Text GLabel 6200 6000 2    60   Input ~ 0
LawnBackSend
Text GLabel 1750 1250 2    60   Input ~ 0
ChargeVoltage
$Comp
L R R2
U 1 1 5384FFAC
P 1400 1250
F 0 "R2" V 1480 1250 40  0000 C CNN
F 1 "47K" V 1407 1251 40  0000 C CNN
F 2 "~" V 1330 1250 30  0000 C CNN
F 3 "~" H 1400 1250 30  0000 C CNN
	1    1400 1250
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 5384FFC0
P 1700 1600
F 0 "R3" V 1780 1600 40  0000 C CNN
F 1 "5K" V 1707 1601 40  0000 C CNN
F 2 "~" V 1630 1600 30  0000 C CNN
F 3 "~" H 1700 1600 30  0000 C CNN
	1    1700 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 53850044
P 1700 1850
F 0 "#PWR016" H 1700 1850 30  0001 C CNN
F 1 "GND" H 1700 1780 30  0001 C CNN
F 2 "" H 1700 1850 60  0000 C CNN
F 3 "" H 1700 1850 60  0000 C CNN
	1    1700 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3300 4150 3200
Wire Wire Line
	4150 3200 3750 3200
Wire Wire Line
	3750 3200 3750 3350
Wire Wire Line
	6200 4900 6050 4900
Wire Wire Line
	6200 5050 6050 5050
Wire Wire Line
	6050 5050 6050 5000
Wire Wire Line
	7800 1150 7800 1000
Wire Wire Line
	8450 1500 8350 1500
Wire Wire Line
	7850 1500 7950 1500
Wire Wire Line
	8100 1200 8200 1200
Wire Wire Line
	10650 4200 10450 4200
Wire Wire Line
	10650 4300 10250 4300
Wire Wire Line
	10250 4300 10250 4200
Wire Wire Line
	10250 4200 10200 4200
Wire Wire Line
	10200 4400 10650 4400
Wire Wire Line
	10650 4500 10450 4500
Wire Wire Line
	6050 2600 6200 2600
Wire Wire Line
	10650 4850 10450 4850
Wire Wire Line
	10450 5350 10650 5350
Wire Wire Line
	10650 4950 10350 4950
Wire Wire Line
	10350 4950 10350 4850
Wire Wire Line
	10350 4850 10250 4850
Wire Wire Line
	10650 5050 10300 5050
Wire Wire Line
	10300 5050 10300 5000
Wire Wire Line
	10300 5000 10250 5000
Wire Wire Line
	10650 5150 10250 5150
Wire Wire Line
	10650 5250 10300 5250
Wire Wire Line
	10300 5250 10300 5300
Wire Wire Line
	10300 5300 10250 5300
Wire Wire Line
	6050 3900 6200 3900
Wire Wire Line
	6050 3800 6950 3800
Wire Wire Line
	6050 6650 6200 6650
Wire Wire Line
	6200 6450 6050 6450
Wire Wire Line
	7950 800  7800 800 
$Comp
L GND #PWR017
U 1 1 5385017D
P 1200 1450
F 0 "#PWR017" H 1200 1450 30  0001 C CNN
F 1 "GND" H 1200 1380 30  0001 C CNN
F 2 "" H 1200 1450 60  0000 C CNN
F 3 "" H 1200 1450 60  0000 C CNN
	1    1200 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1650 1250 1750 1250
Wire Wire Line
	1700 1350 1700 1250
Connection ~ 1700 1250
Text GLabel 1750 2050 2    60   Input ~ 0
BatteryVoltage
$Comp
L R R4
U 1 1 5385024E
P 1400 2050
F 0 "R4" V 1480 2050 40  0000 C CNN
F 1 "47K" V 1407 2051 40  0000 C CNN
F 2 "~" V 1330 2050 30  0000 C CNN
F 3 "~" H 1400 2050 30  0000 C CNN
	1    1400 2050
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 53850254
P 1700 2400
F 0 "R5" V 1780 2400 40  0000 C CNN
F 1 "5K" V 1707 2401 40  0000 C CNN
F 2 "~" V 1630 2400 30  0000 C CNN
F 3 "~" H 1700 2400 30  0000 C CNN
	1    1700 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5385025A
P 1700 2650
F 0 "#PWR018" H 1700 2650 30  0001 C CNN
F 1 "GND" H 1700 2580 30  0001 C CNN
F 2 "" H 1700 2650 60  0000 C CNN
F 3 "" H 1700 2650 60  0000 C CNN
	1    1700 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2050 1750 2050
Wire Wire Line
	1700 2150 1700 2050
Connection ~ 1700 2050
Wire Wire Line
	4150 3800 3650 3800
Wire Wire Line
	4150 4600 3650 4600
$Comp
L CONN_5 P3
U 1 1 53850523
P 700 1250
F 0 "P3" V 650 1250 50  0000 C CNN
F 1 "Bat charge" V 750 1250 50  0000 C CNN
F 2 "" H 700 1250 60  0000 C CNN
F 3 "" H 700 1250 60  0000 C CNN
	1    700  1250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 1450 1200 1450
Wire Wire Line
	1100 1150 1250 1150
$Comp
L +5V #PWR019
U 1 1 538505FE
P 1150 950
F 0 "#PWR019" H 1150 1040 20  0001 C CNN
F 1 "+5V" H 1150 1040 30  0000 C CNN
F 2 "" H 1150 950 60  0000 C CNN
F 3 "" H 1150 950 60  0000 C CNN
	1    1150 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1050 1150 1050
Wire Wire Line
	1150 1050 1150 950 
Wire Wire Line
	1100 1250 1150 1250
Text GLabel 1750 1050 2    60   Input ~ 0
ChargeCurrent
Wire Wire Line
	1750 1050 1250 1050
Wire Wire Line
	1250 1050 1250 1150
Wire Wire Line
	1150 2050 1150 1700
Wire Wire Line
	1150 1700 1400 1700
Wire Wire Line
	1400 1700 1400 1350
Wire Wire Line
	1400 1350 1100 1350
Text GLabel 8900 900  0    60   Input ~ 0
TX2
Text GLabel 9750 1100 0    60   Input ~ 0
RX2
$Comp
L R R6
U 1 1 53850775
P 9150 900
F 0 "R6" V 9230 900 40  0000 C CNN
F 1 "470R" V 9157 901 40  0000 C CNN
F 2 "~" V 9080 900 30  0000 C CNN
F 3 "~" H 9150 900 30  0000 C CNN
	1    9150 900 
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 53850784
P 9400 1300
F 0 "R7" V 9480 1300 40  0000 C CNN
F 1 "1K" V 9407 1301 40  0000 C CNN
F 2 "~" V 9330 1300 30  0000 C CNN
F 3 "~" H 9400 1300 30  0000 C CNN
	1    9400 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 538507B1
P 9400 1600
F 0 "#PWR020" H 9400 1600 30  0001 C CNN
F 1 "GND" H 9400 1530 30  0001 C CNN
F 2 "" H 9400 1600 60  0000 C CNN
F 3 "" H 9400 1600 60  0000 C CNN
	1    9400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1600 9400 1550
Wire Wire Line
	9400 900  9400 1050
$Comp
L R R8
U 1 1 53850952
P 9800 1350
F 0 "R8" V 9880 1350 40  0000 C CNN
F 1 "1K" V 9807 1351 40  0000 C CNN
F 2 "~" V 9730 1350 30  0000 C CNN
F 3 "~" H 9800 1350 30  0000 C CNN
	1    9800 1350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 53850961
P 9800 1600
F 0 "#PWR021" H 9800 1690 20  0001 C CNN
F 1 "+5V" H 9800 1690 30  0000 C CNN
F 2 "" H 9800 1600 60  0000 C CNN
F 3 "" H 9800 1600 60  0000 C CNN
	1    9800 1600
	-1   0    0    1   
$EndComp
Connection ~ 9800 1100
$Comp
L CONN_4 P6
U 1 1 53850AD4
P 700 5600
F 0 "P6" V 650 5600 50  0000 C CNN
F 1 "Sonar C" V 750 5600 50  0000 C CNN
F 2 "" H 700 5600 60  0000 C CNN
F 3 "" H 700 5600 60  0000 C CNN
	1    700  5600
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR022
U 1 1 53850AE3
P 1100 5350
F 0 "#PWR022" H 1100 5440 20  0001 C CNN
F 1 "+5V" H 1100 5440 30  0000 C CNN
F 2 "" H 1100 5350 60  0000 C CNN
F 3 "" H 1100 5350 60  0000 C CNN
	1    1100 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 53850AF2
P 1100 5850
F 0 "#PWR023" H 1100 5850 30  0001 C CNN
F 1 "GND" H 1100 5780 30  0001 C CNN
F 2 "" H 1100 5850 60  0000 C CNN
F 3 "" H 1100 5850 60  0000 C CNN
	1    1100 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 5750 1100 5750
Wire Wire Line
	1100 5750 1100 5850
Wire Wire Line
	1050 5450 1100 5450
Wire Wire Line
	1100 5450 1100 5350
Wire Wire Line
	1250 5700 1200 5700
Wire Wire Line
	1200 5700 1200 5650
Wire Wire Line
	1200 5650 1050 5650
Wire Wire Line
	1050 5550 1200 5550
Wire Wire Line
	1200 5550 1200 5500
Wire Wire Line
	1200 5500 1250 5500
Text Notes 1300 6050 2    60   ~ 0
Sonar HC SR-04\n
Text Notes 850  1650 2    60   ~ 0
Battery\nCharge
Text Notes 11100 4100 2    60   ~ 0
Perimeter coil
Text Notes 11100 4750 2    60   ~ 0
Motor Driver\n
Wire Wire Line
	4150 4500 3850 4500
Wire Wire Line
	3850 4500 3850 4450
Wire Wire Line
	3850 4450 3650 4450
$Comp
L CONN_4 P5
U 1 1 53850EEA
P 700 4850
F 0 "P5" V 650 4850 50  0000 C CNN
F 1 "Motor sens" V 750 4850 50  0000 C CNN
F 2 "" H 700 4850 60  0000 C CNN
F 3 "" H 700 4850 60  0000 C CNN
	1    700  4850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 53850F02
P 1150 5150
F 0 "#PWR024" H 1150 5150 30  0001 C CNN
F 1 "GND" H 1150 5080 30  0001 C CNN
F 2 "" H 1150 5150 60  0000 C CNN
F 3 "" H 1150 5150 60  0000 C CNN
	1    1150 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 7200 4150 7200
Wire Wire Line
	6200 7050 6050 7050
$Comp
L CONN_5 P4
U 1 1 538511D8
P 700 3950
F 0 "P4" V 650 3950 50  0000 C CNN
F 1 "Mow Motor" V 750 3950 50  0000 C CNN
F 2 "" H 700 3950 60  0000 C CNN
F 3 "" H 700 3950 60  0000 C CNN
	1    700  3950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 3950 1350 3950
Wire Wire Line
	1350 4150 1250 4150
Wire Wire Line
	1250 4150 1250 4050
Wire Wire Line
	1250 4050 1100 4050
Wire Wire Line
	1350 3750 1250 3750
Wire Wire Line
	1250 3750 1250 3850
Wire Wire Line
	1250 3850 1100 3850
$Comp
L GND #PWR025
U 1 1 5385134B
P 1100 4300
F 0 "#PWR025" H 1100 4300 30  0001 C CNN
F 1 "GND" H 1100 4230 30  0001 C CNN
F 2 "" H 1100 4300 60  0000 C CNN
F 3 "" H 1100 4300 60  0000 C CNN
	1    1100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 4300 1100 4150
$Comp
L +5V #PWR026
U 1 1 538513C9
P 1100 3650
F 0 "#PWR026" H 1100 3740 20  0001 C CNN
F 1 "+5V" H 1100 3740 30  0000 C CNN
F 2 "" H 1100 3650 60  0000 C CNN
F 3 "" H 1100 3650 60  0000 C CNN
	1    1100 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 3750 1100 3650
Text GLabel 6200 3900 2    60   Input ~ 0
MotorMow
Text GLabel 3650 3950 0    60   Input ~ 0
MotorMowSense
Text GLabel 3650 3650 0    60   Input ~ 0
MotorLeftSense
Text GLabel 3650 3500 0    60   Input ~ 0
MotorRightSense
Wire Wire Line
	4150 3700 3850 3700
Wire Wire Line
	3850 3700 3850 3650
Wire Wire Line
	3850 3650 3650 3650
Wire Wire Line
	3650 3500 4000 3500
Wire Wire Line
	4000 3500 4000 3600
Wire Wire Line
	4000 3600 4150 3600
NoConn ~ 4150 4200
NoConn ~ 4150 4300
Wire Wire Line
	3650 3950 3850 3950
Wire Wire Line
	3850 3950 3850 3900
Wire Wire Line
	3850 3900 4150 3900
Wire Wire Line
	3650 4250 3950 4250
Wire Wire Line
	3950 4250 3950 4100
Wire Wire Line
	3950 4100 4150 4100
Wire Wire Line
	4150 4000 3850 4000
Wire Wire Line
	3850 4000 3850 4100
Wire Wire Line
	3850 4100 3650 4100
NoConn ~ 4150 4800
NoConn ~ 4150 4700
NoConn ~ 4150 3400
NoConn ~ 4150 2900
NoConn ~ 6050 2500
NoConn ~ 6050 5250
NoConn ~ 6050 5350
Text GLabel 3400 7300 0    60   Input ~ 0
SonarCenterTrigger
Text GLabel 3400 7100 0    60   Input ~ 0
SonarCenterEcho
$Comp
L CONN_4 P7
U 1 1 53851A62
P 700 6450
F 0 "P7" V 650 6450 50  0000 C CNN
F 1 "Sonar R" V 750 6450 50  0000 C CNN
F 2 "" H 700 6450 60  0000 C CNN
F 3 "" H 700 6450 60  0000 C CNN
	1    700  6450
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR027
U 1 1 53851A68
P 1100 6200
F 0 "#PWR027" H 1100 6290 20  0001 C CNN
F 1 "+5V" H 1100 6290 30  0000 C CNN
F 2 "" H 1100 6200 60  0000 C CNN
F 3 "" H 1100 6200 60  0000 C CNN
	1    1100 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 53851A6E
P 1100 6700
F 0 "#PWR028" H 1100 6700 30  0001 C CNN
F 1 "GND" H 1100 6630 30  0001 C CNN
F 2 "" H 1100 6700 60  0000 C CNN
F 3 "" H 1100 6700 60  0000 C CNN
	1    1100 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 6600 1100 6600
Wire Wire Line
	1100 6600 1100 6700
Wire Wire Line
	1050 6300 1100 6300
Wire Wire Line
	1100 6300 1100 6200
Wire Wire Line
	1250 6550 1200 6550
Wire Wire Line
	1200 6550 1200 6500
Wire Wire Line
	1200 6500 1050 6500
Wire Wire Line
	1050 6400 1200 6400
Wire Wire Line
	1200 6400 1200 6350
Wire Wire Line
	1200 6350 1250 6350
Text Notes 1300 6900 2    60   ~ 0
Sonar HC SR-04\n
Text GLabel 4050 6850 0    60   Input ~ 0
SonarRightTrigger
Text GLabel 4050 6650 0    60   Input ~ 0
SonarRightEcho
Wire Wire Line
	6050 6350 7050 6350
Wire Wire Line
	6050 6550 7050 6550
$Comp
L CONN_4 P8
U 1 1 53851BA4
P 700 7300
F 0 "P8" V 650 7300 50  0000 C CNN
F 1 "Sonar L" V 750 7300 50  0000 C CNN
F 2 "" H 700 7300 60  0000 C CNN
F 3 "" H 700 7300 60  0000 C CNN
	1    700  7300
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR029
U 1 1 53851BAA
P 1100 7050
F 0 "#PWR029" H 1100 7140 20  0001 C CNN
F 1 "+5V" H 1100 7140 30  0000 C CNN
F 2 "" H 1100 7050 60  0000 C CNN
F 3 "" H 1100 7050 60  0000 C CNN
	1    1100 7050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 53851BB0
P 1100 7550
F 0 "#PWR030" H 1100 7550 30  0001 C CNN
F 1 "GND" H 1100 7480 30  0001 C CNN
F 2 "" H 1100 7550 60  0000 C CNN
F 3 "" H 1100 7550 60  0000 C CNN
	1    1100 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 7450 1100 7450
Wire Wire Line
	1100 7450 1100 7550
Wire Wire Line
	1050 7150 1100 7150
Wire Wire Line
	1100 7150 1100 7050
Wire Wire Line
	1250 7400 1200 7400
Wire Wire Line
	1200 7400 1200 7350
Wire Wire Line
	1200 7350 1050 7350
Wire Wire Line
	1050 7250 1200 7250
Wire Wire Line
	1200 7250 1200 7200
Wire Wire Line
	1200 7200 1250 7200
Text Notes 1300 7750 2    60   ~ 0
Sonar HC SR-04\n
Text GLabel 6900 6750 2    60   Input ~ 0
SonarLeftTrigger
Text GLabel 6900 6950 2    60   Input ~ 0
SonarLeftEcho
Wire Wire Line
	6900 6750 6050 6750
Wire Wire Line
	6900 6950 6050 6950
$Comp
L +5V #PWR031
U 1 1 53852507
P 10400 6450
F 0 "#PWR031" H 10400 6540 20  0001 C CNN
F 1 "+5V" H 10400 6540 30  0000 C CNN
F 2 "" H 10400 6450 60  0000 C CNN
F 3 "" H 10400 6450 60  0000 C CNN
	1    10400 6450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 53852516
P 10400 7000
F 0 "#PWR032" H 10400 7000 30  0001 C CNN
F 1 "GND" H 10400 6930 30  0001 C CNN
F 2 "" H 10400 7000 60  0000 C CNN
F 3 "" H 10400 7000 60  0000 C CNN
	1    10400 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 6450 10400 6500
Wire Wire Line
	10400 6500 10600 6500
$Comp
L CONN_5 P12
U 1 1 53852677
P 11000 6700
F 0 "P12" V 10950 6700 50  0000 C CNN
F 1 "User switch" V 11050 6700 50  0000 C CNN
F 2 "" H 11000 6700 60  0000 C CNN
F 3 "" H 11000 6700 60  0000 C CNN
	1    11000 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 6900 10600 6900
Wire Wire Line
	10400 7000 10400 6900
Wire Wire Line
	10600 6700 10200 6700
Wire Wire Line
	10200 6550 10400 6550
Wire Wire Line
	10400 6550 10400 6600
Wire Wire Line
	10400 6600 10600 6600
Wire Wire Line
	10600 6800 10400 6800
Wire Wire Line
	10400 6800 10400 6850
Wire Wire Line
	10400 6850 10200 6850
Text GLabel 4050 7000 0    60   Input ~ 0
UserSwitch1
Text GLabel 3150 6750 0    60   Input ~ 0
UserSwitch2
Text GLabel 3150 6550 0    60   Input ~ 0
UserSwitch3
Wire Wire Line
	6050 6000 6200 6000
Wire Wire Line
	6050 6100 7050 6100
Wire Wire Line
	6200 6200 6050 6200
$Comp
L CONN_4 P11
U 1 1 53852D92
P 4900 850
F 0 "P11" V 4850 850 50  0000 C CNN
F 1 "ODO Right" V 4950 850 50  0000 C CNN
F 2 "" H 4900 850 60  0000 C CNN
F 3 "" H 4900 850 60  0000 C CNN
	1    4900 850 
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR033
U 1 1 53852D98
P 5300 600
F 0 "#PWR033" H 5300 690 20  0001 C CNN
F 1 "+5V" H 5300 690 30  0000 C CNN
F 2 "" H 5300 600 60  0000 C CNN
F 3 "" H 5300 600 60  0000 C CNN
	1    5300 600 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 53852D9E
P 5300 1100
F 0 "#PWR034" H 5300 1100 30  0001 C CNN
F 1 "GND" H 5300 1030 30  0001 C CNN
F 2 "" H 5300 1100 60  0000 C CNN
F 3 "" H 5300 1100 60  0000 C CNN
	1    5300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1000 5300 1000
Wire Wire Line
	5300 1000 5300 1100
Wire Wire Line
	5250 700  5300 700 
Wire Wire Line
	5300 700  5300 600 
Wire Wire Line
	5450 950  5400 950 
Wire Wire Line
	5400 950  5400 900 
Wire Wire Line
	5400 900  5250 900 
Wire Wire Line
	5250 800  5400 800 
Wire Wire Line
	5400 800  5400 750 
Wire Wire Line
	5400 750  5450 750 
Text Notes 6050 1850 2    60   ~ 0
Odometry left\n\n\n
Text GLabel 3650 4750 0    60   Input ~ 0
OdometryLeft
Text GLabel 3650 5050 0    60   Input ~ 0
OdometryRight
Text GLabel 5450 1450 2    60   Input ~ 0
OdometryLeft
Text GLabel 5450 750  2    60   Input ~ 0
OdometryRight
$Comp
L CONN_4 P10
U 1 1 53852DC8
P 4900 1550
F 0 "P10" V 4850 1550 50  0000 C CNN
F 1 "ODO Left" V 4950 1550 50  0000 C CNN
F 2 "" H 4900 1550 60  0000 C CNN
F 3 "" H 4900 1550 60  0000 C CNN
	1    4900 1550
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR035
U 1 1 53852DCE
P 5300 1300
F 0 "#PWR035" H 5300 1390 20  0001 C CNN
F 1 "+5V" H 5300 1390 30  0000 C CNN
F 2 "" H 5300 1300 60  0000 C CNN
F 3 "" H 5300 1300 60  0000 C CNN
	1    5300 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 53852DD4
P 5300 1800
F 0 "#PWR036" H 5300 1800 30  0001 C CNN
F 1 "GND" H 5300 1730 30  0001 C CNN
F 2 "" H 5300 1800 60  0000 C CNN
F 3 "" H 5300 1800 60  0000 C CNN
	1    5300 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1700 5300 1700
Wire Wire Line
	5300 1700 5300 1800
Wire Wire Line
	5250 1400 5300 1400
Wire Wire Line
	5300 1400 5300 1300
Wire Wire Line
	5450 1650 5400 1650
Wire Wire Line
	5400 1650 5400 1600
Wire Wire Line
	5400 1600 5250 1600
Wire Wire Line
	5250 1500 5400 1500
Wire Wire Line
	5400 1500 5400 1450
Wire Wire Line
	5400 1450 5450 1450
Text Notes 6100 1150 2    60   ~ 0
Odometry right\n\n\n
Text GLabel 5450 1650 2    60   Input ~ 0
OdometryLeft2
Wire Wire Line
	3150 6550 4150 6550
Wire Wire Line
	3400 7300 4150 7300
$Comp
L CONN_3 K1
U 1 1 5385309E
P 700 3050
F 0 "K1" V 650 3050 50  0000 C CNN
F 1 "Tilt sens" V 750 3050 40  0000 C CNN
F 2 "" H 700 3050 60  0000 C CNN
F 3 "" H 700 3050 60  0000 C CNN
	1    700  3050
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR037
U 1 1 538530BD
P 1050 2800
F 0 "#PWR037" H 1050 2890 20  0001 C CNN
F 1 "+5V" H 1050 2890 30  0000 C CNN
F 2 "" H 1050 2800 60  0000 C CNN
F 3 "" H 1050 2800 60  0000 C CNN
	1    1050 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 538530CC
P 1050 3300
F 0 "#PWR038" H 1050 3300 30  0001 C CNN
F 1 "GND" H 1050 3230 30  0001 C CNN
F 2 "" H 1050 3300 60  0000 C CNN
F 3 "" H 1050 3300 60  0000 C CNN
	1    1050 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 2950 1050 2800
Wire Wire Line
	1050 3150 1050 3300
Wire Wire Line
	1350 3050 1050 3050
Wire Wire Line
	3150 6750 4150 6750
$Comp
L CONN_4 P13
U 1 1 5385368B
P 2800 1150
F 0 "P13" V 2750 1150 50  0000 C CNN
F 1 "Lawn sens" V 2850 1150 50  0000 C CNN
F 2 "" H 2800 1150 60  0000 C CNN
F 3 "" H 2800 1150 60  0000 C CNN
	1    2800 1150
	-1   0    0    -1  
$EndComp
Text GLabel 3850 900  2    60   Input ~ 0
LawnBackSend
Text GLabel 3250 1050 2    60   Input ~ 0
LawnBackRecv
Text GLabel 3850 1200 2    60   Input ~ 0
LawnFrontSend
Text GLabel 3250 1350 2    60   Input ~ 0
LawnFrontRecv
$Comp
L R R9
U 1 1 538536B3
P 3500 900
F 0 "R9" V 3580 900 40  0000 C CNN
F 1 "2M2" V 3507 901 40  0000 C CNN
F 2 "~" V 3430 900 30  0000 C CNN
F 3 "~" H 3500 900 30  0000 C CNN
	1    3500 900 
	0    -1   -1   0   
$EndComp
$Comp
L R R10
U 1 1 538536C2
P 3500 1200
F 0 "R10" V 3580 1200 40  0000 C CNN
F 1 "2M2" V 3507 1201 40  0000 C CNN
F 2 "~" V 3430 1200 30  0000 C CNN
F 3 "~" H 3500 1200 30  0000 C CNN
	1    3500 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3850 1200 3750 1200
Wire Wire Line
	3250 1200 3150 1200
Wire Wire Line
	3250 1050 3200 1050
Wire Wire Line
	3200 1050 3200 1100
Wire Wire Line
	3200 1100 3150 1100
Wire Wire Line
	3150 1300 3200 1300
Wire Wire Line
	3200 1300 3200 1350
Wire Wire Line
	3200 1350 3250 1350
Wire Wire Line
	3250 900  3200 900 
Wire Wire Line
	3200 900  3200 1000
Wire Wire Line
	3200 1000 3150 1000
Wire Wire Line
	3750 900  3850 900 
Text Notes 3350 1550 2    60   ~ 0
Lawn sensor\n\n\n\n
Text Notes 1700 3300 2    60   ~ 0
Tilt sensor\n\n\n\n\n
Wire Wire Line
	9950 1100 9950 1600
Wire Wire Line
	9450 750  9500 750 
Wire Wire Line
	10150 750  10100 750 
$Comp
L MC33926 Dual1
U 1 1 538656B8
P 10250 2900
F 0 "Dual1" H 10200 1950 60  0000 C CNN
F 1 "MC33926" H 10250 4050 60  0000 C CNN
F 2 "" H 10400 2950 60  0000 C CNN
F 3 "" H 10400 2950 60  0000 C CNN
	1    10250 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 538656C7
P 9250 3050
F 0 "#PWR039" H 9250 3050 30  0001 C CNN
F 1 "GND" H 9250 2980 30  0001 C CNN
F 2 "" H 9250 3050 60  0000 C CNN
F 3 "" H 9250 3050 60  0000 C CNN
	1    9250 3050
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR040
U 1 1 538656D6
P 9250 3150
F 0 "#PWR040" H 9250 3240 20  0001 C CNN
F 1 "+5V" H 9250 3240 30  0000 C CNN
F 2 "" H 9250 3150 60  0000 C CNN
F 3 "" H 9250 3150 60  0000 C CNN
	1    9250 3150
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR041
U 1 1 538656F4
P 9250 2250
F 0 "#PWR041" H 9250 2340 20  0001 C CNN
F 1 "+5V" H 9250 2340 30  0000 C CNN
F 2 "" H 9250 2250 60  0000 C CNN
F 3 "" H 9250 2250 60  0000 C CNN
	1    9250 2250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR042
U 1 1 53865703
P 9250 2150
F 0 "#PWR042" H 9250 2150 30  0001 C CNN
F 1 "GND" H 9250 2080 30  0001 C CNN
F 2 "" H 9250 2150 60  0000 C CNN
F 3 "" H 9250 2150 60  0000 C CNN
	1    9250 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	9250 2150 9400 2150
Wire Wire Line
	9400 2250 9250 2250
Wire Wire Line
	9400 3050 9250 3050
Wire Wire Line
	9400 3150 9250 3150
$Comp
L GND #PWR043
U 1 1 53865B59
P 9250 3550
F 0 "#PWR043" H 9250 3550 30  0001 C CNN
F 1 "GND" H 9250 3480 30  0001 C CNN
F 2 "" H 9250 3550 60  0000 C CNN
F 3 "" H 9250 3550 60  0000 C CNN
	1    9250 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	9250 3550 9400 3550
$Comp
L +5V #PWR044
U 1 1 53865C46
P 9250 3450
F 0 "#PWR044" H 9250 3540 20  0001 C CNN
F 1 "+5V" H 9250 3540 30  0000 C CNN
F 2 "" H 9250 3450 60  0000 C CNN
F 3 "" H 9250 3450 60  0000 C CNN
	1    9250 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9250 3450 9400 3450
Text GLabel 9100 2850 0    60   Input ~ 0
MotorLeftSense
Text GLabel 9100 1950 0    60   Input ~ 0
MotorRightSense
Text GLabel 9100 3400 0    60   Input ~ 0
MotorLeftDir
Text GLabel 9100 2350 0    60   Input ~ 0
MotorRightPWM
Text GLabel 9100 3250 0    60   Input ~ 0
MotorLeftPWM
Text GLabel 9100 2500 0    60   Input ~ 0
MotorRightDir
Wire Wire Line
	9100 1950 9400 1950
Wire Wire Line
	9100 2350 9400 2350
Wire Wire Line
	9100 2500 9250 2500
Wire Wire Line
	9250 2500 9250 2450
Wire Wire Line
	9250 2450 9400 2450
Wire Wire Line
	9100 3250 9400 3250
Wire Wire Line
	9100 3400 9250 3400
Wire Wire Line
	9250 3400 9250 3350
Wire Wire Line
	9250 3350 9400 3350
NoConn ~ 9400 3650
NoConn ~ 9400 2550
NoConn ~ 9400 2650
NoConn ~ 11000 2000
NoConn ~ 11000 2100
NoConn ~ 11000 2600
NoConn ~ 11000 2700
NoConn ~ 11000 3250
NoConn ~ 11000 3350
$Comp
L CONN_4 P14
U 1 1 538663DA
P 9200 5900
F 0 "P14" V 9150 5900 50  0000 C CNN
F 1 "GPS RX" V 9250 5900 50  0000 C CNN
F 2 "" H 9200 5900 60  0000 C CNN
F 3 "" H 9200 5900 60  0000 C CNN
	1    9200 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR045
U 1 1 538663E0
P 8650 6050
F 0 "#PWR045" H 8650 6050 30  0001 C CNN
F 1 "GND" H 8650 5980 30  0001 C CNN
F 2 "" H 8650 6050 60  0000 C CNN
F 3 "" H 8650 6050 60  0000 C CNN
	1    8650 6050
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR046
U 1 1 538663E6
P 8650 5750
F 0 "#PWR046" H 8650 5840 20  0001 C CNN
F 1 "+5V" H 8650 5840 30  0000 C CNN
F 2 "" H 8650 5750 60  0000 C CNN
F 3 "" H 8650 5750 60  0000 C CNN
	1    8650 5750
	0    -1   -1   0   
$EndComp
Text GLabel 8400 5750 0    60   Input ~ 0
GPS_RX
Text GLabel 8400 5950 0    60   Output ~ 0
GPS_TX
Wire Wire Line
	8850 5750 8650 5750
Wire Wire Line
	8850 5850 8450 5850
Wire Wire Line
	8450 5850 8450 5750
Wire Wire Line
	8450 5750 8400 5750
Wire Wire Line
	8400 5950 8850 5950
Wire Wire Line
	8850 6050 8650 6050
Text Notes 9300 5650 2    60   ~ 0
GPS\n
Text GLabel 6250 4150 2    60   Input ~ 0
GPS_RX
Text GLabel 6250 4300 2    60   Output ~ 0
GPS_TX
Wire Wire Line
	6050 4300 6150 4300
Wire Wire Line
	6150 4300 6150 4150
Wire Wire Line
	6150 4150 6250 4150
Wire Wire Line
	6250 4300 6200 4300
Wire Wire Line
	6200 4300 6200 4400
Wire Wire Line
	6200 4400 6050 4400
Text GLabel 6250 4450 2    60   Output ~ 0
TX2
Text GLabel 6250 4600 2    60   Input ~ 0
RX2
Wire Wire Line
	6050 4500 6200 4500
Wire Wire Line
	6200 4500 6200 4450
Wire Wire Line
	6200 4450 6250 4450
Wire Wire Line
	6050 4600 6250 4600
$Comp
L CONN_2 P15
U 1 1 53866CB8
P 2800 2050
F 0 "P15" V 2750 2050 40  0000 C CNN
F 1 "DC/DC" V 2850 2050 40  0000 C CNN
F 2 "" H 2800 2050 60  0000 C CNN
F 3 "" H 2800 2050 60  0000 C CNN
	1    2800 2050
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR047
U 1 1 53866CD6
P 3150 2350
F 0 "#PWR047" H 3150 2350 30  0001 C CNN
F 1 "GND" H 3150 2280 30  0001 C CNN
F 2 "" H 3150 2350 60  0000 C CNN
F 3 "" H 3150 2350 60  0000 C CNN
	1    3150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2350 3150 2150
$Comp
L 7805 U4
U 1 1 53866DE0
P 3800 2000
F 0 "U4" H 3950 1804 60  0000 C CNN
F 1 "Traco TSR 1-2450" H 3800 2200 60  0000 C CNN
F 2 "~" H 3800 2000 60  0000 C CNN
F 3 "~" H 3800 2000 60  0000 C CNN
	1    3800 2000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR048
U 1 1 53866DEF
P 4650 1900
F 0 "#PWR048" H 4650 1990 20  0001 C CNN
F 1 "+5V" H 4650 1990 30  0000 C CNN
F 2 "" H 4650 1900 60  0000 C CNN
F 3 "" H 4650 1900 60  0000 C CNN
	1    4650 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 53866DFE
P 4350 2400
F 0 "#PWR049" H 4350 2400 30  0001 C CNN
F 1 "GND" H 4350 2330 30  0001 C CNN
F 2 "" H 4350 2400 60  0000 C CNN
F 3 "" H 4350 2400 60  0000 C CNN
	1    4350 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR050
U 1 1 53866E0D
P 3800 2350
F 0 "#PWR050" H 3800 2350 30  0001 C CNN
F 1 "GND" H 3800 2280 30  0001 C CNN
F 2 "" H 3800 2350 60  0000 C CNN
F 3 "" H 3800 2350 60  0000 C CNN
	1    3800 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR051
U 1 1 53866E1C
P 3300 2400
F 0 "#PWR051" H 3300 2400 30  0001 C CNN
F 1 "GND" H 3300 2330 30  0001 C CNN
F 2 "" H 3300 2400 60  0000 C CNN
F 3 "" H 3300 2400 60  0000 C CNN
	1    3300 2400
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 53866E2B
P 3300 2200
F 0 "C1" H 3350 2300 50  0000 L CNN
F 1 "10uF" H 3350 2100 50  0000 L CNN
F 2 "~" H 3300 2200 60  0000 C CNN
F 3 "~" H 3300 2200 60  0000 C CNN
	1    3300 2200
	1    0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 53866E3A
P 4350 2200
F 0 "C2" H 4400 2300 50  0000 L CNN
F 1 "10uF" H 4400 2100 50  0000 L CNN
F 2 "~" H 4350 2200 60  0000 C CNN
F 3 "~" H 4350 2200 60  0000 C CNN
	1    4350 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1950 4650 1950
Wire Wire Line
	4650 1950 4650 1900
Wire Wire Line
	3150 1950 3400 1950
Wire Wire Line
	3800 2350 3800 2250
$Comp
L CONN_4 P16
U 1 1 53867437
P 2700 3450
F 0 "P16" V 2650 3450 50  0000 C CNN
F 1 "I2C" V 2750 3450 50  0000 C CNN
F 2 "" H 2700 3450 60  0000 C CNN
F 3 "" H 2700 3450 60  0000 C CNN
	1    2700 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR052
U 1 1 53867444
P 2350 3750
F 0 "#PWR052" H 2350 3750 30  0001 C CNN
F 1 "GND" H 2350 3680 30  0001 C CNN
F 2 "" H 2350 3750 60  0000 C CNN
F 3 "" H 2350 3750 60  0000 C CNN
	1    2350 3750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR053
U 1 1 5386744A
P 2350 3150
F 0 "#PWR053" H 2350 3240 20  0001 C CNN
F 1 "+5V" H 2350 3240 30  0000 C CNN
F 2 "" H 2350 3150 60  0000 C CNN
F 3 "" H 2350 3150 60  0000 C CNN
	1    2350 3150
	1    0    0    -1  
$EndComp
Text GLabel 2150 3550 0    60   Input ~ 0
SCL
Text GLabel 2150 3400 0    60   BiDi ~ 0
SDA
Wire Wire Line
	2350 3300 2350 3150
Wire Wire Line
	2350 3600 2350 3750
Wire Wire Line
	2150 3550 2250 3550
Wire Wire Line
	2250 3550 2250 3500
Wire Wire Line
	2250 3500 2350 3500
Wire Wire Line
	2150 3400 2350 3400
Text GLabel 4000 6350 0    60   Input ~ 0
Tilt
Wire Wire Line
	6200 5850 6150 5850
Wire Wire Line
	6150 5850 6150 5800
Wire Wire Line
	6150 5800 6050 5800
$Comp
L CONN_4 P17
U 1 1 53878C5D
P 9200 6550
F 0 "P17" V 9150 6550 50  0000 C CNN
F 1 "Bumper" V 9250 6550 50  0000 C CNN
F 2 "" H 9200 6550 60  0000 C CNN
F 3 "" H 9200 6550 60  0000 C CNN
	1    9200 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR054
U 1 1 53878C63
P 8650 6700
F 0 "#PWR054" H 8650 6700 30  0001 C CNN
F 1 "GND" H 8650 6630 30  0001 C CNN
F 2 "" H 8650 6700 60  0000 C CNN
F 3 "" H 8650 6700 60  0000 C CNN
	1    8650 6700
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR055
U 1 1 53878C69
P 8650 6400
F 0 "#PWR055" H 8650 6490 20  0001 C CNN
F 1 "+5V" H 8650 6490 30  0000 C CNN
F 2 "" H 8650 6400 60  0000 C CNN
F 3 "" H 8650 6400 60  0000 C CNN
	1    8650 6400
	0    -1   -1   0   
$EndComp
Text GLabel 8400 6400 0    60   Input ~ 0
Bumperright
Text GLabel 8400 6600 0    60   Output ~ 0
Bumperleft
Wire Wire Line
	8850 6400 8650 6400
Wire Wire Line
	8850 6500 8450 6500
Wire Wire Line
	8450 6500 8450 6400
Wire Wire Line
	8450 6400 8400 6400
Wire Wire Line
	8400 6600 8850 6600
Wire Wire Line
	8850 6700 8650 6700
Text Notes 9300 6300 2    60   ~ 0
Bumper\n\n
NoConn ~ 6050 3200
NoConn ~ 6050 3400
NoConn ~ 6050 3500
Wire Wire Line
	4350 2000 4350 1950
Connection ~ 4350 1950
Wire Wire Line
	3300 1850 3300 2000
Connection ~ 3300 1950
$Comp
L +3.3V #PWR056
U 1 1 538791F4
P 3950 2900
F 0 "#PWR056" H 3950 2860 30  0001 C CNN
F 1 "+3.3V" H 3950 3010 30  0000 C CNN
F 2 "" H 3950 2900 60  0000 C CNN
F 3 "" H 3950 2900 60  0000 C CNN
	1    3950 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3000 3950 3000
Wire Wire Line
	3950 3000 3950 2900
NoConn ~ 6050 4000
NoConn ~ 6050 4100
NoConn ~ 11050 4350
NoConn ~ 11050 5150
Wire Wire Line
	4000 6150 4150 6150
Wire Wire Line
	6050 5600 6150 5600
Wire Wire Line
	6150 5600 6150 5550
Wire Wire Line
	6150 5550 6200 5550
Wire Wire Line
	6200 6850 6050 6850
Wire Wire Line
	1350 4900 1050 4900
Wire Wire Line
	1050 4800 1250 4800
Wire Wire Line
	1050 5000 1150 5000
Wire Wire Line
	1250 4800 1250 4700
Wire Wire Line
	1250 4700 1350 4700
Wire Wire Line
	1150 5000 1150 5150
$Comp
L +5V #PWR057
U 1 1 5387C08B
P 1050 4550
F 0 "#PWR057" H 1050 4640 20  0001 C CNN
F 1 "+5V" H 1050 4640 30  0000 C CNN
F 2 "" H 1050 4550 60  0000 C CNN
F 3 "" H 1050 4550 60  0000 C CNN
	1    1050 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 4550 1050 4700
Wire Wire Line
	9100 2850 9400 2850
$Comp
L CONN_2 P18
U 1 1 538908AB
P 8000 3150
F 0 "P18" V 7950 3150 40  0000 C CNN
F 1 "24V in" V 8050 3150 40  0000 C CNN
F 2 "" H 8000 3150 60  0000 C CNN
F 3 "" H 8000 3150 60  0000 C CNN
	1    8000 3150
	0    1    -1   0   
$EndComp
$Comp
L R R11
U 1 1 53890911
P 7900 4250
F 0 "R11" V 7980 4250 40  0000 C CNN
F 1 "180" V 7907 4251 40  0000 C CNN
F 2 "~" V 7830 4250 30  0000 C CNN
F 3 "~" H 7900 4250 30  0000 C CNN
	1    7900 4250
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 53890920
P 8100 4950
F 0 "R12" V 8180 4950 40  0000 C CNN
F 1 "10K" V 8107 4951 40  0000 C CNN
F 2 "~" V 8030 4950 30  0000 C CNN
F 3 "~" H 8100 4950 30  0000 C CNN
	1    8100 4950
	-1   0    0    1   
$EndComp
$Comp
L DIODESCH D2
U 1 1 5389092F
P 8900 4100
F 0 "D2" H 8900 4200 40  0000 C CNN
F 1 "MBR1045 schotky" H 8900 4000 40  0000 C CNN
F 2 "~" H 8900 4100 60  0000 C CNN
F 3 "~" H 8900 4100 60  0000 C CNN
	1    8900 4100
	0    -1   -1   0   
$EndComp
$Comp
L FET_N Q1
U 1 1 5389093E
P 8750 4700
F 0 "Q1" H 8653 4950 70  0000 C CNN
F 1 "IRLIZ44N" H 8603 4453 60  0000 C CNN
F 2 "~" H 8750 4700 60  0000 C CNN
F 3 "~" H 8750 4700 60  0000 C CNN
	1    8750 4700
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P19
U 1 1 5389094D
P 9400 3950
F 0 "P19" V 9350 3950 40  0000 C CNN
F 1 "Mow Motor" V 9450 3950 40  0000 C CNN
F 2 "" H 9400 3950 60  0000 C CNN
F 3 "" H 9400 3950 60  0000 C CNN
	1    9400 3950
	1    0    0    -1  
$EndComp
Text GLabel 7600 4250 0    60   Input ~ 0
MotorMow
$Comp
L GND #PWR058
U 1 1 53890F61
P 8350 5350
F 0 "#PWR058" H 8350 5350 30  0001 C CNN
F 1 "GND" H 8350 5280 30  0001 C CNN
F 2 "" H 8350 5350 60  0000 C CNN
F 3 "" H 8350 5350 60  0000 C CNN
	1    8350 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 5350 8350 5200
Connection ~ 8350 5200
$Comp
L +24V #PWR059
U 1 1 538911BA
P 8600 3800
F 0 "#PWR059" H 8600 3750 20  0001 C CNN
F 1 "+24V" H 8600 3900 30  0000 C CNN
F 2 "" H 8600 3800 60  0000 C CNN
F 3 "" H 8600 3800 60  0000 C CNN
	1    8600 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 3800 8600 3850
Connection ~ 8600 3850
$Comp
L GND #PWR060
U 1 1 5389141A
P 8100 3600
F 0 "#PWR060" H 8100 3600 30  0001 C CNN
F 1 "GND" H 8100 3530 30  0001 C CNN
F 2 "" H 8100 3600 60  0000 C CNN
F 3 "" H 8100 3600 60  0000 C CNN
	1    8100 3600
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR061
U 1 1 53891FE7
P 3300 1850
F 0 "#PWR061" H 3300 1800 20  0001 C CNN
F 1 "+24V" H 3300 1950 30  0000 C CNN
F 2 "" H 3300 1850 60  0000 C CNN
F 3 "" H 3300 1850 60  0000 C CNN
	1    3300 1850
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P9
U 1 1 538A4012
P 11000 5950
F 0 "P9" V 10950 5950 60  0000 C CNN
F 1 "RC Remote" V 11050 5950 60  0000 C CNN
F 2 "" H 11000 5950 60  0000 C CNN
F 3 "" H 11000 5950 60  0000 C CNN
	1    11000 5950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR062
U 1 1 538A4021
P 10550 6350
F 0 "#PWR062" H 10550 6350 30  0001 C CNN
F 1 "GND" H 10550 6280 30  0001 C CNN
F 2 "" H 10550 6350 60  0000 C CNN
F 3 "" H 10550 6350 60  0000 C CNN
	1    10550 6350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR063
U 1 1 538A4030
P 10550 5550
F 0 "#PWR063" H 10550 5640 20  0001 C CNN
F 1 "+5V" H 10550 5640 30  0000 C CNN
F 2 "" H 10550 5550 60  0000 C CNN
F 3 "" H 10550 5550 60  0000 C CNN
	1    10550 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 5550 10550 5700
Wire Wire Line
	10550 5700 10650 5700
Wire Wire Line
	10650 6200 10550 6200
Wire Wire Line
	10550 6200 10550 6350
Text GLabel 10250 5700 0    60   Input ~ 0
RemoteMow
Text GLabel 10250 5850 0    60   Input ~ 0
RemoteSteer
Text GLabel 10250 6000 0    60   Input ~ 0
RemoteSpeed
Text GLabel 10250 6150 0    60   Input ~ 0
RemoteSwitch
Wire Wire Line
	10250 6150 10450 6150
Wire Wire Line
	10450 6150 10450 6100
Wire Wire Line
	10450 6100 10650 6100
Wire Wire Line
	10250 6000 10650 6000
Wire Wire Line
	10250 5850 10450 5850
Wire Wire Line
	10450 5850 10450 5900
Wire Wire Line
	10450 5900 10650 5900
Wire Wire Line
	10250 5700 10500 5700
Wire Wire Line
	10500 5700 10500 5800
Wire Wire Line
	10500 5800 10650 5800
Text GLabel 6300 2800 2    60   Input ~ 0
RemoteMow
Text GLabel 6300 2950 2    60   Input ~ 0
RemoteSteer
Text GLabel 6300 3100 2    60   Input ~ 0
RemoteSpeed
Text GLabel 6300 3250 2    60   Input ~ 0
RemoteSwitch
Wire Wire Line
	4050 6650 4150 6650
Wire Wire Line
	4050 6850 4150 6850
Wire Wire Line
	3400 7100 4150 7100
NoConn ~ 6050 5500
NoConn ~ 6050 5700
NoConn ~ 6050 5900
$Comp
L R R13
U 1 1 538A5BD3
P 2350 2600
F 0 "R13" V 2430 2600 40  0000 C CNN
F 1 "470r" V 2357 2601 40  0000 C CNN
F 2 "~" V 2280 2600 30  0000 C CNN
F 3 "~" H 2350 2600 30  0000 C CNN
	1    2350 2600
	0    -1   -1   0   
$EndComp
$Comp
L R R14
U 1 1 538A5BE2
P 2350 2900
F 0 "R14" V 2430 2900 40  0000 C CNN
F 1 "2k2" V 2357 2901 40  0000 C CNN
F 2 "~" V 2280 2900 30  0000 C CNN
F 3 "~" H 2350 2900 30  0000 C CNN
	1    2350 2900
	0    -1   -1   0   
$EndComp
$Comp
L LED D3
U 1 1 538A5BFB
P 2800 2600
F 0 "D3" H 2800 2700 50  0000 C CNN
F 1 "5V" H 2800 2500 50  0000 C CNN
F 2 "~" H 2800 2600 60  0000 C CNN
F 3 "~" H 2800 2600 60  0000 C CNN
	1    2800 2600
	1    0    0    -1  
$EndComp
$Comp
L LED D4
U 1 1 538A5C0A
P 2800 2900
F 0 "D4" H 2800 3000 50  0000 C CNN
F 1 "24V" H 2800 2800 50  0000 C CNN
F 2 "~" H 2800 2900 60  0000 C CNN
F 3 "~" H 2800 2900 60  0000 C CNN
	1    2800 2900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR064
U 1 1 538A5C19
P 2000 2500
F 0 "#PWR064" H 2000 2590 20  0001 C CNN
F 1 "+5V" H 2000 2590 30  0000 C CNN
F 2 "" H 2000 2500 60  0000 C CNN
F 3 "" H 2000 2500 60  0000 C CNN
	1    2000 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR065
U 1 1 538A5C28
P 3000 2600
F 0 "#PWR065" H 3000 2600 30  0001 C CNN
F 1 "GND" H 3000 2530 30  0001 C CNN
F 2 "" H 3000 2600 60  0000 C CNN
F 3 "" H 3000 2600 60  0000 C CNN
	1    3000 2600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR066
U 1 1 538A5C37
P 3000 2900
F 0 "#PWR066" H 3000 2900 30  0001 C CNN
F 1 "GND" H 3000 2830 30  0001 C CNN
F 2 "" H 3000 2900 60  0000 C CNN
F 3 "" H 3000 2900 60  0000 C CNN
	1    3000 2900
	0    -1   -1   0   
$EndComp
$Comp
L +24V #PWR067
U 1 1 538A5C46
P 2000 2800
F 0 "#PWR067" H 2000 2750 20  0001 C CNN
F 1 "+24V" H 2000 2900 30  0000 C CNN
F 2 "" H 2000 2800 60  0000 C CNN
F 3 "" H 2000 2800 60  0000 C CNN
	1    2000 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2800 2000 2900
Wire Wire Line
	2000 2900 2100 2900
Wire Wire Line
	2000 2500 2000 2600
Wire Wire Line
	2000 2600 2100 2600
Wire Wire Line
	8900 3900 8900 3850
Connection ~ 8900 3850
Wire Wire Line
	8900 4300 8900 4350
Wire Wire Line
	9050 4050 9050 4350
Wire Wire Line
	9050 4350 8900 4350
Connection ~ 8900 4350
Wire Wire Line
	8100 4700 8450 4700
Wire Wire Line
	7600 4250 7650 4250
Wire Wire Line
	8150 4250 8300 4250
Wire Wire Line
	8300 4250 8300 4700
Connection ~ 8300 4700
Wire Wire Line
	8100 5200 8900 5200
Wire Wire Line
	8900 5200 8900 5050
Wire Wire Line
	6050 3600 6200 3600
NoConn ~ 6050 3700
Text GLabel 7050 6350 2    60   Input ~ 0
MotorEnable
Text GLabel 7050 6100 2    60   Input ~ 0
MotorLeftFault
Text GLabel 7050 6550 2    60   Input ~ 0
MotorRightFault
Wire Wire Line
	4150 5350 4150 5550
Connection ~ 4150 5450
Wire Wire Line
	4150 5350 4050 5350
Text GLabel 9000 2650 0    60   Input ~ 0
MotorEnable
Text GLabel 9100 3000 0    60   Input ~ 0
MotorLeftFault
Text GLabel 9100 2100 0    60   Input ~ 0
MotorRightFault
Wire Wire Line
	9100 3000 9150 3000
Wire Wire Line
	9150 3000 9150 2950
Wire Wire Line
	9150 2950 9400 2950
Wire Wire Line
	9000 2650 9250 2650
Wire Wire Line
	9250 2650 9250 2750
Wire Wire Line
	9250 2750 9400 2750
Wire Wire Line
	9100 2100 9150 2100
Wire Wire Line
	9150 2100 9150 2050
Wire Wire Line
	9150 2050 9400 2050
Wire Wire Line
	4150 5200 3650 5200
Wire Wire Line
	4150 5100 3800 5100
Wire Wire Line
	3800 5100 3800 5050
Wire Wire Line
	3800 5050 3650 5050
Wire Wire Line
	4150 5000 3900 5000
Wire Wire Line
	3900 5000 3900 4900
Wire Wire Line
	3900 4900 3650 4900
Wire Wire Line
	4150 4900 4000 4900
Wire Wire Line
	4000 4900 4000 4750
Wire Wire Line
	4000 4750 3650 4750
NoConn ~ 4150 6250
NoConn ~ 4150 6000
Wire Wire Line
	4050 7000 4150 7000
$Comp
L CONN_4 P20
U 1 1 539E1936
P 6350 1350
F 0 "P20" V 6300 1350 50  0000 C CNN
F 1 "SW_LED" V 6400 1350 50  0000 C CNN
F 2 "" H 6350 1350 60  0000 C CNN
F 3 "" H 6350 1350 60  0000 C CNN
	1    6350 1350
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR068
U 1 1 539E196E
P 6800 950
F 0 "#PWR068" H 6800 950 30  0001 C CNN
F 1 "GND" H 6800 880 30  0001 C CNN
F 2 "" H 6800 950 60  0000 C CNN
F 3 "" H 6800 950 60  0000 C CNN
	1    6800 950 
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR069
U 1 1 539E197D
P 6850 1650
F 0 "#PWR069" H 6850 1740 20  0001 C CNN
F 1 "+5V" H 6850 1740 30  0000 C CNN
F 2 "" H 6850 1650 60  0000 C CNN
F 3 "" H 6850 1650 60  0000 C CNN
	1    6850 1650
	0    1    1    0   
$EndComp
Text GLabel 6850 1500 2    60   Input ~ 0
Led
Text GLabel 6850 1300 2    60   Input ~ 0
Button
Wire Wire Line
	6700 950  6700 1200
Wire Wire Line
	6700 950  6800 950 
Wire Wire Line
	6850 1650 6700 1650
Wire Wire Line
	6700 1650 6700 1500
Wire Wire Line
	6850 1500 6800 1500
Wire Wire Line
	6800 1500 6800 1400
Wire Wire Line
	6800 1400 6700 1400
Wire Wire Line
	6700 1300 6850 1300
Wire Wire Line
	4000 6350 4150 6350
NoConn ~ 4150 6450
Wire Wire Line
	4000 5700 4150 5700
Wire Wire Line
	6050 2800 6300 2800
Wire Wire Line
	6050 2900 6200 2900
Wire Wire Line
	6200 2900 6200 2950
Wire Wire Line
	6200 2950 6300 2950
Wire Wire Line
	6050 3000 6200 3000
Wire Wire Line
	6200 3000 6200 3100
Wire Wire Line
	6200 3100 6300 3100
Wire Wire Line
	6300 3250 6150 3250
Wire Wire Line
	6150 3250 6150 3100
Wire Wire Line
	6150 3100 6050 3100
Text GLabel 6600 4700 2    60   Output ~ 0
TX1
Text GLabel 6600 4850 2    60   Input ~ 0
RX1
Wire Wire Line
	6600 4700 6050 4700
Wire Wire Line
	6600 4850 6500 4850
Wire Wire Line
	6500 4850 6500 4800
Wire Wire Line
	6500 4800 6050 4800
Text GLabel 7550 5150 2    60   Output ~ 0
TX1
Text GLabel 7550 5300 2    60   Input ~ 0
RX1
$Comp
L CONN_4 P21
U 1 1 53A04B34
P 7050 5250
F 0 "P21" V 7000 5250 50  0000 C CNN
F 1 "UART1" V 7100 5250 50  0000 C CNN
F 2 "" H 7050 5250 60  0000 C CNN
F 3 "" H 7050 5250 60  0000 C CNN
	1    7050 5250
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR070
U 1 1 53A04B5A
P 7400 5550
F 0 "#PWR070" H 7400 5550 30  0001 C CNN
F 1 "GND" H 7400 5480 30  0001 C CNN
F 2 "" H 7400 5550 60  0000 C CNN
F 3 "" H 7400 5550 60  0000 C CNN
	1    7400 5550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR071
U 1 1 53A04B69
P 7400 4950
F 0 "#PWR071" H 7400 5040 20  0001 C CNN
F 1 "+5V" H 7400 5040 30  0000 C CNN
F 2 "" H 7400 4950 60  0000 C CNN
F 3 "" H 7400 4950 60  0000 C CNN
	1    7400 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 5100 7400 4950
Wire Wire Line
	7400 5400 7400 5550
Wire Wire Line
	7400 5300 7550 5300
Wire Wire Line
	7400 5200 7500 5200
Wire Wire Line
	7500 5200 7500 5150
Wire Wire Line
	7500 5150 7550 5150
Text GLabel 4000 5850 0    60   Input ~ 0
MotorMowRpm
NoConn ~ 6050 2700
Wire Wire Line
	4150 5900 4050 5900
Wire Wire Line
	4050 5900 4050 5850
Wire Wire Line
	4050 5850 4000 5850
NoConn ~ 4150 5800
$Comp
L DS1307_RTC_EMARTEE U1
U 1 1 53A3060D
P 7750 1950
F 0 "U1" H 7950 1200 60  0000 C CNN
F 1 "DS1307_RTC_EMARTEE" H 7750 2150 60  0000 C CNN
F 2 "~" H 7950 1200 60  0000 C CNN
F 3 "~" H 7950 1200 60  0000 C CNN
	1    7750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2000 7100 2000
Wire Wire Line
	7100 2100 6750 2100
Wire Wire Line
	6750 2100 6750 2050
Wire Wire Line
	7100 2250 6950 2250
Wire Wire Line
	6950 2250 6950 2200
Wire Wire Line
	6950 2200 6750 2200
Wire Wire Line
	6750 2350 7100 2350
$Comp
L DIODE D5
U 1 1 53A32559
P 8600 4050
F 0 "D5" H 8600 4150 40  0000 C CNN
F 1 "1N4007" H 8600 3950 40  0000 C CNN
F 2 "~" H 8600 4050 60  0000 C CNN
F 3 "~" H 8600 4050 60  0000 C CNN
	1    8600 4050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR072
U 1 1 53A32568
P 8600 4250
F 0 "#PWR072" H 8600 4250 30  0001 C CNN
F 1 "GND" H 8600 4180 30  0001 C CNN
F 2 "" H 8600 4250 60  0000 C CNN
F 3 "" H 8600 4250 60  0000 C CNN
	1    8600 4250
	1    0    0    -1  
$EndComp
$Comp
L FUSE F1
U 1 1 53A35357
P 8250 3850
F 0 "F1" H 8350 3900 40  0000 C CNN
F 1 "FUSE" H 8150 3800 40  0000 C CNN
F 2 "~" H 8250 3850 60  0000 C CNN
F 3 "~" H 8250 3850 60  0000 C CNN
	1    8250 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3850 9050 3850
Wire Wire Line
	7850 3850 8000 3850
Wire Wire Line
	7900 3850 7900 3500
Wire Wire Line
	8100 3500 8100 3600
$Comp
L HC05_MODULE_ARDUMOWER_ HC5
U 1 1 53A5F751
P 10650 700
F 0 "HC5" H 10850 -50 60  0000 C CNN
F 1 "HC05_MODULE_ARDUMOWER_" H 10550 850 60  0000 C CNN
F 2 "~" H 10850 -50 60  0000 C CNN
F 3 "~" H 10850 -50 60  0000 C CNN
	1    10650 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 750  10150 800 
Wire Wire Line
	10150 800  10200 800 
Wire Wire Line
	9400 900  10200 900 
Wire Wire Line
	9750 1100 9900 1100
Wire Wire Line
	9900 1100 9900 1000
Wire Wire Line
	9900 1000 10200 1000
Wire Wire Line
	10150 1200 10200 1200
Wire Wire Line
	9950 1100 10200 1100
NoConn ~ 10200 650 
Wire Wire Line
	3800 3100 4150 3100
$Comp
L +5V #PWR073
U 1 1 53B47FE4
P 3800 3100
F 0 "#PWR073" H 3800 3190 20  0001 C CNN
F 1 "+5V" H 3800 3190 30  0000 C CNN
F 2 "" H 3800 3100 60  0000 C CNN
F 3 "" H 3800 3100 60  0000 C CNN
	1    3800 3100
	0    -1   -1   0   
$EndComp
$Comp
L +24V #PWR?
U 1 1 53B68BF1
P 7850 3850
F 0 "#PWR?" H 7850 3800 20  0001 C CNN
F 1 "+24V" H 7850 3950 30  0000 C CNN
F 2 "" H 7850 3850 60  0000 C CNN
F 3 "" H 7850 3850 60  0000 C CNN
	1    7850 3850
	0    -1   -1   0   
$EndComp
Connection ~ 7900 3850
$EndSCHEMATC
