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
Sheet 25 25
Title "BumperDuino"
Date "2015-08-14"
Rev ""
Comp "Layout & Plan von UweZ"
Comment1 "Übertrag in KIcad von UZ"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L F_Small F1
U 1 1 5629263E
P 2305 1595
F 0 "F1" H 2265 1655 50  0000 L CNN
F 1 "PTC" H 2185 1535 50  0000 L CNN
F 2 "Fuse_Holders_and_Fuses:Fuse_SMD1206_Reflow" H 2305 1595 60  0001 C CNN
F 3 "" H 2305 1595 60  0000 C CNN
	1    2305 1595
	1    0    0    -1  
$EndComp
$Comp
L D D17
U 1 1 5629263F
P 2655 1595
F 0 "D17" H 2655 1695 50  0000 C CNN
F 1 "1N 4004 SMD" H 2655 1495 39  0000 C CNN
F 2 "Diodes_SMD:MELF_Standard" H 2655 1595 60  0001 C CNN
F 3 "" H 2655 1595 60  0000 C CNN
F 4 "Gleichrichterdiode SMD, DO213AB, 400V, 1A" H 2655 1595 60  0001 C CNN "Technische Daten"
F 5 "R: 1N 4004 SMD" H 2655 1595 60  0001 C CNN "Bestellnummer"
F 6 "Melf" H 2655 1595 60  0001 C CNN "Bauform"
F 7 "http://www.reichelt.de/1N-4004-SMD/3/index.html?&ACTION=3&LA=446&ARTICLE=18399&artnr=1N+4004+SMD&SEARCH=1n4004" H 2655 1595 60  0001 C CNN "Bestelllink"
	1    2655 1595
	-1   0    0    -1  
$EndComp
$Comp
L LM2940CS-5.0 U5
U 1 1 56292641
P 4505 1595
F 0 "U5" H 4275 1846 50  0000 L CNN
F 1 "LM2940CS-5.0" H 4332 986 50  0000 L CNN
F 2 "LM2940CS-5.0:TO254P1435X464-4N" H 4505 1595 50  0001 L CNN
F 3 "" H 4505 1595 60  0000 C CNN
	1    4505 1595
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C16
U 1 1 56292642
P 2955 1795
F 0 "C16" H 2965 1865 50  0000 L CNN
F 1 "10uF / 63V" H 2965 1715 28  0000 L CNN
F 2 "Capacitors_SMD:c_elec_6.3x5.8" H 2955 1795 60  0001 C CNN
F 3 "" H 2955 1795 60  0000 C CNN
F 4 "Elektrolytkondensator 10µF • 63V • 105°C +-20%" H 2955 1795 60  0001 C CNN "Technische Daten"
F 5 "R: VF 10/63 K-D" H 2955 1795 60  0001 C CNN "Bestellnummer"
F 6 "SMD D: 6,3mm H:5,8" H 2955 1795 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/Elkos-SMD-Low-ESR-105-C/2/index.html?ACTION=3;ARTICLE=84741;SEARCH=VF%2010/63%20K-D" H 2955 1795 60  0001 C CNN "Bestelllink"
	1    2955 1795
	1    0    0    -1  
$EndComp
$Comp
L C_Small C18
U 1 1 56292643
P 3305 1795
F 0 "C18" H 3315 1865 50  0000 L CNN
F 1 "100nF 10%" H 3315 1715 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3305 1795 60  0001 C CNN
F 3 "" H 3305 1795 60  0000 C CNN
F 4 "Value" H 3305 1795 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 3305 1795 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 3305 1795 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 3305 1795 60  0001 C CNN "Bestelllink"
	1    3305 1795
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C22
U 1 1 5629264D
P 5905 1795
F 0 "C22" H 5915 1865 50  0000 L CNN
F 1 "22uF / 63V" H 5915 1715 28  0000 L CNN
F 2 "Capacitors_SMD:c_elec_8x6.5" H 5905 1795 60  0001 C CNN
F 3 "" H 5905 1795 60  0000 C CNN
F 4 "Elektrolytkondensator 22µF • 63V • 105°C +-20%" H 5905 1795 60  0001 C CNN "Technische Daten"
F 5 "R: VF 22/63 K-E" H 5905 1795 60  0001 C CNN "Bestellnummer"
F 6 "D:8mm  H:6,2mm" H 5905 1795 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/Elkos-SMD-Low-ESR-105-C/2/index.html?ACTION=3;ARTICLE=84746;SEARCH=VF%2022/63%20K-E" H 5905 1795 60  0001 C CNN "Bestelllink"
	1    5905 1795
	1    0    0    -1  
$EndComp
$Comp
L C_Small C20
U 1 1 5629264E
P 5455 1795
F 0 "C20" H 5465 1865 50  0000 L CNN
F 1 "100nF 10%" H 5465 1715 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5455 1795 60  0001 C CNN
F 3 "" H 5455 1795 60  0000 C CNN
F 4 "Value" H 5455 1795 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 5455 1795 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 5455 1795 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 5455 1795 60  0001 C CNN "Bestelllink"
	1    5455 1795
	1    0    0    -1  
$EndComp
$Comp
L LED LED1
U 1 1 56292650
P 6330 2295
F 0 "LED1" H 6330 2395 50  0000 C CNN
F 1 "POWER 5V" H 6330 2195 50  0000 C CNN
F 2 "LEDs:LED-1206" H 6330 2295 60  0001 C CNN
F 3 "" H 6330 2295 60  0000 C CNN
F 4 "ED, SMD 3216 (1206), 285 mcd, grün" H 6330 2295 60  0001 C CNN "Technische Daten"
F 5 "R: LED EL 1206 GR2" H 6330 2295 60  0001 C CNN "Bestellnummer"
F 6 "1206" H 6330 2295 60  0001 C CNN "Bauform"
F 7 "http://www.reichelt.de/SMD-LEDs-Standard/LED-EL-1206-GR2/3/index.html?&ACTION=3&LA=2&ARTICLE=156248&GROUPID=3035&artnr=LED+EL+1206+GR2" H 6330 2295 60  0001 C CNN "Bestelllink"
	1    6330 2295
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R50
U 1 1 56292651
P 6330 1795
F 0 "R50" H 6360 1815 50  0000 L CNN
F 1 "1K" H 6360 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 6330 1795 60  0001 C CNN
F 3 "" H 6330 1795 60  0000 C CNN
	1    6330 1795
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 1595 2205 1595
Wire Wire Line
	2405 1595 2505 1595
Wire Wire Line
	2955 1695 2955 1595
Wire Wire Line
	2805 1595 3805 1595
Wire Wire Line
	3305 1595 3305 1695
Connection ~ 2955 1595
Connection ~ 3305 1595
Wire Wire Line
	3805 1895 3705 1895
Wire Wire Line
	3705 1795 3805 1795
Wire Wire Line
	3305 2595 3305 1895
Connection ~ 3705 1895
Wire Wire Line
	2955 2595 2955 1895
Wire Wire Line
	5205 1595 8375 1595
Wire Wire Line
	5455 1595 5455 1695
Wire Wire Line
	5905 1595 5905 1695
Connection ~ 5455 1595
Wire Wire Line
	6330 2095 6330 1895
Connection ~ 5905 1595
Text HLabel 8375 1595 2    60   Output ~ 0
VCC
Text HLabel 8375 1895 2    60   Output ~ 0
AVCC
Text HLabel 8375 2195 2    60   Input ~ 0
AREF
$Comp
L C_Small C28
U 1 1 562931AF
P 8025 2395
F 0 "C28" H 8035 2465 50  0000 L CNN
F 1 "100nF 10%" H 8035 2315 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8025 2395 60  0001 C CNN
F 3 "" H 8025 2395 60  0000 C CNN
F 4 "Value" H 8025 2395 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 8025 2395 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 8025 2395 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 8025 2395 60  0001 C CNN "Bestelllink"
	1    8025 2395
	1    0    0    -1  
$EndComp
$Comp
L C_Small C25
U 1 1 562931B5
P 7275 2395
F 0 "C25" H 7285 2465 50  0000 L CNN
F 1 "100nF 10%" H 7285 2315 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7275 2395 60  0001 C CNN
F 3 "" H 7275 2395 60  0000 C CNN
F 4 "Value" H 7275 2395 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 7275 2395 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 7275 2395 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 7275 2395 60  0001 C CNN "Bestelllink"
	1    7275 2395
	1    0    0    -1  
$EndComp
$Comp
L L_Small L1
U 1 1 562931C7
P 7025 1895
F 0 "L1" H 7055 1935 50  0000 L CNN
F 1 "10uH" H 7055 1855 50  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" H 7025 1895 60  0001 C CNN
F 3 "" H 7025 1895 60  0000 C CNN
	1    7025 1895
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C26
U 1 1 562931D9
P 7625 1345
F 0 "C26" H 7635 1415 50  0000 L CNN
F 1 "100nF 10%" H 7635 1265 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7625 1345 60  0001 C CNN
F 3 "" H 7625 1345 60  0000 C CNN
F 4 "Value" H 7625 1345 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 7625 1345 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 7625 1345 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 7625 1345 60  0001 C CNN "Bestelllink"
	1    7625 1345
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0186
U 1 1 562931DF
P 7975 1245
F 0 "#PWR0186" H 7975 995 50  0001 C CNN
F 1 "GND" H 7975 1095 50  0000 C CNN
F 2 "" H 7975 1245 60  0000 C CNN
F 3 "" H 7975 1245 60  0000 C CNN
	1    7975 1245
	1    0    0    -1  
$EndComp
Wire Wire Line
	8375 2195 8025 2195
Wire Wire Line
	8025 2195 8025 2295
Wire Wire Line
	8025 2595 8025 2495
Wire Wire Line
	1850 2595 8025 2595
Wire Wire Line
	7675 2595 7675 2495
Wire Wire Line
	7675 1895 7675 2295
Wire Wire Line
	7125 1895 8375 1895
Wire Wire Line
	7275 2295 7275 1895
Connection ~ 7675 1895
Connection ~ 7275 1895
Wire Wire Line
	6725 1895 6925 1895
Connection ~ 7675 2595
Wire Wire Line
	7275 1445 7275 1595
Connection ~ 7275 1595
Wire Wire Line
	7625 1445 7625 1595
Connection ~ 7625 1595
Wire Wire Line
	7275 1245 7275 1145
Wire Wire Line
	7275 1145 7975 1145
Wire Wire Line
	7625 1145 7625 1245
Wire Wire Line
	7975 1145 7975 1245
Connection ~ 7625 1145
Wire Wire Line
	3705 1795 3705 2595
Wire Wire Line
	5905 1895 5905 2595
Wire Wire Line
	6330 1695 6330 1595
Connection ~ 6330 1595
Text HLabel 1850 2595 0    60   Input ~ 0
GND
Wire Wire Line
	7275 2595 7275 2495
Wire Wire Line
	6330 2595 6330 2495
Connection ~ 7275 2595
Connection ~ 6330 2595
Wire Wire Line
	5455 1895 5455 2595
Connection ~ 5905 2595
Connection ~ 5455 2595
Connection ~ 3705 2595
Connection ~ 3305 2595
Text HLabel 1850 1595 0    60   Input ~ 0
VIN
Connection ~ 2955 2595
Wire Wire Line
	6725 1895 6725 1595
Connection ~ 6725 1595
$Comp
L F_Small F2
U 1 1 56300E2B
P 2305 3580
F 0 "F2" H 2265 3640 50  0000 L CNN
F 1 "PTC" H 2185 3520 50  0000 L CNN
F 2 "Fuse_Holders_and_Fuses:Fuse_SMD1206_Reflow" H 2305 3580 60  0001 C CNN
F 3 "" H 2305 3580 60  0000 C CNN
	1    2305 3580
	1    0    0    -1  
$EndComp
$Comp
L LM2940CS-5.0 U6
U 1 1 56300E37
P 4505 3580
F 0 "U6" H 4275 3831 50  0000 L CNN
F 1 "LM2940CS-3.3" H 4332 2971 50  0000 L CNN
F 2 "LM2940CS-5.0:TO254P1435X464-4N" H 4505 3580 50  0001 L CNN
F 3 "" H 4505 3580 60  0000 C CNN
	1    4505 3580
	1    0    0    -1  
$EndComp
$Comp
L C_Small C19
U 1 1 56300E43
P 3305 3780
F 0 "C19" H 3315 3850 50  0000 L CNN
F 1 "100nF 10%" H 3315 3700 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3305 3780 60  0001 C CNN
F 3 "" H 3305 3780 60  0000 C CNN
F 4 "Value" H 3305 3780 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 3305 3780 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 3305 3780 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 3305 3780 60  0001 C CNN "Bestelllink"
	1    3305 3780
	1    0    0    -1  
$EndComp
$Comp
L C_Small C21
U 1 1 56300E4F
P 5455 3780
F 0 "C21" H 5465 3850 50  0000 L CNN
F 1 "100nF 10%" H 5465 3700 28  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5455 3780 60  0001 C CNN
F 3 "" H 5455 3780 60  0000 C CNN
F 4 "Value" H 5455 3780 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G0805 100N" H 5455 3780 60  0001 C CNN "Bestellnummer"
F 6 "0805" H 5455 3780 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G0805-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=31879&artnr=X7R-G0805+100N&SEARCH=kondensator+smd" H 5455 3780 60  0001 C CNN "Bestelllink"
	1    5455 3780
	1    0    0    -1  
$EndComp
$Comp
L R_Small R51
U 1 1 56300E5B
P 6330 3780
F 0 "R51" H 6360 3800 50  0000 L CNN
F 1 "1K" H 6360 3740 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 6330 3780 60  0001 C CNN
F 3 "" H 6330 3780 60  0000 C CNN
	1    6330 3780
	-1   0    0    1   
$EndComp
Wire Wire Line
	2405 3580 2505 3580
Wire Wire Line
	2955 3680 2955 3580
Wire Wire Line
	2805 3580 3805 3580
Wire Wire Line
	3305 3580 3305 3680
Connection ~ 2955 3580
Connection ~ 3305 3580
Wire Wire Line
	3805 3880 3705 3880
Wire Wire Line
	3705 3780 3805 3780
Wire Wire Line
	3305 4580 3305 3880
Connection ~ 3705 3880
Wire Wire Line
	2955 3880 2955 4580
Wire Wire Line
	5205 3580 6550 3580
Wire Wire Line
	5455 3580 5455 3680
Wire Wire Line
	5905 3580 5905 3680
Connection ~ 5455 3580
Wire Wire Line
	6330 4080 6330 3880
Connection ~ 5905 3580
Wire Wire Line
	3705 4580 3705 3780
Wire Wire Line
	5905 4580 5905 3880
Wire Wire Line
	6330 3680 6330 3580
Connection ~ 6330 3580
Wire Wire Line
	6330 4580 6330 4480
Wire Wire Line
	5455 4580 5455 3880
Connection ~ 5905 4580
Connection ~ 5455 4580
Connection ~ 3705 4580
Connection ~ 3305 4580
Connection ~ 2955 4580
Wire Wire Line
	2205 3580 2115 3580
Wire Wire Line
	2115 3580 2115 1595
Connection ~ 2115 1595
Wire Wire Line
	1980 4580 1980 2595
Connection ~ 1980 2595
Text Notes 6375 3795 0    39   ~ 0
Vorwiderstand muss an 3,3V angepasst werden
Wire Wire Line
	1980 4580 6330 4580
Text HLabel 6550 3580 2    60   Output ~ 0
3,3V
Text Notes 4430 1280 0    157  ~ 0
5V
Text Notes 4400 3280 0    157  ~ 0
3,3V
Text Notes 4090 4355 0    39   ~ 0
Gibt es das Bauteil LM2940CS-3.3\noder als Ersatz evl R-78E3.3-0.5
$Comp
L D D18
U 1 1 563D475C
P 2655 3580
F 0 "D18" H 2655 3680 50  0000 C CNN
F 1 "1N 4004 SMD" H 2655 3480 39  0000 C CNN
F 2 "Diodes_SMD:MELF_Standard" H 2655 3580 60  0001 C CNN
F 3 "" H 2655 3580 60  0000 C CNN
F 4 "Gleichrichterdiode SMD, DO213AB, 400V, 1A" H 2655 3580 60  0001 C CNN "Technische Daten"
F 5 "R: 1N 4004 SMD" H 2655 3580 60  0001 C CNN "Bestellnummer"
F 6 "Melf" H 2655 3580 60  0001 C CNN "Bauform"
F 7 "http://www.reichelt.de/1N-4004-SMD/3/index.html?&ACTION=3&LA=446&ARTICLE=18399&artnr=1N+4004+SMD&SEARCH=1n4004" H 2655 3580 60  0001 C CNN "Bestelllink"
	1    2655 3580
	-1   0    0    -1  
$EndComp
$Comp
L LED LED2
U 1 1 563DBF14
P 6330 4280
F 0 "LED2" H 6330 4380 50  0000 C CNN
F 1 "POWER 3,3V" H 6330 4180 50  0000 C CNN
F 2 "LEDs:LED-1206" H 6330 4280 60  0001 C CNN
F 3 "" H 6330 4280 60  0000 C CNN
F 4 "ED, SMD 3216 (1206), 285 mcd, grün" H 6330 4280 60  0001 C CNN "Technische Daten"
F 5 "R: LED EL 1206 GR2" H 6330 4280 60  0001 C CNN "Bestellnummer"
F 6 "1206" H 6330 4280 60  0001 C CNN "Bauform"
F 7 "http://www.reichelt.de/SMD-LEDs-Standard/LED-EL-1206-GR2/3/index.html?&ACTION=3&LA=2&ARTICLE=156248&GROUPID=3035&artnr=LED+EL+1206+GR2" H 6330 4280 60  0001 C CNN "Bestelllink"
	1    6330 4280
	0    -1   -1   0   
$EndComp
$Comp
L CP_Small C23
U 1 1 563ECBA3
P 5905 3780
F 0 "C23" H 5915 3850 50  0000 L CNN
F 1 "22uF / 63V" H 5915 3700 28  0000 L CNN
F 2 "Capacitors_SMD:c_elec_8x6.5" H 5905 3780 60  0001 C CNN
F 3 "" H 5905 3780 60  0000 C CNN
F 4 "Elektrolytkondensator 22µF • 63V • 105°C +-20%" H 5905 3780 60  0001 C CNN "Technische Daten"
F 5 "R: VF 22/63 K-E" H 5905 3780 60  0001 C CNN "Bestellnummer"
F 6 "D:8mm  H:6,2mm" H 5905 3780 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/Elkos-SMD-Low-ESR-105-C/2/index.html?ACTION=3;ARTICLE=84746;SEARCH=VF%2022/63%20K-E" H 5905 3780 60  0001 C CNN "Bestelllink"
	1    5905 3780
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C27
U 1 1 563ED932
P 7675 2395
F 0 "C27" H 7685 2465 50  0000 L CNN
F 1 "10uF / 63V" H 7685 2315 28  0000 L CNN
F 2 "Capacitors_SMD:c_elec_6.3x5.8" H 7675 2395 60  0001 C CNN
F 3 "" H 7675 2395 60  0000 C CNN
F 4 "Elektrolytkondensator 10µF • 63V • 105°C +-20%" H 7675 2395 60  0001 C CNN "Technische Daten"
F 5 "R: VF 10/63 K-D" H 7675 2395 60  0001 C CNN "Bestellnummer"
F 6 "SMD D: 6,3mm H:5,8" H 7675 2395 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/Elkos-SMD-Low-ESR-105-C/2/index.html?ACTION=3;ARTICLE=84741;SEARCH=VF%2010/63%20K-D" H 7675 2395 60  0001 C CNN "Bestelllink"
	1    7675 2395
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C24
U 1 1 563EDCBF
P 7275 1345
F 0 "C24" H 7285 1415 50  0000 L CNN
F 1 "10uF / 63V" H 7285 1265 28  0000 L CNN
F 2 "Capacitors_SMD:c_elec_6.3x5.8" H 7275 1345 60  0001 C CNN
F 3 "" H 7275 1345 60  0000 C CNN
F 4 "Elektrolytkondensator 10µF • 63V • 105°C +-20%" H 7275 1345 60  0001 C CNN "Technische Daten"
F 5 "R: VF 10/63 K-D" H 7275 1345 60  0001 C CNN "Bestellnummer"
F 6 "SMD D: 6,3mm H:5,8" H 7275 1345 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/Elkos-SMD-Low-ESR-105-C/2/index.html?ACTION=3;ARTICLE=84741;SEARCH=VF%2010/63%20K-D" H 7275 1345 60  0001 C CNN "Bestelllink"
	1    7275 1345
	1    0    0    1   
$EndComp
$Comp
L CP_Small C17
U 1 1 563EE38B
P 2955 3780
F 0 "C17" H 2965 3850 50  0000 L CNN
F 1 "10uF / 63V" H 2965 3700 28  0000 L CNN
F 2 "Capacitors_SMD:c_elec_6.3x5.8" H 2955 3780 60  0001 C CNN
F 3 "" H 2955 3780 60  0000 C CNN
F 4 "Elektrolytkondensator 10µF • 63V • 105°C +-20%" H 2955 3780 60  0001 C CNN "Technische Daten"
F 5 "R: VF 10/63 K-D" H 2955 3780 60  0001 C CNN "Bestellnummer"
F 6 "SMD D: 6,3mm H:5,8" H 2955 3780 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/Elkos-SMD-Low-ESR-105-C/2/index.html?ACTION=3;ARTICLE=84741;SEARCH=VF%2010/63%20K-D" H 2955 3780 60  0001 C CNN "Bestelllink"
	1    2955 3780
	1    0    0    -1  
$EndComp
$EndSCHEMATC
