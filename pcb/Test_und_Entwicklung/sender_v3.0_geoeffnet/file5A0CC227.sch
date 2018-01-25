EESchema Schematic File Version 4
LIBS:sender_v3.0_geoeffnet-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 8
Title "Perimeter Sender"
Date "2016-01-14"
Rev "V1.3"
Comp "Layout & Plan von JürgenL und UweZ"
Comment1 "Schaltplan und Layout JürgenL & UweZ"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CC8AB
P 5230 3385
F 0 "R?" V 5390 3385 50  0000 C CNN
F 1 "10K" V 5310 3385 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5160 3385 30  0001 C CNN
F 3 "" H 5230 3385 30  0000 C CNN
F 4 "Value" H 5230 3385 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5230 3385 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5230 3385 60  0001 C CNN "Bauform"
F 7 "Value" H 5230 3385 60  0001 C CNN "Bestelllink"
	1    5230 3385
	0    -1   -1   0   
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:OP275-RESCUE-Perimeter_sender_v2-RESCUE-sender_v3.0_neu_geoeffnet U?
U 1 1 5A0CC8B0
P 6180 3485
F 0 "U?" H 6180 3635 60  0000 L CNN
F 1 "OPA2340PA" H 6180 3335 60  0000 L CNN
F 2 "40xx:40xx-DIL08" H 6180 3485 60  0001 C CNN
F 3 "" H 6180 3485 60  0000 C CNN
F 4 "Value" H 6180 3485 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6180 3485 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6180 3485 60  0001 C CNN "Bauform"
F 7 "Value" H 6180 3485 60  0001 C CNN "Bestelllink"
	1    6180 3485
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CC8B1
P 7275 3485
F 0 "R?" V 7380 3485 50  0000 C CNN
F 1 "1K" V 7155 3485 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 7205 3485 30  0001 C CNN
F 3 "" H 7275 3485 30  0000 C CNN
F 4 "Value" H 7275 3485 60  0001 C CNN "Technische Daten"
F 5 "Value" H 7275 3485 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 7275 3485 60  0001 C CNN "Bauform"
F 7 "Value" H 7275 3485 60  0001 C CNN "Bestelllink"
	1    7275 3485
	0    1    -1   0   
$EndComp
Text GLabel 7745 3485 2    60   Output ~ 0
Messwiderstand_Ausgang
$Comp
L sender_v3.0_neu_geoeffnet-rescue:C-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A0CC8B9
P 6595 2945
F 0 "C?" H 6620 3045 50  0000 L CNN
F 1 "100nF" H 6620 2845 50  0000 L CNN
F 2 "ACS712:C_Rect_L4_W2.5_P2.5_P5.0" H 6633 2795 30  0001 C CNN
F 3 "" H 6595 2945 60  0000 C CNN
F 4 "Value" H 6595 2945 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6595 2945 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6595 2945 60  0001 C CNN "Bauform"
F 7 "Value" H 6595 2945 60  0001 C CNN "Bestelllink"
	1    6595 2945
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:CP_Small-RESCUE-sender_v3.0_neu_geoeffnet C?
U 1 1 5A0CC8BC
P 6930 2950
F 0 "C?" H 6940 3020 50  0000 L CNN
F 1 "10uF/16V" H 6940 2870 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 6930 2950 60  0001 C CNN
F 3 "" H 6930 2950 60  0000 C CNN
F 4 "Value" H 6930 2950 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6930 2950 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6930 2950 60  0001 C CNN "Bauform"
F 7 "Value" H 6930 2950 60  0001 C CNN "Bestelllink"
	1    6930 2950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5A0CC8C1
P 6080 2445
F 0 "#PWR?" H 6080 2295 50  0001 C CNN
F 1 "+5V" H 6098 2619 50  0000 C CNN
F 2 "" H 6080 2445 50  0000 C CNN
F 3 "" H 6080 2445 50  0000 C CNN
	1    6080 2445
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A0CC8D0
P 6080 3935
F 0 "#PWR?" H 6080 3685 50  0001 C CNN
F 1 "GND" H 6085 3762 50  0000 C CNN
F 2 "" H 6080 3935 50  0001 C CNN
F 3 "" H 6080 3935 50  0001 C CNN
	1    6080 3935
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A0CC8D1
P 6595 3220
F 0 "#PWR?" H 6595 2970 50  0001 C CNN
F 1 "GND" H 6600 3047 50  0000 C CNN
F 2 "" H 6595 3220 50  0001 C CNN
F 3 "" H 6595 3220 50  0001 C CNN
	1    6595 3220
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A0CC8D2
P 6930 3225
F 0 "#PWR?" H 6930 2975 50  0001 C CNN
F 1 "GND" H 6935 3052 50  0000 C CNN
F 2 "" H 6930 3225 50  0001 C CNN
F 3 "" H 6930 3225 50  0001 C CNN
	1    6930 3225
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CADEB
P 5230 3585
F 0 "R?" V 5070 3585 50  0000 C CNN
F 1 "10K" V 5140 3585 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5160 3585 30  0001 C CNN
F 3 "" H 5230 3585 30  0000 C CNN
F 4 "Value" H 5230 3585 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5230 3585 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5230 3585 60  0001 C CNN "Bauform"
F 7 "Value" H 5230 3585 60  0001 C CNN "Bestelllink"
	1    5230 3585
	0    -1   -1   0   
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CB0BC
P 4350 3030
F 0 "R?" H 4455 3030 50  0000 C CNN
F 1 "47K" H 4485 2965 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 4280 3030 30  0001 C CNN
F 3 "" H 4350 3030 30  0000 C CNN
F 4 "Value" H 4350 3030 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4350 3030 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4350 3030 60  0001 C CNN "Bauform"
F 7 "Value" H 4350 3030 60  0001 C CNN "Bestelllink"
	1    4350 3030
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CB1AF
P 3640 3010
F 0 "R?" H 3745 3010 50  0000 C CNN
F 1 "470" H 3770 2940 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 3570 3010 30  0001 C CNN
F 3 "" H 3640 3010 30  0000 C CNN
F 4 "Value" H 3640 3010 60  0001 C CNN "Technische Daten"
F 5 "Value" H 3640 3010 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 3640 3010 60  0001 C CNN "Bauform"
F 7 "Value" H 3640 3010 60  0001 C CNN "Bestelllink"
	1    3640 3010
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CB4BC
P 4350 3905
F 0 "R?" H 4455 3905 50  0000 C CNN
F 1 "10" H 4450 3840 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 4280 3905 30  0001 C CNN
F 3 "" H 4350 3905 30  0000 C CNN
F 4 "Value" H 4350 3905 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4350 3905 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4350 3905 60  0001 C CNN "Bauform"
F 7 "Value" H 4350 3905 60  0001 C CNN "Bestelllink"
	1    4350 3905
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5A0CBECD
P 4350 4330
F 0 "#PWR?" H 4350 4080 50  0001 C CNN
F 1 "GND" H 4355 4157 50  0000 C CNN
F 2 "" H 4350 4330 50  0001 C CNN
F 3 "" H 4350 4330 50  0001 C CNN
	1    4350 4330
	1    0    0    -1  
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CC31D
P 6360 4250
F 0 "R?" V 6200 4250 50  0000 C CNN
F 1 "480K" V 6270 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 6290 4250 30  0001 C CNN
F 3 "" H 6360 4250 30  0000 C CNN
F 4 "Value" H 6360 4250 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6360 4250 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6360 4250 60  0001 C CNN "Bauform"
F 7 "Value" H 6360 4250 60  0001 C CNN "Bestelllink"
	1    6360 4250
	0    -1   -1   0   
$EndComp
$Comp
L sender_v3.0_neu_geoeffnet-rescue:R-RESCUE-sender_v3.0_neu_geoeffnet R?
U 1 1 5A0CC7A1
P 5495 3925
F 0 "R?" H 5600 3925 50  0000 C CNN
F 1 "480K" H 5640 3855 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5425 3925 30  0001 C CNN
F 3 "" H 5495 3925 30  0000 C CNN
F 4 "Value" H 5495 3925 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5495 3925 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5495 3925 60  0001 C CNN "Bauform"
F 7 "Value" H 5495 3925 60  0001 C CNN "Bestelllink"
	1    5495 3925
	1    0    0    -1  
$EndComp
Text GLabel 3460 3575 0    60   Input ~ 0
Messwiderstand_1
Text GLabel 3460 3905 0    60   Input ~ 0
Messwiderstand_1
Wire Wire Line
	5380 3585 5830 3585
Wire Wire Line
	5775 3585 5775 4250
Wire Wire Line
	6885 4250 6885 3485
Wire Wire Line
	6530 3485 7125 3485
Connection ~ 6885 3485
Wire Wire Line
	6080 3935 6080 3785
Wire Wire Line
	6080 2445 6080 3185
Wire Wire Line
	7425 3485 7745 3485
Wire Wire Line
	6595 3220 6595 3095
Wire Wire Line
	6930 3050 6930 3225
Connection ~ 5775 3585
Wire Wire Line
	5080 3585 4350 3585
Wire Wire Line
	4350 3180 4350 3755
Connection ~ 4350 3585
Wire Wire Line
	5380 3385 5830 3385
Wire Wire Line
	5080 3385 3640 3385
Wire Wire Line
	3640 3160 3640 3575
Wire Wire Line
	4350 4055 4350 4330
Wire Wire Line
	4350 2570 4350 2880
Wire Wire Line
	3640 2570 3640 2860
Wire Wire Line
	5775 4250 6210 4250
Wire Wire Line
	6510 4250 6885 4250
Wire Wire Line
	5495 4250 5495 4075
Wire Wire Line
	5495 3775 5495 3385
Connection ~ 5495 3385
Wire Wire Line
	3640 3575 3460 3575
Connection ~ 3640 3385
Wire Wire Line
	3460 3905 3640 3905
Wire Wire Line
	3640 3905 3640 4250
Wire Wire Line
	3640 4250 5495 4250
Connection ~ 4350 4250
Wire Wire Line
	3640 2570 6930 2570
Wire Wire Line
	6930 2570 6930 2850
Connection ~ 6080 2570
Wire Wire Line
	6595 2795 6595 2570
Connection ~ 6595 2570
Connection ~ 4350 2570
$EndSCHEMATC
