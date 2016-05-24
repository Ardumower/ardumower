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
Sheet 23 27
Title "Ardumower Shield - Verpolungsschutz Ladespannung"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MOS_P Q2
U 1 1 553AC2EB
P 5095 1935
F 0 "Q2" V 5415 1930 70  0000 C CNN
F 1 "IRF9530N" V 5310 1900 60  0000 C CNN
F 2 "Transistors_TO-220:TO-220_FET-GDS_Vertical" H 5095 1935 60  0001 C CNN
F 3 "" H 5095 1935 60  0000 C CNN
	1    5095 1935
	0    -1   -1   0   
$EndComp
$Comp
L R R27
U 1 1 553AC2EC
P 5095 2770
F 0 "R27" V 5175 2770 40  0000 C CNN
F 1 "100K" V 5102 2771 40  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5025 2770 30  0001 C CNN
F 3 "" H 5095 2770 30  0000 C CNN
	1    5095 2770
	1    0    0    -1  
$EndComp
Wire Wire Line
	5095 2035 5095 2520
Wire Wire Line
	5245 1835 6025 1835
Wire Wire Line
	4385 1835 4945 1835
Text HLabel 6025 1835 2    60   Output ~ 0
Verpols.L.aus
Text HLabel 4385 1835 0    60   Input ~ 0
Verpol.s.L.in
$Comp
L GND #PWR0180
U 1 1 553AC2ED
P 5095 3155
F 0 "#PWR0180" H 5095 2905 60  0001 C CNN
F 1 "GND" H 5095 3005 60  0000 C CNN
F 2 "" H 5095 3155 60  0000 C CNN
F 3 "" H 5095 3155 60  0000 C CNN
	1    5095 3155
	1    0    0    -1  
$EndComp
Wire Wire Line
	5095 3020 5095 3155
$Comp
L Z-DIODE ZD4
U 1 1 553A38F8
P 5525 2240
F 0 "ZD4" H 5525 2340 40  0000 C CNN
F 1 "SMD ZF 15" H 5525 2140 40  0000 C CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 5525 2240 60  0001 C CNN
F 3 "" H 5525 2240 60  0000 C CNN
F 4 "Chip-Zener-Diode 0,5W 15V" H 5525 2240 60  0001 C CNN "Technische Daten"
F 5 "R: SMD ZF 15" H 5525 2240 60  0001 C CNN "Bestellnummer"
F 6 "Mini Melf" H 5525 2240 60  0001 C CNN "Bauform"
F 7 "http://www.reichelt.de/SMD-ZF-15/3/index.html?&ACTION=3&LA=446&ARTICLE=18932&artnr=SMD+ZF+15&SEARCH=SMD+ZF+15" H 5525 2240 60  0001 C CNN "Bestelllink"
	1    5525 2240
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5525 2440 5095 2440
Connection ~ 5095 2440
Wire Wire Line
	5525 2040 5525 1835
Connection ~ 5525 1835
$EndSCHEMATC
