EESchema Schematic File Version 2
LIBS:Wlan_ESP8266
LIBS:power
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 22 25
Title "Ardumower Shield - Batteriespannungsmessung"
Date ""
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R12
U 1 1 554C8CE5
P 6340 1505
F 0 "R12" V 6420 1505 40  0000 C CNN
F 1 "47K 0,1%" V 6347 1506 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 6270 1505 30  0001 C CNN
F 3 "" H 6340 1505 30  0000 C CNN
F 4 "R: MPR 47,0K" H 6340 1505 60  0001 C CNN "Bestellnummer"
F 5 "Value" H 6340 1505 60  0001 C CNN "Technische Daten"
	1    6340 1505
	-1   0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 554BCD3E
P 6340 2220
F 0 "R13" V 6420 2220 40  0000 C CNN
F 1 "5,10K 0,1%" V 6347 2221 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 6270 2220 30  0001 C CNN
F 3 "" H 6340 2220 30  0000 C CNN
F 4 "Value" H 6340 2220 60  0001 C CNN "Bestellnummer"
F 5 "Value" H 6340 2220 60  0001 C CNN "Technische Daten"
	1    6340 2220
	1    0    0    -1  
$EndComp
$Comp
L Z-DIODE ZD4
U 1 1 554BCD9F
P 6660 2195
F 0 "ZD4" H 6660 2295 40  0000 C CNN
F 1 "ZD-5W 5,1" H 6660 2095 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 6660 2195 60  0001 C CNN
F 3 "" H 6660 2195 60  0000 C CNN
F 4 "R: ZD-5W 5,1" H 6660 2195 60  0001 C CNN "Bestellnummer"
F 5 "Value" H 6660 2195 60  0001 C CNN "Technische Daten"
	1    6660 2195
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6340 1755 6340 1970
$Comp
L GND #PWR0172
U 1 1 554BD908
P 6340 2600
F 0 "#PWR0172" H 6340 2350 60  0001 C CNN
F 1 "GND" H 6340 2450 60  0000 C CNN
F 2 "" H 6340 2600 60  0000 C CNN
F 3 "" H 6340 2600 60  0000 C CNN
	1    6340 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6340 2470 6340 2600
$Comp
L GND #PWR0173
U 1 1 554C8CE9
P 6660 2600
F 0 "#PWR0173" H 6660 2350 60  0001 C CNN
F 1 "GND" H 6660 2450 60  0000 C CNN
F 2 "" H 6660 2600 60  0000 C CNN
F 3 "" H 6660 2600 60  0000 C CNN
	1    6660 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6660 2395 6660 2600
Wire Wire Line
	6660 1870 6660 1995
Wire Wire Line
	5885 1870 6900 1870
Connection ~ 6340 1870
Text HLabel 5475 1150 0    60   Input ~ 0
Batteriespannung
Wire Wire Line
	5475 1150 6340 1150
Wire Wire Line
	6340 1150 6340 1255
Text GLabel 6900 1870 2    60   Output ~ 0
pinBatteryVoltage
Connection ~ 6660 1870
$Comp
L Kondensator CC5
U 1 1 5558A3B2
P 5885 2215
F 0 "CC5" H 5935 2315 50  0000 L CNN
F 1 "100nF" H 5935 2115 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 5885 2215 60  0001 C CNN
F 3 "" H 5885 2215 60  0000 C CNN
F 4 "R: KERKO 100N" H 5885 2215 60  0001 C CNN "Bestellnummer"
F 5 "http://www.reichelt.de/Scheiben/KERKO-100N/3/index.html?&ACTION=3&LA=2&ARTICLE=9265&GROUPID=3169&artnr=KERKO+100N" H 5885 2215 60  0001 C CNN "Bestelllink"
	1    5885 2215
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0174
U 1 1 5558A47F
P 5885 2600
F 0 "#PWR0174" H 5885 2350 60  0001 C CNN
F 1 "GND" H 5885 2450 60  0000 C CNN
F 2 "" H 5885 2600 60  0000 C CNN
F 3 "" H 5885 2600 60  0000 C CNN
	1    5885 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5885 2600 5885 2415
Wire Wire Line
	5885 1870 5885 2015
$EndSCHEMATC
