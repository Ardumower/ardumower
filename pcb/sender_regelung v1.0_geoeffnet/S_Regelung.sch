EESchema Schematic File Version 2
LIBS:op-amp
LIBS:Perimeter sender v2-rescue
LIBS:arduino_shieldsNCL
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:w_microcontrollers
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:MC33926
LIBS:Perimeter sender v2-cache
LIBS:ardumower mega shield svn-cache
LIBS:Arduino
LIBS:Ina169
LIBS:OPA2340PA
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date "25 sep 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DC-DC_Stepdown U6
U 1 1 5642FEE7
P 3585 3580
F 0 "U6" H 3585 3580 28  0000 C CNN
F 1 "DC-DC_Stepdown" H 3585 3630 24  0000 C CNN
F 2 "sender_v2:DC_DC_DSN2596_mit_Bohrloch" H 3585 3580 60  0001 C CNN
F 3 "" H 3585 3580 60  0000 C CNN
	1    3585 3580
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 5642FEE8
P 1925 2705
F 0 "P5" H 1925 2855 50  0000 C CNN
F 1 "Vin 24V" V 2025 2705 50  0000 C CNN
F 2 "sender_v2:Anschlussklemme_2P_RM5,08" H 1925 2705 60  0001 C CNN
F 3 "" H 1925 2705 60  0000 C CNN
	1    1925 2705
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P6
U 1 1 5642FEE9
P 6795 4620
F 0 "P6" H 6795 4770 50  0000 C CNN
F 1 "VOut 24V" V 6895 4620 50  0000 C CNN
F 2 "sender_v2:Anschlussklemme_2P_RM5,08" H 6795 4620 60  0001 C CNN
F 3 "" H 6795 4620 60  0000 C CNN
	1    6795 4620
	0    -1   1    0   
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR32
U 1 1 5642FEEA
P 1975 3005
F 0 "#PWR32" H 1975 3005 30  0001 C CNN
F 1 "GND" H 1975 2935 30  0001 C CNN
F 2 "" H 1975 3005 60  0000 C CNN
F 3 "" H 1975 3005 60  0000 C CNN
	1    1975 3005
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR37
U 1 1 5642FEEB
P 4010 3780
F 0 "#PWR37" H 4010 3780 30  0001 C CNN
F 1 "GND" H 4010 3710 30  0001 C CNN
F 2 "" H 4010 3780 60  0000 C CNN
F 3 "" H 4010 3780 60  0000 C CNN
	1    4010 3780
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR34
U 1 1 5642FEEC
P 3160 3780
F 0 "#PWR34" H 3160 3780 30  0001 C CNN
F 1 "GND" H 3160 3710 30  0001 C CNN
F 2 "" H 3160 3780 60  0000 C CNN
F 3 "" H 3160 3780 60  0000 C CNN
	1    3160 3780
	1    0    0    -1  
$EndComp
$Comp
L ACS712 U7
U 1 1 5642FEF0
P 6185 3580
F 0 "U7" H 6185 3830 50  0000 C CNN
F 1 "INA 169" H 6185 3330 50  0000 C CNN
F 2 "sender_v2:INA169" H 6185 3580 60  0001 C CNN
F 3 "" H 6185 3580 60  0000 C CNN
F 4 "Value" H 6185 3580 60  0001 C CNN "Bestellnummer"
	1    6185 3580
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR45
U 1 1 5642FEF1
P 7045 4420
F 0 "#PWR45" H 7045 4170 60  0001 C CNN
F 1 "GND" H 7045 4270 60  0001 C CNN
F 2 "" H 7045 4420 60  0000 C CNN
F 3 "" H 7045 4420 60  0000 C CNN
F 4 "Value" H 7045 4420 60  0001 C CNN "Bestellnummer"
	1    7045 4420
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR47
U 1 1 5642FEF2
P 7325 3805
F 0 "#PWR47" H 7325 3555 60  0001 C CNN
F 1 "GND" H 7325 3655 60  0001 C CNN
F 2 "" H 7325 3805 60  0000 C CNN
F 3 "" H 7325 3805 60  0000 C CNN
F 4 "Value" H 7325 3805 60  0001 C CNN "Bestellnummer"
	1    7325 3805
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR46
U 1 1 5642FEF4
P 7325 3380
F 0 "#PWR46" H 7325 3470 20  0001 C CNN
F 1 "+5V" H 7325 3510 30  0000 C CNN
F 2 "" H 7325 3380 60  0000 C CNN
F 3 "" H 7325 3380 60  0000 C CNN
	1    7325 3380
	1    0    0    -1  
$EndComp
$Comp
L F_10A F1
U 1 1 5642FEFB
P 1875 3180
F 0 "F1" H 1925 3105 40  0000 C CNN
F 1 "????" H 1775 3100 40  0000 C CNN
F 2 "sender_v2:Fuseholder_Reichelt_PL112000" H 1875 3180 60  0001 C CNN
F 3 "" H 1875 3180 60  0000 C CNN
F 4 "Value" H 1875 3180 60  0001 C CNN "Technische Daten"
F 5 "R: PL112000" H 1775 3030 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 1875 3180 60  0001 C CNN "Bauform"
F 7 "Value" H 1875 3180 60  0001 C CNN "Bestelllink"
	1    1875 3180
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR33
U 1 1 5642FEFE
P 2605 4100
F 0 "#PWR33" H 2605 4100 30  0001 C CNN
F 1 "GND" H 2605 4030 30  0001 C CNN
F 2 "" H 2605 4100 60  0000 C CNN
F 3 "" H 2605 4100 60  0000 C CNN
	1    2605 4100
	-1   0    0    -1  
$EndComp
$Comp
L DIODE D2
U 1 1 5642FF02
P 2175 3480
F 0 "D2" H 2175 3580 50  0000 C CNN
F 1 "MBR 1045" H 2175 3380 50  0000 C CNN
F 2 "sender_v2:MBR1045_Horizontal" H 2175 3480 60  0001 C CNN
F 3 "" H 2175 3480 60  0000 C CNN
	1    2175 3480
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR39
U 1 1 56431646
P 4350 4100
F 0 "#PWR39" H 4350 4100 30  0001 C CNN
F 1 "GND" H 4350 4030 30  0001 C CNN
F 2 "" H 4350 4100 60  0000 C CNN
F 3 "" H 4350 4100 60  0000 C CNN
	1    4350 4100
	-1   0    0    -1  
$EndComp
Text GLabel 6875 3580 2    60   Output ~ 0
A7
$Comp
L C_Small C9
U 1 1 5643245D
P 7325 3580
F 0 "C9" H 7335 3650 50  0000 L CNN
F 1 "100nF" H 7335 3500 50  0000 L CNN
F 2 "ACS712:C_Rect_L4_W2.5_P2.5_P5.0" H 7325 3580 60  0001 C CNN
F 3 "" H 7325 3580 60  0000 C CNN
F 4 "Value" H 7325 3580 60  0001 C CNN "Technische Daten"
F 5 "Value" H 7325 3580 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 7325 3580 60  0001 C CNN "Bauform"
F 7 "Value" H 7325 3580 60  0001 C CNN "Bestelllink"
	1    7325 3580
	1    0    0    -1  
$EndComp
$Comp
L F_10A F2
U 1 1 5643282C
P 6370 4095
F 0 "F2" H 6420 4020 40  0000 C CNN
F 1 "????" H 6270 4015 40  0000 C CNN
F 2 "sender_v2:Fuseholder_Reichelt_PL112000" H 6370 4095 60  0001 C CNN
F 3 "" H 6370 4095 60  0000 C CNN
F 4 "R: PL112000" H 6270 3945 60  0001 C CNN "Bestellnummer"
	1    6370 4095
	1    0    0    -1  
$EndComp
Wire Wire Line
	1975 3005 1975 2905
Wire Wire Line
	4010 3780 4010 3680
Wire Wire Line
	3160 3780 3160 3680
Wire Wire Line
	4010 3680 3935 3680
Wire Wire Line
	3160 3680 3235 3680
Wire Wire Line
	6745 4095 6745 4420
Wire Wire Line
	6845 4420 6845 4370
Wire Wire Line
	6845 4370 7045 4370
Wire Wire Line
	7045 4370 7045 4420
Wire Wire Line
	7325 3680 7325 3805
Wire Wire Line
	2605 3945 2605 4100
Wire Wire Line
	2375 3480 3235 3480
Wire Wire Line
	1875 2980 1875 2905
Wire Wire Line
	1975 3480 1875 3480
Wire Wire Line
	1875 3480 1875 3380
Wire Wire Line
	2605 3480 2605 3645
Connection ~ 2605 3480
Wire Wire Line
	3935 3480 5785 3480
Wire Wire Line
	4350 3950 4350 4100
Wire Wire Line
	4350 3480 4350 3650
Connection ~ 4350 3480
Wire Wire Line
	6585 3580 6875 3580
Wire Wire Line
	7325 3380 7325 3480
Wire Wire Line
	6585 3480 6585 3450
Wire Wire Line
	6585 3450 7675 3450
Connection ~ 7325 3450
Wire Wire Line
	6585 3680 6585 3710
Wire Wire Line
	6585 3710 7675 3710
Connection ~ 7325 3710
Wire Wire Line
	5785 3680 5735 3680
Wire Wire Line
	5735 3680 5735 4280
Wire Wire Line
	5735 4095 6170 4095
Connection ~ 5735 4095
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR43
U 1 1 56432DDB
P 5735 4740
F 0 "#PWR43" H 5735 4490 60  0001 C CNN
F 1 "GND" H 5735 4590 60  0001 C CNN
F 2 "" H 5735 4740 60  0000 C CNN
F 3 "" H 5735 4740 60  0000 C CNN
F 4 "Value" H 5735 4740 60  0001 C CNN "Bestellnummer"
	1    5735 4740
	1    0    0    -1  
$EndComp
Wire Wire Line
	5735 4680 5735 4740
Wire Wire Line
	6570 4095 6745 4095
$Comp
L R R9
U 1 1 5643336E
P 5080 4420
F 0 "R9" H 5185 4420 50  0000 C CNN
F 1 "100K/1%" H 5320 4350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5010 4420 30  0001 C CNN
F 3 "" H 5080 4420 30  0000 C CNN
F 4 "Value" H 5080 4420 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5080 4420 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5080 4420 60  0001 C CNN "Bauform"
F 7 "Value" H 5080 4420 60  0001 C CNN "Bestelllink"
	1    5080 4420
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 56433756
P 5080 4965
F 0 "R10" H 5185 4965 50  0000 C CNN
F 1 "10K/1%" H 5295 4895 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5010 4965 30  0001 C CNN
F 3 "" H 5080 4965 30  0000 C CNN
F 4 "Value" H 5080 4965 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5080 4965 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5080 4965 60  0001 C CNN "Bauform"
F 7 "Value" H 5080 4965 60  0001 C CNN "Bestelllink"
	1    5080 4965
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 56433A7E
P 4725 4965
F 0 "C6" H 4750 5065 50  0000 L CNN
F 1 "47pP" H 4750 4865 50  0000 L CNN
F 2 "ACS712:C_Rect_L4_W2.5_P2.5_P5.0" H 4763 4815 30  0001 C CNN
F 3 "" H 4725 4965 60  0000 C CNN
F 4 "Value" H 4725 4965 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4725 4965 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4725 4965 60  0001 C CNN "Bauform"
F 7 "Value" H 4725 4965 60  0001 C CNN "Bestelllink"
	1    4725 4965
	1    0    0    -1  
$EndComp
$Comp
L ZENER D5
U 1 1 56433D7A
P 4135 4970
F 0 "D5" V 4095 4845 50  0000 C CNN
F 1 "ZPD5,1V" V 4170 4735 50  0000 C CNN
F 2 "ACS712:Diode_ligend_RM10" H 4135 4970 60  0001 C CNN
F 3 "" H 4135 4970 60  0000 C CNN
F 4 "Value" H 4135 4970 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4135 4970 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4135 4970 60  0001 C CNN "Bauform"
F 7 "Value" H 4135 4970 60  0001 C CNN "Bestelllink"
	1    4135 4970
	0    -1   1    0   
$EndComp
Wire Wire Line
	4135 5170 4135 5260
Wire Wire Line
	4135 5260 5080 5260
Wire Wire Line
	4725 5260 4725 5115
Wire Wire Line
	5080 5260 5080 5115
Connection ~ 4725 5260
Wire Wire Line
	4135 4770 4135 4700
Wire Wire Line
	3700 4700 5080 4700
Wire Wire Line
	4725 4700 4725 4815
Wire Wire Line
	5080 4570 5080 4815
Connection ~ 4725 4700
Connection ~ 5080 4700
Wire Wire Line
	5080 3480 5080 4270
$Comp
L OP275 U5
U 1 1 5643505D
P 3350 4800
F 0 "U5" H 3350 4950 60  0000 L CNN
F 1 "OPA2340PA" H 3350 4650 60  0000 L CNN
F 2 "" H 3350 4800 60  0000 C CNN
F 3 "" H 3350 4800 60  0000 C CNN
F 4 "Value" H 3350 4800 60  0001 C CNN "Technische Daten"
F 5 "Value" H 3350 4800 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 3350 4800 60  0001 C CNN "Bauform"
F 7 "Value" H 3350 4800 60  0001 C CNN "Bestelllink"
	1    3350 4800
	-1   0    0    -1  
$EndComp
Connection ~ 4135 4700
Connection ~ 5080 3480
Wire Wire Line
	3700 4900 3755 4900
Wire Wire Line
	3755 4900 3755 5225
Wire Wire Line
	3755 5225 2645 5225
Wire Wire Line
	2645 4800 2645 5330
Wire Wire Line
	2405 4800 3000 4800
Text GLabel 2405 4800 0    60   Output ~ 0
A3
Connection ~ 2645 4800
Text Notes 2885 3440 0    60   ~ 0
In 28V
Text Notes 3940 3445 0    60   ~ 0
Out 16V
$Comp
L OP275 U5
U 2 1 56436B16
P 5670 1915
F 0 "U5" H 5670 2065 60  0000 L CNN
F 1 "OPA2340PA" H 5670 1765 60  0000 L CNN
F 2 "" H 5670 1915 60  0000 C CNN
F 3 "" H 5670 1915 60  0000 C CNN
F 4 "Value" H 5670 1915 60  0001 C CNN "Technische Daten"
F 5 "Value" H 5670 1915 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 5670 1915 60  0001 C CNN "Bauform"
F 7 "Value" H 5670 1915 60  0001 C CNN "Bestelllink"
	2    5670 1915
	1    0    0    -1  
$EndComp
Wire Wire Line
	5320 2015 5265 2015
Wire Wire Line
	5265 2015 5265 2680
Wire Wire Line
	5265 2680 6375 2680
Wire Wire Line
	6375 2680 6375 1915
Wire Wire Line
	6020 1915 6615 1915
Connection ~ 6375 1915
$Comp
L R R11
U 1 1 56436B9D
P 6765 1915
F 0 "R11" V 6870 1915 50  0000 C CNN
F 1 "1K" V 6645 1915 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6695 1915 30  0001 C CNN
F 3 "" H 6765 1915 30  0000 C CNN
F 4 "Value" H 6765 1915 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6765 1915 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6765 1915 60  0001 C CNN "Bauform"
F 7 "Value" H 6765 1915 60  0001 C CNN "Bestelllink"
	1    6765 1915
	0    1    -1   0   
$EndComp
$Comp
L R R8
U 1 1 5643711C
P 3935 1815
F 0 "R8" V 4040 1815 50  0000 C CNN
F 1 "47K" V 3815 1815 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3865 1815 30  0001 C CNN
F 3 "" H 3935 1815 30  0000 C CNN
F 4 "Value" H 3935 1815 60  0001 C CNN "Technische Daten"
F 5 "Value" H 3935 1815 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 3935 1815 60  0001 C CNN "Bauform"
F 7 "Value" H 3935 1815 60  0001 C CNN "Bestelllink"
	1    3935 1815
	0    1    -1   0   
$EndComp
$Comp
L D D3
U 1 1 564376AF
P 3550 1595
F 0 "D3" H 3550 1695 50  0000 C CNN
F 1 "1N4148" H 3550 1495 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" H 3550 1595 60  0001 C CNN
F 3 "" H 3550 1595 60  0000 C CNN
F 4 "Value" H 3550 1595 60  0001 C CNN "Technische Daten"
F 5 "Value" H 3550 1595 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 3550 1595 60  0001 C CNN "Bauform"
F 7 "Value" H 3550 1595 60  0001 C CNN "Bestelllink"
	1    3550 1595
	0    -1   1    0   
$EndComp
$Comp
L D D4
U 1 1 564376F9
P 3550 2040
F 0 "D4" H 3550 2140 50  0000 C CNN
F 1 "1N4148" H 3550 1940 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" H 3550 2040 60  0001 C CNN
F 3 "" H 3550 2040 60  0000 C CNN
F 4 "Value" H 3550 2040 60  0001 C CNN "Technische Daten"
F 5 "Value" H 3550 2040 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 3550 2040 60  0001 C CNN "Bauform"
F 7 "Value" H 3550 2040 60  0001 C CNN "Bestelllink"
	1    3550 2040
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR35
U 1 1 56437A9B
P 3550 1345
F 0 "#PWR35" H 3550 1435 20  0001 C CNN
F 1 "+5V" H 3550 1475 30  0000 C CNN
F 2 "" H 3550 1345 60  0000 C CNN
F 3 "" H 3550 1345 60  0000 C CNN
	1    3550 1345
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR36
U 1 1 56437C18
P 3550 2340
F 0 "#PWR36" H 3550 2090 60  0001 C CNN
F 1 "GND" H 3550 2190 60  0001 C CNN
F 2 "" H 3550 2340 60  0000 C CNN
F 3 "" H 3550 2340 60  0000 C CNN
F 4 "Value" H 3550 2340 60  0001 C CNN "Bestellnummer"
	1    3550 2340
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2340 3550 2190
Wire Wire Line
	3550 1745 3550 1890
Wire Wire Line
	3255 1815 3785 1815
Connection ~ 3550 1815
Wire Wire Line
	3550 1445 3550 1345
Wire Wire Line
	4085 1815 5320 1815
$Comp
L C C4
U 1 1 56438933
P 4295 2285
F 0 "C4" H 4320 2385 50  0000 L CNN
F 1 "220nF" H 4320 2185 50  0000 L CNN
F 2 "ACS712:C_Rect_L4_W2.5_P2.5_P5.0" H 4333 2135 30  0001 C CNN
F 3 "" H 4295 2285 60  0000 C CNN
F 4 "Value" H 4295 2285 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4295 2285 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4295 2285 60  0001 C CNN "Bauform"
F 7 "Value" H 4295 2285 60  0001 C CNN "Bestelllink"
	1    4295 2285
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 56438A30
P 2605 3795
F 0 "C3" H 2630 3895 50  0000 L CNN
F 1 "220uF/63V" H 2630 3695 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 2643 3645 30  0001 C CNN
F 3 "" H 2605 3795 60  0000 C CNN
F 4 "Value" H 2605 3795 60  0001 C CNN "Technische Daten"
F 5 "Value" H 2605 3795 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 2605 3795 60  0001 C CNN "Bauform"
F 7 "Value" H 2605 3795 60  0001 C CNN "Bestelllink"
	1    2605 3795
	1    0    0    -1  
$EndComp
$Comp
L CP C5
U 1 1 56439195
P 4350 3800
F 0 "C5" H 4375 3900 50  0000 L CNN
F 1 "220uF/63V" H 4375 3700 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 4388 3650 30  0001 C CNN
F 3 "" H 4350 3800 60  0000 C CNN
F 4 "Value" H 4350 3800 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4350 3800 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4350 3800 60  0001 C CNN "Bauform"
F 7 "Value" H 4350 3800 60  0001 C CNN "Bestelllink"
	1    4350 3800
	1    0    0    -1  
$EndComp
$Comp
L CP C7
U 1 1 56439786
P 4765 2285
F 0 "C7" H 4790 2385 50  0000 L CNN
F 1 "47uF/16V" H 4790 2185 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 4803 2135 30  0001 C CNN
F 3 "" H 4765 2285 60  0000 C CNN
F 4 "Value" H 4765 2285 60  0001 C CNN "Technische Daten"
F 5 "Value" H 4765 2285 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 4765 2285 60  0001 C CNN "Bauform"
F 7 "Value" H 4765 2285 60  0001 C CNN "Bestelllink"
	1    4765 2285
	1    0    0    -1  
$EndComp
Text GLabel 3255 1815 0    60   Output ~ 0
D11
Wire Wire Line
	4295 2135 4295 1815
Connection ~ 4295 1815
Wire Wire Line
	4765 2135 4765 1815
Connection ~ 4765 1815
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR40
U 1 1 5643A395
P 4765 2585
F 0 "#PWR40" H 4765 2335 60  0001 C CNN
F 1 "GND" H 4765 2435 60  0001 C CNN
F 2 "" H 4765 2585 60  0000 C CNN
F 3 "" H 4765 2585 60  0000 C CNN
F 4 "Value" H 4765 2585 60  0001 C CNN "Bestellnummer"
	1    4765 2585
	1    0    0    -1  
$EndComp
Wire Wire Line
	4765 2585 4765 2435
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR38
U 1 1 5643A3E7
P 4295 2585
F 0 "#PWR38" H 4295 2335 60  0001 C CNN
F 1 "GND" H 4295 2435 60  0001 C CNN
F 2 "" H 4295 2585 60  0000 C CNN
F 3 "" H 4295 2585 60  0000 C CNN
F 4 "Value" H 4295 2585 60  0001 C CNN "Bestellnummer"
	1    4295 2585
	1    0    0    -1  
$EndComp
Wire Wire Line
	4295 2585 4295 2435
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR42
U 1 1 5643A5C5
P 5570 2365
F 0 "#PWR42" H 5570 2115 60  0001 C CNN
F 1 "GND" H 5570 2215 60  0001 C CNN
F 2 "" H 5570 2365 60  0000 C CNN
F 3 "" H 5570 2365 60  0000 C CNN
F 4 "Value" H 5570 2365 60  0001 C CNN "Bestellnummer"
	1    5570 2365
	1    0    0    -1  
$EndComp
Wire Wire Line
	5570 2365 5570 2215
$Comp
L +5V #PWR41
U 1 1 5643A736
P 5570 1340
F 0 "#PWR41" H 5570 1430 20  0001 C CNN
F 1 "+5V" H 5570 1470 30  0000 C CNN
F 2 "" H 5570 1340 60  0000 C CNN
F 3 "" H 5570 1340 60  0000 C CNN
	1    5570 1340
	1    0    0    -1  
$EndComp
Wire Wire Line
	5570 1340 5570 1615
Text GLabel 7235 1915 2    60   Output ~ 0
DC_Wandler_Pin_4
Wire Wire Line
	6915 1915 7235 1915
Text Notes 7385 5080 0    60   ~ 0
 Abschluss-Widerstand ist mit 12Ohm 50Watt
Text Notes 1430 100  0    60   ~ 0
Ach ja die VCC also die +5V habe ich mir über die LED vom Sender geholt.\nAlso widerstand von der LED raus und Brücke rein die Anschlüsse genommen\n(5V+, GND) und auf den Regler hochgelegt. Kannst ja dort noch eine LED einplanen.\n\nja genau ich habe in meiner Skitze die 3 Anschlüsse bezeichnet.\nEs werden die Podi AD verwendet und D11 der muss dann auf \nder Senderplatine unterbrochen werden und wird als PWM für \nden DCDC verwendet. das rote bauteil ist der regler vom DCDC\nsitzt auf der DCDC Platine und wird auf PIN4 vom Regler über\n1KOhm mit dem PWM verbunden.\n\nHi Uwe wenn du lust und zeit hast kannst du dafür mal eine kleine Platine\nund einen richtigen Plan machen. Sollte die gleiche größe haben wie der Sender.\nBei IC1A die 22nF sind 220nF und bei IC1B die 220nF sind 47pF Keramik. \nIch schick dir noch ein Bild von meinem Testaufbau nur damit du dich\norientieren kannst.
$Comp
L CONN_01X06 P7
U 1 1 564320C3
P 8595 2710
F 0 "P7" H 8595 3060 50  0000 C CNN
F 1 "CONN_01X06" V 8695 2710 50  0000 C CNN
F 2 "" H 8595 2710 60  0000 C CNN
F 3 "" H 8595 2710 60  0000 C CNN
	1    8595 2710
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR48
U 1 1 564322B6
P 8920 2460
F 0 "#PWR48" H 8920 2550 20  0001 C CNN
F 1 "+5V" V 8920 2640 30  0000 C CNN
F 2 "" H 8920 2460 60  0000 C CNN
F 3 "" H 8920 2460 60  0000 C CNN
	1    8920 2460
	0    1    -1   0   
$EndComp
Wire Wire Line
	8795 2460 8920 2460
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR49
U 1 1 5643265A
P 8970 2560
F 0 "#PWR49" H 8970 2310 60  0001 C CNN
F 1 "GND" H 8970 2410 60  0001 C CNN
F 2 "" H 8970 2560 60  0000 C CNN
F 3 "" H 8970 2560 60  0000 C CNN
F 4 "Value" H 8970 2560 60  0001 C CNN "Bestellnummer"
	1    8970 2560
	0    -1   1    0   
$EndComp
Wire Wire Line
	8795 2560 8970 2560
Text GLabel 8970 2660 2    39   Output ~ 0
D11
Text GLabel 8970 2760 2    39   Output ~ 0
A3
Text GLabel 8970 2860 2    39   Output ~ 0
A7
Text GLabel 8970 2960 2    39   Output ~ 0
DC_Wandler_Pin_4
Wire Wire Line
	8795 2660 8970 2660
Wire Wire Line
	8795 2760 8970 2760
Wire Wire Line
	8795 2860 8970 2860
Wire Wire Line
	8795 2960 8970 2960
$Comp
L C C8
U 1 1 5643347B
P 6085 1575
F 0 "C8" H 6110 1675 50  0000 L CNN
F 1 "100nF" H 6110 1475 50  0000 L CNN
F 2 "ACS712:C_Rect_L4_W2.5_P2.5_P5.0" H 6123 1425 30  0001 C CNN
F 3 "" H 6085 1575 60  0000 C CNN
F 4 "Value" H 6085 1575 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6085 1575 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6085 1575 60  0001 C CNN "Bauform"
F 7 "Value" H 6085 1575 60  0001 C CNN "Bestelllink"
	1    6085 1575
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR44
U 1 1 564335B4
P 6085 1800
F 0 "#PWR44" H 6085 1550 60  0001 C CNN
F 1 "GND" H 6085 1650 60  0001 C CNN
F 2 "" H 6085 1800 60  0000 C CNN
F 3 "" H 6085 1800 60  0000 C CNN
F 4 "Value" H 6085 1800 60  0001 C CNN "Bestellnummer"
	1    6085 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6085 1800 6085 1725
Wire Wire Line
	5570 1425 6420 1425
Connection ~ 5570 1425
Text Notes 7210 -455 0    60   ~ 0
Hallo Uwe sehr schöne Arbeit\nBei der INA kannst du als Kondensator 1x 100nF und 1x 10uF Elko vorsehen \nBei den 220uF Kondensatoren sind 63V richtig. Bei den Elko für Pwm und INA reichen 16V aus. Da wir sicher Platz haben kannst du für den OP auch noch einen Elko 10uF 16V nehmen. \nDie Schutzdioden am Pwm sind 1N4148 (D4, D3) \nDer Verpolungsschutz ist eine MBR1045 auch der gegenspannungsschutz am Ausgang ist eine MBR1045\nDen Pwm out Pin 4 solltest du von der leiste lösen und als einzelnen darstellen da dieser später so dicht wie möglich an den dcdc wandler gebracht werden muss \nAm A3 kannst du noch proforma einen 10k widerstand gegen Masse einzeichnen mal sehen ob wir ihn nutzen \nHinten vor der Sicherung von Volt 24V kannst du noch einen varistor mit 24V einzeichnen \nWas die Platine angeht hast du genau recht die ist für uns zum testen. Wenn das so bei uns allen läuft machen wir eine V3 mit eigener MCU wie bei der BUMPERDUINO
$Comp
L CP_Small C?
U 1 1 5647BD45
P 7675 3585
F 0 "C?" H 7685 3655 50  0000 L CNN
F 1 "10uF/16V" H 7685 3505 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 7675 3585 60  0001 C CNN
F 3 "" H 7675 3585 60  0000 C CNN
F 4 "Value" H 7675 3585 60  0001 C CNN "Technische Daten"
F 5 "Value" H 7675 3585 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 7675 3585 60  0001 C CNN "Bauform"
F 7 "Value" H 7675 3585 60  0001 C CNN "Bestelllink"
	1    7675 3585
	1    0    0    -1  
$EndComp
Wire Wire Line
	7675 3450 7675 3485
Wire Wire Line
	7675 3710 7675 3685
$Comp
L DIODE D6
U 1 1 5647C163
P 5735 4480
F 0 "D6" H 5735 4580 50  0000 C CNN
F 1 "MBR 1045" H 5735 4380 50  0000 C CNN
F 2 "sender_v2:MBR1045_Horizontal" H 5735 4480 60  0001 C CNN
F 3 "" H 5735 4480 60  0000 C CNN
	1    5735 4480
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5647CDC7
P 2645 5480
F 0 "R?" H 2750 5480 50  0000 C CNN
F 1 "10K/1%" H 2860 5410 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2575 5480 30  0001 C CNN
F 3 "" H 2645 5480 30  0000 C CNN
F 4 "Value" H 2645 5480 60  0001 C CNN "Technische Daten"
F 5 "Value" H 2645 5480 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 2645 5480 60  0001 C CNN "Bauform"
F 7 "Value" H 2645 5480 60  0001 C CNN "Bestelllink"
	1    2645 5480
	1    0    0    -1  
$EndComp
Connection ~ 2645 5225
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR?
U 1 1 5647D0B9
P 2645 5725
F 0 "#PWR?" H 2645 5475 60  0001 C CNN
F 1 "GND" H 2645 5575 60  0001 C CNN
F 2 "" H 2645 5725 60  0000 C CNN
F 3 "" H 2645 5725 60  0000 C CNN
F 4 "Value" H 2645 5725 60  0001 C CNN "Bestellnummer"
	1    2645 5725
	1    0    0    -1  
$EndComp
Wire Wire Line
	2645 5725 2645 5630
$Comp
L CP_Small C?
U 1 1 5647D528
P 6420 1580
F 0 "C?" H 6430 1650 50  0000 L CNN
F 1 "10uF/16V" H 6430 1500 50  0000 L CNN
F 2 "ACS712:Elko_vert_11.2x6.3mm_RM2.5_RM5.0" H 6420 1580 60  0001 C CNN
F 3 "" H 6420 1580 60  0000 C CNN
F 4 "Value" H 6420 1580 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6420 1580 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6420 1580 60  0001 C CNN "Bauform"
F 7 "Value" H 6420 1580 60  0001 C CNN "Bestelllink"
	1    6420 1580
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR?
U 1 1 5647D587
P 6420 1800
F 0 "#PWR?" H 6420 1550 60  0001 C CNN
F 1 "GND" H 6420 1650 60  0001 C CNN
F 2 "" H 6420 1800 60  0000 C CNN
F 3 "" H 6420 1800 60  0000 C CNN
F 4 "Value" H 6420 1800 60  0001 C CNN "Bestellnummer"
	1    6420 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6420 1680 6420 1800
Wire Wire Line
	6420 1425 6420 1480
Connection ~ 6085 1425
$Comp
L VR 24V
U 1 1 5647DE3C
P 6095 4495
F 0 "24V" V 6155 4449 50  0000 C TNN
F 1 "VR" V 6095 4495 50  0000 C CNN
F 2 "Varistors:RV_Disc_D7_W3.4_P5" H 6095 4495 60  0001 C CNN
F 3 "" H 6095 4495 60  0000 C CNN
F 4 "Value" H 6095 4495 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6095 4495 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6095 4495 60  0001 C CNN "Bauform"
F 7 "Value" H 6095 4495 60  0001 C CNN "Bestelllink"
	1    6095 4495
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Perimeter_sender_v2 #PWR?
U 1 1 5647E1F7
P 6095 4805
F 0 "#PWR?" H 6095 4555 60  0001 C CNN
F 1 "GND" H 6095 4655 60  0001 C CNN
F 2 "" H 6095 4805 60  0000 C CNN
F 3 "" H 6095 4805 60  0000 C CNN
F 4 "Value" H 6095 4805 60  0001 C CNN "Bestellnummer"
	1    6095 4805
	1    0    0    -1  
$EndComp
Wire Wire Line
	6095 4745 6095 4805
Wire Wire Line
	6095 4245 6095 4095
Connection ~ 6095 4095
$EndSCHEMATC
