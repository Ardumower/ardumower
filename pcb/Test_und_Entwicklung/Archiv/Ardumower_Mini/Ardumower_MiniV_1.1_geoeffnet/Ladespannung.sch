EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
LIBS:device
LIBS:78xx-Regler-BuildingBlock_ModB_RevA-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 11 11
Title "Ardumower Shield - Ladespannungsmessung"
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
U 1 1 554BCCCE
P 6340 1505
AR Path="/554BCB67/554BCCCE" Ref="R12"  Part="1" 
AR Path="/554C1C35/554BCCCE" Ref="R9"  Part="1" 
F 0 "R9" V 6420 1505 40  0000 C CNN
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
U 1 1 554C8CE6
P 6340 2220
AR Path="/554BCB67/554C8CE6" Ref="R13"  Part="1" 
AR Path="/554C1C35/554C8CE6" Ref="R10"  Part="1" 
F 0 "R10" V 6420 2220 40  0000 C CNN
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
L GND #PWR164
U 1 1 554C8CE8
P 6340 2600
AR Path="/554BCB67/554C8CE8" Ref="#PWR164"  Part="1" 
AR Path="/554C1C35/554C8CE8" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 6340 2350 60  0001 C CNN
F 1 "GND" H 6340 2450 60  0000 C CNN
F 2 "" H 6340 2600 60  0000 C CNN
F 3 "" H 6340 2600 60  0000 C CNN
	1    6340 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6340 2470 6340 2600
Connection ~ 6340 1870
Text HLabel 5625 1150 0    60   Input ~ 0
Ladespannung
Wire Wire Line
	5625 1150 6340 1150
Wire Wire Line
	6340 1150 6340 1255
Text GLabel 6900 1870 2    60   Output ~ 0
pinChargeVoltage
Wire Wire Line
	6900 1870 6340 1870
$EndSCHEMATC
