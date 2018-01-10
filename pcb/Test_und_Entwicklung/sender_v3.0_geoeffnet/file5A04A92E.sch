EESchema Schematic File Version 4
LIBS:sender_v3.0_geoeffnet-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 8
Title "Ardumower shield SVN Version"
Date "2017-04-13"
Rev "1.3"
Comp "ML AG JL UZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L sender_v3.0_neu_geoeffnet-rescue:DC-DC_Stepdown-RESCUE-sender_v3.0_neu_geoeffnet U?
U 1 1 5A099537
P 2470 1140
F 0 "U?" H 2470 1190 60  0000 C CNN
F 1 "DC 9V" H 2470 890 60  0000 C CNN
F 2 "Zimprich:DC_DC_DSN2596_mit_Bohrloch_doppelte_Lochreihe" H 4270 1040 60  0001 C CNN
F 3 "" H 4270 1040 60  0001 C CNN
F 4 "Value" H 2470 1140 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2470 1140 60  0001 C CNN "Bestelllink"
	1    2470 1140
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR?
U 1 1 5A09953E
P 3620 1575
F 0 "#PWR?" H 3620 1425 50  0001 C CNN
F 1 "+9V" H 3620 1745 50  0000 C CNN
F 2 "" H 3620 1575 50  0000 C CNN
F 3 "" H 3620 1575 50  0000 C CNN
	1    3620 1575
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A099541
P 2820 990
F 0 "#PWR?" H 2820 740 50  0001 C CNN
F 1 "GND" H 2825 817 50  0000 C CNN
F 2 "" H 2820 990 50  0000 C CNN
F 3 "" H 2820 990 50  0000 C CNN
	1    2820 990 
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A099542
P 2120 990
F 0 "#PWR?" H 2120 740 50  0001 C CNN
F 1 "GND" H 2125 817 50  0000 C CNN
F 2 "" H 2120 990 50  0000 C CNN
F 3 "" H 2120 990 50  0000 C CNN
	1    2120 990 
	1    0    0    1   
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:F_Small-RESCUE-sender_v3.0_neu_geoeffnet F?
U 1 1 5A099543
P 3440 1240
F 0 "F?" H 3400 1300 50  0000 L CNN
F 1 "PTC" H 3320 1180 50  0000 L CNN
F 2 "SMD_Packages:Fuse_SMD" H 3440 1240 60  0001 C CNN
F 3 "" H 3440 1240 60  0000 C CNN
F 4 "Value" H 3440 1240 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SMD-Sicherungen/OMT-125-3-5A/3/index.html?ACTION=3&LA=446&ARTICLE=52972&GROUPID=7660&artnr=OMT+125+3%2C5A&SEARCH=smd%2Bsicherung%2B125" H 3440 1240 60  0001 C CNN "Bestelllink"
F 6 "https://www.reichelt.de/SMD-Sicherungen/OMH-125-HALTER/3/index.html?ACTION=3&LA=446&ARTICLE=77866&GROUPID=7660&artnr=OMH+125+HALTER&SEARCH=smd%2Bsicherung%2B125" H 3440 1240 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3440 1240 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3440 1240 60  0001 C CNN "Bauform"
F 9 "Value" H 3440 1240 60  0001 C CNN "Funktion"
F 10 "Value" H 3440 1240 60  0001 C CNN "Hersteller"
F 11 "Value" H 3440 1240 60  0001 C CNN "Hersteller Bestellnummer"
	1    3440 1240
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:D-RESCUE-sender_v3.0_neu_geoeffnet D?
U 1 1 5A099544
P 4285 1240
F 0 "D?" H 4285 1340 50  0000 C CNN
F 1 "S 1G SMD" H 4285 1140 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Standard" H 4285 1240 60  0001 C CNN
F 3 "" H 4285 1240 60  0001 C CNN
F 4 "Value" H 4285 1240 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SB-SKE-4F-Dioden/S-1G-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=95354&GROUPID=2991&artnr=S+1G+SMD&SEARCH=1N%2B4004%2BSMD" H 4285 1240 60  0001 C CNN "Bestelllink"
F 6 "Si-Gleichrichterdiode, DO214AC, 400V, 1A" H 4285 1240 60  0001 C CNN "Technische Daten"
F 7 "R: S 1G SMD" H 4285 1240 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4285 1240 60  0001 C CNN "Bauform"
F 9 "Value" H 4285 1240 60  0001 C CNN "Funktion"
F 10 "Value" H 4285 1240 60  0001 C CNN "Hersteller"
F 11 "Value" H 4285 1240 60  0001 C CNN "Hersteller Bestellnummer"
	1    4285 1240
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:LM2940CS-5.0-RESCUE-sender_v3.0_neu_geoeffnet U?
U 1 1 5A099545
P 6285 1240
F 0 "U?" H 6055 1491 50  0000 L CNN
F 1 "LM2940CS-5.0" H 6112 631 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-3Lead" H 6285 1240 50  0001 L CNN
F 3 "" H 6285 1240 60  0000 C CNN
	1    6285 1240
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:CP_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A099546
P 4735 1440
F 0 "C?" H 4745 1510 50  0000 L CNN
F 1 "22uF" H 4745 1360 50  0000 L CNN
F 2 "Zimprich:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 4735 1440 60  0001 C CNN
F 3 "" H 4735 1440 60  0000 C CNN
F 4 "Value" H 4735 1440 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4735 1440 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4735 1440 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4735 1440 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4735 1440 60  0001 C CNN "Bauform"
F 9 "Value" H 4735 1440 60  0001 C CNN "Funktion"
F 10 "Value" H 4735 1440 60  0001 C CNN "Hersteller"
F 11 "Value" H 4735 1440 60  0001 C CNN "Hersteller Bestellnummer"
	1    4735 1440
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A099547
P 5085 1440
F 0 "C?" H 5095 1510 50  0000 L CNN
F 1 "100nF" H 5095 1360 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5085 1440 60  0001 C CNN
F 3 "" H 5085 1440 60  0000 C CNN
	1    5085 1440
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A099548
P 7185 2915
F 0 "#PWR?" H 7185 2665 50  0001 C CNN
F 1 "GND" H 7185 2765 50  0000 C CNN
F 2 "" H 7185 2915 60  0000 C CNN
F 3 "" H 7185 2915 60  0000 C CNN
	1    7185 2915
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:CP_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A099549
P 7595 1440
F 0 "C?" H 7605 1510 50  0000 L CNN
F 1 "22uF" H 7605 1360 50  0000 L CNN
F 2 "Zimprich:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 7595 1440 60  0001 C CNN
F 3 "" H 7595 1440 60  0000 C CNN
F 4 "Value" H 7595 1440 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7595 1440 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7595 1440 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7595 1440 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7595 1440 60  0001 C CNN "Bauform"
F 9 "Value" H 7595 1440 60  0001 C CNN "Funktion"
F 10 "Value" H 7595 1440 60  0001 C CNN "Hersteller"
F 11 "Value" H 7595 1440 60  0001 C CNN "Hersteller Bestellnummer"
	1    7595 1440
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A09954A
P 7235 1440
F 0 "C?" H 7245 1510 50  0000 L CNN
F 1 "100nF" H 7245 1360 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7235 1440 60  0001 C CNN
F 3 "" H 7235 1440 60  0000 C CNN
	1    7235 1440
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09954B
P 7235 1665
F 0 "#PWR?" H 7235 1415 50  0001 C CNN
F 1 "GND" H 7235 1515 50  0000 C CNN
F 2 "" H 7235 1665 60  0000 C CNN
F 3 "" H 7235 1665 60  0000 C CNN
	1    7235 1665
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:LM2940CS-5.0-RESCUE-sender_v3.0_neu_geoeffnet U?
U 1 1 5A09954C
P 6285 2365
F 0 "U?" H 6055 2616 50  0000 L CNN
F 1 "LM3940IS-3.3" H 6112 1756 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-3Lead" H 6285 2365 50  0001 L CNN
F 3 "Value" H 6285 2365 60  0001 C CNN
F 4 "Value" H 6285 2365 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6285 2365 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6285 2365 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6285 2365 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6285 2365 60  0001 C CNN "Bauform"
	1    6285 2365
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A09954D
P 5185 2515
F 0 "C?" H 5195 2585 50  0000 L CNN
F 1 "100nF" H 5195 2435 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5185 2515 60  0001 C CNN
F 3 "" H 5185 2515 60  0000 C CNN
	1    5185 2515
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A09954E
P 7185 2565
F 0 "C?" H 7195 2635 50  0000 L CNN
F 1 "100nF" H 7195 2485 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7185 2565 60  0001 C CNN
F 3 "" H 7185 2565 60  0000 C CNN
	1    7185 2565
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09954F
P 5535 2915
F 0 "#PWR?" H 5535 2665 50  0001 C CNN
F 1 "GND" H 5535 2765 50  0000 C CNN
F 2 "" H 5535 2915 60  0000 C CNN
F 3 "" H 5535 2915 60  0000 C CNN
	1    5535 2915
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A099550
P 5485 1750
F 0 "#PWR?" H 5485 1500 50  0001 C CNN
F 1 "GND" H 5485 1600 50  0000 C CNN
F 2 "" H 5485 1750 60  0000 C CNN
F 3 "" H 5485 1750 60  0000 C CNN
	1    5485 1750
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:CP_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A099551
P 7605 2565
F 0 "C?" H 7615 2635 50  0000 L CNN
F 1 "22uF" H 7615 2485 50  0000 L CNN
F 2 "Zimprich:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 7605 2565 60  0001 C CNN
F 3 "" H 7605 2565 60  0000 C CNN
F 4 "Value" H 7605 2565 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7605 2565 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7605 2565 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7605 2565 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7605 2565 60  0001 C CNN "Bauform"
F 9 "Value" H 7605 2565 60  0001 C CNN "Funktion"
F 10 "Value" H 7605 2565 60  0001 C CNN "Hersteller"
F 11 "Value" H 7605 2565 60  0001 C CNN "Hersteller Bestellnummer"
	1    7605 2565
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Small-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A099552
P 3100 1240
F 0 "JP?" H 3100 1452 50  0000 C CNN
F 1 "pwr 9V" H 3100 1361 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3100 1240 50  0001 C CNN
F 3 "Value" H 3100 1240 50  0001 C CNN
F 4 "Value" H 3100 1240 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3100 1240 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3100 1240 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3100 1240 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3100 1240 60  0001 C CNN "Bauform"
	1    3100 1240
	1    0    0    -1  
$EndComp
Text Notes 6075 3315 0    60   ~ 0
Bezeichnung\nWert und\nFootprint richtig ?
Text Notes 3880 2205 0    60   ~ 0
Eingang vom 5V Ausgang ?
$Comp
L power:+5VP #PWR?
U 1 1 5A099553
P 8060 1240
F 0 "#PWR?" H 8060 1090 50  0001 C CNN
F 1 "+5VP" V 8060 1460 50  0000 C CNN
F 2 "" H 8060 1240 50  0000 C CNN
F 3 "" H 8060 1240 50  0000 C CNN
	1    8060 1240
	0    1    -1   0   
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 5A099554
P 8065 2365
F 0 "#PWR?" H 8215 2315 50  0001 C CNN
F 1 "+3.3VP" V 8065 2615 50  0000 C CNN
F 2 "" H 8065 2365 50  0000 C CNN
F 3 "" H 8065 2365 50  0000 C CNN
	1    8065 2365
	0    1    -1   0   
$EndComp
Text Notes -1265 -1415 0    79   ~ 0
[00:10:17] Jürgen Lange: dahinter sitzen die regler 5v und an dem hängt der regler 3,3v so alles was du an externen versorgungen hast die immer gleich bleiben egal ob 5 oder 3,3v kommen da her. alles was mal mit 3,3 oder 5v laufen muss kommt vom ioref\n[00:11:04] Kurzschuss - Uwe: okay das ist eine klare ansage\n[00:11:24] Jürgen Lange: Beispiel: die pca selber kommen von ioref die module dahinter sind festgelegt wie uhr etc die kommen vom längsregler\n[00:12:15] Kurzschuss - Uwe: die Jumper für die widerstände dann beim I2C bus dann auch von den Längsreglern\n[00:13:01] Jürgen Lange: wichtig ist nur das alles von einem dcdc wandler versorgt wird arduino und die module damit diese immer gemeinsam abgeschaltet werden\n[00:14:09] Kurzschuss - Uwe: müsste so eigentlich stimmen\n[00:14:20] Jürgen Lange: die pullups da kommt es darauf an auf welecher seite die sitzen wenn die zwei die auf der mega/due seite sitzen kommen über ioref der rest von der versorgung des jeweiligen moduls
Text Notes -1215 -680 0    79   ~ 0
im plan spannungsversorgung c2 bitte nach der ptc Sicherung f1. \nich würde an dieser stlle auch keine ptc sondern eine Schmelzsicherung\nempfehlen die den DCDC komplett rausnimmt wenn es zu heftig wird\nda ist ptc ungeeignet wenn du willst kannst du die ptc in den 3,3v und 5,V zweig machen
Wire Wire Line
	2120 990  2120 1040
Wire Wire Line
	3200 1240 3340 1240
Wire Wire Line
	2820 1240 3000 1240
Wire Wire Line
	1890 1240 2120 1240
Wire Wire Line
	2820 990  2820 1040
Wire Wire Line
	3540 1240 3620 1240
Wire Wire Line
	5585 1540 5485 1540
Wire Wire Line
	5485 1440 5585 1440
Wire Wire Line
	5485 1690 5085 1690
Wire Wire Line
	5085 1690 5085 1540
Connection ~ 5485 1540
Wire Wire Line
	4735 1690 4735 1540
Connection ~ 5085 1690
Connection ~ 5485 1690
Wire Wire Line
	6985 1240 7065 1240
Wire Wire Line
	7235 1240 7235 1340
Wire Wire Line
	7595 1240 7595 1340
Connection ~ 7235 1240
Wire Wire Line
	7235 1540 7235 1615
Connection ~ 7595 1240
Wire Wire Line
	5485 1440 5485 1540
Wire Wire Line
	5185 2365 5585 2365
Wire Wire Line
	5185 2035 5185 2365
Wire Wire Line
	5185 2615 5185 2665
Wire Wire Line
	5185 2665 5535 2665
Wire Wire Line
	5585 2565 5535 2565
Wire Wire Line
	5535 2565 5535 2665
Connection ~ 5535 2665
Wire Wire Line
	7605 2365 7605 2465
Wire Wire Line
	7185 2465 7185 2365
Connection ~ 7185 2365
Wire Wire Line
	7185 2665 7185 2715
Wire Wire Line
	7605 2715 7605 2665
Connection ~ 7185 2715
Wire Wire Line
	4735 1240 4735 1340
Connection ~ 4735 1240
Wire Wire Line
	5085 1240 5085 1340
Connection ~ 5085 1240
Connection ~ 7235 1615
Wire Wire Line
	7595 1540 7595 1615
Wire Wire Line
	4435 1240 4735 1240
Connection ~ 5185 2365
Wire Wire Line
	6985 2365 7185 2365
Wire Wire Line
	7065 1240 7065 2035
Wire Wire Line
	7065 2035 5185 2035
Connection ~ 7065 1240
Wire Wire Line
	7595 1615 7235 1615
Wire Wire Line
	7605 2715 7185 2715
Connection ~ 7605 2365
Wire Wire Line
	3620 1240 3620 1575
Connection ~ 3620 1240
Text GLabel 1890 1240 0    39   Input ~ 0
Spannungsaufbereitung
Wire Wire Line
	5485 1540 5485 1690
Wire Wire Line
	5085 1690 4735 1690
Wire Wire Line
	5485 1690 5485 1750
Wire Wire Line
	7235 1240 7595 1240
Wire Wire Line
	7595 1240 8060 1240
Wire Wire Line
	5535 2665 5585 2665
Wire Wire Line
	5535 2665 5535 2915
Wire Wire Line
	7185 2365 7605 2365
Wire Wire Line
	7185 2715 7185 2915
Wire Wire Line
	4735 1240 5085 1240
Wire Wire Line
	5085 1240 5585 1240
Wire Wire Line
	7235 1615 7235 1665
Wire Wire Line
	5185 2365 5185 2415
Wire Wire Line
	7065 1240 7235 1240
Wire Wire Line
	7605 2365 8065 2365
Wire Wire Line
	3620 1240 4135 1240
$EndSCHEMATC
