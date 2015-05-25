1.0a3-Azurit

2015-05-25 adjusted version
2015-05-25 fixes https://github.com/Ardumower/ardumower/issues/36
2015-05-25 Due to safety issues timer is only active when mower is in STATE_STATION. when mower is OFF it stays OFF. It represents now the actuall state machine http://wiki.ardumower.de/index.php?title=Ardumower_software_design
2015-05-25 default PWM frequency for motor dirvers is now 3.9kHz
2015-05-25 Revert "default PWM frequency for motor drivers is now 3.9kHz"
2015-05-25 default PWM frequency for motor drivers is now 3.9kHz
2015-05-23 added missing values from mower.cpp to printSettingSerial()
2015-05-23 changed VERSION to new versioning scheme minor bugfix
2015-05-22 added ERR_EEPROM_DATA if user settings are lost Ardumower goes into EEPROM_DATA error, so user have to check and save settings minor improvements in console menu
2015-05-22 -motor errors are now shown in console -all errors (even motor errors) are now resettable through console
2015-05-22 added resetMotorFault() to resetErrorCounters()
--------------------------------------------------------------------------------------------------------------------------------------

1.0a2-Azurit

2015-05-10 adjusted motorPowerMax
2015-05-10 mower is now allowed to be outside perimeter when in station
2015-05-10 using differential perimeter signal as default now
2015-05-10 added motorZeroSettleTime for STATE_STATION_...
2015-05-10 adjusted some perimeter values relevant for tracking
2015-05-10 Revert "adjusted some perimeter values relevant for tracking"
2015-05-09 adjusted some perimeter values relevant for tracking the adjustement of perimeterPID was necessary due to the changes to motorLeftPID
2015-05-10 using differential perimeter signal as default now
2015-05-10 Merge commit 'a35ae10b7efb6d040b964fbab4b7ed086cb0f775' into feature/perimeter-improvement
2015-05-09 added odometry interrupt flag: allow interrupt nesting
2015-05-08 -changed perimeter adc sample rate back to 9 khz (added a comment why) -increased version number
2015-05-08 changed perimeter sample rate to 19 khz
2015-05-08 pfodapp: added inside/outside indication in settings
2015-05-08 -corrected perimeter matched filter normalization -increased version number
2015-05-08 -perimeter matched filter normalization (4095)
2015-05-08 -perimeter matched filter normalization (4096)
2015-05-08 adjustable ADC sample rate for perimeter
2015-05-07 -faster perimeter LED -typo correction
2015-05-07 saving eeprom when resettting error counters
2015-05-07 added comments
2015-05-07 -saving error counters before battery shutdown -increased version number
2015-05-07 -moved strings to EEPROM (saving memory) -improved battery switch handling
2015-05-07 batSwitchOffIfIdle: changed seconds to minutes