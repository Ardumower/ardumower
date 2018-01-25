EESchema Schematic File Version 4
LIBS:sender_v3.0_geoeffnet-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
Title "Ardumower shield SVN Version"
Date "2017-04-13"
Rev "1.3"
Comp "ML AG JL UZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 5360 4990 2    39   Input ~ 0
TX2
Text GLabel 4180 6060 2    39   Input ~ 0
RX2
$Comp
L power:GND #PWR?
U 1 1 5A09FF01
P 2185 1945
F 0 "#PWR?" H 2185 1695 50  0001 C CNN
F 1 "GND" V 2185 1745 50  0000 C CNN
F 2 "" H 2185 1945 50  0000 C CNN
F 3 "" H 2185 1945 50  0000 C CNN
	1    2185 1945
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09FF02
P 3070 1795
F 0 "#PWR?" H 3070 1545 50  0001 C CNN
F 1 "GND" V 3070 1595 50  0000 C CNN
F 2 "" H 3070 1795 50  0000 C CNN
F 3 "" H 3070 1795 50  0000 C CNN
	1    3070 1795
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09FF03
P 2695 5470
F 0 "#PWR?" H 2695 5220 50  0001 C CNN
F 1 "GND" V 2695 5270 50  0000 C CNN
F 2 "" H 2695 5470 50  0000 C CNN
F 3 "" H 2695 5470 50  0000 C CNN
	1    2695 5470
	0    -1   -1   0   
$EndComp
Text GLabel 2085 2045 2    39   Output ~ 0
Led-Wlan
Text GLabel 2915 5070 2    39   Output ~ 0
Led-BT
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Wlan_ESP8266_mit_Beschriftung-RESCUE-sender_v3.0_neu_geoeffnet U?
U 1 1 5A09FF04
P 1565 1895
F 0 "U?" H 1843 1941 50  0000 L CNN
F 1 "Wlan_ESP8266" H 1843 1850 50  0000 L CNN
F 2 "Zimprich:Wlan_ESP8266_3D_mit_Pin_Beschreibung_ohne_Rahmen" H 1565 1895 50  0001 C CNN
F 3 "DOCUMENTATION" H 1565 1895 50  0001 C CNN
F 4 "Value" H 1843 1910 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 1843 1804 60  0001 L CNN "Bestelllink"
F 6 "Value" H 1843 1698 60  0001 L CNN "Technische Daten"
F 7 "Value" H 1565 1895 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1565 1895 60  0001 C CNN "Bauform"
F 9 "Value" H 1565 1895 60  0001 C CNN "Funktion"
F 10 "Value" H 1565 1895 60  0001 C CNN "Hersteller"
F 11 "Value" H 1565 1895 60  0001 C CNN "Hersteller Bestellnummer"
	1    1565 1895
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Bluetooth_CZ_HC_05_mit_Beschriftung-RESCUE-sender_v3.0_neu_geoeffnet U?
U 1 1 5A09FF05
P 2170 5320
F 0 "U?" H 2448 5366 50  0000 L CNN
F 1 "Bluetooth_CZ_HC_05" H 2448 5275 50  0000 L CNN
F 2 "Zimprich:Bluetooth_Buchse_Platz_mit_Beschriftung_4_fach" H 2170 5320 50  0001 C CNN
F 3 "DOCUMENTATION" H 2170 5320 50  0001 C CNN
F 4 "Value" H 2448 5335 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 2448 5229 60  0001 L CNN "Bestelllink"
F 6 "Value" H 2448 5123 60  0001 L CNN "Technische Daten"
F 7 "Value" H 2170 5320 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2170 5320 60  0001 C CNN "Bauform"
	1    2170 5320
	-1   0    0    -1  
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5A09FF07
P 2965 6750
F 0 "#PWR?" H 2965 6600 50  0001 C CNN
F 1 "+5VP" H 2965 6910 50  0000 C CNN
F 2 "" H 2965 6750 50  0000 C CNN
F 3 "" H 2965 6750 50  0000 C CNN
	1    2965 6750
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 5A09FF08
P 3465 6725
F 0 "#PWR?" H 3615 6675 50  0001 C CNN
F 1 "+3.3VP" H 3335 6855 50  0000 L CNN
F 2 "" H 3465 6725 50  0000 C CNN
F 3 "" H 3465 6725 50  0000 C CNN
	1    3465 6725
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 5A09FF09
P 2820 5170
F 0 "#PWR?" H 2970 5120 50  0001 C CNN
F 1 "+3.3VP" V 2820 5245 50  0000 L CNN
F 2 "" H 2820 5170 50  0000 C CNN
F 3 "" H 2820 5170 50  0000 C CNN
	1    2820 5170
	0    1    -1   0   
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Small-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A09FF0A
P 2695 5170
F 0 "JP?" H 2695 5240 39  0000 C CNN
F 1 "Key" H 2695 5120 39  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2695 5821 50  0001 C CNN
F 3 "" H 2695 5170 50  0001 C CNN
F 4 "Value" H 2695 5722 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2695 5616 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2695 5510 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2695 5404 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2695 5298 60  0001 C CNN "Bauform"
	1    2695 5170
	1    0    0    -1  
$EndComp
Text GLabel 4290 1610 2    39   Input ~ 0
RX1
Text GLabel 5735 1960 2    39   Input ~ 0
TX1
$Comp
L power:+5VP #PWR?
U 1 1 5A09FF0C
P 2965 2735
F 0 "#PWR?" H 2965 2585 50  0001 C CNN
F 1 "+5VP" H 2965 2895 50  0000 C CNN
F 2 "" H 2965 2735 50  0000 C CNN
F 3 "" H 2965 2735 50  0000 C CNN
	1    2965 2735
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 5A09FF0D
P 3465 2710
F 0 "#PWR?" H 3615 2660 50  0001 C CNN
F 1 "+3.3VP" H 3335 2840 50  0000 L CNN
F 2 "" H 3465 2710 50  0000 C CNN
F 3 "" H 3465 2710 50  0000 C CNN
	1    3465 2710
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF0E
P 4830 2495
F 0 "R?" H 4918 2541 50  0000 L CNN
F 1 "10K" H 4918 2450 50  0000 L CNN
F 2 "Zimprich:R_0603" V 4760 2495 50  0001 C CNN
F 3 "Value" H 4830 2495 50  0001 C CNN
F 4 "Value" H 4918 2616 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4918 2510 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4918 2404 60  0001 L CNN "Technische Daten"
F 7 "Value" H 4918 2298 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4918 2192 60  0001 L CNN "Bauform"
	1    4830 2495
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF0F
P 5370 1960
F 0 "R?" V 5290 1880 50  0000 L CNN
F 1 "4K7" V 5370 1890 50  0000 L CNN
F 2 "Zimprich:R_0603" V 5300 1960 50  0001 C CNN
F 3 "Value" H 5370 1960 50  0001 C CNN
F 4 "Value" H 5458 2081 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 5458 1975 60  0001 L CNN "Bestelllink"
F 6 "Value" H 5458 1869 60  0001 L CNN "Technische Daten"
F 7 "Value" H 5458 1763 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 5458 1657 60  0001 L CNN "Bauform"
	1    5370 1960
	0    -1   1    0   
$EndComp
Text GLabel 4000 980  0    39   Input ~ 0
IOREF
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Small-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A09FF10
P 2090 2145
F 0 "JP?" H 2200 2095 39  0000 C CNN
F 1 "Key" H 2090 2095 39  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2090 2796 50  0001 C CNN
F 3 "" H 2090 2145 50  0001 C CNN
F 4 "Value" H 2090 2697 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2090 2591 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2090 2485 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2090 2379 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2090 2273 60  0001 C CNN "Bauform"
	1    2090 2145
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09FF11
P 2230 2145
F 0 "#PWR?" H 2230 1895 50  0001 C CNN
F 1 "GND" V 2230 1945 50  0000 C CNN
F 2 "" H 2230 2145 50  0000 C CNN
F 3 "" H 2230 2145 50  0000 C CNN
	1    2230 2145
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3465 6725 3465 6795
Wire Wire Line
	2965 6750 2965 6795
Wire Wire Line
	2085 2045 1965 2045
Wire Wire Line
	1965 1645 2505 1645
Wire Wire Line
	2590 1995 3130 1995
Wire Wire Line
	2585 1895 3130 1895
Wire Wire Line
	2505 1845 1965 1845
Wire Wire Line
	3130 1795 3070 1795
Wire Wire Line
	2505 1695 3130 1695
Wire Wire Line
	2570 5070 2915 5070
Wire Wire Line
	2570 5170 2595 5170
Connection ~ 2585 1545
Wire Wire Line
	1965 1945 2185 1945
Wire Wire Line
	2795 5170 2820 5170
Wire Wire Line
	2695 5470 2570 5470
Connection ~ 2590 2245
Wire Wire Line
	1965 2245 2590 2245
Wire Wire Line
	2570 5570 2685 5570
Wire Wire Line
	3465 2710 3465 2780
Wire Wire Line
	2965 2735 2965 2780
Wire Wire Line
	2505 2435 3215 2435
Wire Wire Line
	2585 1370 2585 1545
Connection ~ 2505 1845
Wire Wire Line
	2590 2245 2590 1995
Wire Wire Line
	1965 2145 1990 2145
Wire Wire Line
	2190 2145 2230 2145
Text GLabel 3010 2095 0    39   Output ~ 0
Led-Wlan
Wire Wire Line
	3010 2095 3130 2095
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Small-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A09FF18
P 2090 1745
F 0 "JP?" H 2265 1695 39  0000 C CNN
F 1 "WlanRst" H 2090 1695 39  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2090 2396 50  0001 C CNN
F 3 "" H 2090 1745 50  0001 C CNN
F 4 "Value" H 2090 2297 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2090 2191 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2090 2085 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2090 1979 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2090 1873 60  0001 C CNN "Bauform"
	1    2090 1745
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09FF19
P 2230 1745
F 0 "#PWR?" H 2230 1495 50  0001 C CNN
F 1 "GND" V 2230 1545 50  0000 C CNN
F 2 "" H 2230 1745 50  0000 C CNN
F 3 "" H 2230 1745 50  0000 C CNN
	1    2230 1745
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1965 1745 1990 1745
Wire Wire Line
	2190 1745 2230 1745
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A09FF1A
P 2505 2690
F 0 "C?" H 2597 2736 50  0000 L CNN
F 1 "100nF" H 2597 2645 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 2505 2690 50  0001 C CNN
F 3 "" H 2505 2690 50  0000 C CNN
	1    2505 2690
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09FF1B
P 2505 2895
F 0 "#PWR?" H 2505 2645 50  0001 C CNN
F 1 "GND" H 2510 2722 50  0000 C CNN
F 2 "" H 2505 2895 50  0000 C CNN
F 3 "" H 2505 2895 50  0000 C CNN
	1    2505 2895
	1    0    0    -1  
$EndComp
Wire Wire Line
	2505 2895 2505 2790
Connection ~ 2505 2435
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A09FF1C
P 2685 5830
F 0 "C?" H 2777 5876 50  0000 L CNN
F 1 "100nF" H 2777 5785 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 2685 5830 50  0001 C CNN
F 3 "" H 2685 5830 50  0000 C CNN
	1    2685 5830
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A09FF1D
P 2685 6035
F 0 "#PWR?" H 2685 5785 50  0001 C CNN
F 1 "GND" H 2690 5862 50  0000 C CNN
F 2 "" H 2685 6035 50  0000 C CNN
F 3 "" H 2685 6035 50  0000 C CNN
	1    2685 6035
	1    0    0    -1  
$EndComp
Wire Wire Line
	2685 6035 2685 5930
Wire Wire Line
	2685 5730 2685 5570
Connection ~ 2685 5570
$Comp
L Transistor:BC849 Q?
U 1 1 5A09FF20
P 4930 1960
F 0 "Q?" H 5121 2006 50  0000 L CNN
F 1 "BC847B" H 5121 1915 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H -850 -805 50  0001 L CIN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/BC846-848-CDIL.pdf" H -1050 -730 50  0001 L CNN
F 4 "SOT-23" H 4930 1960 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BC-Transistoren/BC-847A-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18561&GROUPID=7206&artnr=BC+847A+SMD&SEARCH=bc847" H 4930 1960 60  0001 C CNN "Bestelllink"
F 6 "Transistor SMD NPN SOT-23 45V 0,1A 0,25W" H 4930 1960 60  0001 C CNN "Technische Daten"
F 7 "R: BC 847A SMD" H 4930 1960 60  0001 C CNN "Bestellnummer"
F 8 "SOT-23" H 4930 1960 60  0001 C CNN "Bauform"
F 9 "Value" H 4930 1960 60  0001 C CNN "Funktion"
F 10 "Value" H 4930 1960 60  0001 C CNN "Hersteller"
F 11 "Value" H 4930 1960 60  0001 C CNN "Hersteller Bestellnummer"
	1    4930 1960
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4830 2160 4830 2245
$Comp
L power:GND #PWR?
U 1 1 5A09FF21
P 4830 2725
F 0 "#PWR?" H 4830 2475 50  0001 C CNN
F 1 "GND" H 4835 2552 50  0000 C CNN
F 2 "" H 4830 2725 50  0000 C CNN
F 3 "" H 4830 2725 50  0000 C CNN
	1    4830 2725
	-1   0    0    -1  
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5A09FF23
P 5080 1375
F 0 "#PWR?" H 5080 1225 50  0001 C CNN
F 1 "+5VP" H 5080 1535 50  0000 C CNN
F 2 "" H 5080 1375 50  0000 C CNN
F 3 "" H 5080 1375 50  0000 C CNN
	1    5080 1375
	1    0    0    1   
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 5A09FF24
P 4580 1400
F 0 "#PWR?" H 4730 1350 50  0001 C CNN
F 1 "+3.3VP" H 4450 1530 50  0000 L CNN
F 2 "" H 4580 1400 50  0000 C CNN
F 3 "" H 4580 1400 50  0000 C CNN
	1    4580 1400
	1    0    0    1   
$EndComp
Wire Wire Line
	4580 1400 4580 1330
Wire Wire Line
	5080 1375 5080 1330
Wire Wire Line
	4830 1760 4830 1430
Wire Wire Line
	5130 1960 5220 1960
Wire Wire Line
	4830 2725 4830 2645
Wire Wire Line
	3215 2435 3215 2680
Connection ~ 2505 1695
Wire Wire Line
	2505 1645 2505 1695
Wire Wire Line
	5520 1960 5735 1960
Connection ~ 4830 2245
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF25
P 4060 1810
F 0 "R?" H 4148 1856 50  0000 L CNN
F 1 "10K" H 4148 1765 50  0000 L CNN
F 2 "Zimprich:R_0603" V 3990 1810 50  0001 C CNN
F 3 "Value" H 4060 1810 50  0001 C CNN
F 4 "Value" H 4148 1931 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4148 1825 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4148 1719 60  0001 L CNN "Technische Daten"
F 7 "Value" H 4148 1613 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4148 1507 60  0001 L CNN "Bauform"
	1    4060 1810
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF26
P 3520 1370
F 0 "R?" V 3440 1290 50  0000 L CNN
F 1 "4K7" V 3520 1300 50  0000 L CNN
F 2 "Zimprich:R_0603" V 3450 1370 50  0001 C CNN
F 3 "Value" H 3520 1370 50  0001 C CNN
F 4 "Value" H 3608 1491 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 3608 1385 60  0001 L CNN "Bestelllink"
F 6 "Value" H 3608 1279 60  0001 L CNN "Technische Daten"
F 7 "Value" H 3608 1173 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 3608 1067 60  0001 L CNN "Bauform"
	1    3520 1370
	0    1    1    0   
$EndComp
$Comp
L Transistor:BC849 Q?
U 1 1 5A09FF27
P 3960 1370
F 0 "Q?" H 4151 1416 50  0000 L CNN
F 1 "BC847B" H 4151 1325 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H -1820 -1395 50  0001 L CIN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/BC846-848-CDIL.pdf" H -2020 -1320 50  0001 L CNN
F 4 "SOT-23" H 3960 1370 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BC-Transistoren/BC-847A-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18561&GROUPID=7206&artnr=BC+847A+SMD&SEARCH=bc847" H 3960 1370 60  0001 C CNN "Bestelllink"
F 6 "Transistor SMD NPN SOT-23 45V 0,1A 0,25W" H 3960 1370 60  0001 C CNN "Technische Daten"
F 7 "R: BC 847A SMD" H 3960 1370 60  0001 C CNN "Bestellnummer"
F 8 "SOT-23" H 3960 1370 60  0001 C CNN "Bauform"
F 9 "Value" H 3960 1370 60  0001 C CNN "Funktion"
F 10 "Value" H 3960 1370 60  0001 C CNN "Hersteller"
F 11 "Value" H 3960 1370 60  0001 C CNN "Hersteller Bestellnummer"
	1    3960 1370
	1    0    0    -1  
$EndComp
Wire Wire Line
	4060 1570 4060 1610
$Comp
L power:GND #PWR?
U 1 1 5A09FF28
P 4060 2000
F 0 "#PWR?" H 4060 1750 50  0001 C CNN
F 1 "GND" H 4065 1827 50  0000 C CNN
F 2 "" H 4060 2000 50  0000 C CNN
F 3 "" H 4060 2000 50  0000 C CNN
	1    4060 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3760 1370 3670 1370
Wire Wire Line
	4060 2000 4060 1960
Connection ~ 4060 1610
Wire Wire Line
	4290 1610 4060 1610
Wire Wire Line
	4060 1170 4060 980 
Wire Wire Line
	4060 980  4000 980 
Wire Wire Line
	2585 1370 3370 1370
Wire Wire Line
	1965 1545 2585 1545
Wire Wire Line
	3220 5570 3215 6695
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF29
P 4455 5525
F 0 "R?" H 4543 5571 50  0000 L CNN
F 1 "10K" H 4543 5480 50  0000 L CNN
F 2 "Zimprich:R_0603" V 4385 5525 50  0001 C CNN
F 3 "Value" H 4455 5525 50  0001 C CNN
F 4 "Value" H 4543 5646 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4543 5540 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4543 5434 60  0001 L CNN "Technische Daten"
F 7 "Value" H 4543 5328 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4543 5222 60  0001 L CNN "Bauform"
	1    4455 5525
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF2A
P 4995 4990
F 0 "R?" V 4915 4910 50  0000 L CNN
F 1 "4K7" V 4995 4920 50  0000 L CNN
F 2 "Zimprich:R_0603" V 4925 4990 50  0001 C CNN
F 3 "Value" H 4995 4990 50  0001 C CNN
F 4 "Value" H 5083 5111 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 5083 5005 60  0001 L CNN "Bestelllink"
F 6 "Value" H 5083 4899 60  0001 L CNN "Technische Daten"
F 7 "Value" H 5083 4793 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 5083 4687 60  0001 L CNN "Bauform"
	1    4995 4990
	0    -1   1    0   
$EndComp
Text GLabel 3890 5580 0    39   Input ~ 0
IOREF
$Comp
L Transistor:BC849 Q?
U 1 1 5A09FF2B
P 4555 4990
F 0 "Q?" H 4746 5036 50  0000 L CNN
F 1 "BC847B" H 4746 4945 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H -1225 2225 50  0001 L CIN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/BC846-848-CDIL.pdf" H -1425 2300 50  0001 L CNN
F 4 "SOT-23" H 4555 4990 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BC-Transistoren/BC-847A-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18561&GROUPID=7206&artnr=BC+847A+SMD&SEARCH=bc847" H 4555 4990 60  0001 C CNN "Bestelllink"
F 6 "Transistor SMD NPN SOT-23 45V 0,1A 0,25W" H 4555 4990 60  0001 C CNN "Technische Daten"
F 7 "R: BC 847A SMD" H 4555 4990 60  0001 C CNN "Bestellnummer"
F 8 "SOT-23" H 4555 4990 60  0001 C CNN "Bauform"
F 9 "Value" H 4555 4990 60  0001 C CNN "Funktion"
F 10 "Value" H 4555 4990 60  0001 C CNN "Hersteller"
F 11 "Value" H 4555 4990 60  0001 C CNN "Hersteller Bestellnummer"
	1    4555 4990
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4455 5190 4455 5270
$Comp
L power:GND #PWR?
U 1 1 5A09FF2C
P 4455 5755
F 0 "#PWR?" H 4455 5505 50  0001 C CNN
F 1 "GND" H 4460 5582 50  0000 C CNN
F 2 "" H 4455 5755 50  0000 C CNN
F 3 "" H 4455 5755 50  0000 C CNN
	1    4455 5755
	-1   0    0    -1  
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5A09FF2E
P 4705 4405
F 0 "#PWR?" H 4705 4255 50  0001 C CNN
F 1 "+5VP" H 4705 4565 50  0000 C CNN
F 2 "" H 4705 4405 50  0000 C CNN
F 3 "" H 4705 4405 50  0000 C CNN
	1    4705 4405
	1    0    0    1   
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 5A09FF2F
P 4205 4430
F 0 "#PWR?" H 4355 4380 50  0001 C CNN
F 1 "+3.3VP" H 4075 4560 50  0000 L CNN
F 2 "" H 4205 4430 50  0000 C CNN
F 3 "" H 4205 4430 50  0000 C CNN
	1    4205 4430
	1    0    0    1   
$EndComp
Wire Wire Line
	4205 4430 4205 4360
Wire Wire Line
	4705 4405 4705 4360
Wire Wire Line
	4455 4790 4455 4460
Wire Wire Line
	4755 4990 4845 4990
Wire Wire Line
	4455 5755 4455 5675
Wire Wire Line
	5145 4990 5360 4990
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF30
P 3950 6260
F 0 "R?" H 4038 6306 50  0000 L CNN
F 1 "10K" H 4038 6215 50  0000 L CNN
F 2 "Zimprich:R_0603" V 3880 6260 50  0001 C CNN
F 3 "Value" H 3950 6260 50  0001 C CNN
F 4 "Value" H 4038 6381 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4038 6275 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4038 6169 60  0001 L CNN "Technische Daten"
F 7 "Value" H 4038 6063 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4038 5957 60  0001 L CNN "Bauform"
	1    3950 6260
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A09FF31
P 3445 5820
F 0 "R?" V 3365 5740 50  0000 L CNN
F 1 "4K7" V 3445 5750 50  0000 L CNN
F 2 "Zimprich:R_0603" V 3375 5820 50  0001 C CNN
F 3 "Value" H 3445 5820 50  0001 C CNN
F 4 "Value" H 3533 5941 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 3533 5835 60  0001 L CNN "Bestelllink"
F 6 "Value" H 3533 5729 60  0001 L CNN "Technische Daten"
F 7 "Value" H 3533 5623 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 3533 5517 60  0001 L CNN "Bauform"
	1    3445 5820
	0    1    1    0   
$EndComp
$Comp
L Transistor:BC849 Q?
U 1 1 5A09FF32
P 3850 5820
F 0 "Q?" H 4041 5866 50  0000 L CNN
F 1 "BC847B" H 4041 5775 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H -1930 3055 50  0001 L CIN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/BC846-848-CDIL.pdf" H -2130 3130 50  0001 L CNN
F 4 "SOT-23" H 3850 5820 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/BC-Transistoren/BC-847A-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18561&GROUPID=7206&artnr=BC+847A+SMD&SEARCH=bc847" H 3850 5820 60  0001 C CNN "Bestelllink"
F 6 "Transistor SMD NPN SOT-23 45V 0,1A 0,25W" H 3850 5820 60  0001 C CNN "Technische Daten"
F 7 "R: BC 847A SMD" H 3850 5820 60  0001 C CNN "Bestellnummer"
F 8 "SOT-23" H 3850 5820 60  0001 C CNN "Bauform"
F 9 "Value" H 3850 5820 60  0001 C CNN "Funktion"
F 10 "Value" H 3850 5820 60  0001 C CNN "Hersteller"
F 11 "Value" H 3850 5820 60  0001 C CNN "Hersteller Bestellnummer"
	1    3850 5820
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6020 3950 6060
$Comp
L power:GND #PWR?
U 1 1 5A09FF33
P 3950 6450
F 0 "#PWR?" H 3950 6200 50  0001 C CNN
F 1 "GND" H 3955 6277 50  0000 C CNN
F 2 "" H 3950 6450 50  0000 C CNN
F 3 "" H 3950 6450 50  0000 C CNN
	1    3950 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5820 3595 5820
Wire Wire Line
	3950 6450 3950 6410
Connection ~ 3950 6060
Wire Wire Line
	4180 6060 3950 6060
Wire Wire Line
	3950 5620 3950 5580
Wire Wire Line
	3950 5580 3890 5580
Wire Wire Line
	2570 5270 4455 5270
Connection ~ 4455 5270
Wire Wire Line
	2570 5370 3295 5370
Wire Wire Line
	3295 5370 3295 5820
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Dual-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A0A0496
P 4455 4360
F 0 "JP?" H 4455 4599 50  0000 C CNN
F 1 "BlueS. 5V/3.3V" H 4455 4508 50  0000 C CNN
F 2 "" H 4455 4360 50  0001 C CNN
F 3 "" H 4455 4360 50  0001 C CNN
	1    4455 4360
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Dual-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A0A0A60
P 4830 1330
F 0 "JP?" H 4830 1569 50  0000 C CNN
F 1 "WlanS. 5V/3.3V" H 4830 1478 50  0000 C CNN
F 2 "" H 4830 1330 50  0001 C CNN
F 3 "" H 4830 1330 50  0001 C CNN
	1    4830 1330
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Dual-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A0A0D7B
P 3215 2780
F 0 "JP?" H 3215 2926 50  0000 C CNN
F 1 "WlanV. 5V/3.3V" H 3215 3017 50  0000 C CNN
F 2 "" H 3215 2780 50  0001 C CNN
F 3 "" H 3215 2780 50  0001 C CNN
	1    3215 2780
	-1   0    0    1   
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:Jumper_NC_Dual-RESCUE-sender_v3.0_neu_geoeffnet JP?
U 1 1 5A0A13B7
P 3215 6795
F 0 "JP?" H 3215 6941 50  0000 C CNN
F 1 "BlueV 5V/3.3V" H 3215 7032 50  0000 C CNN
F 2 "" H 3215 6795 50  0001 C CNN
F 3 "" H 3215 6795 50  0001 C CNN
	1    3215 6795
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05 P?
U 1 1 5A0A174A
P 3330 1895
F 0 "P?" H 3409 1937 50  0000 L CNN
F 1 "Wlan" H 3409 1846 50  0000 L CNN
F 2 "Zimprich:JST_EH_B05B-EH-A_05x2.50mm_Straight" H 3330 1895 50  0001 C CNN
F 3 "~" H 3330 1895 50  0001 C CNN
F 4 "Value" H 3330 1895 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3330 1895 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3330 1895 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3330 1895 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3330 1895 60  0001 C CNN "Bauform"
F 9 "Value" H 3330 1895 60  0001 C CNN "Funktion"
F 10 "Value" H 3330 1895 60  0001 C CNN "Hersteller"
F 11 "Value" H 3330 1895 60  0001 C CNN "Hersteller Bestellnummer"
	1    3330 1895
	1    0    0    -1  
$EndComp
Wire Wire Line
	2585 1545 2585 1895
Wire Wire Line
	2590 2245 4830 2245
Wire Wire Line
	2505 1845 2505 2435
Wire Wire Line
	2505 2435 2505 2590
Wire Wire Line
	2685 5570 3220 5570
Wire Wire Line
	2505 1695 2505 1845
Wire Wire Line
	4830 2245 4830 2345
Wire Wire Line
	4060 1610 4060 1660
Wire Wire Line
	3950 6060 3950 6110
Wire Wire Line
	4455 5270 4455 5375
$EndSCHEMATC
