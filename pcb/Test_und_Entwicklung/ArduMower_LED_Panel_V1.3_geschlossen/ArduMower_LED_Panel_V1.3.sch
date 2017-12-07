EESchema Schematic File Version 2
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
LIBS:Zimprich
LIBS:logo
LIBS:ArduMower_LED_Panel_V1.3-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Ardumower _LED_Panel_V1.3"
Date "2017-07-14"
Rev "1.3"
Comp "ML AG JL UZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Speaker SP1
U 1 1 59517E25
P 3955 3685
F 0 "SP1" V 4175 3650 70  0000 C CNN
F 1 "Buzzer" V 4290 3665 70  0000 C CNN
F 2 "Zimprich:Buzzer_12x9.5RM7.6_RM5.0" H 3955 3685 60  0001 C CNN
F 3 "" H 3955 3685 60  0001 C CNN
F 4 "Value" H 3955 3685 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3955 3685 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3955 3685 60  0001 C CNN "Technische Daten"
F 7 "R: SUMMER TDB 05" H 3955 3685 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3955 3685 60  0001 C CNN "Bauform"
F 9 "Value" H 3955 3685 60  0001 C CNN "Funktion"
F 10 "Value" H 3955 3685 60  0001 C CNN "Hersteller"
F 11 "Value" H 3955 3685 60  0001 C CNN "Hersteller Bestellnummer"
	1    3955 3685
	0    -1   1    0   
$EndComp
$Comp
L CONN_02X07 P1
U 1 1 59517E64
P 5200 3080
F 0 "P1" H 5200 3595 50  0000 C CNN
F 1 "Led Panel" H 5200 3504 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_2x07_Pitch2.54mm" H -3335 -2265 50  0001 C CNN
F 3 "" H -3335 -2265 50  0001 C CNN
F 4 "Value" H 5200 3080 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5200 3080 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5200 3080 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5200 3080 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5200 3080 60  0001 C CNN "Bauform"
F 9 "Value" H 5200 3080 60  0001 C CNN "Funktion"
F 10 "Value" H 5200 3080 60  0001 C CNN "Hersteller"
F 11 "Value" H 5200 3080 60  0001 C CNN "Hersteller Bestellnummer"
	1    5200 3080
	1    0    0    -1  
$EndComp
Text Label 4340 3380 0    31   ~ 0
Buzzer
Text Label 5595 3280 0    31   ~ 0
GPS_LED
Text Label 4340 3280 0    31   ~ 0
PinCharging_Enable
Text Label 5600 3180 0    31   ~ 0
Wlan
Text Label 4340 3180 0    31   ~ 0
Bluetooth
Text Label 5595 3080 0    31   ~ 0
Led_Status
Text Label 4340 3080 0    31   ~ 0
Duo_Led_Rot
Text Label 5595 2980 0    31   ~ 0
Duo_Led_grün
$Comp
L LED D5
U 1 1 59518EB3
P 7720 2780
F 0 "D5" H 7500 2820 50  0000 C CNN
F 1 "Station" H 7235 2820 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 7720 2780 50  0001 C CNN
F 3 "" H 7720 2780 50  0001 C CNN
	1    7720 2780
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5952ECC8
P 4050 2980
F 0 "D1" H 3855 3020 50  0000 C CNN
F 1 "24V" H 3725 3020 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4050 2980 50  0001 C CNN
F 3 "" H 4050 2980 50  0001 C CNN
	1    4050 2980
	1    0    0    -1  
$EndComp
$Comp
L LED D6
U 1 1 595304D8
P 6825 2980
F 0 "D6" H 7035 3015 50  0000 C CNN
F 1 "LED_grün" H 7350 3015 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 6825 2980 50  0001 C CNN
F 3 "" H 6825 2980 50  0001 C CNN
F 4 "Value" H 6825 2980 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6825 2980 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6825 2980 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6825 2980 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6825 2980 60  0001 C CNN "Bauform"
F 9 "Value" H 6825 2980 60  0001 C CNN "Funktion"
F 10 "Value" H 6825 2980 60  0001 C CNN "Hersteller"
F 11 "Value" H 6825 2980 60  0001 C CNN "Hersteller Bestellnummer"
	1    6825 2980
	-1   0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 595306A8
P 3570 3080
F 0 "D2" H 3360 3115 50  0000 C CNN
F 1 "Led_rot" H 3065 3115 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3570 3080 50  0001 C CNN
F 3 "" H 3570 3080 50  0001 C CNN
F 4 "Value" H 3570 3080 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3570 3080 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3570 3080 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3570 3080 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3570 3080 60  0001 C CNN "Bauform"
F 9 "Value" H 3570 3080 60  0001 C CNN "Funktion"
F 10 "Value" H 3570 3080 60  0001 C CNN "Hersteller"
F 11 "Value" H 3570 3080 60  0001 C CNN "Hersteller Bestellnummer"
	1    3570 3080
	1    0    0    -1  
$EndComp
$Comp
L LED D7
U 1 1 595308D8
P 7720 3080
F 0 "D7" H 7935 3120 50  0000 C CNN
F 1 "Status" H 8200 3120 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 7720 3080 50  0001 C CNN
F 3 "" H 7720 3080 50  0001 C CNN
F 4 "Value" H 7720 3080 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7720 3080 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7720 3080 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7720 3080 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7720 3080 60  0001 C CNN "Bauform"
F 9 "Value" H 7720 3080 60  0001 C CNN "Funktion"
F 10 "Value" H 7720 3080 60  0001 C CNN "Hersteller"
F 11 "Value" H 7720 3080 60  0001 C CNN "Hersteller Bestellnummer"
	1    7720 3080
	-1   0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 59530AC8
P 4050 3180
F 0 "D3" H 3825 3215 50  0000 C CNN
F 1 "Bluetooth" H 3590 3220 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4050 3180 50  0001 C CNN
F 3 "" H 4050 3180 50  0001 C CNN
F 4 "Value" H 4050 3180 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4050 3180 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4050 3180 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4050 3180 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4050 3180 60  0001 C CNN "Bauform"
F 9 "Value" H 4050 3180 60  0001 C CNN "Funktion"
F 10 "Value" H 4050 3180 60  0001 C CNN "Hersteller"
F 11 "Value" H 4050 3180 60  0001 C CNN "Hersteller Bestellnummer"
	1    4050 3180
	1    0    0    -1  
$EndComp
$Comp
L LED D8
U 1 1 59530C9A
P 6825 3180
F 0 "D8" H 7030 3215 50  0000 C CNN
F 1 "Wlan" H 7180 3215 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 6825 3180 50  0001 C CNN
F 3 "" H 6825 3180 50  0001 C CNN
F 4 "Value" H 6825 3180 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6825 3180 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6825 3180 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6825 3180 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6825 3180 60  0001 C CNN "Bauform"
F 9 "Value" H 6825 3180 60  0001 C CNN "Funktion"
F 10 "Value" H 6825 3180 60  0001 C CNN "Hersteller"
F 11 "Value" H 6825 3180 60  0001 C CNN "Hersteller Bestellnummer"
	1    6825 3180
	-1   0    0    -1  
$EndComp
$Comp
L LED D4
U 1 1 59530EEA
P 3575 3280
F 0 "D4" H 3355 3320 50  0000 C CNN
F 1 "Relais" H 2915 3320 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3575 3280 50  0001 C CNN
F 3 "" H 3575 3280 50  0001 C CNN
F 4 "Value" H 3575 3280 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3575 3280 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3575 3280 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3575 3280 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3575 3280 60  0001 C CNN "Bauform"
F 9 "Value" H 3575 3280 60  0001 C CNN "Funktion"
F 10 "Value" H 3575 3280 60  0001 C CNN "Hersteller"
F 11 "Value" H 3575 3280 60  0001 C CNN "Hersteller Bestellnummer"
	1    3575 3280
	1    0    0    -1  
$EndComp
$Comp
L LED D9
U 1 1 59531322
P 7720 3280
F 0 "D9" H 7930 3315 50  0000 C CNN
F 1 "GPS" H 8145 3315 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 7720 3280 50  0001 C CNN
F 3 "" H 7720 3280 50  0001 C CNN
F 4 "Value" H 7720 3280 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7720 3280 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7720 3280 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7720 3280 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7720 3280 60  0001 C CNN "Bauform"
F 9 "Value" H 7720 3280 60  0001 C CNN "Funktion"
F 10 "Value" H 7720 3280 60  0001 C CNN "Hersteller"
F 11 "Value" H 7720 3280 60  0001 C CNN "Hersteller Bestellnummer"
	1    7720 3280
	-1   0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 595323DF
P 3550 2780
F 0 "SW1" H 3550 3035 50  0000 C CNN
F 1 "Button" H 3550 2944 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h8.5mm" H 3550 2780 60  0001 C CNN
F 3 "" H 3550 2780 60  0000 C CNN
	1    3550 2780
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 59585CEC
P 8615 3080
F 0 "#PWR02" H 8615 2830 60  0001 C CNN
F 1 "GND" V 8615 2855 60  0000 C CNN
F 2 "" H 8615 3080 60  0000 C CNN
F 3 "" H 8615 3080 60  0000 C CNN
	1    8615 3080
	0    -1   -1   0   
$EndComp
Text Label 5600 3380 0    31   ~ 0
GND
Text Label 4340 2980 0    31   ~ 0
24V
Text Label 4340 2880 0    31   ~ 0
24V_GND
Text Label 4340 2780 0    31   ~ 0
Taster
Text Label 5595 2880 0    31   ~ 0
StationLed
Text Label 5595 2780 0    31   ~ 0
StationLed_GND
$Comp
L CONN_01X05 P5
U 1 1 595D7A27
P 4740 4830
F 0 "P5" V 4900 4830 50  0000 L CNN
F 1 "CONN_01X05" V 4825 4605 50  0000 L CNN
F 2 "Connectors_JST:JST_XH_S05B-XH-A_05x2.50mm_Angled" H 4740 4830 50  0001 C CNN
F 3 "" H 4740 4830 50  0001 C CNN
	1    4740 4830
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 595D7AA8
P 3395 5870
F 0 "SW2" H 3395 6125 50  0000 C CNN
F 1 "SW_PUSH" H 3395 6034 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h8.5mm" H 3395 5870 60  0001 C CNN
F 3 "" H 3395 5870 60  0000 C CNN
	1    3395 5870
	1    0    0    -1  
$EndComp
$Comp
L LED D10
U 1 1 595D7B3C
P 3440 5355
F 0 "D10" H 3440 5440 50  0000 C CNN
F 1 "AnhebeS." H 3440 5505 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3440 5355 50  0001 C CNN
F 3 "" H 3440 5355 50  0001 C CNN
F 4 "Value" H 3440 5355 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3440 5355 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3440 5355 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3440 5355 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3440 5355 60  0001 C CNN "Bauform"
F 9 "Value" H 3440 5355 60  0001 C CNN "Funktion"
F 10 "Value" H 3440 5355 60  0001 C CNN "Hersteller"
F 11 "Value" H 3440 5355 60  0001 C CNN "Hersteller Bestellnummer"
	1    3440 5355
	1    0    0    -1  
$EndComp
$Comp
L Speaker SP2
U 1 1 595D7BE3
P 3340 6285
F 0 "SP2" V 3560 6250 70  0000 C CNN
F 1 "SPEAKER" V 3675 6265 70  0000 C CNN
F 2 "Zimprich:Buzzer_12x9.5RM7.6_RM5.0" H 3340 6285 60  0001 C CNN
F 3 "" H 3340 6285 60  0001 C CNN
F 4 "Value" H 3340 6285 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3340 6285 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3340 6285 60  0001 C CNN "Technische Daten"
F 7 "R: SUMMER TDB 05" H 3340 6285 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3340 6285 60  0001 C CNN "Bauform"
F 9 "Value" H 3340 6285 60  0001 C CNN "Funktion"
F 10 "Value" H 3340 6285 60  0001 C CNN "Hersteller"
F 11 "Value" H 3340 6285 60  0001 C CNN "Hersteller Bestellnummer"
	1    3340 6285
	0    -1   1    0   
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 595D7C6F
P 3415 7385
F 0 "P2" V 3590 7360 50  0000 L CNN
F 1 "AnhebeS." V 3515 7170 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02_Pitch2.54mm" H 3415 7385 50  0001 C CNN
F 3 "" H 3415 7385 50  0001 C CNN
	1    3415 7385
	0    -1   1    0   
$EndComp
$Comp
L R R1
U 1 1 595D7D04
P 4005 5355
F 0 "R1" V 4150 5330 50  0000 L CNN
F 1 "220" V 4080 5285 50  0000 L CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3935 5355 50  0001 C CNN
F 3 "" H 4005 5355 50  0001 C CNN
F 4 "Value" H 4005 5355 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4005 5355 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4005 5355 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4005 5355 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4005 5355 60  0001 C CNN "Bauform"
F 9 "Value" H 4005 5355 60  0001 C CNN "Funktion"
F 10 "Value" H 4005 5355 60  0001 C CNN "Hersteller"
F 11 "Value" H 4005 5355 60  0001 C CNN "Hersteller Bestellnummer"
	1    4005 5355
	0    -1   -1   0   
$EndComp
$Comp
L GNDD #PWR01
U 1 1 595DB2B7
P 2590 7215
F 0 "#PWR01" H 2590 6965 50  0001 C CNN
F 1 "GNDD" H 2594 7060 50  0000 C CNN
F 2 "" H 2590 7215 50  0001 C CNN
F 3 "" H 2590 7215 50  0001 C CNN
	1    2590 7215
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 595DBCF1
P 3555 2170
F 0 "P3" V 3730 2145 50  0000 L CNN
F 1 "Button EX." V 3655 1955 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02_Pitch2.54mm" H 3555 2170 50  0001 C CNN
F 3 "" H 3555 2170 50  0001 C CNN
	1    3555 2170
	0    -1   -1   0   
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B4
U 1 1 595E76B5
P 9040 5375
F 0 "B4" H 9144 5428 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9144 5322 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9144 5269 60  0001 L CNN
F 3 "" H 9040 5375 60  0000 C CNN
F 4 "Value" H 9040 5375 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9040 5375 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9040 5375 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9040 5375 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9040 5375 60  0001 C CNN "Bauform"
F 9 "Value" H 9040 5375 60  0001 C CNN "Funktion"
F 10 "Value" H 9040 5375 60  0001 C CNN "Hersteller"
F 11 "Value" H 9040 5375 60  0001 C CNN "Hersteller Bestellnummer"
	1    9040 5375
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B3
U 1 1 595E7943
P 9040 5140
F 0 "B3" H 9144 5193 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9144 5087 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9144 5034 60  0001 L CNN
F 3 "" H 9040 5140 60  0000 C CNN
F 4 "Value" H 9040 5140 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9040 5140 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9040 5140 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9040 5140 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9040 5140 60  0001 C CNN "Bauform"
F 9 "Value" H 9040 5140 60  0001 C CNN "Funktion"
F 10 "Value" H 9040 5140 60  0001 C CNN "Hersteller"
F 11 "Value" H 9040 5140 60  0001 C CNN "Hersteller Bestellnummer"
	1    9040 5140
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B2
U 1 1 595E79AE
P 9035 4900
F 0 "B2" H 9139 4953 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9139 4847 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9139 4794 60  0001 L CNN
F 3 "" H 9035 4900 60  0000 C CNN
F 4 "Value" H 9035 4900 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9035 4900 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9035 4900 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9035 4900 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9035 4900 60  0001 C CNN "Bauform"
F 9 "Value" H 9035 4900 60  0001 C CNN "Funktion"
F 10 "Value" H 9035 4900 60  0001 C CNN "Hersteller"
F 11 "Value" H 9035 4900 60  0001 C CNN "Hersteller Bestellnummer"
	1    9035 4900
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B1
U 1 1 595E7A32
P 9030 4655
F 0 "B1" H 9134 4708 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9134 4602 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9134 4549 60  0001 L CNN
F 3 "" H 9030 4655 60  0000 C CNN
F 4 "Value" H 9030 4655 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9030 4655 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9030 4655 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9030 4655 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9030 4655 60  0001 C CNN "Bauform"
F 9 "Value" H 9030 4655 60  0001 C CNN "Funktion"
F 10 "Value" H 9030 4655 60  0001 C CNN "Hersteller"
F 11 "Value" H 9030 4655 60  0001 C CNN "Hersteller Bestellnummer"
	1    9030 4655
	1    0    0    -1  
$EndComp
Text Notes 3315 4865 0    60   ~ 0
Bumperduino
$Comp
L LED D12
U 1 1 595E8222
P 4010 4220
F 0 "D12" H 4010 4025 50  0000 C CNN
F 1 "Buzzer" H 4010 4105 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4010 4220 50  0001 C CNN
F 3 "" H 4010 4220 50  0001 C CNN
F 4 "Value" H 4010 4220 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4010 4220 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4010 4220 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4010 4220 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4010 4220 60  0001 C CNN "Bauform"
F 9 "Value" H 4010 4220 60  0001 C CNN "Funktion"
F 10 "Value" H 4010 4220 60  0001 C CNN "Hersteller"
F 11 "Value" H 4010 4220 60  0001 C CNN "Hersteller Bestellnummer"
	1    4010 4220
	1    0    0    -1  
$EndComp
$Comp
L LED D11
U 1 1 595E906D
P 6010 5430
F 0 "D11" H 6010 5515 50  0000 C CNN
F 1 "RES." H 6010 5580 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 6010 5430 50  0001 C CNN
F 3 "" H 6010 5430 50  0001 C CNN
F 4 "Value" H 6010 5430 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6010 5430 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6010 5430 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6010 5430 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6010 5430 60  0001 C CNN "Bauform"
F 9 "Value" H 6010 5430 60  0001 C CNN "Funktion"
F 10 "Value" H 6010 5430 60  0001 C CNN "Hersteller"
F 11 "Value" H 6010 5430 60  0001 C CNN "Hersteller Bestellnummer"
	1    6010 5430
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 595E937B
P 6460 5430
F 0 "R2" V 6605 5405 50  0000 L CNN
F 1 "220" V 6535 5360 50  0000 L CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6390 5430 50  0001 C CNN
F 3 "" H 6460 5430 50  0001 C CNN
F 4 "Value" H 6460 5430 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6460 5430 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6460 5430 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6460 5430 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6460 5430 60  0001 C CNN "Bauform"
F 9 "Value" H 6460 5430 60  0001 C CNN "Funktion"
F 10 "Value" H 6460 5430 60  0001 C CNN "Hersteller"
F 11 "Value" H 6460 5430 60  0001 C CNN "Hersteller Bestellnummer"
	1    6460 5430
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 595EA3F6
P 4450 4220
F 0 "R3" V 4595 4195 50  0000 L CNN
F 1 "220" V 4525 4150 50  0000 L CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 4220 50  0001 C CNN
F 3 "" H 4450 4220 50  0001 C CNN
F 4 "Value" H 4450 4220 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4450 4220 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4450 4220 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4450 4220 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4450 4220 60  0001 C CNN "Bauform"
F 9 "Value" H 4450 4220 60  0001 C CNN "Funktion"
F 10 "Value" H 4450 4220 60  0001 C CNN "Hersteller"
F 11 "Value" H 4450 4220 60  0001 C CNN "Hersteller Bestellnummer"
	1    4450 4220
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4840 5030 4840 6030
Wire Wire Line
	4300 4220 4160 4220
Wire Wire Line
	4600 4220 4665 4220
Connection ~ 2590 6895
Wire Wire Line
	5860 5430 5495 5430
Wire Wire Line
	6160 5430 6310 5430
Connection ~ 4665 3380
Wire Wire Line
	4665 4220 4665 3380
Connection ~ 2405 3380
Wire Wire Line
	2405 4220 3860 4220
Wire Wire Line
	3505 2455 3505 2370
Wire Wire Line
	3170 2455 3505 2455
Wire Wire Line
	3170 2780 3170 2455
Wire Wire Line
	3605 2455 3605 2370
Wire Wire Line
	3965 2455 3605 2455
Wire Wire Line
	3965 2780 3965 2455
Connection ~ 3170 2780
Connection ~ 3965 2780
Connection ~ 2590 7115
Connection ~ 2590 6030
Wire Wire Line
	3365 7115 3365 7185
Wire Wire Line
	2590 7115 3365 7115
Connection ~ 2590 5870
Wire Wire Line
	3340 6030 3340 6085
Wire Wire Line
	2590 6030 3340 6030
Connection ~ 2590 5355
Wire Wire Line
	2590 5870 3095 5870
Wire Wire Line
	3855 5355 3590 5355
Wire Wire Line
	4155 5355 4640 5355
Wire Wire Line
	3465 7115 3465 7185
Wire Wire Line
	4940 7115 3465 7115
Wire Wire Line
	4940 5030 4940 7115
Wire Wire Line
	3440 6030 3440 6085
Wire Wire Line
	4840 6030 3440 6030
Wire Wire Line
	4740 5870 3695 5870
Wire Wire Line
	4740 5030 4740 5870
Wire Wire Line
	2590 5355 3290 5355
Wire Wire Line
	2590 5115 2590 7215
Wire Wire Line
	4540 5115 2590 5115
Wire Wire Line
	4540 5030 4540 5115
Wire Wire Line
	4640 5355 4640 5030
Wire Wire Line
	8505 1755 8505 3380
Wire Wire Line
	2405 1755 2405 4220
Connection ~ 2405 2780
Connection ~ 8505 2980
Wire Wire Line
	2405 1755 8505 1755
Connection ~ 2405 3080
Wire Wire Line
	2405 2780 3250 2780
Wire Wire Line
	3955 3380 2405 3380
Wire Wire Line
	3955 3485 3955 3380
Wire Wire Line
	4055 3380 4055 3485
Connection ~ 8505 3280
Wire Wire Line
	8505 3280 7870 3280
Connection ~ 2405 3280
Wire Wire Line
	2405 3280 3425 3280
Connection ~ 8505 3180
Wire Wire Line
	8505 3180 6975 3180
Connection ~ 2405 3180
Wire Wire Line
	2405 3180 3900 3180
Connection ~ 8505 3080
Wire Wire Line
	7870 3080 8615 3080
Wire Wire Line
	6975 2980 8505 2980
Wire Wire Line
	2405 3080 3420 3080
Wire Wire Line
	7905 2780 7870 2780
Wire Wire Line
	7905 2880 7905 2780
Wire Wire Line
	3430 2980 3900 2980
Wire Wire Line
	3430 2880 3430 2980
Wire Wire Line
	3430 2880 4950 2880
Wire Wire Line
	8505 3380 5450 3380
Wire Wire Line
	4055 3380 4950 3380
Wire Wire Line
	5450 3280 7570 3280
Wire Wire Line
	3725 3280 4950 3280
Wire Wire Line
	4200 3180 4950 3180
Wire Wire Line
	5450 3180 6675 3180
Wire Wire Line
	5450 3080 7570 3080
Wire Wire Line
	3720 3080 4950 3080
Wire Wire Line
	5450 2980 6675 2980
Wire Wire Line
	4200 2980 4950 2980
Wire Wire Line
	5450 2880 7905 2880
Wire Wire Line
	5450 2780 7570 2780
Wire Wire Line
	3850 2780 4950 2780
$Comp
L CONN_01X02 P4
U 1 1 59618039
P 6135 5030
F 0 "P4" V 6310 5005 50  0000 L CNN
F 1 "RES." V 6230 4950 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02_Pitch2.54mm" H 6135 5030 50  0001 C CNN
F 3 "" H 6135 5030 50  0001 C CNN
	1    6135 5030
	0    -1   1    0   
$EndComp
Wire Wire Line
	6610 5430 6730 5430
Wire Wire Line
	6730 5430 6730 4725
Wire Wire Line
	6730 4725 6185 4725
Wire Wire Line
	6185 4725 6185 4830
Wire Wire Line
	6085 4830 6085 4725
Wire Wire Line
	6085 4725 5495 4725
Wire Wire Line
	5495 4725 5495 5430
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B6
U 1 1 59692452
P 9040 5870
F 0 "B6" H 9144 5923 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9144 5817 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9144 5764 60  0001 L CNN
F 3 "" H 9040 5870 60  0000 C CNN
F 4 "Value" H 9040 5870 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9040 5870 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9040 5870 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9040 5870 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9040 5870 60  0001 C CNN "Bauform"
F 9 "Value" H 9040 5870 60  0001 C CNN "Funktion"
F 10 "Value" H 9040 5870 60  0001 C CNN "Hersteller"
F 11 "Value" H 9040 5870 60  0001 C CNN "Hersteller Bestellnummer"
	1    9040 5870
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B5
U 1 1 59692460
P 9040 5635
F 0 "B5" H 9144 5688 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9144 5582 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9144 5529 60  0001 L CNN
F 3 "" H 9040 5635 60  0000 C CNN
F 4 "Value" H 9040 5635 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9040 5635 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9040 5635 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9040 5635 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9040 5635 60  0001 C CNN "Bauform"
F 9 "Value" H 9040 5635 60  0001 C CNN "Funktion"
F 10 "Value" H 9040 5635 60  0001 C CNN "Hersteller"
F 11 "Value" H 9040 5635 60  0001 C CNN "Hersteller Bestellnummer"
	1    9040 5635
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B8
U 1 1 596B3EB8
P 9055 6345
F 0 "B8" H 9159 6398 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9159 6292 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9159 6239 60  0001 L CNN
F 3 "" H 9055 6345 60  0000 C CNN
F 4 "Value" H 9055 6345 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9055 6345 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9055 6345 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9055 6345 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9055 6345 60  0001 C CNN "Bauform"
F 9 "Value" H 9055 6345 60  0001 C CNN "Funktion"
F 10 "Value" H 9055 6345 60  0001 C CNN "Hersteller"
F 11 "Value" H 9055 6345 60  0001 C CNN "Hersteller Bestellnummer"
	1    9055 6345
	1    0    0    -1  
$EndComp
$Comp
L Bohrloch_3,2mm_ohne_Kupferfläche B7
U 1 1 596B3EC6
P 9055 6110
F 0 "B7" H 9159 6163 60  0000 L CNN
F 1 "Bohrloch_3,2mm_ohne_Kupferfläche" H 9159 6057 60  0000 L CNN
F 2 "Zimprich:Bohrloch_3,2mm" H 9159 6004 60  0001 L CNN
F 3 "" H 9055 6110 60  0000 C CNN
F 4 "Value" H 9055 6110 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9055 6110 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9055 6110 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9055 6110 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9055 6110 60  0001 C CNN "Bauform"
F 9 "Value" H 9055 6110 60  0001 C CNN "Funktion"
F 10 "Value" H 9055 6110 60  0001 C CNN "Hersteller"
F 11 "Value" H 9055 6110 60  0001 C CNN "Hersteller Bestellnummer"
	1    9055 6110
	1    0    0    -1  
$EndComp
Text Notes 12310 3505 0    60   ~ 0
ich habe den zweiten OC Ausgang auf den TILT eingang der 1.3 geschaltet\n ist aber in dem Plan eingezeichnet den ich veröffentlicht habe
$EndSCHEMATC
