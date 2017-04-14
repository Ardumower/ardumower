EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-rescue
LIBS:power
LIBS:device
LIBS:Zimprich
LIBS:conn
LIBS:transistors
LIBS:switches
LIBS:linear
LIBS:texas
LIBS:diode
LIBS:ardumower mega shield svn-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 33
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
L MC33926 Dual1
U 1 1 57D96B1D
P 4510 2375
F 0 "Dual1" H 4460 1425 60  0000 C CNN
F 1 "MC33926" H 4510 3525 60  0000 C CNN
F 2 "Zimprich:MC_33926_31polig_mit_Bohrloch_neue_Masse_mit_zweite_Lochreihe" H 4660 2425 60  0001 C CNN
F 3 "" H 4660 2425 60  0001 C CNN
F 4 "Value" H 4510 2375 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4510 2375 60  0001 C CNN "Bestelllink"
	1    4510 2375
	1    0    0    -1  
$EndComp
Text GLabel 3360 2325 0    39   Output ~ 0
pinMotorLeftSense
Text GLabel 3360 1425 0    39   Output ~ 0
pinMotorRightSense
Text GLabel 3360 2825 0    39   Input ~ 0
pinMotorLeftDir
Text GLabel 3360 1825 0    39   Input ~ 0
pinMotorRightPWM
Text GLabel 3360 2725 0    39   Input ~ 0
pinMotorLeftPWM
Text GLabel 3360 1925 0    39   Input ~ 0
pinMotorRightDir
NoConn ~ 3660 3125
NoConn ~ 3660 2025
NoConn ~ 3660 2125
Text GLabel 3260 2225 0    39   Input ~ 0
pinMotorEnable
Text GLabel 3360 2425 0    39   Output ~ 0
pinMotorLeftFault
Text GLabel 3360 1525 0    39   Output ~ 0
pinMotorRightFault
$Comp
L MC33926 Dual2
U 1 1 57D96B33
P 4510 5025
F 0 "Dual2" H 4460 4075 60  0000 C CNN
F 1 "MC33926" H 4510 6175 60  0000 C CNN
F 2 "Zimprich:MC_33926_31polig_mit_Bohrloch_neue_Masse_mit_zweite_Lochreihe" H 4660 5075 60  0001 C CNN
F 3 "" H 4660 5075 60  0001 C CNN
F 4 "Value" H 4510 5025 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4510 5025 60  0001 C CNN "Bestelllink"
	1    4510 5025
	1    0    0    -1  
$EndComp
Text GLabel 3360 4075 0    39   Output ~ 0
pinMotorMowSense
Text GLabel 3360 4475 0    39   Input ~ 0
pinMotorMowPWM
Text GLabel 3360 4575 0    39   Input ~ 0
pinMotorMowDir
NoConn ~ 3660 5775
NoConn ~ 3660 4675
NoConn ~ 3660 4775
Text GLabel 3260 4775 0    39   Input ~ 0
pinMotorMowEnable
Text GLabel 3360 4175 0    39   Output ~ 0
pinMotorMowFault
Text GLabel 2425 4975 0    39   Input ~ 0
ReserveAD6
$Comp
L Jumper JP3
U 1 1 57D96C22
P 2795 4975
F 0 "JP3" H 2790 4815 60  0000 C CNN
F 1 "M1FB" H 2795 4895 40  0000 C CNN
F 2 "Zimprich:SJ" H 2795 4975 60  0001 C CNN
F 3 "" H 2795 4975 60  0001 C CNN
F 4 "Value" H 2795 4975 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2795 4975 60  0001 C CNN "Bestelllink"
	1    2795 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	3510 1625 3660 1625
Wire Wire Line
	3660 2525 3510 2525
Wire Wire Line
	3660 2625 3510 2625
Wire Wire Line
	3510 3025 3660 3025
Wire Wire Line
	3360 1425 3660 1425
Wire Wire Line
	3360 1925 3660 1925
Wire Wire Line
	3360 2825 3660 2825
Wire Wire Line
	3360 2325 3660 2325
Wire Wire Line
	3360 2425 3660 2425
Wire Wire Line
	3260 2225 3660 2225
Wire Wire Line
	3360 1525 3660 1525
Wire Wire Line
	3360 1825 3660 1825
Wire Wire Line
	3360 2725 3660 2725
Wire Wire Line
	3510 4275 3660 4275
Wire Wire Line
	3660 4375 3510 4375
Wire Wire Line
	3360 4075 3660 4075
Wire Wire Line
	3360 4575 3660 4575
Wire Wire Line
	3510 4575 3510 5475
Wire Wire Line
	3300 4875 3660 4875
Wire Wire Line
	3360 4175 3660 4175
Wire Wire Line
	3360 4475 3660 4475
Wire Wire Line
	3510 2925 3660 2925
Wire Wire Line
	3510 1725 3660 1725
Wire Wire Line
	5385 4875 6050 4875
Wire Wire Line
	5385 4825 5260 4825
Wire Wire Line
	5385 4725 5260 4725
Wire Wire Line
	5385 4675 6050 4675
Wire Wire Line
	5385 2175 5260 2175
Wire Wire Line
	5385 2075 5260 2075
Wire Wire Line
	5385 2675 5610 2675
Wire Wire Line
	5385 2675 5385 2725
Wire Wire Line
	5385 2725 5260 2725
Wire Wire Line
	5385 2875 5610 2875
Wire Wire Line
	5385 2875 5385 2825
Wire Wire Line
	5385 2825 5260 2825
Wire Wire Line
	5385 1425 5640 1425
Wire Wire Line
	5385 1425 5385 1475
Wire Wire Line
	5385 1475 5260 1475
Wire Wire Line
	5385 1625 5640 1625
Wire Wire Line
	5385 1625 5385 1575
Wire Wire Line
	5385 1575 5260 1575
Wire Wire Line
	5385 4075 6055 4075
Wire Wire Line
	5385 4075 5385 4125
Wire Wire Line
	5385 4125 5260 4125
Wire Wire Line
	5385 4275 6055 4275
Wire Wire Line
	5385 4275 5385 4225
Wire Wire Line
	5385 4225 5260 4225
Wire Wire Line
	3510 5675 3660 5675
Wire Wire Line
	3660 5575 3560 5575
Wire Wire Line
	3330 5175 3660 5175
Wire Wire Line
	3660 5275 3330 5275
Wire Wire Line
	3660 5075 3590 5075
Wire Wire Line
	3590 5075 3590 4175
Connection ~ 3590 4175
Wire Wire Line
	3660 5375 3550 5375
Wire Wire Line
	3550 5375 3550 4475
Connection ~ 3550 4475
Wire Wire Line
	3300 4875 3300 4775
Wire Wire Line
	3300 4775 3260 4775
Wire Wire Line
	3510 5475 3660 5475
Connection ~ 3510 4575
Wire Wire Line
	5260 5375 5450 5375
Wire Wire Line
	5450 5375 5450 4075
Connection ~ 5450 4075
Wire Wire Line
	5260 5475 5565 5475
Wire Wire Line
	3095 4975 3660 4975
Wire Wire Line
	2495 4975 2425 4975
$Comp
L GND #PWR013
U 1 1 57DCB31A
P 7305 2190
F 0 "#PWR013" H 7305 1940 50  0001 C CNN
F 1 "GND" V 7305 1995 50  0000 C CNN
F 2 "" H 7305 2190 50  0000 C CNN
F 3 "" H 7305 2190 50  0000 C CNN
	1    7305 2190
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR014
U 1 1 57DCB496
P 3510 3025
F 0 "#PWR014" H 3510 2775 50  0001 C CNN
F 1 "GND" V 3510 2830 50  0000 C CNN
F 2 "" H 3510 3025 50  0000 C CNN
F 3 "" H 3510 3025 50  0000 C CNN
	1    3510 3025
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR015
U 1 1 57DCB679
P 3510 2525
F 0 "#PWR015" H 3510 2275 50  0001 C CNN
F 1 "GND" V 3510 2330 50  0000 C CNN
F 2 "" H 3510 2525 50  0000 C CNN
F 3 "" H 3510 2525 50  0000 C CNN
	1    3510 2525
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR016
U 1 1 57DCB703
P 3510 1625
F 0 "#PWR016" H 3510 1375 50  0001 C CNN
F 1 "GND" V 3510 1430 50  0000 C CNN
F 2 "" H 3510 1625 50  0000 C CNN
F 3 "" H 3510 1625 50  0000 C CNN
	1    3510 1625
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR017
U 1 1 57DCB93A
P 3510 4275
F 0 "#PWR017" H 3510 4025 50  0001 C CNN
F 1 "GND" V 3510 4080 50  0000 C CNN
F 2 "" H 3510 4275 50  0000 C CNN
F 3 "" H 3510 4275 50  0000 C CNN
	1    3510 4275
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR018
U 1 1 57DCBAED
P 3330 5175
F 0 "#PWR018" H 3330 4925 50  0001 C CNN
F 1 "GND" V 3330 4980 50  0000 C CNN
F 2 "" H 3330 5175 50  0000 C CNN
F 3 "" H 3330 5175 50  0000 C CNN
	1    3330 5175
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR019
U 1 1 57DCBBA3
P 3510 5675
F 0 "#PWR019" H 3510 5425 50  0001 C CNN
F 1 "GND" V 3510 5480 50  0000 C CNN
F 2 "" H 3510 5675 50  0000 C CNN
F 3 "" H 3510 5675 50  0000 C CNN
	1    3510 5675
	0    1    -1   0   
$EndComp
$Sheet
S 6055 3985 1120 455 
U 57DAEC1D
F0 "MähmotorSchutz" 60
F1 "MähmotorSchutz.sch" 60
F2 "MotorIN1" B L 6055 4275 60 
F3 "MotorIN2" B L 6055 4075 60 
F4 "MotorOUT1" I R 7175 4280 60 
F5 "MotorOUT2" I R 7175 4080 60 
F6 "+24V" I R 7175 4385 60 
$EndSheet
Wire Wire Line
	7255 4080 7175 4080
Wire Wire Line
	7255 4280 7175 4280
Wire Wire Line
	5565 5475 5565 4275
Connection ~ 5565 4275
$Sheet
S 5610 2605 1120 495 
U 57DB3A39
F0 "MotorLinks" 60
F1 "MotorLinks.sch" 60
F2 "MotorIN1" B L 5610 2875 60 
F3 "MotorIN2" B L 5610 2675 60 
F4 "MotorOUT1" I R 6730 2860 60 
F5 "MotorOUT2" I R 6730 2660 60 
F6 "+24V" I R 6730 3010 60 
$EndSheet
Wire Wire Line
	6860 2660 6730 2660
Wire Wire Line
	6860 2860 6730 2860
$Sheet
S 5640 1350 1120 460 
U 57DB6176
F0 "MotorRechts" 60
F1 "MotorRechts.sch" 60
F2 "MotorIN1" B L 5640 1625 60 
F3 "MotorIN2" B L 5640 1425 60 
F4 "MotorOUT1" I R 6760 1625 60 
F5 "MotorOUT2" I R 6760 1425 60 
F6 "+24V" I R 6760 1745 60 
$EndSheet
Wire Wire Line
	6880 1625 6760 1625
Wire Wire Line
	6880 1425 6760 1425
$Sheet
S 5620 1960 1550 355 
U 57DB84D9
F0 "Motortreiber1" 60
F1 "Motortreiber1.sch" 60
F2 "Dual1_IN_+" I R 7170 2055 60 
F3 "Dual1_IN_GND" I R 7170 2190 60 
F4 "Dual1_OUT_+" I L 5620 2025 60 
F5 "Dual1_OUT_GND" I L 5620 2225 60 
$EndSheet
Wire Wire Line
	7170 2055 7305 2055
Wire Wire Line
	7170 2190 7305 2190
Wire Wire Line
	5385 2075 5385 2025
Wire Wire Line
	5385 2025 5620 2025
Wire Wire Line
	5385 2175 5385 2225
Wire Wire Line
	5385 2225 5620 2225
$Sheet
S 6050 4595 1550 355 
U 57DBD284
F0 "Motortreiber2" 60
F1 "Motortreiber2.sch" 60
F2 "Dual1_IN_+" I R 7600 4665 60 
F3 "Dual1_IN_GND" I R 7600 4840 60 
F4 "Dual1_OUT_+" I L 6050 4675 60 
F5 "Dual1_OUT_GND" I L 6050 4875 60 
$EndSheet
Wire Wire Line
	7600 4665 7735 4665
$Comp
L GND #PWR020
U 1 1 57DC2092
P 7735 4840
F 0 "#PWR020" H 7735 4590 50  0001 C CNN
F 1 "GND" V 7735 4645 50  0000 C CNN
F 2 "" H 7735 4840 50  0000 C CNN
F 3 "" H 7735 4840 50  0000 C CNN
	1    7735 4840
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 4840 7735 4840
Wire Wire Line
	5385 4825 5385 4875
Wire Wire Line
	5385 4725 5385 4675
$Comp
L GND #PWR021
U 1 1 57DC50B6
P 10310 1730
F 0 "#PWR021" H 10310 1480 50  0001 C CNN
F 1 "GND" V 10310 1535 50  0000 C CNN
F 2 "" H 10310 1730 50  0000 C CNN
F 3 "" H 10310 1730 50  0000 C CNN
	1    10310 1730
	0    1    -1   0   
$EndComp
Wire Wire Line
	10445 1630 10310 1630
Wire Wire Line
	10445 1730 10310 1730
$Comp
L GND #PWR022
U 1 1 57DC5B70
P 10315 1095
F 0 "#PWR022" H 10315 845 50  0001 C CNN
F 1 "GND" V 10315 900 50  0000 C CNN
F 2 "" H 10315 1095 50  0000 C CNN
F 3 "" H 10315 1095 50  0000 C CNN
	1    10315 1095
	0    1    -1   0   
$EndComp
Wire Wire Line
	10450 995  10315 995 
Wire Wire Line
	10450 1095 10315 1095
$Comp
L CONN_01X02 P39
U 1 1 57E0418F
P 10645 1680
F 0 "P39" H 10563 1405 50  0000 C CNN
F 1 "Res24V-1" H 10563 1496 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 10722 1743 50  0001 L CNN
F 3 "" H 10645 1680 50  0001 C CNN
F 4 "Value" H 10722 1644 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 10722 1538 60  0001 L CNN "Bestelllink"
F 6 "Value" H 10722 1432 60  0001 L CNN "Technische Daten"
F 7 "Value" H 10645 1680 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10645 1680 60  0001 C CNN "Bauform"
	1    10645 1680
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P36
U 1 1 57E067EC
P 10650 1045
F 0 "P36" H 10568 770 50  0000 C CNN
F 1 "Res24V-2" H 10568 861 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 10727 1108 50  0001 L CNN
F 3 "" H 10650 1045 50  0001 C CNN
F 4 "Value" H 10727 1009 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 10727 903 60  0001 L CNN "Bestelllink"
F 6 "Value" H 10727 797 60  0001 L CNN "Technische Daten"
F 7 "Value" H 10650 1045 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10650 1045 60  0001 C CNN "Bauform"
	1    10650 1045
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P37
U 1 1 57E0AFDE
P 7555 4175
F 0 "P37" H 7473 3900 50  0000 C CNN
F 1 "Mower" H 7473 3991 50  0000 C CNN
F 2 "Zimprich:Anschlussklemme_RM5,08-RM7,62" H 7632 4238 50  0001 L CNN
F 3 "" H 7555 4175 50  0001 C CNN
F 4 "Value" H 7632 4139 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 7632 4033 60  0001 L CNN "Bestelllink"
F 6 "Value" H 7632 3927 60  0001 L CNN "Technische Daten"
F 7 "Value" H 7555 4175 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7555 4175 60  0001 C CNN "Bauform"
	1    7555 4175
	1    0    0    1   
$EndComp
Wire Wire Line
	7255 4280 7255 4225
Wire Wire Line
	7255 4225 7355 4225
Wire Wire Line
	7255 4080 7255 4125
Wire Wire Line
	7255 4125 7355 4125
$Comp
L CONN_01X02 P15
U 1 1 57E0CA53
P 7120 2755
F 0 "P15" H 7038 2480 50  0000 C CNN
F 1 "Left" H 7038 2571 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 7197 2818 50  0001 L CNN
F 3 "" H 7120 2755 50  0001 C CNN
F 4 "Value" H 7197 2719 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 7197 2613 60  0001 L CNN "Bestelllink"
F 6 "Value" H 7197 2507 60  0001 L CNN "Technische Daten"
F 7 "Value" H 7120 2755 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7120 2755 60  0001 C CNN "Bauform"
	1    7120 2755
	1    0    0    1   
$EndComp
Wire Wire Line
	6860 2860 6860 2805
Wire Wire Line
	6860 2805 6920 2805
Wire Wire Line
	6860 2660 6860 2705
Wire Wire Line
	6860 2705 6920 2705
$Comp
L CONN_01X02 P18
U 1 1 57E0DF43
P 7140 1525
F 0 "P18" H 7058 1250 50  0000 C CNN
F 1 "Right" H 7058 1341 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 7217 1588 50  0001 L CNN
F 3 "" H 7140 1525 50  0001 C CNN
F 4 "Value" H 7217 1489 60  0001 L CNN "Gehäuseart"
F 5 "Value" H 7217 1383 60  0001 L CNN "Bestelllink"
F 6 "Value" H 7217 1277 60  0001 L CNN "Technische Daten"
F 7 "Value" H 7140 1525 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7140 1525 60  0001 C CNN "Bauform"
F 9 "Value" H 7140 1525 60  0001 C CNN "Funktion"
F 10 "Value" H 7140 1525 60  0001 C CNN "Hersteller"
F 11 "Value" H 7140 1525 60  0001 C CNN "Hersteller Bestellnummer"
	1    7140 1525
	1    0    0    1   
$EndComp
Wire Wire Line
	6880 1625 6880 1575
Wire Wire Line
	6880 1575 6940 1575
Wire Wire Line
	6880 1425 6880 1475
Wire Wire Line
	6880 1475 6940 1475
Text GLabel 3510 2925 0    39   Output ~ 0
IOREF
Text GLabel 3510 2625 0    39   Output ~ 0
IOREF
Text GLabel 3510 1725 0    39   Output ~ 0
IOREF
Text GLabel 3560 5575 0    39   Output ~ 0
IOREF
Text GLabel 3330 5275 0    39   Output ~ 0
IOREF
Text GLabel 3510 4375 0    39   Output ~ 0
IOREF
Text Notes 1100 6255 0    60   ~ 0
https://www.schukat.com/schukat/schukat_cms_de.nsf/index/CMSDF15D356B046D53BC1256D550038A9E0?OpenDocument&wg=V3672&refDoc=CMS12B13E45BB196811C1257A6A002C97CA\n\nhttps://www.infineon.com/cms/packages/SMD_-_Surface_Mounted_Devices/P-PG-TO252/P-PG-TO252-03-023.html?__locale=de_AT
Text HLabel 7735 4665 2    50   Input ~ 0
+24V
Text HLabel 10310 1630 0    50   Input ~ 0
+24V
Text HLabel 10315 995  0    50   Input ~ 0
+24V
Text HLabel 7305 2055 2    50   Input ~ 0
+24V
Text HLabel 6925 1745 2    50   Input ~ 0
+24V
Wire Wire Line
	6925 1745 6760 1745
Text HLabel 6895 3010 2    50   Input ~ 0
+24V
Wire Wire Line
	6895 3010 6730 3010
Wire Wire Line
	7175 4385 7310 4385
Text HLabel 7310 4385 2    50   Input ~ 0
+24V
Text Notes 995  -470 0    79   ~ 0
Unsere Motoren haben:\nEncoder 5 Impulse pro Umdrehung\n31 Umdrehungen nach dem Getriebe\nmit einer Übersetzung 1:212\nDas entspricht etwa 6572 Umdrehungen des Motors vor dem Getriebe.\nDas heißt der Motor vor dem Getriebe dreht sich 212mal damit der Motor nach dem Getriebe sich 1 mal dreht.\nImpulse pro Umdrehung wäre demnach : 6572 /31 = 212\nDa der Encoder aber vor dem Getriebe sitzt haben wir bei einer Radumdrehung 212*5 Impulse.\nAlso 1060 pro Radumdrehung
$EndSCHEMATC
