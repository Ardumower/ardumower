EESchema Schematic File Version 2
LIBS:Lötpad_2,5mm
LIBS:power
LIBS:Bluetooth_ZS_HC_05
LIBS:Bluetooth_CZ_HC_05
LIBS:ds1307
LIBS:Wlan_ESP8266
LIBS:transistor-fet
LIBS:transistor-fet+irf7201
LIBS:transistors
LIBS:w_transistor
LIBS:diode
LIBS:diode-1
LIBS:led
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 17
Title "Ardumower shield SVN Version 1.3"
Date "Sonntag, 26. April 2015"
Rev "1.3"
Comp "von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR037
U 1 1 553A971E
P 3735 2085
F 0 "#PWR037" H 3735 1935 60  0001 C CNN
F 1 "+5V" V 3735 2300 60  0000 C CNN
F 2 "" H 3735 2085 60  0000 C CNN
F 3 "" H 3735 2085 60  0000 C CNN
	1    3735 2085
	0    1    1    0   
$EndComp
$Comp
L CONN_3 P30
U 1 1 553A9732
P 3210 2185
F 0 "P30" V 3160 2185 50  0000 C CNN
F 1 "P.Right" V 3260 2185 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 3210 2185 60  0001 C CNN
F 3 "" H 3210 2185 60  0000 C CNN
F 4 "Value" H 3210 2185 60  0001 C CNN "Bestellnummer"
	1    3210 2185
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 553A97A2
P 3730 2185
F 0 "#PWR038" H 3730 1935 60  0001 C CNN
F 1 "GND" V 3730 1960 60  0000 C CNN
F 2 "" H 3730 2185 60  0000 C CNN
F 3 "" H 3730 2185 60  0000 C CNN
	1    3730 2185
	0    -1   -1   0   
$EndComp
Text GLabel 4070 2285 2    60   Output ~ 0
pinPerimeterRight
Wire Wire Line
	3560 2085 3735 2085
Wire Wire Line
	3560 2185 3730 2185
Wire Wire Line
	3560 2285 4070 2285
$Comp
L +5V #PWR039
U 1 1 553AAAF0
P 3735 2495
F 0 "#PWR039" H 3735 2345 60  0001 C CNN
F 1 "+5V" V 3735 2710 60  0000 C CNN
F 2 "" H 3735 2495 60  0000 C CNN
F 3 "" H 3735 2495 60  0000 C CNN
	1    3735 2495
	0    1    1    0   
$EndComp
$Comp
L CONN_3 P12
U 1 1 553AAAF7
P 3210 2595
F 0 "P12" V 3160 2595 50  0000 C CNN
F 1 "P.Left" V 3260 2595 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 3210 2595 60  0001 C CNN
F 3 "" H 3210 2595 60  0000 C CNN
F 4 "Value" H 3210 2595 60  0001 C CNN "Bestellnummer"
	1    3210 2595
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR040
U 1 1 553AAAFD
P 3730 2595
F 0 "#PWR040" H 3730 2345 60  0001 C CNN
F 1 "GND" V 3730 2370 60  0000 C CNN
F 2 "" H 3730 2595 60  0000 C CNN
F 3 "" H 3730 2595 60  0000 C CNN
	1    3730 2595
	0    -1   -1   0   
$EndComp
Text GLabel 4070 2695 2    60   Output ~ 0
pinPerimeterLeft
Wire Wire Line
	3560 2495 3735 2495
Wire Wire Line
	3560 2595 3730 2595
Wire Wire Line
	3560 2695 4070 2695
Text Notes 2095 2275 0    60   ~ 0
Perimeter rechts auf\nWunsch hinzugefügt
Text Notes 2375 2630 0    60   ~ 0
Perimeter coil
$EndSCHEMATC
