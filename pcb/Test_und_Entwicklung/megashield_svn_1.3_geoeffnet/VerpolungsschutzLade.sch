EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-rescue
LIBS:power
LIBS:device
LIBS:Zimprich
LIBS:conn
LIBS:transistors
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 23 24
Title "Ardumower shield SVN Version"
Date "2016-09-25"
Rev "1.21"
Comp "ML AG JL UZ"
Comment1 "Unterspannungsschutz von AlexanderG"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R_Small R57
U 1 1 57E64A6C
P 4905 3250
F 0 "R57" H 4964 3296 50  0000 L CNN
F 1 "100K" H 4964 3205 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 4905 3250 50  0001 C CNN
F 3 "" H 4905 3250 50  0001 C CNN
F 4 "Value" H 4964 3371 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4964 3265 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4964 3159 60  0001 L CNN "Technische Daten"
F 7 "Value" H 4964 3053 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4964 2947 60  0001 L CNN "Bauform"
	1    4905 3250
	-1   0    0    -1  
$EndComp
$Comp
L ZENER D7
U 1 1 57E64BD0
P 5290 3255
F 0 "D7" V 5244 3334 50  0000 L CNN
F 1 "SMD ZF 15" V 5335 3334 50  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 5290 3255 50  0001 C CNN
F 3 "" H 5290 3255 50  0001 C CNN
F 4 "Value" V 5169 3334 60  0001 L CNN "Gehäuseart"
F 5 "http://www.reichelt.de/SMD-ZF-15/3/index.html?&ACTION=3&LA=446&ARTICLE=18932&artnr=SMD+ZF+15&SEARCH=SMD+ZF+15" V 5275 3334 60  0001 L CNN "Bestelllink"
F 6 "Chip-Zener-Diode 0,5W 15V" V 5381 3334 60  0001 L CNN "Technische Daten"
F 7 "R: ZD 15" V 5487 3334 60  0001 L CNN "Bestellnummer"
F 8 "Value" V 5593 3334 60  0001 L CNN "Bauform"
	1    5290 3255
	0    1    1    0   
$EndComp
Wire Wire Line
	5290 3455 4905 3455
Wire Wire Line
	4905 3350 4905 3620
Wire Wire Line
	5290 3055 5290 2755
Wire Wire Line
	5055 2755 5480 2755
Text HLabel 5480 2755 2    39   Output ~ 0
Ausgang
Connection ~ 5290 2755
Text HLabel 4480 2755 0    39   Input ~ 0
Eingang
Wire Wire Line
	4480 2755 4655 2755
$Comp
L GND #PWR184
U 1 1 57E64EC6
P 4905 3620
F 0 "#PWR184" H 4905 3370 50  0001 C CNN
F 1 "GND" H 4910 3447 50  0000 C CNN
F 2 "" H 4905 3620 50  0000 C CNN
F 3 "" H 4905 3620 50  0000 C CNN
	1    4905 3620
	1    0    0    -1  
$EndComp
Connection ~ 4905 3455
Text Notes 4195 2960 0    39   ~ 0
Eingang\n10-80V
Text Notes 5950 3325 0    60   ~ 0
d7 geändert\nvon ZPD15 auf\nSMD ZF 15
$Comp
L IRF9540N Q4
U 1 1 57E9A340
P 4855 2855
F 0 "Q4" V 5317 2855 50  0000 C CNN
F 1 "IRF9530" V 5226 2855 50  0000 C CNN
F 2 "Power_Integrations:TO-220" V 5135 2855 50  0000 C CIN
F 3 "" H 4855 2855 50  0000 L CNN
	1    4855 2855
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4905 3055 4905 3150
Text Notes 2955 3905 0    60   ~ 0
evl ersetzen durch IRF9540N\nkann mehr strom und ist\nschon in der Unterspannungsabschaltung\nvorhanden\n\nals smd ersatz evl  IRF 9540NS
$EndSCHEMATC
