1.0a4-Azurit

2015-07-08 changed motorLeftPID.Kp
2015-06-26 better driving around perimeter
2015-06-26 more robust sonar sensor
2015-06-26 battery stats display fix (nan)
2015-06-25 optimized driving behavior around perimeter
2015-06-25 mower now stops immediately when in station
2015-06-25 added sonar turn feature ( http://www.ardumower.de/index.php/de/forum/anleitungen-hilfe/585-ultraschallsensoren-bitte-um-hilfe#7146)
2015-06-24 another small bugfix for battery stats
2015-06-24 small bugfix for battery stats
2015-06-22 made "mow modulate" a developer option (use at your own risk)
2015-06-19 optimized station times
2015-06-18 bugfix: better checking for zero values (float is never exactly zero)
2015-06-18 bugfix: really stop if setspeed=0 and actualspeed almost zero
2015-06-18 bugfix:  now reacting on motorcurrent  in state PFND, PTRK
2015-06-17 Merge branch 'leftright_pid_sync' into develop
2015-06-17 mini config fix
2015-06-15 pfodapp plot adjustments
2015-06-15 leftright pid sync
2015-06-15 better and more random driving behavior around obstacles and perimeter new values in Settings-Motor and Perimeter
2015-06-14 enabled checkTilt()  again some code cleanup
2015-06-14 new stats: mower now records battery statistics
2015-06-12 Revert "recharged battery capacity in maH is now only updated if mower is in STATE_STATION_CHARGING"
2015-06-12 recharged battery capacity in maH is now only updated if mower is in STATE_STATION_CHARGING
2015-06-12 optimized mower motor over current behavior fixes: https://github.com/Ardumower/ardumower/issues/20 https://github.com/Ardumower/ardumower/issues/52
2015-06-10 performance improvements and code cleanup also fixes https://github.com/Ardumower/ardumower/issues/21
2015-06-10 new config.h option: USE_BLANK_MEGA for testing purposes only when using USE_BLANK_MEGA in config.h it is possible to run the ardumower code on an blank Arduino Mega
2015-06-06 added statsOverride option now it is possible to reenter accidentally lost mower stats
2015-06-06 new feature: mower now records statistics first version mow time total and mow time trip is recorded
2015-06-04 improved driving behavior after mower was outside perimeter
2015-06-03 added missing values in Robot::printSettingSerial()
2015-06-03 mower now uses perimeter as default new defaults: motorZeroSettleTime, motorRollTimeMax, motorRollTimeMin, motorReverseTime, motorForwTimeMax, sonarTriggerBelow, perimeterTrackRollTime, perimeterTrackRevTime
2015-06-03 improved driving behavior
2015-05-31 new default: motorSwapDir = 0; for both driving motors current measurements from MC are more reliable
2015-05-31 new default: using only one channel of our motor odometry encoder solves https://github.com/Ardumower/ardumower/issues/35
2015-05-31 corrected version number
2015-05-31 improved handling of sonar sensors sonar sensor readings and caused behavior should now be more reliable
2015-05-31 improved behavior when the robot is stucked
2015-05-31 improved checkPerimeterBoundary behavior mower now moves back in when driven outside perimeter while driving backwards
2015-05-29 bugfix for Robot::checkIfStucked() added STATE_ERROR
2015-05-29 initial stuck detection feature if GPS is in use the mower can now detect if it´s stucked if stucked the mower tries to set free, if not successful mower is switched into ERROR
2015-05-25 now time and date under DATE/TIME are always shown fixes https://github.com/Ardumower/ardumower/issues/42
2015-05-25 added motorRollTimeMin implements https://github.com/Ardumower/ardumower/issues/41 so we are in better control of robot movement
-------------------------------------------------------------------------------------------------------------------------------------------

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