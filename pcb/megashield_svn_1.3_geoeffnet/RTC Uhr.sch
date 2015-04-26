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
Sheet 12 17
Title "Ardumower shield SVN Version 1.3"
Date "Sonntag, 26. April 2015"
Rev "1.3"
Comp "von UweZ"
Comment1 "RTC Uhr"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DS1307+ U8
U 1 1 5540CB56
P 5395 3070
F 0 "U8" H 5395 3200 60  0000 C CNN
F 1 "DS1307+" H 5395 3005 60  0000 C CNN
F 2 "ACS712:Tiny_RTC_DS1307_geändert_mit_Bohrloch_4Lochreihen" H 5395 3070 60  0001 C CNN
F 3 "" H 5395 3070 60  0000 C CNN
F 4 "Value" H 5395 3070 60  0001 C CNN "Bestellnummer"
	1    5395 3070
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR098
U 1 1 5540D156
P 5395 2410
F 0 "#PWR098" H 5395 2260 60  0001 C CNN
F 1 "+5V" H 5395 2550 60  0000 C CNN
F 2 "" H 5395 2410 60  0000 C CNN
F 3 "" H 5395 2410 60  0000 C CNN
	1    5395 2410
	1    0    0    -1  
$EndComp
Wire Wire Line
	5395 2470 5395 2410
$Comp
L GND #PWR099
U 1 1 5540D459
P 5395 3790
F 0 "#PWR099" H 5395 3540 60  0001 C CNN
F 1 "GND" H 5395 3640 60  0000 C CNN
F 2 "" H 5395 3790 60  0000 C CNN
F 3 "" H 5395 3790 60  0000 C CNN
	1    5395 3790
	1    0    0    -1  
$EndComp
Wire Wire Line
	5395 3670 5395 3790
NoConn ~ 5995 3370
NoConn ~ 5995 2770
NoConn ~ 4795 3270
Text GLabel 4585 2770 0    39   Input ~ 0
SCL1
Wire Wire Line
	4585 2770 4795 2770
Text GLabel 4580 2970 0    39   BiDi ~ 0
SDA1
Wire Wire Line
	4580 2970 4795 2970
$EndSCHEMATC
