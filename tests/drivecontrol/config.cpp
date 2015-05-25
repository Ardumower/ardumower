#include "config.h"
#include "drivers.h"
#include "motorcontrol.h"
#include "motormow.h"
#include "timer.h"
#include "sonar.h"


FactoryConfig Config;


void FactoryConfig::setup(){
  Console.println(F("FactoryConfig::setup"));
  
  // -------------- gear motors -------------------------------------------
  MotorCtrl.motorSpeedMaxRpm = 18;      
  MotorCtrl.enableStallDetection = true;
  MotorCtrl.motorSpeedMaxPwm = 255;    
  MotorCtrl.motorLeftPID.Kp       = 0.87;    // PID speed controller
  MotorCtrl.motorLeftPID.Ki       = 0.29;
  MotorCtrl.motorLeftPID.Kd       = 0.25;     
/*  MotorCtrl.odometryTicksPerRevolution = 20;   // encoder ticks per one full resolution
  MotorCtrl.odometryTicksPerCm = 0.5;    // encoder ticks per cm
  MotorCtrl.odometryWheelBaseCm = 14;    // wheel-to-wheel distance (cm)    
  MotorCtrl.motorLeftSwapDir = false;
  MotorCtrl.motorRightSwapDir = false;*/  
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

  // ---------------- mower motor ---------------------------------------
  MotorMow.motorMowAccel       = 0.1;  // motor mower acceleration (warning: do not set too high)
  MotorMow.motorMowSpeedMaxPwm   = 255;    // motor mower max PWM
  MotorMow.motorMowPowerMax = 75.0;     // motor mower max power (Watt)  
  // MC33926 current:  5V / 1024 ADC counts,  525 mV per A  => 9.3 mA per ADC step  
  MotorMow.motorSenseScale  = 9.3;  // motor left sense scale  (mA=(ADC-zero) * scale)
  MotorMow.motorVoltageDC = 24.0;      

  // ------------------ sonar -------------------------------------------
  Sonar.sonarTriggerBelow = 900;
  Sonar.enableCenter = false;
  Sonar.enableRight = true;
  Sonar.enableLeft = true;

  // ----------------- timer/RTC -----------------------------------------
  Timer.enable = true;
}






