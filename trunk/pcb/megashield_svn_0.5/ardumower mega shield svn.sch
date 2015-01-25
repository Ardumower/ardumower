EESchema Schematic File Version 2
LIBS:power
LIBS:Bluetooth_ZS_HC_05
LIBS:Bluetooth_CZ_HC_05
LIBS:Wlan_ESP8266
LIBS:ds1307
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Ardumower shield SVN Version"
Date "29 Dez 2014"
Rev "C"
Comp " by StefanM"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUINO_MEGA_SHIELD SHIELD1
U 1 1 5375252C
P 8200 4600
F 0 "SHIELD1" H 8250 4650 60  0001 C CNN
F 1 "ARDUINO_MEGA_SHIELD" H 8200 4600 60  0001 C CNN
F 2 "Arduino Mega Shield:ARDUINO MEGA SHIELD" H 8200 4600 60  0001 C CNN
F 3 "" H 8200 4600 60  0001 C CNN
F 4 "SHIELD" H 7800 7100 60  0000 C CNN "Reference"
F 5 "ARDUINO_MEGA_SHIELD" H 8100 1900 60  0000 C CNN "Value"
F 6 "" H 8200 4600 60  0000 C CNN "Datasheet"
	1    8200 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 537FB5D9
P 1275 1150
F 0 "#PWR01" H 1275 1150 30  0001 C CNN
F 1 "GND" H 1275 1080 30  0001 C CNN
F 2 "" H 1275 1150 60  0000 C CNN
F 3 "" H 1275 1150 60  0000 C CNN
	1    1275 1150
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 537FB5E8
P 7100 2950
F 0 "#PWR02" H 7100 2950 30  0001 C CNN
F 1 "GND" H 7100 2880 30  0001 C CNN
F 2 "" H 7100 2950 60  0000 C CNN
F 3 "" H 7100 2950 60  0000 C CNN
	1    7100 2950
	0    1    1    0   
$EndComp
$Comp
L JUMPER JP2
U 1 1 537FB697
P 1550 850
F 0 "JP2" H 1550 1000 60  0000 C CNN
F 1 "Key" H 1550 770 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1550 850 60  0001 C CNN
F 3 "~" H 1550 850 60  0000 C CNN
	1    1550 850 
	-1   0    0    -1  
$EndComp
$Comp
L SPEAKER SP1
U 1 1 537FB76E
P 11850 2875
F 0 "SP1" H 11750 3125 70  0000 C CNN
F 1 "SPEAKER" H 11750 2625 70  0000 C CNN
F 2 "Buzzers_Beepers:Buzzer_12x9.5RM7.6" H 11850 2875 60  0001 C CNN
F 3 "~" H 11850 2875 60  0000 C CNN
	1    11850 2875
	-1   0    0    1   
$EndComp
Text GLabel 9250 4800 2    60   Output ~ 0
SCL2
Text GLabel 9250 4650 2    60   BiDi ~ 0
SDA2
$Comp
L GND #PWR03
U 1 1 5384EC59
P 12150 3125
F 0 "#PWR03" H 12150 3125 30  0001 C CNN
F 1 "GND" H 12150 3055 30  0001 C CNN
F 2 "" H 12150 3125 60  0000 C CNN
F 3 "" H 12150 3125 60  0000 C CNN
	1    12150 3125
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5384EC7E
P 9450 2450
F 0 "R5" V 9530 2450 40  0000 C CNN
F 1 "470R" V 9457 2451 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 9380 2450 30  0001 C CNN
F 3 "~" H 9450 2450 30  0000 C CNN
	1    9450 2450
	0    -1   -1   0   
$EndComp
Text GLabel 5400 3850 0    60   Input ~ 0
pinPerimeterLeft
$Comp
L GND #PWR04
U 1 1 5384F323
P 7150 5300
F 0 "#PWR04" H 7150 5300 30  0001 C CNN
F 1 "GND" H 7150 5230 30  0001 C CNN
F 2 "" H 7150 5300 60  0000 C CNN
F 3 "" H 7150 5300 60  0000 C CNN
	1    7150 5300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 5384F385
P 9250 2350
F 0 "#PWR05" H 9250 2350 30  0001 C CNN
F 1 "GND" H 9250 2280 30  0001 C CNN
F 2 "" H 9250 2350 60  0000 C CNN
F 3 "" H 9250 2350 60  0000 C CNN
	1    9250 2350
	0    -1   -1   0   
$EndComp
Text GLabel 10450 3550 2    60   Output ~ 0
pinMotorRightPWM
Text GLabel 10450 3350 2    60   Output ~ 0
pinMotorLeftPWM
Text GLabel 9250 5550 2    60   Input ~ 0
pinMotorLeftFault
Text GLabel 9250 6600 2    60   Input ~ 0
pinTilt
Text GLabel 12300 2775 2    60   Input ~ 0
pinBuzzer
Text GLabel 5300 5550 0    60   Output ~ 0
pinBuzzer
Text GLabel 6200 6950 0    60   Input ~ 0
pinBumperLeft
Text GLabel 9250 6800 2    60   Output ~ 0
pinMotorEnable
Text GLabel 1250 4300 2    60   Input ~ 0
pinSonarCenterTrigger
Text GLabel 1250 4500 2    60   Output ~ 0
pinSonarCenterEcho
Text GLabel 1250 5150 2    60   Input ~ 0
pinSonarRightTrigger
Text GLabel 1250 5350 2    60   Output ~ 0
pinSonarRightEcho
Text GLabel 1250 6000 2    60   Input ~ 0
pinSonarLeftTrigger
Text GLabel 1250 6200 2    60   Output ~ 0
pinSonarLeftEcho
Text GLabel 4425 7100 2    60   Output ~ 0
pinTilt
Text GLabel 4400 3550 0    60   Input ~ 0
pinBatteryVoltage
Text GLabel 4400 4250 0    60   Input ~ 0
pinChargeCurrent
Text GLabel 5400 4350 0    60   Input ~ 0
pinChargeVoltage
Text GLabel 5450 1050 2    60   Output ~ 0
pinOdometryRight2
Text GLabel 9250 6200 2    60   Output ~ 0
pinMotorLeftDir
Text GLabel 9250 6400 2    60   Output ~ 0
pinMotorRightDir
Text GLabel 9250 5950 2    60   Output ~ 0
pinMotorMowDir
Text GLabel 9250 5750 2    60   Input ~ 0
pinMotorRightFault
Text GLabel 2500 8775 0    60   Output ~ 0
pinChargeVoltage
$Comp
L R R9
U 1 1 5384FFAC
P 2600 8525
F 0 "R9" V 2680 8525 40  0000 C CNN
F 1 "47K" V 2607 8526 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2530 8525 30  0001 C CNN
F 3 "~" H 2600 8525 30  0000 C CNN
	1    2600 8525
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5384FFC0
P 2600 9125
F 0 "R10" V 2680 9125 40  0000 C CNN
F 1 "5K" V 2607 9126 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2530 9125 30  0001 C CNN
F 3 "~" H 2600 9125 30  0000 C CNN
	1    2600 9125
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 53850044
P 2600 9425
F 0 "#PWR06" H 2600 9425 30  0001 C CNN
F 1 "GND" H 2600 9355 30  0001 C CNN
F 2 "" H 2600 9425 60  0000 C CNN
F 3 "" H 2600 9425 60  0000 C CNN
	1    2600 9425
	1    0    0    -1  
$EndComp
Text GLabel 10175 7050 2    47   Output ~ 0
pinBatteryVoltage
$Comp
L R R12
U 1 1 5385024E
P 9725 7050
F 0 "R12" V 9805 7050 40  0000 C CNN
F 1 "47K" V 9732 7051 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 9655 7050 30  0001 C CNN
F 3 "~" H 9725 7050 30  0000 C CNN
	1    9725 7050
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 53850254
P 10025 7400
F 0 "R13" V 10105 7400 40  0000 C CNN
F 1 "5K" V 10032 7401 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 9955 7400 30  0001 C CNN
F 3 "~" H 10025 7400 30  0000 C CNN
	1    10025 7400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5385025A
P 10025 7700
F 0 "#PWR07" H 10025 7700 30  0001 C CNN
F 1 "GND" H 10025 7630 30  0001 C CNN
F 2 "" H 10025 7700 60  0000 C CNN
F 3 "" H 10025 7700 60  0000 C CNN
	1    10025 7700
	1    0    0    -1  
$EndComp
Text GLabel 3700 9250 2    47   Output ~ 0
pinChargeCurrent
Text GLabel 2225 1600 3    60   Input ~ 0
TX2
Text GLabel 1775 1050 2    60   Input ~ 0
RX2
$Comp
L R R6
U 1 1 53850775
P 2225 1350
F 0 "R6" V 2305 1350 40  0000 C CNN
F 1 "470R" V 2232 1351 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2155 1350 30  0001 C CNN
F 3 "~" H 2225 1350 30  0000 C CNN
	1    2225 1350
	-1   0    0    1   
$EndComp
$Comp
L R R7
U 1 1 53850784
P 2050 1350
F 0 "R7" V 2130 1350 40  0000 C CNN
F 1 "1K" V 2057 1351 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 1980 1350 30  0001 C CNN
F 3 "~" H 2050 1350 30  0000 C CNN
	1    2050 1350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 538507B1
P 2050 1625
F 0 "#PWR08" H 2050 1625 30  0001 C CNN
F 1 "GND" H 2050 1555 30  0001 C CNN
F 2 "" H 2050 1625 60  0000 C CNN
F 3 "" H 2050 1625 60  0000 C CNN
	1    2050 1625
	-1   0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 53850952
P 1725 1350
F 0 "R8" V 1805 1350 40  0000 C CNN
F 1 "1K" V 1732 1351 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 1655 1350 30  0001 C CNN
F 3 "~" H 1725 1350 30  0000 C CNN
	1    1725 1350
	-1   0    0    -1  
$EndComp
$Comp
L CONN_4 P1
U 1 1 53850AD4
P 700 4300
F 0 "P1" V 650 4300 50  0000 C CNN
F 1 "Sonar C" V 750 4300 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 700 4300 60  0001 C CNN
F 3 "" H 700 4300 60  0000 C CNN
	1    700  4300
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 53850AE3
P 1100 4050
F 0 "#PWR09" H 1100 4140 20  0001 C CNN
F 1 "+5V" H 1100 4140 30  0000 C CNN
F 2 "" H 1100 4050 60  0000 C CNN
F 3 "" H 1100 4050 60  0000 C CNN
	1    1100 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 53850AF2
P 1200 4200
F 0 "#PWR010" H 1200 4200 30  0001 C CNN
F 1 "GND" H 1200 4130 30  0001 C CNN
F 2 "" H 1200 4200 60  0000 C CNN
F 3 "" H 1200 4200 60  0000 C CNN
	1    1200 4200
	0    -1   -1   0   
$EndComp
Text Notes 1500 4750 2    60   ~ 0
Sonar HC SR-04\n
Text Notes 14700 6050 2    60   ~ 0
Perimeter coil
Text GLabel 9450 3650 2    60   Output ~ 0
pinMotorMowPWM
Text GLabel 5400 3650 0    60   Input ~ 0
pinMotorMowSense
Text GLabel 5400 3450 0    60   Input ~ 0
pinMotorLeftSense
Text GLabel 4400 3350 0    60   Input ~ 0
pinMotorRightSense
NoConn ~ 7200 2650
NoConn ~ 9100 2250
NoConn ~ 9100 5000
NoConn ~ 9100 5100
Text GLabel 7050 7050 0    60   Input ~ 0
pinBumperRight
Text GLabel 7100 6850 0    60   Input ~ 0
pinLawnFrontRecv
$Comp
L CONN_4 P2
U 1 1 53851A62
P 700 5150
F 0 "P2" V 650 5150 50  0000 C CNN
F 1 "Sonar R" V 750 5150 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 700 5150 60  0001 C CNN
F 3 "" H 700 5150 60  0000 C CNN
	1    700  5150
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 53851A6E
P 1200 5050
F 0 "#PWR011" H 1200 5050 30  0001 C CNN
F 1 "GND" H 1200 4980 30  0001 C CNN
F 2 "" H 1200 5050 60  0000 C CNN
F 3 "" H 1200 5050 60  0000 C CNN
	1    1200 5050
	0    -1   -1   0   
$EndComp
Text Notes 1500 5600 2    60   ~ 0
Sonar HC SR-04\n
Text GLabel 7100 6600 0    60   Input ~ 0
pinLawnBackRecv
Text GLabel 7100 6400 0    60   Input ~ 0
pinRain
$Comp
L CONN_4 P3
U 1 1 53851BA4
P 700 6000
F 0 "P3" V 650 6000 50  0000 C CNN
F 1 "Sonar L" V 750 6000 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 700 6000 60  0001 C CNN
F 3 "" H 700 6000 60  0000 C CNN
	1    700  6000
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR012
U 1 1 53851BAA
P 1100 5750
F 0 "#PWR012" H 1100 5840 20  0001 C CNN
F 1 "+5V" H 1100 5840 30  0000 C CNN
F 2 "" H 1100 5750 60  0000 C CNN
F 3 "" H 1100 5750 60  0000 C CNN
	1    1100 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 53851BB0
P 1200 5850
F 0 "#PWR013" H 1200 5850 30  0001 C CNN
F 1 "GND" H 1200 5780 30  0001 C CNN
F 2 "" H 1200 5850 60  0000 C CNN
F 3 "" H 1200 5850 60  0000 C CNN
	1    1200 5850
	0    -1   -1   0   
$EndComp
Text Notes 1500 6450 2    60   ~ 0
Sonar HC SR-04\n
Text GLabel 10250 6500 2    60   Output ~ 0
pinSonarLeftTrigger
Text GLabel 10250 6700 2    60   Input ~ 0
pinSonarLeftEcho
Text GLabel 6200 6750 0    60   Output ~ 0
pinLawnFrontSend
Text GLabel 6200 6500 0    60   Output ~ 0
pinLawnBackSend
$Comp
L CONN_4 P8
U 1 1 53852D92
P 4900 850
F 0 "P8" V 4850 850 50  0000 C CNN
F 1 "ODO Right" V 4950 850 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 4900 850 60  0001 C CNN
F 3 "" H 4900 850 60  0000 C CNN
	1    4900 850 
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 53852D9E
P 5450 700
F 0 "#PWR014" H 5450 700 30  0001 C CNN
F 1 "GND" H 5450 630 30  0001 C CNN
F 2 "" H 5450 700 60  0000 C CNN
F 3 "" H 5450 700 60  0000 C CNN
	1    5450 700 
	0    -1   -1   0   
$EndComp
Text GLabel 4400 4650 0    60   Input ~ 0
pinOdometryLeft
Text GLabel 5450 1550 2    60   Output ~ 0
pinOdometryLeft
Text GLabel 5450 850  2    60   Output ~ 0
pinOdometryRight
$Comp
L CONN_4 P9
U 1 1 53852DC8
P 4900 1550
F 0 "P9" V 4850 1550 50  0000 C CNN
F 1 "ODO Left" V 4950 1550 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 4900 1550 60  0001 C CNN
F 3 "" H 4900 1550 60  0000 C CNN
	1    4900 1550
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 53852DD4
P 5450 1400
F 0 "#PWR015" H 5450 1400 30  0001 C CNN
F 1 "GND" H 5450 1330 30  0001 C CNN
F 2 "" H 5450 1400 60  0000 C CNN
F 3 "" H 5450 1400 60  0000 C CNN
	1    5450 1400
	0    -1   -1   0   
$EndComp
Text GLabel 5450 1700 2    60   Output ~ 0
pinOdometryLeft2
$Comp
L CONN_3 P19
U 1 1 5385309E
P 3775 7000
F 0 "P19" V 3725 7000 50  0000 C CNN
F 1 "Tilt sens" V 3825 7000 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 3775 7000 60  0001 C CNN
F 3 "" H 3775 7000 60  0000 C CNN
	1    3775 7000
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 538530CC
P 4275 7000
F 0 "#PWR016" H 4275 7000 30  0001 C CNN
F 1 "GND" H 4275 6930 30  0001 C CNN
F 2 "" H 4275 7000 60  0000 C CNN
F 3 "" H 4275 7000 60  0000 C CNN
	1    4275 7000
	0    -1   -1   0   
$EndComp
$Comp
L CONN_4 P6
U 1 1 5385368B
P 1775 2425
F 0 "P6" V 1725 2425 50  0000 C CNN
F 1 "Lawn sens" V 1825 2425 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 1775 2425 60  0001 C CNN
F 3 "" H 1775 2425 60  0000 C CNN
	1    1775 2425
	-1   0    0    -1  
$EndComp
Text GLabel 2825 2475 2    60   Input ~ 0
pinLawnBackSend
Text GLabel 2225 2625 2    60   Output ~ 0
pinLawnBackRecv
Text GLabel 2825 2175 2    60   Input ~ 0
pinLawnFrontSend
Text GLabel 2225 2325 2    60   Output ~ 0
pinLawnFrontRecv
$Comp
L R R3
U 1 1 538536B3
P 2475 2475
F 0 "R3" V 2555 2475 40  0000 C CNN
F 1 "2M2" V 2482 2476 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2405 2475 30  0001 C CNN
F 3 "~" H 2475 2475 30  0000 C CNN
	1    2475 2475
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 538536C2
P 2475 2175
F 0 "R4" V 2555 2175 40  0000 C CNN
F 1 "2M2" V 2482 2176 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2405 2175 30  0001 C CNN
F 3 "~" H 2475 2175 30  0000 C CNN
	1    2475 2175
	0    -1   -1   0   
$EndComp
Text Notes 3675 2625 2    60   ~ 0
Lawn sensor\n\n\n\n
Text Notes 4775 7350 2    60   ~ 0
Tilt sensor\n\n\n\n\n
$Comp
L MC33926 Dual1
U 1 1 538656B8
P 13500 1750
F 0 "Dual1" H 13450 800 60  0000 C CNN
F 1 "MC33926" H 13500 2900 60  0000 C CNN
F 2 "ACS712:MC_33926_31polig" H 13650 1800 60  0001 C CNN
F 3 "" H 13650 1800 60  0000 C CNN
	1    13500 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 538656C7
P 12500 1900
F 0 "#PWR017" H 12500 1900 30  0001 C CNN
F 1 "GND" H 12500 1830 30  0001 C CNN
F 2 "" H 12500 1900 60  0000 C CNN
F 3 "" H 12500 1900 60  0000 C CNN
	1    12500 1900
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR018
U 1 1 538656D6
P 12500 2000
F 0 "#PWR018" H 12500 2090 20  0001 C CNN
F 1 "+5V" H 12500 2090 30  0000 C CNN
F 2 "" H 12500 2000 60  0000 C CNN
F 3 "" H 12500 2000 60  0000 C CNN
	1    12500 2000
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR019
U 1 1 538656F4
P 12500 1100
F 0 "#PWR019" H 12500 1190 20  0001 C CNN
F 1 "+5V" H 12500 1190 30  0000 C CNN
F 2 "" H 12500 1100 60  0000 C CNN
F 3 "" H 12500 1100 60  0000 C CNN
	1    12500 1100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR020
U 1 1 53865703
P 12500 1000
F 0 "#PWR020" H 12500 1000 30  0001 C CNN
F 1 "GND" H 12500 930 30  0001 C CNN
F 2 "" H 12500 1000 60  0000 C CNN
F 3 "" H 12500 1000 60  0000 C CNN
	1    12500 1000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR021
U 1 1 53865B59
P 12500 2400
F 0 "#PWR021" H 12500 2400 30  0001 C CNN
F 1 "GND" H 12500 2330 30  0001 C CNN
F 2 "" H 12500 2400 60  0000 C CNN
F 3 "" H 12500 2400 60  0000 C CNN
	1    12500 2400
	0    1    1    0   
$EndComp
Text GLabel 12350 1700 0    60   Output ~ 0
pinMotorLeftSense
Text GLabel 12350 800  0    60   Output ~ 0
pinMotorRightSense
Text GLabel 12350 2250 0    60   Input ~ 0
pinMotorLeftDir
Text GLabel 12350 1200 0    60   Input ~ 0
pinMotorRightPWM
Text GLabel 12350 2100 0    60   Input ~ 0
pinMotorLeftPWM
Text GLabel 12350 1350 0    60   Input ~ 0
pinMotorRightDir
NoConn ~ 12650 2500
NoConn ~ 12650 1400
NoConn ~ 12650 1500
$Comp
L CONN_4 P10
U 1 1 538663DA
P 12500 6900
F 0 "P10" V 12450 6900 50  0000 C CNN
F 1 "GPS" V 12550 6900 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 12500 6900 60  0001 C CNN
F 3 "" H 12500 6900 60  0000 C CNN
	1    12500 6900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 538663E0
P 11950 6850
F 0 "#PWR022" H 11950 6850 30  0001 C CNN
F 1 "GND" H 11950 6780 30  0001 C CNN
F 2 "" H 11950 6850 60  0000 C CNN
F 3 "" H 11950 6850 60  0000 C CNN
	1    11950 6850
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR023
U 1 1 538663E6
P 11950 6750
F 0 "#PWR023" H 11950 6840 20  0001 C CNN
F 1 "+5V" H 11950 6840 30  0000 C CNN
F 2 "" H 11950 6750 60  0000 C CNN
F 3 "" H 11950 6750 60  0000 C CNN
	1    11950 6750
	0    -1   -1   0   
$EndComp
Text GLabel 11700 6850 0    60   Input ~ 0
GPS_RX
Text GLabel 11700 7050 0    60   Output ~ 0
GPS_TX
Text Notes 12600 6650 2    60   ~ 0
GPS\n
Text GLabel 9300 4050 2    60   Input ~ 0
GPS_RX
Text GLabel 9750 4150 2    60   Output ~ 0
GPS_TX
Text GLabel 9300 4250 2    60   Output ~ 0
TX2
Text GLabel 9750 4350 2    60   Input ~ 0
RX2
$Comp
L CONN_2 Batterie1
U 1 1 53866CB8
P 8100 7600
F 0 "Batterie1" V 8050 7600 40  0000 C CNN
F 1 "DC/DC" V 8150 7600 40  0000 C CNN
F 2 "ACS712:Aschlussklemme_2p_3D" H 8100 7600 98  0001 C CNN
F 3 "" H 8100 7600 60  0000 C CNN
	1    8100 7600
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR024
U 1 1 53866CD6
P 8450 7750
F 0 "#PWR024" H 8450 7750 30  0001 C CNN
F 1 "GND" H 8450 7680 30  0001 C CNN
F 2 "" H 8450 7750 60  0000 C CNN
F 3 "" H 8450 7750 60  0000 C CNN
	1    8450 7750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 53866E0D
P 11450 9150
F 0 "#PWR025" H 11450 9150 30  0001 C CNN
F 1 "GND" H 11450 9080 30  0001 C CNN
F 2 "" H 11450 9150 60  0000 C CNN
F 3 "" H 11450 9150 60  0000 C CNN
	1    11450 9150
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR026
U 1 1 53866E1C
P 5800 2850
F 0 "#PWR026" H 5800 2850 30  0001 C CNN
F 1 "GND" H 5800 2780 30  0001 C CNN
F 2 "" H 5800 2850 60  0000 C CNN
F 3 "" H 5800 2850 60  0000 C CNN
	1    5800 2850
	0    1    1    0   
$EndComp
$Comp
L CP1 C2
U 1 1 53866E3A
P 11650 9650
F 0 "C2" H 11700 9750 50  0000 L CNN
F 1 "100uF" H 11700 9550 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 11650 9650 60  0001 C CNN
F 3 "~" H 11650 9650 60  0000 C CNN
	1    11650 9650
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P5
U 1 1 53867437
P 2800 5100
F 0 "P5" V 2750 5100 50  0000 C CNN
F 1 "IMU Kompas" V 2850 5100 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 2800 5100 60  0001 C CNN
F 3 "" H 2800 5100 60  0000 C CNN
	1    2800 5100
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 53867444
P 3250 5000
F 0 "#PWR027" H 3250 5000 30  0001 C CNN
F 1 "GND" H 3250 4930 30  0001 C CNN
F 2 "" H 3250 5000 60  0000 C CNN
F 3 "" H 3250 5000 60  0000 C CNN
	1    3250 5000
	0    -1   1    0   
$EndComp
Text GLabel 3350 5250 2    60   Input ~ 0
SCL2
Text GLabel 3350 5100 2    60   BiDi ~ 0
SDA2
Text GLabel 6250 6100 0    60   Input ~ 0
pinUserSwitch2
Text GLabel 13800 6900 0    60   Input ~ 0
pinBumperRight
Text GLabel 13800 7100 0    60   Output ~ 0
pinBumperLeft
Text Notes 14750 6800 2    60   ~ 0
Bumper\n\n
$Comp
L CONN_6 P13
U 1 1 538A4012
P 14700 7750
F 0 "P13" V 14650 7750 60  0000 C CNN
F 1 "RC Remote" V 14750 7750 60  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x06_3D" H 14700 7750 60  0001 C CNN
F 3 "" H 14700 7750 60  0000 C CNN
	1    14700 7750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 538A4021
P 13950 7450
F 0 "#PWR028" H 13950 7450 30  0001 C CNN
F 1 "GND" H 13950 7380 30  0001 C CNN
F 2 "" H 13950 7450 60  0000 C CNN
F 3 "" H 13950 7450 60  0000 C CNN
	1    13950 7450
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR029
U 1 1 538A4030
P 14250 7350
F 0 "#PWR029" H 14250 7440 20  0001 C CNN
F 1 "+5V" H 14250 7440 30  0000 C CNN
F 2 "" H 14250 7350 60  0000 C CNN
F 3 "" H 14250 7350 60  0000 C CNN
	1    14250 7350
	1    0    0    -1  
$EndComp
Text GLabel 13950 7600 0    60   Output ~ 0
pinRemoteMow
Text GLabel 13950 7750 0    60   Output ~ 0
pinRemoteSteer
Text GLabel 13950 7900 0    60   Output ~ 0
pinRemoteSpeed
Text GLabel 13950 8050 0    60   Output ~ 0
pinRemoteSwitch
Text GLabel 10450 2550 2    60   Input ~ 0
pinRemoteMow
Text GLabel 9450 2650 2    60   Input ~ 0
pinRemoteSteer
Text GLabel 10450 2750 2    60   Input ~ 0
pinRemoteSpeed
$Comp
L R R1
U 1 1 538A5BD3
P 4500 2175
F 0 "R1" V 4580 2175 40  0000 C CNN
F 1 "220" V 4507 2176 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 4430 2175 30  0001 C CNN
F 3 "~" H 4500 2175 30  0000 C CNN
	1    4500 2175
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 538A5BE2
P 4500 2475
F 0 "R2" V 4580 2475 40  0000 C CNN
F 1 "1K5" V 4507 2476 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 4430 2475 30  0001 C CNN
F 3 "~" H 4500 2475 30  0000 C CNN
	1    4500 2475
	0    -1   -1   0   
$EndComp
Text GLabel 10250 6100 2    60   Output ~ 0
pinSonarRightTrigger
Text GLabel 10250 5850 2    60   Output ~ 0
pinMotorMowEnable
Text GLabel 10250 6300 2    60   Input ~ 0
pinSonarRightEcho
Text GLabel 12250 1500 0    60   Input ~ 0
pinMotorEnable
Text GLabel 12350 1850 0    60   Output ~ 0
pinMotorLeftFault
Text GLabel 12350 950  0    60   Output ~ 0
pinMotorRightFault
$Comp
L GND #PWR030
U 1 1 539E196E
P 6800 1150
F 0 "#PWR030" H 6800 1150 30  0001 C CNN
F 1 "GND" H 6800 1080 30  0001 C CNN
F 2 "" H 6800 1150 60  0000 C CNN
F 3 "" H 6800 1150 60  0000 C CNN
	1    6800 1150
	0    -1   -1   0   
$EndComp
Text GLabel 6850 1500 2    60   Output ~ 0
pinButton
Text GLabel 5350 6000 0    60   Input ~ 0
pinMotorMowRpm
Text GLabel 5350 5750 0    60   Input ~ 0
pinButton
Text GLabel 10250 5650 2    60   Input ~ 0
pinMotorMowFault
Text GLabel 10250 5450 2    60   Input ~ 0
pinSonarCenterTrigger
Text GLabel 10250 5250 2    60   Input ~ 0
pinSonarCenterEcho
Text GLabel 4600 5650 0    60   Input ~ 0
pinRemoteSwitch
Text GLabel 7100 6200 0    60   Input ~ 0
pinUserSwitch1
Text GLabel 7100 6000 0    60   Input ~ 0
pinUserSwitch3
$Comp
L JUMPER JP1
U 1 1 5417E831
P 11950 9400
F 0 "JP1" H 11950 9550 60  0000 C CNN
F 1 "pwr 10V" H 11950 9320 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 11950 9400 60  0001 C CNN
F 3 "" H 11950 9400 60  0000 C CNN
	1    11950 9400
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P11
U 1 1 53878C5D
P 14600 6950
F 0 "P11" V 14550 6950 50  0000 C CNN
F 1 "Bumper" V 14650 6950 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x04_3D" H 14600 6950 60  0001 C CNN
F 3 "" H 14600 6950 60  0000 C CNN
	1    14600 6950
	1    0    0    -1  
$EndComp
Text GLabel 4825 3175 2    60   Output ~ 0
pinRain
$Comp
L MC33926 Dual2
U 1 1 541DE74B
P 13500 4400
F 0 "Dual2" H 13450 3450 60  0000 C CNN
F 1 "MC33926" H 13500 5550 60  0000 C CNN
F 2 "ACS712:MC_33926_31polig" H 13650 4450 60  0001 C CNN
F 3 "" H 13650 4450 60  0000 C CNN
	1    13500 4400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR031
U 1 1 541DE75D
P 12500 3750
F 0 "#PWR031" H 12500 3840 20  0001 C CNN
F 1 "+5V" H 12500 3840 30  0000 C CNN
F 2 "" H 12500 3750 60  0000 C CNN
F 3 "" H 12500 3750 60  0000 C CNN
	1    12500 3750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR032
U 1 1 541DE763
P 12500 3650
F 0 "#PWR032" H 12500 3650 30  0001 C CNN
F 1 "GND" H 12500 3580 30  0001 C CNN
F 2 "" H 12500 3650 60  0000 C CNN
F 3 "" H 12500 3650 60  0000 C CNN
	1    12500 3650
	0    1    1    0   
$EndComp
Text GLabel 12350 3450 0    60   Output ~ 0
pinMotorMowSense
Text GLabel 12350 3850 0    60   Input ~ 0
pinMotorMowPWM
Text GLabel 12350 4000 0    60   Input ~ 0
pinMotorMowDir
NoConn ~ 12650 5150
NoConn ~ 12650 4050
NoConn ~ 12650 4150
Text GLabel 12250 4150 0    60   Input ~ 0
pinMotorMowEnable
Text GLabel 12350 3600 0    60   Output ~ 0
pinMotorMowFault
$Comp
L GND #PWR033
U 1 1 541DE7A5
P 14375 4325
F 0 "#PWR033" H 14375 4325 30  0001 C CNN
F 1 "GND" H 14375 4255 30  0001 C CNN
F 2 "" H 14375 4325 60  0000 C CNN
F 3 "" H 14375 4325 60  0000 C CNN
	1    14375 4325
	1    0    0    -1  
$EndComp
NoConn ~ 12650 4350
NoConn ~ 12650 4450
NoConn ~ 12650 4550
NoConn ~ 12650 4650
NoConn ~ 12650 4750
NoConn ~ 12650 4850
$Comp
L +5V #PWR034
U 1 1 541E6ED6
P 5700 1950
F 0 "#PWR034" H 5700 2040 20  0001 C CNN
F 1 "+5V" H 5700 2040 30  0000 C CNN
F 2 "" H 5700 1950 60  0000 C CNN
F 3 "" H 5700 1950 60  0000 C CNN
	1    5700 1950
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR035
U 1 1 541E96E8
P 12550 8500
F 0 "#PWR035" H 12550 8460 30  0001 C CNN
F 1 "+3.3V" H 12550 8610 30  0000 C CNN
F 2 "" H 12550 8500 60  0000 C CNN
F 3 "" H 12550 8500 60  0000 C CNN
	1    12550 8500
	0    1    1    0   
$EndComp
$Comp
L +24V #PWR036
U 1 1 541EAD0D
P 14375 4000
F 0 "#PWR036" H 14375 3950 20  0001 C CNN
F 1 "+24V" H 14375 4100 30  0000 C CNN
F 2 "" H 14375 4000 60  0000 C CNN
F 3 "" H 14375 4000 60  0000 C CNN
	1    14375 4000
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR037
U 1 1 54158880
P 4150 2375
F 0 "#PWR037" H 4150 2325 20  0001 C CNN
F 1 "+24V" H 4150 2475 30  0000 C CNN
F 2 "" H 4150 2375 60  0000 C CNN
F 3 "" H 4150 2375 60  0000 C CNN
	1    4150 2375
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR038
U 1 1 54159F8C
P 1725 1600
F 0 "#PWR038" H 1725 1690 20  0001 C CNN
F 1 "+5V" H 1725 1690 30  0000 C CNN
F 2 "" H 1725 1600 60  0000 C CNN
F 3 "" H 1725 1600 60  0000 C CNN
	1    1725 1600
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR039
U 1 1 5415DC99
P 5250 700
F 0 "#PWR039" H 5250 790 20  0001 C CNN
F 1 "+5V" H 5250 790 30  0000 C CNN
F 2 "" H 5250 700 60  0000 C CNN
F 3 "" H 5250 700 60  0000 C CNN
	1    5250 700 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR040
U 1 1 5415E01C
P 1100 4900
F 0 "#PWR040" H 1100 4990 20  0001 C CNN
F 1 "+5V" H 1100 4990 30  0000 C CNN
F 2 "" H 1100 4900 60  0000 C CNN
F 3 "" H 1100 4900 60  0000 C CNN
	1    1100 4900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR041
U 1 1 5415E303
P 5300 1300
F 0 "#PWR041" H 5300 1390 20  0001 C CNN
F 1 "+5V" H 5300 1390 30  0000 C CNN
F 2 "" H 5300 1300 60  0000 C CNN
F 3 "" H 5300 1300 60  0000 C CNN
	1    5300 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR042
U 1 1 5415E5B6
P 12500 2300
F 0 "#PWR042" H 12500 2390 20  0001 C CNN
F 1 "+5V" H 12500 2390 30  0000 C CNN
F 2 "" H 12500 2300 60  0000 C CNN
F 3 "" H 12500 2300 60  0000 C CNN
	1    12500 2300
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR043
U 1 1 5416025F
P 4125 6750
F 0 "#PWR043" H 4125 6840 20  0001 C CNN
F 1 "+5V" H 4125 6840 30  0000 C CNN
F 2 "" H 4125 6750 60  0000 C CNN
F 3 "" H 4125 6750 60  0000 C CNN
	1    4125 6750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR044
U 1 1 54163106
P 1150 2250
F 0 "#PWR044" H 1150 2340 20  0001 C CNN
F 1 "+5V" H 1150 2340 30  0000 C CNN
F 2 "" H 1150 2250 60  0000 C CNN
F 3 "" H 1150 2250 60  0000 C CNN
	1    1150 2250
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P18
U 1 1 54168B06
P 14875 900
F 0 "P18" V 14825 900 40  0000 C CNN
F 1 "Mow Motor" V 14925 900 40  0000 C CNN
F 2 "Connect:PINHEAD1-2" H 14875 900 60  0001 C CNN
F 3 "" H 14875 900 60  0000 C CNN
	1    14875 900 
	1    0    0    1   
$EndComp
$Comp
L GND #PWR045
U 1 1 5416EE98
P 1225 8000
F 0 "#PWR045" H 1225 8000 30  0001 C CNN
F 1 "GND" H 1225 7930 30  0001 C CNN
F 2 "" H 1225 8000 60  0000 C CNN
F 3 "" H 1225 8000 60  0000 C CNN
	1    1225 8000
	1    0    0    -1  
$EndComp
$Comp
L ACS712 U3
U 1 1 5417150B
P 3450 8600
F 0 "U3" H 3450 8850 50  0000 C CNN
F 1 "INA169 Adafruit" H 3450 8350 50  0000 C CNN
F 2 "ACS712:INA169" H 3450 8600 60  0000 C CNN
F 3 "" H 3450 8600 60  0000 C CNN
	1    3450 8600
	0    1    1    0   
$EndComp
Text Notes 7750 7950 0    99   ~ 0
Batterie\n
$Comp
L +5V #PWR046
U 1 1 54172399
P 3550 9100
F 0 "#PWR046" H 3550 9190 20  0001 C CNN
F 1 "+5V" H 3550 9190 30  0000 C CNN
F 2 "" H 3550 9100 60  0000 C CNN
F 3 "" H 3550 9100 60  0000 C CNN
	1    3550 9100
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR047
U 1 1 54172562
P 3300 9450
F 0 "#PWR047" H 3300 9450 30  0001 C CNN
F 1 "GND" H 3300 9380 30  0001 C CNN
F 2 "" H 3300 9450 60  0000 C CNN
F 3 "" H 3300 9450 60  0000 C CNN
	1    3300 9450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 541751D4
P 6700 10600
F 0 "#PWR048" H 6700 10600 30  0001 C CNN
F 1 "GND" H 6700 10530 30  0001 C CNN
F 2 "" H 6700 10600 60  0000 C CNN
F 3 "" H 6700 10600 60  0000 C CNN
	1    6700 10600
	1    0    0    -1  
$EndComp
Text GLabel 4600 5850 0    60   Output ~ 0
pinChargingEnable
$Comp
L CONN_2 Ladeanschluss1
U 1 1 541A0C85
P 1325 7500
F 0 "Ladeanschluss1" V 1275 7500 40  0000 C CNN
F 1 "DC/DC" V 1375 7500 40  0000 C CNN
F 2 "ACS712:Aschlussklemme_2p_3D" H 1325 7500 98  0001 C CNN
F 3 "" H 1325 7500 60  0000 C CNN
	1    1325 7500
	0    -1   -1   0   
$EndComp
$Comp
L CONN_2 P15
U 1 1 541D1F00
P 14875 2150
F 0 "P15" V 14825 2150 40  0000 C CNN
F 1 "Dual2-M1Out" V 14925 2150 40  0000 C CNN
F 2 "Connect:PINHEAD1-2" H 14875 2150 60  0001 C CNN
F 3 "" H 14875 2150 60  0000 C CNN
	1    14875 2150
	1    0    0    1   
$EndComp
Text GLabel 4750 2175 2    60   Output ~ 0
LedPin-5v
Text GLabel 4750 2475 2    60   Output ~ 0
LedPin-24v
Text GLabel 9750 2450 2    60   Output ~ 0
Led-Status
Text GLabel 9525 1200 0    60   Input ~ 0
LedPin-5v
Text GLabel 10175 1100 0    60   Input ~ 0
LedPin-24v
Text GLabel 9550 1600 0    60   Input ~ 0
Led-Status
$Comp
L CONN_01X02 P20
U 1 1 541DAF9A
P 6500 1450
F 0 "P20" H 6500 1600 50  0000 C CNN
F 1 "Button" V 6600 1450 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x02_3D" H 6500 1450 60  0001 C CNN
F 3 "" H 6500 1450 60  0000 C CNN
	1    6500 1450
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P16
U 1 1 541D656A
P 14875 1500
F 0 "P16" V 14825 1500 40  0000 C CNN
F 1 "Dual2-pwr" V 14925 1500 40  0000 C CNN
F 2 "Connect:PINHEAD1-2" H 14875 1500 60  0001 C CNN
F 3 "" H 14875 1500 60  0000 C CNN
	1    14875 1500
	1    0    0    1   
$EndComp
$Comp
L CONN_2 P17
U 1 1 541D7765
P 14875 4150
F 0 "P17" V 14825 4150 40  0000 C CNN
F 1 "Dual2-pwr" V 14925 4150 40  0000 C CNN
F 2 "Connect:PINHEAD1-2" H 14875 4150 60  0001 C CNN
F 3 "" H 14875 4150 60  0000 C CNN
	1    14875 4150
	1    0    0    1   
$EndComp
$Comp
L CP1 C3
U 1 1 541DF105
P 3500 9400
F 0 "C3" H 3550 9500 50  0000 L CNN
F 1 "0,1uF" H 3550 9300 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 3500 9400 60  0001 C CNN
F 3 "~" H 3500 9400 60  0000 C CNN
	1    3500 9400
	0    1    1    0   
$EndComp
$Comp
L DC-DC_Stepdown U1
U 1 1 5459779F
P 11100 9300
F 0 "U1" H 11100 9350 60  0000 C CNN
F 1 "DC 10V" H 11100 9050 60  0000 C CNN
F 2 "ACS712:DC-DC" H 12900 9200 60  0001 C CNN
F 3 "" H 12900 9200 60  0000 C CNN
	1    11100 9300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 54597FC1
P 10750 9150
F 0 "#PWR049" H 10750 9150 30  0001 C CNN
F 1 "GND" H 10750 9080 30  0001 C CNN
F 2 "" H 10750 9150 60  0000 C CNN
F 3 "" H 10750 9150 60  0000 C CNN
	1    10750 9150
	-1   0    0    1   
$EndComp
Text GLabel 9650 4650 2    60   BiDi ~ 0
SDA1
Text GLabel 9650 4800 2    60   Output ~ 0
SCL1
Text Label 3250 5250 2    60   ~ 0
SCL
Text Label 3250 5100 2    60   ~ 0
SDA
Text Label 9350 4550 0    60   ~ 0
SDA
Text Label 9350 4900 0    60   ~ 0
SCL
$Comp
L R_PACK8 RP1
U 1 1 5478A23C
P 5750 3700
F 0 "RP1" H 5750 3600 40  0000 C CNN
F 1 "150" H 5750 3250 40  0000 C CNN
F 2 "Sockets_DIP:DIP-16__300" H 5750 3700 60  0001 C CNN
F 3 "" H 5750 3700 60  0000 C CNN
	1    5750 3700
	1    0    0    1   
$EndComp
$Comp
L RR8 RR1
U 1 1 54994E69
P 6450 2450
F 0 "RR1" H 6500 3000 70  0000 C CNN
F 1 "C100uF" V 6480 2450 70  0000 C CNN
F 2 "ACS712:Kondensatorenleiste_8er_9pin_3D" H 6450 2450 60  0001 C CNN
F 3 "" H 6450 2450 60  0000 C CNN
	1    6450 2450
	0    -1   -1   0   
$EndComp
$Comp
L RR8 RR2
U 1 1 5499A2BD
P 6450 5450
F 0 "RR2" H 6500 6000 70  0000 C CNN
F 1 "C100uF" V 6480 5450 70  0000 C CNN
F 2 "ACS712:Kondensatorenleiste_8er_9pin_3D" H 6450 5450 60  0001 C CNN
F 3 "" H 6450 5450 60  0000 C CNN
	1    6450 5450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR050
U 1 1 5499A343
P 7000 5100
F 0 "#PWR050" H 7000 5100 30  0001 C CNN
F 1 "GND" H 7000 5030 30  0001 C CNN
F 2 "" H 7000 5100 60  0000 C CNN
F 3 "" H 7000 5100 60  0000 C CNN
	1    7000 5100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR051
U 1 1 54999A98
P 11650 9000
F 0 "#PWR051" H 11650 9000 30  0001 C CNN
F 1 "GND" H 11650 8930 30  0001 C CNN
F 2 "" H 11650 9000 60  0000 C CNN
F 3 "" H 11650 9000 60  0000 C CNN
	1    11650 9000
	1    0    0    -1  
$EndComp
Text GLabel 6650 2150 0    60   Input ~ 0
Power
Text GLabel 12550 9400 2    60   Output ~ 0
Power
$Comp
L RELAY_2RT K3
U 1 1 54A679F2
P 7100 8500
F 0 "K3" H 7050 8900 70  0000 C CNN
F 1 "RELAY_2RT" H 7250 8000 70  0000 C CNN
F 2 "ACS712:Relais_DPDT_Schrack-RT2_RM5mm_3D" H 7100 8500 60  0001 C CNN
F 3 "" H 7100 8500 60  0000 C CNN
	1    7100 8500
	1    0    0    -1  
$EndComp
$Comp
L F_10A EF1
U 1 1 54A79B5A
P 1625 8000
F 0 "EF1" H 1445 8080 40  0000 C CNN
F 1 "F_10A" H 1525 7920 40  0000 C CNN
F 2 "ACS712:BladeFuse-Mini" H 1625 8000 60  0001 C CNN
F 3 "" H 1625 8000 60  0000 C CNN
	1    1625 8000
	-1   0    0    1   
$EndComp
$Comp
L F_10A EF2
U 1 1 54A7AB0D
P 8800 7500
F 0 "EF2" H 8620 7580 40  0000 C CNN
F 1 "F_10A" H 8700 7420 40  0000 C CNN
F 2 "ACS712:BladeFuse-Mini" H 8800 7500 60  0001 C CNN
F 3 "" H 8800 7500 60  0000 C CNN
	1    8800 7500
	1    0    0    -1  
$EndComp
$Comp
L DIODE D2
U 1 1 54A7D925
P 14725 3550
F 0 "D2" H 14725 3650 40  0000 C CNN
F 1 "MBR1045" H 14725 3450 40  0000 C CNN
F 2 "ACS712:MBR1045_liegend" H 14725 3550 60  0001 C CNN
F 3 "" H 14725 3550 60  0000 C CNN
	1    14725 3550
	1    0    0    -1  
$EndComp
Text GLabel 6200 6300 0    60   Input ~ 0
DropLeft
Text GLabel 9250 5350 2    60   Input ~ 0
DropRight
Text GLabel 10450 4400 2    60   Input ~ 0
TX1
Text GLabel 10450 4550 2    60   Input ~ 0
RX1
Text GLabel 1325 3750 3    60   Input ~ 0
RX1
Text GLabel 1325 2450 1    60   Input ~ 0
TX1
$Comp
L R R15
U 1 1 54B23352
P 1325 2700
F 0 "R15" V 1405 2700 40  0000 C CNN
F 1 "470R" V 1332 2701 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 1255 2700 30  0001 C CNN
F 3 "~" H 1325 2700 30  0000 C CNN
	1    1325 2700
	-1   0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 54B23358
P 1625 2950
F 0 "R16" V 1705 2950 40  0000 C CNN
F 1 "1K" V 1632 2951 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 1555 2950 30  0001 C CNN
F 3 "~" H 1625 2950 30  0000 C CNN
	1    1625 2950
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR052
U 1 1 54B2335E
P 1975 2950
F 0 "#PWR052" H 1975 2950 30  0001 C CNN
F 1 "GND" H 1975 2880 30  0001 C CNN
F 2 "" H 1975 2950 60  0000 C CNN
F 3 "" H 1975 2950 60  0000 C CNN
	1    1975 2950
	0    -1   1    0   
$EndComp
$Comp
L R R14
U 1 1 54B24323
P 1625 3650
F 0 "R14" V 1705 3650 40  0000 C CNN
F 1 "1K" V 1632 3651 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 1555 3650 30  0001 C CNN
F 3 "~" H 1625 3650 30  0000 C CNN
	1    1625 3650
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR053
U 1 1 54B24329
P 1975 3650
F 0 "#PWR053" H 1975 3740 20  0001 C CNN
F 1 "+5V" H 1975 3740 30  0000 C CNN
F 2 "" H 1975 3650 60  0000 C CNN
F 3 "" H 1975 3650 60  0000 C CNN
	1    1975 3650
	0    1    -1   0   
$EndComp
$Comp
L BC237 Q1
U 1 1 54B46879
P 6600 10100
F 0 "Q1" H 6800 10000 50  0000 C CNN
F 1 "BC237" H 6850 10250 50  0000 C CNN
F 2 "Discret:TO92-EBC" H 6790 10100 30  0001 C CNN
F 3 "" H 6600 10100 60  0000 C CNN
	1    6600 10100
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 54B46970
P 6050 10100
F 0 "R18" V 6130 10100 40  0000 C CNN
F 1 "2k2" V 6057 10101 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 5980 10100 30  0001 C CNN
F 3 "" H 6050 10100 30  0000 C CNN
	1    6050 10100
	0    -1   -1   0   
$EndComp
$Comp
L LM350T U4
U 1 1 54B48E94
P 4800 8300
F 0 "U4" H 4600 8500 40  0000 C CNN
F 1 "LM350T" H 4800 8500 40  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 4800 8400 30  0001 C CIN
F 3 "" H 4800 8300 60  0000 C CNN
	1    4800 8300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 54B48E9A
P 4350 8450
F 0 "C1" H 4350 8550 40  0000 L CNN
F 1 "1uF" H 4356 8365 40  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 4388 8300 30  0001 C CNN
F 3 "" H 4350 8450 60  0000 C CNN
	1    4350 8450
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 54B48EA0
P 5550 8450
F 0 "C4" H 5550 8550 40  0000 L CNN
F 1 "1uF" H 5556 8365 40  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 5588 8300 30  0001 C CNN
F 3 "" H 5550 8450 60  0000 C CNN
	1    5550 8450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR054
U 1 1 54B48EA8
P 4350 8850
F 0 "#PWR054" H 4350 8850 30  0001 C CNN
F 1 "GND" H 4350 8780 30  0001 C CNN
F 2 "" H 4350 8850 60  0000 C CNN
F 3 "" H 4350 8850 60  0000 C CNN
	1    4350 8850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR055
U 1 1 54B48EAE
P 5550 8850
F 0 "#PWR055" H 5550 8850 30  0001 C CNN
F 1 "GND" H 5550 8780 30  0001 C CNN
F 2 "" H 5550 8850 60  0000 C CNN
F 3 "" H 5550 8850 60  0000 C CNN
	1    5550 8850
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 54B48EBA
P 5300 8550
F 0 "R17" V 5380 8550 40  0000 C CNN
F 1 "240" V 5307 8551 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 5230 8550 30  0001 C CNN
F 3 "" H 5300 8550 30  0000 C CNN
	1    5300 8550
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 54B48EC0
P 4800 8900
F 0 "RV1" H 4800 8800 50  0000 C CNN
F 1 "5K" H 4800 8900 50  0000 C CNN
F 2 "ACS712:Potentiometer_VishaySpectrol-Econtrim-Type36T_3D" H 4800 8900 60  0001 C CNN
F 3 "" H 4800 8900 60  0000 C CNN
	1    4800 8900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR056
U 1 1 54B48ECF
P 5150 9150
F 0 "#PWR056" H 5150 9150 30  0001 C CNN
F 1 "GND" H 5150 9080 30  0001 C CNN
F 2 "" H 5150 9150 60  0000 C CNN
F 3 "" H 5150 9150 60  0000 C CNN
	1    5150 9150
	0    -1   -1   0   
$EndComp
$Comp
L JUMPER JP6
U 1 1 54B504F9
P 8700 9250
F 0 "JP6" H 8700 9400 60  0000 C CNN
F 1 "V-A-Relais" H 8700 9170 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8700 9250 60  0001 C CNN
F 3 "" H 8700 9250 60  0000 C CNN
	1    8700 9250
	0    -1   -1   0   
$EndComp
$Comp
L JUMPER JP7
U 1 1 54B50727
P 9450 9200
F 0 "JP7" H 9450 9350 60  0000 C CNN
F 1 "V-A-Relais" H 9450 9120 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 9450 9200 60  0001 C CNN
F 3 "" H 9450 9200 60  0000 C CNN
	1    9450 9200
	0    -1   -1   0   
$EndComp
$Comp
L CP1 C5
U 1 1 54B51225
P 9450 10025
F 0 "C5" H 9500 10125 50  0000 L CNN
F 1 "470uF" H 9500 9925 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 9450 10025 60  0001 C CNN
F 3 "~" H 9450 10025 60  0000 C CNN
	1    9450 10025
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR057
U 1 1 54B5122B
P 9450 10275
F 0 "#PWR057" H 9450 10275 30  0001 C CNN
F 1 "GND" H 9450 10205 30  0001 C CNN
F 2 "" H 9450 10275 60  0000 C CNN
F 3 "" H 9450 10275 60  0000 C CNN
	1    9450 10275
	1    0    0    -1  
$EndComp
Text Notes 9150 10525 0    60   ~ 0
Pufferkondensator\nfür Relaisumschaltung
Text Notes 9550 9100 0    39   ~ 0
Jumper Spannungsversorgung \nvon Akku
Text Notes 7750 9150 0    39   ~ 0
Jumper Spannungsversorgung \nvon über Relais
$Comp
L R R19
U 1 1 54B574C4
P 6450 8250
F 0 "R19" V 6530 8250 40  0000 C CNN
F 1 "????" V 6457 8251 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 6380 8250 30  0001 C CNN
F 3 "" H 6450 8250 30  0000 C CNN
	1    6450 8250
	1    0    0    -1  
$EndComp
Text GLabel 5000 10100 0    60   Output ~ 0
pinChargingEnable
$Comp
L JUMPER JP4
U 1 1 54B57EFB
P 5400 10100
F 0 "JP4" H 5400 10250 60  0000 C CNN
F 1 "R-Arduino" H 5400 10020 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 5400 10100 60  0001 C CNN
F 3 "" H 5400 10100 60  0000 C CNN
	1    5400 10100
	1    0    0    -1  
$EndComp
Text Notes 5050 10400 0    39   ~ 0
Jumper Relais\nEin oder Ausschalten Ansteuerung\ndurch Arduino
$Comp
L JUMPER JP5
U 1 1 54B5A1C5
P 7400 10200
F 0 "JP5" H 7400 10350 60  0000 C CNN
F 1 "R-GND" H 7400 10120 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 7400 10200 60  0001 C CNN
F 3 "" H 7400 10200 60  0000 C CNN
	1    7400 10200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR058
U 1 1 54B5A511
P 7400 10600
F 0 "#PWR058" H 7400 10600 30  0001 C CNN
F 1 "GND" H 7400 10530 30  0001 C CNN
F 2 "" H 7400 10600 60  0000 C CNN
F 3 "" H 7400 10600 60  0000 C CNN
	1    7400 10600
	1    0    0    -1  
$EndComp
Text Notes 7600 10200 0    39   ~ 0
Jumper Relais\nEin oder Ausschalten Ansteuerung\ndurch Ladespannung
Text Notes 6750 9450 0    39   ~ 0
Laderelais Spulenspannung 5V\noder Variabel\nEingang Spulenspannung\nkann über Vorwiderspannung\nangepasst werden\ndurch Ladespannung
Text Notes 5750 8300 0    39   ~ 0
Vorwiderstand Relais\nkann über ändern \nangepasst werden an\nverschiedene\nLadespannung
Text Notes 5450 7700 0    39   ~ 0
Rückflussdiode\nFalls Ladeschaltung nicht benötigt \nLadeschaltung nicht bestücken \nund für Diode Drahtbrücke einlöten\n
$Comp
L GND #PWR059
U 1 1 54B5D3E4
P 9550 900
F 0 "#PWR059" H 9550 900 30  0001 C CNN
F 1 "GND" H 9550 830 30  0001 C CNN
F 2 "" H 9550 900 60  0000 C CNN
F 3 "" H 9550 900 60  0000 C CNN
	1    9550 900 
	0    1    1    0   
$EndComp
Text GLabel 10175 1500 0    60   Input ~ 0
DuoLED-Rot
Text GLabel 9550 1400 0    60   Input ~ 0
DuoLED_Grün
Text Notes 10575 1450 0    60   ~ 0
Anschlußklemme\n geändert\n+ Duo LED\n hinzugefügt
$Comp
L R R21
U 1 1 54B5FC72
P 9450 3250
F 0 "R21" V 9530 3250 40  0000 C CNN
F 1 "470R" V 9457 3251 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 9380 3250 30  0001 C CNN
F 3 "~" H 9450 3250 30  0000 C CNN
	1    9450 3250
	0    -1   -1   0   
$EndComp
$Comp
L R R20
U 1 1 54B5FD13
P 9450 3050
F 0 "R20" V 9530 3050 40  0000 C CNN
F 1 "470R" V 9457 3051 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 9380 3050 30  0001 C CNN
F 3 "~" H 9450 3050 30  0000 C CNN
	1    9450 3050
	0    -1   -1   0   
$EndComp
Text GLabel 9750 3050 2    60   Output ~ 0
DuoLED-Rot
Text GLabel 9750 3250 2    60   Output ~ 0
DuoLED_Grün
Text Notes 10400 3150 0    60   ~ 0
Duo LED hinzugefügt
$Comp
L R R11
U 1 1 54B48CE0
P 2925 8550
F 0 "R11" V 3005 8550 40  0000 C CNN
F 1 "1K5" V 2932 8551 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2855 8550 30  0001 C CNN
F 3 "~" H 2925 8550 30  0000 C CNN
	1    2925 8550
	1    0    0    -1  
$EndComp
Text GLabel 2925 8950 3    60   Output ~ 0
StationLed
Text GLabel 10175 1300 0    60   Input ~ 0
StationLed
Text Notes 2825 9750 0    39   ~ 0
Station LED\nbzw:\nGrundlast\nPerimetersender
Text Notes 2700 7750 0    39   ~ 0
Strom von Relais muss vor der Diode geholt werden\nwenn nach Diode oderLM350T geholt wird\ngeht das Relais rückwärt in Selbthaltung\n und kann nicht mehr abfallen
$Comp
L +5V #PWR060
U 1 1 54B507D5
P 3150 4800
F 0 "#PWR060" H 3150 4890 20  0001 C CNN
F 1 "+5V" H 3150 4890 30  0000 C CNN
F 2 "" H 3150 4800 60  0000 C CNN
F 3 "" H 3150 4800 60  0000 C CNN
	1    3150 4800
	0    1    1    0   
$EndComp
Text Notes 2500 4800 0    39   ~ 0
Hier 5V richtig??
Text GLabel 10700 10800 2    47   Output ~ 0
pinChargingBilanz
$Comp
L ACS712 U5
U 1 1 54B50EFB
P 10450 10150
F 0 "U5" H 10450 10400 50  0000 C CNN
F 1 "INA169 Adafruit" H 10450 9900 50  0000 C CNN
F 2 "ACS712:INA169" H 10450 10150 60  0000 C CNN
F 3 "" H 10450 10150 60  0000 C CNN
	1    10450 10150
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR061
U 1 1 54B50F01
P 10550 10650
F 0 "#PWR061" H 10550 10740 20  0001 C CNN
F 1 "+5V" H 10550 10740 30  0000 C CNN
F 2 "" H 10550 10650 60  0000 C CNN
F 3 "" H 10550 10650 60  0000 C CNN
	1    10550 10650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR062
U 1 1 54B50F07
P 10300 11000
F 0 "#PWR062" H 10300 11000 30  0001 C CNN
F 1 "GND" H 10300 10930 30  0001 C CNN
F 2 "" H 10300 11000 60  0000 C CNN
F 3 "" H 10300 11000 60  0000 C CNN
	1    10300 11000
	1    0    0    -1  
$EndComp
$Comp
L CP1 C6
U 1 1 54B50F0D
P 10500 10950
F 0 "C6" H 10550 11050 50  0000 L CNN
F 1 "0,1uF" H 10550 10850 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 10500 10950 60  0001 C CNN
F 3 "~" H 10500 10950 60  0000 C CNN
	1    10500 10950
	0    1    1    0   
$EndComp
$Comp
L CONN_3 P21
U 1 1 54B5391D
P 14600 5650
F 0 "P21" V 14550 5650 50  0000 C CNN
F 1 "DropRight" V 14650 5650 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 14600 5650 60  0001 C CNN
F 3 "" H 14600 5650 60  0000 C CNN
	1    14600 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR063
U 1 1 54B53923
P 14100 5400
F 0 "#PWR063" H 14100 5400 30  0001 C CNN
F 1 "GND" H 14100 5330 30  0001 C CNN
F 2 "" H 14100 5400 60  0000 C CNN
F 3 "" H 14100 5400 60  0000 C CNN
	1    14100 5400
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR064
U 1 1 54B5392A
P 14250 5400
F 0 "#PWR064" H 14250 5490 20  0001 C CNN
F 1 "+5V" H 14250 5490 30  0000 C CNN
F 2 "" H 14250 5400 60  0000 C CNN
F 3 "" H 14250 5400 60  0000 C CNN
	1    14250 5400
	-1   0    0    -1  
$EndComp
Text GLabel 13650 5750 0    60   Output ~ 0
DropRight
$Comp
L DIODE D6
U 1 1 54B53F62
P 13950 5750
F 0 "D6" H 13950 5850 40  0000 C CNN
F 1 "1N4148" H 13950 5650 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 13950 5750 60  0001 C CNN
F 3 "" H 13950 5750 60  0000 C CNN
	1    13950 5750
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR065
U 1 1 54B5558C
P 14050 6800
F 0 "#PWR065" H 14050 6800 30  0001 C CNN
F 1 "GND" H 14050 6730 30  0001 C CNN
F 2 "" H 14050 6800 60  0000 C CNN
F 3 "" H 14050 6800 60  0000 C CNN
	1    14050 6800
	0    1    1    0   
$EndComp
$Comp
L CONN_3 P31
U 1 1 54B55773
P 12850 5650
F 0 "P31" V 12800 5650 50  0000 C CNN
F 1 "DropLeft" V 12900 5650 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 12850 5650 60  0001 C CNN
F 3 "" H 12850 5650 60  0000 C CNN
	1    12850 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR066
U 1 1 54B55779
P 12350 5400
F 0 "#PWR066" H 12350 5400 30  0001 C CNN
F 1 "GND" H 12350 5330 30  0001 C CNN
F 2 "" H 12350 5400 60  0000 C CNN
F 3 "" H 12350 5400 60  0000 C CNN
	1    12350 5400
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR067
U 1 1 54B5577F
P 12500 5400
F 0 "#PWR067" H 12500 5490 20  0001 C CNN
F 1 "+5V" H 12500 5490 30  0000 C CNN
F 2 "" H 12500 5400 60  0000 C CNN
F 3 "" H 12500 5400 60  0000 C CNN
	1    12500 5400
	-1   0    0    -1  
$EndComp
Text GLabel 11900 5750 0    60   Output ~ 0
DropLeft
$Comp
L DIODE D5
U 1 1 54B55789
P 12200 5750
F 0 "D5" H 12200 5850 40  0000 C CNN
F 1 "1N4148" H 12200 5650 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 12200 5750 60  0001 C CNN
F 3 "" H 12200 5750 60  0000 C CNN
	1    12200 5750
	-1   0    0    1   
$EndComp
$Comp
L DIODE D3
U 1 1 54B617F6
P 5750 7850
F 0 "D3" H 5750 7950 40  0000 C CNN
F 1 "MPR 1045" H 5750 7750 40  0000 C CNN
F 2 "ACS712:MBR1045" H 5750 7850 60  0001 C CNN
F 3 "" H 5750 7850 60  0000 C CNN
	1    5750 7850
	1    0    0    -1  
$EndComp
$Comp
L DIODE D4
U 1 1 54B63125
P 8050 8650
F 0 "D4" H 8050 8750 40  0000 C CNN
F 1 "MBR 1045" H 8050 8550 40  0000 C CNN
F 2 "ACS712:MBR1045" H 8050 8650 60  0001 C CNN
F 3 "" H 8050 8650 60  0000 C CNN
	1    8050 8650
	1    0    0    -1  
$EndComp
Text Notes 7700 8600 0    39   ~ 0
Sperrdiode die die Rückwärtsspannung \nvermeidet wenn DC-DC wander von\nLadestrom versorgt werden soll\n(@SteanM]\n\n
Text Notes 4400 7700 0    39   ~ 0
Rückflussdiode oder\nLötbrücke um\nLeiterbahn zu\nSchließen falls LM350T\nnicht bestückt wird
Text GLabel 12300 6400 0    60   Output ~ 0
pinPerimeterRight
$Comp
L CONN_3 P30
U 1 1 54B6707E
P 12750 6300
F 0 "P30" V 12700 6300 50  0000 C CNN
F 1 "PerimeterRight" V 12800 6300 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 12750 6300 60  0001 C CNN
F 3 "" H 12750 6300 60  0000 C CNN
	1    12750 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR068
U 1 1 54B67084
P 12250 6300
F 0 "#PWR068" H 12250 6300 30  0001 C CNN
F 1 "GND" H 12250 6230 30  0001 C CNN
F 2 "" H 12250 6300 60  0000 C CNN
F 3 "" H 12250 6300 60  0000 C CNN
	1    12250 6300
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR069
U 1 1 54B6708A
P 12400 6050
F 0 "#PWR069" H 12400 6140 20  0001 C CNN
F 1 "+5V" H 12400 6140 30  0000 C CNN
F 2 "" H 12400 6050 60  0000 C CNN
F 3 "" H 12400 6050 60  0000 C CNN
	1    12400 6050
	-1   0    0    -1  
$EndComp
Text GLabel 13900 6400 0    60   Output ~ 0
pinPerimeterLeft
$Comp
L CONN_3 P12
U 1 1 54B673DE
P 14600 6300
F 0 "P12" V 14550 6300 50  0000 C CNN
F 1 "PerimeterRight" V 14650 6300 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 14600 6300 60  0001 C CNN
F 3 "" H 14600 6300 60  0000 C CNN
	1    14600 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR070
U 1 1 54B673E4
P 14150 6300
F 0 "#PWR070" H 14150 6300 30  0001 C CNN
F 1 "GND" H 14150 6230 30  0001 C CNN
F 2 "" H 14150 6300 60  0000 C CNN
F 3 "" H 14150 6300 60  0000 C CNN
	1    14150 6300
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR071
U 1 1 54B673EA
P 14250 6200
F 0 "#PWR071" H 14250 6290 20  0001 C CNN
F 1 "+5V" H 14250 6290 30  0000 C CNN
F 2 "" H 14250 6200 60  0000 C CNN
F 3 "" H 14250 6200 60  0000 C CNN
	1    14250 6200
	-1   0    0    -1  
$EndComp
Text Notes 11650 6150 0    39   ~ 0
Perimeter rechts auf\nWunsch hinzugefügt
Text GLabel 4400 3750 0    60   Input ~ 0
pinPerimeterRight
Text GLabel 5400 4750 0    60   Input ~ 0
pinOdometryLeft2
Text GLabel 5400 4950 0    60   Input ~ 0
pinOdometryRight2
Text GLabel 4400 4850 0    60   Input ~ 0
pinOdometryRight
Text GLabel 4400 4450 0    60   Input ~ 0
pinChargingBilanz
$Comp
L R_PACK8 RP2
U 1 1 54B686DE
P 5750 4600
F 0 "RP2" H 5750 4600 40  0000 C CNN
F 1 "150" H 5750 4150 40  0000 C CNN
F 2 "Sockets_DIP:DIP-16__300" H 5750 4600 60  0001 C CNN
F 3 "" H 5750 4600 60  0000 C CNN
	1    5750 4600
	1    0    0    1   
$EndComp
$Comp
L CONN_01X08 P7
U 1 1 54B7B04A
P 10425 1250
F 0 "P7" H 10425 1700 50  0000 C CNN
F 1 "Status LEDs" V 10525 1250 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x08_3D" H 10425 1250 60  0001 C CNN
F 3 "" H 10425 1250 60  0000 C CNN
	1    10425 1250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P33
U 1 1 54B73600
P 15300 2800
F 0 "P33" H 15300 3250 50  0000 C CNN
F 1 "Stromleiste 5V" V 15400 2800 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 15300 2800 60  0001 C CNN
F 3 "" H 15300 2800 60  0000 C CNN
	1    15300 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P32
U 1 1 54B73B5A
P 14800 2800
F 0 "P32" H 14800 3250 50  0000 C CNN
F 1 "Stromleiste GND" V 14900 2800 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 14800 2800 60  0001 C CNN
F 3 "" H 14800 2800 60  0000 C CNN
	1    14800 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P34
U 1 1 54B73CFB
P 15750 2800
F 0 "P34" H 15750 3250 50  0000 C CNN
F 1 "Stromleiste 3,3V" V 15850 2800 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 15750 2800 60  0001 C CNN
F 3 "" H 15750 2800 60  0000 C CNN
	1    15750 2800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR072
U 1 1 54B77FA5
P 15100 3300
F 0 "#PWR072" H 15100 3390 20  0001 C CNN
F 1 "+5V" H 15100 3390 30  0000 C CNN
F 2 "" H 15100 3300 60  0000 C CNN
F 3 "" H 15100 3300 60  0000 C CNN
	1    15100 3300
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR073
U 1 1 54B7868E
P 15550 3250
F 0 "#PWR073" H 15550 3210 30  0001 C CNN
F 1 "+3.3V" H 15550 3360 30  0000 C CNN
F 2 "" H 15550 3250 60  0000 C CNN
F 3 "" H 15550 3250 60  0000 C CNN
	1    15550 3250
	1    0    0    1   
$EndComp
$Comp
L GND #PWR074
U 1 1 54B7933B
P 14600 3300
F 0 "#PWR074" H 14600 3300 30  0001 C CNN
F 1 "GND" H 14600 3230 30  0001 C CNN
F 2 "" H 14600 3300 60  0000 C CNN
F 3 "" H 14600 3300 60  0000 C CNN
	1    14600 3300
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP8
U 1 1 54B7D8CC
P 1150 1850
F 0 "JP8" H 1150 2000 60  0000 C CNN
F 1 "Blue5.0V" H 1150 1770 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1150 1850 60  0001 C CNN
F 3 "~" H 1150 1850 60  0000 C CNN
	1    1150 1850
	0    -1   -1   0   
$EndComp
$Comp
L JUMPER JP9
U 1 1 54B7DF62
P 1500 1850
F 0 "JP9" H 1500 2000 60  0000 C CNN
F 1 "Blue3.3V" H 1500 1770 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1500 1850 60  0001 C CNN
F 3 "~" H 1500 1850 60  0000 C CNN
	1    1500 1850
	0    -1   -1   0   
$EndComp
Text Notes 13925 2950 0    39   ~ 0
Abgriff 5V, 3V, GND
$Comp
L CONN_3 P35
U 1 1 54B8B4D4
P 2100 5650
F 0 "P35" V 2050 5650 50  0000 C CNN
F 1 "MowRpm" V 2150 5650 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 2100 5650 60  0001 C CNN
F 3 "" H 2100 5650 60  0000 C CNN
	1    2100 5650
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR075
U 1 1 54B8B4DA
P 2600 5650
F 0 "#PWR075" H 2600 5650 30  0001 C CNN
F 1 "GND" H 2600 5580 30  0001 C CNN
F 2 "" H 2600 5650 60  0000 C CNN
F 3 "" H 2600 5650 60  0000 C CNN
	1    2600 5650
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR076
U 1 1 54B8B4E1
P 2450 5400
F 0 "#PWR076" H 2450 5490 20  0001 C CNN
F 1 "+5V" H 2450 5490 30  0000 C CNN
F 2 "" H 2450 5400 60  0000 C CNN
F 3 "" H 2450 5400 60  0000 C CNN
	1    2450 5400
	1    0    0    -1  
$EndComp
Text GLabel 2750 5750 2    60   Output ~ 0
pinMotorMowRpm
$Comp
L CONN_3 P41
U 1 1 54B80251
P 4175 3075
F 0 "P41" V 4125 3075 50  0000 C CNN
F 1 "Rain" V 4225 3075 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 4175 3075 60  0001 C CNN
F 3 "" H 4175 3075 60  0000 C CNN
	1    4175 3075
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR077
U 1 1 54B80257
P 4675 3075
F 0 "#PWR077" H 4675 3075 30  0001 C CNN
F 1 "GND" H 4675 3005 30  0001 C CNN
F 2 "" H 4675 3075 60  0000 C CNN
F 3 "" H 4675 3075 60  0000 C CNN
	1    4675 3075
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR078
U 1 1 54B8025E
P 4675 2975
F 0 "#PWR078" H 4675 3065 20  0001 C CNN
F 1 "+5V" H 4675 3065 30  0000 C CNN
F 2 "" H 4675 2975 60  0000 C CNN
F 3 "" H 4675 2975 60  0000 C CNN
	1    4675 2975
	0    1    -1   0   
$EndComp
$Comp
L CONN_5 P40
U 1 1 54B80ED9
P 14700 8550
F 0 "P40" V 14650 8550 50  0000 C CNN
F 1 "UserSwitsch" V 14750 8550 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x05_3D" H 14700 8550 60  0001 C CNN
F 3 "" H 14700 8550 60  0000 C CNN
	1    14700 8550
	1    0    0    -1  
$EndComp
Text GLabel 13900 8500 0    60   Output ~ 0
pinUserSwitch1
Text GLabel 13900 8650 0    60   Output ~ 0
pinUserSwitch2
Text GLabel 13900 8800 0    60   Output ~ 0
pinUserSwitch3
$Comp
L GND #PWR079
U 1 1 54B81142
P 13950 8300
F 0 "#PWR079" H 13950 8300 30  0001 C CNN
F 1 "GND" H 13950 8230 30  0001 C CNN
F 2 "" H 13950 8300 60  0000 C CNN
F 3 "" H 13950 8300 60  0000 C CNN
	1    13950 8300
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR080
U 1 1 54B81148
P 14100 8300
F 0 "#PWR080" H 14100 8390 20  0001 C CNN
F 1 "+5V" H 14100 8390 30  0000 C CNN
F 2 "" H 14100 8300 60  0000 C CNN
F 3 "" H 14100 8300 60  0000 C CNN
	1    14100 8300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR081
U 1 1 54B8E463
P 11450 8250
F 0 "#PWR081" H 11450 8250 30  0001 C CNN
F 1 "GND" H 11450 8180 30  0001 C CNN
F 2 "" H 11450 8250 60  0000 C CNN
F 3 "" H 11450 8250 60  0000 C CNN
	1    11450 8250
	-1   0    0    1   
$EndComp
$Comp
L CP1 C7
U 1 1 54B8E469
P 11650 8750
F 0 "C7" H 11700 8850 50  0000 L CNN
F 1 "100uF" H 11700 8650 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 11650 8750 60  0001 C CNN
F 3 "~" H 11650 8750 60  0000 C CNN
	1    11650 8750
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP10
U 1 1 54B8E46F
P 11950 8500
F 0 "JP10" H 11950 8650 60  0000 C CNN
F 1 "pwr 3,3V" H 11950 8420 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 11950 8500 60  0001 C CNN
F 3 "" H 11950 8500 60  0000 C CNN
	1    11950 8500
	1    0    0    -1  
$EndComp
$Comp
L DC-DC_Stepdown U6
U 1 1 54B8E475
P 11100 8400
F 0 "U6" H 11100 8450 60  0000 C CNN
F 1 "DC  3,3V" H 11100 8150 60  0000 C CNN
F 2 "ACS712:DC-DC" H 12900 8300 60  0001 C CNN
F 3 "" H 12900 8300 60  0000 C CNN
	1    11100 8400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR082
U 1 1 54B8E47B
P 10750 8250
F 0 "#PWR082" H 10750 8250 30  0001 C CNN
F 1 "GND" H 10750 8180 30  0001 C CNN
F 2 "" H 10750 8250 60  0000 C CNN
F 3 "" H 10750 8250 60  0000 C CNN
	1    10750 8250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR083
U 1 1 54B91415
P 11650 9950
F 0 "#PWR083" H 11650 9950 30  0001 C CNN
F 1 "GND" H 11650 9880 30  0001 C CNN
F 2 "" H 11650 9950 60  0000 C CNN
F 3 "" H 11650 9950 60  0000 C CNN
	1    11650 9950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR084
U 1 1 54B92E0D
P 11450 7300
F 0 "#PWR084" H 11450 7300 30  0001 C CNN
F 1 "GND" H 11450 7230 30  0001 C CNN
F 2 "" H 11450 7300 60  0000 C CNN
F 3 "" H 11450 7300 60  0000 C CNN
	1    11450 7300
	-1   0    0    1   
$EndComp
$Comp
L CP1 C8
U 1 1 54B92E13
P 11650 7800
F 0 "C8" H 11700 7900 50  0000 L CNN
F 1 "100uF" H 11700 7700 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5" H 11650 7800 60  0001 C CNN
F 3 "~" H 11650 7800 60  0000 C CNN
	1    11650 7800
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP11
U 1 1 54B92E19
P 11950 7550
F 0 "JP11" H 11950 7700 60  0000 C CNN
F 1 "pwr 5V" H 11950 7470 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 11950 7550 60  0001 C CNN
F 3 "" H 11950 7550 60  0000 C CNN
	1    11950 7550
	1    0    0    -1  
$EndComp
$Comp
L DC-DC_Stepdown U7
U 1 1 54B92E1F
P 11100 7450
F 0 "U7" H 11100 7500 60  0000 C CNN
F 1 "DC  5V" H 11100 7200 60  0000 C CNN
F 2 "ACS712:DC-DC" H 12900 7350 60  0001 C CNN
F 3 "" H 12900 7350 60  0000 C CNN
	1    11100 7450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR085
U 1 1 54B92E25
P 10750 7300
F 0 "#PWR085" H 10750 7300 30  0001 C CNN
F 1 "GND" H 10750 7230 30  0001 C CNN
F 2 "" H 10750 7300 60  0000 C CNN
F 3 "" H 10750 7300 60  0000 C CNN
	1    10750 7300
	-1   0    0    1   
$EndComp
Text GLabel 12550 7550 2    60   Output ~ 0
Power5
$Comp
L GND #PWR086
U 1 1 54B93040
P 11650 8050
F 0 "#PWR086" H 11650 8050 30  0001 C CNN
F 1 "GND" H 11650 7980 30  0001 C CNN
F 2 "" H 11650 8050 60  0000 C CNN
F 3 "" H 11650 8050 60  0000 C CNN
	1    11650 8050
	1    0    0    -1  
$EndComp
Text GLabel 5800 2150 2    60   Input ~ 0
Power5
$Comp
L JUMPER JP12
U 1 1 54B90ACC
P 6550 1950
F 0 "JP12" H 6550 2100 60  0000 C CNN
F 1 "pwrAA5.0V" H 6550 1870 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 6550 1950 60  0001 C CNN
F 3 "" H 6550 1950 60  0000 C CNN
	1    6550 1950
	1    0    0    -1  
$EndComp
Text GLabel 4350 1975 2    60   Input ~ 0
Power5
$Comp
L +3.3V #PWR087
U 1 1 54B93CB3
P 1875 850
F 0 "#PWR087" H 1875 810 30  0001 C CNN
F 1 "+3.3V" H 1875 960 30  0000 C CNN
F 2 "" H 1875 850 60  0000 C CNN
F 3 "" H 1875 850 60  0000 C CNN
	1    1875 850 
	0    1    -1   0   
$EndComp
$Comp
L +3.3V #PWR088
U 1 1 54B944D0
P 1500 2250
F 0 "#PWR088" H 1500 2210 30  0001 C CNN
F 1 "+3.3V" H 1500 2360 30  0000 C CNN
F 2 "" H 1500 2250 60  0000 C CNN
F 3 "" H 1500 2250 60  0000 C CNN
	1    1500 2250
	-1   0    0    1   
$EndComp
NoConn ~ 7500 8450
$Comp
L CONN_3 P27
U 1 1 54B99CFF
P 15900 6500
F 0 "P27" V 15850 6500 50  0000 C CNN
F 1 "ReservePin0" V 15950 6500 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 6500 60  0001 C CNN
F 3 "" H 15900 6500 60  0000 C CNN
	1    15900 6500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR089
U 1 1 54B99D05
P 15450 6500
F 0 "#PWR089" H 15450 6500 30  0001 C CNN
F 1 "GND" H 15450 6430 30  0001 C CNN
F 2 "" H 15450 6500 60  0000 C CNN
F 3 "" H 15450 6500 60  0000 C CNN
	1    15450 6500
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR090
U 1 1 54B99D0B
P 15550 6400
F 0 "#PWR090" H 15550 6490 20  0001 C CNN
F 1 "+5V" H 15550 6490 30  0000 C CNN
F 2 "" H 15550 6400 60  0000 C CNN
F 3 "" H 15550 6400 60  0000 C CNN
	1    15550 6400
	-1   0    0    -1  
$EndComp
Text GLabel 15300 6600 0    60   Output ~ 0
ReservePin0
Text GLabel 9450 3850 2    60   Input ~ 0
ReservePin0
$Comp
L CONN_3 P29
U 1 1 54B9BD45
P 15900 7200
F 0 "P29" V 15850 7200 50  0000 C CNN
F 1 "ReservePin1" V 15950 7200 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 7200 60  0001 C CNN
F 3 "" H 15900 7200 60  0000 C CNN
	1    15900 7200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR091
U 1 1 54B9BD4B
P 15450 7200
F 0 "#PWR091" H 15450 7200 30  0001 C CNN
F 1 "GND" H 15450 7130 30  0001 C CNN
F 2 "" H 15450 7200 60  0000 C CNN
F 3 "" H 15450 7200 60  0000 C CNN
	1    15450 7200
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR092
U 1 1 54B9BD51
P 15550 7100
F 0 "#PWR092" H 15550 7190 20  0001 C CNN
F 1 "+5V" H 15550 7190 30  0000 C CNN
F 2 "" H 15550 7100 60  0000 C CNN
F 3 "" H 15550 7100 60  0000 C CNN
	1    15550 7100
	-1   0    0    -1  
$EndComp
Text GLabel 15300 7300 0    60   Output ~ 0
ReservePin1
Text GLabel 10450 3750 2    60   Input ~ 0
ReservePin1
$Comp
L CONN_3 P26
U 1 1 54B9D1FD
P 15900 8100
F 0 "P26" V 15850 8100 50  0000 C CNN
F 1 "ReservePin4" V 15950 8100 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 8100 60  0001 C CNN
F 3 "" H 15900 8100 60  0000 C CNN
	1    15900 8100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR093
U 1 1 54B9D203
P 15450 8100
F 0 "#PWR093" H 15450 8100 30  0001 C CNN
F 1 "GND" H 15450 8030 30  0001 C CNN
F 2 "" H 15450 8100 60  0000 C CNN
F 3 "" H 15450 8100 60  0000 C CNN
	1    15450 8100
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR094
U 1 1 54B9D209
P 15550 8000
F 0 "#PWR094" H 15550 8090 20  0001 C CNN
F 1 "+5V" H 15550 8090 30  0000 C CNN
F 2 "" H 15550 8000 60  0000 C CNN
F 3 "" H 15550 8000 60  0000 C CNN
	1    15550 8000
	-1   0    0    -1  
$EndComp
Text GLabel 15300 8200 0    60   Output ~ 0
ReservePin4
Text GLabel 9450 3450 2    60   Input ~ 0
ReservePin4
$Comp
L CONN_3 P28
U 1 1 54B9EA98
P 15900 8950
F 0 "P28" V 15850 8950 50  0000 C CNN
F 1 "ReservePin8" V 15950 8950 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 8950 60  0001 C CNN
F 3 "" H 15900 8950 60  0000 C CNN
	1    15900 8950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR095
U 1 1 54B9EA9E
P 15450 8950
F 0 "#PWR095" H 15450 8950 30  0001 C CNN
F 1 "GND" H 15450 8880 30  0001 C CNN
F 2 "" H 15450 8950 60  0000 C CNN
F 3 "" H 15450 8950 60  0000 C CNN
	1    15450 8950
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR096
U 1 1 54B9EAA4
P 15550 8850
F 0 "#PWR096" H 15550 8940 20  0001 C CNN
F 1 "+5V" H 15550 8940 30  0000 C CNN
F 2 "" H 15550 8850 60  0000 C CNN
F 3 "" H 15550 8850 60  0000 C CNN
	1    15550 8850
	-1   0    0    -1  
$EndComp
Text GLabel 15300 9050 0    60   Output ~ 0
ReservePin8
Text GLabel 10450 2950 2    60   Input ~ 0
ReservePin8
$Comp
L CONN_3 P25
U 1 1 54BA0300
P 15900 9500
F 0 "P25" V 15850 9500 50  0000 C CNN
F 1 "ReservePin9" V 15950 9500 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 9500 60  0001 C CNN
F 3 "" H 15900 9500 60  0000 C CNN
	1    15900 9500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR097
U 1 1 54BA0306
P 15450 9500
F 0 "#PWR097" H 15450 9500 30  0001 C CNN
F 1 "GND" H 15450 9430 30  0001 C CNN
F 2 "" H 15450 9500 60  0000 C CNN
F 3 "" H 15450 9500 60  0000 C CNN
	1    15450 9500
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR098
U 1 1 54BA030C
P 15550 9400
F 0 "#PWR098" H 15550 9490 20  0001 C CNN
F 1 "+5V" H 15550 9490 30  0000 C CNN
F 2 "" H 15550 9400 60  0000 C CNN
F 3 "" H 15550 9400 60  0000 C CNN
	1    15550 9400
	-1   0    0    -1  
$EndComp
Text GLabel 15300 9600 0    60   Output ~ 0
ReservePin9
Text GLabel 9450 2850 2    60   Input ~ 0
ReservePin9
$Comp
L CONN_3 P22
U 1 1 54BA46EA
P 15900 5800
F 0 "P22" V 15850 5800 50  0000 C CNN
F 1 "ReserveAD6" V 15950 5800 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 5800 60  0001 C CNN
F 3 "" H 15900 5800 60  0000 C CNN
	1    15900 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR099
U 1 1 54BA46F0
P 15450 5800
F 0 "#PWR099" H 15450 5800 30  0001 C CNN
F 1 "GND" H 15450 5730 30  0001 C CNN
F 2 "" H 15450 5800 60  0000 C CNN
F 3 "" H 15450 5800 60  0000 C CNN
	1    15450 5800
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR0100
U 1 1 54BA46F6
P 15550 5700
F 0 "#PWR0100" H 15550 5790 20  0001 C CNN
F 1 "+5V" H 15550 5790 30  0000 C CNN
F 2 "" H 15550 5700 60  0000 C CNN
F 3 "" H 15550 5700 60  0000 C CNN
	1    15550 5700
	-1   0    0    -1  
$EndComp
Text GLabel 15300 5900 0    60   Output ~ 0
ReserveAD6
Text GLabel 4400 3950 0    60   Input ~ 0
ReserveAD6
$Comp
L CONN_3 P14
U 1 1 54BA653E
P 15900 5250
F 0 "P14" V 15850 5250 50  0000 C CNN
F 1 "Mess V" V 15950 5250 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 15900 5250 60  0001 C CNN
F 3 "" H 15900 5250 60  0000 C CNN
	1    15900 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0101
U 1 1 54BA6544
P 15450 5250
F 0 "#PWR0101" H 15450 5250 30  0001 C CNN
F 1 "GND" H 15450 5180 30  0001 C CNN
F 2 "" H 15450 5250 60  0000 C CNN
F 3 "" H 15450 5250 60  0000 C CNN
	1    15450 5250
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR0102
U 1 1 54BA654A
P 15550 5150
F 0 "#PWR0102" H 15550 5240 20  0001 C CNN
F 1 "+5V" H 15550 5240 30  0000 C CNN
F 2 "" H 15550 5150 60  0000 C CNN
F 3 "" H 15550 5150 60  0000 C CNN
	1    15550 5150
	-1   0    0    -1  
$EndComp
Text GLabel 15300 5350 0    60   Output ~ 0
Spannungmessung
Text GLabel 5400 4050 0    60   Input ~ 0
Spannungmessung
$Comp
L CONN_3 P4
U 1 1 54BA7CCC
P 15900 4375
F 0 "P4" V 15850 4375 50  0000 C CNN
F 1 "ReserveAD11" V 15950 4375 40  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x03_3D" H 15900 4375 60  0001 C CNN
F 3 "" H 15900 4375 60  0000 C CNN
	1    15900 4375
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0103
U 1 1 54BA7CD2
P 15450 4375
F 0 "#PWR0103" H 15450 4375 30  0001 C CNN
F 1 "GND" H 15450 4305 30  0001 C CNN
F 2 "" H 15450 4375 60  0000 C CNN
F 3 "" H 15450 4375 60  0000 C CNN
	1    15450 4375
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR0104
U 1 1 54BA7CD8
P 15550 4275
F 0 "#PWR0104" H 15550 4365 20  0001 C CNN
F 1 "+5V" H 15550 4365 30  0000 C CNN
F 2 "" H 15550 4275 60  0000 C CNN
F 3 "" H 15550 4275 60  0000 C CNN
	1    15550 4275
	-1   0    0    -1  
$EndComp
Text GLabel 15300 4475 0    60   Output ~ 0
ReserveAD11
Text GLabel 5400 4550 0    60   Input ~ 0
ReserveAD11
$Comp
L GND #PWR0105
U 1 1 54BA6AAA
P 1550 6800
F 0 "#PWR0105" H 1550 6800 30  0001 C CNN
F 1 "GND" H 1550 6730 30  0001 C CNN
F 2 "" H 1550 6800 60  0000 C CNN
F 3 "" H 1550 6800 60  0000 C CNN
	1    1550 6800
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR0106
U 1 1 54BA6AB4
P 1200 6700
F 0 "#PWR0106" H 1200 6790 20  0001 C CNN
F 1 "+5V" H 1200 6790 30  0000 C CNN
F 2 "" H 1200 6700 60  0000 C CNN
F 3 "" H 1200 6700 60  0000 C CNN
	1    1200 6700
	0    1    1    0   
$EndComp
$Comp
L CONN_5 P23
U 1 1 54BA7798
P 700 6900
F 0 "P23" V 650 6900 50  0000 C CNN
F 1 "I2C Res.1" V 750 6900 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x05_3D" H 700 6900 60  0001 C CNN
F 3 "" H 700 6900 60  0000 C CNN
	1    700  6900
	-1   0    0    -1  
$EndComp
Text GLabel 1200 6900 2    60   BiDi ~ 0
SDA2
Text GLabel 1550 7000 2    60   Input ~ 0
SCL2
$Comp
L GND #PWR0107
U 1 1 54BA9F2E
P 3050 6800
F 0 "#PWR0107" H 3050 6800 30  0001 C CNN
F 1 "GND" H 3050 6730 30  0001 C CNN
F 2 "" H 3050 6800 60  0000 C CNN
F 3 "" H 3050 6800 60  0000 C CNN
	1    3050 6800
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR0108
U 1 1 54BA9F34
P 2700 6700
F 0 "#PWR0108" H 2700 6790 20  0001 C CNN
F 1 "+5V" H 2700 6790 30  0000 C CNN
F 2 "" H 2700 6700 60  0000 C CNN
F 3 "" H 2700 6700 60  0000 C CNN
	1    2700 6700
	0    1    1    0   
$EndComp
$Comp
L CONN_5 P24
U 1 1 54BA9F3B
P 2200 6900
F 0 "P24" V 2150 6900 50  0000 C CNN
F 1 "I2C Res.2" V 2250 6900 50  0000 C CNN
F 2 "ACS712:Pin_Header_KK110_1x05_3D" H 2200 6900 60  0001 C CNN
F 3 "" H 2200 6900 60  0000 C CNN
	1    2200 6900
	-1   0    0    -1  
$EndComp
Text GLabel 2700 6900 2    60   BiDi ~ 0
SDA2
Text GLabel 3050 7000 2    60   Input ~ 0
SCL2
$Comp
L DIODE D7
U 1 1 54BB9425
P 4750 7850
F 0 "D7" H 4750 7950 40  0000 C CNN
F 1 "DIODE" H 4750 7750 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 4750 7850 60  0001 C CNN
F 3 "" H 4750 7850 60  0000 C CNN
	1    4750 7850
	-1   0    0    1   
$EndComp
$Comp
L DS1307+ U8
U 1 1 54BBCE9E
P 8100 1350
F 0 "U8" H 8100 1500 60  0000 C CNN
F 1 "DS1307+" H 8125 1350 60  0000 C CNN
F 2 "ACS712:Tiny_RTC_DS1307_geändert" H 8100 1350 60  0001 C CNN
F 3 "" H 8100 1350 60  0000 C CNN
	1    8100 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0109
U 1 1 54BBD3E5
P 8100 2000
F 0 "#PWR0109" H 8100 2000 30  0001 C CNN
F 1 "GND" H 8100 1930 30  0001 C CNN
F 2 "" H 8100 2000 60  0000 C CNN
F 3 "" H 8100 2000 60  0000 C CNN
	1    8100 2000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR0110
U 1 1 54BBDB92
P 8100 700
F 0 "#PWR0110" H 8100 790 20  0001 C CNN
F 1 "+5V" H 8100 790 30  0000 C CNN
F 2 "" H 8100 700 60  0000 C CNN
F 3 "" H 8100 700 60  0000 C CNN
	1    8100 700 
	1    0    0    -1  
$EndComp
NoConn ~ 7500 1550
NoConn ~ 8700 1650
NoConn ~ 8700 1050
Text GLabel 7450 1050 0    60   Input ~ 0
SCL1
Text GLabel 7450 1250 0    60   BiDi ~ 0
SDA1
$Comp
L Wlan_ESP8266 U9
U 1 1 54BC06A2
P 875 3300
F 0 "U9" H 825 2800 50  0000 C CNN
F 1 "Wlan_ESP8266" V 1025 3300 50  0000 C CNN
F 2 "ACS712:Wlan_ESP8266_3D" H 875 3300 50  0001 C CNN
F 3 "DOCUMENTATION" H 875 3300 50  0001 C CNN
	1    875  3300
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR0111
U 1 1 54BC27F4
P 1575 3200
F 0 "#PWR0111" H 1575 3290 20  0001 C CNN
F 1 "+3.3V" H 1575 3290 30  0000 C CNN
F 2 "" H 1575 3200 60  0000 C CNN
F 3 "" H 1575 3200 60  0000 C CNN
	1    1575 3200
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR0112
U 1 1 54BC2D58
P 1425 3350
F 0 "#PWR0112" H 1425 3350 30  0001 C CNN
F 1 "GND" H 1425 3280 30  0001 C CNN
F 2 "" H 1425 3350 60  0000 C CNN
F 3 "" H 1425 3350 60  0000 C CNN
	1    1425 3350
	0    -1   -1   0   
$EndComp
NoConn ~ 1275 3050
NoConn ~ 1275 3150
NoConn ~ 1275 3450
NoConn ~ 1275 3550
$Comp
L Bluetooth_CZ_HC_05 U2
U 1 1 54BC29A1
P 750 1000
F 0 "U2" H 650 600 50  0000 C CNN
F 1 "Bluetooth_CZ_HC_05" V 856 1008 50  0000 C CNN
F 2 "ACS712:Bluetooth_Buchse_Platz" H 750 1000 50  0001 C CNN
F 3 "DOCUMENTATION" H 750 1000 50  0001 C CNN
	1    750  1000
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X02 D8
U 1 1 54BD3C36
P 2575 1250
F 0 "D8" H 2575 1400 50  0000 C CNN
F 1 "BlueLED" V 2675 1250 50  0000 C CNN
F 2 "ACS712:Diode_LED_5mm_round_vertical" H 2575 1250 60  0001 C CNN
F 3 "" H 2575 1250 60  0000 C CNN
	1    2575 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0113
U 1 1 54BD3CF4
P 2375 1375
F 0 "#PWR0113" H 2375 1375 30  0001 C CNN
F 1 "GND" H 2375 1305 30  0001 C CNN
F 2 "" H 2375 1375 60  0000 C CNN
F 3 "" H 2375 1375 60  0000 C CNN
	1    2375 1375
	-1   0    0    -1  
$EndComp
$Comp
L R R22
U 1 1 54BD4662
P 2375 850
F 0 "R22" V 2455 850 40  0000 C CNN
F 1 "120" V 2382 851 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 2305 850 30  0001 C CNN
F 3 "" H 2375 850 30  0000 C CNN
	1    2375 850 
	-1   0    0    -1  
$EndComp
$Comp
L R R23
U 1 1 54BD9865
P 4500 2800
F 0 "R23" V 4580 2800 40  0000 C CNN
F 1 "68" V 4507 2801 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 4430 2800 30  0001 C CNN
F 3 "~" H 4500 2800 30  0000 C CNN
	1    4500 2800
	0    -1   -1   0   
$EndComp
Text GLabel 4750 2800 2    60   Output ~ 0
LedPin-3V
$Comp
L +3.3V #PWR0114
U 1 1 54BD9CE1
P 4150 2700
F 0 "#PWR0114" H 4150 2660 30  0001 C CNN
F 1 "+3.3V" H 4150 2810 30  0000 C CNN
F 2 "" H 4150 2700 60  0000 C CNN
F 3 "" H 4150 2700 60  0000 C CNN
	1    4150 2700
	-1   0    0    -1  
$EndComp
Text GLabel 9475 1000 0    60   Input ~ 0
LedPin-3V
$Comp
L GND #PWR0115
U 1 1 54BDC7AE
P 14375 1675
F 0 "#PWR0115" H 14375 1675 30  0001 C CNN
F 1 "GND" H 14375 1605 30  0001 C CNN
F 2 "" H 14375 1675 60  0000 C CNN
F 3 "" H 14375 1675 60  0000 C CNN
	1    14375 1675
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR0116
U 1 1 54BDC7B4
P 14375 1350
F 0 "#PWR0116" H 14375 1300 20  0001 C CNN
F 1 "+24V" H 14375 1450 30  0000 C CNN
F 2 "" H 14375 1350 60  0000 C CNN
F 3 "" H 14375 1350 60  0000 C CNN
	1    14375 1350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P37
U 1 1 54BE02C5
P 15350 3550
F 0 "P37" V 15300 3550 40  0000 C CNN
F 1 "Dual2 M2" V 15400 3550 40  0000 C CNN
F 2 "Connect:PINHEAD1-2" H 15350 3550 60  0001 C CNN
F 3 "" H 15350 3550 60  0000 C CNN
	1    15350 3550
	1    0    0    1   
$EndComp
$Comp
L CONN_2 P36
U 1 1 54BE082F
P 14875 4800
F 0 "P36" V 14825 4800 40  0000 C CNN
F 1 "Dual2 M1" V 14925 4800 40  0000 C CNN
F 2 "Connect:PINHEAD1-2" H 14875 4800 60  0001 C CNN
F 3 "" H 14875 4800 60  0000 C CNN
	1    14875 4800
	1    0    0    1   
$EndComp
$Comp
L +24V #PWR0117
U 1 1 54BE5BDF
P 9300 8050
F 0 "#PWR0117" H 9300 8000 20  0001 C CNN
F 1 "+24V" H 9300 8150 30  0000 C CNN
F 2 "" H 9300 8050 60  0000 C CNN
F 3 "" H 9300 8050 60  0000 C CNN
	1    9300 8050
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR0118
U 1 1 54BE6166
P 2700 7100
F 0 "#PWR0118" H 2700 7060 30  0001 C CNN
F 1 "+3.3V" H 2700 7210 30  0000 C CNN
F 2 "" H 2700 7100 60  0000 C CNN
F 3 "" H 2700 7100 60  0000 C CNN
	1    2700 7100
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR0119
U 1 1 54BE632C
P 1175 7100
F 0 "#PWR0119" H 1175 7060 30  0001 C CNN
F 1 "+3.3V" H 1175 7210 30  0000 C CNN
F 2 "" H 1175 7100 60  0000 C CNN
F 3 "" H 1175 7100 60  0000 C CNN
	1    1175 7100
	0    1    1    0   
$EndComp
$Comp
L CONN_2 P39
U 1 1 54BEAE04
P 15850 1500
F 0 "P39" V 15800 1500 40  0000 C CNN
F 1 "Res24V-1" V 15900 1500 40  0000 C CNN
F 2 "ACS712:Aschlussklemme_2p_3D" H 15850 1500 60  0001 C CNN
F 3 "" H 15850 1500 60  0000 C CNN
	1    15850 1500
	1    0    0    1   
$EndComp
$Comp
L GND #PWR0120
U 1 1 54BEAE0A
P 15350 1675
F 0 "#PWR0120" H 15350 1675 30  0001 C CNN
F 1 "GND" H 15350 1605 30  0001 C CNN
F 2 "" H 15350 1675 60  0000 C CNN
F 3 "" H 15350 1675 60  0000 C CNN
	1    15350 1675
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR0121
U 1 1 54BEAE10
P 15350 1350
F 0 "#PWR0121" H 15350 1300 20  0001 C CNN
F 1 "+24V" H 15350 1450 30  0000 C CNN
F 2 "" H 15350 1350 60  0000 C CNN
F 3 "" H 15350 1350 60  0000 C CNN
	1    15350 1350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P38
U 1 1 54BEB61D
P 15850 875
F 0 "P38" V 15800 875 40  0000 C CNN
F 1 "Res24V-2" V 15900 875 40  0000 C CNN
F 2 "ACS712:Aschlussklemme_2p_3D" H 15850 875 60  0001 C CNN
F 3 "" H 15850 875 60  0000 C CNN
	1    15850 875 
	1    0    0    1   
$EndComp
$Comp
L GND #PWR0122
U 1 1 54BEB623
P 15350 1050
F 0 "#PWR0122" H 15350 1050 30  0001 C CNN
F 1 "GND" H 15350 980 30  0001 C CNN
F 2 "" H 15350 1050 60  0000 C CNN
F 3 "" H 15350 1050 60  0000 C CNN
	1    15350 1050
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR0123
U 1 1 54BEB629
P 15350 725
F 0 "#PWR0123" H 15350 675 20  0001 C CNN
F 1 "+24V" H 15350 825 30  0000 C CNN
F 2 "" H 15350 725 60  0000 C CNN
F 3 "" H 15350 725 60  0000 C CNN
	1    15350 725 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0124
U 1 1 54C0E917
P 12500 5050
F 0 "#PWR0124" H 12500 5050 30  0001 C CNN
F 1 "GND" H 12500 4980 30  0001 C CNN
F 2 "" H 12500 5050 60  0000 C CNN
F 3 "" H 12500 5050 60  0000 C CNN
	1    12500 5050
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR0125
U 1 1 54C0F6F7
P 12550 4950
F 0 "#PWR0125" H 12550 5040 20  0001 C CNN
F 1 "+5V" H 12550 5040 30  0000 C CNN
F 2 "" H 12550 4950 60  0000 C CNN
F 3 "" H 12550 4950 60  0000 C CNN
	1    12550 4950
	0    -1   1    0   
$EndComp
Text Notes 8700 -225 0    60   ~ 0
LED Anzeigen - Hardware:\n\nLed 3V grün -   Betriebsanzeige Versorgungsspannung\nLED 24V grün - Betriebsanzeige Versorgungsspannung\nLED 5V grün -   Betriebsanzeige Versorgungsspannung\nLED Station - gelb - Statusanzeige ob Mover in Ladestation\n\n----------------------------------------------------------\n\nLED Anzeigen - Software:\n\nDual LED z.B:\nDual LED grün. Dauerlicht - Mover innerhalb Perimeter\nDual LED grün+rot = Orange - Dauerlicht Mover außerhalb Perimeter\nDual LED grün+rot = Orange - Blinkt Mover findet  Perimeter nicht oder sucht danach\nDual LED rot =  Blinkt Fehler kurzseitig Überlast Antriebmotor Treibe oder Mähmotor. \nDual LED rot - Dauerlicht - Fehler muß für weiterfahren durch drücken \nvon Button zurückgesetzt werden\n----------------------------------------------------------\n\nLED Status - grün Dauerlicht - warte auf Eingabe\n\nLED Status - grün blinken 1 bis 5 mal hintereinander\nmit länger Pause dazwischen für Anzeige in welchen\nBetriebsmodi sich der Mover befindet
$Comp
L JUMPER JP3
U 1 1 54C10ED7
P 7125 2250
F 0 "JP3" H 7125 2400 60  0000 C CNN
F 1 "pwrAA3,3" H 7125 2170 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 7125 2250 60  0001 C CNN
F 3 "" H 7125 2250 60  0000 C CNN
	1    7125 2250
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR0126
U 1 1 54C11BD9
P 7125 1950
F 0 "#PWR0126" H 7125 1910 30  0001 C CNN
F 1 "+3.3V" H 7125 2060 30  0000 C CNN
F 2 "" H 7125 1950 60  0000 C CNN
F 3 "" H 7125 1950 60  0000 C CNN
	1    7125 1950
	-1   0    0    -1  
$EndComp
$Comp
L JUMPER JP13
U 1 1 54C156E1
P 2900 1525
F 0 "JP13" H 2900 1675 60  0000 C CNN
F 1 "Mess3.3V" H 2900 1445 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 2900 1525 60  0001 C CNN
F 3 "" H 2900 1525 60  0000 C CNN
	1    2900 1525
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR0127
U 1 1 54C156E7
P 2900 1175
F 0 "#PWR0127" H 2900 1135 30  0001 C CNN
F 1 "+3.3V" H 2900 1285 30  0000 C CNN
F 2 "" H 2900 1175 60  0000 C CNN
F 3 "" H 2900 1175 60  0000 C CNN
	1    2900 1175
	-1   0    0    -1  
$EndComp
$Comp
L JUMPER JP14
U 1 1 54C157D5
P 3250 1525
F 0 "JP14" H 3250 1675 60  0000 C CNN
F 1 "Mess5.0V" H 3250 1445 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3250 1525 60  0001 C CNN
F 3 "" H 3250 1525 60  0000 C CNN
	1    3250 1525
	0    1    1    0   
$EndComp
$Comp
L JUMPER JP15
U 1 1 54C158E5
P 3600 1525
F 0 "JP15" H 3600 1675 60  0000 C CNN
F 1 "MessA3.3V" H 3600 1445 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3600 1525 60  0001 C CNN
F 3 "" H 3600 1525 60  0000 C CNN
	1    3600 1525
	0    1    1    0   
$EndComp
Text GLabel 7400 2450 1    60   Output ~ 0
PowerA3,3
Text GLabel 3600 1150 1    60   Input ~ 0
PowerA3,3
$Comp
L +5V #PWR0128
U 1 1 54C174E1
P 3250 1200
F 0 "#PWR0128" H 3250 1290 20  0001 C CNN
F 1 "+5V" H 3250 1290 30  0000 C CNN
F 2 "" H 3250 1200 60  0000 C CNN
F 3 "" H 3250 1200 60  0000 C CNN
	1    3250 1200
	1    0    0    -1  
$EndComp
Text GLabel 3525 1950 0    60   Input ~ 0
Spannungmessung
Text Notes 2525 -125 0    60   ~ 0
LED Rechner:\nhttp://www.elektronik-kompendium.de/sites/bau/1109111.htm\n\nZ-Dioden Rechner:\nhttp://www.dieelektronikerseite.de/Tools/Zenerdiode.htm
$Comp
L DIODE D9
U 1 1 54C30B35
P 9300 7700
F 0 "D9" H 9300 7800 40  0000 C CNN
F 1 "MBR 1045" H 9300 7600 40  0000 C CNN
F 2 "ACS712:MBR1045" H 9300 7700 60  0001 C CNN
F 3 "" H 9300 7700 60  0000 C CNN
	1    9300 7700
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 2950 7200 3050
Wire Wire Line
	12150 3125 12150 2975
Wire Wire Line
	9100 2350 9250 2350
Wire Wire Line
	9100 6400 9250 6400
Wire Wire Line
	9250 6200 9100 6200
Wire Wire Line
	12300 2775 12150 2775
Wire Wire Line
	2600 8875 2600 8775
Connection ~ 2600 8775
Wire Wire Line
	9975 7050 10175 7050
Wire Wire Line
	10025 7150 10025 7050
Connection ~ 10025 7050
Wire Wire Line
	2050 1625 2050 1600
Wire Wire Line
	2050 950  2050 1100
Wire Wire Line
	1050 4150 1100 4150
Wire Wire Line
	1100 4150 1100 4050
Wire Wire Line
	1250 4500 1200 4500
Wire Wire Line
	1200 4500 1200 4450
Wire Wire Line
	1200 4450 1050 4450
Wire Wire Line
	1050 4350 1200 4350
Wire Wire Line
	1200 4350 1200 4300
Wire Wire Line
	1200 4300 1250 4300
Wire Wire Line
	6200 6950 7200 6950
Wire Wire Line
	9100 6800 9250 6800
Wire Wire Line
	1050 5000 1100 5000
Wire Wire Line
	1100 5000 1100 4900
Wire Wire Line
	1250 5350 1200 5350
Wire Wire Line
	1200 5350 1200 5300
Wire Wire Line
	1200 5300 1050 5300
Wire Wire Line
	1050 5200 1200 5200
Wire Wire Line
	1200 5200 1200 5150
Wire Wire Line
	1200 5150 1250 5150
Wire Wire Line
	9100 6100 10250 6100
Wire Wire Line
	9100 6300 10250 6300
Wire Wire Line
	1050 5850 1100 5850
Wire Wire Line
	1100 5850 1100 5750
Wire Wire Line
	1250 6200 1200 6200
Wire Wire Line
	1200 6200 1200 6150
Wire Wire Line
	1200 6150 1050 6150
Wire Wire Line
	1050 6050 1200 6050
Wire Wire Line
	1200 6050 1200 6000
Wire Wire Line
	1200 6000 1250 6000
Wire Wire Line
	9100 5750 9250 5750
Wire Wire Line
	4125 7000 4275 7000
Wire Wire Line
	4425 7100 4125 7100
Wire Wire Line
	6200 6500 7200 6500
Wire Wire Line
	2825 2175 2725 2175
Wire Wire Line
	2225 2475 2125 2475
Wire Wire Line
	2225 2325 2175 2325
Wire Wire Line
	2175 2325 2175 2375
Wire Wire Line
	2175 2375 2125 2375
Wire Wire Line
	2125 2575 2175 2575
Wire Wire Line
	2175 2575 2175 2625
Wire Wire Line
	2175 2625 2225 2625
Wire Wire Line
	2225 2175 2175 2175
Wire Wire Line
	2175 2175 2175 2275
Wire Wire Line
	2175 2275 2125 2275
Wire Wire Line
	2725 2475 2825 2475
Wire Wire Line
	12500 1000 12650 1000
Wire Wire Line
	12650 1900 12500 1900
Wire Wire Line
	12650 2000 12500 2000
Wire Wire Line
	12500 2400 12650 2400
Wire Wire Line
	12350 800  12650 800 
Wire Wire Line
	12350 1350 12500 1350
Wire Wire Line
	12500 1350 12500 1300
Wire Wire Line
	12500 1300 12650 1300
Wire Wire Line
	12350 2250 12500 2250
Wire Wire Line
	12500 2250 12500 2200
Wire Wire Line
	12500 2200 12650 2200
Wire Wire Line
	12150 6750 11950 6750
Wire Wire Line
	12150 6950 11750 6950
Wire Wire Line
	11750 6950 11750 6850
Wire Wire Line
	11750 6850 11700 6850
Wire Wire Line
	11700 7050 12150 7050
Wire Wire Line
	12150 6850 11950 6850
Wire Wire Line
	9100 4150 9750 4150
Wire Wire Line
	9100 4350 9750 4350
Wire Wire Line
	8450 7750 8450 7700
Wire Wire Line
	3150 4950 3150 4800
Wire Wire Line
	14250 7000 13850 7000
Wire Wire Line
	13850 7000 13850 6900
Wire Wire Line
	13850 6900 13800 6900
Wire Wire Line
	13800 7100 14250 7100
Wire Wire Line
	11650 9450 11650 9400
Connection ~ 11650 9400
Wire Wire Line
	9250 6600 9100 6600
Wire Wire Line
	12350 1700 12650 1700
Wire Wire Line
	13950 8050 14150 8050
Wire Wire Line
	14150 8050 14150 8000
Wire Wire Line
	14150 8000 14350 8000
Wire Wire Line
	13950 7900 14350 7900
Wire Wire Line
	13950 7750 14150 7750
Wire Wire Line
	14150 7750 14150 7800
Wire Wire Line
	14150 7800 14350 7800
Wire Wire Line
	13950 7600 14200 7600
Wire Wire Line
	14200 7600 14200 7700
Wire Wire Line
	14200 7700 14350 7700
Wire Wire Line
	7100 6600 7200 6600
Wire Wire Line
	4150 2475 4250 2475
Wire Wire Line
	4150 1975 4150 2175
Wire Wire Line
	4150 2175 4250 2175
Wire Wire Line
	12350 1850 12400 1850
Wire Wire Line
	12400 1850 12400 1800
Wire Wire Line
	12400 1800 12650 1800
Wire Wire Line
	12250 1500 12500 1500
Wire Wire Line
	12500 1500 12500 1600
Wire Wire Line
	12500 1600 12650 1600
Wire Wire Line
	12350 950  12400 950 
Wire Wire Line
	12400 950  12400 900 
Wire Wire Line
	12400 900  12650 900 
Wire Wire Line
	6200 6750 7200 6750
Wire Wire Line
	6700 1150 6700 1400
Wire Wire Line
	6700 1150 6800 1150
Wire Wire Line
	6700 1500 6850 1500
Wire Wire Line
	6250 6100 7200 6100
Wire Wire Line
	9100 2550 10450 2550
Wire Wire Line
	9100 4450 10050 4450
Wire Wire Line
	1150 950  2225 950 
Wire Wire Line
	1150 1050 1775 1050
Wire Wire Line
	1275 1150 1150 1150
Wire Wire Line
	9100 5250 10250 5250
Wire Wire Line
	9100 5450 10250 5450
Wire Wire Line
	7100 6000 7200 6000
Wire Wire Line
	9100 6700 10250 6700
Wire Wire Line
	9100 6500 10250 6500
Wire Wire Line
	4125 6900 4125 6750
Wire Wire Line
	7100 6400 7200 6400
Wire Wire Line
	5450 1050 5350 1050
Wire Wire Line
	5350 1050 5350 1000
Wire Wire Line
	5350 1000 5250 1000
Wire Wire Line
	5450 1700 5250 1700
Wire Wire Line
	9100 3650 9450 3650
Wire Wire Line
	9100 3350 10450 3350
Wire Wire Line
	14250 7350 14350 7350
Wire Wire Line
	14350 7350 14350 7500
Wire Wire Line
	9100 5950 9250 5950
Wire Wire Line
	9100 5650 10250 5650
Wire Wire Line
	9100 5850 10250 5850
Wire Wire Line
	9100 3550 10450 3550
Wire Wire Line
	12350 1200 12650 1200
Wire Wire Line
	12350 2100 12650 2100
Wire Wire Line
	12500 3650 12650 3650
Wire Wire Line
	12650 3750 12500 3750
Wire Wire Line
	12350 3450 12650 3450
Wire Wire Line
	12350 4000 12500 4000
Wire Wire Line
	12500 4000 12500 3950
Wire Wire Line
	12500 3950 12650 3950
Wire Wire Line
	12250 4150 12500 4150
Wire Wire Line
	12500 4150 12500 4250
Wire Wire Line
	12500 4250 12650 4250
Wire Wire Line
	12350 3600 12400 3600
Wire Wire Line
	12400 3600 12400 3550
Wire Wire Line
	12400 3550 12650 3550
Wire Wire Line
	12350 3850 12650 3850
Wire Wire Line
	5300 1300 5300 1400
Wire Wire Line
	5300 1400 5250 1400
Wire Wire Line
	12500 2300 12650 2300
Wire Wire Line
	12500 1100 12650 1100
Connection ~ 12500 2000
Connection ~ 7200 2850
Connection ~ 12500 2300
Connection ~ 12500 1100
Wire Wire Line
	3550 9000 3550 9100
Wire Wire Line
	3350 9000 3350 9150
Wire Wire Line
	3450 9000 3450 9250
Wire Wire Line
	3450 9250 3700 9250
Wire Wire Line
	1225 7850 1225 8000
Wire Wire Line
	3350 9150 3300 9400
Wire Wire Line
	3300 9400 3300 9450
Wire Wire Line
	11650 9400 11450 9400
Wire Wire Line
	11450 9150 11450 9200
Wire Wire Line
	10750 9150 10750 9200
Connection ~ 10750 9400
Connection ~ 11450 9400
Connection ~ 11450 9200
Connection ~ 10750 9200
Wire Wire Line
	9700 2450 9750 2450
Wire Wire Line
	9100 4650 9250 4650
Wire Wire Line
	9100 4750 9200 4750
Wire Wire Line
	9200 4750 9200 4900
Wire Wire Line
	9200 4800 9250 4800
Wire Wire Line
	9150 4650 9200 4650
Wire Wire Line
	9200 4650 9200 4550
Wire Wire Line
	9200 4550 9650 4550
Wire Wire Line
	9650 4550 9650 4650
Connection ~ 9150 4650
Wire Wire Line
	9200 4900 9550 4900
Wire Wire Line
	9550 4900 9550 4800
Wire Wire Line
	9550 4800 9650 4800
Connection ~ 9200 4800
Wire Wire Line
	3150 5250 3350 5250
Wire Wire Line
	7100 2950 7200 2950
Wire Wire Line
	5800 2850 6000 2850
Wire Wire Line
	11650 9850 11650 9950
Wire Wire Line
	10025 7650 10025 7700
Wire Wire Line
	2600 9375 2600 9425
Wire Wire Line
	2600 8775 2500 8775
Wire Wire Line
	6000 2850 6000 2800
Wire Wire Line
	12250 9400 12550 9400
Wire Wire Line
	6650 2150 6900 2150
Wire Wire Line
	6700 10300 6700 10600
Wire Wire Line
	9100 8150 7500 8150
Wire Wire Line
	8600 7500 8450 7500
Connection ~ 6700 8250
Wire Wire Line
	6450 8750 6700 8750
Wire Wire Line
	6700 8000 6700 8550
Wire Wire Line
	1425 7850 1425 8000
Wire Wire Line
	1825 8000 2050 8000
Wire Wire Line
	2450 8000 3550 8000
Wire Wire Line
	3550 8000 3550 8200
Wire Wire Line
	7200 6300 6200 6300
Wire Wire Line
	10050 4450 10050 4400
Wire Wire Line
	10050 4400 10450 4400
Wire Wire Line
	9100 4550 9100 4500
Wire Wire Line
	9100 4500 10400 4500
Wire Wire Line
	10400 4500 10400 4550
Wire Wire Line
	10400 4550 10450 4550
Wire Wire Line
	5400 5900 7200 5900
Wire Wire Line
	1875 2950 1975 2950
Wire Wire Line
	6300 10100 6400 10100
Wire Wire Line
	3550 9050 4400 9050
Wire Wire Line
	4400 9050 4400 9400
Wire Wire Line
	4400 9400 3700 9400
Connection ~ 3550 9050
Wire Wire Line
	6450 8500 6450 8750
Wire Wire Line
	4400 8250 4350 8250
Wire Wire Line
	5200 8250 5550 8250
Wire Wire Line
	5300 8250 5300 8300
Connection ~ 5300 8250
Wire Wire Line
	5300 8800 5100 8800
Wire Wire Line
	5100 8800 5100 8600
Wire Wire Line
	5100 8600 4800 8600
Wire Wire Line
	4800 8550 4800 8650
Connection ~ 4800 8600
Wire Wire Line
	4950 8900 4950 9150
Wire Wire Line
	4800 9150 5150 9150
Connection ~ 4950 9150
Wire Wire Line
	5550 8650 5550 8850
Wire Wire Line
	4350 8650 4350 8850
Wire Wire Line
	3350 7850 3350 8200
Wire Wire Line
	7700 8350 7500 8350
Wire Wire Line
	7700 7850 7700 8350
Wire Wire Line
	3350 7850 4550 7850
Wire Wire Line
	4350 8250 4350 7850
Wire Wire Line
	6700 8850 6700 9900
Wire Wire Line
	6700 8000 8700 8000
Wire Wire Line
	9100 7500 9100 8650
Connection ~ 9100 8150
Wire Wire Line
	8700 8000 8700 8950
Wire Wire Line
	8700 9550 8700 9700
Wire Wire Line
	8700 9700 10550 9700
Wire Wire Line
	9450 9500 9450 9825
Connection ~ 9450 9700
Wire Wire Line
	9450 10225 9450 10275
Wire Wire Line
	1925 8000 1925 7350
Connection ~ 1925 8000
Wire Wire Line
	5800 10100 5700 10100
Wire Wire Line
	5100 10100 5000 10100
Wire Wire Line
	7400 9900 7400 9700
Wire Wire Line
	7400 9700 6700 9700
Connection ~ 6700 9700
Wire Wire Line
	7400 10500 7400 10600
Wire Wire Line
	10225 1100 10175 1100
Wire Wire Line
	9200 3250 9100 3250
Wire Wire Line
	9700 3050 9750 3050
Wire Wire Line
	9700 3250 9750 3250
Wire Wire Line
	2925 8800 2925 8950
Wire Wire Line
	10550 10550 10550 10650
Wire Wire Line
	10350 10550 10350 10700
Wire Wire Line
	10450 10550 10450 10800
Wire Wire Line
	10450 10800 10700 10800
Wire Wire Line
	10350 10700 10300 10950
Wire Wire Line
	10300 10950 10300 11000
Wire Wire Line
	10550 10600 11450 10600
Wire Wire Line
	10700 10950 11450 10950
Connection ~ 10550 10600
Wire Wire Line
	10550 9700 10550 9750
Wire Wire Line
	10350 7550 10350 9750
Wire Wire Line
	10350 9400 10750 9400
Wire Wire Line
	9000 7500 9300 7500
Connection ~ 9100 7500
Wire Wire Line
	11450 10950 11450 10600
Wire Wire Line
	14100 5400 14100 5650
Wire Wire Line
	14150 5750 14250 5750
Wire Wire Line
	14250 5550 14250 5400
Wire Wire Line
	13750 5750 13650 5750
Wire Wire Line
	14050 6800 14250 6800
Wire Wire Line
	12400 5750 12500 5750
Wire Wire Line
	12500 5550 12500 5400
Wire Wire Line
	12000 5750 11900 5750
Wire Wire Line
	4150 2475 4150 2375
Wire Wire Line
	9100 8650 8250 8650
Connection ~ 4350 7850
Wire Wire Line
	12400 6300 12250 6300
Wire Wire Line
	12300 6400 12400 6400
Wire Wire Line
	12400 6200 12400 6050
Wire Wire Line
	14150 6300 14250 6300
Wire Wire Line
	14250 6200 14250 6200
Wire Wire Line
	5950 4250 7200 4250
Wire Wire Line
	5950 4350 7200 4350
Wire Wire Line
	5950 4450 7200 4450
Wire Wire Line
	5950 4650 7200 4650
Wire Wire Line
	5950 4750 7200 4750
Wire Wire Line
	5950 4850 7200 4850
Wire Wire Line
	5950 4950 7200 4950
Wire Wire Line
	5950 4550 7200 4550
Wire Wire Line
	5950 3350 7200 3350
Wire Wire Line
	5950 3450 7200 3450
Wire Wire Line
	5950 3550 7200 3550
Wire Wire Line
	5950 3650 7200 3650
Wire Wire Line
	5950 3750 7200 3750
Wire Wire Line
	5950 3850 7200 3850
Wire Wire Line
	5950 3950 7200 3950
Wire Wire Line
	5950 4050 7200 4050
Wire Wire Line
	7200 3150 6900 3150
Wire Wire Line
	6900 3150 6900 2150
Wire Wire Line
	6100 2800 6100 3350
Connection ~ 6100 3350
Wire Wire Line
	6200 2800 6200 3450
Connection ~ 6200 3450
Wire Wire Line
	6300 2800 6300 3550
Connection ~ 6300 3550
Wire Wire Line
	6400 2800 6400 3650
Connection ~ 6400 3650
Wire Wire Line
	6500 2800 6500 3750
Connection ~ 6500 3750
Wire Wire Line
	6600 2800 6600 3850
Connection ~ 6600 3850
Wire Wire Line
	6700 2800 6700 3950
Connection ~ 6700 3950
Wire Wire Line
	6800 2800 6800 4050
Connection ~ 6800 4050
Wire Wire Line
	6100 5100 6100 4250
Connection ~ 6100 4250
Wire Wire Line
	6200 5100 6200 4350
Connection ~ 6200 4350
Wire Wire Line
	6300 5100 6300 4450
Connection ~ 6300 4450
Wire Wire Line
	6400 5100 6400 4550
Connection ~ 6400 4550
Wire Wire Line
	6500 5100 6500 4650
Connection ~ 6500 4650
Wire Wire Line
	6600 5100 6600 4750
Connection ~ 6600 4750
Wire Wire Line
	6700 5100 6700 4850
Connection ~ 6700 4850
Wire Wire Line
	6800 5100 6800 4950
Connection ~ 6800 4950
Wire Wire Line
	5400 5900 5400 6000
Wire Wire Line
	5400 6000 5350 6000
Wire Wire Line
	5550 4850 4400 4850
Wire Wire Line
	5400 4950 5550 4950
Wire Wire Line
	5550 4750 5400 4750
Wire Wire Line
	5550 4450 4400 4450
Wire Wire Line
	5550 4650 4400 4650
Wire Wire Line
	5550 4550 5400 4550
Wire Wire Line
	5550 4350 5400 4350
Wire Wire Line
	5550 4250 4400 4250
Wire Wire Line
	4400 3350 5550 3350
Wire Wire Line
	5550 3450 5400 3450
Wire Wire Line
	5550 3550 4400 3550
Wire Wire Line
	5550 3650 5400 3650
Wire Wire Line
	5550 3950 4400 3950
Wire Wire Line
	5550 4050 5400 4050
Wire Wire Line
	5550 3750 4400 3750
Wire Wire Line
	5400 3850 5550 3850
Wire Wire Line
	4600 5850 7200 5850
Wire Wire Line
	5350 5750 7150 5750
Wire Wire Line
	4600 5650 7100 5650
Wire Wire Line
	5400 5600 7050 5600
Wire Wire Line
	5400 5600 5400 5550
Wire Wire Line
	5400 5550 5300 5550
Wire Wire Line
	9550 1400 10225 1400
Wire Wire Line
	9100 3850 9450 3850
Wire Wire Line
	9100 3750 10450 3750
Wire Wire Line
	9100 3450 9450 3450
Wire Wire Line
	9100 3150 9150 3150
Wire Wire Line
	9150 3150 9150 3050
Wire Wire Line
	9150 3050 9200 3050
Wire Wire Line
	9100 2950 10450 2950
Wire Wire Line
	9200 2450 9100 2450
Wire Wire Line
	9100 2650 9450 2650
Wire Wire Line
	9100 2750 10450 2750
Wire Wire Line
	9100 2850 9450 2850
Wire Wire Line
	9100 4250 9300 4250
Wire Wire Line
	9300 4050 9100 4050
Wire Wire Line
	9100 5550 9250 5550
Wire Wire Line
	9100 5350 9250 5350
Wire Wire Line
	7200 6850 7100 6850
Wire Wire Line
	7200 7050 7050 7050
Wire Wire Line
	7200 6200 7100 6200
Wire Wire Line
	14600 2450 14600 3300
Connection ~ 14600 2550
Connection ~ 14600 2650
Connection ~ 14600 2750
Connection ~ 14600 2850
Connection ~ 14600 2950
Connection ~ 14600 3050
Wire Wire Line
	15100 2450 15100 3300
Connection ~ 15100 2550
Connection ~ 15100 2650
Connection ~ 15100 2750
Connection ~ 15100 2850
Connection ~ 15100 2950
Connection ~ 15100 3050
Wire Wire Line
	15550 2450 15550 3250
Connection ~ 15550 2550
Connection ~ 15550 2650
Connection ~ 15550 2750
Connection ~ 15550 2850
Connection ~ 15550 2950
Connection ~ 15550 3050
Connection ~ 15100 3150
Connection ~ 15550 3150
Connection ~ 14600 3150
Wire Wire Line
	1150 2150 1150 2250
Wire Wire Line
	1150 1550 1500 1550
Wire Wire Line
	1500 1550 1500 1250
Wire Wire Line
	1050 4250 1150 4250
Wire Wire Line
	1150 4250 1150 4200
Wire Wire Line
	1150 4200 1200 4200
Wire Wire Line
	1050 5100 1100 5100
Wire Wire Line
	1100 5100 1100 5050
Wire Wire Line
	1100 5050 1200 5050
Wire Wire Line
	1200 5850 1150 5850
Wire Wire Line
	1150 5850 1150 5950
Wire Wire Line
	1150 5950 1050 5950
Wire Wire Line
	3350 5100 3250 5100
Wire Wire Line
	3250 5150 3150 5150
Wire Wire Line
	3250 5100 3250 5150
Wire Wire Line
	3150 5050 3200 5050
Wire Wire Line
	3200 5050 3200 5000
Wire Wire Line
	3200 5000 3250 5000
Wire Wire Line
	5450 850  5350 850 
Wire Wire Line
	5350 850  5350 900 
Wire Wire Line
	5350 900  5250 900 
Wire Wire Line
	5250 800  5300 800 
Wire Wire Line
	5300 800  5300 700 
Wire Wire Line
	5300 700  5450 700 
Wire Wire Line
	5250 1600 5400 1600
Wire Wire Line
	5400 1600 5400 1550
Wire Wire Line
	5400 1550 5450 1550
Wire Wire Line
	5450 1400 5350 1400
Wire Wire Line
	5350 1400 5350 1500
Wire Wire Line
	5350 1500 5250 1500
Wire Wire Line
	5950 7850 7700 7850
Wire Wire Line
	4950 7850 5550 7850
Wire Wire Line
	5550 7850 5550 8250
Wire Wire Line
	14350 7600 14250 7600
Wire Wire Line
	14250 7600 14250 7450
Wire Wire Line
	14250 7450 13950 7450
Wire Wire Line
	13900 6400 14250 6400
Wire Wire Line
	14100 5650 14250 5650
Wire Wire Line
	12350 5650 12500 5650
Wire Wire Line
	12350 5400 12350 5650
Wire Wire Line
	2450 5650 2600 5650
Wire Wire Line
	2750 5750 2450 5750
Wire Wire Line
	2450 5550 2450 5400
Wire Wire Line
	4525 3075 4675 3075
Wire Wire Line
	4825 3175 4525 3175
Wire Wire Line
	4525 2975 4675 2975
Wire Wire Line
	14100 8300 14100 8350
Wire Wire Line
	14100 8350 14300 8350
Wire Wire Line
	14300 8650 13900 8650
Wire Wire Line
	13900 8500 14100 8500
Wire Wire Line
	14100 8500 14100 8550
Wire Wire Line
	14100 8550 14300 8550
Wire Wire Line
	14300 8750 14100 8750
Wire Wire Line
	14100 8750 14100 8800
Wire Wire Line
	14100 8800 13900 8800
Wire Wire Line
	14300 8450 13950 8450
Wire Wire Line
	13950 8450 13950 8300
Wire Wire Line
	14250 6900 14150 6900
Wire Wire Line
	14150 6900 14150 6800
Connection ~ 14150 6800
Wire Wire Line
	10175 1500 10225 1500
Wire Wire Line
	11650 8550 11650 8500
Connection ~ 11650 8500
Wire Wire Line
	11650 8500 11450 8500
Wire Wire Line
	11450 8250 11450 8300
Wire Wire Line
	10750 8250 10750 8300
Connection ~ 10750 8500
Connection ~ 11450 8500
Connection ~ 11450 8300
Connection ~ 10750 8300
Wire Wire Line
	12250 8500 12550 8500
Wire Wire Line
	10350 8500 10750 8500
Connection ~ 10350 9400
Wire Wire Line
	1850 850  1875 850 
Wire Wire Line
	11650 9000 11650 8950
Wire Wire Line
	11650 7600 11650 7550
Connection ~ 11650 7550
Wire Wire Line
	11650 7550 11450 7550
Wire Wire Line
	11450 7300 11450 7350
Wire Wire Line
	10750 7300 10750 7350
Connection ~ 10750 7550
Connection ~ 11450 7550
Connection ~ 11450 7350
Connection ~ 10750 7350
Wire Wire Line
	12250 7550 12550 7550
Wire Wire Line
	10350 7550 10750 7550
Wire Wire Line
	11650 8050 11650 8000
Connection ~ 10350 8500
Wire Wire Line
	6950 2850 6950 1950
Wire Wire Line
	6950 1950 6850 1950
Wire Wire Line
	5700 1950 6250 1950
Wire Wire Line
	7200 2850 6950 2850
Wire Wire Line
	5800 2150 5750 2150
Wire Wire Line
	5750 2150 5750 1950
Connection ~ 5750 1950
Wire Wire Line
	4150 1975 4350 1975
Wire Wire Line
	1500 2250 1500 2150
Wire Wire Line
	7850 8650 7500 8650
Wire Wire Line
	15450 6500 15550 6500
Wire Wire Line
	15550 6400 15550 6400
Wire Wire Line
	15300 6600 15550 6600
Wire Wire Line
	15450 7200 15550 7200
Wire Wire Line
	15550 7100 15550 7100
Wire Wire Line
	15300 7300 15550 7300
Wire Wire Line
	15450 8100 15550 8100
Wire Wire Line
	15550 8000 15550 8000
Wire Wire Line
	15300 8200 15550 8200
Wire Wire Line
	15450 8950 15550 8950
Wire Wire Line
	15550 8850 15550 8850
Wire Wire Line
	15300 9050 15550 9050
Wire Wire Line
	15450 9500 15550 9500
Wire Wire Line
	15550 9400 15550 9400
Wire Wire Line
	15300 9600 15550 9600
Wire Wire Line
	15450 5800 15550 5800
Wire Wire Line
	15550 5700 15550 5700
Wire Wire Line
	15300 5900 15550 5900
Wire Wire Line
	15450 5250 15550 5250
Wire Wire Line
	15550 5150 15550 5150
Wire Wire Line
	15300 5350 15550 5350
Wire Wire Line
	15450 4375 15550 4375
Wire Wire Line
	15550 4275 15550 4275
Wire Wire Line
	15300 4475 15550 4475
Wire Wire Line
	1100 6800 1550 6800
Wire Wire Line
	1100 6700 1200 6700
Wire Wire Line
	1100 7000 1550 7000
Wire Wire Line
	2600 6800 3050 6800
Wire Wire Line
	2600 6700 2700 6700
Wire Wire Line
	2600 7000 3050 7000
Wire Wire Line
	2700 6900 2600 6900
Wire Wire Line
	1200 6900 1100 6900
Wire Wire Line
	8100 2000 8100 1950
Wire Wire Line
	8100 750  8100 700 
Wire Wire Line
	7500 1050 7450 1050
Wire Wire Line
	7500 1250 7450 1250
Wire Wire Line
	7200 5850 7200 5750
Wire Wire Line
	7150 5750 7150 5650
Wire Wire Line
	7150 5650 7200 5650
Wire Wire Line
	7100 5650 7100 5550
Wire Wire Line
	7100 5550 7200 5550
Wire Wire Line
	7050 5600 7050 5450
Wire Wire Line
	7050 5450 7200 5450
Wire Wire Line
	7200 5200 7200 5300
Wire Wire Line
	7200 5300 7150 5300
Wire Wire Line
	6900 5100 7000 5100
Wire Wire Line
	1575 3200 1575 3250
Wire Wire Line
	1575 3250 1275 3250
Wire Wire Line
	1275 3350 1425 3350
Wire Wire Line
	1275 3650 1375 3650
Wire Wire Line
	1325 3750 1325 3650
Connection ~ 1325 3650
Wire Wire Line
	1275 2950 1375 2950
Connection ~ 1325 2950
Wire Wire Line
	1975 3650 1875 3650
Wire Wire Line
	1250 850  1150 850 
Wire Wire Line
	1500 1250 1150 1250
Connection ~ 1725 1050
Wire Wire Line
	10225 1200 9525 1200
Wire Wire Line
	10225 1300 10175 1300
Wire Wire Line
	10225 1600 9550 1600
Wire Wire Line
	9550 900  10225 900 
Wire Wire Line
	2375 1300 2375 1375
Wire Wire Line
	2375 1200 2375 1100
Wire Wire Line
	1150 750  1225 750 
Wire Wire Line
	1225 750  1225 600 
Wire Wire Line
	1225 600  2375 600 
Wire Wire Line
	4150 2800 4250 2800
Wire Wire Line
	4150 2800 4150 2700
Wire Wire Line
	9475 1000 10225 1000
Wire Wire Line
	14525 4250 14375 4250
Wire Wire Line
	14375 4200 14375 4325
Wire Wire Line
	14375 4200 14250 4200
Wire Wire Line
	14375 4100 14250 4100
Wire Wire Line
	14375 4000 14375 4100
Wire Wire Line
	14375 4050 14525 4050
Connection ~ 14375 4250
Connection ~ 14375 4050
Wire Wire Line
	14525 1600 14375 1600
Wire Wire Line
	14375 1550 14375 1675
Wire Wire Line
	14375 1550 14250 1550
Wire Wire Line
	14375 1450 14250 1450
Wire Wire Line
	14375 1350 14375 1450
Wire Wire Line
	14375 1400 14525 1400
Connection ~ 14375 1600
Connection ~ 14375 1400
Wire Wire Line
	14525 2050 14375 2050
Wire Wire Line
	14375 2050 14375 2100
Wire Wire Line
	14375 2100 14250 2100
Wire Wire Line
	14525 2250 14375 2250
Wire Wire Line
	14375 2250 14375 2200
Wire Wire Line
	14375 2200 14250 2200
Wire Wire Line
	14525 800  14375 800 
Wire Wire Line
	14375 800  14375 850 
Wire Wire Line
	14375 850  14250 850 
Wire Wire Line
	14525 1000 14375 1000
Wire Wire Line
	14375 1000 14375 950 
Wire Wire Line
	14375 950  14250 950 
Wire Wire Line
	14525 4700 14375 4700
Wire Wire Line
	14375 4700 14375 4750
Wire Wire Line
	14375 4750 14250 4750
Wire Wire Line
	14525 4900 14375 4900
Wire Wire Line
	14375 4900 14375 4850
Wire Wire Line
	14375 4850 14250 4850
Wire Wire Line
	14375 3450 15000 3450
Wire Wire Line
	14375 3450 14375 3500
Wire Wire Line
	14375 3500 14250 3500
Wire Wire Line
	14375 3650 15000 3650
Wire Wire Line
	14375 3650 14375 3600
Wire Wire Line
	14375 3600 14250 3600
Wire Wire Line
	14525 3550 14525 3650
Connection ~ 14525 3650
Wire Wire Line
	14925 3550 14925 3450
Connection ~ 14925 3450
Wire Wire Line
	2700 7100 2600 7100
Wire Wire Line
	1175 7100 1100 7100
Wire Wire Line
	15500 1600 15350 1600
Wire Wire Line
	15350 1600 15350 1675
Wire Wire Line
	15350 1350 15350 1400
Wire Wire Line
	15350 1400 15500 1400
Wire Wire Line
	15500 975  15350 975 
Wire Wire Line
	15350 975  15350 1050
Wire Wire Line
	15350 725  15350 775 
Wire Wire Line
	15350 775  15500 775 
Wire Wire Line
	12500 5050 12650 5050
Wire Wire Line
	12650 4950 12550 4950
Wire Wire Line
	7125 2550 7125 2750
Wire Wire Line
	7125 2750 7200 2750
Wire Wire Line
	1725 1100 1725 1050
Wire Wire Line
	7125 2550 7400 2550
Wire Wire Line
	7400 2550 7400 2450
Wire Wire Line
	3600 1225 3600 1150
Wire Wire Line
	2900 1825 3600 1825
Connection ~ 3250 1825
Wire Wire Line
	3525 1950 3600 1950
Wire Wire Line
	3600 1950 3600 1825
Wire Wire Line
	2225 950  2225 1100
Connection ~ 2050 950 
Wire Wire Line
	3250 1225 3250 1200
Wire Wire Line
	2900 1225 2900 1175
Wire Wire Line
	9300 7900 9300 8050
Wire Wire Line
	9450 7050 9450 8900
Wire Wire Line
	9450 7950 9300 7950
Connection ~ 9300 7950
Wire Wire Line
	9450 7050 9475 7050
Connection ~ 9450 7950
Wire Wire Line
	6450 7350 6450 8000
Wire Wire Line
	1925 7350 6450 7350
Wire Wire Line
	2925 8300 2925 8000
Connection ~ 2925 8000
Wire Wire Line
	2600 8275 2600 8000
Connection ~ 2600 8000
$Comp
L DIODE D1
U 1 1 54C4EFC4
P 2250 8000
F 0 "D1" H 2250 8100 40  0000 C CNN
F 1 "MBR 1045" H 2250 7900 40  0000 C CNN
F 2 "ACS712:MBR1045" H 2250 8000 60  0001 C CNN
F 3 "" H 2250 8000 60  0000 C CNN
	1    2250 8000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
