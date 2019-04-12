EESchema Schematic File Version 4
LIBS:sender_v3.0_geoeffnet-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title "Ardumower shield SVN Version"
Date "2019-03-06"
Rev "1.3"
Comp "ML AG JL UZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR044
U 1 1 5A04C8D0
P 5615 2410
F 0 "#PWR044" H 5615 2160 60  0001 C CNN
F 1 "GND" V 5615 2185 60  0000 C CNN
F 2 "" H 5615 2410 60  0000 C CNN
F 3 "" H 5615 2410 60  0000 C CNN
	1    5615 2410
	0    1    -1   0   
$EndComp
Text GLabel 2715 3830 0    39   Input ~ 0
Mover_in_Ladestation
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R18
U 1 1 5A04C8D1
P 5425 2610
F 0 "R18" V 5400 2840 40  0000 C CNN
F 1 "220R" V 5432 2611 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 5355 2610 30  0001 C CNN
F 3 "" H 5425 2610 30  0000 C CNN
F 4 "Value" H 5425 2610 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5425 2610 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5425 2610 60  0001 C CNN "Bauform"
F 7 "Value" H 5425 2610 60  0001 C CNN "Bestelllink"
	1    5425 2610
	0    -1   1    0   
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R16
U 1 1 5A04C8D2
P 5010 2510
F 0 "R16" V 4980 2720 40  0000 C CNN
F 1 "100R" V 5017 2511 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4940 2510 30  0001 C CNN
F 3 "" H 5010 2510 30  0000 C CNN
F 4 "Value" H 5010 2510 60  0001 C CNN "Bestellnummer"
	1    5010 2510
	0    -1   1    0   
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R14
U 1 1 5A04C8D3
P 5000 3530
F 0 "R14" V 4970 3760 40  0000 C CNN
F 1 "220R" V 5007 3531 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4930 3530 30  0001 C CNN
F 3 "" H 5000 3530 30  0000 C CNN
F 4 "220" H 5000 3530 60  0001 C CNN "Bestellnummer"
	1    5000 3530
	0    -1   1    0   
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R10
U 1 1 5A04C8D4
P 4530 3430
F 0 "R10" V 4500 3645 40  0000 C CNN
F 1 "220R" V 4537 3431 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4460 3430 30  0001 C CNN
F 3 "" H 4530 3430 30  0000 C CNN
F 4 "220" H 4530 3430 60  0001 C CNN "Bestellnummer"
	1    4530 3430
	0    -1   1    0   
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R13
U 1 1 5A04C8D5
P 5000 3330
F 0 "R13" V 4970 3545 40  0000 C CNN
F 1 "220R" V 5007 3331 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4930 3330 30  0001 C CNN
F 3 "" H 5000 3330 30  0000 C CNN
F 4 "220" H 5000 3330 60  0001 C CNN "Bestellnummer"
	1    5000 3330
	0    -1   1    0   
$EndComp
Wire Wire Line
	5740 2410 5615 2410
Wire Wire Line
	5155 2710 5740 2710
Wire Wire Line
	5150 3330 5735 3330
Wire Wire Line
	4680 3430 5735 3430
Wire Wire Line
	5150 3530 5735 3530
Wire Wire Line
	4680 2510 4860 2510
Wire Wire Line
	2715 3830 2825 3830
Wire Wire Line
	2715 3930 2825 3930
Wire Wire Line
	2710 4030 2825 4030
Wire Wire Line
	4225 3330 4850 3330
Wire Wire Line
	4225 3430 4380 3430
Wire Wire Line
	4225 3530 4850 3530
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R19
U 1 1 5A04C8DC
P 5005 2710
F 0 "R19" V 4975 2925 40  0000 C CNN
F 1 "0R" V 5012 2711 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4935 2710 30  0001 C CNN
F 3 "" H 5005 2710 30  0000 C CNN
F 4 "220" H 5005 2710 60  0001 C CNN "Bestellnummer"
	1    5005 2710
	0    -1   1    0   
$EndComp
Wire Wire Line
	4695 2710 4855 2710
Wire Wire Line
	5160 2510 5740 2510
Wire Wire Line
	5575 2610 5740 2610
$Comp
L power:+24V #PWR043
U 1 1 5A04C8DE
P 4695 2710
F 0 "#PWR043" H 4695 2560 50  0001 C CNN
F 1 "+24V" V 4695 2930 50  0000 C CNN
F 2 "" H 4695 2710 50  0000 C CNN
F 3 "" H 4695 2710 50  0000 C CNN
	1    4695 2710
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4675 2610 5275 2610
Wire Wire Line
	2705 4530 2825 4530
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R12
U 1 1 5A04C8E1
P 4750 4030
F 0 "R12" V 4720 4245 40  0000 C CNN
F 1 "220R" V 4757 4031 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4680 4030 30  0001 C CNN
F 3 "" H 4750 4030 30  0000 C CNN
F 4 "220" H 4750 4030 60  0001 C CNN "Bestellnummer"
	1    4750 4030
	0    -1   1    0   
$EndComp
Wire Wire Line
	4900 4030 5735 4030
$Comp
L sender_v3.0_geoeffnet-rescue:Conn_01x09-Connector P10
U 1 1 5A04C8E5
P 7045 3625
F 0 "P10" H 7123 3663 50  0000 L CNN
F 1 "Status LEDs  GND" H 7123 3571 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 7045 3625 50  0001 C CNN
F 3 "" H 7045 3625 50  0000 C CNN
	1    7045 3625
	1    0    0    -1  
$EndComp
Wire Wire Line
	6745 2415 6745 2515
Wire Wire Line
	6845 3225 6745 3225
Wire Wire Line
	6745 3225 6745 3325
Wire Wire Line
	6745 3325 6845 3325
Wire Wire Line
	6745 3425 6845 3425
Connection ~ 6745 3325
Wire Wire Line
	6745 3525 6845 3525
Connection ~ 6745 3425
Wire Wire Line
	6745 3625 6845 3625
Connection ~ 6745 3525
Wire Wire Line
	6745 3725 6845 3725
Connection ~ 6745 3625
Wire Wire Line
	6745 3825 6845 3825
Connection ~ 6745 3725
Wire Wire Line
	6745 3925 6845 3925
Connection ~ 6745 3825
Wire Wire Line
	6745 4025 6845 4025
Connection ~ 6745 3925
Wire Wire Line
	6745 2615 6845 2615
Wire Wire Line
	6745 2515 6845 2515
Connection ~ 6745 2615
Wire Wire Line
	6745 2415 6845 2415
Connection ~ 6745 2515
$Comp
L power:GND #PWR047
U 1 1 5A04C8E6
P 6745 4100
F 0 "#PWR047" H 6745 3850 60  0001 C CNN
F 1 "GND" H 6745 3935 60  0000 C CNN
F 2 "" H 6745 4100 60  0000 C CNN
F 3 "" H 6745 4100 60  0000 C CNN
	1    6745 4100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR046
U 1 1 5A04C8E7
P 6745 2960
F 0 "#PWR046" H 6745 2710 60  0001 C CNN
F 1 "GND" H 6745 2795 60  0000 C CNN
F 2 "" H 6745 2960 60  0000 C CNN
F 3 "" H 6745 2960 60  0000 C CNN
	1    6745 2960
	-1   0    0    -1  
$EndComp
Connection ~ 6745 4025
$Comp
L power:GND #PWR045
U 1 1 5A04C8E8
P 5670 4200
F 0 "#PWR045" H 5670 3950 60  0001 C CNN
F 1 "GND" H 5670 4035 60  0000 C CNN
F 2 "" H 5670 4200 60  0000 C CNN
F 3 "" H 5670 4200 60  0000 C CNN
	1    5670 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5670 4200 5670 4130
Wire Wire Line
	5670 4130 5735 4130
$Comp
L sender_v3.0_geoeffnet-rescue:SPEAKER-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue SP1
U 1 1 5A04C8E9
P 4935 5065
F 0 "SP1" H 5213 5111 50  0000 L CNN
F 1 "SPEAKER" H 5213 5019 50  0000 L CNN
F 2 "Zimprich:Buzzer_12x9.5RM7.6_RM5.0" H 4935 5065 50  0001 C CNN
F 3 "" H 4935 5065 50  0000 C CNN
	1    4935 5065
	1    0    0    1   
$EndComp
Text GLabel 2705 4530 0    39   Input ~ 0
Summer
$Comp
L power:GND #PWR039
U 1 1 5A04C8EA
P 4610 5200
F 0 "#PWR039" H 4610 4950 60  0001 C CNN
F 1 "GND" V 4610 4995 60  0000 C CNN
F 2 "" H 4610 5200 60  0000 C CNN
F 3 "" H 4610 5200 60  0000 C CNN
	1    4610 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4610 5200 4610 5165
Wire Wire Line
	4610 5165 4635 5165
Connection ~ 4580 4030
Wire Wire Line
	6745 3325 6745 3425
Wire Wire Line
	6745 3425 6745 3525
Wire Wire Line
	6745 3525 6745 3625
Wire Wire Line
	6745 3625 6745 3725
Wire Wire Line
	6745 3725 6745 3825
Wire Wire Line
	6745 3825 6745 3925
Wire Wire Line
	6745 3925 6745 4025
Wire Wire Line
	6745 2515 6745 2615
Wire Wire Line
	6745 4025 6745 4100
Wire Wire Line
	4580 4030 4600 4030
$Comp
L power:+5V #PWR040
U 1 1 5CA45012
P 4675 2610
F 0 "#PWR040" H 4675 2460 50  0001 C CNN
F 1 "+5V" V 4670 2800 50  0000 C CNN
F 2 "" H 4675 2610 50  0001 C CNN
F 3 "" H 4675 2610 50  0001 C CNN
	1    4675 2610
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR041
U 1 1 5CA45C01
P 4680 2510
F 0 "#PWR041" H 4680 2360 50  0001 C CNN
F 1 "+3.3V" V 4680 2745 50  0000 C CNN
F 2 "" H 4680 2510 50  0001 C CNN
F 3 "" H 4680 2510 50  0001 C CNN
	1    4680 2510
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR037
U 1 1 5CA52CE3
P 2695 3330
F 0 "#PWR037" H 2695 3180 50  0001 C CNN
F 1 "+5V" V 2690 3520 50  0000 C CNN
F 2 "" H 2695 3330 50  0001 C CNN
F 3 "" H 2695 3330 50  0001 C CNN
	1    2695 3330
	0    -1   -1   0   
$EndComp
Text GLabel 2715 3930 0    39   Input ~ 0
LED_SchleifenStatus_Grün
Text GLabel 2710 4130 0    39   Input ~ 0
LED_SchleifenStatus_Rot
Text GLabel 2710 4030 0    39   Input ~ 0
LED_SchleifenStatus_Gelb
Text GLabel 2730 4230 0    39   Input ~ 0
LED_Motortreiber_ÜLast+Temp_Rot
Wire Wire Line
	2710 4130 2825 4130
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R15
U 1 1 5C783229
P 5000 3730
F 0 "R15" V 4970 3960 40  0000 C CNN
F 1 "220R" V 5007 3731 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4930 3730 30  0001 C CNN
F 3 "" H 5000 3730 30  0000 C CNN
F 4 "220" H 5000 3730 60  0001 C CNN "Bestellnummer"
	1    5000 3730
	0    -1   1    0   
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R11
U 1 1 5C783234
P 4530 3630
F 0 "R11" V 4500 3845 40  0000 C CNN
F 1 "220R" V 4537 3631 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4460 3630 30  0001 C CNN
F 3 "" H 4530 3630 30  0000 C CNN
F 4 "220" H 4530 3630 60  0001 C CNN "Bestellnummer"
	1    4530 3630
	0    -1   1    0   
$EndComp
Wire Wire Line
	4225 3630 4380 3630
Wire Wire Line
	4225 3730 4850 3730
$Comp
L sender_v3.0_geoeffnet-rescue:Conn_01x09-Connector P7
U 1 1 5A04C8E2
P 5935 3730
F 0 "P7" H 6013 3768 50  0000 L CNN
F 1 "Status LEDs" H 6013 3676 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 5935 3730 50  0001 C CNN
F 3 "" H 5935 3730 50  0000 C CNN
	1    5935 3730
	1    0    0    -1  
$EndComp
Wire Wire Line
	4680 3630 5735 3630
Wire Wire Line
	5150 3730 5735 3730
Text GLabel 2730 4330 0    39   Input ~ 0
Pin39
Wire Wire Line
	2825 4230 2730 4230
Wire Wire Line
	2825 4330 2730 4330
Text GLabel 2735 4430 0    39   Input ~ 0
Pin36
Wire Wire Line
	2825 4430 2735 4430
Wire Wire Line
	4225 3830 4380 3830
Wire Wire Line
	4680 3830 5735 3830
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R8
U 1 1 5C82874A
P 4530 3830
F 0 "R8" V 4500 4045 40  0000 C CNN
F 1 "220R" V 4537 3831 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4460 3830 30  0001 C CNN
F 3 "" H 4530 3830 30  0000 C CNN
F 4 "220" H 4530 3830 60  0001 C CNN "Bestellnummer"
	1    4530 3830
	0    -1   1    0   
$EndComp
Wire Wire Line
	4225 3930 4375 3930
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet-sender_v3.0_neu_geoeffnet-rescue R7
U 1 1 5C82626E
P 5000 3930
F 0 "R7" V 4970 4145 40  0000 C CNN
F 1 "0R" V 5000 3930 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4930 3930 30  0001 C CNN
F 3 "" H 5000 3930 30  0000 C CNN
F 4 "220" H 5000 3930 60  0001 C CNN "Bestellnummer"
	1    5000 3930
	0    -1   1    0   
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:BC817-40-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue Q3
U 1 1 5803F35D
P 8755 4145
F 0 "Q3" H 8946 4236 50  0000 L CNN
F 1 "BC817" H 8946 4145 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8946 4054 50  0001 L CIN
F 3 "" H 8755 4145 50  0000 L CNN
	1    8755 4145
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:BC817-40-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue Q2
U 1 1 5803F363
P 8495 3605
F 0 "Q2" H 8686 3696 50  0000 L CNN
F 1 "BC817" H 8686 3605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8686 3514 50  0001 L CIN
F 3 "" H 8495 3605 50  0000 L CNN
	1    8495 3605
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:GND-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue #PWR038
U 1 1 5803F36B
P 8395 4935
F 0 "#PWR038" H 8395 4685 50  0001 C CNN
F 1 "GND" H 8400 4762 50  0000 C CNN
F 2 "" H 8395 4935 50  0000 C CNN
F 3 "" H 8395 4935 50  0000 C CNN
	1    8395 4935
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue R33
U 1 1 5803F388
P 8395 4570
F 0 "R33" H 8483 4616 50  0000 L CNN
F 1 "68R" H 8483 4525 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8325 4570 50  0001 C CNN
F 3 "" H 8395 4570 50  0001 C CNN
F 4 "Value" H 8395 4570 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8395 4570 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8395 4570 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8395 4570 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8395 4570 60  0001 C CNN "Bauform"
F 9 "Value" H 8395 4570 60  0001 C CNN "Funktion"
F 10 "Value" H 8395 4570 60  0001 C CNN "Hersteller"
F 11 "Value" H 8395 4570 60  0001 C CNN "Hersteller Bestellnummer"
	1    8395 4570
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue R34
U 1 1 5803F393
P 8855 3210
F 0 "R34" H 8943 3256 50  0000 L CNN
F 1 "8K2" H 8943 3165 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 8943 3384 50  0001 L CNN
F 3 "" H 8855 3210 50  0001 C CNN
F 4 "Value" H 8943 3285 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 8943 3179 60  0001 L CNN "Bestelllink"
F 6 "Value" H 8943 3073 60  0001 L CNN "Technische Daten"
F 7 "Value" H 8943 2967 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 8943 2861 60  0001 L CNN "Bauform"
F 9 "Value" H 8855 3210 60  0001 C CNN "Funktion"
F 10 "Value" H 8855 3210 60  0001 C CNN "Hersteller"
F 11 "Value" H 8855 3210 60  0001 C CNN "Hersteller Bestellnummer"
	1    8855 3210
	-1   0    0    -1  
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:UDN2987A-6-T-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue IC1
U 1 1 5895D97B
P 3525 3930
F 0 "IC1" H 3525 4900 50  0000 C CNN
F 1 "UDN 2987 LWTR-6T" H 3525 4809 50  0000 C CNN
F 2 "Package_SO:SOIC-20W_7.5x12.8mm_P1.27mm" H 1505 -2890 50  0001 L CNN
F 3 "DABIC-5 8-Channel Source Driver with Overcurrent Protection" H 1505 -2890 50  0001 L CNN
F 4 "SOIC-20W" H 3525 3930 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3525 3930 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3525 3930 60  0001 C CNN "Technische Daten"
F 7 "R: UDN 2987 LWTR-6T" H 3525 3930 60  0001 C CNN "Bestellnummer"
F 8 "SOIC-20W" H 3525 3930 60  0001 C CNN "Bauform"
F 9 "Value" H 3525 3930 60  0001 C CNN "Funktion"
F 10 "Value" H 3525 3930 60  0001 C CNN "Hersteller"
F 11 "Value" H 3525 3930 60  0001 C CNN "Hersteller Bestellnummer"
F 12 "Allegro MicroSystems LLC" H 1505 -2890 50  0001 L CNN "MF"
F 13 "Unavailable" H 1505 -2890 50  0001 L CNN "Availability"
F 14 "DIP-20 Allegro MicroSystems LLC" H 1505 -2890 50  0001 L CNN "Package"
F 15 "1.94 USD" H 1505 -2890 50  0001 L CNN "Price"
F 16 "UDN2987A-6-T" H 1505 -2890 50  0001 L CNN "MP"
	1    3525 3930
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_geoeffnet-rescue:GND-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue #PWR013
U 1 1 589621EF
P 2710 4730
F 0 "#PWR013" H 2710 4480 60  0001 C CNN
F 1 "GND" V 2710 4525 60  0000 C CNN
F 2 "" H 2710 4730 60  0000 C CNN
F 3 "" H 2710 4730 60  0000 C CNN
	1    2710 4730
	0    1    1    0   
$EndComp
NoConn ~ 2825 3630
$Comp
L sender_v3.0_geoeffnet-rescue:R-RESCUE-ardumower_mega_shield_svn-ardumower-mega-shield-svn-rescue R17
U 1 1 58A302BB
P 2605 3530
F 0 "R17" V 2575 3745 40  0000 C CNN
F 1 "2k2" V 2612 3531 40  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2535 3530 30  0001 C CNN
F 3 "" H 2605 3530 30  0001 C CNN
F 4 "Value" H 2605 3530 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2605 3530 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2605 3530 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2605 3530 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2605 3530 60  0001 C CNN "Bauform"
F 9 "Value" H 2605 3530 60  0001 C CNN "Funktion"
F 10 "Value" H 2605 3530 60  0001 C CNN "Hersteller"
F 11 "Value" H 2605 3530 60  0001 C CNN "Hersteller Bestellnummer"
	1    2605 3530
	0    -1   1    0   
$EndComp
Wire Wire Line
	2825 3330 2695 3330
Connection ~ 8395 4805
Wire Wire Line
	8855 2945 8855 3060
Wire Wire Line
	8855 4805 8855 4345
Wire Wire Line
	8395 4805 8855 4805
Wire Wire Line
	8395 4720 8395 4805
Connection ~ 8395 4145
Wire Wire Line
	8395 3805 8395 4145
Wire Wire Line
	8555 4145 8395 4145
Connection ~ 8855 3605
Wire Wire Line
	8855 3360 8855 3605
Wire Wire Line
	8695 3605 8855 3605
Wire Wire Line
	8395 2945 8395 3405
Wire Wire Line
	2710 4730 2825 4730
Wire Wire Line
	2455 3530 2325 3530
Wire Wire Line
	2755 3530 2825 3530
Wire Wire Line
	8395 4805 8395 4935
Wire Wire Line
	8395 4145 8395 4420
Wire Wire Line
	8855 3605 8855 3945
Wire Wire Line
	8395 2945 8855 2945
Connection ~ 8395 2945
Wire Wire Line
	6745 2615 6745 2960
Wire Wire Line
	6790 2945 6790 2715
Wire Wire Line
	6790 2715 6845 2715
Wire Wire Line
	6790 2945 8395 2945
$Comp
L Connector_Generic:Conn_01x04 P9
U 1 1 5C9766EA
P 7045 2515
F 0 "P9" H 7125 2507 50  0000 L CNN
F 1 "Spannungs Led GND" H 7125 2416 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7045 2515 50  0001 C CNN
F 3 "~" H 7045 2515 50  0001 C CNN
	1    7045 2515
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 P8
U 1 1 5C988824
P 5940 2510
F 0 "P8" H 6020 2502 50  0000 L CNN
F 1 "Spannungs Led" H 6020 2411 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5940 2510 50  0001 C CNN
F 3 "~" H 5940 2510 50  0001 C CNN
	1    5940 2510
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5CA07D50
P 2325 3530
F 0 "#PWR05" H 2325 3380 50  0001 C CNN
F 1 "+5V" V 2320 3720 50  0000 C CNN
F 2 "" H 2325 3530 50  0001 C CNN
F 3 "" H 2325 3530 50  0001 C CNN
	1    2325 3530
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4225 4030 4580 4030
Wire Wire Line
	4580 4965 4635 4965
Wire Wire Line
	4580 4030 4580 4965
Text Notes 4655 4335 0    50   ~ 0
Ventilator Anschluss\nDeswegen hat R7 0Ohm
Wire Notes Line
	4880 3870 5120 3870
Wire Notes Line
	5120 3870 5120 3990
Wire Notes Line
	5120 3990 4880 3990
Wire Notes Line
	4880 3990 4880 3870
Wire Notes Line
	5110 3995 5110 4180
$Comp
L Connector_Generic:Conn_01x02 P13
U 1 1 5C909760
P 5950 4675
F 0 "P13" H 6030 4667 50  0000 L CNN
F 1 "Vent." H 6030 4576 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B2B-EH-A_1x02_P2.50mm_Vertical" H 5950 4675 50  0001 C CNN
F 3 "~" H 5950 4675 50  0001 C CNN
	1    5950 4675
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5C90CD11
P 5685 4845
F 0 "#PWR0109" H 5685 4595 60  0001 C CNN
F 1 "GND" H 5685 4680 60  0000 C CNN
F 2 "" H 5685 4845 60  0000 C CNN
F 3 "" H 5685 4845 60  0000 C CNN
	1    5685 4845
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5685 4845 5685 4775
Wire Wire Line
	5685 4775 5750 4775
Wire Wire Line
	5150 3930 5735 3930
Wire Wire Line
	4375 4675 4375 3930
Wire Wire Line
	4375 4675 5750 4675
Connection ~ 4375 3930
Wire Wire Line
	4375 3930 4850 3930
$EndSCHEMATC
