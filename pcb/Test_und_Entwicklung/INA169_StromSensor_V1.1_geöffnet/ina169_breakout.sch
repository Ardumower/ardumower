EESchema Schematic File Version 4
LIBS:ina169_breakout-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "INA169_StromSensor"
Date "2017-11-30"
Rev "V1.1"
Comp "Uwe Zimprich"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 5850 3500 2    60   ~ 0
Rshunt (RS)\nSMD CRM2512-FX-R100ELF
Text Notes 2550 2750 0    60   ~ 0
INA169 DC Current Sensor \nVCC/Vin: 2.7-60V\nMax Current: 5.0A (1V/Amp)\nVout=RL/10K*I(Amps)
Text Notes 6550 2850 0    60   ~ 0
http://de.wikipedia.org/wiki/Chip-Bauform
Wire Wire Line
	4000 2400 4000 4535
Wire Wire Line
	4890 2400 4000 2400
Connection ~ 4000 4535
Wire Wire Line
	5940 2300 6250 2300
Wire Wire Line
	6250 2050 6250 2300
Wire Wire Line
	6250 3545 6250 5035
Wire Wire Line
	3200 4535 4000 4535
Wire Wire Line
	4100 2500 4270 2500
Wire Wire Line
	5940 2500 5950 2500
Connection ~ 5950 3250
Wire Wire Line
	3900 2300 4200 2300
Wire Wire Line
	6250 2050 3800 2050
Wire Wire Line
	3800 2050 3800 4435
Wire Wire Line
	3800 4435 3200 4435
Connection ~ 6250 2300
Wire Wire Line
	4270 3250 5300 3250
Wire Wire Line
	5600 3250 5950 3250
Wire Wire Line
	5950 4635 3200 4635
Wire Wire Line
	5950 2500 5950 3250
Wire Wire Line
	3900 2300 3900 4835
Wire Wire Line
	3900 4835 3200 4835
Wire Wire Line
	4100 4735 3200 4735
Wire Wire Line
	4100 2500 4100 4735
Wire Wire Line
	4270 2500 4270 3250
Connection ~ 4270 2500
Wire Wire Line
	4200 3070 4200 3825
Wire Wire Line
	4200 4375 4200 4535
Wire Wire Line
	4200 2300 4200 2770
Connection ~ 4200 2300
$Comp
L ina169_breakout-rescue:C-RESCUE-ina169_breakout C1
U 1 1 587A6051
P 6250 3395
F 0 "C1" H 6365 3441 50  0000 L CNN
F 1 "0.1uF" H 6365 3350 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 6365 3304 50  0001 L CNN
F 3 "" H 6250 3395 50  0000 C CNN
F 4 "Value" H 6250 3395 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6250 3395 60  0001 C CNN "Bestelllink"
F 6 "SMD 12 X7R-G1206 100N" H 6250 3395 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6250 3395 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6250 3395 60  0001 C CNN "Bauform"
F 9 "Value" H 6250 3395 60  0001 C CNN "Funktion"
F 10 "Value" H 6250 3395 60  0001 C CNN "Hersteller"
F 11 "Value" H 6250 3395 60  0001 C CNN "Hersteller Bestellnummer"
	1    6250 3395
	1    0    0    -1  
$EndComp
$Comp
L ina169_breakout-rescue:INA169_IC-RESCUE-ina169_breakout U1
U 1 1 587A66BB
P 5440 2450
F 0 "U1" H 5415 2887 60  0000 C CNN
F 1 "INA169_IC" H 5415 2781 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 5415 2781 60  0001 C CNN
F 3 "" H 5440 2150 60  0000 C CNN
F 4 "Value" H 5440 2450 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5440 2450 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5440 2450 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5440 2450 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5440 2450 60  0001 C CNN "Bauform"
F 9 "Value" H 5440 2450 60  0001 C CNN "Funktion"
F 10 "Value" H 5440 2450 60  0001 C CNN "Hersteller"
F 11 "Value" H 5440 2450 60  0001 C CNN "Hersteller Bestellnummer"
	1    5440 2450
	1    0    0    -1  
$EndComp
$Comp
L ina169_breakout-rescue:R-RESCUE-ina169_breakout R3
U 1 1 587A6B3F
P 4200 4225
F 0 "R3" H 4288 4271 50  0000 L CNN
F 1 "10K 1%" H 4288 4180 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 4288 4134 50  0001 L CNN
F 3 "" H 4200 4225 50  0000 C CNN
F 4 "Value" H 4200 4225 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4200 4225 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4200 4225 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4200 4225 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4200 4225 60  0001 C CNN "Bauform"
F 9 "Value" H 4200 4225 60  0001 C CNN "Funktion"
F 10 "Value" H 4200 4225 60  0001 C CNN "Hersteller"
F 11 "Value" H 4200 4225 60  0001 C CNN "Hersteller Bestellnummer"
	1    4200 4225
	1    0    0    -1  
$EndComp
$Comp
L ina169_breakout-rescue:R-RESCUE-ina169_breakout R2
U 1 1 587A79B6
P 4200 2920
F 0 "R2" H 4288 2966 50  0000 L CNN
F 1 "10K 1%" H 4288 2875 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 4288 2829 50  0001 L CNN
F 3 "" H 4200 2920 50  0000 C CNN
F 4 "Value" H 4200 2920 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4200 2920 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4200 2920 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4200 2920 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4200 2920 60  0001 C CNN "Bauform"
F 9 "Value" H 4200 2920 60  0001 C CNN "Funktion"
F 10 "Value" H 4200 2920 60  0001 C CNN "Hersteller"
F 11 "Value" H 4200 2920 60  0001 C CNN "Hersteller Bestellnummer"
	1    4200 2920
	1    0    0    -1  
$EndComp
Text Notes 5140 2915 2    60   ~ 0
Load resistor (RL)\nSMD-0603 10K
$Comp
L ina169_breakout-rescue:R-RESCUE-ina169_breakout R1
U 1 1 587A7CC4
P 5450 3250
F 0 "R1" V 5243 3250 50  0000 C CNN
F 1 "0.1 1% 2W" V 5334 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_2512" H 5538 3159 50  0001 L CNN
F 3 "" H 5450 3250 50  0000 C CNN
F 4 "Value" H 5450 3250 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5450 3250 60  0001 C CNN "Bestelllink"
F 6 "SMD CRM2512-FX-R100ELF" H 5450 3250 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5450 3250 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5450 3250 60  0001 C CNN "Bauform"
F 9 "Value" H 5450 3250 60  0001 C CNN "Funktion"
F 10 "Value" H 5450 3250 60  0001 C CNN "Hersteller"
F 11 "Value" H 5450 3250 60  0001 C CNN "Hersteller Bestellnummer"
	1    5450 3250
	0    -1   1    0   
$EndComp
$Comp
L ina169_breakout-rescue:GND-RESCUE-ina169_breakout #PWR01
U 1 1 587A819B
P 4000 5035
F 0 "#PWR01" H 4000 4785 50  0001 C CNN
F 1 "GND" H 4005 4862 50  0000 C CNN
F 2 "" H 4000 5035 50  0000 C CNN
F 3 "" H 4000 5035 50  0000 C CNN
	1    4000 5035
	1    0    0    -1  
$EndComp
$Comp
L ina169_breakout-rescue:GND-RESCUE-ina169_breakout #PWR02
U 1 1 587A8262
P 6250 5035
F 0 "#PWR02" H 6250 4785 50  0001 C CNN
F 1 "GND" H 6255 4862 50  0000 C CNN
F 2 "" H 6250 5035 50  0000 C CNN
F 3 "" H 6250 5035 50  0000 C CNN
	1    6250 5035
	1    0    0    -1  
$EndComp
Text Label 3325 4435 0    60   ~ 0
VCC
Text Label 3325 4535 0    60   ~ 0
GND
Text Label 3340 4635 0    60   ~ 0
Vin-
Text Label 3345 4735 0    60   ~ 0
Vin+
Text Label 3350 4835 0    60   ~ 0
Out
$Comp
L ina169_breakout-rescue:CONN_01X05-RESCUE-ina169_breakout J1
U 1 1 587A8695
P 3000 4635
F 0 "J1" H 3078 4676 50  0000 L CNN
F 1 "INA169 Breakout 2,5 / 5A (short pad JP1)" H 3078 4585 50  0000 L CNN
F 2 "Zimprich:ina169_breakout_footprint_mit_unterem_Lötpad" H 3000 4635 50  0001 C CNN
F 3 "" H 3000 4635 50  0000 C CNN
F 4 "Value" H 3000 4635 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3000 4635 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3000 4635 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3000 4635 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3000 4635 60  0001 C CNN "Bauform"
F 9 "Value" H 3000 4635 60  0001 C CNN "Funktion"
F 10 "Value" H 3000 4635 60  0001 C CNN "Hersteller"
F 11 "Value" H 3000 4635 60  0001 C CNN "Hersteller Bestellnummer"
	1    3000 4635
	-1   0    0    -1  
$EndComp
$Comp
L device:Jumper JP1
U 1 1 5A20683E
P 4665 3825
F 0 "JP1" H 4665 4089 50  0000 C CNN
F 1 "5A" H 4665 3998 50  0000 C CNN
F 2 "Connectors:GS2" H 4665 3825 50  0001 C CNN
F 3 "" H 4665 3825 50  0001 C CNN
	1    4665 3825
	1    0    0    -1  
$EndComp
Wire Wire Line
	5030 4535 5030 3825
Wire Wire Line
	5030 3825 4965 3825
Connection ~ 4200 4535
Wire Wire Line
	4365 3825 4200 3825
Connection ~ 4200 3825
$Comp
L zimprich:Symbol_leer H1
U 1 1 5A20ED28
P 6350 7530
F 0 "H1" H 6458 7572 45  0000 L CNN
F 1 "Mülleimer" H 6458 7488 45  0000 L CNN
F 2 "Symbols:WEEE-Logo_4.2x6mm_SilkScreen" H 6380 7680 20  0001 C CNN
F 3 "" H 6350 7530 60  0001 C CNN
	1    6350 7530
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4535 4000 5035
Wire Wire Line
	4000 4535 4200 4535
Wire Wire Line
	5950 3250 5950 4635
Wire Wire Line
	6250 2300 6250 3245
Wire Wire Line
	4270 2500 4890 2500
Wire Wire Line
	4200 2300 4890 2300
Wire Wire Line
	4200 4535 5030 4535
Wire Wire Line
	4200 3825 4200 4075
$EndSCHEMATC
