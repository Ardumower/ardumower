EESchema Schematic File Version 2
LIBS:Wlan_ESP8266
LIBS:power
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 25
Title "Ardumower Shield - Stiftleisten"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_4 P6
U 1 1 553DFED0
P 1040 1465
F 0 "P6" V 990 1465 50  0000 C CNN
F 1 "Lawn sens" V 1090 1465 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x04" H 1040 1465 60  0001 C CNN
F 3 "" H 1040 1465 60  0000 C CNN
F 4 "Value" H 1040 1465 60  0001 C CNN "Bestellnummer"
	1    1040 1465
	-1   0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 553DFF72
P 1765 1315
F 0 "R4" V 1845 1315 40  0000 C CNN
F 1 "2M2" V 1772 1316 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 1695 1315 30  0001 C CNN
F 3 "" H 1765 1315 30  0000 C CNN
	1    1765 1315
	0    -1   1    0   
$EndComp
$Comp
L R R3
U 1 1 553DFFFF
P 1765 1515
F 0 "R3" V 1845 1515 40  0000 C CNN
F 1 "2M2" V 1772 1516 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 1695 1515 30  0001 C CNN
F 3 "" H 1765 1515 30  0000 C CNN
F 4 "Value" H 1765 1515 60  0001 C CNN "Bestellnummer"
	1    1765 1515
	0    -1   1    0   
$EndComp
Text GLabel 2140 1315 2    39   Input ~ 0
pinLawnFrontSend
Text GLabel 2140 1415 2    39   Output ~ 0
pinLawnFrontRecv
Text GLabel 2140 1515 2    39   Input ~ 0
pinLawnBackSend
Text GLabel 2140 1615 2    39   Output ~ 0
pinLawnBackRecv
$Comp
L +5V #PWR071
U 1 1 553E3A32
P 1515 795
F 0 "#PWR071" H 1515 645 60  0001 C CNN
F 1 "+5V" V 1515 1015 60  0000 C CNN
F 2 "" H 1515 795 60  0000 C CNN
F 3 "" H 1515 795 60  0000 C CNN
	1    1515 795 
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR072
U 1 1 553E3A49
P 1510 895
F 0 "#PWR072" H 1510 645 60  0001 C CNN
F 1 "GND" V 1510 670 60  0000 C CNN
F 2 "" H 1510 895 60  0000 C CNN
F 3 "" H 1510 895 60  0000 C CNN
	1    1510 895 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P19
U 1 1 553E3A60
P 1035 895
F 0 "P19" V 985 895 50  0000 C CNN
F 1 "Tilt sens" V 1085 895 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 1035 895 60  0001 C CNN
F 3 "" H 1035 895 60  0000 C CNN
F 4 "Value" H 1035 895 60  0001 C CNN "Bestellnummer"
	1    1035 895 
	-1   0    0    -1  
$EndComp
Text GLabel 1515 995  2    39   Output ~ 0
pinTilt
$Comp
L +5V #PWR073
U 1 1 553E7056
P 1510 1855
F 0 "#PWR073" H 1510 1705 60  0001 C CNN
F 1 "+5V" V 1510 2075 60  0000 C CNN
F 2 "" H 1510 1855 60  0000 C CNN
F 3 "" H 1510 1855 60  0000 C CNN
	1    1510 1855
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR074
U 1 1 553E705C
P 1505 1955
F 0 "#PWR074" H 1505 1705 60  0001 C CNN
F 1 "GND" V 1505 1730 60  0000 C CNN
F 2 "" H 1505 1955 60  0000 C CNN
F 3 "" H 1505 1955 60  0000 C CNN
	1    1505 1955
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P4
U 1 1 553E7063
P 1030 1955
F 0 "P4" V 980 1955 50  0000 C CNN
F 1 "MowRpm" V 1080 1955 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 1030 1955 60  0001 C CNN
F 3 "" H 1030 1955 60  0000 C CNN
F 4 "Value" H 1030 1955 60  0001 C CNN "Bestellnummer"
	1    1030 1955
	-1   0    0    -1  
$EndComp
Text GLabel 1510 2055 2    39   Output ~ 0
pinMotorMowRpm
$Comp
L +5V #PWR075
U 1 1 553E917A
P 1505 2265
F 0 "#PWR075" H 1505 2115 60  0001 C CNN
F 1 "+5V" V 1505 2485 60  0000 C CNN
F 2 "" H 1505 2265 60  0000 C CNN
F 3 "" H 1505 2265 60  0000 C CNN
	1    1505 2265
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR076
U 1 1 553E9180
P 1500 2365
F 0 "#PWR076" H 1500 2115 60  0001 C CNN
F 1 "GND" V 1500 2140 60  0000 C CNN
F 2 "" H 1500 2365 60  0000 C CNN
F 3 "" H 1500 2365 60  0000 C CNN
	1    1500 2365
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P41
U 1 1 553E9187
P 1025 2365
F 0 "P41" V 975 2365 50  0000 C CNN
F 1 "Rain" V 1075 2365 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 1025 2365 60  0001 C CNN
F 3 "" H 1025 2365 60  0000 C CNN
F 4 "Value" H 1025 2365 60  0001 C CNN "Bestellnummer"
	1    1025 2365
	-1   0    0    -1  
$EndComp
Text GLabel 1505 2465 2    39   Output ~ 0
pinRain
$Comp
L +5V #PWR077
U 1 1 553EA88B
P 1500 2645
F 0 "#PWR077" H 1500 2495 60  0001 C CNN
F 1 "+5V" V 1500 2865 60  0000 C CNN
F 2 "" H 1500 2645 60  0000 C CNN
F 3 "" H 1500 2645 60  0000 C CNN
	1    1500 2645
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR078
U 1 1 553EA891
P 1495 2745
F 0 "#PWR078" H 1495 2495 60  0001 C CNN
F 1 "GND" V 1495 2520 60  0000 C CNN
F 2 "" H 1495 2745 60  0000 C CNN
F 3 "" H 1495 2745 60  0000 C CNN
	1    1495 2745
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P14
U 1 1 553EA898
P 1020 2745
F 0 "P14" V 970 2745 50  0000 C CNN
F 1 "Meas V" V 1070 2745 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 1020 2745 60  0001 C CNN
F 3 "" H 1020 2745 60  0000 C CNN
F 4 "Value" H 1020 2745 60  0001 C CNN "Bestellnummer"
	1    1020 2745
	-1   0    0    -1  
$EndComp
Text GLabel 1500 2845 2    39   Output ~ 0
Voltage measurement
$Comp
L CONN_4 P11
U 1 1 553ECCEE
P 1020 3200
F 0 "P11" V 970 3200 50  0000 C CNN
F 1 "Bumper" V 1070 3200 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x04" H 1020 3200 60  0001 C CNN
F 3 "" H 1020 3200 60  0000 C CNN
F 4 "Value" H 1020 3200 60  0001 C CNN "Bestellnummer"
	1    1020 3200
	-1   0    0    -1  
$EndComp
Text GLabel 1495 3250 2    39   Output ~ 0
pinBumperRight
Text GLabel 1495 3350 2    39   Output ~ 0
pinBumperLeft
$Comp
L GND #PWR079
U 1 1 553ECD4C
P 1495 3050
F 0 "#PWR079" H 1495 2800 60  0001 C CNN
F 1 "GND" V 1495 2825 60  0000 C CNN
F 2 "" H 1495 3050 60  0000 C CNN
F 3 "" H 1495 3050 60  0000 C CNN
	1    1495 3050
	0    -1   -1   0   
$EndComp
$Comp
L CONN_5 P40
U 1 1 553EF93A
P 1010 3770
F 0 "P40" V 960 3770 50  0000 C CNN
F 1 "UserSwitsch" V 1060 3770 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x05" H 1010 3770 60  0001 C CNN
F 3 "" H 1010 3770 60  0000 C CNN
F 4 "Value" H 1010 3770 60  0001 C CNN "Bestellnummer"
	1    1010 3770
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR080
U 1 1 553F049F
P 1540 3570
F 0 "#PWR080" H 1540 3420 60  0001 C CNN
F 1 "+5V" V 1540 3790 60  0000 C CNN
F 2 "" H 1540 3570 60  0000 C CNN
F 3 "" H 1540 3570 60  0000 C CNN
	1    1540 3570
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR081
U 1 1 553F04A5
P 1535 3670
F 0 "#PWR081" H 1535 3420 60  0001 C CNN
F 1 "GND" V 1535 3445 60  0000 C CNN
F 2 "" H 1535 3670 60  0000 C CNN
F 3 "" H 1535 3670 60  0000 C CNN
	1    1535 3670
	0    -1   -1   0   
$EndComp
Text GLabel 1540 3770 2    39   Output ~ 0
pinUserSwitch1
Text GLabel 1540 3870 2    39   Output ~ 0
pinUserSwitch2
Text GLabel 1540 3970 2    39   Output ~ 0
pinUserSwitch3
$Comp
L CONN_6 P13
U 1 1 553F19AF
P 995 4490
F 0 "P13" V 945 4490 60  0000 C CNN
F 1 "RC Remote" V 1045 4490 60  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x06" H 995 4490 60  0001 C CNN
F 3 "" H 995 4490 60  0000 C CNN
F 4 "Value" H 995 4490 60  0001 C CNN "Bestellnummer"
	1    995  4490
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR082
U 1 1 553F2197
P 1485 4240
F 0 "#PWR082" H 1485 4090 60  0001 C CNN
F 1 "+5V" V 1485 4460 60  0000 C CNN
F 2 "" H 1485 4240 60  0000 C CNN
F 3 "" H 1485 4240 60  0000 C CNN
	1    1485 4240
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR083
U 1 1 553F219D
P 1480 4340
F 0 "#PWR083" H 1480 4090 60  0001 C CNN
F 1 "GND" V 1480 4115 60  0000 C CNN
F 2 "" H 1480 4340 60  0000 C CNN
F 3 "" H 1480 4340 60  0000 C CNN
	1    1480 4340
	0    -1   -1   0   
$EndComp
Text GLabel 1800 4440 2    39   Output ~ 0
pinRemoteMow
Text GLabel 1800 4540 2    39   Output ~ 0
pinRemoteSteer
Text GLabel 1800 4640 2    39   Output ~ 0
pinRemoteSpeed
Text GLabel 1800 4740 2    39   Output ~ 0
pinRemoteSwitch
$Comp
L CONN_01X08 P34
U 1 1 553FB959
P 5585 1220
F 0 "P34" H 5585 1670 50  0000 C CNN
F 1 "Voltage header 3,3V" V 5685 1220 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 5585 1220 60  0001 C CNN
F 3 "" H 5585 1220 60  0000 C CNN
F 4 "Value" H 5585 1220 60  0001 C CNN "Bestellnummer"
	1    5585 1220
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR084
U 1 1 553FC409
P 5895 1705
F 0 "#PWR084" H 5895 1665 30  0001 C CNN
F 1 "+3.3V" H 5895 1815 30  0000 C CNN
F 2 "" H 5895 1705 60  0000 C CNN
F 3 "" H 5895 1705 60  0000 C CNN
	1    5895 1705
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X08 P33
U 1 1 553FE0F1
P 4835 1225
F 0 "P33" H 4835 1675 50  0000 C CNN
F 1 "Voltage header 5V" V 4935 1225 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 4835 1225 60  0001 C CNN
F 3 "" H 4835 1225 60  0000 C CNN
F 4 "Value" H 4835 1225 60  0001 C CNN "Bestellnummer"
	1    4835 1225
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR085
U 1 1 553FE1B9
P 5145 1710
F 0 "#PWR085" H 5145 1560 60  0001 C CNN
F 1 "+5V" H 5145 1870 60  0000 C CNN
F 2 "" H 5145 1710 60  0000 C CNN
F 3 "" H 5145 1710 60  0000 C CNN
	1    5145 1710
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X08 P32
U 1 1 553FFEDE
P 4045 1245
F 0 "P32" H 4045 1695 50  0000 C CNN
F 1 "Voltage header GND" V 4145 1245 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 4045 1245 60  0001 C CNN
F 3 "" H 4045 1245 60  0000 C CNN
F 4 "Value" H 4045 1245 60  0001 C CNN "Bestellnummer"
	1    4045 1245
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR086
U 1 1 553FFF8E
P 4355 1730
F 0 "#PWR086" H 4355 1480 60  0001 C CNN
F 1 "GND" H 4355 1565 60  0000 C CNN
F 2 "" H 4355 1730 60  0000 C CNN
F 3 "" H 4355 1730 60  0000 C CNN
	1    4355 1730
	-1   0    0    -1  
$EndComp
Text Notes 5340 700  2    39   ~ 0
Abgriff 5V, 3V, GND
$Comp
L CONN_01X08 P38
U 1 1 55401F07
P 7075 1195
F 0 "P38" H 7075 1645 50  0000 C CNN
F 1 "Status LEDs GND" V 7175 1195 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 7075 1195 60  0001 C CNN
F 3 "" H 7075 1195 60  0000 C CNN
F 4 "Value" H 7075 1195 60  0001 C CNN "Bestellnummer"
	1    7075 1195
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR087
U 1 1 55401F1D
P 7385 1680
F 0 "#PWR087" H 7385 1430 60  0001 C CNN
F 1 "GND" H 7385 1515 60  0000 C CNN
F 2 "" H 7385 1680 60  0000 C CNN
F 3 "" H 7385 1680 60  0000 C CNN
	1    7385 1680
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X08 P7
U 1 1 55403386
P 8100 1225
F 0 "P7" H 8100 1675 50  0000 C CNN
F 1 "Status LEDs" V 8200 1225 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x08" H 8100 1225 60  0001 C CNN
F 3 "" H 8100 1225 60  0000 C CNN
	1    8100 1225
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR088
U 1 1 55403610
P 8425 875
F 0 "#PWR088" H 8425 625 60  0001 C CNN
F 1 "GND" V 8425 650 60  0000 C CNN
F 2 "" H 8425 875 60  0000 C CNN
F 3 "" H 8425 875 60  0000 C CNN
	1    8425 875 
	0    -1   -1   0   
$EndComp
Text GLabel 8430 975  2    39   Output ~ 0
LedPin-3V
Text GLabel 8430 1075 2    39   Output ~ 0
LedPin-24v
Text GLabel 8430 1175 2    39   Output ~ 0
LedPin-5v
Text GLabel 8430 1275 2    39   Output ~ 0
StationLed
Text GLabel 8430 1375 2    39   Output ~ 0
DuoLED_Grün
Text GLabel 8430 1475 2    39   Output ~ 0
DuoLED-Rot
Text GLabel 8430 1575 2    39   Output ~ 0
Led-Status
$Comp
L R R1
U 1 1 55406FDF
P 8260 2215
F 0 "R1" V 8340 2215 40  0000 C CNN
F 1 "220" V 8267 2216 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM15mm" V 8190 2215 30  0001 C CNN
F 3 "" H 8260 2215 30  0000 C CNN
F 4 "Value" H 8260 2215 60  0001 C CNN "Bestellnummer"
	1    8260 2215
	0    -1   1    0   
$EndComp
Text GLabel 7840 2215 0    39   Input ~ 0
Power5
Text GLabel 8675 2215 2    39   Output ~ 0
LedPin-5v
$Comp
L +24V #PWR089
U 1 1 5540858D
P 7835 2500
F 0 "#PWR089" H 7835 2350 60  0001 C CNN
F 1 "+24V" V 7835 2750 60  0000 C CNN
F 2 "" H 7835 2500 60  0000 C CNN
F 3 "" H 7835 2500 60  0000 C CNN
	1    7835 2500
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 55408729
P 8255 2500
F 0 "R2" V 8335 2500 40  0000 C CNN
F 1 "1K5" V 8262 2501 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 8185 2500 30  0001 C CNN
F 3 "" H 8255 2500 30  0000 C CNN
F 4 "Value" H 8255 2500 60  0001 C CNN "Bestellnummer"
	1    8255 2500
	0    -1   1    0   
$EndComp
Text GLabel 8670 2500 2    39   Output ~ 0
LedPin-24v
$Comp
L R R23
U 1 1 55409786
P 8260 2730
F 0 "R23" V 8340 2730 40  0000 C CNN
F 1 "100" V 8267 2731 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 8190 2730 30  0001 C CNN
F 3 "" H 8260 2730 30  0000 C CNN
F 4 "Value" H 8260 2730 60  0001 C CNN "Bestellnummer"
	1    8260 2730
	0    -1   1    0   
$EndComp
Text GLabel 8675 2730 2    39   Output ~ 0
LedPin-3V
$Comp
L +3.3V #PWR090
U 1 1 55409ED6
P 7840 2730
F 0 "#PWR090" H 7840 2690 30  0001 C CNN
F 1 "+3.3V" V 7840 2910 30  0000 C CNN
F 2 "" H 7840 2730 60  0000 C CNN
F 3 "" H 7840 2730 60  0000 C CNN
	1    7840 2730
	0    -1   -1   0   
$EndComp
Text Notes 4135 2530 0    39   ~ 0
LED Rechner:\nhttp://www.elektronik-kompendium.de/sites/bau/1109111.htm\n\nZ-Dioden Rechner:\nhttp://www.dieelektronikerseite.de/Tools/Zenerdiode.htm
Text Notes 4110 4200 0    39   ~ 0
LED Anzeigen - Hardware:\n\nLed 3V grün -   Betriebsanzeige Versorgungsspannung\nLED 24V grün - Betriebsanzeige Versorgungsspannung R2 für 12 V anpassen\nLED 5V grün -   Betriebsanzeige Versorgungsspannung\nLED Station - gelb - Statusanzeige ob Mover in Ladestation\n\n----------------------------------------------------------\n\nLED Anzeigen - Software:\n\nDual LED z.B:\nDual LED grün. Dauerlicht - Mover innerhalb Perimeter\nDual LED grün+rot = Orange - Dauerlicht Mover außerhalb Perimeter\nDual LED grün+rot = Orange - Blinkt Mover findet  Perimeter nicht oder sucht danach\nDual LED rot =  Blinkt Fehler kurzseitig Überlast Antriebmotor Treibe oder Mähmotor. \nDual LED rot - Dauerlicht - Fehler muß für weiterfahren durch drücken \nvon Button zurückgesetzt werden\n----------------------------------------------------------\n\nLED Status - grün Dauerlicht - warte auf Eingabe\n\nLED Status - grün blinken 1 bis 5 mal hintereinander\nmit länger Pause dazwischen für Anzeige in welchen\nBetriebsmodi sich der Mover befindet
$Comp
L +5V #PWR091
U 1 1 55571675
P 1490 5020
F 0 "#PWR091" H 1490 4870 60  0001 C CNN
F 1 "+5V" V 1490 5240 60  0000 C CNN
F 2 "" H 1490 5020 60  0000 C CNN
F 3 "" H 1490 5020 60  0000 C CNN
	1    1490 5020
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR092
U 1 1 5557167B
P 1485 5120
F 0 "#PWR092" H 1485 4870 60  0001 C CNN
F 1 "GND" V 1485 4895 60  0000 C CNN
F 2 "" H 1485 5120 60  0000 C CNN
F 3 "" H 1485 5120 60  0000 C CNN
	1    1485 5120
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P48
U 1 1 55571682
P 1010 5120
F 0 "P48" V 960 5120 50  0000 C CNN
F 1 "Reset" V 1060 5120 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x03" H 1010 5120 60  0001 C CNN
F 3 "" H 1010 5120 60  0000 C CNN
F 4 "Value" H 1010 5120 60  0001 C CNN "Bestellnummer"
	1    1010 5120
	-1   0    0    -1  
$EndComp
Text GLabel 1490 5220 2    39   Output ~ 0
Reset
Wire Wire Line
	1390 1315 1515 1315
Wire Wire Line
	2015 1315 2140 1315
Wire Wire Line
	1390 1515 1515 1515
Wire Wire Line
	2015 1515 2140 1515
Wire Wire Line
	1390 1615 2140 1615
Wire Wire Line
	1390 1415 2140 1415
Wire Wire Line
	1385 795  1515 795 
Wire Wire Line
	1385 895  1510 895 
Wire Wire Line
	1385 995  1515 995 
Wire Wire Line
	1380 1855 1510 1855
Wire Wire Line
	1380 1955 1505 1955
Wire Wire Line
	1380 2055 1510 2055
Wire Wire Line
	1375 2265 1505 2265
Wire Wire Line
	1375 2365 1500 2365
Wire Wire Line
	1375 2465 1505 2465
Wire Wire Line
	1370 2645 1500 2645
Wire Wire Line
	1370 2745 1495 2745
Wire Wire Line
	1370 2845 1500 2845
Wire Wire Line
	1370 3250 1495 3250
Wire Wire Line
	1370 3350 1495 3350
Wire Wire Line
	1370 3050 1495 3050
Wire Wire Line
	1370 3150 1445 3150
Wire Wire Line
	1445 3150 1445 3050
Connection ~ 1445 3050
Wire Wire Line
	1410 3570 1540 3570
Wire Wire Line
	1410 3670 1535 3670
Wire Wire Line
	1410 3770 1540 3770
Wire Wire Line
	1410 3870 1540 3870
Wire Wire Line
	1410 3970 1540 3970
Wire Wire Line
	5895 870  5895 1705
Wire Wire Line
	5895 870  5785 870 
Wire Wire Line
	5785 970  5895 970 
Connection ~ 5895 970 
Wire Wire Line
	5785 1070 5895 1070
Connection ~ 5895 1070
Wire Wire Line
	5785 1170 5895 1170
Connection ~ 5895 1170
Wire Wire Line
	5785 1270 5895 1270
Connection ~ 5895 1270
Wire Wire Line
	5785 1370 5895 1370
Connection ~ 5895 1370
Wire Wire Line
	5785 1470 5895 1470
Connection ~ 5895 1470
Wire Wire Line
	5785 1570 5895 1570
Connection ~ 5895 1570
Wire Wire Line
	5145 875  5145 1710
Wire Wire Line
	5145 875  5035 875 
Wire Wire Line
	5035 975  5145 975 
Connection ~ 5145 975 
Wire Wire Line
	5035 1075 5145 1075
Connection ~ 5145 1075
Wire Wire Line
	5035 1175 5145 1175
Connection ~ 5145 1175
Wire Wire Line
	5035 1275 5145 1275
Connection ~ 5145 1275
Wire Wire Line
	5035 1375 5145 1375
Connection ~ 5145 1375
Wire Wire Line
	5035 1475 5145 1475
Connection ~ 5145 1475
Wire Wire Line
	5035 1575 5145 1575
Connection ~ 5145 1575
Wire Wire Line
	4355 895  4355 1730
Wire Wire Line
	4355 895  4245 895 
Wire Wire Line
	4245 995  4355 995 
Connection ~ 4355 995 
Wire Wire Line
	4245 1095 4355 1095
Connection ~ 4355 1095
Wire Wire Line
	4245 1195 4355 1195
Connection ~ 4355 1195
Wire Wire Line
	4245 1295 4355 1295
Connection ~ 4355 1295
Wire Wire Line
	4245 1395 4355 1395
Connection ~ 4355 1395
Wire Wire Line
	4245 1495 4355 1495
Connection ~ 4355 1495
Wire Wire Line
	4245 1595 4355 1595
Connection ~ 4355 1595
Wire Wire Line
	7385 845  7385 1680
Wire Wire Line
	7385 845  7275 845 
Wire Wire Line
	7275 945  7385 945 
Connection ~ 7385 945 
Wire Wire Line
	7275 1045 7385 1045
Connection ~ 7385 1045
Wire Wire Line
	7275 1145 7385 1145
Connection ~ 7385 1145
Wire Wire Line
	7275 1245 7385 1245
Connection ~ 7385 1245
Wire Wire Line
	7275 1345 7385 1345
Connection ~ 7385 1345
Wire Wire Line
	7275 1445 7385 1445
Connection ~ 7385 1445
Wire Wire Line
	7275 1545 7385 1545
Connection ~ 7385 1545
Wire Wire Line
	8300 875  8425 875 
Wire Wire Line
	8300 975  8430 975 
Wire Wire Line
	8300 1075 8430 1075
Wire Wire Line
	8300 1175 8430 1175
Wire Wire Line
	8300 1275 8430 1275
Wire Wire Line
	8300 1375 8430 1375
Wire Wire Line
	8300 1475 8430 1475
Wire Wire Line
	8300 1575 8430 1575
Wire Wire Line
	8010 2215 7840 2215
Wire Wire Line
	8510 2215 8675 2215
Wire Wire Line
	8005 2500 7835 2500
Wire Wire Line
	8505 2500 8670 2500
Wire Wire Line
	8010 2730 7840 2730
Wire Wire Line
	8510 2730 8675 2730
Wire Wire Line
	1360 5020 1490 5020
Wire Wire Line
	1360 5120 1485 5120
Wire Wire Line
	1360 5220 1490 5220
Wire Wire Line
	1345 4440 1800 4440
Wire Wire Line
	1345 4340 1480 4340
Wire Wire Line
	1345 4240 1485 4240
Wire Wire Line
	1345 4540 1800 4540
Wire Wire Line
	1345 4640 1800 4640
Wire Wire Line
	1345 4740 1800 4740
$EndSCHEMATC
