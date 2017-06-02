/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  
  Private-use only! (you need to ask for a commercial-use)
 
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
  
  Private-use only! (you need to ask for a commercial-use)

*/

#ifndef MOWER_H
#define MOWER_H

#include <Arduino.h>
#include "robot.h"

#include "drivers.h"
#include "bt.h"


/* Ardumower Chassis Kit 1.0 - robot configuration (Ardumower electronics, Arduino Mega/Due) 
   http://wiki.ardumower.de/index.php?title=Ardumower_chassis
   
   Requires: Ardumower PCB v0.5/1.2/1.3  ( https://www.marotronics.de/Ardumower-Board-Prototyp ) 
   
*/
   

// ------- NOTE: Choose one Ardumower PCB revision (1.2, 1.3 etc.) ------------------
#define PCB_1_2    
//#define PCB_1_3    
// -----------------------------------------------------------------------------------


#ifdef __AVR__
  #define IOREF 5.0  // I/O reference voltage 
#else 
	#define IOREF 3.3   // I/O reference voltage 
#endif
		


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
                                    
#define pinMotorMowPWM 2           // M1_IN1 mower motor PWM pin (if using MOSFET, use this pin)
#define pinMotorMowDir 29          // M1_IN2 mower motor Dir pin (if using MOSFET, keep unconnected)
#define pinMotorMowSense A3        // M1_FB  mower motor current sense  
#define pinMotorMowFault 26        // M1_SF  mower motor fault   (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowEnable 28       // EN mower motor enable      (if using MOSFET/L298N, keep unconnected)
#define pinMotorMowRpm A11
    
#define pinBumperLeft 39           // bumper pins
#define pinBumperRight 38

#define pinDropLeft 45           // drop pins                                                                                          Dropsensor - Absturzsensor
#define pinDropRight 23          // drop pins                                                                                          Dropsensor - Absturzsensor

#define pinSonarCenterTrigger 24   // ultrasonic sensor pins
#define pinSonarCenterEcho 22
#define pinSonarRightTrigger 30    
#define pinSonarRightEcho 32
#define pinSonarLeftTrigger 34         
#define pinSonarLeftEcho 36
#define pinPerimeterRight A4       // perimeter
#define pinPerimeterLeft A5

#define pinGreenLED 6              // DuoLED green
#define pinRedLED 7                // DuoLED red
#define pinLED 13                  // LED
#define pinBuzzer 53               // Buzzer
#define pinTilt 35                 // Tilt sensor (BumperDuino)
#define pinButton 51               // digital ON/OFF button
#define pinBatteryVoltage A2       // battery voltage sensor
#define pinBatterySwitch 4         // battery-OFF switch   
#define pinChargeVoltage A9        // charging voltage sensor
#define pinChargeCurrent A8        // charge current sensor
#define pinChargeRelay 50          // charge relay
#define pinRemoteMow 12            // remote control mower motor
#define pinRemoteSteer 11          // remote control steering 
#define pinRemoteSpeed 10          // remote control speed
#define pinRemoteSwitch 52         // remote control switch
#define pinVoltageMeasurement A7   // test pin for your own voltage measurements
#ifdef __AVR__
  #define pinOdometryLeft A12      // left odometry sensor
  #define pinOdometryLeft2 A13     // left odometry sensor (optional two-wire)
  #define pinOdometryRight A14     // right odometry sensor 
  #define pinOdometryRight2 A15    // right odometry sensor (optional two-wire)  
#else
  #define pinOdometryLeft DAC0     // left odometry sensor
  #define pinOdometryLeft2 DAC1    // left odometry sensor (optional two-wire)
  #define pinOdometryRight CANRX   // right odometry sensor  
  #define pinOdometryRight2 CANTX  // right odometry sensor (optional two-wire)  
#endif
#define pinLawnFrontRecv 40        // lawn sensor front receive
#define pinLawnFrontSend 41        // lawn sensor front sender 
#define pinLawnBackRecv 42         // lawn sensor back receive
#define pinLawnBackSend 43         // lawn sensor back sender 
#define pinUserSwitch1 46          // user-defined switch 1
#define pinUserSwitch2 47          // user-defined switch 2
#define pinUserSwitch3 48          // user-defined switch 3
#define pinRain 44                 // rain sensor
// IMU (compass/gyro/accel): I2C  (SCL, SDA) 
// Bluetooth: Serial2 (TX2, RX2)
// GPS: Serial3 (TX3, RX3) 

// ------- baudrates---------------------------------
#define CONSOLE_BAUDRATE    19200       // baudrate used for console
#define BLUETOOTH_BAUDRATE  19200       // baudrate used for communication with Bluetooth module (Ardumower default)
#define ESP8266_BAUDRATE    115200      // baudrate used for communication with esp8266 Wifi module
#define BLUETOOTH_PIN       1234


// ------ used serial ports for console, Bluetooth, ESP8266 -----------------------------
#ifdef __AVR__
  // Arduino Mega
  #define Console Serial
  #define ESP8266port Serial1
  #define Bluetooth Serial2
#else 
  // Arduino Due  
   // Due has two serial ports: Native (SerialUSB) and Programming (Serial) - we want to use 'SerialUSB' for 'Console'
  #define Console Serial
  #define ESP8266port Serial1
  #define Bluetooth Serial2  // Ardumower default
#endif

// ------- ultrasonic config ---------------------------------------------------------
// ultrasonic sensor max echo time (WARNING: do not set too high, it consumes CPU time!)
#define MAX_ECHO_TIME 3000     
#define MIN_ECHO_TIME 300    
#define NO_ECHO 0

// ------- I2C addresses --------------------------------------------------------------
#define DS1307_ADDRESS B1101000

// ---- choose only one perimeter signal code ----
#define SIGCODE_1  // Ardumower default perimeter signal
//#define SIGCODE_2  // Ardumower alternative perimeter signal
//#define SIGCODE_3  // Ardumower alternative perimeter signal


/*
  Ardumower robot chassis
*/

class Mower : public Robot
{
  public:
    Mower();  
    virtual void setup(void);
    virtual void resetMotorFault();
    virtual int readSensor(char type);
    virtual void setActuator(char type, int value);
    virtual void configureBluetooth(boolean quick);
};


extern Mower robot;

#endif

