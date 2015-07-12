EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 25
Title "Ardumower Shield - Odometry"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR027
U 1 1 553AD719
P 4655 2910
F 0 "#PWR027" H 4655 2660 60  0001 C CNN
F 1 "GND" V 4655 2685 60  0000 C CNN
F 2 "" H 4655 2910 60  0000 C CNN
F 3 "" H 4655 2910 60  0000 C CNN
	1    4655 2910
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR028
U 1 1 553AD72D
P 6280 2810
F 0 "#PWR028" H 6280 2660 60  0001 C CNN
F 1 "+5V" V 6280 3025 60  0000 C CNN
F 2 "" H 6280 2810 60  0000 C CNN
F 3 "" H 6280 2810 60  0000 C CNN
	1    6280 2810
	0    1    1    0   
$EndComp
$Comp
L CONN_4 P8
U 1 1 553AD741
P 4185 2960
F 0 "P8" V 4135 2960 50  0000 C CNN
F 1 "ODO Right" V 4235 2960 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x04" H 4185 2960 60  0001 C CNN
F 3 "" H 4185 2960 60  0000 C CNN
F 4 "Value" H 4185 2960 60  0001 C CNN "Bestellnummer"
	1    4185 2960
	-1   0    0    -1  
$EndComp
Text GLabel 5180 3010 2    60   Output ~ 0
pinOdometryRight
Text GLabel 6315 3110 2    60   Output ~ 0
pinOdometryRight2
Wire Wire Line
	4535 2810 6280 2810
Wire Wire Line
	4535 2910 4655 2910
Wire Wire Line
	4535 3010 5180 3010
Wire Wire Line
	4535 3110 6315 3110
$Comp
L GND #PWR029
U 1 1 553B1AA7
P 4655 3435
F 0 "#PWR029" H 4655 3185 60  0001 C CNN
F 1 "GND" V 4655 3210 60  0000 C CNN
F 2 "" H 4655 3435 60  0000 C CNN
F 3 "" H 4655 3435 60  0000 C CNN
	1    4655 3435
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR030
U 1 1 553B1AAD
P 6305 3335
F 0 "#PWR030" H 6305 3185 60  0001 C CNN
F 1 "+5V" V 6305 3550 60  0000 C CNN
F 2 "" H 6305 3335 60  0000 C CNN
F 3 "" H 6305 3335 60  0000 C CNN
	1    6305 3335
	0    1    1    0   
$EndComp
$Comp
L CONN_4 P9
U 1 1 553B1AB4
P 4180 3485
F 0 "P9" V 4130 3485 50  0000 C CNN
F 1 "ODO Left" V 4230 3485 50  0000 C CNN
F 2 "ACS712:Pin_Header_Straight_1x04" H 4180 3485 60  0001 C CNN
F 3 "" H 4180 3485 60  0000 C CNN
F 4 "Value" H 4180 3485 60  0001 C CNN "Bestellnummer"
	1    4180 3485
	-1   0    0    -1  
$EndComp
Text GLabel 5165 3535 2    60   Output ~ 0
pinOdometryLeft
Text GLabel 6320 3635 2    60   Output ~ 0
pinOdometryLeft2
Wire Wire Line
	4530 3335 6305 3335
Wire Wire Line
	4530 3435 4655 3435
Wire Wire Line
	4530 3535 5165 3535
Wire Wire Line
	4530 3635 6320 3635
$Comp
L R R38
U 1 1 555C6BCC
P 5335 2880
F 0 "R38" V 5440 2880 40  0000 C CNN
F 1 "4,7K" V 5342 2881 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 5265 2880 30  0001 C CNN
F 3 "" H 5335 2880 30  0000 C CNN
F 4 "R: METALL 4,70K" H 5335 2880 60  0001 C CNN "Bestellnummer"
F 5 "https://www.reichelt.de/METALL-4-70K/3/index.html?&ACTION=3&LA=446&ARTICLE=11784&artnr=METALL+4%2C70K&SEARCH=widerstand+4k7" H 5335 2880 60  0001 C CNN "Bestelllink"
	1    5335 2880
	0    -1   -1   0   
$EndComp
$Comp
L R R40
U 1 1 555C6CE7
P 5910 2880
F 0 "R40" V 6015 2880 40  0000 C CNN
F 1 "4,7K" V 5917 2881 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 5840 2880 30  0001 C CNN
F 3 "" H 5910 2880 30  0000 C CNN
F 4 "R: METALL 4,70K" H 5910 2880 60  0001 C CNN "Bestellnummer"
F 5 "https://www.reichelt.de/METALL-4-70K/3/index.html?&ACTION=3&LA=446&ARTICLE=11784&artnr=METALL+4%2C70K&SEARCH=widerstand+4k7" H 5910 2880 60  0001 C CNN "Bestelllink"
	1    5910 2880
	0    1    -1   0   
$EndComp
Wire Wire Line
	5660 2880 5660 2810
Connection ~ 5660 2810
Wire Wire Line
	5585 2880 5585 2810
Connection ~ 5585 2810
Wire Wire Line
	5085 2880 5085 3010
Connection ~ 5085 3010
Wire Wire Line
	6160 2880 6160 3110
Connection ~ 6160 3110
$Comp
L R R39
U 1 1 555C6EC6
P 5905 3405
F 0 "R39" V 6010 3405 40  0000 C CNN
F 1 "4,7K" V 5912 3406 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 5835 3405 30  0001 C CNN
F 3 "" H 5905 3405 30  0000 C CNN
F 4 "R: METALL 4,70K" H 5905 3405 60  0001 C CNN "Bestellnummer"
F 5 "https://www.reichelt.de/METALL-4-70K/3/index.html?&ACTION=3&LA=446&ARTICLE=11784&artnr=METALL+4%2C70K&SEARCH=widerstand+4k7" H 5905 3405 60  0001 C CNN "Bestelllink"
	1    5905 3405
	0    1    -1   0   
$EndComp
$Comp
L R R37
U 1 1 555C6E5F
P 5325 3405
F 0 "R37" V 5435 3405 40  0000 C CNN
F 1 "4,7K" V 5332 3406 40  0000 C CNN
F 2 "ACS712:Resistor_Horizontal_RM10mm" V 5255 3405 30  0001 C CNN
F 3 "" H 5325 3405 30  0000 C CNN
F 4 "R: METALL 4,70K" H 5325 3405 60  0001 C CNN "Bestellnummer"
F 5 "https://www.reichelt.de/METALL-4-70K/3/index.html?&ACTION=3&LA=446&ARTICLE=11784&artnr=METALL+4%2C70K&SEARCH=widerstand+4k7" H 5325 3405 60  0001 C CNN "Bestelllink"
	1    5325 3405
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5655 3405 5655 3335
Connection ~ 5655 3335
Wire Wire Line
	5575 3405 5575 3335
Connection ~ 5575 3335
Wire Wire Line
	6155 3405 6155 3635
Connection ~ 6155 3635
Wire Wire Line
	5075 3405 5075 3535
Connection ~ 5075 3535
$EndSCHEMATC
