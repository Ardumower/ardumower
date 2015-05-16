EESchema Schematic File Version 2
LIBS:Wlan_ESP8266
LIBS:power
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 24
Title "Ardumower Shield - Odometry"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR023
U 1 1 553AD719
P 5610 2910
F 0 "#PWR023" H 5610 2660 60  0001 C CNN
F 1 "GND" V 5610 2685 60  0000 C CNN
F 2 "" H 5610 2910 60  0000 C CNN
F 3 "" H 5610 2910 60  0000 C CNN
	1    5610 2910
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR024
U 1 1 553AD72D
P 4655 2810
F 0 "#PWR024" H 4655 2660 60  0001 C CNN
F 1 "+5V" V 4655 3025 60  0000 C CNN
F 2 "" H 4655 2810 60  0000 C CNN
F 3 "" H 4655 2810 60  0000 C CNN
	1    4655 2810
	0    1    1    0   
$EndComp
$Comp
L CONN_4 P8
U 1 1 553AD741
P 4185 2960
F 0 "P8" V 4135 2960 50  0000 C CNN
F 1 "ODO Right" V 4235 2960 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x04" H 4185 2960 60  0001 C CNN
F 3 "" H 4185 2960 60  0000 C CNN
F 4 "Value" H 4185 2960 60  0001 C CNN "Bestellnummer"
	1    4185 2960
	-1   0    0    -1  
$EndComp
Text GLabel 4655 3010 2    60   Output ~ 0
pinOdometryRight
Text GLabel 5610 3110 2    60   Output ~ 0
pinOdometryRight2
Wire Wire Line
	4535 2810 4655 2810
Wire Wire Line
	4535 2910 5610 2910
Wire Wire Line
	4535 3010 4655 3010
Wire Wire Line
	4535 3110 5610 3110
$Comp
L GND #PWR025
U 1 1 553B1AA7
P 5605 3435
F 0 "#PWR025" H 5605 3185 60  0001 C CNN
F 1 "GND" V 5605 3210 60  0000 C CNN
F 2 "" H 5605 3435 60  0000 C CNN
F 3 "" H 5605 3435 60  0000 C CNN
	1    5605 3435
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR026
U 1 1 553B1AAD
P 4650 3335
F 0 "#PWR026" H 4650 3185 60  0001 C CNN
F 1 "+5V" V 4650 3550 60  0000 C CNN
F 2 "" H 4650 3335 60  0000 C CNN
F 3 "" H 4650 3335 60  0000 C CNN
	1    4650 3335
	0    1    1    0   
$EndComp
$Comp
L CONN_4 P9
U 1 1 553B1AB4
P 4180 3485
F 0 "P9" V 4130 3485 50  0000 C CNN
F 1 "ODO Left" V 4230 3485 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x04" H 4180 3485 60  0001 C CNN
F 3 "" H 4180 3485 60  0000 C CNN
F 4 "Value" H 4180 3485 60  0001 C CNN "Bestellnummer"
	1    4180 3485
	-1   0    0    -1  
$EndComp
Text GLabel 4650 3535 2    60   Output ~ 0
pinOdometryLeft
Text GLabel 5605 3635 2    60   Output ~ 0
pinOdometryLeft2
Wire Wire Line
	4530 3335 4650 3335
Wire Wire Line
	4530 3435 5605 3435
Wire Wire Line
	4530 3535 4650 3535
Wire Wire Line
	4530 3635 5605 3635
$EndSCHEMATC
