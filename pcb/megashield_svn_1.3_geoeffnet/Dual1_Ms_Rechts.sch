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
Sheet 13 25
Title "Ardumower Shield - Motortreiber 1 - Rechts"
Date ""
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 "Motordriverschutz von JürgenL"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2940 3870 0    60   BiDi ~ 0
MotorRechtsA
Text HLabel 5125 3870 2    60   BiDi ~ 0
MotorRechtsB
$Comp
L +24V #PWR0143
U 1 1 554BE90F
P 4895 3310
F 0 "#PWR0143" H 4895 3160 60  0001 C CNN
F 1 "+24V" H 4895 3450 60  0000 C CNN
F 2 "" H 4895 3310 60  0000 C CNN
F 3 "" H 4895 3310 60  0000 C CNN
	1    4895 3310
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR0144
U 1 1 554BE911
P 4895 4445
F 0 "#PWR0144" H 4895 4195 60  0001 C CNN
F 1 "GND" H 4895 4295 60  0000 C CNN
F 2 "" H 4895 4445 60  0000 C CNN
F 3 "" H 4895 4445 60  0000 C CNN
	1    4895 4445
	-1   0    0    -1  
$EndComp
$Comp
L DIODE DBY3
U 1 1 554BE913
P 4895 3580
F 0 "DBY3" H 4895 3680 40  0000 C CNN
F 1 "BY 500/1000" H 4895 3480 40  0000 C CNN
F 2 "ACS712:Diode_liegend_BY500_1000_RM15" H 4895 3580 60  0001 C CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 4895 3580 60  0001 C CNN
F 4 "R: BY 500/1000" H 4895 3580 60  0001 C CNN "Bestellnummer"
F 5 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" H 4895 3580 60  0001 C CNN "Technische Daten"
	1    4895 3580
	0    1    -1   0   
$EndComp
$Comp
L DIODE DBY4
U 1 1 554BE915
P 4895 4140
F 0 "DBY4" H 4895 4240 40  0000 C CNN
F 1 "BY 500/1000" H 4895 4040 40  0000 C CNN
F 2 "ACS712:Diode_liegend_BY500_1000_RM15" H 4895 4140 60  0001 C CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 4895 4140 60  0001 C CNN
F 4 "R: BY 500/1000" H 4895 4140 60  0001 C CNN "Bestellnummer"
F 5 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" H 4895 4140 60  0001 C CNN "Technische Daten"
	1    4895 4140
	0    1    -1   0   
$EndComp
Wire Wire Line
	4895 3380 4895 3310
Wire Wire Line
	4895 3780 4895 3940
Wire Wire Line
	4895 4340 4895 4445
Wire Wire Line
	4600 3870 5125 3870
Connection ~ 4895 3870
$Comp
L +24V #PWR0145
U 1 1 554BE918
P 3170 3310
F 0 "#PWR0145" H 3170 3160 60  0001 C CNN
F 1 "+24V" H 3170 3450 60  0000 C CNN
F 2 "" H 3170 3310 60  0000 C CNN
F 3 "" H 3170 3310 60  0000 C CNN
	1    3170 3310
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0146
U 1 1 554BE91A
P 3170 4445
F 0 "#PWR0146" H 3170 4195 60  0001 C CNN
F 1 "GND" H 3170 4295 60  0000 C CNN
F 2 "" H 3170 4445 60  0000 C CNN
F 3 "" H 3170 4445 60  0000 C CNN
	1    3170 4445
	1    0    0    -1  
$EndComp
$Comp
L DIODE DBY1
U 1 1 554BE91C
P 3170 3580
F 0 "DBY1" H 3170 3680 40  0000 C CNN
F 1 "BY 500/1000" H 3170 3480 40  0000 C CNN
F 2 "ACS712:Diode_liegend_BY500_1000_RM15" H 3170 3580 60  0001 C CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 3170 3580 60  0001 C CNN
F 4 "R: BY 500/1000" H 3170 3580 60  0001 C CNN "Bestellnummer"
F 5 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" H 3170 3580 60  0001 C CNN "Technische Daten"
	1    3170 3580
	0    -1   -1   0   
$EndComp
$Comp
L DIODE DBY2
U 1 1 554BE91E
P 3170 4140
F 0 "DBY2" H 3170 4240 40  0000 C CNN
F 1 "BY 500/1000" H 3170 4040 40  0000 C CNN
F 2 "ACS712:Diode_liegend_BY500_1000_RM15" H 3170 4140 60  0001 C CNN
F 3 "https://www.reichelt.de/BY-500-1000/3/index.html?&ACTION=3&LA=446&ARTICLE=6337&artnr=BY+500%2F1000&SEARCH=BY+500%2F1000" H 3170 4140 60  0001 C CNN
F 4 "R: BY 500/1000" H 3170 4140 60  0001 C CNN "Bestellnummer"
F 5 "Fast-Recovery-Gleichr.-Diode, DO201, 1000V, 5A" H 3170 4140 60  0001 C CNN "Technische Daten"
	1    3170 4140
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3170 3380 3170 3310
Wire Wire Line
	3170 3780 3170 3940
Wire Wire Line
	3170 4340 3170 4445
Wire Wire Line
	2940 3870 3415 3870
Connection ~ 3170 3870
$Comp
L CONN_2 P18
U 1 1 554BE920
P 4050 4515
F 0 "P18" V 4000 4515 40  0000 C CNN
F 1 "Right" V 4100 4515 40  0000 C CNN
F 2 "ACS712:Anschlussklemme_2P_RM5,08" H 4050 4515 60  0001 C CNN
F 3 "" H 4050 4515 60  0000 C CNN
	1    4050 4515
	0    -1   1    0   
$EndComp
$Comp
L R R17
U 1 1 55434642
P 4350 3870
F 0 "R17" V 4430 3870 40  0000 C CNN
F 1 "2W METALL 1,8" V 4357 3871 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM20mm" V 4280 3870 30  0001 C CNN
F 3 "https://www.reichelt.de/2W-METALL-1-8/3/index.html?&ACTION=3&LA=446&ARTICLE=2309&artnr=2W+METALL+1%2C8&SEARCH=2W+METALL+1%2C8" H 4350 3870 30  0001 C CNN
F 4 "R: 2W METALL 1,8" H 4350 3870 60  0001 C CNN "Bestellnummer"
F 5 "Metalloxidschicht-Widerstand 2W, 5% 1,8 Ohm" H 4350 3870 60  0001 C CNN "Technische Daten"
	1    4350 3870
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3815 3870 4100 3870
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
Text Notes 3840 3585 0    60   ~ 0
Kondensator noch \nnicht der richtige\ndarf kein Elko sein
$Comp
L Kondensator C1
U 1 1 554BE928
P 3615 3870
F 0 "C1" H 3665 3970 50  0000 L CNN
F 1 "MP3-Y2 10N Rastermass 15mm" H 3665 3770 50  0000 L CNN
F 2 "ACS712:Kondensator_cnp_18x5mm" H 3615 3870 60  0001 C CNN
F 3 "https://www.reichelt.de/MP3-Y2-10N/3/index.html?&ACTION=3&LA=446&ARTICLE=32025&artnr=MP3-Y2+10N&SEARCH=MP3-Y2+10N" H 3615 3870 60  0001 C CNN
F 4 "R: MP3-Y2 10N" H 3615 3870 60  0001 C CNN "Bestellnummer"
F 5 "IMA, Funk-Entstörkondensator, Klasse Y2" H 3615 3870 60  0001 C CNN "Technische Daten"
	1    3615 3870
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
