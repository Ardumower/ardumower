EESchema Schematic File Version 2
LIBS:ardumower mega shield svn-rescue
LIBS:power
LIBS:device
LIBS:Zimprich
LIBS:conn
LIBS:transistors
LIBS:ardumower mega shield svn-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 19 24
Title "Ardumower shield SVN Version"
Date "2016-09-17"
Rev "1.21"
Comp "AG JL UZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 7070 3885 2    39   Output ~ 0
SCL
Text GLabel 7045 3785 2    39   BiDi ~ 0
SDA
Text GLabel 3400 2985 0    39   Input ~ 0
pinPerimeterLeft
Text GLabel 7070 2685 2    39   Output ~ 0
pinMotorRightPWM
Text GLabel 7070 2485 2    39   Output ~ 0
pinMotorLeftPWM
Text GLabel 7010 4685 2    39   Input ~ 0
pinMotorLeftFault
Text GLabel 7010 5735 2    39   Input ~ 0
pinTilt
Text GLabel 4425 4585 0    39   Output ~ 0
pinBuzzer
Text GLabel 4475 6085 0    39   Input ~ 0
pinBumperLeft
Text GLabel 7010 5935 2    39   Output ~ 0
pinMotorEnable
Text GLabel 3400 2685 0    39   Input ~ 0
pinBatteryVoltage
Text GLabel 3400 3385 0    39   Input ~ 0
pinChargeCurrent
Text GLabel 3400 3485 0    39   Input ~ 0
pinChargeVoltage
Text GLabel 7010 5335 2    39   Output ~ 0
pinMotorLeftDir
Text GLabel 7010 5535 2    39   Output ~ 0
pinMotorRightDir
Text GLabel 7010 5085 2    39   Output ~ 0
pinMotorMowDir
Text GLabel 7010 4885 2    39   Input ~ 0
pinMotorRightFault
Text GLabel 7070 2785 2    39   Output ~ 0
pinMotorMowPWM
Text GLabel 3400 2785 0    39   Input ~ 0
pinMotorMowSense
Text GLabel 3400 2585 0    39   Input ~ 0
pinMotorLeftSense
Text GLabel 3400 2485 0    39   Input ~ 0
pinMotorRightSense
NoConn ~ 6860 4135
NoConn ~ 6860 4235
Text GLabel 4475 6185 0    39   Input ~ 0
pinBumperRight
Text GLabel 4475 5535 0    39   Input ~ 0
pinRain
Text GLabel 8010 5635 2    39   Output ~ 0
pinSonarLeftTrigger
Text GLabel 8010 5835 2    39   Input ~ 0
pinSonarLeftEcho
Text GLabel 3405 3785 0    39   Input ~ 0
pinOdometryLeft
Text GLabel 7070 3185 2    39   Input ~ 0
GPS_RX
Text GLabel 7070 3285 2    39   Output ~ 0
GPS_TX
Text GLabel 7070 3385 2    39   Output ~ 0
TX2
Text GLabel 7060 3485 2    39   Input ~ 0
RX2
Text GLabel 4475 5235 0    39   Input ~ 0
pinUserSwitch2
Text GLabel 7070 1685 2    39   Input ~ 0
pinRemoteMow
Text GLabel 7070 1785 2    39   Input ~ 0
pinRemoteSteer
Text GLabel 7070 1885 2    39   Input ~ 0
pinRemoteSpeed
Text GLabel 8010 5235 2    39   Output ~ 0
pinSonarRightTrigger
Text GLabel 8010 4985 2    39   Output ~ 0
pinMotorMowEnable
Text GLabel 8010 5435 2    39   Input ~ 0
pinSonarRightEcho
Text GLabel 4450 5035 0    39   Input ~ 0
ReservePin49
Text GLabel 4435 4785 0    39   Input ~ 0
pinButton
Text GLabel 8010 4785 2    39   Input ~ 0
pinMotorMowFault
Text GLabel 8010 4585 2    39   Input ~ 0
pinSonarCenterTrigger
Text GLabel 8010 4385 2    39   Input ~ 0
pinSonarCenterEcho
Text GLabel 4440 4685 0    39   Input ~ 0
pinRemoteSwitch
Text GLabel 4475 5335 0    39   Input ~ 0
pinUserSwitch1
Text GLabel 4475 5135 0    39   Input ~ 0
pinUserSwitch3
Text GLabel 4435 4885 0    39   Output ~ 0
pinChargingEnable
Text GLabel 7065 1585 2    39   Output ~ 0
Led-Status
Text GLabel 4470 5435 0    39   Input ~ 0
DropLeft
Text GLabel 7010 4485 2    39   Input ~ 0
DropRight
Text GLabel 7070 3585 2    39   Input ~ 0
TX1
Text GLabel 7060 3685 2    39   Input ~ 0
RX1
Text GLabel 7070 2285 2    39   Output ~ 0
DuoLED-Rot
Text GLabel 7070 2385 2    39   Output ~ 0
DuoLED_Grün
Text Notes 8160 2285 0    60   ~ 0
Duo LED hinzugefügt
Text GLabel 3400 2885 0    39   Input ~ 0
pinPerimeterRight
Text GLabel 3405 3885 0    39   Input ~ 0
pinOdometryLeft2
Text GLabel 3405 4085 0    39   Input ~ 0
pinOdometryRight2
Text GLabel 3405 3985 0    39   Input ~ 0
pinOdometryRight
Text GLabel 3400 3585 0    39   Input ~ 0
ReserveAD10
Text GLabel 7070 2985 2    39   Input ~ 0
ReservePin0
Text GLabel 7070 2885 2    39   Input ~ 0
ReservePin1
Text GLabel 7070 2585 2    39   Input ~ 0
RelaisAbschaltung
Text GLabel 7070 2085 2    39   Input ~ 0
ReservePin8
Text GLabel 7070 1985 2    39   Input ~ 0
ReservePin9
Text GLabel 3400 3085 0    39   Input ~ 0
ReserveAD6
Text GLabel 3400 3185 0    39   Input ~ 0
Voltage measurement
Text GLabel 3405 3685 0    39   Input ~ 0
pinMotorMowRpm_neu
NoConn ~ 5060 1585
$Comp
L C_Small C9
U 1 1 57DFEDC9
P 6900 1215
F 0 "C9" H 6992 1261 50  0000 L CNN
F 1 "100nF" H 6992 1170 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 6900 1215 50  0001 C CNN
F 3 "" H 6900 1215 50  0000 C CNN
	1    6900 1215
	1    0    0    -1  
$EndComp
$Comp
L ARDUINO_MEGA_SHIELD SHIELD1
U 1 1 57DFED57
P 5960 3735
F 0 "SHIELD1" H 6010 3785 60  0001 C CNN
F 1 "ARDUINO_MEGA_SHIELD" H 5960 3735 60  0001 C CNN
F 2 "Zimprich:ARDUINO_MEGA_SHIELD_DUO_3D" H 5960 3735 60  0001 C CNN
F 3 "" H 5960 3735 60  0001 C CNN
F 4 "Value" H 5960 3735 60  0001 C CNN "Gehäuseart"
F 5 "Value" H 5960 3735 60  0001 C CNN "Bestelllink"
F 6 "SHIELD" H 5560 6235 60  0001 C CNN "Reference"
F 7 "ARDUINO_MEGA_SHIELD" H 5860 1035 60  0001 C CNN "Value"
	1    5960 3735
	1    0    0    -1  
$EndComp
$Comp
L +9V #PWR130
U 1 1 57DB02C7
P 4560 2285
F 0 "#PWR130" H 4560 2135 50  0001 C CNN
F 1 "+9V" V 4560 2475 50  0000 C CNN
F 2 "" H 4560 2285 50  0000 C CNN
F 3 "" H 4560 2285 50  0000 C CNN
	1    4560 2285
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR127
U 1 1 57DB1AC1
P 4400 1885
F 0 "#PWR127" H 4400 1735 50  0001 C CNN
F 1 "+3.3V" V 4400 2115 50  0000 C CNN
F 2 "" H 4400 1885 50  0000 C CNN
F 3 "" H 4400 1885 50  0000 C CNN
	1    4400 1885
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR126
U 1 1 57DC5ACC
P 4145 1985
F 0 "#PWR126" H 4145 1835 50  0001 C CNN
F 1 "+5V" V 4145 2170 50  0000 C CNN
F 2 "" H 4145 1985 50  0000 C CNN
F 3 "" H 4145 1985 50  0000 C CNN
	1    4145 1985
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR128
U 1 1 57DC997D
P 4525 4435
F 0 "#PWR128" H 4525 4185 50  0001 C CNN
F 1 "GND" H 4530 4262 50  0000 C CNN
F 2 "" H 4525 4435 50  0000 C CNN
F 3 "" H 4525 4435 50  0000 C CNN
	1    4525 4435
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR131
U 1 1 57DCA6F9
P 6900 1065
F 0 "#PWR131" H 6900 815 50  0001 C CNN
F 1 "GND" H 6905 892 50  0000 C CNN
F 2 "" H 6900 1065 50  0000 C CNN
F 3 "" H 6900 1065 50  0000 C CNN
	1    6900 1065
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR132
U 1 1 57DCA959
P 7015 1485
F 0 "#PWR132" H 7015 1235 50  0001 C CNN
F 1 "GND" V 7020 1312 50  0000 C CNN
F 2 "" H 7015 1485 50  0000 C CNN
F 3 "" H 7015 1485 50  0000 C CNN
	1    7015 1485
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR129
U 1 1 57DD92E3
P 4550 2130
F 0 "#PWR129" H 4550 1880 50  0001 C CNN
F 1 "GND" V 4550 1940 50  0000 C CNN
F 2 "" H 4550 2130 50  0000 C CNN
F 3 "" H 4550 2130 50  0000 C CNN
	1    4550 2130
	0    1    -1   0   
$EndComp
Wire Wire Line
	6860 1485 7015 1485
Wire Wire Line
	6860 5535 7010 5535
Wire Wire Line
	7010 5335 6860 5335
Wire Wire Line
	4475 6085 4960 6085
Wire Wire Line
	6860 5935 7010 5935
Wire Wire Line
	6860 5235 8010 5235
Wire Wire Line
	6860 4885 7010 4885
Wire Wire Line
	4470 5635 4960 5635
Wire Wire Line
	6860 3285 7070 3285
Wire Wire Line
	6860 3485 7060 3485
Wire Wire Line
	7010 5735 6860 5735
Wire Wire Line
	4475 5735 4960 5735
Wire Wire Line
	4475 5885 4960 5885
Wire Wire Line
	4475 5235 4960 5235
Wire Wire Line
	6860 1685 7070 1685
Wire Wire Line
	6860 4585 8010 4585
Wire Wire Line
	4475 5135 4960 5135
Wire Wire Line
	6860 5635 8010 5635
Wire Wire Line
	4475 5535 4960 5535
Wire Wire Line
	6860 2785 7070 2785
Wire Wire Line
	6860 2485 7070 2485
Wire Wire Line
	6860 5085 7010 5085
Wire Wire Line
	6860 4785 8010 4785
Wire Wire Line
	6860 4985 8010 4985
Wire Wire Line
	6860 2685 7070 2685
Wire Wire Line
	6860 1585 7065 1585
Wire Wire Line
	6860 3885 7070 3885
Wire Wire Line
	4960 5435 4470 5435
Wire Wire Line
	6860 2385 7070 2385
Wire Wire Line
	3400 2485 4960 2485
Wire Wire Line
	3400 2585 4960 2585
Wire Wire Line
	3400 2685 4960 2685
Wire Wire Line
	3400 2885 4960 2885
Wire Wire Line
	3400 2985 4960 2985
Wire Wire Line
	3400 3085 4960 3085
Wire Wire Line
	3400 3185 4960 3185
Wire Wire Line
	4435 4885 4960 4885
Wire Wire Line
	4435 4785 4960 4785
Wire Wire Line
	4440 4685 4960 4685
Wire Wire Line
	6860 2985 7070 2985
Wire Wire Line
	6860 2885 7070 2885
Wire Wire Line
	6860 2585 7070 2585
Wire Wire Line
	6860 2085 7070 2085
Wire Wire Line
	6860 1785 7070 1785
Wire Wire Line
	6860 1885 7070 1885
Wire Wire Line
	6860 1985 7070 1985
Wire Wire Line
	6860 3385 7070 3385
Wire Wire Line
	7070 3185 6860 3185
Wire Wire Line
	6860 4685 7010 4685
Wire Wire Line
	6860 4485 7010 4485
Wire Wire Line
	4960 5985 4475 5985
Wire Wire Line
	4960 6185 4475 6185
Wire Wire Line
	4960 5335 4475 5335
Wire Wire Line
	4425 4585 4960 4585
Wire Wire Line
	4525 4435 4960 4435
Wire Wire Line
	3405 3985 4960 3985
Wire Wire Line
	3405 3885 4960 3885
Wire Wire Line
	3405 3785 4960 3785
Wire Wire Line
	3400 3585 4960 3585
Wire Wire Line
	3400 3385 4960 3385
Wire Wire Line
	3400 3485 4960 3485
Wire Wire Line
	4560 2285 4960 2285
Wire Wire Line
	4145 1985 4960 1985
Wire Wire Line
	4400 1885 4960 1885
Wire Wire Line
	4525 1785 4960 1785
Wire Wire Line
	6860 4385 8010 4385
Wire Wire Line
	6860 5435 8010 5435
Wire Wire Line
	6860 5835 8010 5835
Wire Wire Line
	3400 2785 4960 2785
Wire Wire Line
	6900 1115 6900 1065
Wire Wire Line
	6900 1315 6900 1385
Wire Wire Line
	4815 4435 4815 4335
Wire Wire Line
	4815 4335 4960 4335
Connection ~ 4815 4435
Wire Wire Line
	4580 2085 4960 2085
Wire Wire Line
	4580 2185 4960 2185
Wire Wire Line
	4580 2085 4580 2185
Wire Wire Line
	4550 2130 4580 2130
Connection ~ 4580 2130
Wire Wire Line
	6860 3785 7045 3785
Wire Wire Line
	6860 3685 7060 3685
Wire Wire Line
	6860 3585 7070 3585
Wire Wire Line
	6860 2285 7070 2285
Text GLabel 4910 1685 0    39   Input ~ 0
IOREF
Wire Wire Line
	5060 1685 4910 1685
Wire Wire Line
	6900 1385 6860 1385
NoConn ~ 5060 1385
NoConn ~ 5060 1485
Wire Wire Line
	3405 3685 4960 3685
Wire Wire Line
	3405 4085 4960 4085
Wire Wire Line
	4960 5035 4450 5035
Text GLabel 4475 5985 0    39   Input ~ 0
pinLawnFrontRecv
Text GLabel 4475 5735 0    39   Input ~ 0
pinLawnBackRecv
Text GLabel 4475 5885 0    39   Output ~ 0
pinLawnFrontSend
Text GLabel 4470 5635 0    39   Output ~ 0
pinLawnBackSend
Text GLabel 4525 1785 0    39   Input ~ 0
Reset
$EndSCHEMATC
