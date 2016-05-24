EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 18 25
Title "Ardumower Shield - Sonstiges"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L JUMPER JP14
U 1 1 553CA94E
P 2410 2650
F 0 "JP14" H 2410 2800 60  0000 C CNN
F 1 "Meas5.0V" H 2410 2570 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x02" H 2410 2650 60  0001 C CNN
F 3 "" H 2410 2650 60  0000 C CNN
F 4 "Value" H 2410 2650 60  0001 C CNN "Bestellnummer"
	1    2410 2650
	-1   0    0    -1  
$EndComp
$Comp
L JUMPER JP15
U 1 1 553CAB00
P 2410 3115
F 0 "JP15" H 2410 3265 60  0000 C CNN
F 1 "MeasA3.3V" H 2410 3035 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x02" H 2410 3115 60  0001 C CNN
F 3 "" H 2410 3115 60  0000 C CNN
	1    2410 3115
	-1   0    0    -1  
$EndComp
$Comp
L JUMPER JP13
U 1 1 553CAB7C
P 2410 2220
F 0 "JP13" H 2410 2370 60  0000 C CNN
F 1 "Meas3.3V" H 2410 2140 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x02" H 2410 2220 60  0001 C CNN
F 3 "" H 2410 2220 60  0000 C CNN
F 4 "Value" H 2410 2220 60  0001 C CNN "Bestellnummer"
	1    2410 2220
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR0159
U 1 1 553CB63B
P 2775 2220
F 0 "#PWR0159" H 2775 2180 30  0001 C CNN
F 1 "+3.3V" V 2775 2385 30  0000 C CNN
F 2 "" H 2775 2220 60  0000 C CNN
F 3 "" H 2775 2220 60  0000 C CNN
	1    2775 2220
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR0160
U 1 1 553CB667
P 2770 2650
F 0 "#PWR0160" H 2770 2500 60  0001 C CNN
F 1 "+5V" V 2770 2860 60  0000 C CNN
F 2 "" H 2770 2650 60  0000 C CNN
F 3 "" H 2770 2650 60  0000 C CNN
	1    2770 2650
	0    1    1    0   
$EndComp
Text GLabel 2770 3115 2    60   Input ~ 0
PowerA3,3
Wire Wire Line
	2710 2220 2775 2220
Wire Wire Line
	2710 2650 2770 2650
Wire Wire Line
	2710 3115 2770 3115
Wire Wire Line
	2110 2220 2050 2220
Wire Wire Line
	2050 2220 2050 3115
Wire Wire Line
	2110 2650 1860 2650
Wire Wire Line
	2050 3115 2110 3115
Connection ~ 2050 2650
Text GLabel 1860 2650 0    60   Input ~ 0
Voltage measurement
$EndSCHEMATC
