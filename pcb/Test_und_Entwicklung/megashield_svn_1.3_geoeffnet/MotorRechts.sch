EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-rescue
LIBS:power
LIBS:device
LIBS:Zimprich
LIBS:conn
LIBS:transistors
LIBS:switches
LIBS:linear
LIBS:texas
LIBS:diode
LIBS:ardumower mega shield svn-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 33
Title "Ardumower shield SVN Version"
Date "2017-04-13"
Rev "1.3"
Comp "ML AG JL UZ"
Comment1 "Motordriverschutz von JürgenL"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2940 3870 0    60   BiDi ~ 0
MotorIN1
Text HLabel 5125 3870 2    60   BiDi ~ 0
MotorIN2
Wire Wire Line
	4895 3310 4895 3425
Wire Wire Line
	4895 3725 4895 3985
Wire Wire Line
	4895 4285 4895 4445
Wire Wire Line
	4500 3870 5125 3870
Connection ~ 4895 3870
Wire Wire Line
	3170 3310 3170 3425
Wire Wire Line
	3170 3725 3170 3980
Wire Wire Line
	3170 4280 3170 4445
Wire Wire Line
	2940 3870 3470 3870
Connection ~ 3170 3870
$Comp
L R RL3
U 1 1 57DB6B7C
P 4350 3870
F 0 "RL3" V 4430 3870 40  0000 C CNN
F 1 "1,8R 2W METALL" V 4255 3870 40  0000 C CNN
F 2 "Zimprich:Resistor_Horizontal_RM25mm-2W" V 4280 3870 30  0001 C CNN
F 3 "https://www.reichelt.de/2W-METALL-1-8/3/index.html?&ACTION=3&LA=446&ARTICLE=2309&artnr=2W+METALL+1%2C8&SEARCH=2W+METALL+1%2C8" H 4350 3870 30  0001 C CNN
F 4 "R: 2W METALL 1,8" H 4350 3870 60  0001 C CNN "Bestellnummer"
F 5 "Metalloxidschicht-Widerstand 2W, 5% 1,8 Ohm" H 4350 3870 60  0001 C CNN "Technische Daten"
	1    4350 3870
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3770 3870 4200 3870
Wire Wire Line
	4150 4165 4700 4165
Wire Wire Line
	4700 4165 4700 3870
Connection ~ 4700 3870
Wire Wire Line
	3950 4165 3325 4165
Wire Wire Line
	3325 4165 3325 3870
Connection ~ 3325 3870
$Comp
L C CC3
U 1 1 57DB6B7D
P 3620 3870
F 0 "CC3" V 3872 3870 50  0000 C CNN
F 1 "MP3-Y2 10N" V 3781 3870 50  0000 C CNN
F 2 "Zimprich:Kondensator_cnp_18x5mm" H 3735 3984 50  0001 L CNN
F 3 "https://www.reichelt.de/MP3-Y2-10N/3/index.html?&ACTION=3&LA=446&ARTICLE=32025&artnr=MP3-Y2+10N&SEARCH=MP3-Y2+10N" H 3735 3938 50  0001 L CNN
F 4 "Rastermass 15mm" H 3735 3885 60  0001 L CNN "Gehäuseart"
F 5 "R: MP3-Y2 10N" H 3735 3832 60  0001 L CNN "Bestelllink"
F 6 "IMA, Funk-Entstörkondensator, Klasse Y2" H 3735 3779 60  0001 L CNN "Technische Daten"
	1    3620 3870
	0    -1   -1   0   
$EndComp
Text HLabel 3950 4270 3    60   Input ~ 0
MotorOUT1
Text HLabel 4150 4270 3    60   Input ~ 0
MotorOUT2
$Comp
L GND #PWR027
U 1 1 57DB6B80
P 4895 4445
F 0 "#PWR027" H 4895 4195 50  0001 C CNN
F 1 "GND" H 4900 4272 50  0000 C CNN
F 2 "" H 4895 4445 50  0000 C CNN
F 3 "" H 4895 4445 50  0000 C CNN
	1    4895 4445
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 57DB6B81
P 3170 4445
F 0 "#PWR028" H 3170 4195 50  0001 C CNN
F 1 "GND" H 3175 4272 50  0000 C CNN
F 2 "" H 3170 4445 50  0000 C CNN
F 3 "" H 3170 4445 50  0000 C CNN
	1    3170 4445
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4165 3950 4270
Wire Wire Line
	4150 4165 4150 4270
$Comp
L D BY11
U 1 1 57E127F7
P 4895 3575
F 0 "BY11" V 4849 3653 50  0000 L CNN
F 1 "BY 500/1000" V 4940 3653 50  0000 L CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 4781 3653 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 4872 3653 50  0001 L CNN
F 4 "Value" V 4971 3653 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 5077 3653 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 5183 3653 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 4895 3575 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 4895 3575 60  0001 C CNN "Bauform"
	1    4895 3575
	0    1    1    0   
$EndComp
$Comp
L D BY12
U 1 1 57E2CAC7
P 4895 4135
F 0 "BY12" V 4849 4213 50  0000 L CNN
F 1 "BY 500/1000" V 4940 4213 50  0000 L CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 4781 4213 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 4872 4213 50  0001 L CNN
F 4 "Value" V 4971 4213 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 5077 4213 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 5183 4213 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 4895 4135 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 4895 4135 60  0001 C CNN "Bauform"
	1    4895 4135
	0    1    1    0   
$EndComp
$Comp
L D BY10
U 1 1 57E13213
P 3170 4130
F 0 "BY10" V 3124 4208 50  0000 L CNN
F 1 "BY 500/1000" V 3215 4208 50  0000 L CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 3056 4208 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3147 4208 50  0001 L CNN
F 4 "Value" V 3246 4208 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3352 4208 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 3458 4208 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 3170 4130 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 3170 4130 60  0001 C CNN "Bauform"
	1    3170 4130
	0    -1   1    0   
$EndComp
$Comp
L D BY9
U 1 1 57E134A5
P 3170 3575
F 0 "BY9" V 3124 3487 50  0000 R CNN
F 1 "BY 500/1000" V 3215 3487 50  0000 R CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 3056 3653 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3147 3653 50  0001 L CNN
F 4 "Value" V 3246 3653 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3352 3653 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 3458 3653 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 3170 3575 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 3170 3575 60  0001 C CNN "Bauform"
	1    3170 3575
	0    1    1    0   
$EndComp
Text HLabel 4895 3310 1    50   Input ~ 0
+24V
Text HLabel 3170 3310 1    50   Input ~ 0
+24V
$EndSCHEMATC
