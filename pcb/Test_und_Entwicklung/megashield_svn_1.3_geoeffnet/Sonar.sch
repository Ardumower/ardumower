EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
LIBS:ina169_ic
LIBS:DS1307_Dil8
LIBS:device
LIBS:supply
LIBS:atmel
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 25
Title "Ardumower Shield  - Ultraschallsensoren"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3310 2530 2    60   Input ~ 0
pinSonarCenterTrigger
$Comp
L CONN_4 P1
U 1 1 553AEB77
P 2660 2480
F 0 "P1" V 2610 2480 50  0000 C CNN
F 1 "Sonar C." V 2710 2480 50  0000 C CNN
F 2 "w_conn_kk100:kk100_22-23-2041" H 2660 2480 60  0001 C CNN
F 3 "" H 2660 2480 60  0000 C CNN
F 4 "Value" H 2660 2480 60  0001 C CNN "Bestellnummer"
	1    2660 2480
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 553AEB8F
P 4405 2330
F 0 "#PWR028" H 4405 2080 60  0001 C CNN
F 1 "GND" V 4405 2105 60  0000 C CNN
F 2 "" H 4405 2330 60  0000 C CNN
F 3 "" H 4405 2330 60  0000 C CNN
	1    4405 2330
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR029
U 1 1 553AEBA4
P 3310 2430
F 0 "#PWR029" H 3310 2280 60  0001 C CNN
F 1 "+5V" V 3310 2645 60  0000 C CNN
F 2 "" H 3310 2430 60  0000 C CNN
F 3 "" H 3310 2430 60  0000 C CNN
	1    3310 2430
	0    1    1    0   
$EndComp
Wire Wire Line
	3310 2430 3010 2430
Wire Wire Line
	3010 2330 4405 2330
Wire Wire Line
	3010 2530 3310 2530
Text GLabel 4410 2630 2    60   Output ~ 0
pinSonarCenterEcho
Wire Wire Line
	3010 2630 4410 2630
Text GLabel 3310 3090 2    60   Input ~ 0
pinSonarRightTrigger
$Comp
L CONN_4 P2
U 1 1 553AF410
P 2660 3040
F 0 "P2" V 2610 3040 50  0000 C CNN
F 1 "Sonar R." V 2710 3040 50  0000 C CNN
F 2 "w_conn_kk100:kk100_22-23-2041" H 2660 3040 60  0001 C CNN
F 3 "" H 2660 3040 60  0000 C CNN
F 4 "Value" H 2660 3040 60  0001 C CNN "Bestellnummer"
	1    2660 3040
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 553AF416
P 4405 2890
F 0 "#PWR030" H 4405 2640 60  0001 C CNN
F 1 "GND" V 4405 2665 60  0000 C CNN
F 2 "" H 4405 2890 60  0000 C CNN
F 3 "" H 4405 2890 60  0000 C CNN
	1    4405 2890
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR031
U 1 1 553AF41C
P 3310 2990
F 0 "#PWR031" H 3310 2840 60  0001 C CNN
F 1 "+5V" V 3310 3205 60  0000 C CNN
F 2 "" H 3310 2990 60  0000 C CNN
F 3 "" H 3310 2990 60  0000 C CNN
	1    3310 2990
	0    1    1    0   
$EndComp
Wire Wire Line
	3310 2990 3010 2990
Wire Wire Line
	3010 2890 4405 2890
Wire Wire Line
	3010 3090 3310 3090
Text GLabel 4410 3190 2    60   Output ~ 0
pinSonarRightEcho
Wire Wire Line
	3010 3190 4410 3190
Text GLabel 3300 3655 2    60   Input ~ 0
pinSonarLeftTrigger
$Comp
L CONN_4 P3
U 1 1 553AFE20
P 2650 3605
F 0 "P3" V 2600 3605 50  0000 C CNN
F 1 "Sonar L." V 2700 3605 50  0000 C CNN
F 2 "w_conn_kk100:kk100_22-23-2041" H 2650 3605 60  0001 C CNN
F 3 "" H 2650 3605 60  0000 C CNN
F 4 "Value" H 2650 3605 60  0001 C CNN "Bestellnummer"
	1    2650 3605
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 553AFE26
P 4395 3455
F 0 "#PWR032" H 4395 3205 60  0001 C CNN
F 1 "GND" V 4395 3230 60  0000 C CNN
F 2 "" H 4395 3455 60  0000 C CNN
F 3 "" H 4395 3455 60  0000 C CNN
	1    4395 3455
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR033
U 1 1 553AFE2C
P 3300 3555
F 0 "#PWR033" H 3300 3405 60  0001 C CNN
F 1 "+5V" V 3300 3770 60  0000 C CNN
F 2 "" H 3300 3555 60  0000 C CNN
F 3 "" H 3300 3555 60  0000 C CNN
	1    3300 3555
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 3555 3000 3555
Wire Wire Line
	3000 3455 4395 3455
Wire Wire Line
	3000 3655 3300 3655
Text GLabel 4400 3755 2    60   Output ~ 0
pinSonarLeftEcho
Wire Wire Line
	3000 3755 4400 3755
$EndSCHEMATC
