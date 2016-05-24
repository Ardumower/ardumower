EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
LIBS:device
LIBS:78xx-Regler-BuildingBlock_ModB_RevA-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 11
Title "Ardumower Shield - Hauptschaltplan"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 4430 905  2    47   Output ~ 0
pinChargeCurrent
$Comp
L CONN_2 P43
U 1 1 53866CB8
P 5505 710
F 0 "P43" V 5455 710 40  0000 C CNN
F 1 "Battery" V 5555 710 40  0000 C CNN
F 2 "ACS712:Anschlussklemme_RM5,08-RM7,62" H 5505 710 98  0001 C CNN
F 3 "" H 5505 710 60  0000 C CNN
	1    5505 710 
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 53866CD6
P 5405 1110
F 0 "#PWR01" H 5405 1110 30  0001 C CNN
F 1 "GND" H 5405 1040 30  0001 C CNN
F 2 "" H 5405 1110 60  0000 C CNN
F 3 "" H 5405 1110 60  0000 C CNN
	1    5405 1110
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5416EE98
P 765 2090
F 0 "#PWR02" H 765 2090 30  0001 C CNN
F 1 "GND" H 765 2020 30  0001 C CNN
F 2 "" H 765 2090 60  0000 C CNN
F 3 "" H 765 2090 60  0000 C CNN
	1    765  2090
	1    0    0    -1  
$EndComp
$Comp
L ACS712 U3
U 1 1 5417150B
P 4180 1555
F 0 "U3" H 4180 1805 50  0000 C CNN
F 1 "INA169" H 4180 1305 50  0000 C CNN
F 2 "ACS712:INA169" H 4180 1555 60  0001 C CNN
F 3 "" H 4180 1555 60  0000 C CNN
F 4 "Value" H 4180 1555 60  0001 C CNN "Bestellnummer"
	1    4180 1555
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR03
U 1 1 54172399
P 4280 1055
F 0 "#PWR03" H 4280 1145 20  0001 C CNN
F 1 "+5V" H 4280 1180 30  0000 C CNN
F 2 "" H 4280 1055 60  0000 C CNN
F 3 "" H 4280 1055 60  0000 C CNN
	1    4280 1055
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 54172562
P 4030 705
F 0 "#PWR04" H 4030 705 30  0001 C CNN
F 1 "GND" H 4030 635 30  0001 C CNN
F 2 "" H 4030 705 60  0000 C CNN
F 3 "" H 4030 705 60  0000 C CNN
	1    4030 705 
	1    0    0    1   
$EndComp
$Comp
L GND #PWR05
U 1 1 541751D4
P 4450 5210
F 0 "#PWR05" H 4450 5210 30  0001 C CNN
F 1 "GND" H 4450 5140 30  0001 C CNN
F 2 "" H 4450 5210 60  0000 C CNN
F 3 "" H 4450 5210 60  0000 C CNN
	1    4450 5210
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P42
U 1 1 541A0C85
P 865 1590
F 0 "P42" V 815 1590 40  0000 C CNN
F 1 "Charger connector" V 915 1590 40  0000 C CNN
F 2 "ACS712:Anschlussklemme_RM5,08-RM7,62" H 865 1590 98  0001 C CNN
F 3 "" H 865 1590 60  0000 C CNN
	1    865  1590
	0    1    -1   0   
$EndComp
$Comp
L CP1 C3
U 1 1 541DF105
P 4230 755
F 0 "C3" H 4280 855 50  0000 L CNN
F 1 "1,0uF" H 4280 655 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 4230 755 60  0001 C CNN
F 3 "~" H 4230 755 60  0000 C CNN
F 4 "R: " H 4230 755 60  0001 C CNN "Bestellnummer"
F 5 "Value" H 4230 755 60  0001 C CNN "Bestelllink"
	1    4230 755 
	0    1    -1   0   
$EndComp
$Comp
L RELAY_2RT K3
U 1 1 54A679F2
P 4850 2740
F 0 "K3" H 4800 3140 70  0000 C CNN
F 1 "RELAY_2RT" H 5000 2240 70  0000 C CNN
F 2 "ACS712:Relais_DPDT_Schrack-RT2_RM5mm_3D_Kontaktbelegung_geändert_FIN40.52.9_6V" H 4850 2740 60  0001 C CNN
F 3 "" H 4850 2740 60  0000 C CNN
F 4 "Siehe Bauteileigenschaften" H 4850 2740 60  0001 C CNN "Bestellnummer"
F 5 "http://www.reichelt.de/Print-Steckrelais/FIN-40-52-9-6V/3/index.html?&ACTION=3&LA=2&ARTICLE=8108&GROUPID=3293&artnr=FIN+40.52.9+6V" H 4850 2740 60  0001 C CNN "Quelle"
F 6 "R: FIN 40.52.9 24V" H 4850 2740 60  0001 C CNN "Bestellnummer 24V"
F 7 "R: FIN 40.52.9 12V" H 4850 2740 60  0001 C CNN "Bestellnummer 12V"
F 8 "R: FIN 40.52.9 6V" H 4850 2740 60  0001 C CNN "Bestellnummer 6V"
F 9 "R: FIN 95.15.2" H 4850 2740 60  0001 C CNN "Printfassung für Relais"
	1    4850 2740
	1    0    0    -1  
$EndComp
$Comp
L BC237 Q1
U 1 1 54B46879
P 4350 4340
F 0 "Q1" H 4550 4240 50  0000 C CNN
F 1 "BC547" H 4600 4490 50  0000 C CNN
F 2 "ACS712:TO92-EBC" H 4540 4340 30  0001 C CNN
F 3 "" H 4350 4340 60  0000 C CNN
	1    4350 4340
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 54B46970
P 3800 4340
F 0 "R18" V 3880 4340 40  0000 C CNN
F 1 "2k2" V 3807 4341 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3730 4340 30  0001 C CNN
F 3 "" H 3800 4340 30  0000 C CNN
	1    3800 4340
	0    -1   -1   0   
$EndComp
Text GLabel 3450 4340 0    60   Input ~ 0
pinChargingEnable
Text GLabel 2910 3510 3    60   Output ~ 0
StationLed
Text Notes 3290 4204 2    39   ~ 0
Station LED\nbzw:\nGrundlast\nPerimetersender
$Comp
L DIODE D10
U 1 1 54C6AF0E
P 4200 3290
F 0 "D10" H 4200 3390 40  0000 C CNN
F 1 "1N4148" H 4200 3190 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 4200 3290 60  0001 C CNN
F 3 "Planar Epitaxial Schaltdiode, DO35, 100V, 0,15A" H 4200 3290 60  0001 C CNN
F 4 "1N4148" H 4200 3290 60  0001 C CNN "Bestellnummer"
	1    4200 3290
	0    -1   -1   0   
$EndComp
$Sheet
S -835 55   620  150 
U 553A7355
F0 "Sonar" 39
F1 "Sonar.sch" 39
$EndSheet
$Sheet
S -960 1965 875  195 
U 553D014E
F0 "I2C" 39
F1 "I2C.sch" 39
$EndSheet
$Sheet
S -770 2860 680  225 
U 553DFC0F
F0 "Stiftleisten" 39
F1 "Stiftleisten.sch" 39
$EndSheet
$Sheet
S -825 -330 615  175 
U 5540C583
F0 "RTC Uhr" 39
F1 "RTC Uhr.sch" 39
$EndSheet
$Sheet
S -960 2420 880  185 
U 553BDA33
F0 "serielle Schnittstelle" 39
F1 "serielle Schnittstelle.sch" 39
$EndSheet
$Sheet
S 185  -330 585  175 
U 553D2376
F0 "Bohrlöcher" 39
F1 "Bohrlöcher.sch" 39
$EndSheet
$Sheet
S 12975 2370 380  1330
U 553E526C
F0 "Stepdownwandler" 60
F1 "Stepdownwandler.sch" 60
F2 "Stepdownwandler_24V_In" I T 13155 2370 60 
$EndSheet
$Comp
L CONN_2 P47
U 1 1 553DAE0C
P 6445 710
F 0 "P47" V 6395 710 40  0000 C CNN
F 1 "Not Aus" V 6495 710 40  0000 C CNN
F 2 "ACS712:Anschlussklemme_RM5,08-RM7,62" H 6445 710 98  0001 C CNN
F 3 "" H 6445 710 60  0000 C CNN
F 4 "Value" H 6445 710 60  0001 C CNN "Bestellnummer"
	1    6445 710 
	0    1    -1   0   
$EndComp
$Sheet
S 9980 2420 880  1220
U 553A6702
F0 "UnterSpannungsSchutz" 60
F1 "UnterSpannungsSchutz.sch" 60
F2 "Batterieeingang 24V" I T 10110 2420 60 
F3 "Batterieausgang 24V" O T 10255 2420 60 
F4 "PinButton" O T 10410 2420 60 
F5 "Ausschalter" I T 10565 2420 60 
$EndSheet
Text GLabel 10575 1570 2    60   Output ~ 0
pinButton
Text GLabel 10725 2030 2    60   Input ~ 0
pinUndervoltageSwitch
Text Notes 12675 2070 3    60   ~ 0
Überspannungsschutzdiode\n?? ob richtiges Zeichen und Polung
$Sheet
S 8385 2420 245  1150
U 554BCB67
F0 "Batteriespannung" 60
F1 "Batteriespannung.sch" 60
F2 "Batteriespannung" I T 8495 2420 60 
$EndSheet
$Comp
L Kondensator CC1
U 1 1 5558C608
P 4805 1470
F 0 "CC1" H 4855 1570 50  0000 L CNN
F 1 "100nF" H 4855 1370 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 4805 1470 60  0001 C CNN
F 3 "" H 4805 1470 60  0000 C CNN
F 4 "R: KERKO 100N" H 4805 1470 60  0001 C CNN "Bestellnummer"
F 5 "Value" H 4805 1470 60  0001 C CNN "Bestelllink"
	1    4805 1470
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5558CC4E
P 4805 1720
F 0 "#PWR06" H 4805 1720 30  0001 C CNN
F 1 "GND" H 4805 1650 30  0001 C CNN
F 2 "" H 4805 1720 60  0000 C CNN
F 3 "" H 4805 1720 60  0000 C CNN
	1    4805 1720
	1    0    0    -1  
$EndComp
Connection ~ 4805 1105
Wire Wire Line
	4805 1270 4805 1105
Wire Wire Line
	4805 1720 4805 1670
Wire Wire Line
	10565 2030 10725 2030
Wire Wire Line
	10565 2420 10565 2030
Wire Wire Line
	10410 1570 10575 1570
Wire Wire Line
	10410 2420 10410 1570
Wire Wire Line
	5415 2590 5250 2590
Wire Wire Line
	5415 2090 5415 2590
Wire Wire Line
	4080 2790 4450 2790
Wire Wire Line
	4280 2490 4450 2490
Wire Wire Line
	4080 1955 4080 2790
Wire Wire Line
	4280 1955 4280 2490
Wire Wire Line
	5130 1105 5130 755 
Wire Wire Line
	4200 3090 4200 2990
Wire Wire Line
	5605 1060 6345 1060
Connection ~ 2910 2090
Connection ~ 4450 3615
Wire Wire Line
	4200 3615 4450 3615
Wire Wire Line
	4200 3490 4200 3615
Wire Wire Line
	2910 2090 2910 3510
Wire Wire Line
	3550 4340 3450 4340
Wire Wire Line
	4450 3090 4450 4140
Connection ~ 4280 1105
Wire Wire Line
	5130 755  4430 755 
Wire Wire Line
	4280 1105 5130 1105
Wire Wire Line
	4050 4340 4150 4340
Wire Wire Line
	4030 755  4030 705 
Wire Wire Line
	4080 1005 4030 755 
Wire Wire Line
	765  1940 765  2090
Wire Wire Line
	4180 905  4430 905 
Wire Wire Line
	4180 1155 4180 905 
Wire Wire Line
	4080 1155 4080 1005
Wire Wire Line
	4280 1055 4280 1155
Wire Wire Line
	5405 1110 5405 1060
Connection ~ 2410 2090
Wire Wire Line
	10110 1060 10110 2420
Wire Wire Line
	10255 2420 10255 1060
Wire Wire Line
	10255 1060 13750 1060
Wire Wire Line
	13155 1060 13155 2370
Connection ~ 13155 1060
Text Notes 13630 1585 0    60   ~ 0
zu den Motortreibern
$Comp
L DIODE D4
U 1 1 5576E06B
P 4450 4880
F 0 "D4" H 4450 4980 40  0000 C CNN
F 1 "1N4148" H 4450 4780 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 4450 4880 60  0001 C CNN
F 3 "Planar Epitaxial Schaltdiode, DO35, 100V, 0,15A" H 4450 4880 60  0001 C CNN
F 4 "1N4148" H 4450 4880 60  0001 C CNN "Bestellnummer"
	1    4450 4880
	0    -1   1    0   
$EndComp
Wire Wire Line
	4450 4540 4450 4680
Wire Wire Line
	4450 5080 4450 5210
Text Notes 4640 4955 0    60   ~ 0
Schutzdiode (Angstdiode)Transistor\nfür den Fall das die Ladespannung verpolt ist
Wire Wire Line
	6725 1060 6725 1235
Connection ~ 6725 1060
Connection ~ 4200 2990
$Sheet
S 2285 2705 245  1150
U 554C1C35
F0 "Ladespannung" 60
F1 "Ladespannung.sch" 60
F2 "Ladespannung" I T 2410 2705 60 
$EndSheet
Wire Wire Line
	2410 2090 2410 2705
Wire Wire Line
	8495 1060 8495 2420
Connection ~ 5415 2090
Wire Wire Line
	5250 2890 7610 2890
Wire Wire Line
	7610 2890 7610 1060
Connection ~ 7610 1060
Connection ~ 8495 1060
Wire Wire Line
	6545 1060 10110 1060
$Comp
L CONN_01X20 P50
U 1 1 55DB0447
P 11175 7790
F 0 "P50" H 11175 8840 50  0000 C CNN
F 1 "CONN_01X20" V 11275 7790 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x20" H 11175 7790 60  0001 C CNN
F 3 "" H 11175 7790 60  0000 C CNN
	1    11175 7790
	-1   0    0    1   
$EndComp
Wire Wire Line
	965  1940 965  2090
$Comp
L GND #PWR07
U 1 1 55DB1F65
P 11475 8825
F 0 "#PWR07" H 11475 8825 30  0001 C CNN
F 1 "GND" H 11480 8675 30  0000 C CNN
F 2 "" H 11475 8825 60  0000 C CNN
F 3 "" H 11475 8825 60  0000 C CNN
F 4 "Value" H 11475 8825 60  0001 C CNN "Technische Daten"
F 5 "Value" H 11475 8825 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 11475 8825 60  0001 C CNN "Bauform"
F 7 "Value" H 11475 8825 60  0001 C CNN "Bestelllink"
	1    11475 8825
	1    0    0    -1  
$EndComp
Wire Wire Line
	11375 8740 11475 8740
Wire Wire Line
	11475 8740 11475 8825
$Comp
L +BATT #PWR08
U 1 1 55DB2CC4
P 6725 1235
F 0 "#PWR08" H 6725 1085 50  0001 C CNN
F 1 "+BATT" H 6725 1375 50  0000 C CNN
F 2 "" H 6725 1235 60  0000 C CNN
F 3 "" H 6725 1235 60  0000 C CNN
	1    6725 1235
	-1   0    0    1   
$EndComp
Wire Wire Line
	965  2090 5415 2090
$Comp
L DIODE D1
U 1 1 55DB5663
P 3315 2560
F 0 "D1" H 3315 2660 40  0000 C CNN
F 1 "1N4148" H 3315 2460 40  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 3315 2560 60  0001 C CNN
F 3 "Planar Epitaxial Schaltdiode, DO35, 100V, 0,15A" H 3315 2560 60  0001 C CNN
F 4 "1N4148" H 3315 2560 60  0001 C CNN "Bestellnummer"
	1    3315 2560
	0    -1   1    0   
$EndComp
Wire Wire Line
	3315 2760 3315 2990
Wire Wire Line
	3315 2360 3315 2090
Connection ~ 3315 2090
Wire Wire Line
	3315 2990 4450 2990
$Comp
L +BATT #PWR09
U 1 1 55DB3743
P 11655 8825
F 0 "#PWR09" H 11655 8675 50  0001 C CNN
F 1 "+BATT" H 11655 8965 50  0000 C CNN
F 2 "" H 11655 8825 60  0000 C CNN
F 3 "" H 11655 8825 60  0000 C CNN
	1    11655 8825
	-1   0    0    1   
$EndComp
Wire Wire Line
	11655 8825 11655 8640
Wire Wire Line
	11655 8640 11375 8640
Text GLabel 11520 6840 2    39   Output ~ 0
Motorstrom
Wire Wire Line
	11520 6840 11375 6840
$Comp
L +5V #PWR010
U 1 1 55DB4926
P 11870 8835
F 0 "#PWR010" H 11870 8925 20  0001 C CNN
F 1 "+5V" V 11870 9000 30  0000 C CNN
F 2 "" H 11870 8835 60  0000 C CNN
F 3 "" H 11870 8835 60  0000 C CNN
	1    11870 8835
	-1   0    0    1   
$EndComp
Wire Wire Line
	11870 8835 11870 8540
Wire Wire Line
	11870 8540 11375 8540
Text GLabel 11490 8340 2    39   Input ~ 0
pinChargeCurrent
Text GLabel 11490 8240 2    39   Input ~ 0
pinChargeVoltage
Text GLabel 11430 6940 2    39   Input ~ 0
pinBatteryVoltage
Text GLabel 11480 8040 2    39   Output ~ 0
pinSonarRightTrigger
Text GLabel 11490 8140 2    39   Input ~ 0
pinSonarRightEcho
Text GLabel 11490 7840 2    39   Output ~ 0
pinSonarLeftTrigger
Text GLabel 11475 7940 2    39   Input ~ 0
pinSonarLeftEcho
Text GLabel 13020 8375 2    39   Output ~ 0
DuoLED-Rot
Text GLabel 13015 8475 2    39   Output ~ 0
DuoLED_Grün
Text GLabel 13005 8275 2    39   Output ~ 0
Led-Status
Text GLabel 13005 8675 2    39   Input ~ 0
pinButton
Text GLabel 13025 8575 2    39   Output ~ 0
pinBuzzer
Text GLabel 13090 8875 2    39   Output ~ 0
pinChargingEnable
Text GLabel 13020 8775 2    39   Output ~ 0
pinUndervoltageSwitch
$Comp
L +3.3V #PWR011
U 1 1 55DB6879
P 12010 8830
F 0 "#PWR011" H 12010 8790 30  0001 C CNN
F 1 "+3.3V" V 12010 9000 30  0000 C CNN
F 2 "" H 12010 8830 60  0000 C CNN
F 3 "" H 12010 8830 60  0000 C CNN
	1    12010 8830
	1    0    0    1   
$EndComp
Wire Wire Line
	12010 8830 12010 8440
Wire Wire Line
	12010 8440 11375 8440
Wire Wire Line
	11375 6940 11430 6940
Wire Wire Line
	11375 8340 11490 8340
Wire Wire Line
	11490 8240 11375 8240
Text GLabel 11530 7740 2    39   Output ~ 0
SCL2
Text GLabel 11525 7640 2    39   BiDi ~ 0
SDA2
Text GLabel 11985 7240 2    39   Output ~ 0
TX2
Text GLabel 11985 7340 2    39   Input ~ 0
RX2
Text GLabel 11990 7640 2    39   BiDi ~ 0
SDA1
Text GLabel 11990 7740 2    39   Output ~ 0
SCL1
Text GLabel 11985 7440 2    39   Input ~ 0
TX1
Text GLabel 11985 7540 2    39   Input ~ 0
RX1
Connection ~ 11475 7640
Wire Wire Line
	11375 7540 11985 7540
Connection ~ 11475 7740
Wire Wire Line
	11920 7740 11990 7740
Wire Wire Line
	11920 7790 11920 7740
Wire Wire Line
	11475 7790 11920 7790
Wire Wire Line
	11475 7740 11475 7790
Wire Wire Line
	11920 7640 11990 7640
Wire Wire Line
	11920 7690 11920 7640
Wire Wire Line
	11475 7690 11920 7690
Wire Wire Line
	11375 7440 11985 7440
Wire Wire Line
	11375 7240 11985 7240
Wire Wire Line
	11475 7640 11475 7690
Wire Wire Line
	11375 7740 11530 7740
Wire Wire Line
	11375 7640 11525 7640
Wire Wire Line
	11375 7340 11985 7340
Wire Wire Line
	11375 7040 11985 7040
Wire Wire Line
	11480 8040 11375 8040
Wire Wire Line
	11375 8140 11490 8140
Wire Wire Line
	11375 7940 11475 7940
Wire Wire Line
	11375 7840 11490 7840
Wire Wire Line
	12945 8775 13020 8775
Wire Wire Line
	13090 8875 12945 8875
Wire Wire Line
	12945 8275 13005 8275
Wire Wire Line
	12945 8375 13020 8375
Wire Wire Line
	12945 8475 13015 8475
Wire Wire Line
	12945 8575 13025 8575
Wire Wire Line
	12945 8675 13005 8675
$Comp
L CONN_01X07 P4
U 1 1 55DD9CBD
P 12745 8575
F 0 "P4" H 12745 8975 50  0000 C CNN
F 1 "CONN_01X07" V 12845 8575 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07" H 12745 8575 60  0001 C CNN
F 3 "" H 12745 8575 60  0000 C CNN
F 4 "Value" H 12745 8575 60  0001 C CNN "Technische Daten"
F 5 "Value" H 12745 8575 60  0001 C CNN "Bestellnummer"
	1    12745 8575
	-1   0    0    1   
$EndComp
Text GLabel 11985 7040 2    39   Input ~ 0
Ausgangspannung
Text GLabel 13750 1060 2    39   Input ~ 0
Ausgangspannung
$Comp
L LM78xxTYPE IC2
U 1 1 561A5204
P 9080 5095
F 0 "IC2" H 9380 4795 30  0000 C CNN
F 1 "R-78E3.3-0.5" H 9130 5345 30  0000 C CNN
F 2 "Transistors_TO-220:TO-220_Neutral123_Vertical" H 9080 5095 60  0001 C CNN
F 3 "" H 9080 5095 60  0000 C CNN
F 4 "Value" H 9080 5095 60  0001 C CNN "Technische Daten"
F 5 "Value" H 9080 5095 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 9080 5095 60  0001 C CNN "Bauform"
F 7 "Value" H 9080 5095 60  0001 C CNN "Bestelllink"
	1    9080 5095
	1    0    0    -1  
$EndComp
Text Notes 10710 9385 0    60   ~ 0
An P50 Anschluß 4 nicht mit dem Arduino 3.3V verbinden.\ndie 3.3V werden von dem IC erzeugt weil die 3.3v des Arduino\nnicht ausreichen um das Wlan Modul zu versorgen\n
Text GLabel 8355 5095 0    39   Input ~ 0
Ausgangspannung
Wire Wire Line
	8480 5095 8355 5095
$Comp
L +3.3V #PWR012
U 1 1 561A5E21
P 9775 5095
F 0 "#PWR012" H 9775 5055 30  0001 C CNN
F 1 "+3.3V" V 9775 5265 30  0000 C CNN
F 2 "" H 9775 5095 60  0000 C CNN
F 3 "" H 9775 5095 60  0000 C CNN
	1    9775 5095
	0    1    -1   0   
$EndComp
Wire Wire Line
	9680 5095 9775 5095
$Comp
L GND #PWR013
U 1 1 561A6421
P 9080 5630
F 0 "#PWR013" H 9080 5630 30  0001 C CNN
F 1 "GND" H 9085 5480 30  0000 C CNN
F 2 "" H 9080 5630 60  0000 C CNN
F 3 "" H 9080 5630 60  0000 C CNN
F 4 "Value" H 9080 5630 60  0001 C CNN "Technische Daten"
F 5 "Value" H 9080 5630 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 9080 5630 60  0001 C CNN "Bauform"
F 7 "Value" H 9080 5630 60  0001 C CNN "Bestelllink"
	1    9080 5630
	1    0    0    -1  
$EndComp
Wire Wire Line
	9080 5630 9080 5545
Text Notes 8290 5945 0    60   ~ 0
Erzeugt die 3v für das wlan Modul
$EndSCHEMATC
