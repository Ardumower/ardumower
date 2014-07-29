/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/* Ardumower Chassis Kit 1.0 - robot configuration (Ardumower electronics)
   (Arduino Mega) */

#include "mower.h"
#include <Arduino.h>


// ------ pins---------------------------------------
#define pinMotorEnable  37         // EN motors enable
#define pinMotorLeftPWM 5          // M1_IN1 left motor PWM pin
#define pinMotorLeftDir 31         // M1_IN2 left motor Dir pin
#define pinMotorLeftSense A1       // M1_FB  left motor current sense
#define pinMotorLeftFault 25       // M1_SF  left motor fault
                                                             
#define pinMotorRightPWM  3        // M2_IN1 right motor PWM pin
#define pinMotorRightDir 33        // M2_IN2 right motor Dir pin
#define pinMotorRightSense A0      // M2_FB  right motor current sense
#define pinMotorRightFault 27      // M2_SF  right motor fault
                                    
#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin
#define pinMotorMowDir 29          // M1_IN2 mower motor Dir pin
#define pinMotorMowSense A3        // M1_FB  mower motor current sense
#define pinMotorMowFault 26        // M1_SF  mower motor fault
#define pinMotorMowEnable 28       // EN mower motor enable
#define pinMotorMowRpm 18
    
#define pinBumperLeft 39           // bumper pins
#define pinBumperRight 37
#define pinSonarCenterTrigger 24   // ultrasonic sensor pins
#define pinSonarCenterEcho 22
#define pinSonarRightTrigger 30    
#define pinSonarRightEcho 32
#define pinSonarLeftTrigger 34         
#define pinSonarLeftEcho 36
#define pinPerimeterRight A4       // perimeter
#define pinPerimeterLeft A5
//#define pinPerimeterMuxZ A6      // perimeter mux Z (only TC-G158 board)
#define pinLED 13                  // LED
#define pinBuzzer 53               // Buzzer
#define pinTilt 35                 // Tilt sensor (required for TC-G158 board)
#define pinButton 51               // digital ON/OFF button
#define pinBatteryVoltage A2       // battery voltage sensor
#define pinChargeVoltage A9        // charging voltage sensor
#define pinChargeCurrent A8        // charge current sensor
#define pinRemoteMow 12            // remote control mower motor
#define pinRemoteSteer 11          // remote control steering 
#define pinRemoteSpeed 10          // remote control speed
#define pinRemoteSwitch 52         // remote control switch
//#define pinMuxS0 28              // mux S0 (only TC-G158 board)
//#define pinMuxS1 26              // mux S1 (only TC-G158 board)
//#define pinMuxZ A7                 // mux Z (only TC-G158 board)
#ifdef __AVR__
  #define pinOdometryLeft A12      // left odometry sensor
  #define pinOdometryLeft2 A13     // left odometry sensor (optional two-wire)
  #define pinOdometryRight A15     // right odometry sensor
  #define pinOdometryRight2 A14    // right odometry sensor (optional two-wire)
#else
  #define pinOdometryLeft DAC0     // left odometry sensor
  #define pinOdometryLeft2 DAC1    // left odometry sensor (optional two-wire)
  #define pinOdometryRight CANTX   // right odometry sensor  
  #define pinOdometryRight2 CANRX  // right odometry sensor (optional two-wire)  
#endif
#define pinLawnFrontRecv 40        // lawn sensor front receive
#define pinLawnFrontSend 41        // lawn sensor front sender 
#define pinLawnBackRecv 42         // lawn sensor back receive
#define pinLawnBackSend 43         // lawn sensor back sender 
#define pinUserSwitch1 46          // user-defined switch 1
#define pinUserSwitch2 47          // user-defined switch 2
#define pinUserSwitch3 48          // user-defined switch 3
// compass/gyro/accel (I2C):   SCL ,  SDA 


// ------- baudrates---------------------------------
#define BAUDRATE 19200            // serial output baud rate
#define PFOD_BAUDRATE 19200       // pfod app serial output baud rate


Mower robot;


Mower::Mower(){
  name = "Ardumower";
  // ------- wheel motors -----------------------------
  motorAccel       = 0.002;  // motor wheel acceleration (warning: do not set too high)
  motorSpeedMax       = 33;   // motor wheel max RPM
  motorSpeedMaxPwm    = 255;  // motor wheel max Pwm  (8-bit PWM=255, 10-bit PWM=1023)
  motorPowerMax     = 23.8;    // motor wheel max power (Watt)
  motorSenseRightScale = 15.3; // motor right sense scale (mA=(ADC-zero)/scale)
  motorSenseLeftScale = 15.3; // motor left sense scale  (mA=(ADC-zero)/scale)
  motorRollTimeMax    = 3000;  // max. roll time (ms)
  motorReverseTime    = 2500;  // max. reverse time (ms)
  motorForwTimeMax   = 60000; // max. forward time (ms) / timeout
  motorBiDirSpeedRatio1 = 0.3;   // bidir mow pattern speed ratio 1
  motorBiDirSpeedRatio2 = 0.92;   // bidir mow pattern speed ratio 2
  // ------ mower motor -------------------------------
  motorMowAccel       = 0.001;  // motor mower acceleration (warning: do not set too high)
  motorMowSpeedMax   = 255;    // motor mower max PWM
  motorMowPowerMax = 40.0;     // motor mower max power (Watt)
  motorMowModulate  = 0;      // motor mower cutter modulation?
  motorMowRPM        = 3300;   // motor mower RPM (only for cutter modulation)
  motorMowSenseScale = 15.3; // motor mower sense scale (mA=(ADC-zero)/scale)
  motorMowPid.Kp = 0.005;    // motor mower RPM PID controller
  motorMowPid.Ki = 0.01;
  motorMowPid.Kd = 0.01;
  //  ------ bumper -----------------------------------
  bumperUse         = 0;      // has bumpers? 
  // ------ sonar ------------------------------------
  sonarUse          = 1;      // use ultra sonic sensor? (WARNING: robot will slow down, if enabled but not connected!)
  sonarTriggerBelow = 900;    // ultrasonic sensor trigger distance
  // ------ perimeter ---------------------------------
  perimeterUse       = 0;      // use perimeter?
  perimeterTrackRollTime  = 3000;   // perimter tracking roll time (ms)
  perimeterTrackRevTime   = 2000;   // perimter tracking reverse time (ms)
  perimeterPid.Kp    = 4.0;  // perimeter PID controller
  perimeterPid.Ki    = 8.0;
  perimeterPid.Kd    = 8.0;
  // ------ lawn sensor --------------------------------
  lawnSensorUse     = 0;       // use capacitive Sensor
  // ------  IMU (compass/accel/gyro) ----------------------
  imuUse            = 0;       // use IMU? 
  imuCorrectDir     = 0;       // correct direction by compass?
  imuDirPid.Kp      = 5.0;     // direction PID controller
  imuDirPid.Ki      = 1.0;
  imuDirPid.Kd      = 1.0;    
  imuRollPid.Kp     = 0.8;   // roll PID controller
  imuRollPid.Ki     = 21;
  imuRollPid.Kd     = 0;  
  // ------ model R/C ------------------------------------
  remoteUse         = 1;       // use model remote control (R/C)?
  // ------ battery -------------------------------------
  batMonitor = 1;              // monitor battery and charge voltage?
  batGoHomeIfBelow = 23.7;     // drive home voltage (Volt)
  batSwitchOffIfBelow = 21.7;  // switch off if below voltage (Volt)
  batFactor       = 0.0658;     // battery conversion factor
  batSenseZero       =77;        // battery volt sense zero point
  batFull          =29.4;      // battery reference Voltage (fully charged)
  chgSenseZero      = 0;       // charge current sense zero point
  chgFactor       = 2.7;     // charge current conversion factor
  // ------  charging station ---------------------------
  stationRevTime     = 4000;    // charge station reverse time (ms)
  stationRollTime    = 3000;    // charge station roll time (ms)
  stationForwTime    = 2000;    // charge station forward time (ms)
  // ------ odometry ------------------------------------
  odometryUse       = 1;       // use odometry?
  odometryTicksPerRevolution = 1060;   // encoder ticks per one full resolution
  odometryTicksPerCm = 13.49;  // encoder ticks per cm
  odometryWheelBaseCm = 36;    // wheel-to-wheel distance (cm)
  // ----- GPS -------------------------------------------
  gpsUse            = 0;       // use GPS?
  // ----- other -----------------------------------------
  buttonUse         = 1;       // has digital ON/OFF button?
  // ----- user-defined switch ---------------------------
  userSwitch1       = 0;       // user-defined switch 1 (default value)
  userSwitch2       = 0;       // user-defined switch 2 (default value)
  userSwitch3       = 0;       // user-defined switch 3 (default value)
  // ----- timer -----------------------------------------
  timerUse          = 0;       // use timer?
  // ------ configuration end -------------------------------------------   
}


// remote control (RC) ppm signal change interrupt
ISR(PCINT0_vect){   
  unsigned long timeMicros = micros();
  boolean remoteSpeedState = digitalRead(pinRemoteSpeed);
  boolean remoteSteerState = digitalRead(pinRemoteSteer);
  boolean remoteMowState = digitalRead(pinRemoteMow);    
  boolean remoteSwitchState = digitalRead(pinRemoteSwitch);    
  robot.setRemotePPMState(timeMicros, remoteSpeedState, remoteSteerState, remoteMowState, remoteSwitchState);    
}

// odometry signal change interrupt
ISR(PCINT2_vect){   
  unsigned long timeMicros = micros();
  boolean odometryLeftState = digitalRead(pinOdometryLeft);
  boolean odometryLeftState2 = digitalRead(pinOdometryLeft2);
  boolean odometryRightState = digitalRead(pinOdometryRight);  
  boolean odometryRightState2 = digitalRead(pinOdometryRight2);  
  robot.setOdometryState(timeMicros, odometryLeftState, odometryRightState, odometryLeftState2, odometryRightState2);
}

// mower motor speed sensor interrupt
void rpm_interrupt(){
  boolean motorMowRpmState = digitalRead(pinMotorMowRpm);
  robot.setMotorMowRPMState(motorMowRpmState);
}


void Mower::setup(){
  Wire.begin();          
  Serial.begin(BAUDRATE);           
  Serial.println("SETUP");
  rc.initSerial(PFOD_BAUDRATE);   
    
  // http://sobisource.com/arduino-mega-pwm-pin-and-frequency-timer-control/
  #ifdef __AVR__
    TCCR3B = (TCCR3B & 0xF8) | 0x02;    // set PWM frequency 3.9 Khz (pin2,3,5) 
  #endif
  
  // i2c -- turn off internal pull-ups (and use external pull-ups)
  //digitalWrite(SDA, 0);  
  //digitalWrite(SCL, 0);
  
  // LED, buzzer, battery
  pinMode(pinLED, OUTPUT);    
  pinMode(pinBuzzer, OUTPUT);    
  pinMode(pinBatteryVoltage, INPUT);        
  pinMode(pinChargeCurrent, INPUT);          
  pinMode(pinChargeVoltage, INPUT);            
  
  // left wheel motor
  pinMode(pinMotorEnable, OUTPUT);  
  digitalWrite(pinMotorEnable, HIGH);
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT);   
  pinMode(pinMotorLeftSense, INPUT);     
  pinMode(pinMotorLeftFault, INPUT);    
  
  // right wheel motor
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT); 
  pinMode(pinMotorRightSense, INPUT);       
  pinMode(pinMotorRightFault, INPUT);  
  
  // mower motor
  pinMode(pinMotorMowDir, OUTPUT); 
  pinMode(pinMotorMowPWM, OUTPUT);     
  pinMode(pinMotorMowSense, INPUT);     
  pinMode(pinMotorMowRpm, INPUT);     
    
  // lawn sensor
  pinMode(pinLawnBackRecv, INPUT);
  pinMode(pinLawnBackSend, OUTPUT);
  pinMode(pinLawnFrontRecv, INPUT);
  pinMode(pinLawnFrontSend, OUTPUT);  
  
  // perimeter
  pinMode(pinPerimeterRight, INPUT);    
  pinMode(pinPerimeterLeft, INPUT);        
  
  // button
  pinMode(pinButton, INPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // bumpers  
  pinMode(pinBumperLeft, INPUT); 
  pinMode(pinBumperLeft, INPUT_PULLUP);
  pinMode(pinBumperRight, INPUT);     
  pinMode(pinBumperRight, INPUT_PULLUP);
  
  // sonar
  pinMode(pinSonarCenterTrigger, OUTPUT); 
  pinMode(pinSonarCenterEcho, INPUT); 
  pinMode(pinSonarLeftTrigger, OUTPUT); 
  pinMode(pinSonarLeftEcho, INPUT); 
  pinMode(pinSonarRightTrigger, OUTPUT); 
  pinMode(pinSonarRightEcho, INPUT); 
        
  // R/C
  pinMode(pinRemoteMow, INPUT);
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT); 
  pinMode(pinRemoteSwitch, INPUT);       

  // odometry
  pinMode(pinOdometryLeft, INPUT_PULLUP);  
  pinMode(pinOdometryLeft2, INPUT_PULLUP);    
  pinMode(pinOdometryRight, INPUT_PULLUP);
  pinMode(pinOdometryRight2, INPUT_PULLUP);  
  
  // user switches
  pinMode(pinUserSwitch1, OUTPUT);
  pinMode(pinUserSwitch2, OUTPUT);
  pinMode(pinUserSwitch3, OUTPUT);   

  // enable interrupts
  #ifdef __AVR__
    // R/C
    PCICR |= (1<<PCIE0);
    PCMSK0 |= (1<<PCINT4);
    PCMSK0 |= (1<<PCINT5);
    PCMSK0 |= (1<<PCINT6);
    PCMSK0 |= (1<<PCINT1);  
    
    // odometry
    PCICR |= (1<<PCIE2);
    PCMSK2 |= (1<<PCINT20);
    PCMSK2 |= (1<<PCINT21);  
    PCMSK2 |= (1<<PCINT22);
    PCMSK2 |= (1<<PCINT23);          
    
    // mower motor speed sensor interrupt
    attachInterrupt(5, rpm_interrupt, CHANGE);  
  #else
    // Due interrupts
    attachInterrupt(pinOdometryLeft, PCINT2_vect, CHANGE);
    attachInterrupt(pinOdometryLeft2, PCINT2_vect, CHANGE);
    attachInterrupt(pinOdometryRight, PCINT2_vect, CHANGE);    
    attachInterrupt(pinOdometryRight2, PCINT2_vect, CHANGE);            
    
    attachInterrupt(pinRemoteSpeed, PCINT0_vect, CHANGE);            
    attachInterrupt(pinRemoteSteer, PCINT0_vect, CHANGE);            
    attachInterrupt(pinRemoteMow, PCINT0_vect, CHANGE);   
    attachInterrupt(pinRemoteSwitch, PCINT0_vect, CHANGE);       
    
    attachInterrupt(pinMotorMowRpm, rpm_interrupt, CHANGE);
  #endif   
  
  
  // ADC
  ADCMan.init();
  ADCMan.setCapture(pinMotorMowSense, 1, true);
  ADCMan.setCapture(pinMotorLeftSense, 1, true);
  ADCMan.setCapture(pinMotorRightSense, 1, true);
  ADCMan.setCapture(pinBatteryVoltage, 1, false);
  perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);      
  
  imu.init();
  gps.init();

  initBehaviors();  
  Robot::setup();
}

void checkMotorFault(){
  if ( (digitalRead(pinMotorLeftFault)==LOW) || (digitalRead(pinMotorRightFault)==LOW) ){
    digitalWrite(pinMotorEnable, LOW);
    digitalWrite(pinMotorEnable, HIGH);
  }
}

 
int Mower::readSensor(char type){
  switch (type) {
// motors------------------------------------------------------------------------------------------------
    case SEN_MOTOR_MOW: return ADCMan.read(pinMotorMowSense); break;
    case SEN_MOTOR_RIGHT: checkMotorFault(); return ADCMan.read(pinMotorRightSense); break;
    case SEN_MOTOR_LEFT:  checkMotorFault(); return ADCMan.read(pinMotorLeftSense); break;
    //case SEN_MOTOR_MOW_RPM: break; // not used - rpm is upated via interrupt

// perimeter----------------------------------------------------------------------------------------------
    case SEN_PERIM_LEFT: return perimeter.getMagnitude(0); break;
    //case SEN_PERIM_RIGHT: return Perimeter.getMagnitude(1); break;
    
// battery------------------------------------------------------------------------------------------------
    case SEN_BAT_VOLTAGE: return ADCMan.read(pinBatteryVoltage); break;
    //case SEN_CHG_VOLTAGE: return((int)(((double)analogRead(pinChargeVoltage)) * batFactor)); break;
    //case SEN_CHG_CURRENT: return((int)(((double)analogRead(pinChargeCurrent)-chgSenseZero) * chgFactor)); break;
    
// buttons------------------------------------------------------------------------------------------------
    case SEN_BUTTON: return(digitalRead(pinButton)); break; 
    
//bumper----------------------------------------------------------------------------------------------------
    case SEN_BUMPER_RIGHT: return(digitalRead(pinBumperRight)); break;
    case SEN_BUMPER_LEFT: return(digitalRead(pinBumperLeft)); break;      
    
// sonar---------------------------------------------------------------------------------------------------
    //case SEN_SONAR_CENTER: return(readURM37(pinSonarCenterTrigger, pinSonarCenterEcho)); break;  
 //   case SEN_SONAR_CENTER: return(readHCSR04(pinSonarCenterTrigger, pinSonarCenterEcho)); break;  
    case SEN_SONAR_LEFT: return(readHCSR04(pinSonarLeftTrigger, pinSonarLeftEcho)); break; 
    case SEN_SONAR_RIGHT: return(readHCSR04(pinSonarRightTrigger, pinSonarRightEcho)); break;    
    //case SEN_LAWN_FRONT: return(measureLawnCapacity(pinLawnFrontSend, pinLawnFrontRecv)); break;    
    //case SEN_LAWN_BACK: return(measureLawnCapacity(pinLawnBackSend, pinLawnBackRecv)); break;    
    
// imu-------------------------------------------------------------------------------------------------------
    case SEN_IMU: float ypr[3]; imu.getEulerRad(ypr); imuYaw=ypr[0]; imuPitch=ypr[1]; imuRoll=ypr[2]; break;    
// rtc--------------------------------------------------------------------------------------------------------
    case SEN_RTC: readDS1307(datetime); break;
  }
  return 0;   
}

void Mower::setActuator(char type, int value){
  switch (type){
    case ACT_MOTOR_MOW: setL298N(pinMotorMowDir, pinMotorMowPWM, value); break;
    // normal direction
    case ACT_MOTOR_LEFT: setL298N(pinMotorLeftDir, pinMotorLeftPWM, value); break;
    case ACT_MOTOR_RIGHT: setL298N(pinMotorRightDir, pinMotorRightPWM, value); break;    
    // reverse direction
    //case ACT_MOTOR_LEFT: setL298N(pinMotorRightDir, pinMotorRightPWM, -value); break;
    //case ACT_MOTOR_RIGHT: setL298N(pinMotorLeftDir, pinMotorLeftPWM, -value); break;    
    case ACT_BUZZER: if (value == 0) noTone(pinBuzzer); else tone(pinBuzzer, value); break;
    case ACT_LED: digitalWrite(pinLED, value); break;    
    case ACT_USER_SW1: digitalWrite(pinUserSwitch1, value); break;     
    case ACT_USER_SW2: digitalWrite(pinUserSwitch2, value); break;     
    case ACT_USER_SW3: digitalWrite(pinUserSwitch3, value); break;         
    case ACT_RTC: setDS1307(datetime); break;
  }
}

void Mower::initBehaviors(void){
   
  /*memset(behaviors, 0, sizeof behaviors);
  behaviors[0] = new ManualBehavior(this);
  behaviors[1] = new ObstacleBehavior(this);
  behaviors[2] = new MowBehavior(this);
  behaviors[3] = new TrackBehavior(this);
  
  // manual behavior 
  // false, ...           not suppressed by manual behavior
  // false, ...           not suppressed by obstacle behavior
  // false, ...           not suppressed by mow behavior 
  // false, ...           not suppressed by track behavior
  
  boolean suppresses[BEHAVIOR_COUNT][BEHAVIOR_COUNT] = {
    { false, true,  true,  true  }, 
    { false, false, true,  true  }, 
    { false, false, false, true  }, 
    { false, false, false, false }  
  };
  
  initSuppresses(suppresses);    */
}

void Mower::configureBluetooth(boolean quick){
  BluetoothConfig bt;
  bt.setParams("Ardumower", 1234, PFOD_BAUDRATE, quick);  
}

