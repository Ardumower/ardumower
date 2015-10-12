EESchema Schematic File Version 2
LIBS:power
LIBS:Bluetooth_ZS_HC_05
LIBS:Bluetooth_CZ_HC_05
LIBS:ds1307
LIBS:Wlan_ESP8266
LIBS:transistor-fet
LIBS:transistor-fet+irf7201
LIBS:transistors
LIBS:w_transistor
LIBS:diode
LIBS:diode-1
LIBS:led
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MOS_P Q?
U 1 1 553A4B73
P 5095 1935
F 0 "Q?" H 4998 2185 70  0000 C CNN
F 1 "IRF9530N" H 4948 1688 60  0000 C CNN
F 2 "" H 5095 1935 60  0000 C CNN
F 3 "" H 5095 1935 60  0000 C CNN
	1    5095 1935
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 553A4BC1
P 5095 2770
F 0 "R?" V 5175 2770 40  0000 C CNN
F 1 "100K" V 5102 2771 40  0000 C CNN
F 2 "" V 5025 2770 30  0000 C CNN
F 3 "" H 5095 2770 30  0000 C CNN
	1    5095 2770
	1    0    0    -1  
$EndComp
$Comp
L ZENER-DIODEC1702-15 D?
U 1 1 553A4C8B
P 5585 2230
F 0 "D?" H 5515 2305 50  0000 L BNN
F 1 "ZPD15" H 5515 2095 50  0000 L BNN
F 2 "diode-C1702-15" H 5585 2380 50  0001 C CNN
F 3 "" H 5585 2230 60  0000 C CNN
	1    5585 2230
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5095 2035 5095 2520
Wire Wire Line
	5585 2130 5585 1835
Wire Wire Line
	5245 1835 6025 1835
Wire Wire Line
	5585 2330 5585 2435
Wire Wire Line
	5585 2435 5095 2435
Connection ~ 5095 2435
Wire Wire Line
	4385 1835 4945 1835
Connection ~ 5585 1835
Text HLabel 6025 1835 2    60   Output ~ 0
Verpols.L.aus
Text HLabel 4385 1835 0    60   Input ~ 0
Verpol.s.L.in
$Comp
L GND #PWR?
U 1 1 553AAF15
P 5095 3155
F 0 "#PWR?" H 5095 2905 60  0001 C CNN
F 1 "GND" H 5095 3005 60  0000 C CNN
F 2 "" H 5095 3155 60  0000 C CNN
F 3 "" H 5095 3155 60  0000 C CNN
	1    5095 3155
	1    0    0    -1  
$EndComp
Wire Wire Line
	5095 3020 5095 3155
$EndSCHEMATC
