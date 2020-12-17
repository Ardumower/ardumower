EESchema Schematic File Version 4
LIBS:ardumower mega shield svn-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 33
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
	4895 3310 4895 3435
Wire Wire Line
	4895 3735 4895 3980
Wire Wire Line
	4895 4280 4895 4445
Wire Wire Line
	4500 3870 5125 3870
Connection ~ 4895 3870
Wire Wire Line
	3170 3310 3170 3415
Wire Wire Line
	3170 3715 3170 3980
Wire Wire Line
	3170 4280 3170 4445
Wire Wire Line
	2940 3870 3470 3870
Connection ~ 3170 3870
$Comp
L ardumower-mega-shield-svn-rescue:R-RESCUE-ardumower_mega_shield_svn RL1
U 1 1 57DAFD0D
P 4350 3870
F 0 "RL1" V 4430 3870 40  0000 C CNN
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
L ardumower-mega-shield-svn-rescue:C-RESCUE-ardumower_mega_shield_svn CC1
U 1 1 57DAFE10
P 3620 3870
F 0 "CC1" V 3872 3870 50  0000 C CNN
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
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR023
U 1 1 57DB0C47
P 4895 4445
F 0 "#PWR023" H 4895 4195 50  0001 C CNN
F 1 "GND" H 4900 4272 50  0000 C CNN
F 2 "" H 4895 4445 50  0000 C CNN
F 3 "" H 4895 4445 50  0000 C CNN
	1    4895 4445
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR024
U 1 1 57DB0D49
P 3170 4445
F 0 "#PWR024" H 3170 4195 50  0001 C CNN
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
L ardumower-mega-shield-svn-rescue:D-RESCUE-ardumower_mega_shield_svn BY3
U 1 1 57E0FCEF
P 4895 3585
F 0 "BY3" V 4849 3663 50  0000 L CNN
F 1 "BY 500/1000" V 4940 3663 50  0000 L CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 4781 3663 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 4872 3663 50  0001 L CNN
F 4 "Value" V 4971 3663 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 5077 3663 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 5183 3663 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 4895 3585 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 4895 3585 60  0001 C CNN "Bauform"
F 9 "Value" H 4895 3585 60  0001 C CNN "Funktion"
F 10 "Value" H 4895 3585 60  0001 C CNN "Hersteller"
F 11 "Value" H 4895 3585 60  0001 C CNN "Hersteller Bestellnummer"
	1    4895 3585
	0    1    1    0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:D-RESCUE-ardumower_mega_shield_svn BY4
U 1 1 57E10963
P 4895 4130
F 0 "BY4" V 4849 4208 50  0000 L CNN
F 1 "BY 500/1000" V 4940 4208 50  0000 L CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 4781 4208 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 4872 4208 50  0001 L CNN
F 4 "Value" V 4971 4208 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 5077 4208 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 5183 4208 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 4895 4130 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 4895 4130 60  0001 C CNN "Bauform"
	1    4895 4130
	0    1    1    0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:D-RESCUE-ardumower_mega_shield_svn BY2
U 1 1 57E10CA0
P 3170 4130
F 0 "BY2" V 3124 4042 50  0000 R CNN
F 1 "BY 500/1000" V 3215 4042 50  0000 R CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 3056 4208 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3147 4208 50  0001 L CNN
F 4 "Value" V 3246 4208 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3352 4208 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 3458 4208 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 3170 4130 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 3170 4130 60  0001 C CNN "Bauform"
	1    3170 4130
	0    1    1    0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:D-RESCUE-ardumower_mega_shield_svn BY1
U 1 1 57E10F58
P 3170 3565
F 0 "BY1" V 3124 3643 50  0000 L CNN
F 1 "BY 500/1000" V 3215 3643 50  0000 L CNN
F 2 "Zimprich:Diode_liegend_BY500_1000_RM15" V 3056 3643 50  0001 L CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3147 3643 50  0001 L CNN
F 4 "Value" V 3246 3643 60  0001 L CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" V 3352 3643 60  0001 L CNN "Bestelllink"
F 6 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" V 3458 3643 60  0001 L CNN "Technische Daten"
F 7 "R: BY 500/1000" H 3170 3565 60  0001 C CNN "Bestellnummer"
F 8 "DO-201" H 3170 3565 60  0001 C CNN "Bauform"
	1    3170 3565
	0    -1   1    0   
$EndComp
Text HLabel 3170 3310 1    50   Input ~ 0
+24V
Text HLabel 4895 3310 1    50   Input ~ 0
+24V
$EndSCHEMATC
