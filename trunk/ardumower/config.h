// Ardumower Chassis Kit 1.0 - robot configuration (Ardumower electronics)
// Copyright (c) 2014 by Alexander Grau
  
// (Arduino Mega)

// ------ configuration --------------------------------------------------
char configName[] = "kit10";
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
#define pinOdometryLeft 49         // left odometry sensor
#define pinOdometryLeft2 45        // left odometry sensor (optional two-wire)
#define pinOdometryRight 44        // right odometry sensor
#define pinOdometryRight2 38       // right odometry sensor (optional two-wire)
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
#define USE_PFOD 1                // use support for pfod app ?

// ------- wheel motors -----------------------------
double motorAccel       = 0.005;  // motor wheel acceleration (warning: do not set too high)
int motorSpeedMax       = 255;   // motor wheel max PWM  (8-bit PWM=255, 10-bit PWM=1023)
int motorCurrentMax     = 930;    // motor wheel max current (mA)
int motorSenseRightZero = 0;     // motor right sense zero point (mA=(ADC-zero)/scale)
double motorSenseRightScale = 9.300595; // motor right sense scale (mA=(ADC-zero)/scale)
int motorSenseLeftZero  = 0;     // motor left sense zero point (mA=(ADC-zero)/scale)
double motorSenseLeftScale = 9.300595; // motor left sense scale  (mA=(ADC-zero)/scale)
int motorRollTimeMax    = 4000;  // max. roll time (ms)
int motorReverseTime    = 1500;  // max. reverse time (ms)
long motorForwTimeMax   = 60000; // max. forward time (ms) / timeout
double motorBiDirSpeedRatio1 = 0.3;   // bidir mow pattern speed ratio 1
double motorBiDirSpeedRatio2 = 0.92;   // bidir mow pattern speed ratio 2
// ------ mower motor -------------------------------
double motorMowAccel       = 0.005;  // motor mower acceleration (warning: do not set too high)
int motorMowSpeedMax   = 255;    // motor mower max PWM
int motorMowCurrentMax = 558;     // motor mower max current (mA)
char motorMowModulate  = 0;      // motor mower cutter modulation?
int motorMowRPM        = 3300;   // motor mower RPM (only for cutter modulation)
int motorMowSenseZero  = 0;    // motor mower sense zero point (mA=(ADC-zero)/scale)
double motorMowSenseScale = 9.300595; // motor mower sense scale (mA=(ADC-zero)/scale)
pid_params_t motorMowPid  = {0.005, 0.01, 0.01};    // motor mower RPM PID controller
// ------ bumper -----------------------------------
char bumperUse         = 0;      // has bumpers? 
// ------ sonar ------------------------------------
char sonarUse          = 1;      // use ultra sonic sensor?
int  sonarTriggerBelow = 1600;    // ultrasonic sensor trigger distance
// ------ perimeter ---------------------------------
char perimeterUse       = 1;      // use perimeter?
int  perimeterTrackRollTime  = 3000;   // perimter tracking roll time (ms)
int  perimeterTrackRevTime   = 2000;   // perimter tracking reverse time (ms)
pid_params_t perimeterPid  = {4.0, 8.0, 8.0};    // perimeter PID controller
// ------ lawn sensor --------------------------------
char lawnSensorUse     = 0;       // use capacitive Sensor
// ------  IMU (compass/accel/gyro) ----------------------
char imuUse            = 0;       // use IMU? 
char imuCorrectDir     = 0;       // correct direction by compass?
pid_params_t imuDirPid  = {5.0, 1.0, 1.0};    // direction PID controller
pid_params_t imuRollPid  = {0.8, 21, 0};    // roll PID controller
// ------ model R/C ------------------------------------
char remoteUse         = 1;       // use model remote control (R/C)?
// ------ battery -------------------------------------
char batMonitor = 0;              // monitor battery and charge voltage?
double batGoHomeIfBelow = 22;     // drive home voltage (Volt)
double batSwitchOffIfBelow = 21;  // switch off if below voltage (Volt)
double batFactor       = 4.7;     // battery conversion factor
int  chgSenseZero      = 0;       // charge current sense zero point
double chgFactor       = 2.7;     // charge current conversion factor
// ------  charging station ---------------------------
int stationRevTime     = 4000;    // charge station reverse time (ms)
int stationRollTime    = 3000;    // charge station roll time (ms)
int stationForwTime    = 2000;    // charge station forward time (ms)
// ------ odometry ------------------------------------
char odometryUse       = 0;       // use odometry?
double odometryTicksPerCm = 1.519;  // encoder ticks per cm
double odometryWheelBaseCm = 30;    // wheel-to-wheel distance (cm)
// ----- GPS -------------------------------------------
char gpsUse            = 0;       // use GPS?
// ----- other -----------------------------------------
char buttonUse         = 1;       // has digital ON/OFF button?
// ----- user-defined switch ---------------------------
char userSwitch1       = 0;       // user-defined switch 1 (default value)
char userSwitch2       = 0;       // user-defined switch 2 (default value)
char userSwitch3       = 0;       // user-defined switch 3 (default value)
// ----- timer -----------------------------------------
char timerUse          = 0;       // use timer?
// ------ configuration end -------------------------------------------


// remote control (RC) ppm signal change interrupt
ISR(PCINT0_vect)
{   
  unsigned long timeMicros = micros();
  boolean remoteSpeedState = digitalRead(pinRemoteSpeed);
  boolean remoteSteerState = digitalRead(pinRemoteSteer);
  boolean remoteMowState = digitalRead(pinRemoteMow);    
  boolean remoteSwitchState = digitalRead(pinRemoteSwitch);    
  setRemotePPMState(timeMicros, remoteSpeedState, remoteSteerState, remoteMowState, remoteSwitchState);    
}

// odometry signal change interrupt
ISR(PCINT2_vect)
{   
  unsigned long timeMicros = micros();
  boolean odometryLeftState = digitalRead(pinOdometryLeft);
  boolean odometryLeftState2 = digitalRead(pinOdometryLeft2);
  boolean odometryRightState = digitalRead(pinOdometryRight);  
  boolean odometryRightState2 = digitalRead(pinOdometryRight2);  
  setOdometryState(timeMicros, odometryLeftState, odometryRightState, odometryLeftState2, odometryRightState2);
}


// mower motor speed sensor interrupt
void rpm_interrupt()
{
  boolean motorMowRpmState = digitalRead(pinMotorMowRpm);
  setMotorMowRPMState(motorMowRpmState);
}

void config(){
  // i2c -- turn off internal pull-ups (and use external pull-ups)
  //digitalWrite(SDA, 0);  
  //digitalWrite(SCL, 0);
  
  // LED, buzzer, battery
  pinMode(pinLED, OUTPUT);    
  pinMode(pinBuzzer, OUTPUT);    
  pinMode(pinBatteryVoltage, INPUT);        
  pinMode(pinChargeCurrent, INPUT);          
  pinMode(pinChargeVoltage, INPUT);            
  
  // motors
  pinMode(pinMotorLeftPWM, OUTPUT);
  pinMode(pinMotorLeftDir, OUTPUT); 
  pinMode(pinMotorRightPWM, OUTPUT);
  pinMode(pinMotorRightDir, OUTPUT); 
  pinMode(pinMotorMowDir, OUTPUT); 
  pinMode(pinMotorMowPWM, OUTPUT);     
  pinMode(pinMotorLeftSense, INPUT);     
  pinMode(pinMotorRightSense, INPUT);     
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
      
  // mower motor speed sensor interrupt
  attachInterrupt(5, rpm_interrupt, CHANGE);
  
  // R/C
  pinMode(pinRemoteMow, INPUT);
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT); 
  pinMode(pinRemoteSwitch, INPUT);       
  #ifdef __AVR__
    PCICR |= (1<<PCIE0);
    PCMSK0 |= (1<<PCINT4);
    PCMSK0 |= (1<<PCINT5);
    PCMSK0 |= (1<<PCINT6);
    PCMSK0 |= (1<<PCINT1);
  #endif   
  
  // odometry
  pinMode(pinOdometryLeft, INPUT_PULLUP);  
  pinMode(pinOdometryLeft2, INPUT_PULLUP);    
  pinMode(pinOdometryRight, INPUT_PULLUP);
  pinMode(pinOdometryRight2, INPUT_PULLUP);  
  #ifdef __AVR__  
    PCICR |= (1<<PCIE2);
    PCMSK2 |= (1<<PCINT20);
    PCMSK2 |= (1<<PCINT21);  
    PCMSK2 |= (1<<PCINT22);
    PCMSK2 |= (1<<PCINT23);      
  #endif
  
  // user switches
  pinMode(pinUserSwitch1, OUTPUT);
  pinMode(pinUserSwitch2, OUTPUT);
  pinMode(pinUserSwitch3, OUTPUT);   
  
  // ADC
  ADCMan.init();
  ADCMan.setCapture(pinMotorMowSense, 1);
  ADCMan.setCapture(pinMotorLeftSense, 1);
  ADCMan.setCapture(pinMotorRightSense, 1);
  Perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);        
}


int readSensor(char type){
  float ypr[3]; // yaw pitch roll
  short comxyz[3]; // raw com
  
  switch (type) {
//    case SEN_MOTOR_MOW: return( (int)(((double)analogRead(pinMotorMowSense)-motorMowSenseZero) * motorMowSenseScale) ); break;
    case SEN_MOTOR_MOW: return(ADCMan.read(pinMotorMowSense)-motorMowSenseZero); break;    
    case SEN_PERIM_LEFT: return Perimeter.getMagnitude(0); break;
    //case SEN_PERIM_RIGHT: return Perimeter.getMagnitude(1); break;  
    //case SEN_BAT_VOLTAGE: return (int)(((double)analogRead(pinBatteryVoltage)) * batFactor); break;
    //case SEN_CHG_VOLTAGE: return((int)(((double)analogRead(pinChargeVoltage)) * batFactor)); break;
    //case SEN_CHG_CURRENT: return((int)(((double)analogRead(pinChargeCurrent)-chgSenseZero) * chgFactor)); break;
    case SEN_BUTTON: return(digitalRead(pinButton)); break;    
//    case SEN_SONAR_CENTER: return(readURM37(pinSonarCenterTrigger, pinSonarCenterEcho)); break;  
    case SEN_SONAR_CENTER: return(readHCSR04(pinSonarCenterTrigger, pinSonarCenterEcho)); break;  
//    case SEN_SONAR_LEFT: return(readHCSR04(pinSonarLeftTrigger, pinSonarLeftEcho)); break; 
//    case SEN_SONAR_RIGHT: return(readHCSR04(pinSonarRightTrigger, pinSonarRightEcho)); break;    
    case SEN_LAWN_FRONT: return(measureLawnCapacity(pinLawnFrontSend, pinLawnFrontRecv)); break;    
    case SEN_LAWN_BACK: return(measureLawnCapacity(pinLawnBackSend, pinLawnBackRecv)); break;    
    /*case SEN_IMU: if (readIMU(ypr, accMin, accMax, comxyz)) 
      { imuYaw=ypr[0]; imuPitch=ypr[1]; imuRoll=ypr[2]; 
        imuComX=comxyz[0]; imuComY=comxyz[1]; imuComZ=comxyz[2]; } break;    */
    case SEN_MOTOR_MOW_RPM: break; // not used - rpm is upated via interrupt
    // reverse direction    
    //case SEN_MOTOR_RIGHT: return( (int)(((double)analogRead(pinMotorRightSense)-motorSenseRightZero) * motorSenseRightScale) ); break;
    //case SEN_MOTOR_LEFT: return( (int)(((double)analogRead(pinMotorLeftSense)-motorSenseLeftZero) * motorSenseLeftScale) ); break;  
    // normal direction output in A for Mc39
//    case SEN_MOTOR_RIGHT: return((analogRead(pinMotorRightSense)-motorSenseRightZero)*5/525); break;
 //   case SEN_MOTOR_RIGHT: return((int)(((double)analogRead(pinMotorRightSense)-motorSenseRightZero) * 0.0093)); break;
//    case SEN_MOTOR_LEFT: return((analogRead(pinMotorLeftSense)-motorSenseLeftZero)*5/525); break;
//    case SEN_MOTOR_LEFT: return((int)(((double)analogRead(pinMotorLeftSense)-motorSenseLeftZero) * 0.0093)); break;
    // normal direction
    case SEN_MOTOR_LEFT: return(ADCMan.read(pinMotorLeftSense)-motorSenseLeftZero); break;
    case SEN_MOTOR_RIGHT: return(ADCMan.read(pinMotorRightSense)-motorSenseRightZero); break;        
    //case SEN_MOTOR_RIGHT: return(analogRead(pinMotorRightSense)-motorSenseRightZero); break;
    //case SEN_MOTOR_LEFT: return(analogRead(pinMotorLeftSense)-motorSenseLeftZero); break;
    case SEN_RTC: readDS1307(datetime); break;
    case SEN_BUMPER_RIGHT: return(digitalRead(pinBumperRight)); break;
    case SEN_BUMPER_LEFT: return(digitalRead(pinBumperLeft)); break;      
  }
  return 0;
}


void setActuator(char type, int value){
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


