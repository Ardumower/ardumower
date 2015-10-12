EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-cache
LIBS:Wlan_ESP8266
LIBS:power
LIBS:conn
LIBS:uln-udn
LIBS:device
LIBS:78xx-Regler-BuildingBlock_ModB_RevA-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 11
Title "Ardumower Shield - I2C Schnittstelle"
Date "Sonntag, 26. April 2015"
Rev "V1.3"
Comp "Layout & Plan von UweZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR018
U 1 1 553D4F12
P 2445 3775
F 0 "#PWR018" H 2445 3525 60  0001 C CNN
F 1 "GND" V 2445 3560 60  0000 C CNN
F 2 "" H 2445 3775 60  0000 C CNN
F 3 "" H 2445 3775 60  0000 C CNN
	1    2445 3775
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR019
U 1 1 553D4F18
P 2445 3975
F 0 "#PWR019" H 2445 3825 60  0001 C CNN
F 1 "+5V" V 2445 4185 60  0000 C CNN
F 2 "" H 2445 3975 60  0000 C CNN
F 3 "" H 2445 3975 60  0000 C CNN
	1    2445 3975
	0    1    -1   0   
$EndComp
Text GLabel 2485 3575 2    60   BiDi ~ 0
SDA2
Text GLabel 2155 3675 2    60   Input ~ 0
SCL2
Wire Wire Line
	1975 3975 2445 3975
Wire Wire Line
	1975 3775 2445 3775
Wire Wire Line
	1975 3675 2155 3675
Wire Wire Line
	1975 3575 2485 3575
$Comp
L CONN_01X10 P5
U 1 1 55DDA0DF
P 1775 3525
F 0 "P5" H 1775 4075 50  0000 C CNN
F 1 "IMU Compas" V 1875 3525 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 1775 3525 60  0001 C CNN
F 3 "" H 1775 3525 60  0000 C CNN
	1    1775 3525
	-1   0    0    1   
$EndComp
NoConn ~ 1975 3075
NoConn ~ 1975 3175
NoConn ~ 1975 3275
NoConn ~ 1975 3375
NoConn ~ 1975 3475
NoConn ~ 1975 3875
$EndSCHEMATC
