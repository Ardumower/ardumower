EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
LIBS:ina169_ic
LIBS:DS1307_Dil8
LIBS:device
LIBS:supply
LIBS:atmel
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 26 25
Title ""
Date ""
Rev ""
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4220 3800 0    60   Input ~ 0
VCC
Text HLabel 4220 3900 0    60   Output ~ 0
GND
Text HLabel 4220 4200 0    60   Output ~ 0
Out
Text HLabel 4220 4100 0    60   Input ~ 0
Vin+
Text HLabel 4220 4000 0    60   Output ~ 0
Vin-
$Comp
L R R42
U 1 1 55DE7623
P 5220 2800
F 0 "R42" V 5130 2790 50  0000 C CNN
F 1 "10K 1%" V 5227 2801 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5150 2800 30  0001 C CNN
F 3 "" H 5220 2800 30  0000 C CNN
	1    5220 2800
	1    0    0    -1  
$EndComp
$Comp
L R R44
U 1 1 55DE7624
P 6470 3150
F 0 "R44" V 6550 3150 50  0000 C CNN
F 1 "0.1 1% 2W" V 6477 3151 50  0000 C CNN
F 2 "Resistors_SMD:R_2512" V 6400 3150 30  0001 C CNN
F 3 "" H 6470 3150 30  0000 C CNN
F 4 "Value" H 6470 3150 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6470 3150 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6470 3150 60  0001 C CNN "Bauform"
	1    6470 3150
	0    -1   -1   0   
$EndComp
$Comp
L C C14
U 1 1 55DE7626
P 7270 3300
F 0 "C14" H 7320 3400 50  0000 L CNN
F 1 "0.1uF" H 7320 3200 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7308 3150 30  0001 C CNN
F 3 "" H 7270 3300 60  0000 C CNN
F 4 "Vielschicht-Keramikkondensator 100N, 10% 63V" H 7270 3300 60  0001 C CNN "Technische Daten"
F 5 "R: X7R-G1206 100N" H 7270 3300 60  0001 C CNN "Bestellnummer"
F 6 "1206" H 7270 3300 60  0001 C CNN "Bauform"
F 7 "https://www.reichelt.de/X7R-G1206-100N/3/index.html?&ACTION=3&LA=446&ARTICLE=22889&artnr=X7R-G1206+100N&SEARCH=X7R-G1206" H 7270 3300 60  0001 C CNN "Bestelllink"
	1    7270 3300
	1    0    0    -1  
$EndComp
$Comp
L INA169_IC U4
U 1 1 55DE7627
P 6460 2350
F 0 "U4" H 6460 2650 60  0000 C CNN
F 1 "INA169_IC" H 6460 2050 60  0000 C CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23-5" H 6460 2050 60  0001 C CNN
F 3 "" H 6460 2050 60  0000 C CNN
F 4 "Value" H 6460 2350 60  0001 C CNN "Technische Daten"
F 5 "Value" H 6460 2350 60  0001 C CNN "Bestellnummer"
F 6 "Value" H 6460 2350 60  0001 C CNN "Bauform"
	1    6460 2350
	1    0    0    -1  
$EndComp
Text Notes 6870 3400 2    39   ~ 0
Rshunt (RS)\nSMD CRM2512-FX-R100ELF
Text Notes 5445 3070 1    39   ~ 0
Load resistor (RL)\nSMD-0603 10K
Text Notes 3570 2650 0    39   ~ 0
INA169 DC Current Sensor \nVCC/Vin: 2.7-60V\nMax Current: 5.0A (1V/Amp)\nVout=RL/10K*I(Amps)
Text Notes 7520 3300 0    39   ~ 0
SMD 12 X7R-G1206 100N
Text Notes 6220 2800 0    60   ~ 0
SOT23-5
Text Notes 7570 2750 0    39   ~ 0
http://de.wikipedia.org/wiki/Chip-Bauform
$Comp
L R R43
U 1 1 55DE7629
P 5220 3600
F 0 "R43" V 5130 3590 50  0000 C CNN
F 1 "10K 1%" V 5227 3601 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5150 3600 30  0001 C CNN
F 3 "" H 5220 3600 30  0000 C CNN
	1    5220 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5910 2300 5020 2300
Connection ~ 5020 3900
Wire Wire Line
	6960 2200 7270 2200
Wire Wire Line
	7270 1950 7270 3100
Wire Wire Line
	4220 3900 7270 3900
Wire Wire Line
	5120 2400 5910 2400
Wire Wire Line
	6960 2400 6970 2400
Connection ~ 6970 3150
Wire Wire Line
	4920 2200 5910 2200
Wire Wire Line
	7270 1950 4820 1950
Wire Wire Line
	4820 1950 4820 3800
Wire Wire Line
	4820 3800 4220 3800
Connection ~ 7270 2200
Wire Wire Line
	5290 3150 6220 3150
Wire Wire Line
	6970 3150 6720 3150
Wire Wire Line
	6970 4000 4220 4000
Wire Wire Line
	6970 2400 6970 4000
Wire Wire Line
	4920 2200 4920 4200
Wire Wire Line
	4920 4200 4220 4200
Wire Wire Line
	5120 4100 4220 4100
Wire Wire Line
	5120 2400 5120 4100
Wire Wire Line
	5290 2400 5290 3150
Connection ~ 5290 2400
Wire Wire Line
	5220 3050 5220 3350
Wire Wire Line
	5220 3900 5220 3850
Wire Wire Line
	5220 2550 5220 2200
Connection ~ 5220 2200
Text Notes 4485 5160 0    60   ~ 0
(26.08.2015)\nSchaltplan von INA169 Breakboard importiert\nJumper entfernt und durch hirarischere Variablen ersetzt\nGnd Anschluß von Kondensator auf gnd Anschluß hirarischer Pin umgeändert
Wire Wire Line
	7270 3900 7270 3500
Connection ~ 5220 3900
Wire Wire Line
	5020 2300 5020 3900
$Comp
L JUMPER JP12
U 1 1 55EE25EF
P 5665 3550
F 0 "JP12" H 5665 3700 60  0000 C CNN
F 1 "Messbereich 5A/2,5A" H 5665 3470 40  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x02" H 5665 3550 60  0001 C CNN
F 3 "" H 5665 3550 60  0000 C CNN
	1    5665 3550
	0    -1   1    0   
$EndComp
Wire Wire Line
	5665 3850 5665 3900
Connection ~ 5665 3900
Wire Wire Line
	5665 3250 5220 3250
Connection ~ 5220 3250
$EndSCHEMATC
