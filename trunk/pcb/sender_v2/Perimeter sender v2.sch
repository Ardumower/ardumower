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
LIBS:w_microcontrollers
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
LIBS:MC33926
LIBS:Perimeter sender v2-cache
LIBS:ardumower mega shield svn-cache
LIBS:Arduino
LIBS:Ina169
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "25 sep 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MC33926 U3
U 1 1 53A98109
P 9675 2325
F 0 "U3" H 9625 1375 60  0000 C CNN
F 1 "MC33926" H 9675 3475 60  0000 C CNN
F 2 "sender_v2:MC_33926_31polig_mit_Bohrloch_neue_Masse" H 9825 2375 60  0001 C CNN
F 3 "~" H 9825 2375 60  0000 C CNN
	1    9675 2325
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 53A981F2
P 10500 2200
F 0 "#PWR01" H 10500 2200 30  0001 C CNN
F 1 "GND" H 10500 2130 30  0001 C CNN
F 2 "" H 10500 2200 60  0000 C CNN
F 3 "" H 10500 2200 60  0000 C CNN
	1    10500 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 53A98276
P 8625 2975
F 0 "#PWR02" H 8625 2975 30  0001 C CNN
F 1 "GND" H 8625 2905 30  0001 C CNN
F 2 "" H 8625 2975 60  0000 C CNN
F 3 "" H 8625 2975 60  0000 C CNN
	1    8625 2975
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR03
U 1 1 53A9829A
P 8575 2875
F 0 "#PWR03" H 8575 2965 20  0001 C CNN
F 1 "+5V" H 8575 2965 30  0000 C CNN
F 2 "" H 8575 2875 60  0000 C CNN
F 3 "" H 8575 2875 60  0000 C CNN
	1    8575 2875
	0    -1   -1   0   
$EndComp
Text GLabel 8675 1375 0    60   Input ~ 0
M2FB
Text GLabel 8225 1475 0    60   Input ~ 0
M2nSF
Text GLabel 8675 1775 0    60   Input ~ 0
M2IN1
Text GLabel 8225 1875 0    60   Input ~ 0
M2IN2
Text GLabel 8225 2175 0    60   Input ~ 0
EN
Text GLabel 8675 2275 0    60   Input ~ 0
M1FB
Text GLabel 8225 2375 0    60   Input ~ 0
M1nSF
Text GLabel 8200 5050 2    60   Output ~ 0
M1_DuoLED_Schleife1_Grün
Text GLabel 8675 2675 0    60   Input ~ 0
M1IN1
Text GLabel 8225 2775 0    60   Input ~ 0
M1IN2
Text GLabel 3700 5050 0    60   Input ~ 0
M1FB
Text GLabel 6350 5550 2    60   Input ~ 0
EN
Text GLabel 5925 5650 2    60   Input ~ 0
M1nSF
Text GLabel 8200 4850 2    60   Output ~ 0
M2_DuoLED_Schleife2_Grün
Text GLabel 6350 5750 2    60   Input ~ 0
M1IN1
Text GLabel 5925 5850 2    60   Input ~ 0
M1IN2
Text GLabel 6875 4950 2    60   Output ~ 0
M1_DuoLED_Schleife1_Rot
$Comp
L R R7
U 1 1 53A992CD
P 6500 5050
F 0 "R7" V 6580 5050 40  0000 C CNN
F 1 "220R" V 6507 5051 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 6430 5050 30  0001 C CNN
F 3 "~" H 6500 5050 30  0000 C CNN
	1    6500 5050
	0    1    -1   0   
$EndComp
$Comp
L R R5
U 1 1 53A992DC
P 6100 4950
F 0 "R5" V 6180 4950 40  0000 C CNN
F 1 "220R" V 6107 4951 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 6030 4950 30  0001 C CNN
F 3 "~" H 6100 4950 30  0000 C CNN
F 4 "Value" H 6100 4950 60  0001 C CNN "Bestellnummer"
	1    6100 4950
	0    1    1    0   
$EndComp
NoConn ~ 8825 1975
NoConn ~ 10425 2675
NoConn ~ 10425 2775
Text GLabel 3300 5150 0    60   Input ~ 0
M2FB
$Comp
L +5V #PWR04
U 1 1 53C6A2CB
P 3475 5950
F 0 "#PWR04" H 3475 6040 20  0001 C CNN
F 1 "+5V" H 3475 6075 30  0000 C CNN
F 2 "" H 3475 5950 60  0000 C CNN
F 3 "" H 3475 5950 60  0000 C CNN
	1    3475 5950
	0    -1   -1   0   
$EndComp
NoConn ~ 8825 2075
Text GLabel 5925 5150 2    60   Input ~ 0
M2nSF
Text GLabel 6875 4750 2    60   Output ~ 0
M2_DuoLED_Schleife2_Rot
Text GLabel 2975 4750 0    60   Output ~ 0
Mover_in_Ladestation
Text GLabel 6350 5250 2    60   Input ~ 0
M2IN1
Text GLabel 5925 5350 2    60   Input ~ 0
M2IN2
NoConn ~ 8825 3075
$Comp
L DC-DC_Stepdown U2
U 1 1 54D4FA89
P 2725 2850
F 0 "U2" H 2725 2850 28  0000 C CNN
F 1 "DC-DC_Stepdown" H 2725 2900 24  0000 C CNN
F 2 "sender_v2:DC_DC_DSN2596_mit_Bohrloch" H 2725 2850 60  0001 C CNN
F 3 "" H 2725 2850 60  0000 C CNN
	1    2725 2850
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 54D4FE5B
P 1750 1975
F 0 "P1" H 1750 2125 50  0000 C CNN
F 1 "Vin 24V" V 1850 1975 50  0000 C CNN
F 2 "sender_v2:Anschlussklemme_2P_RM5,08" H 1750 1975 60  0001 C CNN
F 3 "" H 1750 1975 60  0000 C CNN
	1    1750 1975
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 54D4FE86
P 1750 4325
F 0 "P2" H 1750 4475 50  0000 C CNN
F 1 "VOut 24V" V 1850 4325 50  0000 C CNN
F 2 "sender_v2:Anschlussklemme_2P_RM5,08" H 1750 4325 60  0001 C CNN
F 3 "" H 1750 4325 60  0000 C CNN
	1    1750 4325
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 54D5004F
P 1800 2275
F 0 "#PWR05" H 1800 2275 30  0001 C CNN
F 1 "GND" H 1800 2205 30  0001 C CNN
F 2 "" H 1800 2275 60  0000 C CNN
F 3 "" H 1800 2275 60  0000 C CNN
	1    1800 2275
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 54D500D0
P 3150 3050
F 0 "#PWR06" H 3150 3050 30  0001 C CNN
F 1 "GND" H 3150 2980 30  0001 C CNN
F 2 "" H 3150 3050 60  0000 C CNN
F 3 "" H 3150 3050 60  0000 C CNN
	1    3150 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 54D50107
P 2300 3050
F 0 "#PWR07" H 2300 3050 30  0001 C CNN
F 1 "GND" H 2300 2980 30  0001 C CNN
F 2 "" H 2300 3050 60  0000 C CNN
F 3 "" H 2300 3050 60  0000 C CNN
	1    2300 3050
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR08
U 1 1 54D50359
P 4200 2750
F 0 "#PWR08" H 4200 2600 60  0001 C CNN
F 1 "+12V" H 4200 2890 30  0000 C CNN
F 2 "" H 4200 2750 60  0000 C CNN
F 3 "" H 4200 2750 60  0000 C CNN
F 4 "Value" H 4200 2750 60  0001 C CNN "Bestellnummer"
	1    4200 2750
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR09
U 1 1 54D505CD
P 3475 6250
F 0 "#PWR09" H 3475 6100 60  0001 C CNN
F 1 "+12V" H 3475 6390 30  0000 C CNN
F 2 "" H 3475 6250 60  0000 C CNN
F 3 "" H 3475 6250 60  0000 C CNN
F 4 "Value" H 3475 6250 60  0001 C CNN "Bestellnummer"
	1    3475 6250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 54D50837
P 3675 6150
F 0 "#PWR010" H 3675 6150 30  0001 C CNN
F 1 "GND" H 3675 6080 30  0001 C CNN
F 2 "" H 3675 6150 60  0000 C CNN
F 3 "" H 3675 6150 60  0000 C CNN
	1    3675 6150
	0    1    -1   0   
$EndComp
$Comp
L ACS712 U1
U 1 1 54D51331
P 2100 3700
F 0 "U1" H 2100 3950 50  0000 C CNN
F 1 "INA 169" H 2100 3450 50  0000 C CNN
F 2 "sender_v2:INA169" H 2100 3700 60  0001 C CNN
F 3 "" H 2100 3700 60  0000 C CNN
F 4 "Value" H 2100 3700 60  0001 C CNN "Bestellnummer"
	1    2100 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 54D518BB
P 2000 4125
F 0 "#PWR011" H 2000 3875 60  0001 C CNN
F 1 "GND" H 2000 3975 60  0001 C CNN
F 2 "" H 2000 4125 60  0000 C CNN
F 3 "" H 2000 4125 60  0000 C CNN
F 4 "Value" H 2000 4125 60  0001 C CNN "Bestellnummer"
	1    2000 4125
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 54D51A61
P 2600 3925
F 0 "#PWR012" H 2600 3675 60  0001 C CNN
F 1 "GND" H 2600 3775 60  0001 C CNN
F 2 "" H 2600 3925 60  0000 C CNN
F 3 "" H 2600 3925 60  0000 C CNN
F 4 "Value" H 2600 3925 60  0001 C CNN "Bestellnummer"
	1    2600 3925
	1    0    0    -1  
$EndComp
Text GLabel 3700 5250 0    60   Input ~ 0
INA169
Text GLabel 2650 3700 2    60   Output ~ 0
INA169
$Comp
L POT RV1
U 1 1 54D524A0
P 1025 1025
F 0 "RV1" H 1025 925 50  0000 C CNN
F 1 "POT" H 1025 1025 50  0000 C CNN
F 2 "sender_v2:Potentiometer_VishaySpectrol-Econtrim-Type36T_3D" H 1025 1025 60  0001 C CNN
F 3 "" H 1025 1025 60  0000 C CNN
	1    1025 1025
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR013
U 1 1 54D52593
P 2600 3500
F 0 "#PWR013" H 2600 3590 20  0001 C CNN
F 1 "+5V" H 2600 3590 30  0000 C CNN
F 2 "" H 2600 3500 60  0000 C CNN
F 3 "" H 2600 3500 60  0000 C CNN
	1    2600 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 54D527F0
P 1125 1275
F 0 "#PWR014" H 1125 1275 30  0001 C CNN
F 1 "GND" H 1125 1205 30  0001 C CNN
F 2 "" H 1125 1275 60  0000 C CNN
F 3 "" H 1125 1275 60  0000 C CNN
	1    1125 1275
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR015
U 1 1 54D5285B
P 1125 775
F 0 "#PWR015" H 1125 865 20  0001 C CNN
F 1 "+5V" H 1125 900 30  0000 C CNN
F 2 "" H 1125 775 60  0000 C CNN
F 3 "" H 1125 775 60  0000 C CNN
	1    1125 775 
	0    1    1    0   
$EndComp
NoConn ~ 8825 2475
NoConn ~ 8825 2575
Text GLabel 1400 1025 2    60   Output ~ 0
POTI
Text GLabel 3300 5350 0    60   Input ~ 0
POTI
$Comp
L JUMPER JP1
U 1 1 54D53A2E
P 3750 2750
F 0 "JP1" H 3750 2900 60  0000 C CNN
F 1 "pwr12V" H 3750 2670 40  0000 C CNN
F 2 "sender_v2:Pin_Header_Straight_1x02" H 3750 2750 60  0001 C CNN
F 3 "~" H 3750 2750 60  0000 C CNN
	1    3750 2750
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 54D53F97
P 6500 4850
F 0 "R6" V 6580 4850 40  0000 C CNN
F 1 "220R" V 6507 4851 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 6430 4850 30  0001 C CNN
F 3 "~" H 6500 4850 30  0000 C CNN
	1    6500 4850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 54D5424D
P 6100 4750
F 0 "R4" V 6180 4750 40  0000 C CNN
F 1 "220R" V 6107 4751 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 6030 4750 30  0001 C CNN
F 3 "~" H 6100 4750 30  0000 C CNN
	1    6100 4750
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 54D5428C
P 3450 4750
F 0 "R3" V 3530 4750 40  0000 C CNN
F 1 "220R" V 3457 4751 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 3380 4750 30  0001 C CNN
F 3 "~" H 3450 4750 30  0000 C CNN
	1    3450 4750
	0    -1   -1   0   
$EndComp
$Comp
L F_10A EF1
U 1 1 54D55253
P 1700 2450
F 0 "EF1" H 1750 2375 40  0000 C CNN
F 1 "F_5A" H 1600 2370 40  0000 C CNN
F 2 "sender_v2:Fuseholder_Reichelt_PL112000" H 1700 2450 60  0001 C CNN
F 3 "" H 1700 2450 60  0000 C CNN
F 4 "R: PL112000" H 1600 2300 60  0000 C CNN "Bestellnummer"
	1    1700 2450
	0    1    1    0   
$EndComp
$Comp
L CONN_6 P3
U 1 1 54D5527A
P 6850 1350
F 0 "P3" V 6800 1350 60  0000 C CNN
F 1 "Status LED" V 6900 1350 60  0000 C CNN
F 2 "sender_v2:Pin_Header_Straight_1x06" H 6850 1350 60  0001 C CNN
F 3 "" H 6850 1350 60  0000 C CNN
F 4 "Value" H 6850 1350 60  0001 C CNN "Bestellnummer"
	1    6850 1350
	1    0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 54D55373
P 2625 1675
F 0 "C2" H 2675 1775 50  0000 L CNN
F 1 "100uF" H 2675 1575 50  0000 L CNN
F 2 "sender_v2:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 2625 1675 60  0001 C CNN
F 3 "" H 2625 1675 60  0000 C CNN
	1    2625 1675
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 54D555BA
P 2250 1675
F 0 "C1" H 2300 1775 50  0000 L CNN
F 1 "100uF" H 2300 1575 50  0000 L CNN
F 2 "sender_v2:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 2250 1675 60  0001 C CNN
F 3 "" H 2250 1675 60  0000 C CNN
	1    2250 1675
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 54D55677
P 2625 1975
F 0 "#PWR016" H 2625 1975 30  0001 C CNN
F 1 "GND" H 2625 1905 30  0001 C CNN
F 2 "" H 2625 1975 60  0000 C CNN
F 3 "" H 2625 1975 60  0000 C CNN
	1    2625 1975
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 54D55697
P 2250 1975
F 0 "#PWR017" H 2250 1975 30  0001 C CNN
F 1 "GND" H 2250 1905 30  0001 C CNN
F 2 "" H 2250 1975 60  0000 C CNN
F 3 "" H 2250 1975 60  0000 C CNN
	1    2250 1975
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR018
U 1 1 54D55836
P 2250 1300
F 0 "#PWR018" H 2250 1390 20  0001 C CNN
F 1 "+5V" H 2250 1425 30  0000 C CNN
F 2 "" H 2250 1300 60  0000 C CNN
F 3 "" H 2250 1300 60  0000 C CNN
F 4 "Value" H 2250 1300 60  0001 C CNN "Bestellnummer"
	1    2250 1300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR019
U 1 1 54D55968
P 2625 1300
F 0 "#PWR019" H 2625 1150 60  0001 C CNN
F 1 "+12V" H 2625 1425 30  0000 C CNN
F 2 "" H 2625 1300 60  0000 C CNN
F 3 "" H 2625 1300 60  0000 C CNN
F 4 "Value" H 2625 1300 60  0001 C CNN "Bestellnummer"
	1    2625 1300
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 54D55CFC
P 2000 2750
F 0 "D1" H 2000 2850 50  0000 C CNN
F 1 "MBR 1045" H 2000 2650 50  0000 C CNN
F 2 "sender_v2:MBR1045_Horizontal" H 2000 2750 60  0001 C CNN
F 3 "" H 2000 2750 60  0000 C CNN
	1    2000 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 54D55FB8
P 6375 1600
F 0 "#PWR020" H 6375 1600 30  0001 C CNN
F 1 "GND" H 6375 1530 30  0001 C CNN
F 2 "" H 6375 1600 60  0000 C CNN
F 3 "" H 6375 1600 60  0000 C CNN
	1    6375 1600
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR021
U 1 1 54D55FF9
P 8675 1575
F 0 "#PWR021" H 8675 1575 30  0001 C CNN
F 1 "GND" H 8675 1505 30  0001 C CNN
F 2 "" H 8675 1575 60  0000 C CNN
F 3 "" H 8675 1575 60  0000 C CNN
	1    8675 1575
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR022
U 1 1 54D560B9
P 8275 1675
F 0 "#PWR022" H 8275 1765 20  0001 C CNN
F 1 "+5V" H 8275 1800 30  0000 C CNN
F 2 "" H 8275 1675 60  0000 C CNN
F 3 "" H 8275 1675 60  0000 C CNN
F 4 "Value" H 8275 1675 60  0001 C CNN "Bestellnummer"
	1    8275 1675
	0    -1   -1   0   
$EndComp
$Comp
L +12V #PWR023
U 1 1 54D564FF
P 10500 1950
F 0 "#PWR023" H 10500 1800 60  0001 C CNN
F 1 "+12V" H 10500 2090 30  0000 C CNN
F 2 "" H 10500 1950 60  0000 C CNN
F 3 "" H 10500 1950 60  0000 C CNN
F 4 "Value" H 10500 1950 60  0001 C CNN "Bestellnummer"
	1    10500 1950
	1    0    0    -1  
$EndComp
NoConn ~ 10425 1525
NoConn ~ 10425 1425
Text GLabel 5000 1100 0    60   Input ~ 0
Mover_in_Ladestation
Text GLabel 5000 1500 0    60   Input ~ 0
M1_DuoLED_Schleife1_Grün
Text GLabel 6350 1200 0    60   Input ~ 0
M2_DuoLED_Schleife2_Grün
Text GLabel 6350 1400 0    60   Input ~ 0
M1_DuoLED_Schleife1_Rot
Text GLabel 5000 1300 0    60   Input ~ 0
M2_DuoLED_Schleife2_Rot
$Comp
L CONN_3 P4
U 1 1 54D57EFB
P 6850 2200
F 0 "P4" V 6800 2200 50  0000 C CNN
F 1 "V.LED" V 6900 2200 40  0000 C CNN
F 2 "sender_v2:Pin_Header_Straight_1x03" H 6850 2200 60  0001 C CNN
F 3 "" H 6850 2200 60  0000 C CNN
F 4 "Value" H 6850 2200 60  0001 C CNN "Bestellnummer"
	1    6850 2200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54D586F5
P 3150 1675
F 0 "R1" V 3230 1675 40  0000 C CNN
F 1 "220R" V 3157 1676 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 3080 1675 30  0001 C CNN
F 3 "~" H 3150 1675 30  0000 C CNN
	1    3150 1675
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR024
U 1 1 54D58864
P 3150 1300
F 0 "#PWR024" H 3150 1390 20  0001 C CNN
F 1 "+5V" H 3150 1425 30  0000 C CNN
F 2 "" H 3150 1300 60  0000 C CNN
F 3 "" H 3150 1300 60  0000 C CNN
F 4 "Value" H 3150 1300 60  0001 C CNN "Bestellnummer"
	1    3150 1300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR025
U 1 1 54D58885
P 3350 1300
F 0 "#PWR025" H 3350 1150 60  0001 C CNN
F 1 "+12V" H 3350 1425 30  0000 C CNN
F 2 "" H 3350 1300 60  0000 C CNN
F 3 "" H 3350 1300 60  0000 C CNN
F 4 "Value" H 3350 1300 60  0001 C CNN "Bestellnummer"
	1    3350 1300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54D588A5
P 3350 1675
F 0 "R2" V 3430 1675 40  0000 C CNN
F 1 "560R" V 3357 1676 40  0000 C CNN
F 2 "sender_v2:Resistor_Horizontal_RM10mm" V 3280 1675 30  0001 C CNN
F 3 "~" H 3350 1675 30  0000 C CNN
F 4 "Value" H 3350 1675 60  0001 C CNN "Bestellnummer"
	1    3350 1675
	1    0    0    -1  
$EndComp
Text GLabel 3150 2025 3    60   Output ~ 0
LED_5V
Text GLabel 5850 2100 0    60   Input ~ 0
LED_5V
Text GLabel 6350 2200 0    60   Input ~ 0
LED_12V
Text GLabel 3350 2025 3    60   Output ~ 0
LED_12V
$Comp
L GND #PWR026
U 1 1 54D58D55
P 6375 2300
F 0 "#PWR026" H 6375 2300 30  0001 C CNN
F 1 "GND" H 6375 2230 30  0001 C CNN
F 2 "" H 6375 2300 60  0000 C CNN
F 3 "" H 6375 2300 60  0000 C CNN
	1    6375 2300
	0    1    -1   0   
$EndComp
$Comp
L ARDUINO_NANO U4
U 1 1 54D6487C
P 4825 5450
F 0 "U4" H 4825 5460 60  0000 C CNN
F 1 "ARDUINO_NANO" H 4835 5230 60  0000 C CNN
F 2 "sender_v2:arduino_nano" H 4825 5450 60  0001 C CNN
F 3 "" H 4825 5450 60  0000 C CNN
F 4 "Value" H 4825 5450 60  0001 C CNN "Bestellnummer"
	1    4825 5450
	1    0    0    -1  
$EndComp
NoConn ~ 3875 6050
NoConn ~ 3875 4950
NoConn ~ 3875 4850
$Comp
L Bohrloch_3,2mm B1
U 1 1 54D689DE
P 12250 475
F 0 "B1" H 12530 635 60  0000 C CNN
F 1 "Bohrloch_3,2mm" H 12480 555 60  0000 C CNN
F 2 "sender_v2:Bohrloch_3,2mm" H 12250 475 60  0001 C CNN
F 3 "" H 12250 475 60  0000 C CNN
	1    12250 475 
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm B2
U 1 1 54D68AA0
P 12250 775
F 0 "B2" H 12530 935 60  0000 C CNN
F 1 "Bohrloch_3,2mm" H 12480 855 60  0000 C CNN
F 2 "sender_v2:Bohrloch_3,2mm" H 12250 775 60  0001 C CNN
F 3 "" H 12250 775 60  0000 C CNN
	1    12250 775 
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm B3
U 1 1 54D68AE1
P 12275 1100
F 0 "B3" H 12555 1260 60  0000 C CNN
F 1 "Bohrloch_3,2mm" H 12505 1180 60  0000 C CNN
F 2 "sender_v2:Bohrloch_3,2mm" H 12275 1100 60  0001 C CNN
F 3 "" H 12275 1100 60  0000 C CNN
	1    12275 1100
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm B4
U 1 1 54D68B23
P 13025 475
F 0 "B4" H 13305 635 60  0000 C CNN
F 1 "Bohrloch_3,2mm" H 13255 555 60  0000 C CNN
F 2 "sender_v2:Bohrloch_3,2mm" H 13025 475 60  0001 C CNN
F 3 "" H 13025 475 60  0000 C CNN
	1    13025 475 
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm B5
U 1 1 54D68B6A
P 13050 775
F 0 "B5" H 13330 935 60  0000 C CNN
F 1 "Bohrloch_3,2mm" H 13280 855 60  0000 C CNN
F 2 "sender_v2:Bohrloch_3,2mm" H 13050 775 60  0001 C CNN
F 3 "" H 13050 775 60  0000 C CNN
	1    13050 775 
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm B6
U 1 1 54D68BA6
P 13050 1050
F 0 "B6" H 13330 1210 60  0000 C CNN
F 1 "Bohrloch_3,2mm" H 13280 1130 60  0000 C CNN
F 2 "sender_v2:Bohrloch_3,2mm" H 13050 1050 60  0001 C CNN
F 3 "" H 13050 1050 60  0000 C CNN
	1    13050 1050
	1    0    0    -1  
$EndComp
NoConn ~ 12250 475 
NoConn ~ 12250 775 
NoConn ~ 12275 1100
NoConn ~ 13050 1050
NoConn ~ 13050 775 
NoConn ~ 13025 475 
Text Notes 4225 3800 0    60   ~ 0
Led Mover in Ladestation:\nAn wenn in Ladestation - aus wenn nicht in Ladestation\n\nSchleife 1 Duo LED\ngrün blinken Perimeter aktiv - rot Dauerlicht überlast oder fehler\n\nSchleife 2 Duo LED\ngrün blinken Perimeter aktiv - rot Dauerlicht überlast oder fehler\n\nMuss geklärt werden ob der DC Stepdownwanler in der Lage ist 2 Schleifen zu versorgen
NoConn ~ 3875 5450
NoConn ~ 3875 5550
NoConn ~ 3900 5650
NoConn ~ 3875 5750
NoConn ~ 5775 6250
NoConn ~ 5775 6150
NoConn ~ 5775 6050
NoConn ~ 5775 5950
Text Notes 7450 7500 0    60   ~ 0
Schleifensender
$Comp
L CONN_3 P5
U 1 1 54F4BE76
P 7490 2200
F 0 "P5" V 7440 2200 50  0000 C CNN
F 1 "V.LED GND" V 7540 2200 40  0000 C CNN
F 2 "sender_v2:Pin_Header_Straight_1x03" H 7490 2200 60  0001 C CNN
F 3 "" H 7490 2200 60  0000 C CNN
F 4 "Value" H 7490 2200 60  0001 C CNN "Bestellnummer"
	1    7490 2200
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P6
U 1 1 54F4BF8D
P 7550 1360
F 0 "P6" V 7500 1360 60  0000 C CNN
F 1 "Status LED GND" V 7600 1360 60  0000 C CNN
F 2 "sender_v2:Pin_Header_Straight_1x06" H 7550 1360 60  0001 C CNN
F 3 "" H 7550 1360 60  0000 C CNN
F 4 "Value" H 7550 1360 60  0001 C CNN "Bestellnummer"
	1    7550 1360
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 54F4C038
P 7090 2460
F 0 "#PWR027" H 7090 2460 30  0001 C CNN
F 1 "GND" H 7090 2390 30  0001 C CNN
F 2 "" H 7090 2460 60  0000 C CNN
F 3 "" H 7090 2460 60  0000 C CNN
	1    7090 2460
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR028
U 1 1 54F4C060
P 7120 1750
F 0 "#PWR028" H 7120 1750 30  0001 C CNN
F 1 "GND" H 7120 1680 30  0001 C CNN
F 2 "" H 7120 1750 60  0000 C CNN
F 3 "" H 7120 1750 60  0000 C CNN
	1    7120 1750
	0    1    -1   0   
$EndComp
Wire Wire Line
	8575 2875 8825 2875
Wire Wire Line
	3475 5950 3875 5950
Wire Wire Line
	8675 1375 8825 1375
Wire Wire Line
	8825 1475 8225 1475
Wire Wire Line
	8675 1775 8825 1775
Wire Wire Line
	8825 1875 8225 1875
Wire Wire Line
	8225 2175 8825 2175
Wire Wire Line
	8825 2275 8675 2275
Wire Wire Line
	8825 2375 8225 2375
Wire Wire Line
	8825 2675 8675 2675
Wire Wire Line
	8825 2775 8225 2775
Wire Wire Line
	3700 5050 3875 5050
Wire Wire Line
	5775 5750 6350 5750
Wire Wire Line
	5775 5850 5925 5850
Wire Wire Line
	5775 5550 6350 5550
Wire Wire Line
	5775 5650 5925 5650
Wire Wire Line
	5775 5250 6350 5250
Wire Wire Line
	8625 2975 8825 2975
Wire Wire Line
	5925 5350 5775 5350
Wire Wire Line
	3300 5350 3875 5350
Wire Wire Line
	5775 5150 5925 5150
Wire Wire Line
	1800 2275 1800 2175
Wire Wire Line
	3150 3050 3150 2950
Wire Wire Line
	2300 3050 2300 2950
Wire Wire Line
	3150 2950 3075 2950
Wire Wire Line
	2300 2950 2375 2950
Wire Wire Line
	4050 2750 4200 2750
Wire Wire Line
	3875 6250 3475 6250
Wire Wire Line
	3675 6150 3875 6150
Wire Wire Line
	1700 3800 1700 4125
Wire Wire Line
	1800 4125 1800 4075
Wire Wire Line
	1800 4075 2000 4075
Wire Wire Line
	2000 4075 2000 4125
Wire Wire Line
	2500 3800 2600 3800
Wire Wire Line
	2600 3800 2600 3925
Wire Wire Line
	3300 5150 3875 5150
Wire Wire Line
	2500 3700 2650 3700
Wire Wire Line
	3875 5250 3700 5250
Wire Wire Line
	2500 3600 2600 3600
Wire Wire Line
	2600 3600 2600 3500
Wire Wire Line
	1125 1275 1025 1275
Wire Wire Line
	1025 775  1125 775 
Wire Wire Line
	1400 1025 1175 1025
Wire Wire Line
	3075 2750 3450 2750
Wire Wire Line
	5850 4950 5775 4950
Wire Wire Line
	5775 4850 6250 4850
Wire Wire Line
	5850 4750 5775 4750
Wire Wire Line
	3875 4750 3700 4750
Wire Wire Line
	6250 5050 5775 5050
Wire Wire Line
	6350 4950 6875 4950
Wire Wire Line
	6750 5050 8200 5050
Wire Wire Line
	6750 4850 8200 4850
Wire Wire Line
	6350 4750 6875 4750
Wire Wire Line
	3200 4750 2975 4750
Wire Wire Line
	2625 1875 2625 1975
Wire Wire Line
	2250 1875 2250 1975
Wire Wire Line
	2250 1475 2250 1300
Wire Wire Line
	2625 1475 2625 1300
Wire Wire Line
	8675 1575 8825 1575
Wire Wire Line
	8825 1675 8275 1675
Wire Wire Line
	10500 2200 10500 2125
Wire Wire Line
	10500 2125 10425 2125
Wire Wire Line
	10425 2025 10500 2025
Wire Wire Line
	10500 2025 10500 1950
Wire Wire Line
	6375 1600 6500 1600
Wire Wire Line
	2375 2750 2200 2750
Wire Wire Line
	1700 2650 1700 3600
Wire Wire Line
	1700 2250 1700 2175
Wire Wire Line
	6500 1100 5000 1100
Wire Wire Line
	6350 1200 6500 1200
Wire Wire Line
	6500 1300 5000 1300
Wire Wire Line
	6350 1400 6500 1400
Wire Wire Line
	6500 1500 5000 1500
Wire Wire Line
	1800 2750 1700 2750
Connection ~ 1700 2750
Wire Wire Line
	3350 1425 3350 1300
Wire Wire Line
	3150 1425 3150 1300
Wire Wire Line
	3350 2025 3350 1925
Wire Wire Line
	3150 2025 3150 1925
Wire Wire Line
	6375 2300 6500 2300
Wire Wire Line
	6500 2100 5850 2100
Wire Wire Line
	6350 2200 6500 2200
Wire Wire Line
	7140 2100 7140 2460
Connection ~ 7140 2200
Wire Wire Line
	7140 2460 7090 2460
Connection ~ 7140 2300
Wire Wire Line
	7200 1110 7200 1750
Connection ~ 7200 1210
Connection ~ 7200 1410
Wire Wire Line
	7200 1310 7210 1310
Connection ~ 7200 1310
Wire Wire Line
	7200 1750 7120 1750
Connection ~ 7200 1610
Wire Wire Line
	7200 1610 7200 1510
Connection ~ 7200 1510
$EndSCHEMATC
