/*

default settings for motor, perimeter, bumper, odometry etc.

*/

#include "mower.h"
#include "NewPing.h"

#include <Arduino.h>
#include "due.h"
#include "drivers.h"
#include "i2c.h"
#include "pinman.h"
#include "buzzer.h"


Mower robot;


// ----------------------------------------------------------------------
// IMPORTANT:  choose your robot type and PCB version in 'mower.h' !
// ----------------------------------------------------------------------


Mower::Mower(){
  #if defined (ROBOT_ARDUMOWER)
    name = "Ardumower";
  #else
    name = "Mini";
  #endif
  
  // ------- wheel motors -----------------------------
  motorAccel                 = 1000;      // motor wheel acceleration - only functional when odometry is not in use (warning: do not set too low)
  #if defined (ROBOT_ARDUMOWER)
		motorPowerMax              = 75;        // motor wheel max power (Watt)		  
		motorSpeedMaxPwm           = 255;       // motor wheel max Pwm  (8-bit PWM=255, 10-bit PWM=1023)
		motorSpeedMaxRpm           = 25;        // motor wheel max RPM (WARNING: do not set too high, so there's still speed control when battery is low!)
		motorLeftPID.Kp            = 1.5;       // motor wheel PID controller
    motorLeftPID.Ki            = 0.29;
    motorLeftPID.Kd            = 0.25;
    motorZeroSettleTime        = 3000 ;     // how long (ms) to wait for motors to settle at zero speed
		motorReverseTime           = 1200;      // max. reverse time (ms)
		motorRollTimeMax           = 1500;      // max. roll time (ms)
		motorRollTimeMin           = 750;       // min. roll time (ms) should be smaller than motorRollTimeMax  
  #else // ROBOT_MINI		
		motorPowerMax              = 2.0;         // motor wheel max power (Watt)			
		motorSpeedMaxPwm           = 127;       // motor wheel max Pwm  (8-bit PWM=255, 10-bit PWM=1023)	  
		motorSpeedMaxRpm           = 50;        // motor wheel max RPM (WARNING: do not set too high, so there's still speed control when battery is low!)		
		motorLeftPID.Kp        		 = 0.2;       // motor wheel PID controller
    motorLeftPID.Ki            = 0.0;
    motorLeftPID.Kd            = 0.0;  
    motorZeroSettleTime        = 0 ;        // how long (ms) to wait for motors to settle at zero speed
		motorReverseTime           = 2200;      // max. reverse time (ms)
		motorRollTimeMax           = 2000;      // max. roll time (ms)
		motorRollTimeMin           = 750;       // min. roll time (ms) should be smaller than motorRollTimeMax  
  #endif		
  motorSenseRightScale       = ADC2voltage(1)*1905;   // ADC to right motor sense milliamp 
	motorSenseLeftScale        = ADC2voltage(1)*1905;   // ADC to left motor sense milliamp 
	motorPowerIgnoreTime       = 2000;      // time to ignore motor power (ms)  
  motorForwTimeMax           = 80000;     // max. forward time (ms) / timeout
  motorBiDirSpeedRatio1      = 0.3;       // bidir mow pattern speed ratio 1
  motorBiDirSpeedRatio2      = 0.92;      // bidir mow pattern speed ratio 2
    
  motorRightSwapDir          = 0;          // inverse right motor direction? 
  motorLeftSwapDir           = 0;          // inverse left motor direction?
  
  // ------ mower motor -------------------------------
  motorMowAccel              = 2000;       // motor mower acceleration (warning: do not set too low) 2000 seems to fit best considerating start time and power consumption 
  motorMowSpeedMaxPwm        = 255;        // motor mower max PWM
  motorMowPowerMax           = 75.0;       // motor mower max power (Watt)
  motorMowModulate           = 0;          // motor mower cutter modulation?
  motorMowRPMSet             = 3300;       // motor mower RPM (only for cutter modulation)
  motorMowSenseScale         = ADC2voltage(1)*1905;    // ADC to mower motor sense milliamp 
  motorMowPID.Kp             = 0.005;      // motor mower RPM PID controller
  motorMowPID.Ki             = 0.01;
  motorMowPID.Kd             = 0.01;
  
  //  ------ bumper (BumperDuino)-------------------------------
  bumperUse                  = 0;          // has bumpers?
  tiltUse                    = 0;          // use tilt-sensor?
  
  //  ------ drop -----------------------------------
  dropUse                    = 0;          // has drops?                                                                                              Dropsensor - Absturzsensor vorhanden ?
  dropcontact                = 1;          // contact 0-openers 1-closers                                                                              Dropsensor - Kontakt 0-Öffner - 1-Schließer betätigt gegen GND
  
  // ------ rain ------------------------------------
  rainUse                    = 0;          // use rain sensor?
  
  // ------ sonar ------------------------------------
  sonarUse                   = 0;          // use ultra sonic sensor? (WARNING: robot will slow down, if enabled but not connected!)
  sonarLeftUse               = 1;
  sonarRightUse              = 1;
  sonarCenterUse             = 0;
  sonarTriggerBelow          = 0;       // ultrasonic sensor trigger distance (0=off)
	sonarSlowBelow             = 100;     // ultrasonic sensor slow down distance
  
  // ------ perimeter ---------------------------------
  perimeterUse               = 0;          // use perimeter?    
  perimeterTriggerTimeout    = 0;          // perimeter trigger timeout when escaping from inside (ms)  
  perimeterOutRollTimeMax    = 2000;       // roll time max after perimeter out (ms)
  perimeterOutRollTimeMin    = 750;        // roll time min after perimeter out (ms)
  perimeterOutRevTime        = 2200;       // reverse time after perimeter out (ms)
  perimeterTrackRollTime     = 1500;       // roll time during perimeter tracking
  perimeterTrackRevTime      = 2200;       // reverse time during perimeter tracking
  #if defined (ROBOT_ARDUMOWER)
	  perimeterPID.Kp            = 16;       // perimeter PID controller
    perimeterPID.Ki            = 8;
    perimeterPID.Kd            = 0.8;  
	#else // ROBOT_MINI
		perimeterPID.Kp    = 24.0;  // perimeter PID controller
    perimeterPID.Ki    = 7.0;
    perimeterPID.Kd    = 9.0;
	#endif  
  
  trackingPerimeterTransitionTimeOut              = 2500;   // never<500 ms
  trackingErrorTimeOut                            = 10000;  // 0=disable
  trackingBlockInnerWheelWhilePerimeterStruggling = 1;
  MaxSpeedperiPwm = 200; // speed max in PWM while perimeter tracking
  // ------ lawn sensor --------------------------------
  lawnSensorUse     = 0;                   // use capacitive lawn Sensor
  
  // ------  IMU (compass/accel/gyro) ----------------------
  imuUse                     = 0;          // use IMU?
  imuCorrectDir              = 0;          // correct direction by compass?
  imuDirPID.Kp               = 5.0;        // direction PID controller
  imuDirPID.Ki               = 1.0;
  imuDirPID.Kd               = 1.0;    
  imuRollPID.Kp              = 0.8;        // roll PID controller
  imuRollPID.Ki              = 21;
  imuRollPID.Kd              = 0;  
  
  // ------ model R/C ------------------------------------
  remoteUse                  = 1;          // use model remote control (R/C)?
  
  // ------ battery -------------------------------------
  #if defined (ROBOT_ARDUMOWER)
    batMonitor                 = 1;          // monitor battery and charge voltage?
		batSwitchOffIfBelow        = 21.7;       // switch off battery if below voltage (Volt)
		batGoHomeIfBelow           = 23.7;       // drive home voltage (Volt)  	
		startChargingIfBelow       = 32.0;      // start charging if battery Voltage is below (99999=disabled)
		batFull                    = 29.4;      // battery reference Voltage (fully charged) PLEASE ADJUST IF USING A DIFFERENT BATTERY VOLTAGE! FOR a 12V SYSTEM TO 14.4V		
		batFullCurrent             = 0.1;       // current flowing when battery is fully charged	(amp), (-99999=disabled)	
	#else  // ROBOT_MINI
		batMonitor                 = 1;          // monitor battery and charge voltage?
		batSwitchOffIfBelow        = 5.0;       // switch off battery if below voltage (Volt)
		batGoHomeIfBelow           = 5.5;       // drive home voltage (Volt)  	
		startChargingIfBelow       = 8.0;      // start charging if battery Voltage is below (99999=disabled)
		batFull                    = 8.0;      // battery reference Voltage (fully charged) PLEASE ADJUST IF USING A DIFFERENT BATTERY VOLTAGE! FOR a 12V SYSTEM TO 14.4V		
		batFullCurrent             = -99999;       // current flowing when battery is fully charged	(amp), (-99999=disabled)	
	#endif   
	
	chargingTimeout            = 2147483647;  // safety timer for charging (ms) 12600000 = 3.5hrs  (2147483647=disabled)	
	
  #if defined (PCB_1_2)     // PCB 1.2	  
	  batSwitchOffIfIdle         = 0;          // switch off battery if idle (minutes, 0=off) 	
		batFactor                  = voltageDividerUges(47, 5.1, 1.0)*ADC2voltage(1)*10;   // ADC to battery voltage factor	*10
		batChgFactor               = voltageDividerUges(47, 5.1, 1.0)*ADC2voltage(1)*10;   // ADC to battery voltage factor *10	
		chgFactor                  = ADC2voltage(1)*10;        // ADC to charging current ampere factor  (see mower.h for macros)								  
  #elif defined (PCB_1_3)   // PCB 1.3
		batSwitchOffIfIdle         = 8;          // switch off battery if idle (minutes, 0=off) 
  	batFactor                  = voltageDividerUges(100, 10, 1.0)*ADC2voltage(1)*10;   // ADC to battery voltage factor *10
		batChgFactor               = voltageDividerUges(100, 10, 1.0)*ADC2voltage(1)*10;   // ADC to battery voltage factor *10
		chgFactor                  = ADC2voltage(1)*5;        // ADC to charging current ampere factor  (see mower.h for macros)								  
  #endif
  
	batChargingCurrentMax      = 1.6;       // maximum current your charger can devliver  
  
  // ------  charging station ---------------------------
  stationRevTime             = 1800;       // charge station reverse time (ms)
  stationRollTime            = 1000;       // charge station roll time (ms)
  stationForwTime            = 1500;       // charge station forward time (ms)
  stationCheckTime           = 1700;       // charge station reverse check time (ms)

  // ------ odometry ------------------------------------
  odometryUse                = 1;          // use odometry?    
  
	#if defined (ROBOT_ARDUMOWER)
	  odometryTicksPerRevolution = 1060;       // encoder ticks per one full resolution (without any divider)
		wheelDiameter              = 250;        // wheel diameter (mm)
		odometryWheelBaseCm        = 36;         // wheel-to-wheel distance (cm)
		odoLeftRightCorrection     = true;       // left-right correction for straight lines?
  #else  // ROBOT_MINI		
		odometryTicksPerRevolution = 20;      // encoder ticks per one full resolution
		wheelDiameter              = 70;        // wheel diameter (mm)
		odometryWheelBaseCm        = 14;         // wheel-to-wheel distance (cm)
		odoLeftRightCorrection     = false; 		 // left-right correction for straight lines?
	#endif
		
  #if defined (PCB_1_3)    
		#define DIVIDER_DIP_SWITCH  2             //  sets used PCB odometry divider (2=DIV/2, 4=DIV/4, 8=DIV/8, etc.) 
		odometryTicksPerRevolution /= DIVIDER_DIP_SWITCH;        // encoder ticks per one full resolution 
  #endif
  odometryTicksPerCm         = ((float)odometryTicksPerRevolution) / (((float)wheelDiameter)/10.0) / (2*3.1415);    // computes encoder ticks per cm (do not change)
  
  // ----- GPS -------------------------------------------
  gpsUse                     = 0;          // use GPS?
  stuckIfGpsSpeedBelow       = 0.2;        // if Gps speed is below given value the mower is stuck
  gpsSpeedIgnoreTime         = 5000;       // how long gpsSpeed is ignored when robot switches into a new STATE (in ms)

  // ----- other -----------------------------------------
  buttonUse                  = 1;          // has digital ON/OFF button?

  // ----- user-defined switch ---------------------------
  userSwitch1                = 0;          // user-defined switch 1 (default value)
  userSwitch2                = 0;          // user-defined switch 2 (default value)
  userSwitch3                = 0;          // user-defined switch 3 (default value)

  // ----- timer -----------------------------------------
  timerUse                   = 0;          // use RTC and timer?

  // ----- bluetooth -------------------------------------
  bluetoothUse               = 1;          // use Bluetooth module?  (WARNING: if enabled, you cannot use ESP8266)

  // ----- esp8266 ---------------------------------------
  esp8266Use                 = 0;          // use ESP8266 Wifi module? (WARNING: if enabled, you cannot use Bluetooth)
  esp8266ConfigString        = "123test321";

  // ------ mower stats-------------------------------------------  
  statsOverride              = false;      // if set to true mower stats are overwritten - be careful
  statsMowTimeMinutesTotal   = 300;
  statsBatteryChargingCounterTotal  = 11;
  statsBatteryChargingCapacityTotal = 30000;
  // -----------configuration end-------------------------------------
}


// ------ code section (do not change) --------------------------------


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
// mower motor speed sensor interrupt
// NOTE: when choosing a higher perimeter sample rate (38 kHz) and using odometry interrupts, 
// the Arduino Mega cannot handle all ADC interrupts anymore - the result will be a 'noisy'
// perimeter filter output (mag value) which disappears when disabling odometry interrupts.
// SOLUTION: allow odometry interrupt handler nesting (see odometry interrupt function)
// http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
#ifdef __AVR__
  
	volatile byte oldOdoPins = 0;
  // Arduino Mega odometry interrupts
  ISR(PCINT2_vect, ISR_NOBLOCK)
  {				
		const byte actPins = PINK;                				// read register PINK
		const byte setPins = (oldOdoPins ^ actPins);
		unsigned long time = millis();    
    if ((setPins & 0b00010000) && (actPins & 0b00010000))               				// pin left is RISING
    {			
			if (robot.motorLeftPWMCurr >= 0)						// forward
        robot.odometryLeft++;
      else
        robot.odometryLeft--;									// backward
    }
    if ((setPins & 0b01000000) && (actPins & 0b01000000))                  				// pin right is RISING
    {			
			if (robot.motorRightPWMCurr >= 0)
        robot.odometryRight++;								// forward
      else
        robot.odometryRight--;								// backward
    }      
		oldOdoPins = actPins;
  }

#else
  
  // Arduino Due odometry interrupts
  void OdometryRightInt(){			
			if (robot.motorRightPWMCurr >= 0)
        robot.odometryRight++;								// forward
      else
        robot.odometryRight--;								// backward
  }   

	void OdometryLeftInt(){			
			if (robot.motorLeftPWMCurr >= 0)						// forward
        robot.odometryLeft++;
      else
        robot.odometryLeft--;									// backward
  }	

#endif

// mower motor speed sensor interrupt
//void rpm_interrupt(){
//}

NewPing NewSonarLeft(pinSonarLeftTrigger, pinSonarLeftEcho, 110);
NewPing NewSonarRight(pinSonarRightTrigger, pinSonarRightEcho, 110);
NewPing NewSonarCenter(pinSonarCenterTrigger, pinSonarCenterEcho, 110);


// WARNING: never use 'Serial' in the Ardumower code - use 'Console' instead
// (required so we can use Arduino Due native port)

void Mower::setup(){
	PinMan.begin();    
  // keep battery switched ON (keep this at system start!)
  pinMode(pinBatterySwitch, OUTPUT);
  digitalWrite(pinBatterySwitch, HIGH);

  Buzzer.begin();
	Console.begin(CONSOLE_BAUDRATE);  
	I2Creset();	
  Wire.begin();            	
	ADCMan.init();
  Console.println("SETUP");
  
  // LED, buzzer, battery
  pinMode(pinLED, OUTPUT);    
  pinMode(pinBuzzer, OUTPUT);    
  digitalWrite(pinBuzzer,0);    
  pinMode(pinBatteryVoltage, INPUT);        
  pinMode(pinChargeCurrent, INPUT);          
  pinMode(pinChargeVoltage, INPUT);            
  pinMode(pinChargeRelay, OUTPUT);
  setActuator(ACT_CHGRELAY, 0);
  
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
  pinMode(pinMotorMowEnable, OUTPUT);
  digitalWrite(pinMotorMowEnable, HIGH);  
  pinMode(pinMotorMowFault, INPUT);      
    
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

  // BumperDuino
  pinMode(pinBumperLeft, INPUT);
  pinMode(pinBumperLeft, INPUT_PULLUP);
  pinMode(pinBumperRight, INPUT);
  pinMode(pinBumperRight, INPUT_PULLUP);
  pinMode(pinTilt, INPUT);
  pinMode(pinTilt, INPUT_PULLUP);
 
 // drops
  pinMode(pinDropLeft, INPUT);                                                                                                         // Dropsensor - Absturzsensor - Deklariert als Eingang
  pinMode(pinDropLeft, INPUT_PULLUP);                                                                                                  // Dropsensor - Absturzsensor - Intern Pullab Widerstand aktiviert (Auslösung erfolgt gegen GND)
  pinMode(pinDropRight, INPUT);                                                                                                        // Dropsensor - Absturzsensor - Deklariert als Eingang 
  pinMode(pinDropRight, INPUT_PULLUP);                                                                                                 // Dropsensor - Absturzsensor - Intern Pullab Widerstand aktiviert (Auslösung erfolgt gegen GND)
  
  // sonar
  pinMode(pinSonarCenterTrigger, OUTPUT); 
  pinMode(pinSonarCenterEcho, INPUT); 
  pinMode(pinSonarLeftTrigger, OUTPUT); 
  pinMode(pinSonarLeftEcho, INPUT); 
  pinMode(pinSonarRightTrigger, OUTPUT); 
  pinMode(pinSonarRightEcho, INPUT); 
  
  // rain
  pinMode(pinRain, INPUT);
        
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
  
  // other
  pinMode(pinVoltageMeasurement, INPUT);  
  
    
  // ADC  
  ADCMan.setCapture(pinChargeCurrent, 1, true);//Aktivierung des LaddeStrom Pins beim ADC-Managers      
  ADCMan.setCapture(pinMotorMowSense, 1, true);
  ADCMan.setCapture(pinMotorLeftSense, 1, true);
  ADCMan.setCapture(pinMotorRightSense, 1, true);
  ADCMan.setCapture(pinBatteryVoltage, 1, false);
  ADCMan.setCapture(pinChargeVoltage, 1, false);  
  ADCMan.setCapture(pinVoltageMeasurement, 1, false);    
  perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);      
    
  imu.init();
	  
  gps.init();

  Robot::setup();  

  if (esp8266Use) {
    Console.println(F("Sending ESP8266 Config"));
    ESP8266port.begin(ESP8266_BAUDRATE);
    ESP8266port.println(esp8266ConfigString);
    ESP8266port.flush();
    ESP8266port.end();
    rc.initSerial(&ESP8266port, ESP8266_BAUDRATE);
  } else if (bluetoothUse) {
    rc.initSerial(&Bluetooth, BLUETOOTH_BAUDRATE);
  }

//-------------------------------------------------------------------------
// enable interrupts
//-------------------------------------------------------------------------
#ifdef __AVR__

	//-------------------------------------------------------------------------
	// Switch
	//-------------------------------------------------------------------------
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT1);

	//-------------------------------------------------------------------------
	// R/C
	//-------------------------------------------------------------------------
	PCICR |= (1<<PCIE0);
	if (remoteUse)
	{
		PCMSK0 |= (1<<PCINT4);
		PCMSK0 |= (1<<PCINT5);
		PCMSK0 |= (1<<PCINT6);
	}
 
	//-------------------------------------------------------------------------    
	// odometry
	//-------------------------------------------------------------------------
	// Wenn odometryUse == 1 dann:
	// PCMSK2, PCINT20, HIGH			-> für links
	// PCMSK2, PCINT22, HIGH			-> für rechts
	//
	// Wenn twoWayOdo == 1 dann:
	// PCMSK2, PCINT21, HIGH
	// PCMSK2, PCINT23, HIGH
	if (odometryUse)
	{ 
	  PCICR |= (1<<PCIE2);
	  PCMSK2 |= (1<<PCINT20);
	  PCMSK2 |= (1<<PCINT22);	  
	}
		
  //-------------------------------------------------------------------------	
  // mower motor speed sensor interrupt
	//-------------------------------------------------------------------------
  if (motorMowModulate)
	{
	  //PCICR |= (1<<PCIE2);
	  //PCMSK2 |= (1<<PCINT19);
	}
#else
  // Due interrupts
  // ODO
  attachInterrupt(pinOdometryLeft, OdometryLeftInt, RISING);    
  attachInterrupt(pinOdometryRight, OdometryRightInt, RISING);  
	PinMan.setDebounce(pinOdometryLeft, 100);  // reject spikes shorter than usecs on pin
	PinMan.setDebounce(pinOdometryRight, 100);  // reject spikes shorter than usecs on pin	      
    
	// RC
  attachInterrupt(pinRemoteSpeed, PCINT0_vect, CHANGE);            
	attachInterrupt(pinRemoteSteer, PCINT0_vect, CHANGE);            
	attachInterrupt(pinRemoteMow, PCINT0_vect, CHANGE);   
	//Switch
	attachInterrupt(pinRemoteSwitch, PCINT0_vect, CHANGE);       
	
	//Motor Mow RPM	
	//attachInterrupt(pinMotorMowRpm, PCINT2_vect, CHANGE);    
#endif   
  
}

void checkMotorFault(){
  if (digitalRead(pinMotorLeftFault)==LOW){
    robot.addErrorCounter(ERR_MOTOR_LEFT);
    //Console.println(F("Error: motor left fault"));
    robot.setNextState(STATE_ERROR, 0);
    //digitalWrite(pinMotorEnable, LOW);
    //digitalWrite(pinMotorEnable, HIGH);
  }
  if  (digitalRead(pinMotorRightFault)==LOW){
    robot.addErrorCounter(ERR_MOTOR_RIGHT);
    //Console.println(F("Error: motor right fault"));
    robot.setNextState(STATE_ERROR, 0);
    //digitalWrite(pinMotorEnable, LOW);
    //digitalWrite(pinMotorEnable, HIGH);
  }
  if (digitalRead(pinMotorMowFault)==LOW){  
    robot.addErrorCounter(ERR_MOTOR_MOW);
    //Console.println(F("Error: motor mow fault"));
    robot.setNextState(STATE_ERROR, 0);
    //digitalWrite(pinMotorMowEnable, LOW);
    //digitalWrite(pinMotorMowEnable, HIGH);
  }
}

void Mower::resetMotorFault(){
  if (digitalRead(pinMotorLeftFault)==LOW){
    digitalWrite(pinMotorEnable, LOW);
    digitalWrite(pinMotorEnable, HIGH);
    //Console.println(F("Reset motor left fault"));
}
  if  (digitalRead(pinMotorRightFault)==LOW){
    digitalWrite(pinMotorEnable, LOW);
    digitalWrite(pinMotorEnable, HIGH);
    //Console.println(F("Reset motor right fault"));
}
  if (digitalRead(pinMotorMowFault)==LOW){  
    digitalWrite(pinMotorMowEnable, LOW);
    digitalWrite(pinMotorMowEnable, HIGH);
    //Console.println(F("Reset motor mow fault"));
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
    case SEN_BAT_VOLTAGE: ADCMan.read(pinVoltageMeasurement);  return ADCMan.read(pinBatteryVoltage); break;
    case SEN_CHG_VOLTAGE: return ADCMan.read(pinChargeVoltage); break;
    //case SEN_CHG_VOLTAGE: return((int)(((double)analogRead(pinChargeVoltage)) * batFactor)); break;
    case SEN_CHG_CURRENT: return ADCMan.read(pinChargeCurrent); break;
    
// buttons------------------------------------------------------------------------------------------------
    case SEN_BUTTON: return(digitalRead(pinButton)); break; 
    
//bumper----------------------------------------------------------------------------------------------------
    case SEN_BUMPER_RIGHT: return(digitalRead(pinBumperRight)); break;
    case SEN_BUMPER_LEFT: return(digitalRead(pinBumperLeft)); break;      

//tilt----------------------------------------------------------------------------------------------------
    case SEN_TILT: return(digitalRead(pinTilt)); break;      
    
//drop----------------------------------------------------------------------------------------------------
    case SEN_DROP_RIGHT: return(digitalRead(pinDropRight)); break;                                                                                      // Dropsensor - Absturzsensor
    case SEN_DROP_LEFT: return(digitalRead(pinDropLeft)); break;                                                                                        // Dropsensor - Absturzsensor

// sonar---------------------------------------------------------------------------------------------------
    //case SEN_SONAR_CENTER: return(readURM37(pinSonarCenterTrigger, pinSonarCenterEcho)); break;  
    //case SEN_SONAR_CENTER: return(readHCSR04(pinSonarCenterTrigger, pinSonarCenterEcho)); break;
    //case SEN_SONAR_LEFT: return(readHCSR04(pinSonarLeftTrigger, pinSonarLeftEcho)); break;
    //case SEN_SONAR_RIGHT: return(readHCSR04(pinSonarRightTrigger, pinSonarRightEcho)); break;
    
    case SEN_SONAR_CENTER: return(NewSonarCenter.ping_cm()); break;
    case SEN_SONAR_LEFT: return(NewSonarLeft.ping_cm()); break;
    case SEN_SONAR_RIGHT: return(NewSonarRight.ping_cm()); break;    
    
    // case SEN_LAWN_FRONT: return(measureLawnCapacity(pinLawnFrontSend, pinLawnFrontRecv)); break;    
    //case SEN_LAWN_BACK: return(measureLawnCapacity(pinLawnBackSend, pinLawnBackRecv)); break;    
    
// imu-------------------------------------------------------------------------------------------------------
    //case SEN_IMU: imuYaw=imu.ypr.yaw; imuPitch=imu.ypr.pitch; imuRoll=imu.ypr.roll; break;    
// rtc--------------------------------------------------------------------------------------------------------
    case SEN_RTC: 
      if (!readDS1307(datetime)) {
        //Console.println("RTC data error!");        
        addErrorCounter(ERR_RTC_DATA);         
        setNextState(STATE_ERROR, 0);       
      }
      break;
// rain--------------------------------------------------------------------------------------------------------
    case SEN_RAIN: if (digitalRead(pinRain)==LOW) return 1; break;
 
  }
  return 0;   
}

void Mower::setActuator(char type, int value){
  switch (type){
    case ACT_MOTOR_MOW: setMC33926(pinMotorMowDir, pinMotorMowPWM, value); break;// Motortreiber einstellung - bei Bedarf ändern z.B setL298N auf setMC33926
    case ACT_MOTOR_LEFT: setMC33926(pinMotorLeftDir, pinMotorLeftPWM, value); break;//                                                                  Motortreiber einstellung - bei Bedarf ändern z.B setL298N auf setMC33926
    case ACT_MOTOR_RIGHT: setMC33926(pinMotorRightDir, pinMotorRightPWM, value); break; //                                                              Motortreiber einstellung - bei Bedarf ändern z.B setL298N auf setMC33926
    case ACT_BUZZER: if (value == 0) Buzzer.noTone(); else Buzzer.tone(value); break;
    case ACT_LED: digitalWrite(pinLED, value); break;    
    case ACT_USER_SW1: digitalWrite(pinUserSwitch1, value); break;     
    case ACT_USER_SW2: digitalWrite(pinUserSwitch2, value); break;     
    case ACT_USER_SW3: digitalWrite(pinUserSwitch3, value); break;         
    case ACT_RTC:  
      if (!setDS1307(datetime)) {
        //Console.println("RTC comm error!");
        addErrorCounter(ERR_RTC_COMM); 
        setNextState(STATE_ERROR, 0);       
      }
      break;
    case ACT_CHGRELAY: digitalWrite(pinChargeRelay, value); break;
    //case ACT_CHGRELAY: digitalWrite(pinChargeRelay, !value); break;
    case ACT_BATTERY_SW: digitalWrite(pinBatterySwitch, value); break;
  }
}

void Mower::configureBluetooth(boolean quick){
  BluetoothConfig bt;
  bt.setParams(name, BLUETOOTH_PIN, BLUETOOTH_BAUDRATE, quick);
}


