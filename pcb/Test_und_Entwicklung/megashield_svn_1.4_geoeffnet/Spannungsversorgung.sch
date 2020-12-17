EESchema Schematic File Version 4
LIBS:ardumower mega shield svn-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 27 33
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
L ardumower-mega-shield-svn-rescue:DC-DC_Stepdown-RESCUE-ardumower_mega_shield_svn U1
U 1 1 57DF681D
P 2470 1140
F 0 "U1" H 2470 1190 60  0000 C CNN
F 1 "DC 9V" H 2470 890 60  0000 C CNN
F 2 "Zimprich:DC_DC_DSN2596_mit_Bohrloch_doppelte_Lochreihe" H 4270 1040 60  0001 C CNN
F 3 "" H 4270 1040 60  0001 C CNN
F 4 "Value" H 2470 1140 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2470 1140 60  0001 C CNN "Bestelllink"
	1    2470 1140
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P33
U 1 1 57DF683D
P 10135 4410
F 0 "P33" H 10135 4860 50  0000 C CNN
F 1 "5V" V 10235 4410 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 10135 4410 60  0001 C CNN
F 3 "" H 10135 4410 60  0000 C CNN
	1    10135 4410
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P32
U 1 1 57DF683E
P 9635 4410
F 0 "P32" H 9635 4860 50  0000 C CNN
F 1 "GND" V 9735 4410 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 9635 4410 60  0001 C CNN
F 3 "" H 9635 4410 60  0000 C CNN
	1    9635 4410
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P34
U 1 1 57DF683F
P 10595 4400
F 0 "P34" H 10595 4850 50  0000 C CNN
F 1 "3,3V" V 10695 4400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 10595 4400 60  0001 C CNN
F 3 "" H 10595 4400 60  0000 C CNN
	1    10595 4400
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0166
U 1 1 57DF6841
P 9435 4810
F 0 "#PWR0166" H 9435 4810 30  0001 C CNN
F 1 "GND" H 9435 4740 30  0001 C CNN
F 2 "" H 9435 4810 60  0000 C CNN
F 3 "" H 9435 4810 60  0000 C CNN
	1    9435 4810
	1    0    0    -1  
$EndComp
Text Notes 8760 4560 0    39   ~ 0
Abgriff 5V, 3V, GND
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P47
U 1 1 57DF689F
P 10605 5490
F 0 "P47" H 10605 5940 50  0000 C CNN
F 1 "9V" V 10705 5490 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 10605 5490 60  0001 C CNN
F 3 "" H 10605 5490 60  0000 C CNN
	1    10605 5490
	1    0    0    -1  
$EndComp
Text HLabel 1890 1240 0    60   Input ~ 0
Spannungsaufbereitung
$Comp
L ardumower-mega-shield-svn-rescue:+9V-RESCUE-ardumower_mega_shield_svn #PWR0167
U 1 1 57DB0947
P 10440 5975
F 0 "#PWR0167" H 10440 5825 50  0001 C CNN
F 1 "+9V" V 10440 6170 50  0000 C CNN
F 2 "" H 10440 5975 50  0000 C CNN
F 3 "" H 10440 5975 50  0000 C CNN
	1    10440 5975
	0    1    -1   0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:+9V-RESCUE-ardumower_mega_shield_svn #PWR0168
U 1 1 57DB0B58
P 3620 1575
F 0 "#PWR0168" H 3620 1425 50  0001 C CNN
F 1 "+9V" H 3620 1745 50  0000 C CNN
F 2 "" H 3620 1575 50  0000 C CNN
F 3 "" H 3620 1575 50  0000 C CNN
	1    3620 1575
	-1   0    0    1   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:+5V-RESCUE-ardumower_mega_shield_svn #PWR0169
U 1 1 57DC5072
P 10045 4865
F 0 "#PWR0169" H 10045 4715 50  0001 C CNN
F 1 "+5V" V 10045 5065 50  0000 C CNN
F 2 "" H 10045 4865 50  0000 C CNN
F 3 "" H 10045 4865 50  0000 C CNN
	1    10045 4865
	0    1    -1   0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:+3.3V-RESCUE-ardumower_mega_shield_svn #PWR0170
U 1 1 57DC50AC
P 10490 4865
F 0 "#PWR0170" H 10490 4715 50  0001 C CNN
F 1 "+3.3V" V 10490 5100 50  0000 C CNN
F 2 "" H 10490 4865 50  0000 C CNN
F 3 "" H 10490 4865 50  0000 C CNN
	1    10490 4865
	0    1    -1   0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0171
U 1 1 57DD8587
P 2820 990
F 0 "#PWR0171" H 2820 740 50  0001 C CNN
F 1 "GND" H 2825 817 50  0000 C CNN
F 2 "" H 2820 990 50  0000 C CNN
F 3 "" H 2820 990 50  0000 C CNN
	1    2820 990 
	1    0    0    1   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0172
U 1 1 57DD8631
P 2120 990
F 0 "#PWR0172" H 2120 740 50  0001 C CNN
F 1 "GND" H 2125 817 50  0000 C CNN
F 2 "" H 2120 990 50  0000 C CNN
F 3 "" H 2120 990 50  0000 C CNN
	1    2120 990 
	1    0    0    1   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:F_Small-RESCUE-ardumower_mega_shield_svn F1
U 1 1 57E52B64
P 3440 1240
F 0 "F1" H 3400 1300 50  0000 L CNN
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
L ardumower-mega-shield-svn-rescue:D-RESCUE-ardumower_mega_shield_svn D4
U 1 1 57E52B65
P 4285 1240
F 0 "D4" H 4285 1340 50  0000 C CNN
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
L ardumower-mega-shield-svn-rescue:LM2940CS-5.0-RESCUE-ardumower_mega_shield_svn U6
U 1 1 57E52B67
P 6285 1240
F 0 "U6" H 6055 1491 50  0000 L CNN
F 1 "LM2940CS-5.0" H 6112 631 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-3Lead" H 6285 1240 50  0001 L CNN
F 3 "" H 6285 1240 60  0000 C CNN
	1    6285 1240
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CP_Small-RESCUE-ardumower_mega_shield_svn C1
U 1 1 57E52B68
P 4735 1440
F 0 "C1" H 4745 1510 50  0000 L CNN
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
L ardumower-mega-shield-svn-rescue:C_Small-RESCUE-ardumower_mega_shield_svn C4
U 1 1 57E52B69
P 5085 1440
F 0 "C4" H 5095 1510 50  0000 L CNN
F 1 "100nF" H 5095 1360 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5085 1440 60  0001 C CNN
F 3 "" H 5085 1440 60  0000 C CNN
	1    5085 1440
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0173
U 1 1 57E52B70
P 7185 2915
F 0 "#PWR0173" H 7185 2665 50  0001 C CNN
F 1 "GND" H 7185 2765 50  0000 C CNN
F 2 "" H 7185 2915 60  0000 C CNN
F 3 "" H 7185 2915 60  0000 C CNN
	1    7185 2915
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CP_Small-RESCUE-ardumower_mega_shield_svn C8
U 1 1 57E52B71
P 7595 1440
F 0 "C8" H 7605 1510 50  0000 L CNN
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
L ardumower-mega-shield-svn-rescue:C_Small-RESCUE-ardumower_mega_shield_svn C7
U 1 1 57E52B72
P 7235 1440
F 0 "C7" H 7245 1510 50  0000 L CNN
F 1 "100nF" H 7245 1360 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7235 1440 60  0001 C CNN
F 3 "" H 7235 1440 60  0000 C CNN
	1    7235 1440
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0174
U 1 1 57E52B73
P 7235 1665
F 0 "#PWR0174" H 7235 1415 50  0001 C CNN
F 1 "GND" H 7235 1515 50  0000 C CNN
F 2 "" H 7235 1665 60  0000 C CNN
F 3 "" H 7235 1665 60  0000 C CNN
	1    7235 1665
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:LM2940CS-5.0-RESCUE-ardumower_mega_shield_svn U7
U 1 1 57E52BA6
P 6285 2365
F 0 "U7" H 6055 2616 50  0000 L CNN
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
L ardumower-mega-shield-svn-rescue:C_Small-RESCUE-ardumower_mega_shield_svn C5
U 1 1 57E52BA7
P 5185 2515
F 0 "C5" H 5195 2585 50  0000 L CNN
F 1 "100nF" H 5195 2435 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5185 2515 60  0001 C CNN
F 3 "" H 5185 2515 60  0000 C CNN
	1    5185 2515
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:C_Small-RESCUE-ardumower_mega_shield_svn C6
U 1 1 57E52BA8
P 7185 2565
F 0 "C6" H 7195 2635 50  0000 L CNN
F 1 "100nF" H 7195 2485 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7185 2565 60  0001 C CNN
F 3 "" H 7185 2565 60  0000 C CNN
	1    7185 2565
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0175
U 1 1 57E52BA9
P 5535 2915
F 0 "#PWR0175" H 5535 2665 50  0001 C CNN
F 1 "GND" H 5535 2765 50  0000 C CNN
F 2 "" H 5535 2915 60  0000 C CNN
F 3 "" H 5535 2915 60  0000 C CNN
	1    5535 2915
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0176
U 1 1 57E52BBF
P 5485 1750
F 0 "#PWR0176" H 5485 1500 50  0001 C CNN
F 1 "GND" H 5485 1600 50  0000 C CNN
F 2 "" H 5485 1750 60  0000 C CNN
F 3 "" H 5485 1750 60  0000 C CNN
	1    5485 1750
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CP_Small-RESCUE-ardumower_mega_shield_svn C13
U 1 1 57E52BC0
P 7605 2565
F 0 "C13" H 7615 2635 50  0000 L CNN
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
L ardumower-mega-shield-svn-rescue:Jumper_NC_Small-RESCUE-ardumower_mega_shield_svn JP1
U 1 1 57E5D727
P 3100 1240
F 0 "JP1" H 3100 1452 50  0000 C CNN
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
L ardumower-mega-shield-svn-rescue:+5VP-RESCUE-ardumower_mega_shield_svn #PWR0177
U 1 1 57E9669C
P 8060 1240
F 0 "#PWR0177" H 8060 1090 50  0001 C CNN
F 1 "+5VP" V 8060 1460 50  0000 C CNN
F 2 "" H 8060 1240 50  0000 C CNN
F 3 "" H 8060 1240 50  0000 C CNN
	1    8060 1240
	0    1    -1   0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:+3.3VP-RESCUE-ardumower_mega_shield_svn #PWR0178
U 1 1 57E966D4
P 8065 2365
F 0 "#PWR0178" H 8215 2315 50  0001 C CNN
F 1 "+3.3VP" V 8065 2615 50  0000 C CNN
F 2 "" H 8065 2365 50  0000 C CNN
F 3 "" H 8065 2365 50  0000 C CNN
	1    8065 2365
	0    1    -1   0   
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P38
U 1 1 57EFA6BF
P 9645 1365
F 0 "P38" H 9722 1406 50  0000 L CNN
F 1 "+5VP" H 9722 1315 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 9645 1365 50  0001 C CNN
F 3 "" H 9645 1365 50  0000 C CNN
	1    9645 1365
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P24
U 1 1 57EFB361
P 9095 2685
F 0 "P24" H 9172 2726 50  0000 L CNN
F 1 "+3.3VP" H 9172 2635 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 9095 2685 50  0001 C CNN
F 3 "" H 9095 2685 50  0000 C CNN
	1    9095 2685
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P45
U 1 1 57EFCC69
P 10155 5485
F 0 "P45" H 10155 5935 50  0000 C CNN
F 1 "GND" V 10255 5485 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 10155 5485 60  0001 C CNN
F 3 "" H 10155 5485 60  0000 C CNN
	1    10155 5485
	1    0    0    -1  
$EndComp
$Comp
L ardumower-mega-shield-svn-rescue:GND-RESCUE-ardumower_mega_shield_svn #PWR0179
U 1 1 57EFCC6F
P 9955 5885
F 0 "#PWR0179" H 9955 5885 30  0001 C CNN
F 1 "GND" H 9955 5815 30  0001 C CNN
F 2 "" H 9955 5885 60  0000 C CNN
F 3 "" H 9955 5885 60  0000 C CNN
	1    9955 5885
	1    0    0    -1  
$EndComp
Text Notes -1265 -1415 0    79   ~ 0
[00:10:17] Jürgen Lange: dahinter sitzen die regler 5v und an dem hängt der regler 3,3v so alles was du an externen versorgungen hast die immer gleich bleiben egal ob 5 oder 3,3v kommen da her. alles was mal mit 3,3 oder 5v laufen muss kommt vom ioref\n[00:11:04] Kurzschuss - Uwe: okay das ist eine klare ansage\n[00:11:24] Jürgen Lange: Beispiel: die pca selber kommen von ioref die module dahinter sind festgelegt wie uhr etc die kommen vom längsregler\n[00:12:15] Kurzschuss - Uwe: die Jumper für die widerstände dann beim I2C bus dann auch von den Längsreglern\n[00:13:01] Jürgen Lange: wichtig ist nur das alles von einem dcdc wandler versorgt wird arduino und die module damit diese immer gemeinsam abgeschaltet werden\n[00:14:09] Kurzschuss - Uwe: müsste so eigentlich stimmen\n[00:14:20] Jürgen Lange: die pullups da kommt es darauf an auf welecher seite die sitzen wenn die zwei die auf der mega/due seite sitzen kommen über ioref der rest von der versorgung des jeweiligen moduls
Text Notes -1215 -680 0    79   ~ 0
im plan spannungsversorgung c2 bitte nach der ptc Sicherung f1. \nich würde an dieser stlle auch keine ptc sondern eine Schmelzsicherung\nempfehlen die den DCDC komplett rausnimmt wenn es zu heftig wird\nda ist ptc ungeeignet wenn du willst kannst du die ptc in den 3,3v und 5,V zweig machen
Text GLabel 9270 5960 0    39   Input ~ 0
9Vgeschaltet
$Comp
L ardumower-mega-shield-svn-rescue:CONN_01X08-RESCUE-ardumower_mega_shield_svn P29
U 1 1 58ACC03E
P 9630 5485
F 0 "P29" H 9630 5935 50  0000 C CNN
F 1 "9V S." V 9730 5485 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 9630 5485 60  0001 C CNN
F 3 "" H 9630 5485 60  0000 C CNN
F 4 "Value" H 9630 5485 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9630 5485 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9630 5485 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9630 5485 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9630 5485 60  0001 C CNN "Bauform"
F 9 "Value" H 9630 5485 60  0001 C CNN "Funktion"
F 10 "Value" H 9630 5485 60  0001 C CNN "Hersteller"
F 11 "Value" H 9630 5485 60  0001 C CNN "Hersteller Bestellnummer"
	1    9630 5485
	1    0    0    -1  
$EndComp
Wire Wire Line
	2120 990  2120 1040
Wire Wire Line
	3200 1240 3340 1240
Wire Wire Line
	9435 4060 9435 4810
Connection ~ 9435 4160
Connection ~ 9435 4260
Connection ~ 9435 4360
Connection ~ 9435 4460
Connection ~ 9435 4560
Connection ~ 9435 4660
Wire Wire Line
	9935 4060 9935 4865
Connection ~ 9935 4160
Connection ~ 9935 4260
Connection ~ 9935 4360
Connection ~ 9935 4460
Connection ~ 9935 4560
Connection ~ 9935 4660
Wire Wire Line
	10395 4050 10395 4865
Connection ~ 10395 4150
Connection ~ 10395 4250
Connection ~ 10395 4350
Connection ~ 10395 4450
Connection ~ 10395 4550
Connection ~ 10395 4650
Connection ~ 9935 4760
Connection ~ 10395 4750
Connection ~ 9435 4760
Wire Wire Line
	10395 4865 10490 4865
Wire Wire Line
	10405 5140 10405 5975
Connection ~ 10405 5240
Connection ~ 10405 5340
Connection ~ 10405 5440
Connection ~ 10405 5540
Connection ~ 10405 5640
Connection ~ 10405 5740
Connection ~ 10405 5840
Wire Wire Line
	10405 5975 10440 5975
Wire Wire Line
	9935 4865 10045 4865
Wire Wire Line
	2820 1240 3000 1240
Wire Wire Line
	1890 1240 2120 1240
Wire Wire Line
	2820 990  2820 1040
Wire Wire Line
	3540 1240 4135 1240
Wire Wire Line
	5585 1540 5485 1540
Wire Wire Line
	5485 1440 5585 1440
Wire Wire Line
	5485 1690 4735 1690
Wire Wire Line
	5085 1690 5085 1540
Connection ~ 5485 1540
Wire Wire Line
	4735 1690 4735 1540
Connection ~ 5085 1690
Connection ~ 5485 1690
Wire Wire Line
	6985 1240 8060 1240
Wire Wire Line
	7235 1240 7235 1340
Wire Wire Line
	7595 1240 7595 1340
Connection ~ 7235 1240
Wire Wire Line
	7235 1540 7235 1665
Connection ~ 7595 1240
Wire Wire Line
	5485 1440 5485 1750
Wire Wire Line
	5185 2365 5585 2365
Wire Wire Line
	5185 2035 5185 2415
Wire Wire Line
	5185 2615 5185 2665
Wire Wire Line
	5185 2665 5585 2665
Wire Wire Line
	5585 2565 5535 2565
Wire Wire Line
	5535 2565 5535 2915
Connection ~ 5535 2665
Wire Wire Line
	7605 2365 7605 2465
Wire Wire Line
	7185 2465 7185 2365
Connection ~ 7185 2365
Wire Wire Line
	7185 2665 7185 2915
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
	4435 1240 5585 1240
Connection ~ 5185 2365
Wire Wire Line
	6985 2365 8065 2365
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
Wire Wire Line
	9345 1715 9445 1715
Wire Wire Line
	9345 1015 9345 1715
Wire Wire Line
	8010 1015 9445 1015
Wire Wire Line
	9445 1115 9345 1115
Connection ~ 9345 1115
Wire Wire Line
	9445 1215 9345 1215
Connection ~ 9345 1215
Wire Wire Line
	9445 1315 9345 1315
Connection ~ 9345 1315
Wire Wire Line
	9345 1415 9445 1415
Connection ~ 9345 1415
Wire Wire Line
	9445 1515 9345 1515
Connection ~ 9345 1515
Wire Wire Line
	9445 1615 9345 1615
Connection ~ 9345 1615
Wire Wire Line
	8795 3035 8895 3035
Wire Wire Line
	8795 2225 8795 3035
Wire Wire Line
	8795 2335 8895 2335
Wire Wire Line
	8895 2435 8795 2435
Connection ~ 8795 2435
Wire Wire Line
	8895 2535 8795 2535
Connection ~ 8795 2535
Wire Wire Line
	8895 2635 8795 2635
Connection ~ 8795 2635
Wire Wire Line
	8795 2735 8895 2735
Connection ~ 8795 2735
Wire Wire Line
	8895 2835 8795 2835
Connection ~ 8795 2835
Wire Wire Line
	8895 2935 8795 2935
Connection ~ 8795 2935
Wire Wire Line
	8010 1240 8010 1015
Connection ~ 9345 1015
Connection ~ 8010 1240
Wire Wire Line
	8025 2365 8025 2225
Wire Wire Line
	8025 2225 8795 2225
Connection ~ 8795 2335
Connection ~ 8025 2365
Wire Wire Line
	9955 5135 9955 5885
Connection ~ 9955 5235
Connection ~ 9955 5335
Connection ~ 9955 5435
Connection ~ 9955 5535
Connection ~ 9955 5635
Connection ~ 9955 5735
Connection ~ 9955 5835
Wire Wire Line
	9430 5135 9430 5960
Connection ~ 9430 5235
Connection ~ 9430 5335
Connection ~ 9430 5435
Connection ~ 9430 5535
Connection ~ 9430 5635
Connection ~ 9430 5735
Connection ~ 9430 5835
Wire Wire Line
	9430 5960 9270 5960
Connection ~ 3620 1240
$EndSCHEMATC
