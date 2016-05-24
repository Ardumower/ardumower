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
Sheet 19 25
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
L DC-DC_Stepdown U1
U 1 1 553E9122
P 5520 1690
F 0 "U1" H 5520 1690 60  0000 C CNN
F 1 "DC 10V" H 5520 1505 39  0000 C CNN
F 2 "ACS712:DC_DC_DSN2596_mit_Bohrloch_doppelte_Lochreihe" H 5520 1690 60  0001 C CNN
F 3 "" H 5520 1690 60  0000 C CNN
F 4 "Value" H 5520 1690 60  0001 C CNN "Bestellnummer"
	1    5520 1690
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0171
U 1 1 553E9128
P 5920 1540
F 0 "#PWR0171" H 5920 1290 60  0001 C CNN
F 1 "GND" H 5920 1390 60  0000 C CNN
F 2 "" H 5920 1540 60  0000 C CNN
F 3 "" H 5920 1540 60  0000 C CNN
	1    5920 1540
	1    0    0    1   
$EndComp
$Comp
L GND #PWR0172
U 1 1 553E912E
P 5120 1540
F 0 "#PWR0172" H 5120 1290 60  0001 C CNN
F 1 "GND" H 5120 1390 60  0000 C CNN
F 2 "" H 5120 1540 60  0000 C CNN
F 3 "" H 5120 1540 60  0000 C CNN
	1    5120 1540
	1    0    0    1   
$EndComp
Wire Wire Line
	5870 1590 5920 1590
Wire Wire Line
	5920 1590 5920 1540
Wire Wire Line
	5170 1590 5120 1590
Wire Wire Line
	5120 1590 5120 1540
$Comp
L CP1 C2
U 1 1 553E9140
P 7145 2065
F 0 "C2" H 7195 2165 50  0000 L CNN
F 1 "220uf /63V" H 7195 1965 50  0000 L CNN
F 2 "w_capacitors:CP_12.5x15mm" H 7145 2065 60  0001 C CNN
F 3 "" H 7145 2065 60  0000 C CNN
F 4 "Elektrolytkondensator 220µF • 63V • 105°C +-20%" H 7145 2065 60  0001 C CNN "Technische Daten"
F 5 "R: VF 220/63 K-H13" H 7145 2065 60  0001 C CNN "Bestellnummer"
F 6 "SMD D12,5mm H13,5mm" H 7145 2065 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/VF-22-35-P-C/3/index.html?ACTION=3;ARTICLE=84769;SEARCH=VF%20220/63%20K-H13" H 7145 2065 60  0001 C CNN "Bestelllink"
	1    7145 2065
	1    0    0    -1  
$EndComp
Wire Wire Line
	7145 1790 7145 1865
Connection ~ 7145 1790
$Comp
L JUMPER JP1
U 1 1 553E9158
P 7615 1790
F 0 "JP1" H 7615 1940 60  0000 C CNN
F 1 "pwr 10V" H 7615 1710 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x02" H 7615 1790 60  0001 C CNN
F 3 "" H 7615 1790 60  0000 C CNN
F 4 "Value" H 7615 1790 60  0001 C CNN "Bestellnummer"
	1    7615 1790
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0173
U 1 1 553E9161
P 7145 2340
F 0 "#PWR0173" H 7145 2090 60  0001 C CNN
F 1 "GND" H 7145 2190 60  0000 C CNN
F 2 "" H 7145 2340 60  0000 C CNN
F 3 "" H 7145 2340 60  0000 C CNN
	1    7145 2340
	1    0    0    -1  
$EndComp
Wire Wire Line
	7145 2265 7145 2340
Wire Wire Line
	7915 1790 8095 1790
Text HLabel 4285 1790 0    60   Input ~ 0
Stepdownwandler_24V_In
$Comp
L F_10A PRFA4
U 1 1 555B2AC8
P 6550 1790
F 0 "PRFA4" H 6370 1870 40  0000 C CNN
F 1 "PFRA 040" H 6450 1710 40  0000 C CNN
F 2 "ACS712:PRFA_500_stehend" H 6550 1790 60  0001 C CNN
F 3 "" H 6550 1790 60  0000 C CNN
F 4 "R: PFRA 040" H 6550 1790 60  0001 C CNN "Bestellnummer"
F 5 "https://www.reichelt.de/PFRA-040/3/index.html?&ACTION=3&LA=446&ARTICLE=35206&artnr=PFRA+040&SEARCH=pfra+040" H 6550 1790 60  0001 C CNN "Bestelllink"
	1    6550 1790
	1    0    0    -1  
$EndComp
Wire Wire Line
	5870 1790 6350 1790
Wire Wire Line
	6750 1790 7315 1790
Text Notes 6490 -55  0    60   ~ 0
Jürgen von 6.6.2015 \n3v 400ma eingang ausgang \n5v max 400ma eingang ausgang \n10v max 400ma eingang ausgang\n\nden 100µF ELKO kannst du durch einen 330nF Kerko ersetzen\ndie ELKOS setzen wir z.T an einer anderen Stelle im Board ein\nwo es mehr sinn macht das gehen wir nochmal an
$Comp
L GND #PWR0174
U 1 1 55761997
P 6215 2545
F 0 "#PWR0174" H 6215 2295 60  0001 C CNN
F 1 "GND" H 6215 2395 60  0000 C CNN
F 2 "" H 6215 2545 60  0000 C CNN
F 3 "" H 6215 2545 60  0000 C CNN
	1    6215 2545
	1    0    0    -1  
$EndComp
Wire Wire Line
	6215 2320 6215 2545
$Comp
L DIODE DBY17
U 1 1 5576199E
P 6215 2120
F 0 "DBY17" H 6215 2220 40  0000 C CNN
F 1 "BY 500/1000" H 6215 2020 40  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-201AD_Horizontal_RM15" H 6215 2120 60  0001 C CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 6215 2120 60  0001 C CNN
F 4 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" H 6215 2120 60  0001 C CNN "Technische Daten"
F 5 "R: BY 500/1000" H 6215 2120 60  0001 C CNN "Bestellnummer"
F 6 "DO-201" H 6215 2120 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 6215 2120 60  0001 C CNN "Bestelllink"
	1    6215 2120
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6215 1920 6215 1790
Connection ~ 6215 1790
$Comp
L DIODE DBY15
U 1 1 55761C96
P 5520 2070
F 0 "DBY15" H 5520 2170 40  0000 C CNN
F 1 "BY 500/1000" H 5520 1970 40  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-201AD_Horizontal_RM15" H 5520 2070 60  0001 C CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 5520 2070 60  0001 C CNN
F 4 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" H 5520 2070 60  0001 C CNN "Technische Daten"
F 5 "R: BY 500/1000" H 5520 2070 60  0001 C CNN "Bestellnummer"
F 6 "DO-201" H 5520 2070 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 5520 2070 60  0001 C CNN "Bestelllink"
	1    5520 2070
	-1   0    0    1   
$EndComp
Wire Wire Line
	5720 2070 6025 2070
Wire Wire Line
	5320 2070 5015 2070
$Comp
L 15KEXXC DKE6
U 1 1 55761C9E
P 5015 2265
F 0 "DKE6" H 4965 2340 50  0000 L BNN
F 1 "P6SMB 33CA SMD" H 4965 2130 50  0000 L BNN
F 2 "w_smd_diode:do214aa" H 5015 2415 50  0001 C CNN
F 3 "" H 5015 2265 60  0000 C CNN
F 4 "Value" H 5015 2265 60  0001 C CNN "Technische Daten"
F 5 "R: P6SMB 33CA SMD" H 5015 2265 60  0001 C CNN "Bestellnummer"
F 6 "DO-214AA" H 5015 2265 60  0001 C CNN "Bauform"
F 7 "http://www.reichelt.de/SMD-ZF-15/3/index.html?ACTION=3;ARTICLE=42032;SEARCH=P6SMB%2033CA%20SMD" H 5015 2265 60  0001 C CNN "Bestelllink"
	1    5015 2265
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0175
U 1 1 55761CA4
P 5015 2545
F 0 "#PWR0175" H 5015 2295 60  0001 C CNN
F 1 "GND" H 5015 2395 60  0000 C CNN
F 2 "" H 5015 2545 60  0000 C CNN
F 3 "" H 5015 2545 60  0000 C CNN
	1    5015 2545
	1    0    0    -1  
$EndComp
Connection ~ 5015 2070
Wire Wire Line
	5015 2545 5015 2465
Wire Wire Line
	6025 2070 6025 1790
Connection ~ 6025 1790
Wire Wire Line
	5015 1790 5015 2165
Connection ~ 5015 1790
$Comp
L F_10A PRFA7
U 1 1 55762018
P 4705 1790
F 0 "PRFA7" H 4525 1870 40  0000 C CNN
F 1 "PFRA 040" H 4605 1710 40  0000 C CNN
F 2 "ACS712:PRFA_500_stehend" H 4705 1790 60  0001 C CNN
F 3 "" H 4705 1790 60  0000 C CNN
F 4 "R: PFRA 040" H 4705 1790 60  0001 C CNN "Bestellnummer"
F 5 "https://www.reichelt.de/PFRA-040/3/index.html?&ACTION=3&LA=446&ARTICLE=35206&artnr=PFRA+040&SEARCH=pfra+040" H 4705 1790 60  0001 C CNN "Bestelllink"
	1    4705 1790
	1    0    0    -1  
$EndComp
Wire Wire Line
	4285 1790 4505 1790
Wire Wire Line
	4905 1790 5170 1790
Text HLabel 8095 1790 2    60   Output ~ 0
+12V
$EndSCHEMATC
