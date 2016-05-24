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
Sheet 8 11
Title "Ardumower Shield - Stepdownwandler"
Date ""
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DC-DC_Stepdown U7
U 1 1 553E5460
P 4630 1115
F 0 "U7" H 4630 1115 60  0000 C CNN
F 1 "DC  5V" H 4630 930 39  0000 C CNN
F 2 "ACS712:DC_DC_DSN2596_mit_Bohrloch_doppelte_Lochreihe" H 4630 1115 60  0001 C CNN
F 3 "" H 4630 1115 60  0000 C CNN
F 4 "Value" H 4630 1115 60  0001 C CNN "Bestellnummer"
	1    4630 1115
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 553E58DC
P 5030 965
F 0 "#PWR039" H 5030 715 60  0001 C CNN
F 1 "GND" H 5030 815 60  0000 C CNN
F 2 "" H 5030 965 60  0000 C CNN
F 3 "" H 5030 965 60  0000 C CNN
	1    5030 965 
	1    0    0    1   
$EndComp
$Comp
L GND #PWR040
U 1 1 553E58FB
P 4230 965
F 0 "#PWR040" H 4230 715 60  0001 C CNN
F 1 "GND" H 4230 815 60  0000 C CNN
F 2 "" H 4230 965 60  0000 C CNN
F 3 "" H 4230 965 60  0000 C CNN
	1    4230 965 
	1    0    0    1   
$EndComp
Wire Wire Line
	4980 1015 5030 1015
Wire Wire Line
	5030 1015 5030 965 
Wire Wire Line
	4280 1015 4230 1015
Wire Wire Line
	4230 1015 4230 965 
Wire Wire Line
	4980 1215 5240 1215
Text GLabel 5240 1215 2    60   Output ~ 0
Motorstrom
Text HLabel 3170 1215 0    60   Input ~ 0
Stepdownwandler_24V_In
Text Notes 6490 -55  0    60   ~ 0
Jürgen von 6.6.2015 \n3v 400ma eingang ausgang \n5v max 400ma eingang ausgang \n10v max 400ma eingang ausgang\n\nden 100µF ELKO kannst du durch einen 330nF Kerko ersetzen\ndie ELKOS setzen wir z.T an einer anderen Stelle im Board ein\nwo es mehr sinn macht das gehen wir nochmal an
Wire Wire Line
	4280 1215 3170 1215
$EndSCHEMATC
