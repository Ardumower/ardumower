EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-rescue
LIBS:power
LIBS:device
LIBS:Zimprich
LIBS:conn
LIBS:transistors
LIBS:cmos_ieee
LIBS:cmos4000
LIBS:switches
LIBS:rfcom
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 28
Title "Ardumower shield SVN Version"
Date "2016-10-28"
Rev "1.3"
Comp "ML AG JL UZ"
Comment1 "Unterspannungsschutz von AlexanderG"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 4240 2790 0    39   Output ~ 0
pinChargeVoltage
Text GLabel 5020 3170 3    39   Output ~ 0
pinChargeCurrent
$Comp
L ACS712 U3
U 1 1 5417150B
P 5020 2520
F 0 "U3" H 5020 2770 50  0000 C CNN
F 1 "INA169" H 5020 2270 50  0000 C CNN
F 2 "Zimprich:INA169" H 5020 2520 60  0001 C CNN
F 3 "" H 5020 2520 60  0000 C CNN
F 4 "Value" H 5020 2520 60  0001 C CNN "Bestellnummer"
	1    5020 2520
	0    -1   1    0   
$EndComp
Text Notes 7035 1290 0    99   ~ 0
Batterie\n
$Comp
L RELAY_2RT K3
U 1 1 54A679F2
P 6330 2540
F 0 "K3" H 6280 2940 70  0000 C CNN
F 1 "RELAY_2RT" H 6480 2040 70  0000 C CNN
F 2 "Zimprich:Relais_DPDT_Schrack-RT2_RM5mm_3D_Kontaktbelegung_geändert_FIN40.52.9_6V" H 6330 2540 60  0001 C CNN
F 3 "" H 6330 2540 60  0000 C CNN
F 4 "Siehe Bauteileigenschaften" H 6330 2540 60  0001 C CNN "Bestellnummer"
F 5 "http://www.reichelt.de/Print-Steckrelais/FIN-40-52-9-6V/3/index.html?&ACTION=3&LA=2&ARTICLE=8108&GROUPID=3293&artnr=FIN+40.52.9+6V" H 6330 2540 60  0001 C CNN "Quelle"
F 6 "R: FIN 40.52.9 24V" H 6330 2540 60  0001 C CNN "Bestellnummer 24V"
F 7 "R: FIN 40.52.9 12V" H 6330 2540 60  0001 C CNN "Bestellnummer 12V"
F 8 "R: FIN 40.52.9 6V" H 6330 2540 60  0001 C CNN "Bestellnummer 6V"
F 9 "R: FIN 95.15.2" H 6330 2540 60  0001 C CNN "Printfassung für Relais"
	1    6330 2540
	1    0    0    -1  
$EndComp
$Comp
L F_10A EF1
U 1 1 54A79B5A
P 2055 2040
F 0 "EF1" H 2055 2105 40  0000 C CNN
F 1 "F_5A" H 2055 1980 40  0000 C CNN
F 2 "Zimprich:Fuseholder5x20_vert_closed_Bulgin_FX0456" H 2055 2040 60  0001 C CNN
F 3 "" H 2055 2040 60  0000 C CNN
F 4 "R: PL 112000" H 2055 2040 60  0001 C CNN "Bestellnummer"
	1    2055 2040
	-1   0    0    1   
$EndComp
$Comp
L F_10A EF2
U 1 1 54A7AB0D
P 7350 2085
F 0 "EF2" V 7280 2195 40  0000 C CNN
F 1 "F_10A" V 7350 2230 40  0000 C CNN
F 2 "Zimprich:Fuseholder5x20_vert_closed_Bulgin_FX0456" H 7350 2085 60  0001 C CNN
F 3 "" H 7350 2085 60  0000 C CNN
F 4 "R: PL 112000" H 7350 2085 60  0001 C CNN "Bestellnummer"
	1    7350 2085
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-ardumower_mega_shield_svn R18
U 1 1 54B46970
P 5280 3920
F 0 "R18" V 5360 3920 40  0000 C CNN
F 1 "2k2" V 5287 3921 40  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5210 3920 30  0001 C CNN
F 3 "" H 5280 3920 30  0000 C CNN
	1    5280 3920
	0    -1   -1   0   
$EndComp
Text GLabel 4870 3920 0    60   Output ~ 0
pinChargingEnable
Text Notes 5980 3490 0    39   ~ 0
Laderelais Spulenspannung 5V\noder Variabel\nEingang Spulenspannung\nkann über Vorwiderspannung\nangepasst werden\ndurch Ladespannung
Text Notes 3495 1995 0    39   ~ 0
Station LED\nbzw:\nGrundlast\nPerimetersender
Text Notes 9055 -450 0    60   ~ 0
LED Anzeigen - Hardware:\n\nLed 3V grün -   Betriebsanzeige Versorgungsspannung\nLED 24V grün - Betriebsanzeige Versorgungsspannung R2 für 12 V anpassen\nLED 5V grün -   Betriebsanzeige Versorgungsspannung\nLED Station - gelb - Statusanzeige ob Mover in Ladestation\n\n----------------------------------------------------------\n\nLED Anzeigen - Software:\n\nDual LED z.B:\nDual LED grün. Dauerlicht - Mover innerhalb Perimeter\nDual LED grün+rot = Orange - Dauerlicht Mover außerhalb Perimeter\nDual LED grün+rot = Orange - Blinkt Mover findet  Perimeter nicht oder sucht danach\nDual LED rot =  Blinkt Fehler kurzseitig Überlast Antriebmotor Treibe oder Mähmotor. \nDual LED rot - Dauerlicht - Fehler muß für weiterfahren durch drücken \nvon Button zurückgesetzt werden\n----------------------------------------------------------\n\nLED Status - grün Dauerlicht - warte auf Eingabe\n\nLED Status - grün blinken 1 bis 5 mal hintereinander\nmit länger Pause dazwischen für Anzeige in welchen\nBetriebsmodi sich der Mover befindet
Text Notes 2880 -350 0    60   ~ 0
LED Rechner:\nhttp://www.elektronik-kompendium.de/sites/bau/1109111.htm\n\nZ-Dioden Rechner:\nhttp://www.dieelektronikerseite.de/Tools/Zenerdiode.htm
Text Notes 12545 3845 0    157  ~ 0
--------------- Änderungen am Board ---------------\n09.03.2016\nok - fehlende Lötbrücke geschlossen\nok - 4 Widerstände Odemetrie eingefügt\nok - 1 Widerstand Mähmotordrehzahl\nok - 1 Stiftleiste abgriff 9V\nok - 1 Aref Kondensator eingefügt\n1 Klemmanschluss für das Unterspannungsabschaltung Board hinzugefügt\n\nok DiodenD1-D10 umgeändert\nAnnode und Kathode waren vertauscht\nJetzt nach neuer Kicad Norm\n\nP45 P46 und U10 entfernt Platz wird benötigt für klemmanschluss Unterspannung\nR19 enfernt und mit Diode D11 ersetzt\nDiode D2 entfernt Mähteller\nZD1, ZD2, ZD3 und R24, R25, R26 bei DC Wandler entfernt\nIna U5 und C6 entfernt\nLAderegelung entfernt D7, C1, C4, U4, R17,RV1, D3\nR22 und D8 entfernt LED BT Modul\n\nJP4, JP5 JP6, JP7 entfernt\nD4 JP17 entfernt\nPufferKondensator C5 entfernt
$Sheet
S 9205 3380 1240 170 
U 57D95AF0
F0 "Motortreiber" 60
F1 "Motortreiber.sch" 60
F2 "+24V" I L 9205 3460 60 
$EndSheet
$Sheet
S 1920 6920 850  170 
U 57DA6878
F0 "Wlan_BT_GPS" 60
F1 "Wlan_BT_GPS.sch" 60
$EndSheet
$Sheet
S 890  6920 855  170 
U 57DBE57B
F0 "Leuchtdioden" 60
F1 "Leuchtdioden.sch" 60
$EndSheet
$Sheet
S 1920 7275 850  170 
U 57DC7E7B
F0 "Anschlußstecker" 60
F1 "Anschlußstecker.sch" 60
$EndSheet
$Sheet
S 9200 2925 1240 170 
U 57DF5E8A
F0 "Spannungsversorgung" 60
F1 "Spannungsversorgung.sch" 60
F2 "Spannungsaufbereitung" I L 9200 3010 60 
$EndSheet
$Sheet
S 3235 7280 1240 170 
U 57DFE528
F0 "Arduino_Mega" 60
F1 "Arduino_Mega.sch" 60
$EndSheet
$Sheet
S 890  7280 850  170 
U 57E12859
F0 "Bohrlöcher" 60
F1 "Bohrlöcher.sch" 60
$EndSheet
$Comp
L GND #PWR01
U 1 1 57DDC12E
P 5930 4420
F 0 "#PWR01" H 5930 4170 50  0001 C CNN
F 1 "GND" H 5935 4247 50  0000 C CNN
F 2 "" H 5930 4420 50  0000 C CNN
F 3 "" H 5930 4420 50  0000 C CNN
	1    5930 4420
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 57DDCE0C
P 4400 3230
F 0 "#PWR02" H 4400 2980 50  0001 C CNN
F 1 "GND" H 4405 3057 50  0000 C CNN
F 2 "" H 4400 3230 50  0000 C CNN
F 3 "" H 4400 3230 50  0000 C CNN
	1    4400 3230
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57DDD4A8
P 1565 2250
F 0 "#PWR03" H 1565 2000 50  0001 C CNN
F 1 "GND" H 1570 2077 50  0000 C CNN
F 2 "" H 1565 2250 50  0000 C CNN
F 3 "" H 1565 2250 50  0000 C CNN
	1    1565 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57DE0396
P 7250 1890
F 0 "#PWR04" H 7250 1640 50  0001 C CNN
F 1 "GND" H 7255 1717 50  0000 C CNN
F 2 "" H 7250 1890 50  0000 C CNN
F 3 "" H 7250 1890 50  0000 C CNN
	1    7250 1890
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR05
U 1 1 57DE1118
P 8845 2550
F 0 "#PWR05" H 8845 2400 50  0001 C CNN
F 1 "+24V" V 8845 2765 50  0000 C CNN
F 2 "" H 8845 2550 50  0000 C CNN
F 3 "" H 8845 2550 50  0000 C CNN
	1    8845 2550
	0    -1   -1   0   
$EndComp
$Sheet
S 9210 2275 1125 400 
U 57DD8E0C
F0 "USpannungAB" 60
F1 "USpannungAB.sch" 60
F2 "Batterieeingang 24V" I L 9210 2390 60 
F3 "Batterieausgang 24V" O L 9210 2550 60 
$EndSheet
$Comp
L CONN_01X02 P43
U 1 1 57DEE5A7
P 7300 1605
F 0 "P43" V 7490 1605 50  0000 C CNN
F 1 "Battery" V 7400 1605 50  0000 C CNN
F 2 "Zimprich:Anschlussklemme_RM5,08-RM7,62" H 7219 1422 50  0001 C CNN
F 3 "" H 7300 1605 50  0000 C CNN
F 4 "Value" H 7219 1415 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7219 1415 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7219 1415 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7300 1605 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7300 1605 60  0001 C CNN "Bauform"
	1    7300 1605
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P42
U 1 1 57DEF264
P 1345 2090
F 0 "P42" H 1425 2030 50  0000 L CNN
F 1 "Charger" H 1425 2090 50  0000 L CNN
F 2 "Zimprich:Anschlussklemme_RM5,08-RM7,62" V 1173 2218 50  0001 L CNN
F 3 "" H 1345 2090 50  0000 C CNN
F 4 "Value" V 1233 2218 60  0001 L CNN "Gehäuseart"
F 5 "Value" V 1180 2218 60  0001 L CNN "Bestelllink"
F 6 "Value" V 1127 2218 60  0001 L CNN "Technische Daten"
F 7 "Value" H 1345 2090 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1345 2090 60  0001 C CNN "Bauform"
	1    1345 2090
	-1   0    0    1   
$EndComp
$Sheet
S 4625 6935 965  170 
U 57E1969E
F0 "I2C" 60
F1 "I2C.sch" 60
$EndSheet
Text Notes 19790 5175 0    118  ~ 0
[20:50:34 | Bearbeitet 20:51:30] Jürgen Lange: setze für den dcdc einen 78s05 ein oder die die ich auf der BumperDuino nehme LM2940CS-5.0 um das bt zuversorgen für die Versorgung vom wlan einen 3,3v low drop\n[20:51:20] Kurzschuss - Uwe: also die 5V nicht vom Mega holen bzw die 3,3V\n[20:51:44] Jürgen Lange: für bt und wlan nicht\n[20:51:54] Jürgen Lange: für den rest okay\n[20:52:01] Kurzschuss - Uwe: okay\n[20:53:21] Jürgen Lange: setze bei allen Wandlern ob dcdc oder 78xx revers Dioden und rückführ Dioden die 78xx oder ähnlich kommen gleich vom 9v dcdc\n[20:54:26] Kurzschuss - Uwe: Ich übernehme die Schaltung vom Bumberduino\n\n\n\n[11:55:48] Jürgen Lange: im Klartext die Spannungen vom längsregler nur für Versorgung von bt etc nehmen gaaaaanz wichtig sonst haust du den due weg wenn jemand den usb stecker steckt\n[11:56:29] Jürgen Lange: der mega könnte auch aufgeben aber das habe ich noch nicht geprüft
Text GLabel 1775 2170 3    39   Input ~ 0
Charg_Pin_+
$Comp
L GND #PWR06
U 1 1 57E3DCAC
P 5120 3070
F 0 "#PWR06" H 5120 2820 50  0001 C CNN
F 1 "GND" H 5150 2925 50  0000 C CNN
F 2 "" H 5120 3070 50  0000 C CNN
F 3 "" H 5120 3070 50  0000 C CNN
	1    5120 3070
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C3
U 1 1 57E3E9D5
P 4735 3325
F 0 "C3" H 4823 3371 50  0000 L CNN
F 1 "10uF" H 4823 3280 50  0000 L CNN
F 2 "Zimprich:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 4735 3325 50  0001 C CNN
F 3 "" H 4735 3325 50  0001 C CNN
F 4 "Value" H 4735 3325 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4735 3325 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4735 3325 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4735 3325 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4735 3325 60  0001 C CNN "Bauform"
	1    4735 3325
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 57E3F322
P 4735 3475
F 0 "#PWR07" H 4735 3225 50  0001 C CNN
F 1 "GND" H 4765 3330 50  0000 C CNN
F 2 "" H 4735 3475 50  0000 C CNN
F 3 "" H 4735 3475 50  0000 C CNN
	1    4735 3475
	1    0    0    -1  
$EndComp
$Comp
L R_Small R9
U 1 1 57E42699
P 4400 2460
F 0 "R9" H 4459 2506 50  0000 L CNN
F 1 "47K 0,1%" H 4459 2415 50  0000 L CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_0805to1206_RM10_HandSoldering" H 4459 2634 50  0001 L CNN
F 3 "" H 4400 2460 50  0001 C CNN
F 4 "Value" H 4459 2535 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4459 2429 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4459 2323 60  0001 L CNN "Technische Daten"
F 7 "R: MPR 47,0K" H 4459 2217 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4459 2111 60  0001 L CNN "Bauform"
	1    4400 2460
	-1   0    0    -1  
$EndComp
$Comp
L R_Small R10
U 1 1 57E43622
P 4400 3080
F 0 "R10" H 4458 3126 50  0000 L CNN
F 1 "5,10K 0,1%" H 4458 3035 50  0000 L CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_0805to1206_RM10_HandSoldering" H 4459 3254 50  0001 L CNN
F 3 "" H 4400 3080 50  0001 C CNN
F 4 "Value" H 4459 3155 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 4459 3049 60  0001 L CNN "Bestelllink"
F 6 "Value" H 4459 2943 60  0001 L CNN "Technische Daten"
F 7 "R: MPR 5,10K" H 4459 2837 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 4459 2731 60  0001 L CNN "Bauform"
	1    4400 3080
	-1   0    0    -1  
$EndComp
Text GLabel 8215 3065 0    39   Output ~ 0
pinBatteryVoltage
$Comp
L GND #PWR08
U 1 1 57E498AE
P 8375 3505
F 0 "#PWR08" H 8375 3255 50  0001 C CNN
F 1 "GND" H 8380 3332 50  0000 C CNN
F 2 "" H 8375 3505 50  0000 C CNN
F 3 "" H 8375 3505 50  0000 C CNN
	1    8375 3505
	1    0    0    -1  
$EndComp
$Comp
L R_Small R12
U 1 1 57E498B9
P 8375 2735
F 0 "R12" H 8434 2781 50  0000 L CNN
F 1 "47K 0,1%" H 8434 2690 50  0000 L CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_0805to1206_RM10_HandSoldering" H 8434 2909 50  0001 L CNN
F 3 "" H 8375 2735 50  0001 C CNN
F 4 "Value" H 8434 2810 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 8434 2704 60  0001 L CNN "Bestelllink"
F 6 "Value" H 8434 2598 60  0001 L CNN "Technische Daten"
F 7 "R: MPR 47,0K" H 8434 2492 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 8434 2386 60  0001 L CNN "Bauform"
	1    8375 2735
	-1   0    0    -1  
$EndComp
$Comp
L R_Small R13
U 1 1 57E498C4
P 8375 3355
F 0 "R13" H 8433 3401 50  0000 L CNN
F 1 "5,10K 0,1%" H 8433 3310 50  0000 L CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_0805to1206_RM10_HandSoldering" H 8434 3529 50  0001 L CNN
F 3 "" H 8375 3355 50  0001 C CNN
F 4 "Value" H 8434 3430 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 8434 3324 60  0001 L CNN "Bestelllink"
F 6 "Value" H 8434 3218 60  0001 L CNN "Technische Daten"
F 7 "R: MPR 5,10K" H 8434 3112 60  0001 L CNN "Bestellnummer"
F 8 "Value" H 8434 3006 60  0001 L CNN "Bauform"
	1    8375 3355
	-1   0    0    -1  
$EndComp
$Comp
L D D9
U 1 1 57E4C8A2
P 7815 2390
F 0 "D9" H 7815 2235 39  0000 C CNN
F 1 "MBR 1045" H 7815 2295 39  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_TO-220_Vertical" H 7815 2513 50  0001 C CNN
F 3 "Value" H 7815 2390 50  0001 C CNN
F 4 "Value" H 7815 2521 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7815 2521 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7815 2390 60  0001 C CNN "Technische Daten"
F 7 "R: MBR 1045" H 7815 2390 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7815 2390 60  0001 C CNN "Bauform"
	1    7815 2390
	-1   0    0    1   
$EndComp
Text Notes 1085 1810 0    99   ~ 0
Akku\n
$Sheet
S 2325 1960 915  165 
U 57E646FF
F0 "VerpolungsschutzLade." 39
F1 "VerpolungsschutzLade.sch" 39
F2 "Ausgang" O R 3240 2040 39 
F3 "Eingang" I L 2325 2040 39 
$EndSheet
$Comp
L D D1
U 1 1 57E6BA60
P 7350 2865
F 0 "D1" V 7290 3110 39  0000 C CNN
F 1 "MBR 1045" V 7350 3125 39  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_TO-220_Vertical" H 7350 2988 50  0001 C CNN
F 3 "Value" H 7350 2865 50  0001 C CNN
F 4 "Value" H 7350 2996 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7350 2996 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7350 2865 60  0001 C CNN "Technische Daten"
F 7 "R: MBR 1045" H 7350 2865 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7350 2865 60  0001 C CNN "Bauform"
	1    7350 2865
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 57E6CA33
P 7350 3065
F 0 "#PWR09" H 7350 2815 50  0001 C CNN
F 1 "GND" H 7355 2892 50  0000 C CNN
F 2 "" H 7350 3065 50  0000 C CNN
F 3 "" H 7350 3065 50  0000 C CNN
	1    7350 3065
	1    0    0    -1  
$EndComp
Text Notes 7090 3485 0    60   ~ 0
Verpolschutz\nBatterie
$Sheet
S 3390 2270 150  500 
U 57E81EBA
F0 "Stationsled" 39
F1 "Stationsled.sch" 39
F2 "LED+" I T 3465 2270 39 
$EndSheet
$Comp
L D D10
U 1 1 57E925D4
P 5680 3085
F 0 "D10" V 5625 2960 39  0000 C CNN
F 1 "1N4148 SMD" V 5685 2840 39  0000 C CNN
F 2 "Zimprich:D_0603" H 5680 3208 50  0001 C CNN
F 3 "" H 5680 3085 50  0001 C CNN
F 4 "Value" H 5680 3428 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-4148-SMD/3/index.html?&ACTION=3&LA=446&ARTICLE=18403&artnr=1N+4148+SMD&SEARCH=1n4148" H 5680 3322 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 5680 3216 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 5680 3085 60  0001 C CNN "Bestellnummer"
F 8 "Mini Melf" H 5680 3085 60  0001 C CNN "Bauform"
	1    5680 3085
	0    1    1    0   
$EndComp
Text Notes 6055 4325 0    60   ~ 0
BC 547 ersetzt mit BC847 SMD\n??\n
$Comp
L BC849 Q1
U 1 1 57F1C5EE
P 5830 3920
F 0 "Q1" H 6021 4011 50  0000 L CNN
F 1 "BC847" H 6021 3920 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6021 3829 50  0000 L CIN
F 3 "" H 5830 3920 50  0000 L CNN
F 4 "Value" H 5830 3920 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5830 3920 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5830 3920 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5830 3920 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5830 3920 60  0001 C CNN "Bauform"
	1    5830 3920
	1    0    0    -1  
$EndComp
Text GLabel 4920 3130 3    39   Input ~ 0
IOREF
Text GLabel 3810 2270 3    39   Input ~ 0
StationLed
Wire Wire Line
	4400 2560 4400 2980
Wire Wire Line
	7250 1890 7250 1805
Wire Wire Line
	5020 2920 5020 3170
Wire Wire Line
	4400 3180 4400 3230
Wire Wire Line
	5930 4120 5930 4420
Wire Wire Line
	7350 1885 7350 1805
Wire Wire Line
	5680 2790 5930 2790
Wire Wire Line
	5530 3920 5630 3920
Wire Wire Line
	5930 2890 5930 3720
Wire Wire Line
	4870 3920 5030 3920
Wire Wire Line
	5680 3235 5680 3415
Wire Wire Line
	5680 3415 5930 3415
Connection ~ 5930 3415
Wire Wire Line
	5865 2590 5930 2590
Wire Wire Line
	5865 2040 5865 2590
Wire Wire Line
	5930 2290 5865 2290
Connection ~ 5865 2290
Wire Wire Line
	6730 2390 7665 2390
Wire Wire Line
	5120 2920 5120 3070
Wire Wire Line
	4920 2920 4920 3130
Wire Wire Line
	4735 3425 4735 3475
Wire Wire Line
	4735 3225 4735 2995
Wire Wire Line
	4735 2995 4920 2995
Connection ~ 4920 2995
Wire Wire Line
	4240 2790 4400 2790
Connection ~ 4400 2790
Wire Wire Line
	3240 2040 4920 2040
Wire Wire Line
	5120 2040 5865 2040
Wire Wire Line
	4400 2040 4400 2360
Connection ~ 4400 2040
Wire Wire Line
	3465 2270 3465 2040
Connection ~ 3465 2040
Wire Wire Line
	1545 2040 1855 2040
Wire Wire Line
	1565 2250 1565 2140
Wire Wire Line
	1565 2140 1545 2140
Wire Wire Line
	1775 2170 1775 2040
Connection ~ 1775 2040
Wire Wire Line
	8375 2835 8375 3255
Wire Wire Line
	8375 3455 8375 3505
Wire Wire Line
	8215 3065 8375 3065
Connection ~ 8375 3065
Connection ~ 7350 2390
Wire Wire Line
	7965 2390 9210 2390
Wire Wire Line
	8845 2550 9210 2550
Connection ~ 9010 2550
Wire Wire Line
	2255 2040 2325 2040
Wire Wire Line
	9010 3010 9200 3010
Wire Wire Line
	7350 3015 7350 3065
Wire Wire Line
	5120 2120 5120 2040
Wire Wire Line
	4920 2040 4920 2120
Wire Wire Line
	8375 2635 8375 2390
Connection ~ 8375 2390
Wire Wire Line
	5680 2040 5680 2935
Connection ~ 5680 2040
Connection ~ 5680 2790
Wire Wire Line
	6730 2690 6880 2690
Wire Wire Line
	6880 2690 6880 2390
Connection ~ 6880 2390
Wire Wire Line
	3810 2270 3810 2040
Connection ~ 3810 2040
Wire Wire Line
	7350 2285 7350 2715
NoConn ~ 6730 2490
NoConn ~ 6730 2190
Wire Wire Line
	9010 3460 9205 3460
Connection ~ 9010 3010
$Comp
L CONN_01X02 P49
U 1 1 5818E3A7
P 8775 3265
F 0 "P49" H 8855 3205 50  0000 L CNN
F 1 "Break" H 8855 3265 50  0000 L CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" V 8603 3393 50  0001 L CNN
F 3 "" H 8775 3265 50  0000 C CNN
F 4 "Value" V 8663 3393 60  0001 L CNN "Gehäuseart"
F 5 "Value" V 8610 3393 60  0001 L CNN "Bestelllink"
F 6 "Value" V 8557 3393 60  0001 L CNN "Technische Daten"
F 7 "Value" H 8775 3265 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8775 3265 60  0001 C CNN "Bauform"
	1    8775 3265
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9010 2550 9010 3460
Wire Wire Line
	9010 3215 8975 3215
Wire Wire Line
	9010 3315 8975 3315
Connection ~ 9010 3315
Connection ~ 9010 3215
Text Notes 8595 3825 0    39   ~ 0
Unterbrechung der Motortreiber\nbei Benutzung muss Leiterbahn unterbrochen werden\nevl noch ändern und Klemme gleich vorsehen mit Drahtbrücke?
Text Notes -5870 1415 0    79   ~ 0
Kontrolle Funktion Ultraschall\nKontrolle RC Fernbedienung\nKontrolle Unterspannunsabschaltung ob sie mit 3V an bleibt\nRelais schaltung ändern damit nur noch 1 Relais notwendig ist\nUDN 2981 ersetzen durch SMD Bauteil evl TD 62783 AFWG :: Treiber-IC, SO-18W\nOdemetrie kontrollieren\nIC2 Bus Kontrollieren\nSpannungsaufbereitung evl ändern mit anderen DC wandlern bis 30V\n\nBauteile siehe Links
Text Notes -5910 -130 0    59   ~ 0
https://www.reichelt.de/ICs-TLC-TSA-/TS-2940-CP33/3/index.html?ACTION=3&LA=5700&ARTICLE=115975&GROUPID=5480&artnr=TS+2940+CP33\n\nhttps://www.reichelt.de/ICs-TLC-TSA-/TS-2940-CP50/3/index.html?ACTION=3&LA=5700&ARTICLE=115976&GROUPID=5480&artnr=TS+2940+CP50\n\nhttps://www.reichelt.de/ICs-TA-TL-/TD-62783-AFWG/3/index.html?ACTION=3&LA=446&ARTICLE=188954&GROUPID=5479&artnr=TD+62783+AFWG&SEARCH=TD62783
$EndSCHEMATC
