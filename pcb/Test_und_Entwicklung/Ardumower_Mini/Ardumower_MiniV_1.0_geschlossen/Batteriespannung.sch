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
Sheet 10 11
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
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6270 1505 30  0001 C CNN
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
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6270 2220 30  0001 C CNN
F 3 "" H 6340 2220 30  0000 C CNN
F 4 "Value" H 6340 2220 60  0001 C CNN "Bestellnummer"
F 5 "Value" H 6340 2220 60  0001 C CNN "Technische Daten"
	1    6340 2220
	1    0    0    -1  
$EndComp
Wire Wire Line
	6340 1755 6340 1970
$Comp
L GND #PWR043
U 1 1 554BD908
P 6340 2600
F 0 "#PWR043" H 6340 2350 60  0001 C CNN
F 1 "GND" H 6340 2450 60  0000 C CNN
F 2 "" H 6340 2600 60  0000 C CNN
F 3 "" H 6340 2600 60  0000 C CNN
	1    6340 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6340 2470 6340 2600
Connection ~ 6340 1870
Text HLabel 5475 1150 0    60   Input ~ 0
Batteriespannung
Wire Wire Line
	5475 1150 6340 1150
Wire Wire Line
	6340 1150 6340 1255
Text GLabel 6900 1870 2    60   Output ~ 0
pinBatteryVoltage
Wire Wire Line
	6900 1870 6340 1870
$EndSCHEMATC
