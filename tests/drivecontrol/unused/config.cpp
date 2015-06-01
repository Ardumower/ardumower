#include "mower.h"
#include "drivers.h"
#include "motorcontrol.h"
#include "motormow.h"
#include "timer.h"
#include "modelrc.h"
#include "sonar.h"
#include "battery.h"
#include "perimeter.h"


// instances
AMotorControl MotorCtrl;
FactoryConfig Config;


// Ardumower factory configuration  (NOTE: see 'config.h' for pin layout!)

void FactoryConfig::setup(){
  Console.println(F("FactoryConfig::setup"));
  
  // -------------- gear motors -------------------------------------------
  // -- Ardumower Mini --
  //MotorCtrl.motorSpeedMaxRpm = 50;        
  MotorCtrl.motorSpeedMaxRpm = 30;      
  MotorCtrl.enableStallDetection = false;
  MotorCtrl.enableErrorDetection = false;  
  MotorCtrl.motorSpeedMaxPwm = 255;      
  MotorCtrl.odometryTicksPerRevolution = 20;   // encoder ticks per one full resolution
  MotorCtrl.odometryTicksPerCm = 0.5;    // encoder ticks per cm
  MotorCtrl.odometryWheelBaseCm = 14;    // wheel-to-wheel distance (cm)    
  MotorCtrl.motorLeftSwapDir = false;
  MotorCtrl.motorRightSwapDir = false;
  MotorCtrl.motorLeftPID.Kp       = 0.1;    // PID speed controller
  MotorCtrl.motorLeftPID.Ki       = 0.01;
  MotorCtrl.motorLeftPID.Kd       = 0.01;       
  
/*
  // -- Ardumower --
  MotorCtrl.motorSpeedMaxRpm = 10;      
  MotorCtrl.enableStallDetection = true;
  MotorCtrl.enableErrorDetection = true;  
  MotorCtrl.motorSpeedMaxPwm = 255;    
  MotorCtrl.odometryTicksPerRevolution = 1060;   // encoder ticks per one full resolution
  MotorCtrl.odometryTicksPerCm = 13.49;  // encoder ticks per cm
  MotorCtrl.odometryWheelBaseCm = 36;    // wheel-to-wheel distance (cm)  
  MotorCtrl.motorLeftSwapDir = true;
//  MotorCtrl.motorLeftSwapDir = false;
  MotorCtrl.motorRightSwapDir = false;
//  motorRightSwapDir = true;   
  // MC33926 current:  5V / 1024 ADC counts,  525 mV per A  => 9.3 mA per ADC step
  MotorCtrl.motorSenseRightScale = 9.3;  // motor right sense scale (mA=(ADC-zero) * scale)
  MotorCtrl.motorSenseLeftScale  = 9.3;  // motor left sense scale  (mA=(ADC-zero) * scale)  
  MotorCtrl.motorVoltageDC = 24.0;
  MotorCtrl.motorEfficiencyMin = 200;    // minimum motor efficiency (stall detection)
  MotorCtrl.motorLeftPID.Kp       = 0.87;    // PID speed controller
  MotorCtrl.motorLeftPID.Ki       = 0.29;
  MotorCtrl.motorLeftPID.Kd       = 0.25;*/       

  // ---------------- mower motor ---------------------------------------
  MotorMow.enableStallDetection = false;
  MotorMow.enableErrorDetection = false;  
  MotorMow.motorMowAccel       = 0.1;  // motor mower acceleration (warning: do not set too high)
  MotorMow.motorMowSpeedMaxPwm   = 255;    // motor mower max PWM
  MotorMow.motorMowPowerMax = 75.0;     // motor mower max power (Watt)  
  // MC33926 current:  5V / 1024 ADC counts,  525 mV per A  => 9.3 mA per ADC step  
  MotorMow.motorSenseScale  = 9.3;  // motor left sense scale  (mA=(ADC-zero) * scale)
  MotorMow.motorVoltageDC = 24.0;      
  
  // ------------------ perimeter -------------------------------------------  
  Perimeter.enable = false;
  Perimeter.timedOutIfBelowSmag = 300;
  Perimeter.timeOutSecIfNotInside = 8;  

  // ------------------ sonar -------------------------------------------
  Sonar.sonarTriggerBelow = 900;
  Sonar.enableCenter = true;
  Sonar.enableRight = false;
  Sonar.enableLeft = false;

  // ------------------ battery ------------------------------------------
  Battery.enableMonitor = false;
  Battery.batGoHomeIfBelow = 23.7;     // drive home voltage (Volt)
  Battery.batSwitchOffIfBelow = 21.7;  // switch off battery if below voltage (Volt)
  Battery.batSwitchOffIfIdle = 1;      // switch off battery if idle (minutes)  
  Battery.batFactor     = 0.495;      // battery conversion factor  / 10 due to arduremote bug, can be removed after fixing (look in robot.cpp)
  Battery.batChgFactor  = 0.495;      // battery conversion factor  / 10 due to arduremote bug, can be removed after fixing (look in robot.cpp)
  Battery.batFull       =29.4;      // battery reference Voltage (fully charged) PLEASE ADJUST IF USING A DIFFERENT BATTERY VOLTAGE! FOR a 12V SYSTEM TO 14.4V
  Battery.batChargingCurrentMax =1.6;  // maximum current your charger can devliver
  Battery.batFullCurrent  = 0.3;      // current flowing when battery is fully charged
  Battery.startChargingIfBelow = 27.0; // start charging if battery Voltage is below
  Battery.chargingTimeoutMinutes = 210; // safety timer for charging (minutes)
  // Sensorausgabe Konsole      (chgSelection =0)
  // Einstellungen ACS712 5A    (chgSelection =1   /   chgSenseZero ~ 511    /    chgFactor = 39    /    chgSense =185.0    /    chgChange = 0 oder 1    (je nach  Stromrichtung)   /   chgNull  = 2)
  // Einstellungen INA169 board (chgSelection =2)
  Battery.chgSelection    = 2;
  Battery.chgSenseZero    = 511;        // charge current sense zero point
  Battery.chgFactor       = 39;         // charge current conversion factor   - Empfindlichkeit nimmt mit ca. 39/V Vcc ab
  Battery.chgSense        = 185.0;      // mV/A empfindlichkeit des Ladestromsensors in mV/A (Für ACS712 5A = 185)
  Battery.chgChange       = 0;          // Messwertumkehr von - nach +         1 oder 0
  Battery.chgNull         = 2;          // Nullduchgang abziehen (1 oder 2)  

  // ----------------- timer/RTC -----------------------------------------
  Timer.enable = true;

  // ------------------ model R/C ----------------------------------------
  ModelRC.enable = true;
}






