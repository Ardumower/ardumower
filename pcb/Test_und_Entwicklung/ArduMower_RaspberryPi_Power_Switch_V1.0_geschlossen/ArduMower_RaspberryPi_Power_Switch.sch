EESchema Schematic File Version 2
LIBS:ArduMower_RaspberryPi_Power_Switch-rescue
LIBS:diode
LIBS:transistors
LIBS:conn
LIBS:device
LIBS:relays
LIBS:switches
LIBS:analog_switches
LIBS:power
LIBS:Zimprich
LIBS:raspberrypi-gpio-cache
LIBS:ArduMower_RaspberryPi_Power_Switch-cache
EELAYER 26 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "ArduMower RaspberryPi Power Switch"
Date "2017-01-01"
Rev "V1.0"
Comp "Schaltplan : Jürgen Lange"
Comment1 "Layout : UZ"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 14020 4520 0    70   ~ 0
LED1   FUSE OKAY
Text Notes 13420 920  0    70   ~ 0
LED indicates the system is on or off
Text Notes 7800 10025 1    70   ~ 0
Versorgung PI
Text Notes 9420 8770 0    66   ~ 0
potentialfreie Ansteuerung\nexterne Baugruppe
Text Notes 13870 3770 0    70   ~ 0
LED indicates the system is up or down
Text Notes 8900 2700 0    70   ~ 0
PI-MON.
Text Notes 7410 2730 0    70   ~ 0
ETH-SWITCH
Text Notes 5945 2710 0    70   ~ 0
USB-HUB
Text Notes 5945 2810 0    70   ~ 0
POWER
Text Notes 7410 2830 0    70   ~ 0
POWER
Text Notes 8900 2800 0    70   ~ 0
POWER
Text Notes 10250 3365 0    70   ~ 0
to Pi
$Comp
L GND #GND01
U 1 1 585BC023
P 10120 6970
F 0 "#GND01" H 10020 6870 70  0001 L BNN
F 1 "GND" H 10025 6775 70  0000 L BNN
F 2 "" H 10120 6970 60  0001 C CNN
F 3 "" H 10120 6970 60  0001 C CNN
	1    10120 6970
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H1
U 1 1 585BCBDB
P 1420 10420
F 0 "H1" H 1530 10442 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 1530 10323 70  0000 L BNN
F 2 "Zimprich:MOUNT-PAD-ROUND3.3" H 1410 10210 65  0001 L TNN
F 3 "" H 1420 10420 60  0001 C CNN
F 4 "Value" H 1420 10420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1420 10420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1420 10420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1420 10420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1420 10420 60  0001 C CNN "Bauform"
F 9 "Value" H 1420 10420 60  0001 C CNN "Funktion"
F 10 "Value" H 1420 10420 60  0001 C CNN "Hersteller"
F 11 "Value" H 1420 10420 60  0001 C CNN "Hersteller Bestellnummer"
	1    1420 10420
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H2
U 1 1 585BCCA3
P 2820 10420
F 0 "H2" H 2930 10442 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 2930 10323 70  0000 L BNN
F 2 "Zimprich:MOUNT-PAD-ROUND3.3" H 2810 10210 65  0001 L TNN
F 3 "" H 2820 10420 60  0001 C CNN
F 4 "Value" H 2820 10420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2820 10420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2820 10420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2820 10420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2820 10420 60  0001 C CNN "Bauform"
F 9 "Value" H 2820 10420 60  0001 C CNN "Funktion"
F 10 "Value" H 2820 10420 60  0001 C CNN "Hersteller"
F 11 "Value" H 2820 10420 60  0001 C CNN "Hersteller Bestellnummer"
	1    2820 10420
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H3
U 1 1 585BCD6B
P 4220 10420
F 0 "H3" H 4330 10442 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 4330 10323 70  0000 L BNN
F 2 "Zimprich:MOUNT-PAD-ROUND3.3" H 4210 10210 65  0001 L TNN
F 3 "" H 4220 10420 60  0001 C CNN
F 4 "Value" H 4220 10420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4220 10420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4220 10420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4220 10420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4220 10420 60  0001 C CNN "Bauform"
F 9 "Value" H 4220 10420 60  0001 C CNN "Funktion"
F 10 "Value" H 4220 10420 60  0001 C CNN "Hersteller"
F 11 "Value" H 4220 10420 60  0001 C CNN "Hersteller Bestellnummer"
	1    4220 10420
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H4
U 1 1 585BCE33
P 5620 10420
F 0 "H4" H 5730 10442 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 5730 10323 70  0000 L BNN
F 2 "Zimprich:MOUNT-PAD-ROUND3.3" H 5610 10210 65  0001 L TNN
F 3 "" H 5620 10420 60  0001 C CNN
F 4 "Value" H 5620 10420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5620 10420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5620 10420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5620 10420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5620 10420 60  0001 C CNN "Bauform"
F 9 "Value" H 5620 10420 60  0001 C CNN "Funktion"
F 10 "Value" H 5620 10420 60  0001 C CNN "Hersteller"
F 11 "Value" H 5620 10420 60  0001 C CNN "Hersteller Bestellnummer"
	1    5620 10420
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H5
U 1 1 585BCEFB
P 7070 10420
F 0 "H5" H 7180 10442 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 7180 10323 70  0000 L BNN
F 2 "Zimprich:MOUNT-PAD-ROUND3.3" H 7060 10210 65  0001 L TNN
F 3 "" H 7070 10420 60  0001 C CNN
F 4 "Value" H 7070 10420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7070 10420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7070 10420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7070 10420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7070 10420 60  0001 C CNN "Bauform"
F 9 "Value" H 7070 10420 60  0001 C CNN "Funktion"
F 10 "Value" H 7070 10420 60  0001 C CNN "Hersteller"
F 11 "Value" H 7070 10420 60  0001 C CNN "Hersteller Bestellnummer"
	1    7070 10420
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H6
U 1 1 585BCFC3
P 8470 10420
F 0 "H6" H 8580 10442 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 8580 10323 70  0000 L BNN
F 2 "Zimprich:MOUNT-PAD-ROUND3.3" H 8460 10210 65  0001 L TNN
F 3 "" H 8470 10420 60  0001 C CNN
F 4 "Value" H 8470 10420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8470 10420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8470 10420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8470 10420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8470 10420 60  0001 C CNN "Bauform"
F 9 "Value" H 8470 10420 60  0001 C CNN "Funktion"
F 10 "Value" H 8470 10420 60  0001 C CNN "Hersteller"
F 11 "Value" H 8470 10420 60  0001 C CNN "Hersteller Bestellnummer"
	1    8470 10420
	1    0    0    -1  
$EndComp
$Comp
L 74ALS05N IC1
U 1 1 585BD08B
P 6470 7670
F 0 "IC1" H 6570 7795 70  0000 L BNN
F 1 "74ALS05N" H 6270 7370 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 6460 7460 65  0001 L TNN
F 3 "" H 6470 7670 60  0001 C CNN
	1    6470 7670
	1    0    0    -1  
$EndComp
$Comp
L 74ALS05N IC1
U 2 1 585BD0EF
P 6670 4270
F 0 "IC1" H 6770 4395 70  0000 L BNN
F 1 "74ALS05N" H 6470 3970 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 6660 4060 65  0001 L TNN
F 3 "" H 6670 4270 60  0001 C CNN
	2    6670 4270
	1    0    0    -1  
$EndComp
$Comp
L 74ALS05N IC1
U 3 1 585BD153
P 7870 4270
F 0 "IC1" H 7970 4395 70  0000 L BNN
F 1 "74ALS05N" H 7670 3970 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 7860 4060 65  0001 L TNN
F 3 "" H 7870 4270 60  0001 C CNN
	3    7870 4270
	1    0    0    -1  
$EndComp
$Comp
L 74ALS05N IC1
U 4 1 585BD1B7
P 9620 6370
F 0 "IC1" H 9719 6495 70  0000 L BNN
F 1 "74ALS05N" H 9720 6170 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 9610 6160 65  0001 L TNN
F 3 "" H 9620 6370 60  0001 C CNN
	4    9620 6370
	-1   0    0    1   
$EndComp
$Comp
L 74ALS05N IC1
U 5 1 585BD21B
P 7870 5270
F 0 "IC1" H 7970 5395 70  0000 L BNN
F 1 "74ALS05N" H 7969 5070 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 7860 5060 65  0001 L TNN
F 3 "" H 7870 5270 60  0001 C CNN
	5    7870 5270
	1    0    0    -1  
$EndComp
$Comp
L 74ALS05N IC1
U 6 1 585BD27F
P 9620 5870
F 0 "IC1" H 9719 5995 70  0000 L BNN
F 1 "74ALS05N" H 9720 5670 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 9610 5660 65  0001 L TNN
F 3 "" H 9620 5870 60  0001 C CNN
	6    9620 5870
	-1   0    0    1   
$EndComp
$Comp
L 74LS73N IC2
U 1 1 585BD347
P 6470 5570
F 0 "IC2" H 6170 5995 70  0000 L BNN
F 1 "74LS73N" H 6170 5170 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 6460 5360 65  0001 L TNN
F 3 "" H 6470 5570 60  0001 C CNN
	1    6470 5570
	1    0    0    -1  
$EndComp
$Comp
L 74LS73N IC2
U 2 1 585BD3AB
P 9420 5020
F 0 "IC2" H 9120 5445 70  0000 L BNN
F 1 "74LS73N" H 9120 4620 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 9410 4810 65  0001 L TNN
F 3 "" H 9420 5020 60  0001 C CNN
	2    9420 5020
	1    0    0    -1  
$EndComp
$Comp
L APF30212C K1
U 1 1 585BDE9B
P 9220 9070
F 0 "K1" H 9070 8770 70  0000 L BNN
F 1 "APF30212C" V 9505 8820 70  0000 L BNN
F 2 "w_relay:relay_34.51" V 9505 8820 70  0001 L BNN
F 3 "" H 9220 9070 60  0001 C CNN
F 4 "Value" H 9220 9070 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9220 9070 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9220 9070 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9220 9070 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9220 9070 60  0001 C CNN "Bauform"
	1    9220 9070
	1    0    0    -1  
$EndComp
$Comp
L APF30212C K1
U 2 1 585BDEFF
P 9870 9170
F 0 "K1" H 9970 9170 70  0000 L BNN
F 1 "APF30212C" H 9860 9060 65  0001 L TNN
F 2 "w_relay:relay_34.51" H 9860 8960 65  0001 L TNN
F 3 "" H 9870 9170 60  0001 C CNN
	2    9870 9170
	-1   0    0    -1  
$EndComp
$Comp
L APF30212C K2
U 1 1 585BDFC7
P 4170 1620
F 0 "K2" H 4021 1320 70  0000 L BNN
F 1 "APF30212C" V 4455 1371 70  0000 L BNN
F 2 "w_relay:relay_34.51" V 4455 1371 70  0001 L BNN
F 3 "" H 4170 1620 60  0001 C CNN
F 4 "Value" H 4170 1620 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4170 1620 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4170 1620 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4170 1620 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4170 1620 60  0001 C CNN "Bauform"
	1    4170 1620
	-1   0    0    1   
$EndComp
$Comp
L APF30212C K2
U 2 1 585BE02B
P 3470 1670
F 0 "K2" H 3570 1670 70  0000 L BNN
F 1 "APF30212C" H 3460 1560 65  0001 L TNN
F 2 "w_relay:relay_34.51" H 3460 1460 65  0001 L TNN
F 3 "" H 3470 1670 60  0001 C CNN
	2    3470 1670
	-1   0    0    1   
$EndComp
$Comp
L APF30212C K3
U 1 1 585BE0F3
P 7270 1620
F 0 "K3" H 7121 1320 70  0000 L BNN
F 1 "APF30212C" V 7555 1371 70  0000 L BNN
F 2 "w_relay:relay_34.51" V 7555 1371 70  0001 L BNN
F 3 "" H 7270 1620 60  0001 C CNN
F 4 "Value" H 7270 1620 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7270 1620 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7270 1620 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7270 1620 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7270 1620 60  0001 C CNN "Bauform"
	1    7270 1620
	-1   0    0    1   
$EndComp
$Comp
L APF30212C K3
U 2 1 585BE157
P 6570 1720
F 0 "K3" H 6670 1720 70  0000 L BNN
F 1 "APF30212C" H 6560 1610 65  0001 L TNN
F 2 "w_relay:relay_34.51" H 6560 1510 65  0001 L TNN
F 3 "" H 6570 1720 60  0001 C CNN
	2    6570 1720
	-1   0    0    1   
$EndComp
$Comp
L CLOCK-MODUL MD1
U 1 1 585BE607
P 14370 5370
F 0 "MD1" H 14360 5360 65  0001 L TNN
F 1 "Tiny_RTC_Modul" H 14360 5260 65  0001 L TNN
F 2 "Zimprich:Tiny_RTC_Modul" H 14360 5160 65  0001 L TNN
F 3 "" H 14370 5370 60  0001 C CNN
F 4 "Value" H 14370 5370 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14370 5370 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14370 5370 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14370 5370 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14370 5370 60  0001 C CNN "Bauform"
F 9 "Value" H 14370 5370 60  0000 C CNN "Funktion"
F 10 "Value" H 14370 5370 60  0001 C CNN "Hersteller"
F 11 "Value" H 14370 5370 60  0001 C CNN "Hersteller Bestellnummer"
	1    14370 5370
	1    0    0    -1  
$EndComp
$Comp
L PCA9517D_118 U1
U 1 1 585C19FB
P 12420 4970
F 0 "U1" H 12207 5569 82  0000 L BNN
F 1 "PCA9517D" H 12229 4100 82  0000 L BNN
F 2 "Zimprich:SOIC127P600X175-8N" H 12410 4760 65  0001 L TNN
F 3 "" H 12420 4970 60  0001 C CNN
F 4 "Value" H 12420 4970 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 12420 4970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 12420 4970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 12420 4970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 12420 4970 60  0001 C CNN "Bauform"
	1    12420 4970
	1    0    0    -1  
$EndComp
$Comp
L PCA9517D_118 U2
U 1 1 585C1AC3
P 12420 7570
F 0 "U2" H 12207 8169 82  0000 L BNN
F 1 "PCA9517D" H 12229 6700 82  0000 L BNN
F 2 "Zimprich:SOIC127P600X175-8N" H 12410 7360 65  0001 L TNN
F 3 "" H 12420 7570 60  0001 C CNN
F 4 "Value" H 12420 7570 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 12420 7570 60  0001 C CNN "Bestelllink"
F 6 "Value" H 12420 7570 60  0001 C CNN "Technische Daten"
F 7 "Value" H 12420 7570 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 12420 7570 60  0001 C CNN "Bauform"
	1    12420 7570
	1    0    0    -1  
$EndComp
Text Label 8420 3120 1    10   ~ 0
+5V
Text Label 8420 2920 2    10   ~ 0
+5V
Text Label 4020 5870 3    10   ~ 0
1WIRE
Text Label 4105 6070 2    10   ~ 0
1WIRE
Text Label 12025 3970 0    10   ~ 0
EXT-GND
Text Label 13920 4220 2    10   ~ 0
EXT-GND
Text Label 12025 3870 0    10   ~ 0
EXT-VCC
Text Label 14970 3520 0    10   ~ 0
EXT-VCC
Text Label 15320 3320 0    10   ~ 0
EXT-VCC
Text Label 14820 4220 0    10   ~ 0
EXT-VCC
Text Label 8870 3120 1    10   ~ 0
GND
Text Label 8920 3020 2    10   ~ 0
GND
Text Label 4105 6270 2    10   ~ 0
GND
Text Label 4020 6270 1    10   ~ 0
GND
Text Label 3670 6270 3    10   ~ 0
GND
Text Label 14320 4220 0    10   ~ 0
N$1
Text Label 14520 4220 2    10   ~ 0
N$1
Text Label 14720 6720 0    10   ~ 0
N$4
Text Label 15190 6720 2    10   ~ 0
N$4
Text Label 14980 7820 0    10   ~ 0
N$4
Text Label 5170 7670 0    10   ~ 0
N$7
Text Label 5430 7670 2    10   ~ 0
N$7
Text Label 5370 8170 1    10   ~ 0
N$7
Text Label 12025 3770 0    10   ~ 0
N$8
Text Label 13920 3520 2    10   ~ 0
N$8
Text Label 10020 6370 0    10   ~ 0
N$9
Text Label 10120 6470 1    10   ~ 0
N$9
Text Label 10220 6370 2    10   ~ 0
N$9
Text Label 10020 5870 0    10   ~ 0
N$9
Text Label 7070 4270 0    10   ~ 0
N$10
Text Label 7470 4270 2    10   ~ 0
N$10
Text Label 7270 4370 1    10   ~ 0
N$10
Text Label 6970 5270 0    10   ~ 0
N$11
Text Label 7470 5270 2    10   ~ 0
N$11
Text Label 3470 1570 1    10   ~ 0
N$14
Text Label 3470 1020 3    10   ~ 0
N$14
Text Label 8670 6635 1    10   ~ 0
N$15
Text Label 8270 5270 0    10   ~ 0
N$15
Text Label 8470 5770 0    10   ~ 0
N$15
Text Label 8270 4270 0    10   ~ 0
N$19
Text Label 8670 4270 2    10   ~ 0
N$19
Text Label 8470 4370 1    10   ~ 0
N$19
Text Label 6870 7670 0    10   ~ 0
N$20
Text Label 7170 7670 2    10   ~ 0
N$20
Text Label 7070 8020 1    10   ~ 0
N$20
Text Label 5220 6170 1    10   ~ 0
N$21
Text Label 5220 5970 3    10   ~ 0
N$21
Text Label 12025 3670 0    10   ~ 0
N$23
Text Label 14320 3320 2    10   ~ 0
N$23
Text Label 3470 7270 1    10   ~ 0
N$26
Text Label 3470 7170 3    10   ~ 0
N$26
Text Label 14720 3320 0    10   ~ 0
N$27
Text Label 15020 3320 2    10   ~ 0
N$27
Text Label 14320 3520 0    10   ~ 0
N$31
Text Label 14670 3520 2    10   ~ 0
N$31
Text Label 12025 3270 0    10   ~ 0
N$40
Text Label 12025 3370 0    10   ~ 0
N$41
Text Label 5120 1270 1    10   ~ 0
N$42
Text Label 4170 1420 1    10   ~ 0
N$42
Text Label 4820 1120 1    10   ~ 0
N$42
Text Label 4820 1620 1    10   ~ 0
N$43
Text Label 4820 1420 3    10   ~ 0
N$43
Text Label 6570 1620 1    10   ~ 0
N$46
Text Label 6570 1020 3    10   ~ 0
N$46
Text Label 3270 1870 2    10   ~ 0
N$47
Text Label 3370 1020 3    10   ~ 0
N$47
Text Label 3670 1870 0    10   ~ 0
N$48
Text Label 3570 1020 3    10   ~ 0
N$48
Text Label 6370 1920 2    10   ~ 0
N$50
Text Label 6470 1020 3    10   ~ 0
N$50
Text Label 6770 1920 0    10   ~ 0
N$51
Text Label 6670 1020 3    10   ~ 0
N$51
Text Label 7270 1420 1    10   ~ 0
N$52
Text Label 8270 1270 1    10   ~ 0
N$52
Text Label 7920 1120 1    10   ~ 0
N$52
Text Label 7920 1620 1    10   ~ 0
N$53
Text Label 7920 1420 3    10   ~ 0
N$53
Text Label 8820 2920 0    10   ~ 0
N$57
Text Label 8920 2920 2    10   ~ 0
N$57
Text Label 14720 7020 0    10   ~ 0
N$64
Text Label 15190 7020 2    10   ~ 0
N$64
Text Label 14980 7520 0    10   ~ 0
N$64
Text Label 13670 6420 0    10   ~ 0
N$66
Text Label 15190 6820 2    10   ~ 0
N$66
Text Label 14120 7820 2    10   ~ 0
N$66
Text Label 14120 7520 2    10   ~ 0
N$66
Text Label 10020 3370 0    10   ~ 0
N$67
Text Label 11255 3370 2    10   ~ 0
N$67
Text Label 10020 3270 0    10   ~ 0
N$68
Text Label 11255 3270 2    10   ~ 0
N$68
Text Label 14520 7520 0    10   ~ 0
N$69
Text Label 14580 7520 2    10   ~ 0
N$69
Text Label 14520 7820 0    10   ~ 0
N$70
Text Label 14580 7820 2    10   ~ 0
N$70
Text Label 3570 5970 0    10   ~ 0
N$74
Text Label 3670 5970 1    10   ~ 0
N$74
Text Label 4105 5970 2    10   ~ 0
N$74
Text Label 4020 5470 1    10   ~ 0
N$74
Text Label 9070 4270 0    10   ~ 0
ON-OFF-KEY
Text Label 5870 1620 1    10   ~ 0
OUT1
Text Label 5870 1470 0    10   ~ 0
OUT1
Text Label 9070 1620 1    10   ~ 0
OUT2
Text Label 9070 1470 0    10   ~ 0
OUT2
Text Label 6070 7670 2    10   ~ 0
PG
Text Label 5870 7970 1    10   ~ 0
PG
Text Label 5770 7670 0    10   ~ 0
PG
Text Label 7570 7670 0    10   ~ 0
POWER-GOOD
Text Label 14320 7020 2    10   ~ 0
SCLEXT
Text Label 14320 6720 2    10   ~ 0
SDAEXT
Text Label 11255 3670 2    10   ~ 0
SIG-BUZZER
Text Label 9220 6370 2    10   ~ 0
SIG-SYSUP
Text Label 5970 5770 2    10   ~ 0
SIG-SYSUP
Text Label 9220 5870 2    10   ~ 0
SIG-SYSUP
Text Label 5970 6370 1    10   ~ 0
SIG-SYSUP
Text Label 9020 6640 1    10   ~ 0
SIG-SYSUP
Text Label 11255 3770 2    10   ~ 0
SIG-SYSUP
Text Label 5970 5470 2    10   ~ 0
SIG-TAST
Text Label 5620 5620 1    10   ~ 0
SIG-TAST
Text Label 6270 4270 2    10   ~ 0
SIG-TAST
Text Label 5220 5670 1    10   ~ 0
SIG-TAST
Text Label 11255 3470 2    10   ~ 0
SIG-TAST
Text Label 8420 8970 1    10   ~ 0
SPOWER
Text Label 8120 8820 1    10   ~ 0
SPOWER
Text Label 9220 8870 1    10   ~ 0
SPOWER
Text Label 4260 6970 0    10   ~ 0
SPOWER
Text Label 4170 1820 3    10   ~ 0
SPOWER
Text Label 4820 2020 3    10   ~ 0
SPOWER
Text Label 7270 1820 3    10   ~ 0
SPOWER
Text Label 7920 2020 3    10   ~ 0
SPOWER
Text Label 11255 3570 2    10   ~ 0
SPOWER
Text Label 12025 3470 0    10   ~ 0
TAST
Text Label 12025 3570 0    10   ~ 0
TLED
$Comp
L 74LS73N IC2
U 3 1 585E5E85
P 1060 7500
F 0 "IC2" H 760 7925 70  0000 L BNN
F 1 "74LS73N" H 760 7100 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 1050 7290 65  0001 L TNN
F 3 "" H 1060 7500 60  0001 C CNN
F 4 "Value" H 1060 7500 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1060 7500 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1060 7500 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1060 7500 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1060 7500 60  0001 C CNN "Bauform"
	3    1060 7500
	1    0    0    -1  
$EndComp
$Comp
L 74ALS05N IC1
U 7 1 585EBA7F
P 1520 7490
F 0 "IC1" H 1620 7615 70  0000 L BNN
F 1 "74ALS05N" H 1320 7190 70  0000 L BNN
F 2 "Sockets_DIP:DIP-14__300" H 1510 7280 65  0001 L TNN
F 3 "" H 1520 7490 60  0001 C CNN
F 4 "Value" H 1520 7490 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1520 7490 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1520 7490 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1520 7490 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1520 7490 60  0001 C CNN "Bauform"
	7    1520 7490
	1    0    0    -1  
$EndComp
Text GLabel 4020 2120 0    39   Input ~ 0
SPOWER
Text GLabel 5770 1070 0    39   Input ~ 0
OUT1
Text GLabel 8970 1070 0    39   Input ~ 0
OUT2
Text GLabel 7120 2120 0    39   Input ~ 0
SPOWER
Text GLabel 4895 3975 2    39   Input ~ 0
BUZZER
Text GLabel 9270 4270 2    39   Input ~ 0
ON-OFF-KEY
Text GLabel 13270 4670 2    39   Input ~ 0
SDAPI
Text GLabel 13270 4770 2    39   Input ~ 0
SDAINT
Text GLabel 13620 5270 0    39   Input ~ 0
SCLINT
Text GLabel 13620 5370 0    39   Input ~ 0
SDAINT
Text GLabel 11570 4970 0    39   Input ~ 0
SCLPI
Text GLabel 11570 5070 0    39   Input ~ 0
SCLINT
Text GLabel 10560 6370 2    39   Input ~ 0
SYSTEM-UP
Text GLabel 13270 7270 2    39   Input ~ 0
SDAPI
Text GLabel 13270 7370 2    39   Input ~ 0
SDAEXT
Text GLabel 14170 6720 0    39   Input ~ 0
SDAEXT
Text GLabel 14170 7020 0    39   Input ~ 0
SCLEXT
Text GLabel 15120 5270 2    39   Input ~ 0
SCLINT-S
Text GLabel 15120 5370 2    39   Input ~ 0
SDAINT-S
Text GLabel 15420 4470 0    39   Input ~ 0
EXT-VCC
Text GLabel 13470 4220 0    39   Input ~ 0
EXT-GND
Text GLabel 12520 3470 2    39   Input ~ 0
TAST
Text GLabel 12520 3570 2    39   Input ~ 0
TLED
Text GLabel 14520 1270 2    39   Input ~ 0
TAST
Text GLabel 14520 1370 2    39   Input ~ 0
EXT-GND
Text GLabel 13670 1270 0    39   Input ~ 0
EXT-VCC
Text GLabel 13670 1720 0    39   Input ~ 0
TLED
Text GLabel 11570 2520 2    39   Input ~ 0
IN2
Text GLabel 10370 2520 2    39   Input ~ 0
IN1
Text GLabel 11020 3670 0    39   Input ~ 0
SIG-BUZZER
Text GLabel 11020 3770 0    39   Input ~ 0
SIG-SYSUP
Text GLabel 11020 3470 0    39   Input ~ 0
SIG-TAST
Text GLabel 11020 3570 0    39   Input ~ 0
SPOWER
Text GLabel 3570 5670 0    39   Input ~ 0
1WIRE
Text GLabel 4670 5470 0    39   Input ~ 0
SIG-TAST
Text GLabel 6920 6670 2    39   Input ~ 0
SIG-SYSUP
Text GLabel 9420 7320 2    39   Input ~ 0
SPOWER
Text GLabel 7670 7670 2    39   Input ~ 0
POWER-GOOD
Text GLabel 11570 7570 0    39   Input ~ 0
SCLPI
Text GLabel 11570 7670 0    39   Input ~ 0
SCLEXT
Text GLabel 12280 8830 0    39   Input ~ 0
SDAINT-S
Text GLabel 12280 8930 0    39   Input ~ 0
SCLINT-S
Text GLabel 14305 8805 0    39   Input ~ 0
SDAPI
Text GLabel 14305 8905 0    39   Input ~ 0
SCLPI
$Comp
L IRF9540N-RESCUE-ArduMower_RaspberryPi_Power_Switch Q2
U 1 1 585F12A5
P 3520 8470
F 0 "Q2" V 3800 8470 50  0000 C CNN
F 1 "IRF 9540NS" V 3891 8470 50  0000 C CNN
F 2 "w_smd_trans:d2-pak" V 3982 8470 50  0001 C CIN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/DS_IRF9540NS.pdf" H 3520 8470 50  0001 L CNN
F 4 "D2-PAK" H 3520 8470 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/IRC-IRF-Transistoren/IRF-9540NS/3/index.html?ACTION=3&LA=446&ARTICLE=129797&GROUPID=2891&artnr=IRF+9540NS&SEARCH=IRF9540" H 3520 8470 60  0001 C CNN "Bestelllink"
F 6 "MOSFET P-Ch 100V 23A 3-Pin(2+Tab), D2-PAK" H 3520 8470 60  0001 C CNN "Technische Daten"
F 7 "R: IRF 9540NS" H 3520 8470 60  0001 C CNN "Bestellnummer"
F 8 "D2-PAK" H 3520 8470 60  0001 C CNN "Bauform"
F 9 "Value" H 3520 8470 60  0001 C CNN "Funktion"
F 10 "Value" H 3520 8470 60  0001 C CNN "Hersteller"
F 11 "Value" H 3520 8470 60  0001 C CNN "Hersteller Bestellnummer"
	1    3520 8470
	0    1    1    0   
$EndComp
$Comp
L IRF9540N-RESCUE-ArduMower_RaspberryPi_Power_Switch Q1
U 1 1 585F4557
P 7720 8820
F 0 "Q1" V 8000 8820 50  0000 C CNN
F 1 "NDB6020P" V 8091 8820 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-263-3Lead" V 8182 8820 50  0001 C CIN
F 3 "http://www.produktinfo.conrad.com/datenblaetter/1200000-1299999/001264953-da-01-en-MOSFET_P_CH_20V_24_NDB6020P_TO_263_3_FSC.pdf" H 7720 8820 50  0001 L CNN
F 4 "TO‑263‑3" H 7720 8820 60  0001 C CNN "Gehäuseart"
F 5 "https://www.conrad.de/de/mosfet-fairchild-semiconductor-ndb6020p-1-p-kanal-60-w-to-263-3-1264953.html" H 7720 8820 60  0001 C CNN "Bestelllink"
F 6 "MOSFET  NDB6020P 1 P-Kanal 60 W TO-263-3" H 7720 8820 60  0001 C CNN "Technische Daten"
F 7 "C: 1264953 - 62" H 7720 8820 60  0001 C CNN "Bestellnummer"
F 8 "TO‑263‑3" H 7720 8820 60  0001 C CNN "Bauform"
F 9 "Value" H 7720 8820 60  0001 C CNN "Funktion"
F 10 "Value" H 7720 8820 60  0001 C CNN "Hersteller"
F 11 "Value" H 7720 8820 60  0001 C CNN "Hersteller Bestellnummer"
	1    7720 8820
	0    1    1    0   
$EndComp
$Comp
L D D17
U 1 1 58619BB9
P 11420 1370
F 0 "D17" V 11458 1449 39  0000 L CNN
F 1 "1N4148" V 11383 1449 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 11420 1495 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 11420 1370 50  0001 C CNN
F 4 "MiniMELF" H 11420 1370 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 11420 1370 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 11420 1370 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 11420 1370 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 11420 1370 60  0001 C CNN "Bauform"
F 9 "Value" H 11420 1370 60  0001 C CNN "Funktion"
F 10 "Value" H 11420 1370 60  0001 C CNN "Hersteller"
F 11 "Value" H 11420 1370 60  0001 C CNN "Hersteller Bestellnummer"
	1    11420 1370
	0    1    -1   0   
$EndComp
$Comp
L D D1
U 1 1 5862E02A
P 3020 9270
F 0 "D1" H 2990 9410 39  0000 L CNN
F 1 "1N4004" H 2910 9360 39  0000 L CNN
F 2 "Diodes_SMD:DO-214AB" H 3020 9395 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A400/S1DSMD_S1GSMD_S1JSMD_S1MSMD_TSC.pdf" H 3020 9270 50  0001 C CNN
F 4 "DO-214AC/SMA" H 3020 9270 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SB-SKE-4F-Dioden/S-1G-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=95354&GROUPID=2991&artnr=S+1G+SMD&SEARCH=1N4004" H 3020 9270 60  0001 C CNN "Bestelllink"
F 6 "Si-Gleichrichterdiode, DO214AC, 400V, 1A" H 3020 9270 60  0001 C CNN "Technische Daten"
F 7 "R: S 1G SMD" H 3020 9270 60  0001 C CNN "Bestellnummer"
F 8 "DO-214AC" H 3020 9270 60  0001 C CNN "Bauform"
F 9 "Value" H 3020 9270 60  0001 C CNN "Funktion"
F 10 "Value" H 3020 9270 60  0001 C CNN "Hersteller"
F 11 "Value" H 3020 9270 60  0001 C CNN "Hersteller Bestellnummer"
	1    3020 9270
	-1   0    0    -1  
$EndComp
$Comp
L D_Zener D15
U 1 1 58647750
P 10520 2020
F 0 "D15" H 10520 2236 50  0000 C CNN
F 1 "ZPD3,1" H 10520 2145 50  0000 C CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 10520 2144 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A900/SMDZF%23VIS.pdf" H 10520 2020 50  0001 C CNN
F 4 "Mini Melf, DO-213AA, SOD 80" H 10520 2020 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SMD-Z-Dioden-Mini-Melf/SMD-ZF-5-1/3/index.html?ACTION=3;ARTICLE=18942;SEARCH=smd%20zf%203" H 10520 2020 60  0001 C CNN "Bestelllink"
F 6 "Chip-Zener-Diode 0,5W 3,3V" H 10520 2020 60  0001 C CNN "Technische Daten"
F 7 "R: SMD ZF 3,3" H 10520 2020 60  0001 C CNN "Bestellnummer"
F 8 "Mini Melf, DO-213AA, SOD 80" H 10520 2020 60  0001 C CNN "Bauform"
F 9 "Value" H 10520 2020 60  0001 C CNN "Funktion"
F 10 "Value" H 10520 2020 60  0001 C CNN "Hersteller"
F 11 "Value" H 10520 2020 60  0001 C CNN "Hersteller Bestellnummer"
	1    10520 2020
	1    0    0    -1  
$EndComp
$Comp
L D_Zener D11
U 1 1 5864C30D
P 5370 8320
F 0 "D11" V 5324 8399 50  0000 L CNN
F 1 "ZPD5,1" V 5415 8399 50  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 5370 8444 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A900/SMDZF%23VIS.pdf" H 5370 8320 50  0001 C CNN
F 4 "Mini Melf, DO-213AA, SOD 80" H 5370 8320 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SMD-Z-Dioden-Mini-Melf/SMD-ZF-5-1/3/index.html?ACTION=3&LA=446&ARTICLE=18953&GROUPID=2995&artnr=SMD+ZF+5%2C1&SEARCH=zenerdiode%2B5%252C1" H 5370 8320 60  0001 C CNN "Bestelllink"
F 6 "Chip-Zener-Diode 0,5W 5,1V" H 5370 8320 60  0001 C CNN "Technische Daten"
F 7 "R: SMD ZF 5,1" H 5370 8320 60  0001 C CNN "Bestellnummer"
F 8 "Mini Melf, DO-213AA, SOD 80" H 5370 8320 60  0001 C CNN "Bauform"
F 9 "Value" H 5370 8320 60  0001 C CNN "Funktion"
F 10 "Value" H 5370 8320 60  0001 C CNN "Hersteller"
F 11 "Value" H 5370 8320 60  0001 C CNN "Hersteller Bestellnummer"
	1    5370 8320
	0    1    1    0   
$EndComp
$Comp
L D_Zener D12
U 1 1 586539CC
P 3070 7890
F 0 "D12" V 3065 8060 50  0000 C CNN
F 1 "ZPD9,1" V 2975 8025 50  0000 C CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 3070 8014 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A900/SMDZF%23VIS.pdf" H 3070 7890 50  0001 C CNN
F 4 "Mini Melf, DO-213AA, SOD 80" H 3070 7890 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SMD-Z-Dioden-Mini-Melf/SMD-ZF-5-1/3/index.html?ACTION=3;ARTICLE=18964;SEARCH=smd%20zf%209,1" H 3070 7890 60  0001 C CNN "Bestelllink"
F 6 "Chip-Zener-Diode 0,5W 9,1V" H 3070 7890 60  0001 C CNN "Technische Daten"
F 7 "R: SMD ZF 9,1" H 3070 7890 60  0001 C CNN "Bestellnummer"
F 8 "Mini Melf, DO-213AA, SOD 80" H 3070 7890 60  0001 C CNN "Bauform"
F 9 "Value" H 3070 7890 60  0001 C CNN "Funktion"
F 10 "Value" H 3070 7890 60  0001 C CNN "Hersteller"
F 11 "Value" H 3070 7890 60  0001 C CNN "Hersteller Bestellnummer"
	1    3070 7890
	0    -1   -1   0   
$EndComp
$Comp
L CONN_02X20 JP2
U 1 1 5866E844
P 1705 2535
F 0 "JP2" H 1705 3700 50  0000 C CNN
F 1 "CONN_02X20" H 1705 3609 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x20" H 1705 3608 50  0001 C CNN
F 3 "" H 1705 1585 50  0000 C CNN
F 4 "Value" H 1705 2535 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1705 2535 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1705 2535 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1705 2535 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1705 2535 60  0001 C CNN "Bauform"
	1    1705 2535
	1    0    0    -1  
$EndComp
Text GLabel 1105 1685 0    39   Input ~ 0
SDAPI
Text GLabel 1105 1785 0    39   Input ~ 0
SCLPI
Text GLabel 1105 1885 0    39   Input ~ 0
1WIRE
Text GLabel 1105 3185 0    39   Input ~ 0
IN1
Text GLabel 1105 3285 0    39   Input ~ 0
35
Text GLabel 1105 3385 0    39   Input ~ 0
IN2
Text GLabel 1105 2885 0    39   Input ~ 0
27
Text GLabel 1105 2985 0    39   Input ~ 0
OUT1
Text GLabel 1105 3085 0    39   Input ~ 0
OUT2
Text GLabel 1105 2485 0    39   Input ~ 0
19
Text GLabel 1105 2585 0    39   Input ~ 0
21
Text GLabel 1105 2685 0    39   Input ~ 0
23
Text GLabel 1105 2085 0    39   Input ~ 0
11
Text GLabel 1105 2185 0    39   Input ~ 0
13
Text GLabel 1105 2285 0    39   Input ~ 0
BUZZER
Text GLabel 2230 3285 2    39   Input ~ 0
36
Text GLabel 2230 3385 2    39   Input ~ 0
38
Text GLabel 2230 3485 2    39   Input ~ 0
40
Text GLabel 2230 3085 2    39   Input ~ 0
32
Text GLabel 2230 2685 2    39   Input ~ 0
24
Text GLabel 2230 2785 2    39   Input ~ 0
26
Text GLabel 2230 2885 2    39   Input ~ 0
28
Text GLabel 2230 2285 2    39   Input ~ 0
ON-OFF-KEY
Text GLabel 2230 2385 2    39   Input ~ 0
SYSTEM-UP
Text GLabel 2230 2585 2    39   Input ~ 0
POWER-GOOD
Text GLabel 2230 1885 2    39   Input ~ 0
8
Text GLabel 2230 1985 2    39   Input ~ 0
10
Text GLabel 2230 2085 2    39   Input ~ 0
12
$Comp
L CONN_02X20 JP1
U 1 1 58681109
P 1705 5080
F 0 "JP1" H 1705 6245 50  0000 C CNN
F 1 "CONN_02X20" H 1705 6154 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x20" H 1705 6153 50  0001 C CNN
F 3 "" H 1705 4130 50  0000 C CNN
F 4 "Value" H 1705 5080 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1705 5080 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1705 5080 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1705 5080 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1705 5080 60  0001 C CNN "Bauform"
	1    1705 5080
	1    0    0    -1  
$EndComp
Text GLabel 1105 4230 0    39   Input ~ 0
SDAPI
Text GLabel 1105 4330 0    39   Input ~ 0
SCLPI
Text GLabel 1105 4430 0    39   Input ~ 0
1WIRE
Text GLabel 1105 5730 0    39   Input ~ 0
IN1
Text GLabel 1105 5830 0    39   Input ~ 0
35
Text GLabel 1105 5930 0    39   Input ~ 0
IN2
Text GLabel 1105 5430 0    39   Input ~ 0
27
Text GLabel 1105 5530 0    39   Input ~ 0
OUT1
Text GLabel 1105 5630 0    39   Input ~ 0
OUT2
Text GLabel 1105 5030 0    39   Input ~ 0
19
Text GLabel 1105 5130 0    39   Input ~ 0
21
Text GLabel 1105 5230 0    39   Input ~ 0
23
Text GLabel 1105 4630 0    39   Input ~ 0
11
Text GLabel 1105 4730 0    39   Input ~ 0
13
Text GLabel 1105 4830 0    39   Input ~ 0
BUZZER
Text GLabel 2230 5830 2    39   Input ~ 0
36
Text GLabel 2230 5930 2    39   Input ~ 0
38
Text GLabel 2230 6030 2    39   Input ~ 0
40
Text GLabel 2230 5630 2    39   Input ~ 0
32
Text GLabel 2230 5230 2    39   Input ~ 0
24
Text GLabel 2230 5330 2    39   Input ~ 0
26
Text GLabel 2230 5430 2    39   Input ~ 0
28
Text GLabel 2230 4830 2    39   Input ~ 0
ON-OFF-KEY
Text GLabel 2230 4930 2    39   Input ~ 0
SYSTEM-UP
Text GLabel 2230 5130 2    39   Input ~ 0
POWER-GOOD
Text GLabel 2230 4430 2    39   Input ~ 0
8
Text GLabel 2230 4530 2    39   Input ~ 0
10
Text GLabel 2230 4630 2    39   Input ~ 0
12
$Comp
L CONN_01X10 J6
U 1 1 5868CB80
P 11455 3520
F 0 "J6" H 11445 4180 50  0000 L CNN
F 1 "CONN_01X10" H 11000 4095 50  0000 L CNN
F 2 "Connectors_Molex:Molex_KK-6410-10_10x2.54mm_Straight" H 11455 3520 50  0001 C CNN
F 3 "" H 11455 3520 50  0000 C CNN
F 4 "Value" H 11455 3520 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 11455 3520 60  0001 C CNN "Bestelllink"
F 6 "Value" H 11455 3520 60  0001 C CNN "Technische Daten"
F 7 "Value" H 11455 3520 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 11455 3520 60  0001 C CNN "Bauform"
	1    11455 3520
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 JP4
U 1 1 58690878
P 11825 3520
F 0 "JP4" H 11815 4180 50  0000 L CNN
F 1 "CONN_01X10" H 11370 4095 50  0000 L CNN
F 2 "Connectors_Molex:Molex_KK-6410-10_10x2.54mm_Straight" H 11825 3520 50  0001 C CNN
F 3 "" H 11825 3520 50  0000 C CNN
F 4 "Value" H 11825 3520 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 11825 3520 60  0001 C CNN "Bestelllink"
F 6 "Value" H 11825 3520 60  0001 C CNN "Technische Daten"
F 7 "Value" H 11825 3520 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 11825 3520 60  0001 C CNN "Bauform"
	1    11825 3520
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 JP3
U 1 1 586133FC
P 9820 3320
F 0 "JP3" H 9739 3045 50  0000 C CNN
F 1 "Reset" H 9739 3136 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02" H 9739 3031 50  0001 C CNN
F 3 "" H 9820 3320 50  0000 C CNN
F 4 "Value" H 9820 3320 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9820 3320 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9820 3320 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9820 3320 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9820 3320 60  0001 C CNN "Bauform"
F 9 "Value" H 9739 3129 60  0001 C CNN "Funktion"
	1    9820 3320
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X04 JP6
U 1 1 5861E6BA
P 13280 8780
F 0 "JP6" H 13358 8821 50  0000 L CNN
F 1 "TWI-INTERN 5V" H 13358 8730 50  0000 L CNN
F 2 "Connectors_Molex:Molex_KK-6410-04_04x2.54mm_Straight" H 13358 8737 50  0001 L CNN
F 3 "" H 13280 8780 50  0000 C CNN
F 4 "Value" H 13280 8780 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 13280 8780 60  0001 C CNN "Bestelllink"
F 6 "Value" H 13280 8780 60  0001 C CNN "Technische Daten"
F 7 "Value" H 13280 8780 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 13280 8780 60  0001 C CNN "Bauform"
F 9 "Value" H 13358 8684 60  0001 L CNN "Funktion"
	1    13280 8780
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW2
U 1 1 586215CD
P 15220 2720
F 0 "SW2" H 15220 3005 50  0000 C CNN
F 1 "Reset" H 15220 2914 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_PTS645" H 15220 3111 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/4301x2xxx8x6.pdf" H 15220 3020 50  0001 C CNN
F 4 "Value" H 15220 2720 60  0001 C CNN "Gehäuseart"
F 5 "http://www.digikey.de/product-detail/de/wurth-electronics-inc/430182070816/732-7006-1-ND/5225454" H 15220 2720 60  0001 C CNN "Bestelllink"
F 6 "SWITCH TACTILE SPST-NO 0.05A 12V" H 15220 2720 60  0001 C CNN "Technische Daten"
F 7 "Digi-Key Teilenummer : 732-7006-1-ND" H 15220 2720 60  0001 C CNN "Bestellnummer"
F 8 "SMD" H 15220 2720 60  0001 C CNN "Bauform"
F 9 "Value" H 15220 2921 60  0001 C CNN "Funktion"
F 10 "Wurth Electronics Inc" H 15220 2720 60  0001 C CNN "Hersteller"
F 11 "430182070816" H 15220 2720 60  0001 C CNN "Hersteller Bestellnummer"
	1    15220 2720
	1    0    0    -1  
$EndComp
$Comp
L LED LED2
U 1 1 5861C520
P 15170 3320
F 0 "LED2" H 15170 3175 50  0000 C CNN
F 1 "LED" H 15170 3240 50  0000 C CNN
F 2 "LEDs:LED_1206" H 15161 3156 50  0001 C CNN
F 3 "" H 15170 3320 50  0000 C CNN
F 4 "Value" H 15170 3320 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 15170 3320 60  0001 C CNN "Bestelllink"
F 6 "Value" H 15170 3320 60  0001 C CNN "Technische Daten"
F 7 "Value" H 15170 3320 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 15170 3320 60  0001 C CNN "Bauform"
F 9 "Value" H 15161 3452 60  0001 C CNN "Funktion"
F 10 "Value" H 15170 3320 60  0001 C CNN "Hersteller"
F 11 "Value" H 15170 3320 60  0001 C CNN "Hersteller Bestellnummer"
	1    15170 3320
	1    0    0    1   
$EndComp
$Comp
L LED LED3
U 1 1 58620B67
P 14820 3520
F 0 "LED3" H 14820 3375 50  0000 C CNN
F 1 "LED" H 14820 3440 50  0000 C CNN
F 2 "LEDs:LED_1206" H 14811 3356 50  0001 C CNN
F 3 "" H 14820 3520 50  0000 C CNN
F 4 "Value" H 14820 3520 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14820 3520 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14820 3520 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14820 3520 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14820 3520 60  0001 C CNN "Bauform"
F 9 "Value" H 14811 3652 60  0001 C CNN "Funktion"
F 10 "Value" H 14820 3520 60  0001 C CNN "Hersteller"
F 11 "Value" H 14820 3520 60  0001 C CNN "Hersteller Bestellnummer"
	1    14820 3520
	1    0    0    1   
$EndComp
$Comp
L LED LED1
U 1 1 58622710
P 14670 4220
F 0 "LED1" H 14670 4075 50  0000 C CNN
F 1 "LED" H 14670 4140 50  0000 C CNN
F 2 "LEDs:LED_1206" H 14661 4056 50  0001 C CNN
F 3 "" H 14670 4220 50  0000 C CNN
F 4 "Value" H 14670 4220 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14670 4220 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14670 4220 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14670 4220 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14670 4220 60  0001 C CNN "Bauform"
F 9 "Value" H 14661 4352 60  0001 C CNN "Funktion"
F 10 "Value" H 14670 4220 60  0001 C CNN "Hersteller"
F 11 "Value" H 14670 4220 60  0001 C CNN "Hersteller Bestellnummer"
	1    14670 4220
	1    0    0    1   
$EndComp
$Comp
L LED LED5
U 1 1 586253A6
P 7920 1270
F 0 "LED5" V 7950 1120 50  0000 C CNN
F 1 "LED" V 7875 1145 50  0000 C CNN
F 2 "LEDs:LED_1206" H 7911 1106 50  0001 C CNN
F 3 "" H 7920 1270 50  0000 C CNN
F 4 "Value" H 7920 1270 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7920 1270 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7920 1270 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7920 1270 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7920 1270 60  0001 C CNN "Bauform"
F 9 "Value" H 7911 1402 60  0001 C CNN "Funktion"
F 10 "Value" H 7920 1270 60  0001 C CNN "Hersteller"
F 11 "Value" H 7920 1270 60  0001 C CNN "Hersteller Bestellnummer"
	1    7920 1270
	0    -1   1    0   
$EndComp
$Comp
L LED LED4
U 1 1 5862A552
P 4820 1270
F 0 "LED4" V 4850 1120 50  0000 C CNN
F 1 "LED" V 4775 1145 50  0000 C CNN
F 2 "LEDs:LED_1206" H 4811 1106 50  0001 C CNN
F 3 "" H 4820 1270 50  0000 C CNN
F 4 "Value" H 4820 1270 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4820 1270 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4820 1270 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4820 1270 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4820 1270 60  0001 C CNN "Bauform"
F 9 "Value" H 4811 1402 60  0001 C CNN "Funktion"
F 10 "Value" H 4820 1270 60  0001 C CNN "Hersteller"
F 11 "Value" H 4820 1270 60  0001 C CNN "Hersteller Bestellnummer"
	1    4820 1270
	0    -1   1    0   
$EndComp
$Comp
L CONN_01X04 J7
U 1 1 5862F801
P 4305 6120
F 0 "J7" H 4382 6161 50  0000 L CNN
F 1 "DHT22 3,3V" H 4382 6070 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_4pol" H 4383 6077 50  0001 L CNN
F 3 "" H 4305 6120 50  0000 C CNN
F 4 "Value" H 4305 6120 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4305 6120 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4305 6120 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4305 6120 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4305 6120 60  0001 C CNN "Bauform"
F 9 "Value" H 4382 6024 60  0001 L CNN "Funktion"
F 10 "Value" H 4305 6120 60  0001 C CNN "Hersteller"
F 11 "Value" H 4305 6120 60  0001 C CNN "Hersteller Bestellnummer"
	1    4305 6120
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 JP5
U 1 1 58634385
P 15255 8755
F 0 "JP5" H 15333 8796 50  0000 L CNN
F 1 "TWI-Pi 3,3V" H 15333 8705 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_4pol" H 15333 8712 50  0001 L CNN
F 3 "" H 15255 8755 50  0000 C CNN
F 4 "Value" H 15255 8755 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 15255 8755 60  0001 C CNN "Bestelllink"
F 6 "Value" H 15255 8755 60  0001 C CNN "Technische Daten"
F 7 "Value" H 15255 8755 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 15255 8755 60  0001 C CNN "Bauform"
F 9 "Value" H 15332 8659 60  0001 L CNN "Funktion"
F 10 "Value" H 15255 8755 60  0001 C CNN "Hersteller"
F 11 "Value" H 15255 8755 60  0001 C CNN "Hersteller Bestellnummer"
	1    15255 8755
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 J1
U 1 1 58638A68
P 15390 6870
F 0 "J1" H 15467 6911 50  0000 L CNN
F 1 "TWI EXTERN 5V" H 15467 6820 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_4pol" H 15468 6827 50  0001 L CNN
F 3 "" H 15390 6870 50  0000 C CNN
F 4 "Value" H 15390 6870 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 15390 6870 60  0001 C CNN "Bestelllink"
F 6 "Value" H 15390 6870 60  0001 C CNN "Technische Daten"
F 7 "Value" H 15390 6870 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 15390 6870 60  0001 C CNN "Bauform"
F 9 "Value" H 15467 6774 60  0001 L CNN "Funktion"
F 10 "Value" H 15390 6870 60  0001 C CNN "Hersteller"
F 11 "Value" H 15390 6870 60  0001 C CNN "Hersteller Bestellnummer"
	1    15390 6870
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J5
U 1 1 5863D4E4
P 9120 2970
F 0 "J5" H 9198 3011 50  0000 L CNN
F 1 "CONN_01X02" H 9198 2920 50  0000 L CNN
F 2 "Zimprich:Anschlussklemme_2P_RM2,54_RM5,08" H 9198 2927 50  0001 L CNN
F 3 "" H 9120 2970 50  0000 C CNN
F 4 "Value" H 9120 2970 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9120 2970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9120 2970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9120 2970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9120 2970 60  0001 C CNN "Bauform"
F 9 "Value" H 9198 2874 60  0001 L CNN "Funktion"
F 10 "Value" H 9120 2970 60  0001 C CNN "Hersteller"
F 11 "Value" H 9120 2970 60  0001 C CNN "Hersteller Bestellnummer"
	1    9120 2970
	1    0    0    -1  
$EndComp
Text GLabel 3845 3500 0    39   Input ~ 0
SIG-BUZZER
$Comp
L CONN_01X02 J2
U 1 1 586469BF
P 4795 3075
F 0 "J2" H 4873 3116 50  0000 L CNN
F 1 "CONN_01X02" H 4873 3025 50  0000 L CNN
F 2 "Zimprich:Anschlussklemme_2P_RM2,54_RM5,08" H 4873 3032 50  0001 L CNN
F 3 "" H 4795 3075 50  0000 C CNN
F 4 "Value" H 4795 3075 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4795 3075 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4795 3075 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4795 3075 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4795 3075 60  0001 C CNN "Bauform"
F 9 "Value" H 4873 2979 60  0001 L CNN "Funktion"
F 10 "Value" H 4795 3075 60  0001 C CNN "Hersteller"
F 11 "Value" H 4795 3075 60  0001 C CNN "Hersteller Bestellnummer"
	1    4795 3075
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5862B0D5
P 11720 8220
F 0 "#PWR02" H 11720 7970 50  0001 C CNN
F 1 "GND" H 11725 8047 50  0000 C CNN
F 2 "" H 11720 8220 50  0000 C CNN
F 3 "" H 11720 8220 50  0000 C CNN
	1    11720 8220
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5862C9A0
P 11170 8320
F 0 "#PWR03" H 11170 8070 50  0001 C CNN
F 1 "GND" H 11175 8147 50  0000 C CNN
F 2 "" H 11170 8320 50  0000 C CNN
F 3 "" H 11170 8320 50  0000 C CNN
	1    11170 8320
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5862DF99
P 12430 9080
F 0 "#PWR04" H 12430 8830 50  0001 C CNN
F 1 "GND" H 12435 8907 50  0000 C CNN
F 2 "" H 12430 9080 50  0000 C CNN
F 3 "" H 12430 9080 50  0000 C CNN
	1    12430 9080
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5862F47E
P 14405 9055
F 0 "#PWR05" H 14405 8805 50  0001 C CNN
F 1 "GND" H 14410 8882 50  0000 C CNN
F 2 "" H 14405 9055 50  0000 C CNN
F 3 "" H 14405 9055 50  0000 C CNN
	1    14405 9055
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 58632066
P 9220 9770
F 0 "#PWR06" H 9220 9520 50  0001 C CNN
F 1 "GND" H 9225 9597 50  0000 C CNN
F 2 "" H 9220 9770 50  0000 C CNN
F 3 "" H 9220 9770 50  0000 C CNN
	1    9220 9770
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5863365D
P 6870 9770
F 0 "#PWR07" H 6870 9520 50  0001 C CNN
F 1 "GND" H 6875 9597 50  0000 C CNN
F 2 "" H 6870 9770 50  0000 C CNN
F 3 "" H 6870 9770 50  0000 C CNN
	1    6870 9770
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 58635125
P 5370 8870
F 0 "#PWR08" H 5370 8620 50  0001 C CNN
F 1 "GND" H 5375 8697 50  0000 C CNN
F 2 "" H 5370 8870 50  0000 C CNN
F 3 "" H 5370 8870 50  0000 C CNN
	1    5370 8870
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 586368B7
P 2070 9770
F 0 "#PWR09" H 2070 9520 50  0001 C CNN
F 1 "GND" H 2075 9597 50  0000 C CNN
F 2 "" H 2070 9770 50  0000 C CNN
F 3 "" H 2070 9770 50  0000 C CNN
	1    2070 9770
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5863826D
P 2070 8870
F 0 "#PWR010" H 2070 8620 50  0001 C CNN
F 1 "GND" H 2075 8697 50  0000 C CNN
F 2 "" H 2070 8870 50  0000 C CNN
F 3 "" H 2070 8870 50  0000 C CNN
	1    2070 8870
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5863941C
P 1520 7910
F 0 "#PWR011" H 1520 7660 50  0001 C CNN
F 1 "GND" H 1525 7737 50  0000 C CNN
F 2 "" H 1520 7910 50  0000 C CNN
F 3 "" H 1520 7910 50  0000 C CNN
	1    1520 7910
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 586396CF
P 1060 7920
F 0 "#PWR012" H 1060 7670 50  0001 C CNN
F 1 "GND" H 1065 7747 50  0000 C CNN
F 2 "" H 1060 7920 50  0000 C CNN
F 3 "" H 1060 7920 50  0000 C CNN
	1    1060 7920
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5863A548
P 3020 6970
F 0 "#PWR013" H 3020 6720 50  0001 C CNN
F 1 "GND" H 3025 6797 50  0000 C CNN
F 2 "" H 3020 6970 50  0000 C CNN
F 3 "" H 3020 6970 50  0000 C CNN
	1    3020 6970
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5863BBC8
P 5620 6870
F 0 "#PWR014" H 5620 6620 50  0001 C CNN
F 1 "GND" H 5625 6697 50  0000 C CNN
F 2 "" H 5620 6870 50  0000 C CNN
F 3 "" H 5620 6870 50  0000 C CNN
	1    5620 6870
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5863CF12
P 4020 6345
F 0 "#PWR015" H 4020 6095 50  0001 C CNN
F 1 "GND" H 4025 6172 50  0000 C CNN
F 2 "" H 4020 6345 50  0000 C CNN
F 3 "" H 4020 6345 50  0000 C CNN
	1    4020 6345
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5863EF39
P 1205 6125
F 0 "#PWR016" H 1205 5875 50  0001 C CNN
F 1 "GND" H 1210 5952 50  0000 C CNN
F 2 "" H 1205 6125 50  0000 C CNN
F 3 "" H 1205 6125 50  0000 C CNN
	1    1205 6125
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 58640978
P 1205 3580
F 0 "#PWR017" H 1205 3330 50  0001 C CNN
F 1 "GND" H 1210 3407 50  0000 C CNN
F 2 "" H 1205 3580 50  0000 C CNN
F 3 "" H 1205 3580 50  0000 C CNN
	1    1205 3580
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 586410FC
P 2225 3905
F 0 "#PWR018" H 2225 3655 50  0001 C CNN
F 1 "GND" H 2230 3732 50  0000 C CNN
F 2 "" H 2225 3905 50  0000 C CNN
F 3 "" H 2225 3905 50  0000 C CNN
	1    2225 3905
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 58642D65
P 3955 4825
F 0 "#PWR019" H 3955 4575 50  0001 C CNN
F 1 "GND" H 3960 4652 50  0000 C CNN
F 2 "" H 3955 4825 50  0000 C CNN
F 3 "" H 3955 4825 50  0000 C CNN
	1    3955 4825
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 586440AF
P 8920 5320
F 0 "#PWR020" H 8920 5070 50  0001 C CNN
F 1 "GND" H 8925 5147 50  0000 C CNN
F 2 "" H 8920 5320 50  0000 C CNN
F 3 "" H 8920 5320 50  0000 C CNN
	1    8920 5320
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 586456A6
P 11170 5770
F 0 "#PWR021" H 11170 5520 50  0001 C CNN
F 1 "GND" H 11175 5597 50  0000 C CNN
F 2 "" H 11170 5770 50  0000 C CNN
F 3 "" H 11170 5770 50  0000 C CNN
	1    11170 5770
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 58647A0C
P 13720 5920
F 0 "#PWR022" H 13720 5670 50  0001 C CNN
F 1 "GND" H 13725 5747 50  0000 C CNN
F 2 "" H 13720 5920 50  0000 C CNN
F 3 "" H 13720 5920 50  0000 C CNN
	1    13720 5920
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5864843D
P 15070 5920
F 0 "#PWR023" H 15070 5670 50  0001 C CNN
F 1 "GND" H 15075 5747 50  0000 C CNN
F 2 "" H 15070 5920 50  0000 C CNN
F 3 "" H 15070 5920 50  0000 C CNN
	1    15070 5920
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 5864B2D2
P 11000 4070
F 0 "#PWR024" H 11000 3820 50  0001 C CNN
F 1 "GND" H 11005 3897 50  0000 C CNN
F 2 "" H 11000 4070 50  0000 C CNN
F 3 "" H 11000 4070 50  0000 C CNN
	1    11000 4070
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5864CEAC
P 8870 3120
F 0 "#PWR025" H 8870 2870 50  0001 C CNN
F 1 "GND" H 8875 2947 50  0000 C CNN
F 2 "" H 8870 3120 50  0000 C CNN
F 3 "" H 8870 3120 50  0000 C CNN
	1    8870 3120
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 5864DC13
P 7420 3120
F 0 "#PWR026" H 7420 2870 50  0001 C CNN
F 1 "GND" H 7425 2947 50  0000 C CNN
F 2 "" H 7420 3120 50  0000 C CNN
F 3 "" H 7420 3120 50  0000 C CNN
	1    7420 3120
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 5864E8F1
P 6070 3120
F 0 "#PWR027" H 6070 2870 50  0001 C CNN
F 1 "GND" H 6075 2947 50  0000 C CNN
F 2 "" H 6070 3120 50  0000 C CNN
F 3 "" H 6070 3120 50  0000 C CNN
	1    6070 3120
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 586511A3
P 5120 2180
F 0 "#PWR028" H 5120 1930 50  0001 C CNN
F 1 "GND" H 5125 2007 50  0000 C CNN
F 2 "" H 5120 2180 50  0000 C CNN
F 3 "" H 5120 2180 50  0000 C CNN
	1    5120 2180
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 586533F0
P 8270 2195
F 0 "#PWR029" H 8270 1945 50  0001 C CNN
F 1 "GND" H 8275 2022 50  0000 C CNN
F 2 "" H 8270 2195 50  0000 C CNN
F 3 "" H 8270 2195 50  0000 C CNN
	1    8270 2195
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 58654EBF
P 10820 2120
F 0 "#PWR030" H 10820 1870 50  0001 C CNN
F 1 "GND" H 10825 1947 50  0000 C CNN
F 2 "" H 10820 2120 50  0000 C CNN
F 3 "" H 10820 2120 50  0000 C CNN
	1    10820 2120
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 58656181
P 12020 2120
F 0 "#PWR031" H 12020 1870 50  0001 C CNN
F 1 "GND" H 12025 1947 50  0000 C CNN
F 2 "" H 12020 2120 50  0000 C CNN
F 3 "" H 12020 2120 50  0000 C CNN
	1    12020 2120
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 58658C59
P 14820 7070
F 0 "#PWR032" H 14820 6820 50  0001 C CNN
F 1 "GND" H 14825 6897 50  0000 C CNN
F 2 "" H 14820 7070 50  0000 C CNN
F 3 "" H 14820 7070 50  0000 C CNN
	1    14820 7070
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR033
U 1 1 5865E4B3
P 9920 2120
F 0 "#PWR033" H 9920 1970 50  0001 C CNN
F 1 "+5V" H 9935 2293 50  0000 C CNN
F 2 "" H 9920 2120 50  0000 C CNN
F 3 "" H 9920 2120 50  0000 C CNN
	1    9920 2120
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR034
U 1 1 58660AC4
P 2225 1610
F 0 "#PWR034" H 2225 1460 50  0001 C CNN
F 1 "+5V" H 2240 1783 50  0000 C CNN
F 2 "" H 2225 1610 50  0000 C CNN
F 3 "" H 2225 1610 50  0000 C CNN
	1    2225 1610
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR035
U 1 1 586624D8
P 2225 4230
F 0 "#PWR035" H 2225 4080 50  0001 C CNN
F 1 "+5V" H 2240 4403 50  0000 C CNN
F 2 "" H 2225 4230 50  0000 C CNN
F 3 "" H 2225 4230 50  0000 C CNN
	1    2225 4230
	1    0    0    1   
$EndComp
$Comp
L GND #PWR036
U 1 1 5866413B
P 2225 1335
F 0 "#PWR036" H 2225 1085 50  0001 C CNN
F 1 "GND" H 2230 1162 50  0000 C CNN
F 2 "" H 2225 1335 50  0000 C CNN
F 3 "" H 2225 1335 50  0000 C CNN
	1    2225 1335
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR037
U 1 1 5866615D
P 5620 3120
F 0 "#PWR037" H 5620 2970 50  0001 C CNN
F 1 "+5V" H 5635 3293 50  0000 C CNN
F 2 "" H 5620 3120 50  0000 C CNN
F 3 "" H 5620 3120 50  0000 C CNN
	1    5620 3120
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR038
U 1 1 58666CA0
P 6970 3120
F 0 "#PWR038" H 6970 2970 50  0001 C CNN
F 1 "+5V" H 6985 3293 50  0000 C CNN
F 2 "" H 6970 3120 50  0000 C CNN
F 3 "" H 6970 3120 50  0000 C CNN
	1    6970 3120
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR039
U 1 1 58667ED8
P 8420 3120
F 0 "#PWR039" H 8420 2970 50  0001 C CNN
F 1 "+5V" H 8435 3293 50  0000 C CNN
F 2 "" H 8420 3120 50  0000 C CNN
F 3 "" H 8420 3120 50  0000 C CNN
	1    8420 3120
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR040
U 1 1 586692AB
P 10970 4670
F 0 "#PWR040" H 10970 4520 50  0001 C CNN
F 1 "+5V" H 10985 4843 50  0000 C CNN
F 2 "" H 10970 4670 50  0000 C CNN
F 3 "" H 10970 4670 50  0000 C CNN
	1    10970 4670
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR041
U 1 1 5866ADFC
P 13420 5920
F 0 "#PWR041" H 13420 5770 50  0001 C CNN
F 1 "+5V" H 13435 6093 50  0000 C CNN
F 2 "" H 13420 5920 50  0000 C CNN
F 3 "" H 13420 5920 50  0000 C CNN
	1    13420 5920
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR042
U 1 1 5866BE99
P 15320 5920
F 0 "#PWR042" H 15320 5770 50  0001 C CNN
F 1 "+5V" H 15335 6093 50  0000 C CNN
F 2 "" H 15320 5920 50  0000 C CNN
F 3 "" H 15320 5920 50  0000 C CNN
	1    15320 5920
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR043
U 1 1 5866D1E3
P 13220 6520
F 0 "#PWR043" H 13220 6370 50  0001 C CNN
F 1 "+5V" H 13235 6693 50  0000 C CNN
F 2 "" H 13220 6520 50  0000 C CNN
F 3 "" H 13220 6520 50  0000 C CNN
	1    13220 6520
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR044
U 1 1 5866E16E
P 10970 7320
F 0 "#PWR044" H 10970 7170 50  0001 C CNN
F 1 "+5V" H 10985 7493 50  0000 C CNN
F 2 "" H 10970 7320 50  0000 C CNN
F 3 "" H 10970 7320 50  0000 C CNN
	1    10970 7320
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR045
U 1 1 586702A2
P 7920 9770
F 0 "#PWR045" H 7920 9620 50  0001 C CNN
F 1 "+5V" H 7935 9943 50  0000 C CNN
F 2 "" H 7920 9770 50  0000 C CNN
F 3 "" H 7920 9770 50  0000 C CNN
	1    7920 9770
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR046
U 1 1 58677282
P 3170 6270
F 0 "#PWR046" H 3170 6120 50  0001 C CNN
F 1 "+3V3" H 3185 6443 50  0000 C CNN
F 2 "" H 3170 6270 50  0000 C CNN
F 3 "" H 3170 6270 50  0000 C CNN
	1    3170 6270
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR047
U 1 1 58678F7A
P 655 4225
F 0 "#PWR047" H 655 4075 50  0001 C CNN
F 1 "+3V3" H 670 4398 50  0000 C CNN
F 2 "" H 655 4225 50  0000 C CNN
F 3 "" H 655 4225 50  0000 C CNN
	1    655  4225
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR048
U 1 1 5867AC66
P 655 1680
F 0 "#PWR048" H 655 1530 50  0001 C CNN
F 1 "+3V3" H 670 1853 50  0000 C CNN
F 2 "" H 655 1680 50  0000 C CNN
F 3 "" H 655 1680 50  0000 C CNN
	1    655  1680
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR049
U 1 1 5867FCB8
P 10570 7320
F 0 "#PWR049" H 10570 7170 50  0001 C CNN
F 1 "+3V3" H 10585 7493 50  0000 C CNN
F 2 "" H 10570 7320 50  0000 C CNN
F 3 "" H 10570 7320 50  0000 C CNN
	1    10570 7320
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR050
U 1 1 58684798
P 3155 4825
F 0 "#PWR050" H 3155 4675 50  0001 C CNN
F 1 "VCC" H 3172 4998 50  0000 C CNN
F 2 "" H 3155 4825 50  0000 C CNN
F 3 "" H 3155 4825 50  0000 C CNN
	1    3155 4825
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR051
U 1 1 58686F44
P 10750 4070
F 0 "#PWR051" H 10750 3920 50  0001 C CNN
F 1 "VCC" H 10767 4243 50  0000 C CNN
F 2 "" H 10750 4070 50  0000 C CNN
F 3 "" H 10750 4070 50  0000 C CNN
	1    10750 4070
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR052
U 1 1 5868875F
P 7870 6020
F 0 "#PWR052" H 7870 5870 50  0001 C CNN
F 1 "VCC" H 7887 6193 50  0000 C CNN
F 2 "" H 7870 6020 50  0000 C CNN
F 3 "" H 7870 6020 50  0000 C CNN
	1    7870 6020
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR053
U 1 1 58689E68
P 10570 4670
F 0 "#PWR053" H 10570 4520 50  0001 C CNN
F 1 "+3V3" H 10585 4843 50  0000 C CNN
F 2 "" H 10570 4670 50  0000 C CNN
F 3 "" H 10570 4670 50  0000 C CNN
	1    10570 4670
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR054
U 1 1 5868C8B5
P 4820 6870
F 0 "#PWR054" H 4820 6720 50  0001 C CNN
F 1 "VCC" H 4837 7043 50  0000 C CNN
F 2 "" H 4820 6870 50  0000 C CNN
F 3 "" H 4820 6870 50  0000 C CNN
	1    4820 6870
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR055
U 1 1 5868D3F8
P 5970 6870
F 0 "#PWR055" H 5970 6720 50  0001 C CNN
F 1 "VCC" H 5987 7043 50  0000 C CNN
F 2 "" H 5970 6870 50  0000 C CNN
F 3 "" H 5970 6870 50  0000 C CNN
	1    5970 6870
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR056
U 1 1 5868EC9C
P 7370 9770
F 0 "#PWR056" H 7370 9620 50  0001 C CNN
F 1 "VCC" H 7387 9943 50  0000 C CNN
F 2 "" H 7370 9770 50  0000 C CNN
F 3 "" H 7370 9770 50  0000 C CNN
	1    7370 9770
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR057
U 1 1 5868F532
P 7070 8870
F 0 "#PWR057" H 7070 8720 50  0001 C CNN
F 1 "+3V3" H 7085 9043 50  0000 C CNN
F 2 "" H 7070 8870 50  0000 C CNN
F 3 "" H 7070 8870 50  0000 C CNN
	1    7070 8870
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR058
U 1 1 58691AAE
P 1520 7110
F 0 "#PWR058" H 1520 6960 50  0001 C CNN
F 1 "VCC" H 1537 7283 50  0000 C CNN
F 2 "" H 1520 7110 50  0000 C CNN
F 3 "" H 1520 7110 50  0000 C CNN
	1    1520 7110
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR059
U 1 1 58692927
P 1060 7105
F 0 "#PWR059" H 1060 6955 50  0001 C CNN
F 1 "VCC" H 1077 7278 50  0000 C CNN
F 2 "" H 1060 7105 50  0000 C CNN
F 3 "" H 1060 7105 50  0000 C CNN
	1    1060 7105
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5862ACFB
P 6270 9420
F 0 "C4" H 6385 9466 50  0000 L CNN
F 1 "100nF" H 6385 9375 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6385 9382 50  0001 L CNN
F 3 "" H 6270 9420 50  0000 C CNN
F 4 "Value" H 6270 9420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6270 9420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6270 9420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6270 9420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6270 9420 60  0001 C CNN "Bauform"
F 9 "Value" H 6385 9329 60  0001 L CNN "Funktion"
F 10 "Value" H 6270 9420 60  0001 C CNN "Hersteller"
F 11 "Value" H 6270 9420 60  0001 C CNN "Hersteller Bestellnummer"
	1    6270 9420
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58628F69
P 5870 9420
F 0 "C2" H 5985 9466 50  0000 L CNN
F 1 "100nF" H 5985 9375 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5985 9382 50  0001 L CNN
F 3 "" H 5870 9420 50  0000 C CNN
F 4 "Value" H 5870 9420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5870 9420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5870 9420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5870 9420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5870 9420 60  0001 C CNN "Bauform"
F 9 "Value" H 5985 9329 60  0001 L CNN "Funktion"
F 10 "Value" H 5870 9420 60  0001 C CNN "Hersteller"
F 11 "Value" H 5870 9420 60  0001 C CNN "Hersteller Bestellnummer"
	1    5870 9420
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5862FA03
P 8420 9120
F 0 "C5" H 8535 9166 50  0000 L CNN
F 1 "100nF" H 8535 9075 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8535 9082 50  0001 L CNN
F 3 "" H 8420 9120 50  0000 C CNN
F 4 "Value" H 8420 9120 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8420 9120 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8420 9120 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8420 9120 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8420 9120 60  0001 C CNN "Bauform"
F 9 "Value" H 8535 9029 60  0001 L CNN "Funktion"
F 10 "Value" H 8420 9120 60  0001 C CNN "Hersteller"
F 11 "Value" H 8420 9120 60  0001 C CNN "Hersteller Bestellnummer"
	1    8420 9120
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 58631A78
P 10770 8120
F 0 "C11" H 10885 8166 50  0000 L CNN
F 1 "100nF" H 10885 8075 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10885 8082 50  0001 L CNN
F 3 "" H 10770 8120 50  0000 C CNN
F 4 "Value" H 10770 8120 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 10770 8120 60  0001 C CNN "Bestelllink"
F 6 "Value" H 10770 8120 60  0001 C CNN "Technische Daten"
F 7 "Value" H 10770 8120 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10770 8120 60  0001 C CNN "Bauform"
F 9 "Value" H 10885 8029 60  0001 L CNN "Funktion"
F 10 "Value" H 10770 8120 60  0001 C CNN "Hersteller"
F 11 "Value" H 10770 8120 60  0001 C CNN "Hersteller Bestellnummer"
	1    10770 8120
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 5863329F
P 11170 8120
F 0 "C10" H 11285 8166 50  0000 L CNN
F 1 "100nF" H 11285 8075 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11285 8082 50  0001 L CNN
F 3 "" H 11170 8120 50  0000 C CNN
F 4 "Value" H 11170 8120 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 11170 8120 60  0001 C CNN "Bestelllink"
F 6 "Value" H 11170 8120 60  0001 C CNN "Technische Daten"
F 7 "Value" H 11170 8120 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 11170 8120 60  0001 C CNN "Bauform"
F 9 "Value" H 11285 8029 60  0001 L CNN "Funktion"
F 10 "Value" H 11170 8120 60  0001 C CNN "Hersteller"
F 11 "Value" H 11170 8120 60  0001 C CNN "Hersteller Bestellnummer"
	1    11170 8120
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5863622B
P 10770 5570
F 0 "C8" H 10885 5616 50  0000 L CNN
F 1 "100nF" H 10885 5525 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10885 5532 50  0001 L CNN
F 3 "" H 10770 5570 50  0000 C CNN
F 4 "Value" H 10770 5570 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 10770 5570 60  0001 C CNN "Bestelllink"
F 6 "Value" H 10770 5570 60  0001 C CNN "Technische Daten"
F 7 "Value" H 10770 5570 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10770 5570 60  0001 C CNN "Bauform"
F 9 "Value" H 10885 5479 60  0001 L CNN "Funktion"
F 10 "Value" H 10770 5570 60  0001 C CNN "Hersteller"
F 11 "Value" H 10770 5570 60  0001 C CNN "Hersteller Bestellnummer"
	1    10770 5570
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 586373F8
P 11170 5570
F 0 "C9" H 11285 5616 50  0000 L CNN
F 1 "100nF" H 11285 5525 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11285 5532 50  0001 L CNN
F 3 "" H 11170 5570 50  0000 C CNN
F 4 "Value" H 11170 5570 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 11170 5570 60  0001 C CNN "Bestelllink"
F 6 "Value" H 11170 5570 60  0001 C CNN "Technische Daten"
F 7 "Value" H 11170 5570 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 11170 5570 60  0001 C CNN "Bauform"
F 9 "Value" H 11285 5479 60  0001 L CNN "Funktion"
F 10 "Value" H 11170 5570 60  0001 C CNN "Hersteller"
F 11 "Value" H 11170 5570 60  0001 C CNN "Hersteller Bestellnummer"
	1    11170 5570
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 5863BCCF
P 3670 6120
F 0 "C12" H 3785 6166 50  0000 L CNN
F 1 "100nF" H 3785 6075 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3785 6082 50  0001 L CNN
F 3 "" H 3670 6120 50  0000 C CNN
F 4 "Value" H 3670 6120 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3670 6120 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3670 6120 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3670 6120 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3670 6120 60  0001 C CNN "Bauform"
F 9 "Value" H 3785 6029 60  0001 L CNN "Funktion"
F 10 "Value" H 3670 6120 60  0001 C CNN "Hersteller"
F 11 "Value" H 3670 6120 60  0001 C CNN "Hersteller Bestellnummer"
	1    3670 6120
	-1   0    0    -1  
$EndComp
$Comp
L CP C7
U 1 1 5863E9E7
P 3605 4725
F 0 "C7" V 3350 4725 50  0000 C CNN
F 1 "22uF" V 3441 4725 50  0000 C CNN
F 2 "Capacitors_THT:C_Radial_D10_L20_P2.5-5" V 3442 4725 50  0001 C CNN
F 3 "" H 3605 4725 50  0000 C CNN
F 4 "Value" H 3605 4725 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3605 4725 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3605 4725 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3605 4725 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3605 4725 60  0001 C CNN "Bauform"
F 9 "Value" V 3434 4725 60  0001 C CNN "Funktion"
F 10 "Value" H 3605 4725 60  0001 C CNN "Hersteller"
F 11 "Value" H 3605 4725 60  0001 C CNN "Hersteller Bestellnummer"
	1    3605 4725
	0    -1   1    0   
$EndComp
$Comp
L C C3
U 1 1 5864386F
P 5220 5820
F 0 "C3" H 5334 5866 50  0000 L CNN
F 1 "330nF" H 5334 5775 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_5x5.8" H 5335 5782 50  0001 L CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/B300/WIMA_SMD_PET.pdf" H 5220 5820 50  0001 C CNN
F 4 "SMD-PET  L:5,7mm B:5,1mm H:4,6mm" H 5220 5820 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SMD-PET/PET2220-100-330N/3/index.html?ACTION=3&LA=446&ARTICLE=31418&GROUPID=7178&artnr=PET2220-100+330N&SEARCH=330nf%2Bsmd" H 5220 5820 60  0001 C CNN "Bestelllink"
F 6 "SMD Kondensator 2220, 330nF, 100V, PET-Folie" H 5220 5820 60  0001 C CNN "Technische Daten"
F 7 "R: PET2220-100 330N" H 5220 5820 60  0001 C CNN "Bestellnummer"
F 8 "SMD-PET" H 5220 5820 60  0001 C CNN "Bauform"
F 9 "Value" H 5335 5729 60  0001 L CNN "Funktion"
F 10 "Value" H 5220 5820 60  0001 C CNN "Hersteller"
F 11 "Value" H 5220 5820 60  0001 C CNN "Hersteller Bestellnummer"
	1    5220 5820
	-1   0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 586470F6
P 6870 9420
F 0 "C1" H 6988 9466 50  0000 L CNN
F 1 "2200uF" H 6988 9375 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D10_L20_P5-7.5" V 6707 9420 50  0001 C CNN
F 3 "" H 6870 9420 50  0000 C CNN
F 4 "Value" H 6870 9420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6870 9420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6870 9420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6870 9420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6870 9420 60  0001 C CNN "Bauform"
F 9 "Value" V 6699 9420 60  0001 C CNN "Funktion"
F 10 "Value" H 6870 9420 60  0001 C CNN "Hersteller"
F 11 "Value" H 6870 9420 60  0001 C CNN "Hersteller Bestellnummer"
	1    6870 9420
	1    0    0    -1  
$EndComp
$Comp
L Buzzer SP1
U 1 1 5864DDA7
P 3855 3200
F 0 "SP1" H 4008 3229 50  0000 L CNN
F 1 "AL60P" H 4008 3138 50  0000 L CNN
F 2 "Zimprich:Buzzer_12x9.5RM7.6_RM5.0" H 4008 3145 50  0001 L CNN
F 3 "" V 3830 3300 50  0000 C CNN
F 4 "Value" H 3855 3200 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3855 3200 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3855 3200 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3855 3200 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3855 3200 60  0001 C CNN "Bauform"
F 9 "Value" H 4008 3092 60  0001 L CNN "Funktion"
F 10 "Value" H 3855 3200 60  0001 C CNN "Hersteller"
F 11 "Value" H 3855 3200 60  0001 C CNN "Hersteller Bestellnummer"
	1    3855 3200
	-1   0    0    -1  
$EndComp
$Comp
L VCC #PWR060
U 1 1 5864F416
P 4445 3170
F 0 "#PWR060" H 4445 3020 50  0001 C CNN
F 1 "VCC" H 4462 3343 50  0000 C CNN
F 2 "" H 4445 3170 50  0000 C CNN
F 3 "" H 4445 3170 50  0000 C CNN
	1    4445 3170
	1    0    0    1   
$EndComp
$Comp
L +3V3 #PWR061
U 1 1 58654B31
P 8470 4870
F 0 "#PWR061" H 8470 4720 50  0001 C CNN
F 1 "+3V3" H 8485 5043 50  0000 C CNN
F 2 "" H 8470 4870 50  0000 C CNN
F 3 "" H 8470 4870 50  0000 C CNN
	1    8470 4870
	1    0    0    1   
$EndComp
$Comp
L VCC #PWR062
U 1 1 586578B4
P 7270 4870
F 0 "#PWR062" H 7270 4720 50  0001 C CNN
F 1 "VCC" H 7287 5043 50  0000 C CNN
F 2 "" H 7270 4870 50  0000 C CNN
F 3 "" H 7270 4870 50  0000 C CNN
	1    7270 4870
	1    0    0    1   
$EndComp
$Comp
L Tact_Switch_12x12mm_with_integrated_LED SW1
U 1 1 5865D1FF
P 14120 1370
F 0 "SW1" H 14120 1670 45  0000 C CNN
F 1 "Tact_Switch_12x12mm_with_integrated_LED" H 14120 1603 24  0000 C CNN
F 2 "Zimprich:Tact_Switch_12x12mm_with_integrated_LED" H 14150 1520 20  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/440xx67082622.pdf" H 14120 1370 60  0001 C CNN
F 4 "Value" H 14120 1370 60  0001 C CNN "Gehäuseart"
F 5 "http://www.digikey.de/product-detail/de/wurth-electronics-inc/440GS67082622/440GS67082622-ND/5209097" H 14120 1370 60  0001 C CNN "Bestelllink"
F 6 "WS-TATL 12x12mm Tact Switch with integrated LED, THT version" H 14120 1370 60  0001 C CNN "Technische Daten"
F 7 "Digikey:_440GS67082622-ND" H 14120 1370 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14120 1370 60  0001 C CNN "Bauform"
F 9 "Tastschalter" H 14120 1631 60  0001 C CNN "Funktion"
F 10 "Würth Elektronik" H 14120 1370 60  0001 C CNN "Hersteller"
F 11 "440GS67082622" H 14120 1370 60  0001 C CNN "Hersteller Bestellnummer"
	1    14120 1370
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 ST4
U 1 1 5862F68F
P 3470 820
F 0 "ST4" V 3435 632 50  0000 R CNN
F 1 "691312710003" V 3344 632 50  0000 R CNN
F 2 "w_conn_screw:mstba_2,5%2f3-g-5,08" V 3351 632 50  0001 R CNN
F 3 "" H 3470 820 50  0000 C CNN
F 4 "Value" H 3470 820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3470 820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3470 820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3470 820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3470 820 60  0001 C CNN "Bauform"
F 9 "Value" V 3298 632 60  0001 R CNN "Funktion"
F 10 "Value" H 3470 820 60  0001 C CNN "Hersteller"
F 11 "Value" H 3470 820 60  0001 C CNN "Hersteller Bestellnummer"
	1    3470 820 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 ST5
U 1 1 58630F54
P 6570 820
F 0 "ST5" V 6535 632 50  0000 R CNN
F 1 "691312710003" V 6444 632 50  0000 R CNN
F 2 "w_conn_screw:mstba_2,5%2f3-g-5,08" V 6451 632 50  0001 R CNN
F 3 "" H 6570 820 50  0000 C CNN
F 4 "Value" H 6570 820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6570 820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6570 820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6570 820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6570 820 60  0001 C CNN "Bauform"
F 9 "Value" V 6398 632 60  0001 R CNN "Funktion"
F 10 "Value" H 6570 820 60  0001 C CNN "Hersteller"
F 11 "Value" H 6570 820 60  0001 C CNN "Hersteller Bestellnummer"
	1    6570 820 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 ST6
U 1 1 58632B69
P 10220 820
F 0 "ST6" V 10185 998 50  0000 L CNN
F 1 "691312710003" V 10094 998 50  0000 L CNN
F 2 "w_conn_screw:mstba_2,5%2f3-g-5,08" V 10101 998 50  0001 L CNN
F 3 "" H 10220 820 50  0000 C CNN
F 4 "Value" H 10220 820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 10220 820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 10220 820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 10220 820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10220 820 60  0001 C CNN "Bauform"
F 9 "Value" V 10048 998 60  0001 L CNN "Funktion"
F 10 "Value" H 10220 820 60  0001 C CNN "Hersteller"
F 11 "Value" H 10220 820 60  0001 C CNN "Hersteller Bestellnummer"
	1    10220 820 
	0    1    -1   0   
$EndComp
$Comp
L CONN_01X03 ST7
U 1 1 58636EE1
P 11420 820
F 0 "ST7" V 11385 998 50  0000 L CNN
F 1 "691312710003" V 11294 998 50  0000 L CNN
F 2 "w_conn_screw:mstba_2,5%2f3-g-5,08" V 11301 998 50  0001 L CNN
F 3 "" H 11420 820 50  0000 C CNN
F 4 "Value" H 11420 820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 11420 820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 11420 820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 11420 820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 11420 820 60  0001 C CNN "Bauform"
F 9 "Value" V 11248 998 60  0001 L CNN "Funktion"
F 10 "Value" H 11420 820 60  0001 C CNN "Hersteller"
F 11 "Value" H 11420 820 60  0001 C CNN "Hersteller Bestellnummer"
	1    11420 820 
	0    1    -1   0   
$EndComp
$Comp
L CONN_01X02 ST1
U 1 1 58640F5A
P 1870 9320
F 0 "ST1" H 1948 9361 50  0000 L CNN
F 1 "691313510002" H 1948 9270 50  0000 L CNN
F 2 "w_conn_screw:mstba_2,5%2f2-g-5,08" H 1948 9277 50  0001 L CNN
F 3 "" H 1870 9320 50  0000 C CNN
F 4 "Value" H 1870 9320 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1870 9320 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1870 9320 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1870 9320 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1870 9320 60  0001 C CNN "Bauform"
F 9 "Value" H 1948 9224 60  0001 L CNN "Funktion"
F 10 "Value" H 1870 9320 60  0001 C CNN "Hersteller"
F 11 "Value" H 1870 9320 60  0001 C CNN "Hersteller Bestellnummer"
	1    1870 9320
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X03 ST3
U 1 1 5864C2E2
P 9870 9820
F 0 "ST3" V 9835 9998 50  0000 L CNN
F 1 "691312710003" V 9744 9998 50  0000 L CNN
F 2 "w_conn_screw:mstba_2,5%2f3-g-5,08" V 9751 9998 50  0001 L CNN
F 3 "" H 9870 9820 50  0000 C CNN
F 4 "Value" H 9870 9820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9870 9820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9870 9820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9870 9820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9870 9820 60  0001 C CNN "Bauform"
F 9 "Value" V 9698 9998 60  0001 L CNN "Funktion"
F 10 "Value" H 9870 9820 60  0001 C CNN "Hersteller"
F 11 "Value" H 9870 9820 60  0001 C CNN "Hersteller Bestellnummer"
	1    9870 9820
	0    -1   1    0   
$EndComp
Text Notes 4705 185  0    60   ~ 0
BC377 ersetzt mit BC817
$Comp
L BC817-40 Q5
U 1 1 5863F433
P 5220 1470
F 0 "Q5" H 5080 1665 50  0000 L CNN
F 1 "BC817" H 4930 1585 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5411 1379 50  0001 L CIN
F 3 "" H 5220 1470 50  0000 L CNN
F 4 "Value" H 5220 1470 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5220 1470 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5220 1470 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5220 1470 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5220 1470 60  0001 C CNN "Bauform"
F 9 "Value" H 5220 1470 60  0001 C CNN "Funktion"
F 10 "Value" H 5220 1470 60  0001 C CNN "Hersteller"
F 11 "Value" H 5220 1470 60  0001 C CNN "Hersteller Bestellnummer"
	1    5220 1470
	-1   0    0    -1  
$EndComp
$Comp
L BC817-40 Q6
U 1 1 58644804
P 8370 1470
F 0 "Q6" H 8230 1665 50  0000 L CNN
F 1 "BC817" H 8080 1585 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8561 1379 50  0001 L CIN
F 3 "" H 8370 1470 50  0000 L CNN
F 4 "Value" H 8370 1470 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8370 1470 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8370 1470 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8370 1470 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8370 1470 60  0001 C CNN "Bauform"
F 9 "Value" H 8370 1470 60  0001 C CNN "Funktion"
F 10 "Value" H 8370 1470 60  0001 C CNN "Hersteller"
F 11 "Value" H 8370 1470 60  0001 C CNN "Hersteller Bestellnummer"
	1    8370 1470
	-1   0    0    -1  
$EndComp
$Comp
L BC817-40 Q4
U 1 1 5864B3AD
P 4055 3975
F 0 "Q4" H 3915 4170 50  0000 L CNN
F 1 "BC817" H 3765 4090 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4246 3884 50  0001 L CIN
F 3 "" H 4055 3975 50  0000 L CNN
F 4 "Value" H 4055 3975 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4055 3975 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4055 3975 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4055 3975 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4055 3975 60  0001 C CNN "Bauform"
F 9 "Value" H 4055 3975 60  0001 C CNN "Funktion"
F 10 "Value" H 4055 3975 60  0001 C CNN "Hersteller"
F 11 "Value" H 4055 3975 60  0001 C CNN "Hersteller Bestellnummer"
	1    4055 3975
	-1   0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 58641136
P 3605 4315
F 0 "C6" V 3857 4315 50  0000 C CNN
F 1 "100nF" V 3766 4315 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805" H 3720 4277 50  0001 L CNN
F 3 "" H 3605 4315 50  0000 C CNN
F 4 "Value" H 3605 4315 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3605 4315 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3605 4315 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3605 4315 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3605 4315 60  0001 C CNN "Bauform"
F 9 "Value" H 3720 4224 60  0001 L CNN "Funktion"
F 10 "Value" H 3605 4315 60  0001 C CNN "Hersteller"
F 11 "Value" H 3605 4315 60  0001 C CNN "Hersteller Bestellnummer"
	1    3605 4315
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 ST2
U 1 1 5865A14C
P 1870 8720
F 0 "ST2" H 1948 8761 50  0000 L CNN
F 1 "691313510002" H 1948 8670 50  0000 L CNN
F 2 "w_conn_screw:mstba_2,5%2f2-g-5,08" H 1948 8677 50  0001 L CNN
F 3 "" H 1870 8720 50  0000 C CNN
F 4 "Value" H 1870 8720 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1870 8720 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1870 8720 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1870 8720 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1870 8720 60  0001 C CNN "Bauform"
F 9 "Value" H 1948 8624 60  0001 L CNN "Funktion"
F 10 "Value" H 1870 8720 60  0001 C CNN "Hersteller"
F 11 "Value" H 1870 8720 60  0001 C CNN "Hersteller Bestellnummer"
	1    1870 8720
	-1   0    0    -1  
$EndComp
$Comp
L BC817-40 Q3
U 1 1 5865DB41
P 3570 6970
F 0 "Q3" H 3430 7165 50  0000 L CNN
F 1 "BC817" H 3280 7085 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3761 6879 50  0001 L CIN
F 3 "" H 3570 6970 50  0000 L CNN
F 4 "Value" H 3570 6970 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/index.html?ACTION=446&LA=3" H 3570 6970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3570 6970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3570 6970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3570 6970 60  0001 C CNN "Bauform"
F 9 "Value" H 3570 6970 60  0001 C CNN "Funktion"
F 10 "Value" H 3570 6970 60  0001 C CNN "Hersteller"
F 11 "Value" H 3570 6970 60  0001 C CNN "Hersteller Bestellnummer"
	1    3570 6970
	-1   0    0    1   
$EndComp
$Comp
L Polyfuse F6
U 1 1 58661884
P 9920 1470
F 0 "F6" H 10070 1500 50  0000 L CNN
F 1 "Polyfuse" H 10015 1420 50  0000 L CNN
F 2 "Zimprich:Polyfuse" H 9970 1270 50  0001 L CNN
F 3 "" H 9920 1470 50  0001 C CNN
F 4 "Value" H 9920 1470 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9920 1470 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9920 1470 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9920 1470 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9920 1470 60  0001 C CNN "Bauform"
F 9 "Value" H 10008 1379 60  0001 L CNN "Funktion"
F 10 "Value" H 9920 1470 60  0001 C CNN "Hersteller"
F 11 "Value" H 9920 1470 60  0001 C CNN "Hersteller Bestellnummer"
	1    9920 1470
	-1   0    0    1   
$EndComp
$Comp
L Polyfuse F4
U 1 1 58668BAD
P 5820 2920
F 0 "F4" V 5975 2920 50  0000 L CNN
F 1 "Polyfuse" V 5915 2775 50  0000 L CNN
F 2 "Zimprich:Polyfuse" H 5870 2720 50  0001 L CNN
F 3 "" H 5820 2920 50  0001 C CNN
F 4 "Value" H 5820 2920 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5820 2920 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5820 2920 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5820 2920 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5820 2920 60  0001 C CNN "Bauform"
F 9 "Value" H 5908 2829 60  0001 L CNN "Funktion"
F 10 "Value" H 5820 2920 60  0001 C CNN "Hersteller"
F 11 "Value" H 5820 2920 60  0001 C CNN "Hersteller Bestellnummer"
	1    5820 2920
	0    -1   -1   0   
$EndComp
$Comp
L Polyfuse F5
U 1 1 5866BC0E
P 7175 2920
F 0 "F5" V 7330 2920 50  0000 L CNN
F 1 "Polyfuse" V 7270 2775 50  0000 L CNN
F 2 "Zimprich:Polyfuse" H 7225 2720 50  0001 L CNN
F 3 "" H 7175 2920 50  0001 C CNN
F 4 "Value" H 7175 2920 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7175 2920 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7175 2920 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7175 2920 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7175 2920 60  0001 C CNN "Bauform"
F 9 "Value" H 7263 2829 60  0001 L CNN "Funktion"
F 10 "Value" H 7175 2920 60  0001 C CNN "Hersteller"
F 11 "Value" H 7175 2920 60  0001 C CNN "Hersteller Bestellnummer"
	1    7175 2920
	0    -1   -1   0   
$EndComp
$Comp
L Polyfuse F7
U 1 1 58671D23
P 8625 2920
F 0 "F7" V 8780 2920 50  0000 L CNN
F 1 "Polyfuse" V 8720 2775 50  0000 L CNN
F 2 "Zimprich:Polyfuse" H 8675 2720 50  0001 L CNN
F 3 "" H 8625 2920 50  0001 C CNN
F 4 "Value" H 8625 2920 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8625 2920 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8625 2920 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8625 2920 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8625 2920 60  0001 C CNN "Bauform"
F 9 "Value" H 8713 2829 60  0001 L CNN "Funktion"
F 10 "Value" H 8625 2920 60  0001 C CNN "Hersteller"
F 11 "Value" H 8625 2920 60  0001 C CNN "Hersteller Bestellnummer"
	1    8625 2920
	0    -1   -1   0   
$EndComp
$Comp
L Polyfuse F8
U 1 1 586794E5
P 13465 6420
F 0 "F8" V 13620 6420 50  0000 L CNN
F 1 "Polyfuse" V 13560 6275 50  0000 L CNN
F 2 "Zimprich:Polyfuse" H 13515 6220 50  0001 L CNN
F 3 "" H 13465 6420 50  0001 C CNN
F 4 "Value" H 13465 6420 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 13465 6420 60  0001 C CNN "Bestelllink"
F 6 "Value" H 13465 6420 60  0001 C CNN "Technische Daten"
F 7 "Value" H 13465 6420 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 13465 6420 60  0001 C CNN "Bauform"
F 9 "Value" H 13553 6329 60  0001 L CNN "Funktion"
F 10 "Value" H 13465 6420 60  0001 C CNN "Hersteller"
F 11 "Value" H 13465 6420 60  0001 C CNN "Hersteller Bestellnummer"
	1    13465 6420
	0    -1   -1   0   
$EndComp
$Comp
L Polyfuse F9
U 1 1 5867E323
P 3375 5970
F 0 "F9" V 3530 5970 50  0000 L CNN
F 1 "Polyfuse" V 3470 5825 50  0000 L CNN
F 2 "Zimprich:Polyfuse" H 3425 5770 50  0001 L CNN
F 3 "" H 3375 5970 50  0001 C CNN
F 4 "Value" H 3375 5970 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3375 5970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3375 5970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3375 5970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3375 5970 60  0001 C CNN "Bauform"
F 9 "Value" H 3463 5879 60  0001 L CNN "Funktion"
F 10 "Value" H 3375 5970 60  0001 C CNN "Hersteller"
F 11 "Value" H 3375 5970 60  0001 C CNN "Hersteller Bestellnummer"
	1    3375 5970
	0    -1   -1   0   
$EndComp
$Comp
L R R25
U 1 1 586442B7
P 4820 1835
F 0 "R25" H 4908 1881 50  0000 L CNN
F 1 "150" H 4908 1790 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 4908 1744 50  0001 L CNN
F 3 "" H 4820 1835 50  0000 C CNN
F 4 "Value" H 4820 1835 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4820 1835 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4820 1835 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4820 1835 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4820 1835 60  0001 C CNN "Bauform"
F 9 "Value" H 4908 1698 60  0001 L CNN "Funktion"
F 10 "Value" H 4820 1835 60  0001 C CNN "Hersteller"
F 11 "Value" H 4820 1835 60  0001 C CNN "Hersteller Bestellnummer"
	1    4820 1835
	1    0    0    -1  
$EndComp
$Comp
L R R27
U 1 1 58643B76
P 5870 1820
F 0 "R27" H 5958 1866 50  0000 L CNN
F 1 "2K2" H 5958 1775 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 5958 1729 50  0001 L CNN
F 3 "" H 5870 1820 50  0000 C CNN
F 4 "Value" H 5870 1820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5870 1820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5870 1820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5870 1820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5870 1820 60  0001 C CNN "Bauform"
F 9 "Value" H 5958 1683 60  0001 L CNN "Funktion"
F 10 "Value" H 5870 1820 60  0001 C CNN "Hersteller"
F 11 "Value" H 5870 1820 60  0001 C CNN "Hersteller Bestellnummer"
	1    5870 1820
	1    0    0    -1  
$EndComp
$Comp
L R R26
U 1 1 5864626C
P 5665 1470
F 0 "R26" V 5585 1400 50  0000 L CNN
F 1 "4K7" V 5745 1400 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 5753 1379 50  0001 L CNN
F 3 "" H 5665 1470 50  0000 C CNN
F 4 "Value" H 5665 1470 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5665 1470 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5665 1470 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5665 1470 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5665 1470 60  0001 C CNN "Bauform"
F 9 "Value" H 5753 1333 60  0001 L CNN "Funktion"
F 10 "Value" H 5665 1470 60  0001 C CNN "Hersteller"
F 11 "Value" H 5665 1470 60  0001 C CNN "Hersteller Bestellnummer"
	1    5665 1470
	0    1    -1   0   
$EndComp
$Comp
L R R28
U 1 1 58648504
P 7920 1835
F 0 "R28" H 8008 1881 50  0000 L CNN
F 1 "150" H 8008 1790 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 8008 1744 50  0001 L CNN
F 3 "" H 7920 1835 50  0000 C CNN
F 4 "Value" H 7920 1835 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7920 1835 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7920 1835 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7920 1835 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7920 1835 60  0001 C CNN "Bauform"
F 9 "Value" H 8008 1698 60  0001 L CNN "Funktion"
F 10 "Value" H 7920 1835 60  0001 C CNN "Hersteller"
F 11 "Value" H 7920 1835 60  0001 C CNN "Hersteller Bestellnummer"
	1    7920 1835
	1    0    0    -1  
$EndComp
$Comp
L R R30
U 1 1 5864B5E4
P 9070 1820
F 0 "R30" H 9158 1866 50  0000 L CNN
F 1 "2K2" H 9158 1775 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 9158 1729 50  0001 L CNN
F 3 "" H 9070 1820 50  0000 C CNN
F 4 "Value" H 9070 1820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 9070 1820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 9070 1820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 9070 1820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 9070 1820 60  0001 C CNN "Bauform"
F 9 "Value" H 9158 1683 60  0001 L CNN "Funktion"
F 10 "Value" H 9070 1820 60  0001 C CNN "Hersteller"
F 11 "Value" H 9070 1820 60  0001 C CNN "Hersteller Bestellnummer"
	1    9070 1820
	1    0    0    -1  
$EndComp
$Comp
L R R29
U 1 1 5864D479
P 8860 1470
F 0 "R29" V 8780 1400 50  0000 L CNN
F 1 "4K7" V 8940 1400 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 8948 1379 50  0001 L CNN
F 3 "" H 8860 1470 50  0000 C CNN
F 4 "Value" H 8860 1470 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8860 1470 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8860 1470 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8860 1470 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8860 1470 60  0001 C CNN "Bauform"
F 9 "Value" H 8948 1333 60  0001 L CNN "Funktion"
F 10 "Value" H 8860 1470 60  0001 C CNN "Hersteller"
F 11 "Value" H 8860 1470 60  0001 C CNN "Hersteller Bestellnummer"
	1    8860 1470
	0    1    -1   0   
$EndComp
$Comp
L R R31
U 1 1 5864FA4E
P 10220 1715
F 0 "R31" H 10308 1761 50  0000 L CNN
F 1 "470" H 10308 1670 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 10308 1624 50  0001 L CNN
F 3 "" H 10220 1715 50  0000 C CNN
F 4 "Value" H 10220 1715 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 10220 1715 60  0001 C CNN "Bestelllink"
F 6 "Value" H 10220 1715 60  0001 C CNN "Technische Daten"
F 7 "Value" H 10220 1715 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10220 1715 60  0001 C CNN "Bauform"
F 9 "Value" H 10308 1578 60  0001 L CNN "Funktion"
F 10 "Value" H 10220 1715 60  0001 C CNN "Hersteller"
F 11 "Value" H 10220 1715 60  0001 C CNN "Hersteller Bestellnummer"
	1    10220 1715
	1    0    0    1   
$EndComp
$Comp
L R R32
U 1 1 58651693
P 11420 1710
F 0 "R32" H 11508 1756 50  0000 L CNN
F 1 "470" H 11508 1665 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 11508 1619 50  0001 L CNN
F 3 "" H 11420 1710 50  0000 C CNN
F 4 "Value" H 11420 1710 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 11420 1710 60  0001 C CNN "Bestelllink"
F 6 "Value" H 11420 1710 60  0001 C CNN "Technische Daten"
F 7 "Value" H 11420 1710 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 11420 1710 60  0001 C CNN "Bauform"
F 9 "Value" H 11508 1573 60  0001 L CNN "Funktion"
F 10 "Value" H 11420 1710 60  0001 C CNN "Hersteller"
F 11 "Value" H 11420 1710 60  0001 C CNN "Hersteller Bestellnummer"
	1    11420 1710
	1    0    0    1   
$EndComp
$Comp
L R R8
U 1 1 58652FFD
P 13960 1720
F 0 "R8" V 13880 1650 50  0000 L CNN
F 1 "330" V 14040 1650 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14048 1629 50  0001 L CNN
F 3 "" H 13960 1720 50  0000 C CNN
F 4 "Value" H 13960 1720 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 13960 1720 60  0001 C CNN "Bestelllink"
F 6 "Value" H 13960 1720 60  0001 C CNN "Technische Daten"
F 7 "Value" H 13960 1720 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 13960 1720 60  0001 C CNN "Bauform"
F 9 "Value" H 14048 1583 60  0001 L CNN "Funktion"
F 10 "Value" H 13960 1720 60  0001 C CNN "Hersteller"
F 11 "Value" H 13960 1720 60  0001 C CNN "Hersteller Bestellnummer"
	1    13960 1720
	0    -1   -1   0   
$EndComp
$Comp
L R R24
U 1 1 5865573B
P 14115 3520
F 0 "R24" V 14035 3450 50  0000 L CNN
F 1 "330" V 14195 3450 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14203 3429 50  0001 L CNN
F 3 "" H 14115 3520 50  0000 C CNN
F 4 "Value" H 14115 3520 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14115 3520 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14115 3520 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14115 3520 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14115 3520 60  0001 C CNN "Bauform"
F 9 "Value" H 14203 3383 60  0001 L CNN "Funktion"
F 10 "Value" H 14115 3520 60  0001 C CNN "Hersteller"
F 11 "Value" H 14115 3520 60  0001 C CNN "Hersteller Bestellnummer"
	1    14115 3520
	0    1    1    0   
$EndComp
$Comp
L R R21
U 1 1 586581C2
P 14515 3320
F 0 "R21" V 14435 3250 50  0000 L CNN
F 1 "150" V 14595 3250 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14603 3229 50  0001 L CNN
F 3 "" H 14515 3320 50  0000 C CNN
F 4 "Value" H 14515 3320 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14515 3320 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14515 3320 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14515 3320 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14515 3320 60  0001 C CNN "Bauform"
F 9 "Value" H 14603 3183 60  0001 L CNN "Funktion"
F 10 "Value" H 14515 3320 60  0001 C CNN "Hersteller"
F 11 "Value" H 14515 3320 60  0001 C CNN "Hersteller Bestellnummer"
	1    14515 3320
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5865A855
P 14120 4220
F 0 "R1" V 14040 4150 50  0000 L CNN
F 1 "330" V 14200 4150 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14208 4129 50  0001 L CNN
F 3 "" H 14120 4220 50  0000 C CNN
F 4 "Value" H 14120 4220 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14120 4220 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14120 4220 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14120 4220 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14120 4220 60  0001 C CNN "Bauform"
F 9 "Value" H 14208 4083 60  0001 L CNN "Funktion"
F 10 "Value" H 14120 4220 60  0001 C CNN "Hersteller"
F 11 "Value" H 14120 4220 60  0001 C CNN "Hersteller Bestellnummer"
	1    14120 4220
	0    -1   1    0   
$EndComp
$Comp
L R R11
U 1 1 5865D417
P 14520 6720
F 0 "R11" V 14440 6650 50  0000 L CNN
F 1 "75" V 14600 6650 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14608 6629 50  0001 L CNN
F 3 "" H 14520 6720 50  0000 C CNN
F 4 "Value" H 14520 6720 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14520 6720 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14520 6720 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14520 6720 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14520 6720 60  0001 C CNN "Bauform"
F 9 "Value" H 14608 6583 60  0001 L CNN "Funktion"
F 10 "Value" H 14520 6720 60  0001 C CNN "Hersteller"
F 11 "Value" H 14520 6720 60  0001 C CNN "Hersteller Bestellnummer"
	1    14520 6720
	0    1    -1   0   
$EndComp
$Comp
L R R33
U 1 1 5866064B
P 14520 7020
F 0 "R33" V 14440 6950 50  0000 L CNN
F 1 "75" V 14600 6950 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14608 6929 50  0001 L CNN
F 3 "" H 14520 7020 50  0000 C CNN
F 4 "Value" H 14520 7020 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14520 7020 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14520 7020 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14520 7020 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14520 7020 60  0001 C CNN "Bauform"
F 9 "Value" H 14608 6883 60  0001 L CNN "Funktion"
F 10 "Value" H 14520 7020 60  0001 C CNN "Hersteller"
F 11 "Value" H 14520 7020 60  0001 C CNN "Hersteller Bestellnummer"
	1    14520 7020
	0    1    -1   0   
$EndComp
$Comp
L R R34
U 1 1 58662E81
P 14320 7520
F 0 "R34" V 14240 7450 50  0000 L CNN
F 1 "4K7" V 14400 7450 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14408 7429 50  0001 L CNN
F 3 "" H 14320 7520 50  0000 C CNN
F 4 "Value" H 14320 7520 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14320 7520 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14320 7520 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14320 7520 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14320 7520 60  0001 C CNN "Bauform"
F 9 "Value" H 14408 7383 60  0001 L CNN "Funktion"
F 10 "Value" H 14320 7520 60  0001 C CNN "Hersteller"
F 11 "Value" H 14320 7520 60  0001 C CNN "Hersteller Bestellnummer"
	1    14320 7520
	0    1    -1   0   
$EndComp
$Comp
L R R35
U 1 1 586652CE
P 14320 7820
F 0 "R35" V 14240 7750 50  0000 L CNN
F 1 "4K7" V 14400 7750 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 14408 7729 50  0001 L CNN
F 3 "" H 14320 7820 50  0000 C CNN
F 4 "Value" H 14320 7820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14320 7820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14320 7820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14320 7820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14320 7820 60  0001 C CNN "Bauform"
F 9 "Value" H 14408 7683 60  0001 L CNN "Funktion"
F 10 "Value" H 14320 7820 60  0001 C CNN "Hersteller"
F 11 "Value" H 14320 7820 60  0001 C CNN "Hersteller Bestellnummer"
	1    14320 7820
	0    1    -1   0   
$EndComp
$Comp
L R R20
U 1 1 58667E95
P 4540 3975
F 0 "R20" V 4460 3905 50  0000 L CNN
F 1 "4K7" V 4620 3905 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 4628 3884 50  0001 L CNN
F 3 "" H 4540 3975 50  0000 C CNN
F 4 "Value" H 4540 3975 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4540 3975 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4540 3975 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4540 3975 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4540 3975 60  0001 C CNN "Bauform"
F 9 "Value" H 4628 3838 60  0001 L CNN "Funktion"
F 10 "Value" H 4540 3975 60  0001 C CNN "Hersteller"
F 11 "Value" H 4540 3975 60  0001 C CNN "Hersteller Bestellnummer"
	1    4540 3975
	0    1    -1   0   
$EndComp
$Comp
L R R22
U 1 1 5866A671
P 4795 4415
F 0 "R22" H 4883 4461 50  0000 L CNN
F 1 "2K2" H 4883 4370 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 4883 4324 50  0001 L CNN
F 3 "" H 4795 4415 50  0000 C CNN
F 4 "Value" H 4795 4415 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4795 4415 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4795 4415 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4795 4415 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4795 4415 60  0001 C CNN "Bauform"
F 9 "Value" H 4883 4278 60  0001 L CNN "Funktion"
F 10 "Value" H 4795 4415 60  0001 C CNN "Hersteller"
F 11 "Value" H 4795 4415 60  0001 C CNN "Hersteller Bestellnummer"
	1    4795 4415
	1    0    0    -1  
$EndComp
$Comp
L R R36
U 1 1 5866E535
P 4020 5675
F 0 "R36" V 3940 5605 50  0000 L CNN
F 1 "4K7" V 4100 5605 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 4108 5584 50  0001 L CNN
F 3 "" H 4020 5675 50  0000 C CNN
F 4 "Value" H 4020 5675 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4020 5675 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4020 5675 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4020 5675 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4020 5675 60  0001 C CNN "Bauform"
F 9 "Value" H 4108 5538 60  0001 L CNN "Funktion"
F 10 "Value" H 4020 5675 60  0001 C CNN "Hersteller"
F 11 "Value" H 4020 5675 60  0001 C CNN "Hersteller Bestellnummer"
	1    4020 5675
	-1   0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 5867093B
P 4070 6970
F 0 "R16" V 3990 6900 50  0000 L CNN
F 1 "4K7" V 4150 6900 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 4158 6879 50  0001 L CNN
F 3 "" H 4070 6970 50  0000 C CNN
F 4 "Value" H 4070 6970 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4070 6970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4070 6970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4070 6970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4070 6970 60  0001 C CNN "Bauform"
F 9 "Value" H 4158 6833 60  0001 L CNN "Funktion"
F 10 "Value" H 4070 6970 60  0001 C CNN "Hersteller"
F 11 "Value" H 4070 6970 60  0001 C CNN "Hersteller Bestellnummer"
	1    4070 6970
	0    1    -1   0   
$EndComp
$Comp
L R R17
U 1 1 58673294
P 3470 7455
F 0 "R17" H 3550 7470 50  0000 L CNN
F 1 "2K2" H 3550 7385 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 3558 7364 50  0001 L CNN
F 3 "" H 3470 7455 50  0000 C CNN
F 4 "Value" H 3470 7455 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3470 7455 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3470 7455 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3470 7455 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3470 7455 60  0001 C CNN "Bauform"
F 9 "Value" H 3558 7318 60  0001 L CNN "Funktion"
F 10 "Value" H 3470 7455 60  0001 C CNN "Hersteller"
F 11 "Value" H 3470 7455 60  0001 C CNN "Hersteller Bestellnummer"
	1    3470 7455
	-1   0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 58676B16
P 3470 7965
F 0 "R19" H 3550 7980 50  0000 L CNN
F 1 "15" H 3550 7895 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 3558 7874 50  0001 L CNN
F 3 "" H 3470 7965 50  0000 C CNN
F 4 "Value" H 3470 7965 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 3470 7965 60  0001 C CNN "Bestelllink"
F 6 "Value" H 3470 7965 60  0001 C CNN "Technische Daten"
F 7 "Value" H 3470 7965 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 3470 7965 60  0001 C CNN "Bauform"
F 9 "Value" H 3558 7828 60  0001 L CNN "Funktion"
F 10 "Value" H 3470 7965 60  0001 C CNN "Hersteller"
F 11 "Value" H 3470 7965 60  0001 C CNN "Hersteller Bestellnummer"
	1    3470 7965
	-1   0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 5867983B
P 5970 6620
F 0 "R9" H 6050 6635 50  0000 L CNN
F 1 "2K2" H 6050 6550 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 6058 6529 50  0001 L CNN
F 3 "" H 5970 6620 50  0000 C CNN
F 4 "Value" H 5970 6620 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5970 6620 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5970 6620 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5970 6620 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5970 6620 60  0001 C CNN "Bauform"
F 9 "Value" H 6058 6483 60  0001 L CNN "Funktion"
F 10 "Value" H 5970 6620 60  0001 C CNN "Hersteller"
F 11 "Value" H 5970 6620 60  0001 C CNN "Hersteller Bestellnummer"
	1    5970 6620
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 5867BCDC
P 5620 5815
F 0 "R6" H 5700 5830 50  0000 L CNN
F 1 "1K" H 5700 5745 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 5708 5724 50  0001 L CNN
F 3 "" H 5620 5815 50  0000 C CNN
F 4 "Value" H 5620 5815 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5620 5815 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5620 5815 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5620 5815 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5620 5815 60  0001 C CNN "Bauform"
F 9 "Value" H 5708 5678 60  0001 L CNN "Funktion"
F 10 "Value" H 5620 5815 60  0001 C CNN "Hersteller"
F 11 "Value" H 5620 5815 60  0001 C CNN "Hersteller Bestellnummer"
	1    5620 5815
	-1   0    0    1   
$EndComp
$Comp
L R R5
U 1 1 5867DE86
P 7270 4575
F 0 "R5" H 7350 4590 50  0000 L CNN
F 1 "2K2" H 7350 4505 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 7358 4484 50  0001 L CNN
F 3 "" H 7270 4575 50  0000 C CNN
F 4 "Value" H 7270 4575 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7270 4575 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7270 4575 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7270 4575 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7270 4575 60  0001 C CNN "Bauform"
F 9 "Value" H 7358 4438 60  0001 L CNN "Funktion"
F 10 "Value" H 7270 4575 60  0001 C CNN "Hersteller"
F 11 "Value" H 7270 4575 60  0001 C CNN "Hersteller Bestellnummer"
	1    7270 4575
	-1   0    0    1   
$EndComp
$Comp
L R R10
U 1 1 5868056D
P 8470 4560
F 0 "R10" H 8550 4575 50  0000 L CNN
F 1 "2K2" H 8550 4490 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 8558 4469 50  0001 L CNN
F 3 "" H 8470 4560 50  0000 C CNN
F 4 "Value" H 8470 4560 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8470 4560 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8470 4560 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8470 4560 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8470 4560 60  0001 C CNN "Bauform"
F 9 "Value" H 8558 4423 60  0001 L CNN "Funktion"
F 10 "Value" H 8470 4560 60  0001 C CNN "Hersteller"
F 11 "Value" H 8470 4560 60  0001 C CNN "Hersteller Bestellnummer"
	1    8470 4560
	-1   0    0    1   
$EndComp
$Comp
L R R14
U 1 1 5868367B
P 8870 4270
F 0 "R14" V 9020 4210 50  0000 L CNN
F 1 "560" V 8950 4200 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 8958 4179 50  0001 L CNN
F 3 "" H 8870 4270 50  0000 C CNN
F 4 "Value" H 8870 4270 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8870 4270 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8870 4270 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8870 4270 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8870 4270 60  0001 C CNN "Bauform"
F 9 "Value" H 8958 4133 60  0001 L CNN "Funktion"
F 10 "Value" H 8870 4270 60  0001 C CNN "Hersteller"
F 11 "Value" H 8870 4270 60  0001 C CNN "Hersteller Bestellnummer"
	1    8870 4270
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 58687347
P 8270 5770
F 0 "R15" V 8415 5700 50  0000 L CNN
F 1 "2K2" V 8350 5700 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 8358 5679 50  0001 L CNN
F 3 "" H 8270 5770 50  0000 C CNN
F 4 "Value" H 8270 5770 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 8270 5770 60  0001 C CNN "Bestelllink"
F 6 "Value" H 8270 5770 60  0001 C CNN "Technische Daten"
F 7 "Value" H 8270 5770 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 8270 5770 60  0001 C CNN "Bauform"
F 9 "Value" H 8358 5633 60  0001 L CNN "Funktion"
F 10 "Value" H 8270 5770 60  0001 C CNN "Hersteller"
F 11 "Value" H 8270 5770 60  0001 C CNN "Hersteller Bestellnummer"
	1    8270 5770
	0    1    -1   0   
$EndComp
Wire Wire Line
	14110 1720 14170 1720
Wire Wire Line
	9010 1470 9070 1470
Wire Wire Line
	5815 1470 5870 1470
Wire Wire Line
	3170 5970 3225 5970
Wire Wire Line
	8420 2920 8475 2920
Wire Wire Line
	6970 2920 7025 2920
Wire Wire Line
	5620 2920 5670 2920
Wire Wire Line
	3770 6970 3920 6970
Wire Wire Line
	4255 3975 4390 3975
Wire Wire Line
	4545 3500 4545 3125
Connection ~ 3955 3500
Wire Wire Line
	3845 3500 4545 3500
Connection ~ 3955 4315
Wire Wire Line
	3755 4315 3955 4315
Connection ~ 3155 4315
Wire Wire Line
	3455 4315 3155 4315
Wire Wire Line
	8570 1470 8710 1470
Wire Wire Line
	5420 1470 5515 1470
Wire Wire Line
	3955 2975 3955 3100
Connection ~ 5870 9270
Connection ~ 6270 9270
Wire Wire Line
	5725 9270 7520 9270
Wire Wire Line
	2225 3880 2225 3905
Wire Wire Line
	4020 6345 4020 6270
Wire Wire Line
	15420 2270 15420 2720
Wire Wire Line
	11000 3970 11255 3970
Wire Wire Line
	1955 4930 2230 4930
Wire Wire Line
	1955 5130 2230 5130
Wire Wire Line
	1955 4830 2230 4830
Connection ~ 2070 5530
Connection ~ 2070 5030
Connection ~ 2070 4730
Connection ~ 2070 4330
Wire Wire Line
	2070 5730 1955 5730
Wire Wire Line
	2070 5530 1955 5530
Wire Wire Line
	2070 5030 1955 5030
Wire Wire Line
	2070 4730 1955 4730
Wire Wire Line
	2070 3880 2225 3880
Wire Wire Line
	2070 3880 2070 5730
Wire Wire Line
	1955 4330 2070 4330
Wire Wire Line
	1955 6030 2230 6030
Wire Wire Line
	1955 5930 2230 5930
Wire Wire Line
	1955 5830 2230 5830
Wire Wire Line
	1955 5630 2230 5630
Wire Wire Line
	1955 5430 2230 5430
Wire Wire Line
	1955 5330 2230 5330
Wire Wire Line
	1955 5230 2230 5230
Wire Wire Line
	1955 4630 2230 4630
Wire Wire Line
	1955 4530 2230 4530
Wire Wire Line
	1955 4430 2230 4430
Connection ~ 1970 4130
Wire Wire Line
	1970 4230 1970 4130
Wire Wire Line
	1955 4230 1970 4230
Wire Wire Line
	2225 4130 2225 4230
Wire Wire Line
	1955 4130 2225 4130
Wire Wire Line
	1455 4230 1105 4230
Wire Wire Line
	1455 4330 1105 4330
Wire Wire Line
	1455 5630 1105 5630
Wire Wire Line
	1455 5530 1105 5530
Wire Wire Line
	1455 5930 1105 5930
Wire Wire Line
	1455 5730 1105 5730
Connection ~ 1205 5330
Connection ~ 1205 6030
Wire Wire Line
	1205 4530 1455 4530
Wire Wire Line
	1205 5330 1455 5330
Wire Wire Line
	1205 6030 1455 6030
Wire Wire Line
	1205 4530 1205 6125
Wire Wire Line
	1455 4830 1105 4830
Wire Wire Line
	1455 5830 1105 5830
Wire Wire Line
	1455 5430 1105 5430
Wire Wire Line
	1455 5230 1105 5230
Wire Wire Line
	1455 5130 1105 5130
Wire Wire Line
	1455 5030 1105 5030
Wire Wire Line
	1455 4730 1105 4730
Wire Wire Line
	1455 4630 1105 4630
Wire Wire Line
	1455 4430 1105 4430
Connection ~ 1355 4130
Wire Wire Line
	1355 4930 1455 4930
Wire Wire Line
	1355 4130 1355 4930
Wire Wire Line
	655  4130 1455 4130
Wire Wire Line
	655  4225 655  4130
Wire Wire Line
	1955 2385 2230 2385
Wire Wire Line
	1955 2585 2230 2585
Wire Wire Line
	1955 2285 2230 2285
Connection ~ 2070 2985
Connection ~ 2070 2485
Connection ~ 2070 2185
Connection ~ 2070 1785
Wire Wire Line
	2070 3185 1955 3185
Wire Wire Line
	2070 2985 1955 2985
Wire Wire Line
	2070 2485 1955 2485
Wire Wire Line
	2070 2185 1955 2185
Wire Wire Line
	2070 1335 2225 1335
Wire Wire Line
	2070 1335 2070 3185
Wire Wire Line
	1955 1785 2070 1785
Wire Wire Line
	1955 3485 2230 3485
Wire Wire Line
	1955 3385 2230 3385
Wire Wire Line
	1955 3285 2230 3285
Wire Wire Line
	1955 3085 2230 3085
Wire Wire Line
	1955 2885 2230 2885
Wire Wire Line
	1955 2785 2230 2785
Wire Wire Line
	1955 2685 2230 2685
Wire Wire Line
	1955 2085 2230 2085
Wire Wire Line
	1955 1985 2230 1985
Wire Wire Line
	1955 1885 2230 1885
Connection ~ 1970 1585
Wire Wire Line
	1970 1685 1970 1585
Wire Wire Line
	1955 1685 1970 1685
Wire Wire Line
	2225 1585 2225 1610
Wire Wire Line
	1955 1585 2225 1585
Wire Wire Line
	1455 1685 1105 1685
Wire Wire Line
	1455 1785 1105 1785
Wire Wire Line
	1455 3085 1105 3085
Wire Wire Line
	1455 2985 1105 2985
Wire Wire Line
	1455 3385 1105 3385
Wire Wire Line
	1455 3185 1105 3185
Connection ~ 1205 2785
Connection ~ 1205 3485
Wire Wire Line
	1205 1985 1455 1985
Wire Wire Line
	1205 2785 1455 2785
Wire Wire Line
	1205 3485 1455 3485
Wire Wire Line
	1205 1985 1205 3580
Wire Wire Line
	1455 2285 1105 2285
Wire Wire Line
	1455 3285 1105 3285
Wire Wire Line
	1455 2885 1105 2885
Wire Wire Line
	1455 2685 1105 2685
Wire Wire Line
	1455 2585 1105 2585
Wire Wire Line
	1455 2485 1105 2485
Wire Wire Line
	1455 2185 1105 2185
Wire Wire Line
	1455 2085 1105 2085
Wire Wire Line
	1455 1885 1105 1885
Connection ~ 1355 1585
Wire Wire Line
	1355 2385 1455 2385
Wire Wire Line
	1355 1585 1355 2385
Wire Wire Line
	655  1585 1455 1585
Wire Wire Line
	3270 8670 3070 8670
Wire Wire Line
	2520 8670 2770 8670
Connection ~ 3070 7670
Wire Wire Line
	3070 7740 3070 7670
Connection ~ 10220 2020
Wire Wire Line
	10370 2020 10220 2020
Connection ~ 11420 2020
Wire Wire Line
	11570 2020 11420 2020
Wire Wire Line
	4270 7670 3970 7670
Connection ~ 3670 9270
Wire Wire Line
	3670 9170 3670 9270
Wire Wire Line
	4570 1470 4570 920 
Wire Wire Line
	7620 1470 7620 920 
Wire Wire Line
	10220 1020 10220 1220
Wire Wire Line
	11420 1220 11420 1020
Wire Wire Line
	10520 6370 10560 6370
Wire Wire Line
	8670 5270 8670 6670
Wire Wire Line
	8120 9385 8120 9120
Wire Wire Line
	8820 8755 8820 8670
Connection ~ 3270 8570
Wire Wire Line
	3320 8570 3270 8570
Wire Wire Line
	3720 8670 3670 8670
Wire Wire Line
	3720 8570 3720 8670
Wire Wire Line
	1520 7790 1520 7910
Wire Wire Line
	1520 7190 1520 7110
Wire Notes Line
	11520 3070 11770 3070
Wire Notes Line
	11520 3170 11770 3170
Wire Notes Line
	11520 3270 11770 3270
Wire Notes Line
	11520 3370 11770 3370
Wire Notes Line
	11520 3470 11770 3470
Wire Notes Line
	11520 3570 11770 3570
Wire Notes Line
	11520 3670 11770 3670
Wire Notes Line
	11520 3770 11770 3770
Wire Notes Line
	11520 3870 11770 3870
Wire Notes Line
	11520 3970 11770 3970
Wire Wire Line
	10750 4070 10750 3870
Wire Wire Line
	10750 3870 11255 3870
Wire Wire Line
	4445 3025 4445 3170
Wire Wire Line
	4595 3025 4445 3025
Connection ~ 3155 4725
Wire Wire Line
	3155 2975 3955 2975
Wire Wire Line
	3455 4725 3155 4725
Wire Wire Line
	3155 2975 3155 4825
Wire Wire Line
	7870 5770 8120 5770
Wire Wire Line
	7870 6020 7870 5770
Connection ~ 4820 6370
Wire Wire Line
	4820 6370 5020 6370
Wire Wire Line
	4820 5270 5970 5270
Wire Wire Line
	4820 5270 4820 6870
Connection ~ 7370 9270
Connection ~ 6870 9270
Wire Wire Line
	7370 8120 7550 8120
Wire Wire Line
	7520 9270 7520 8920
Wire Wire Line
	7370 8120 7370 9770
Wire Wire Line
	12025 3570 12520 3570
Wire Wire Line
	13670 1720 13810 1720
Wire Wire Line
	12025 3470 12520 3470
Wire Wire Line
	14420 1270 14520 1270
Wire Wire Line
	11255 3570 11020 3570
Connection ~ 7270 2120
Connection ~ 7620 2120
Wire Wire Line
	7920 2120 7920 1985
Wire Wire Line
	7620 2120 7620 1770
Wire Wire Line
	7120 2120 7920 2120
Wire Wire Line
	7270 2120 7270 1820
Connection ~ 4170 2120
Connection ~ 4570 2120
Wire Wire Line
	4820 2120 4820 1985
Wire Wire Line
	4570 2120 4570 1770
Wire Wire Line
	4020 2120 4820 2120
Wire Wire Line
	4170 2120 4170 1820
Connection ~ 9220 7320
Connection ~ 8820 8670
Connection ~ 8420 8670
Connection ~ 9220 8670
Wire Wire Line
	4470 7320 9420 7320
Wire Wire Line
	4470 6970 4470 7320
Wire Wire Line
	4220 6970 4470 6970
Wire Wire Line
	9220 7320 9220 8870
Wire Wire Line
	8120 8670 8120 8820
Wire Wire Line
	8120 8670 9220 8670
Wire Wire Line
	8420 8970 8420 8670
Wire Wire Line
	11255 3470 11020 3470
Connection ~ 5220 5470
Connection ~ 5620 5470
Wire Wire Line
	5220 5670 5220 5470
Wire Wire Line
	5620 4270 6270 4270
Wire Wire Line
	5620 4270 5620 5665
Wire Wire Line
	4670 5470 5970 5470
Wire Wire Line
	11255 3770 11020 3770
Connection ~ 6770 6370
Connection ~ 5970 6370
Connection ~ 9020 6370
Wire Wire Line
	6770 6670 6920 6670
Wire Wire Line
	6770 6370 6770 6670
Wire Wire Line
	9020 5870 9020 6670
Wire Wire Line
	9220 5870 9020 5870
Wire Wire Line
	5970 5770 5970 6470
Wire Wire Line
	5970 6370 9220 6370
Wire Wire Line
	11255 3670 11020 3670
Wire Wire Line
	4545 3125 4595 3125
Wire Wire Line
	3955 3300 3955 3775
Wire Wire Line
	15055 8805 14305 8805
Wire Wire Line
	13120 7270 13270 7270
Wire Wire Line
	13120 4670 13270 4670
Wire Wire Line
	13080 8830 12280 8830
Wire Wire Line
	14970 5370 15120 5370
Wire Wire Line
	13770 5370 13620 5370
Wire Wire Line
	13120 4770 13270 4770
Wire Wire Line
	14170 6720 14370 6720
Wire Wire Line
	13120 7370 13270 7370
Wire Wire Line
	15055 8905 14305 8905
Wire Wire Line
	11720 4970 11570 4970
Wire Wire Line
	11720 7570 11570 7570
Wire Wire Line
	13080 8930 12280 8930
Wire Wire Line
	14970 5270 15120 5270
Wire Wire Line
	13770 5270 13620 5270
Wire Wire Line
	11720 5070 11570 5070
Wire Wire Line
	14170 7020 14370 7020
Wire Wire Line
	11720 7670 11570 7670
Wire Wire Line
	7520 7670 7670 7670
Connection ~ 5870 7670
Wire Wire Line
	5870 7670 5870 8015
Wire Wire Line
	5770 7670 6070 7670
Connection ~ 9070 1470
Wire Wire Line
	9070 1070 8970 1070
Wire Wire Line
	9070 1070 9070 1670
Connection ~ 5870 1470
Wire Wire Line
	5870 1070 5770 1070
Wire Wire Line
	5870 1070 5870 1670
Wire Wire Line
	9020 4270 9270 4270
Connection ~ 3670 5970
Wire Wire Line
	3670 5470 4020 5470
Wire Wire Line
	3670 5970 3670 5470
Wire Wire Line
	3525 5970 4105 5970
Wire Wire Line
	14470 7820 14580 7820
Wire Wire Line
	14470 7520 14580 7520
Wire Wire Line
	10020 3270 11255 3270
Wire Wire Line
	10020 3370 11255 3370
Connection ~ 13770 7520
Connection ~ 13770 6420
Wire Wire Line
	13770 7520 14170 7520
Wire Wire Line
	13770 7820 14170 7820
Wire Wire Line
	13770 6420 13770 7820
Wire Wire Line
	14980 6820 15190 6820
Wire Wire Line
	14980 6420 14980 6820
Wire Wire Line
	13615 6420 14980 6420
Wire Wire Line
	10220 1520 10220 1565
Connection ~ 14980 7020
Wire Wire Line
	14980 7520 14980 7020
Wire Wire Line
	14670 7020 15190 7020
Wire Wire Line
	11420 1520 11420 1560
Connection ~ 10120 1120
Wire Wire Line
	11320 1120 11320 1020
Wire Wire Line
	10120 1120 10120 1020
Wire Wire Line
	9920 1120 11320 1120
Wire Wire Line
	9920 1120 9920 1320
Wire Wire Line
	8775 2920 8920 2920
Wire Wire Line
	5970 2920 6120 2920
Wire Wire Line
	7920 1420 7920 1685
Connection ~ 7620 920 
Connection ~ 7920 920 
Wire Wire Line
	7920 1120 7920 920 
Wire Wire Line
	8270 920  8270 1270
Wire Wire Line
	7270 920  8270 920 
Wire Wire Line
	7270 1420 7270 920 
Wire Wire Line
	6670 1120 6670 1020
Wire Wire Line
	6870 1120 6670 1120
Wire Wire Line
	6870 1920 6870 1120
Wire Wire Line
	6770 1920 6870 1920
Wire Wire Line
	6470 1120 6470 1020
Wire Wire Line
	6270 1120 6470 1120
Wire Wire Line
	6270 1920 6270 1120
Wire Wire Line
	6370 1920 6270 1920
Wire Wire Line
	7325 2920 7470 2920
Wire Wire Line
	3570 1120 3570 1020
Wire Wire Line
	3770 1120 3570 1120
Wire Wire Line
	3770 1870 3770 1120
Wire Wire Line
	3670 1870 3770 1870
Wire Wire Line
	3370 1120 3370 1020
Wire Wire Line
	3170 1120 3370 1120
Wire Wire Line
	3170 1870 3170 1120
Wire Wire Line
	3270 1870 3170 1870
Wire Wire Line
	6570 1620 6570 1020
Wire Wire Line
	4820 1420 4820 1685
Connection ~ 4820 920 
Connection ~ 4570 920 
Wire Wire Line
	4820 1120 4820 920 
Wire Wire Line
	4170 920  4170 1420
Wire Wire Line
	4170 920  5120 920 
Wire Wire Line
	5120 920  5120 1270
Wire Wire Line
	12025 3370 13270 3370
Wire Wire Line
	13270 2270 15420 2270
Wire Wire Line
	13270 3370 13270 2270
Wire Wire Line
	12025 3270 13120 3270
Wire Wire Line
	13120 2120 15020 2120
Wire Wire Line
	13120 3270 13120 2120
Wire Wire Line
	15020 2120 15020 2720
Wire Wire Line
	9620 8970 9670 8970
Wire Wire Line
	9620 9620 9620 8970
Wire Wire Line
	9770 9620 9620 9620
Wire Wire Line
	10070 9620 9970 9620
Wire Wire Line
	10070 8970 10070 9620
Wire Wire Line
	9870 9620 9870 9270
Wire Wire Line
	14265 3520 14670 3520
Wire Wire Line
	2070 9270 2225 9270
Wire Wire Line
	2070 8670 2220 8670
Wire Wire Line
	14665 3320 15020 3320
Wire Wire Line
	3470 7170 3470 7305
Connection ~ 3470 7670
Wire Wire Line
	3470 7605 3470 7815
Wire Wire Line
	2570 7670 3470 7670
Wire Wire Line
	2570 7670 2570 7810
Wire Wire Line
	3470 8115 3470 8270
Wire Wire Line
	13670 3320 14365 3320
Wire Wire Line
	13670 3670 13670 3320
Wire Wire Line
	12025 3670 13670 3670
Wire Wire Line
	7920 8620 7670 8620
Wire Wire Line
	5220 6170 5220 5970
Connection ~ 7070 7670
Wire Wire Line
	7070 7670 7070 8070
Wire Wire Line
	6870 7670 7220 7670
Connection ~ 8470 4270
Wire Wire Line
	8470 4270 8470 4410
Wire Wire Line
	8270 4270 8720 4270
Wire Wire Line
	3670 8670 3670 8870
Connection ~ 3070 8170
Wire Wire Line
	3070 8040 3070 8170
Wire Wire Line
	3270 8170 3270 8670
Wire Wire Line
	2570 8170 3270 8170
Connection ~ 7920 8120
Connection ~ 8670 7120
Wire Wire Line
	7920 8120 7920 8285
Wire Wire Line
	7850 8120 8670 8120
Wire Wire Line
	8670 8120 8670 6970
Wire Wire Line
	9020 7120 8670 7120
Wire Wire Line
	9020 7120 9020 6970
Connection ~ 8670 5770
Wire Wire Line
	8420 5770 8670 5770
Wire Wire Line
	8670 5270 8270 5270
Wire Wire Line
	3470 1570 3470 1020
Wire Wire Line
	13670 1370 13820 1370
Wire Wire Line
	13670 1520 13670 1370
Wire Wire Line
	14170 1520 13670 1520
Wire Wire Line
	14170 1720 14170 1520
Wire Wire Line
	6970 5270 7470 5270
Connection ~ 7270 4270
Wire Wire Line
	7270 4270 7270 4425
Wire Wire Line
	7070 4270 7470 4270
Connection ~ 10120 6370
Wire Wire Line
	10020 5870 10120 5870
Wire Wire Line
	10120 5870 10120 6520
Wire Wire Line
	10020 6370 10220 6370
Wire Wire Line
	13770 3520 13965 3520
Wire Wire Line
	13770 3770 13770 3520
Wire Wire Line
	12025 3770 13770 3770
Connection ~ 5370 7670
Wire Wire Line
	5370 8170 5370 7670
Wire Wire Line
	5125 7670 5470 7670
Connection ~ 2670 9270
Wire Wire Line
	2670 9770 2670 9270
Wire Wire Line
	3970 9770 2670 9770
Wire Wire Line
	3970 7670 3970 9770
Wire Wire Line
	2525 9270 2870 9270
Wire Wire Line
	4570 7670 4825 7670
Connection ~ 15090 6720
Wire Wire Line
	15090 7820 15090 6720
Wire Wire Line
	14980 7820 15090 7820
Wire Wire Line
	14670 6720 15190 6720
Wire Wire Line
	5170 9270 5425 9270
Wire Wire Line
	14270 4220 14520 4220
Wire Wire Line
	11420 2520 11570 2520
Wire Wire Line
	11420 1860 11420 2520
Wire Wire Line
	10220 2520 10370 2520
Wire Wire Line
	10220 1865 10220 2520
Connection ~ 4020 6270
Wire Wire Line
	3670 6270 4105 6270
Connection ~ 11170 5720
Wire Wire Line
	11170 5720 10770 5720
Wire Wire Line
	11170 5770 11170 5720
Connection ~ 11170 8270
Wire Wire Line
	11170 8270 11170 8320
Wire Wire Line
	10770 8270 11170 8270
Wire Wire Line
	14405 8605 15055 8605
Wire Wire Line
	14405 9055 14405 8605
Wire Wire Line
	12430 8630 13080 8630
Wire Wire Line
	12430 9080 12430 8630
Wire Wire Line
	14820 6920 15190 6920
Wire Wire Line
	11720 8220 11720 8070
Wire Wire Line
	11720 5620 11720 5470
Wire Wire Line
	11000 4070 11000 3970
Connection ~ 12020 2020
Wire Wire Line
	11870 2020 12020 2020
Wire Wire Line
	12020 1270 12020 2120
Wire Wire Line
	11520 1270 12020 1270
Wire Wire Line
	11520 1020 11520 1270
Connection ~ 10820 2020
Wire Wire Line
	10670 2020 10820 2020
Wire Wire Line
	10320 1270 10320 1020
Wire Wire Line
	10820 1270 10320 1270
Wire Wire Line
	10820 1270 10820 2120
Wire Wire Line
	8870 3020 8920 3020
Wire Wire Line
	8870 3120 8870 3020
Wire Wire Line
	7420 3020 7470 3020
Wire Wire Line
	7420 3120 7420 3020
Wire Wire Line
	6070 3020 6120 3020
Wire Wire Line
	6070 3120 6070 3020
Wire Wire Line
	15070 5770 14970 5770
Wire Wire Line
	15070 5920 15070 5770
Wire Wire Line
	13720 5770 13770 5770
Wire Wire Line
	13720 5920 13720 5770
Connection ~ 8270 2120
Wire Wire Line
	9070 1970 9070 2120
Wire Wire Line
	9070 2120 8270 2120
Wire Wire Line
	8270 1670 8270 2195
Connection ~ 5120 2120
Wire Wire Line
	5870 1970 5870 2120
Wire Wire Line
	5870 2120 5120 2120
Wire Wire Line
	5120 1670 5120 2180
Connection ~ 3955 4725
Wire Wire Line
	4795 4725 3755 4725
Wire Wire Line
	4795 4565 4795 4725
Wire Wire Line
	3955 4175 3955 4825
Wire Wire Line
	3020 6770 3470 6770
Wire Wire Line
	3020 6970 3020 6770
Connection ~ 2070 9570
Wire Wire Line
	4170 9570 2070 9570
Wire Wire Line
	2070 9370 2070 9770
Wire Wire Line
	2070 8770 2070 8870
Connection ~ 8820 9570
Connection ~ 9220 9570
Wire Wire Line
	8820 9055 8820 9570
Wire Wire Line
	8420 9270 8420 9570
Wire Wire Line
	9220 9270 9220 9770
Wire Wire Line
	8420 9570 9220 9570
Connection ~ 8920 4920
Connection ~ 8920 5120
Connection ~ 8920 5220
Wire Wire Line
	8920 4720 8920 5320
Wire Wire Line
	10120 6820 10120 6970
Connection ~ 5620 6370
Wire Wire Line
	5820 5670 5970 5670
Wire Wire Line
	5820 6370 5820 5670
Wire Wire Line
	5420 6370 5820 6370
Wire Wire Line
	5620 5965 5620 6870
Connection ~ 5370 8770
Wire Wire Line
	5870 8315 5870 8770
Wire Wire Line
	5870 8770 5370 8770
Wire Wire Line
	5370 8470 5370 8870
Connection ~ 6270 9570
Connection ~ 5870 9570
Connection ~ 6870 9570
Wire Wire Line
	6870 9570 6870 9770
Wire Wire Line
	5170 9570 6870 9570
Wire Wire Line
	13670 1270 13820 1270
Connection ~ 15570 4220
Connection ~ 15570 3870
Connection ~ 15570 3520
Wire Wire Line
	14820 4220 15570 4220
Wire Wire Line
	15570 4470 15420 4470
Wire Wire Line
	15320 3320 15570 3320
Wire Wire Line
	15570 3320 15570 4470
Wire Wire Line
	14970 3520 15570 3520
Wire Wire Line
	15570 3870 12025 3870
Wire Wire Line
	14420 1370 14520 1370
Connection ~ 13720 4220
Wire Wire Line
	13720 3970 13720 4220
Wire Wire Line
	13470 4220 13970 4220
Wire Wire Line
	12025 3970 13720 3970
Connection ~ 4795 3975
Wire Wire Line
	4690 3975 4895 3975
Wire Wire Line
	4795 3975 4795 4265
Connection ~ 4020 6070
Wire Wire Line
	3820 5670 3570 5670
Wire Wire Line
	3820 6070 3820 5670
Wire Wire Line
	3820 6070 4105 6070
Wire Wire Line
	4020 5825 4020 6070
Wire Wire Line
	12680 8730 13080 8730
Wire Wire Line
	15320 5570 15320 5920
Wire Wire Line
	13420 5570 13770 5570
Wire Wire Line
	13420 5920 13420 5570
Connection ~ 11170 7070
Wire Wire Line
	11170 7970 11170 7070
Wire Wire Line
	11620 7070 11620 7370
Wire Wire Line
	10970 7070 11620 7070
Wire Wire Line
	10970 7320 10970 7070
Connection ~ 11170 4520
Wire Wire Line
	11170 5420 11170 4520
Wire Wire Line
	10970 4670 10970 4520
Wire Wire Line
	10970 4520 11620 4520
Wire Wire Line
	11620 4520 11620 4770
Wire Wire Line
	11620 4770 11720 4770
Wire Wire Line
	9920 1620 9920 2120
Wire Wire Line
	8420 3120 8420 2920
Wire Wire Line
	6970 3120 6970 2920
Wire Wire Line
	5620 3120 5620 2920
Connection ~ 7920 9385
Wire Wire Line
	7920 9385 8120 9385
Wire Wire Line
	7920 8920 7920 9770
Wire Wire Line
	3170 6270 3170 5970
Wire Wire Line
	14655 8705 15055 8705
Wire Wire Line
	14655 9055 14655 8705
Connection ~ 10770 6970
Wire Wire Line
	10770 7970 10770 6970
Wire Wire Line
	10570 6970 11720 6970
Connection ~ 10770 4420
Wire Wire Line
	10770 5420 10770 4420
Wire Wire Line
	11720 4420 11720 4670
Wire Wire Line
	10570 4420 11720 4420
Wire Wire Line
	4020 5470 4020 5525
$Comp
L R R7
U 1 1 5868A3B7
P 10120 6670
F 0 "R7" H 10200 6685 50  0000 L CNN
F 1 "1K" H 10200 6600 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 10208 6579 50  0001 L CNN
F 3 "" H 10120 6670 50  0000 C CNN
F 4 "Value" H 10120 6670 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 10120 6670 60  0001 C CNN "Bestelllink"
F 6 "Value" H 10120 6670 60  0001 C CNN "Technische Daten"
F 7 "Value" H 10120 6670 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 10120 6670 60  0001 C CNN "Bauform"
F 9 "Value" H 10208 6533 60  0001 L CNN "Funktion"
F 10 "Value" H 10120 6670 60  0001 C CNN "Hersteller"
F 11 "Value" H 10120 6670 60  0001 C CNN "Hersteller Bestellnummer"
	1    10120 6670
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 5868DEC3
P 4975 7670
F 0 "R3" V 4895 7600 50  0000 L CNN
F 1 "3K3" V 5055 7600 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 5063 7579 50  0001 L CNN
F 3 "" H 4975 7670 50  0000 C CNN
F 4 "Value" H 4975 7670 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4975 7670 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4975 7670 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4975 7670 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4975 7670 60  0001 C CNN "Bauform"
F 9 "Value" H 5063 7533 60  0001 L CNN "Funktion"
F 10 "Value" H 4975 7670 60  0001 C CNN "Hersteller"
F 11 "Value" H 4975 7670 60  0001 C CNN "Hersteller Bestellnummer"
	1    4975 7670
	0    1    -1   0   
$EndComp
$Comp
L R R13
U 1 1 58690373
P 7370 7670
F 0 "R13" V 7290 7600 50  0000 L CNN
F 1 "560" V 7450 7600 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 7458 7579 50  0001 L CNN
F 3 "" H 7370 7670 50  0000 C CNN
F 4 "Value" H 7370 7670 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7370 7670 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7370 7670 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7370 7670 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7370 7670 60  0001 C CNN "Bauform"
F 9 "Value" H 7458 7533 60  0001 L CNN "Funktion"
F 10 "Value" H 7370 7670 60  0001 C CNN "Hersteller"
F 11 "Value" H 7370 7670 60  0001 C CNN "Hersteller Bestellnummer"
	1    7370 7670
	0    -1   1    0   
$EndComp
$Comp
L R R18
U 1 1 58693EA1
P 2570 7960
F 0 "R18" H 2650 7975 50  0000 L CNN
F 1 "10K" H 2650 7890 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 2658 7869 50  0001 L CNN
F 3 "" H 2570 7960 50  0000 C CNN
F 4 "Value" H 2570 7960 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2570 7960 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2570 7960 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2570 7960 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2570 7960 60  0001 C CNN "Bauform"
F 9 "Value" H 2658 7823 60  0001 L CNN "Funktion"
F 10 "Value" H 2570 7960 60  0001 C CNN "Hersteller"
F 11 "Value" H 2570 7960 60  0001 C CNN "Hersteller Bestellnummer"
	1    2570 7960
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2570 8110 2570 8170
$Comp
L R R2
U 1 1 586969AE
P 5870 8165
F 0 "R2" H 5950 8180 50  0000 L CNN
F 1 "4K7" H 5950 8095 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 5958 8074 50  0001 L CNN
F 3 "" H 5870 8165 50  0000 C CNN
F 4 "Value" H 5870 8165 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5870 8165 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5870 8165 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5870 8165 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5870 8165 60  0001 C CNN "Bauform"
F 9 "Value" H 5958 8028 60  0001 L CNN "Funktion"
F 10 "Value" H 5870 8165 60  0001 C CNN "Hersteller"
F 11 "Value" H 5870 8165 60  0001 C CNN "Hersteller Bestellnummer"
	1    5870 8165
	1    0    0    1   
$EndComp
$Comp
L R R4
U 1 1 58698991
P 7070 8220
F 0 "R4" H 7150 8235 50  0000 L CNN
F 1 "2K2" H 7150 8150 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 7158 8129 50  0001 L CNN
F 3 "" H 7070 8220 50  0000 C CNN
F 4 "Value" H 7070 8220 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7070 8220 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7070 8220 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7070 8220 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7070 8220 60  0001 C CNN "Bauform"
F 9 "Value" H 7158 8083 60  0001 L CNN "Funktion"
F 10 "Value" H 7070 8220 60  0001 C CNN "Hersteller"
F 11 "Value" H 7070 8220 60  0001 C CNN "Hersteller Bestellnummer"
	1    7070 8220
	-1   0    0    1   
$EndComp
$Comp
L R R23
U 1 1 5869B6C2
P 7920 8435
F 0 "R23" H 8000 8450 50  0000 L CNN
F 1 "15" H 8000 8365 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 8008 8344 50  0001 L CNN
F 3 "" H 7920 8435 50  0000 C CNN
F 4 "Value" H 7920 8435 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7920 8435 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7920 8435 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7920 8435 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7920 8435 60  0001 C CNN "Bauform"
F 9 "Value" H 8008 8298 60  0001 L CNN "Funktion"
F 10 "Value" H 7920 8435 60  0001 C CNN "Hersteller"
F 11 "Value" H 7920 8435 60  0001 C CNN "Hersteller Bestellnummer"
	1    7920 8435
	-1   0    0    1   
$EndComp
Wire Wire Line
	7920 8620 7920 8585
$Comp
L R R12
U 1 1 5869EF44
P 7700 8120
F 0 "R12" V 7845 8060 50  0000 L CNN
F 1 "10K" V 7780 8050 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 7788 8029 50  0001 L CNN
F 3 "" H 7700 8120 50  0000 C CNN
F 4 "Value" H 7700 8120 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7700 8120 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7700 8120 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7700 8120 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7700 8120 60  0001 C CNN "Bauform"
F 9 "Value" H 7788 7983 60  0001 L CNN "Funktion"
F 10 "Value" H 7700 8120 60  0001 C CNN "Hersteller"
F 11 "Value" H 7700 8120 60  0001 C CNN "Hersteller Bestellnummer"
	1    7700 8120
	0    -1   -1   0   
$EndComp
$Comp
L DC-DC-XL1450 DC-DC1
U 1 1 586A38C4
P 4670 9670
F 0 "DC-DC1" H 4670 10324 45  0000 C CNN
F 1 "DC-DC-XL1450" H 4670 10240 45  0000 C CNN
F 2 "Zimprich:DCDC-XL1450_Bohrlöcher_und_Rahmen" H 4700 9820 20  0001 C CNN
F 3 "" H 4670 9670 60  0001 C CNN
F 4 "Value" H 4670 9670 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 4670 9670 60  0001 C CNN "Bestelllink"
F 6 "Value" H 4670 9670 60  0001 C CNN "Technische Daten"
F 7 "Value" H 4670 9670 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 4670 9670 60  0001 C CNN "Bauform"
F 9 "Value" H 4670 10251 60  0001 C CNN "Funktion"
F 10 "Value" H 4670 9670 60  0001 C CNN "Hersteller"
F 11 "Value" H 4670 9670 60  0001 C CNN "Hersteller Bestellnummer"
	1    4670 9670
	1    0    0    -1  
$EndComp
$Comp
L SJ2W SJ1
U 1 1 586A6BBF
P 5220 6370
F 0 "SJ1" V 5385 6340 45  0000 L CNN
F 1 "SJ2W" V 5315 6305 45  0000 L CNN
F 2 "Zimprich:SJ_2W" H 5250 6520 20  0001 C CNN
F 3 "" H 5220 6370 60  0001 C CNN
F 4 "Value" H 5220 6370 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5220 6370 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5220 6370 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5220 6370 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5220 6370 60  0001 C CNN "Bauform"
F 9 "Value" H 5220 6370 60  0001 C CNN "Funktion"
F 10 "Value" H 5220 6370 60  0001 C CNN "Hersteller"
F 11 "Value" H 5220 6370 60  0001 C CNN "Hersteller Bestellnummer"
	1    5220 6370
	0    1    1    0   
$EndComp
$Comp
L SJW SJ3
U 1 1 586A9CA4
P 14780 7820
F 0 "SJ3" H 14780 7999 45  0000 C CNN
F 1 "SJW" H 14780 7915 45  0000 C CNN
F 2 "Zimprich:SJ" H 14810 7970 20  0001 C CNN
F 3 "" H 14780 7820 60  0001 C CNN
F 4 "Value" H 14780 7820 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14780 7820 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14780 7820 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14780 7820 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14780 7820 60  0001 C CNN "Bauform"
F 9 "Value" H 14780 7926 60  0001 C CNN "Funktion"
F 10 "Value" H 14780 7820 60  0001 C CNN "Hersteller"
F 11 "Value" H 14780 7820 60  0001 C CNN "Hersteller Bestellnummer"
	1    14780 7820
	1    0    0    -1  
$EndComp
$Comp
L SJW SJ2
U 1 1 586AB0C8
P 14780 7520
F 0 "SJ2" H 14780 7699 45  0000 C CNN
F 1 "SJW" H 14780 7615 45  0000 C CNN
F 2 "Zimprich:SJ" H 14810 7670 20  0001 C CNN
F 3 "" H 14780 7520 60  0001 C CNN
F 4 "Value" H 14780 7520 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 14780 7520 60  0001 C CNN "Bestelllink"
F 6 "Value" H 14780 7520 60  0001 C CNN "Technische Daten"
F 7 "Value" H 14780 7520 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 14780 7520 60  0001 C CNN "Bauform"
F 9 "Value" H 14780 7626 60  0001 C CNN "Funktion"
F 10 "Value" H 14780 7520 60  0001 C CNN "Hersteller"
F 11 "Value" H 14780 7520 60  0001 C CNN "Hersteller Bestellnummer"
	1    14780 7520
	1    0    0    -1  
$EndComp
$Comp
L Fuse F2
U 1 1 58646538
P 2375 9270
F 0 "F2" V 2230 9285 50  0000 L CNN
F 1 "1A/T" V 2300 9200 50  0000 L CNN
F 2 "Zimprich:Sicherungs_Sockel_für_TR5_TE5" V 2305 9270 50  0001 C CNN
F 3 "" H 2375 9270 50  0000 C CNN
F 4 "Value" H 2375 9270 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2375 9270 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2375 9270 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2375 9270 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2375 9270 60  0001 C CNN "Bauform"
F 9 "Value" H 2375 9270 60  0001 C CNN "Funktion"
F 10 "Value" H 2375 9270 60  0001 C CNN "Hersteller"
F 11 "Value" H 2375 9270 60  0001 C CNN "Hersteller Bestellnummer"
	1    2375 9270
	0    -1   1    0   
$EndComp
$Comp
L Fuse F3
U 1 1 5864B245
P 2370 8670
F 0 "F3" V 2225 8685 50  0000 L CNN
F 1 "1A/T" V 2295 8600 50  0000 L CNN
F 2 "Zimprich:Sicherungs_Sockel_für_TR5_TE5" V 2300 8670 50  0001 C CNN
F 3 "" H 2370 8670 50  0000 C CNN
F 4 "Value" H 2370 8670 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 2370 8670 60  0001 C CNN "Bestelllink"
F 6 "Value" H 2370 8670 60  0001 C CNN "Technische Daten"
F 7 "Value" H 2370 8670 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 2370 8670 60  0001 C CNN "Bauform"
F 9 "Value" H 2370 8670 60  0001 C CNN "Funktion"
F 10 "Value" H 2370 8670 60  0001 C CNN "Hersteller"
F 11 "Value" H 2370 8670 60  0001 C CNN "Hersteller Bestellnummer"
	1    2370 8670
	0    -1   1    0   
$EndComp
$Comp
L Fuse F1
U 1 1 5864597F
P 5575 9270
F 0 "F1" V 5430 9285 50  0000 L CNN
F 1 "2A/T" V 5500 9200 50  0000 L CNN
F 2 "Zimprich:Sicherungs_Sockel_für_TR5_TE5" V 5505 9270 50  0001 C CNN
F 3 "" H 5575 9270 50  0000 C CNN
F 4 "Value" H 5575 9270 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5575 9270 60  0001 C CNN "Bestelllink"
F 6 "Value" H 5575 9270 60  0001 C CNN "Technische Daten"
F 7 "Value" H 5575 9270 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 5575 9270 60  0001 C CNN "Bauform"
F 9 "Value" H 5575 9270 60  0001 C CNN "Funktion"
F 10 "Value" H 5575 9270 60  0001 C CNN "Hersteller"
F 11 "Value" H 5575 9270 60  0001 C CNN "Hersteller Bestellnummer"
	1    5575 9270
	0    -1   1    0   
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H7
U 1 1 58656088
P 1420 10660
F 0 "H7" H 1530 10682 70  0000 L BNN
F 1 "Raspberry_Pi_B_Bohrschablone" H 1530 10563 70  0000 L BNN
F 2 "Zimprich:Raspberry_Pi_B_Bohrschablone_Rueckseite" H 1410 10450 65  0001 L TNN
F 3 "" H 1420 10660 60  0001 C CNN
F 4 "Value" H 1420 10660 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 1420 10660 60  0001 C CNN "Bestelllink"
F 6 "Value" H 1420 10660 60  0001 C CNN "Technische Daten"
F 7 "Value" H 1420 10660 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 1420 10660 60  0001 C CNN "Bauform"
F 9 "Value" H 1420 10660 60  0001 C CNN "Funktion"
F 10 "Value" H 1420 10660 60  0001 C CNN "Hersteller"
F 11 "Value" H 1420 10660 60  0001 C CNN "Hersteller Bestellnummer"
	1    1420 10660
	1    0    0    -1  
$EndComp
Wire Wire Line
	1060 7800 1060 7920
Wire Wire Line
	14820 6920 14820 7070
Wire Wire Line
	3170 9270 4170 9270
NoConn ~ 11720 7870
NoConn ~ 11720 5270
NoConn ~ 13770 4970
NoConn ~ 14970 5070
NoConn ~ 14970 4970
NoConn ~ 11255 3170
NoConn ~ 11255 3070
NoConn ~ 12025 3070
NoConn ~ 12025 3170
Wire Wire Line
	10570 7320 10570 6970
NoConn ~ 6970 5770
NoConn ~ 9920 4720
NoConn ~ 9920 5220
Wire Wire Line
	5970 6870 5970 6770
NoConn ~ 14970 5870
NoConn ~ 4105 6170
$Comp
L +3V3 #PWR063
U 1 1 5867DEBA
P 14655 9055
F 0 "#PWR063" H 14655 8905 50  0001 C CNN
F 1 "+3V3" H 14670 9228 50  0000 C CNN
F 2 "" H 14655 9055 50  0000 C CNN
F 3 "" H 14655 9055 50  0000 C CNN
	1    14655 9055
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR064
U 1 1 58671ABD
P 12680 9080
F 0 "#PWR064" H 12680 8930 50  0001 C CNN
F 1 "+5V" H 12695 9253 50  0000 C CNN
F 2 "" H 12680 9080 50  0000 C CNN
F 3 "" H 12680 9080 50  0000 C CNN
	1    12680 9080
	1    0    0    1   
$EndComp
Wire Wire Line
	12680 9080 12680 8730
$Comp
L CONN_01X02 J4
U 1 1 5861CAF1
P 7670 2970
F 0 "J4" H 7748 3011 50  0000 L CNN
F 1 "CONN_01X02" H 7748 2920 50  0000 L CNN
F 2 "Zimprich:Anschlussklemme_2P_RM2,54_RM5,08" H 7748 2927 50  0001 L CNN
F 3 "" H 7670 2970 50  0000 C CNN
F 4 "Value" H 7670 2970 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7670 2970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7670 2970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7670 2970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7670 2970 60  0001 C CNN "Bauform"
F 9 "Value" H 7748 2874 60  0001 L CNN "Funktion"
F 10 "Value" H 7670 2970 60  0001 C CNN "Hersteller"
F 11 "Value" H 7670 2970 60  0001 C CNN "Hersteller Bestellnummer"
	1    7670 2970
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J3
U 1 1 5864A36F
P 6320 2970
F 0 "J3" H 6398 3011 50  0000 L CNN
F 1 "CONN_01X02" H 6398 2920 50  0000 L CNN
F 2 "Zimprich:Anschlussklemme_2P_RM2,54_RM5,08" H 6398 2927 50  0001 L CNN
F 3 "" H 6320 2970 50  0000 C CNN
F 4 "Value" H 6320 2970 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 6320 2970 60  0001 C CNN "Bestelllink"
F 6 "Value" H 6320 2970 60  0001 C CNN "Technische Daten"
F 7 "Value" H 6320 2970 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 6320 2970 60  0001 C CNN "Bauform"
F 9 "Value" H 6398 2874 60  0001 L CNN "Funktion"
F 10 "Value" H 6320 2970 60  0001 C CNN "Hersteller"
F 11 "Value" H 6320 2970 60  0001 C CNN "Hersteller Bestellnummer"
	1    6320 2970
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR065
U 1 1 58646272
P 11720 5620
F 0 "#PWR065" H 11720 5370 50  0001 C CNN
F 1 "GND" H 11725 5447 50  0000 C CNN
F 2 "" H 11720 5620 50  0000 C CNN
F 3 "" H 11720 5620 50  0000 C CNN
	1    11720 5620
	1    0    0    -1  
$EndComp
Wire Wire Line
	14970 5570 15320 5570
Wire Wire Line
	11620 7370 11720 7370
Wire Wire Line
	11720 6970 11720 7270
Wire Wire Line
	7270 4725 7270 4870
Wire Wire Line
	1060 7200 1060 7105
Wire Wire Line
	13315 6420 13220 6420
Wire Wire Line
	13220 6420 13220 6520
Wire Wire Line
	655  1680 655  1585
Wire Wire Line
	7070 8370 7070 8870
Wire Wire Line
	8470 4710 8470 4870
Wire Wire Line
	10570 4420 10570 4670
$Comp
L D D3
U 1 1 586AF0CA
P 2920 8670
F 0 "D3" H 2890 8810 39  0000 L CNN
F 1 "1N4004" H 2810 8760 39  0000 L CNN
F 2 "Diodes_SMD:DO-214AB" H 2920 8795 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A400/S1DSMD_S1GSMD_S1JSMD_S1MSMD_TSC.pdf" H 2920 8670 50  0001 C CNN
F 4 "DO-214AC/SMA" H 2920 8670 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SB-SKE-4F-Dioden/S-1G-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=95354&GROUPID=2991&artnr=S+1G+SMD&SEARCH=1N4004" H 2920 8670 60  0001 C CNN "Bestelllink"
F 6 "Si-Gleichrichterdiode, DO214AC, 400V, 1A" H 2920 8670 60  0001 C CNN "Technische Daten"
F 7 "R: S 1G SMD" H 2920 8670 60  0001 C CNN "Bestellnummer"
F 8 "DO-214AC" H 2920 8670 60  0001 C CNN "Bauform"
F 9 "Value" H 2920 8670 60  0001 C CNN "Funktion"
F 10 "Value" H 2920 8670 60  0001 C CNN "Hersteller"
F 11 "Value" H 2920 8670 60  0001 C CNN "Hersteller Bestellnummer"
	1    2920 8670
	-1   0    0    -1  
$EndComp
$Comp
L D D4
U 1 1 586B0530
P 3670 9020
F 0 "D4" V 3695 9095 39  0000 L CNN
F 1 "1N4004" V 3640 9065 39  0000 L CNN
F 2 "Diodes_SMD:DO-214AB" H 3670 9145 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A400/S1DSMD_S1GSMD_S1JSMD_S1MSMD_TSC.pdf" H 3670 9020 50  0001 C CNN
F 4 "DO-214AC/SMA" H 3670 9020 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SB-SKE-4F-Dioden/S-1G-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=95354&GROUPID=2991&artnr=S+1G+SMD&SEARCH=1N4004" H 3670 9020 60  0001 C CNN "Bestelllink"
F 6 "Si-Gleichrichterdiode, DO214AC, 400V, 1A" H 3670 9020 60  0001 C CNN "Technische Daten"
F 7 "R: S 1G SMD" H 3670 9020 60  0001 C CNN "Bestellnummer"
F 8 "DO-214AC" H 3670 9020 60  0001 C CNN "Bauform"
F 9 "Value" H 3670 9020 60  0001 C CNN "Funktion"
F 10 "Value" H 3670 9020 60  0001 C CNN "Hersteller"
F 11 "Value" H 3670 9020 60  0001 C CNN "Hersteller Bestellnummer"
	1    3670 9020
	0    1    -1   0   
$EndComp
$Comp
L D D2
U 1 1 586B36C6
P 4420 7670
F 0 "D2" H 4390 7810 39  0000 L CNN
F 1 "1N4004" H 4310 7760 39  0000 L CNN
F 2 "Diodes_SMD:DO-214AB" H 4420 7795 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A400/S1DSMD_S1GSMD_S1JSMD_S1MSMD_TSC.pdf" H 4420 7670 50  0001 C CNN
F 4 "DO-214AC/SMA" H 4420 7670 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SB-SKE-4F-Dioden/S-1G-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=95354&GROUPID=2991&artnr=S+1G+SMD&SEARCH=1N4004" H 4420 7670 60  0001 C CNN "Bestelllink"
F 6 "Si-Gleichrichterdiode, DO214AC, 400V, 1A" H 4420 7670 60  0001 C CNN "Technische Daten"
F 7 "R: S 1G SMD" H 4420 7670 60  0001 C CNN "Bestellnummer"
F 8 "DO-214AC" H 4420 7670 60  0001 C CNN "Bauform"
F 9 "Value" H 4420 7670 60  0001 C CNN "Funktion"
F 10 "Value" H 4420 7670 60  0001 C CNN "Hersteller"
F 11 "Value" H 4420 7670 60  0001 C CNN "Hersteller Bestellnummer"
	1    4420 7670
	-1   0    0    -1  
$EndComp
$Comp
L D D18
U 1 1 586B724B
P 10220 1370
F 0 "D18" V 10258 1449 39  0000 L CNN
F 1 "1N4148" V 10183 1449 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 10220 1495 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 10220 1370 50  0001 C CNN
F 4 "MiniMELF" H 10220 1370 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 10220 1370 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 10220 1370 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 10220 1370 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 10220 1370 60  0001 C CNN "Bauform"
F 9 "Value" H 10220 1370 60  0001 C CNN "Funktion"
F 10 "Value" H 10220 1370 60  0001 C CNN "Hersteller"
F 11 "Value" H 10220 1370 60  0001 C CNN "Hersteller Bestellnummer"
	1    10220 1370
	0    1    -1   0   
$EndComp
$Comp
L D D14
U 1 1 586B8A40
P 7620 1620
F 0 "D14" V 7658 1699 39  0000 L CNN
F 1 "1N4148" V 7583 1699 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 7620 1745 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 7620 1620 50  0001 C CNN
F 4 "MiniMELF" H 7620 1620 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 7620 1620 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 7620 1620 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 7620 1620 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 7620 1620 60  0001 C CNN "Bauform"
F 9 "Value" H 7620 1620 60  0001 C CNN "Funktion"
F 10 "Value" H 7620 1620 60  0001 C CNN "Hersteller"
F 11 "Value" H 7620 1620 60  0001 C CNN "Hersteller Bestellnummer"
	1    7620 1620
	0    1    -1   0   
$EndComp
$Comp
L D D13
U 1 1 586BA8FA
P 4570 1620
F 0 "D13" V 4608 1699 39  0000 L CNN
F 1 "1N4148" V 4533 1699 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 4570 1745 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 4570 1620 50  0001 C CNN
F 4 "MiniMELF" H 4570 1620 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 4570 1620 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 4570 1620 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 4570 1620 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 4570 1620 60  0001 C CNN "Bauform"
F 9 "Value" H 4570 1620 60  0001 C CNN "Funktion"
F 10 "Value" H 4570 1620 60  0001 C CNN "Hersteller"
F 11 "Value" H 4570 1620 60  0001 C CNN "Hersteller Bestellnummer"
	1    4570 1620
	0    1    -1   0   
$EndComp
$Comp
L D D7
U 1 1 586BD7BE
P 8670 6820
F 0 "D7" V 8708 6899 39  0000 L CNN
F 1 "1N4148" V 8633 6899 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 8670 6945 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 8670 6820 50  0001 C CNN
F 4 "MiniMELF" H 8670 6820 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 8670 6820 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 8670 6820 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 8670 6820 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 8670 6820 60  0001 C CNN "Bauform"
F 9 "Value" H 8670 6820 60  0001 C CNN "Funktion"
F 10 "Value" H 8670 6820 60  0001 C CNN "Hersteller"
F 11 "Value" H 8670 6820 60  0001 C CNN "Hersteller Bestellnummer"
	1    8670 6820
	0    1    1    0   
$EndComp
$Comp
L D D8
U 1 1 586BDF08
P 9020 6820
F 0 "D8" V 9058 6899 39  0000 L CNN
F 1 "1N4148" V 8983 6899 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 9020 6945 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 9020 6820 50  0001 C CNN
F 4 "MiniMELF" H 9020 6820 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 9020 6820 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 9020 6820 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 9020 6820 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 9020 6820 60  0001 C CNN "Bauform"
F 9 "Value" H 9020 6820 60  0001 C CNN "Funktion"
F 10 "Value" H 9020 6820 60  0001 C CNN "Hersteller"
F 11 "Value" H 9020 6820 60  0001 C CNN "Hersteller Bestellnummer"
	1    9020 6820
	0    1    1    0   
$EndComp
$Comp
L D D9
U 1 1 586C0453
P 8820 8905
F 0 "D9" V 8858 8984 39  0000 L CNN
F 1 "1N4148" V 8783 8984 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 8820 9030 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 8820 8905 50  0001 C CNN
F 4 "MiniMELF" H 8820 8905 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 8820 8905 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 8820 8905 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 8820 8905 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 8820 8905 60  0001 C CNN "Bauform"
F 9 "Value" H 8820 8905 60  0001 C CNN "Funktion"
F 10 "Value" H 8820 8905 60  0001 C CNN "Hersteller"
F 11 "Value" H 8820 8905 60  0001 C CNN "Hersteller Bestellnummer"
	1    8820 8905
	0    1    1    0   
$EndComp
$Comp
L D D10
U 1 1 586C13C5
P 8120 8970
F 0 "D10" V 8158 9049 39  0000 L CNN
F 1 "1N4148" V 8083 9049 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 8120 9095 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 8120 8970 50  0001 C CNN
F 4 "MiniMELF" H 8120 8970 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 8120 8970 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 8120 8970 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 8120 8970 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 8120 8970 60  0001 C CNN "Bauform"
F 9 "Value" H 8120 8970 60  0001 C CNN "Funktion"
F 10 "Value" H 8120 8970 60  0001 C CNN "Hersteller"
F 11 "Value" H 8120 8970 60  0001 C CNN "Hersteller Bestellnummer"
	1    8120 8970
	0    1    1    0   
$EndComp
$Comp
L D D5
U 1 1 586C2908
P 10370 6370
F 0 "D5" H 10370 6505 39  0000 L CNN
F 1 "1N4148" H 10333 6449 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 10370 6495 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 10370 6370 50  0001 C CNN
F 4 "MiniMELF" H 10370 6370 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 10370 6370 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 10370 6370 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 10370 6370 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 10370 6370 60  0001 C CNN "Bauform"
F 9 "Value" H 10370 6370 60  0001 C CNN "Funktion"
F 10 "Value" H 10370 6370 60  0001 C CNN "Hersteller"
F 11 "Value" H 10370 6370 60  0001 C CNN "Hersteller Bestellnummer"
	1    10370 6370
	1    0    0    -1  
$EndComp
$Comp
L D D6
U 1 1 586C6B7F
P 5620 7670
F 0 "D6" H 5620 7805 39  0000 L CNN
F 1 "1N4148" H 5583 7749 39  0000 L CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 5620 7795 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A100/SMD1N4148%23VIS.pdf" H 5620 7670 50  0001 C CNN
F 4 "MiniMELF" H 5620 7670 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/1N-UF-AA-Dioden/1N-4148-SMD/3/index.html?ACTION=3&LA=446&ARTICLE=18403&GROUPID=2987&artnr=1N+4148+SMD&SEARCH=1n4148" H 5620 7670 60  0001 C CNN "Bestelllink"
F 6 "Gleichrichterdiode SMD, Mini Melf , 100V, 0,15A" H 5620 7670 60  0001 C CNN "Technische Daten"
F 7 "R: 1N 4148 SMD" H 5620 7670 60  0001 C CNN "Bestellnummer"
F 8 "MiniMELF" H 5620 7670 60  0001 C CNN "Bauform"
F 9 "Value" H 5620 7670 60  0001 C CNN "Funktion"
F 10 "Value" H 5620 7670 60  0001 C CNN "Hersteller"
F 11 "Value" H 5620 7670 60  0001 C CNN "Hersteller Bestellnummer"
	1    5620 7670
	-1   0    0    -1  
$EndComp
Text Notes 10315 2825 0    39   ~ 0
@Jürgen kontrollieren\nhabe keine Zenerdiode mit 3,1V gefunden\nhabe daher von Conrad eine mit 3,3V in smd vorgesehen\nfalls es doch eine mit 3,1 gibt Footprint kontrollieren.
$Comp
L D_Zener D16
U 1 1 586C6D2B
P 11720 2020
F 0 "D16" H 11720 2236 50  0000 C CNN
F 1 "ZPD3,1" H 11720 2145 50  0000 C CNN
F 2 "Diodes_SMD:MiniMELF_Standard" H 11720 2144 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/A900/SMDZF%23VIS.pdf" H 11720 2020 50  0001 C CNN
F 4 "Mini Melf, DO-213AA, SOD 80" H 11720 2020 60  0001 C CNN "Gehäuseart"
F 5 "https://www.reichelt.de/SMD-Z-Dioden-Mini-Melf/SMD-ZF-5-1/3/index.html?ACTION=3;ARTICLE=18942;SEARCH=smd%20zf%203" H 11720 2020 60  0001 C CNN "Bestelllink"
F 6 "Chip-Zener-Diode 0,5W 3,3V" H 11720 2020 60  0001 C CNN "Technische Daten"
F 7 "R: SMD ZF 3,3" H 11720 2020 60  0001 C CNN "Bestellnummer"
F 8 "Mini Melf, DO-213AA, SOD 80" H 11720 2020 60  0001 C CNN "Bauform"
F 9 "Value" H 11720 2020 60  0001 C CNN "Funktion"
F 10 "Value" H 11720 2020 60  0001 C CNN "Hersteller"
F 11 "Value" H 11720 2020 60  0001 C CNN "Hersteller Bestellnummer"
	1    11720 2020
	1    0    0    -1  
$EndComp
Text Notes 13675 4755 0    39   ~ 0
@ Jürgen\nmüsste vom rtc Modul her auf DS:0 bzw pin5\nGND angeschlossen werden\nlaut Beschriftung von den RTC Modul ?
Text Notes 3740 8535 0    39   ~ 0
Q2 von IRF9540 auf \nIRF 9540NS als SMD umgeändert\n
Text Notes 8070 8550 0    39   ~ 0
Q1 von NDP6020P auf \nIRF NDB6020P als SMD umgeändert\n
Wire Notes Line
	635  6825 635  8185
Wire Notes Line
	635  8185 1960 8185
Wire Notes Line
	1960 8185 1960 6825
Wire Notes Line
	1960 6825 635  6825
Text Notes 1060 6770 0    60   ~ 0
Hinzugefügt
$Comp
L R R37
U 1 1 58A6DCA1
P 7260 5560
F 0 "R37" H 7340 5575 50  0000 L CNN
F 1 "2K2" H 7340 5490 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" H 7348 5469 50  0001 L CNN
F 3 "" H 7260 5560 50  0000 C CNN
F 4 "Value" H 7260 5560 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 7260 5560 60  0001 C CNN "Bestelllink"
F 6 "Value" H 7260 5560 60  0001 C CNN "Technische Daten"
F 7 "Value" H 7260 5560 60  0001 C CNN "Bestellnummer"
F 8 "Value" H 7260 5560 60  0001 C CNN "Bauform"
F 9 "Value" H 7348 5423 60  0001 L CNN "Funktion"
F 10 "Value" H 7260 5560 60  0001 C CNN "Hersteller"
F 11 "Value" H 7260 5560 60  0001 C CNN "Hersteller Bestellnummer"
	1    7260 5560
	-1   0    0    1   
$EndComp
Wire Wire Line
	7260 5710 7260 5870
$Comp
L GND #PWR066
U 1 1 58A6ED16
P 7260 5870
F 0 "#PWR066" H 7260 5620 50  0001 C CNN
F 1 "GND" H 7265 5697 50  0000 C CNN
F 2 "" H 7260 5870 50  0000 C CNN
F 3 "" H 7260 5870 50  0000 C CNN
	1    7260 5870
	1    0    0    -1  
$EndComp
Wire Wire Line
	7260 5410 7260 5270
Connection ~ 7260 5270
$EndSCHEMATC
