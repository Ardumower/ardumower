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
Sheet 4 25
Title "Ardumower Shield - Perimeter"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR031
U 1 1 553A971E
P 3735 2085
F 0 "#PWR031" H 3735 1935 60  0001 C CNN
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
L GND #PWR032
U 1 1 553A97A2
P 3730 2185
F 0 "#PWR032" H 3730 1935 60  0001 C CNN
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
L +5V #PWR033
U 1 1 553AAAF0
P 3735 2495
F 0 "#PWR033" H 3735 2345 60  0001 C CNN
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
L GND #PWR034
U 1 1 553AAAFD
P 3730 2595
F 0 "#PWR034" H 3730 2345 60  0001 C CNN
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
