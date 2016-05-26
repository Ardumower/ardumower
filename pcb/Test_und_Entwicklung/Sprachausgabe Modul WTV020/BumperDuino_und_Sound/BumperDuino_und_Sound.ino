/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  Copyright (c) 2013-2015 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri    
  Copyright (c) 2015 by Uwe Zimprich
  Copyright (c) 2015 by Frederic Goddeeres
  Copyright (c) 2015 by Jürgen Lange
  
  
  Autor: Jürgen Lange
  Stand: 05.08.2015
  Version: 0.03 Testversion
  
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

#include <Wtv020sd16p.h>
// Created by Diego J. Arevalo, August 6th, 2012.
// Released into the public domain.
int resetPin = 13;  // The pin number of the reset pin.
int clockPin = 11;  // The pin number of the clock pin.
int dataPin = 13;  // The pin number of the data pin.
int busyPin = 12;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

// These constants won't change.  They're used to give names
// to the pins used:
const int sensor1InPin = A0;  // Analog input pin that the MPX5010 is attached to
const int sensor2InPin = A1;  // Analog input pin that the MPX5010 is attached to
//const int analogOut1Pin = 9; // Analog output pin Bumper 1 (PWM)
//const int analogOut2Pin = 10; // Analog output pin Bumper 2 (PWM)
const int Bumper1OutPin = 9;
const int Bumper2OutPin = 10;
const int LEDCollision1 = 7;
const int LEDCollision2 = 8;
const int LEDActive = 13;

int LEDActiveState = LOW;             // ledState used to set the LED

int sensor1Diff = 0;  // = sensor1DiffSecond - sensor1DiffFirst
int sensor1DiffFirst = 0;        // value for zero Point
int sensor1DiffSecond = 0;        // value for touch Point
int sensor1MAP = 0;        // value output to the PWM (analog out)
int sensor1Trigger = 3;  // Sensor-Trigger-Level Sensor 1
int trigger1Counter = 0; // Trigger-Counter Sensor 1
byte sensor1State = 0; // Sensor-State Sensor 1 zero point or touch point
byte count1FirstRead = 0; // Read-Counter for zero point Sensor 1
byte count1SecondRead = 0; // Read-Counter for touch point Sensor 1
byte flagAdc0Read = 0; // Flag its Time to read ADC Sensor 1
int soundBumper1 = 0;

int sensor2Diff = 0;  // = sensor2DiffSecond - sensor2DiffFirst
int sensor2DiffFirst = 0;        // value for zero Point
int sensor2DiffSecond = 0;       // value for touch Point
int sensor2MAP = 0;        // value output to the PWM (analog out)
int sensor2Trigger = 3;  // Sensor-Trigger-Level Sensor 2
int trigger2Counter = 0;  // Trigger-Counter Sensor 2
byte sensor2State = 0;  // Sensor-State Sensor 2 zero point or touch point
byte count2FirstRead = 0;  // Read-Counter for zero point Sensor 2
byte count2SecondRead = 0;  // Read-Counter for touch point Sensor 2
byte flagAdc1Read = 0;  // Flag its Time to read ADC Sensor 2
int soundBumper2 = 2;

unsigned long previousMillis = 0;        // will store last time Timer was updated
const long interval = 15;           // interval at which ADC was read (milliseconds)
const long intervalLedActive = 250; // interval at which LED was blink (milliseconds)
unsigned long previousMillisLedActive = 0;

unsigned long playJokeSoundMillis = 0;
unsigned long playNextJokeSound = 60000;
int jokeSound1 = 3;
//====================================================================================
//================================== SETUP ==========================================
void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // setup Ports
  pinMode(LEDCollision1, OUTPUT);
  pinMode(LEDCollision2, OUTPUT);
  pinMode(LEDActive, OUTPUT);
  pinMode(Bumper1OutPin, OUTPUT);
  pinMode(Bumper2OutPin, OUTPUT);
  digitalWrite(LEDCollision1,LOW);
  digitalWrite(LEDCollision2,LOW);
  digitalWrite(Bumper1OutPin,LOW);
  digitalWrite(Bumper2OutPin,LOW);
}
//================================== END SETUP =======================================
//====================================================================================
//==================================== MAIN ==========================================
void loop() 
{
  // ----------------------------------------- mS Timer for measurement interval -----
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;   
    flagAdc0Read = 1;
    flagAdc1Read = 1;
  }
  // --------------------------------------------------------------------------------
  // ----------------------------------------------- active LED blink ---------------
  if(currentMillis - previousMillisLedActive >= intervalLedActive) 
  {
    previousMillisLedActive = currentMillis;   
    if (LEDActiveState == LOW)
      LEDActiveState = HIGH;
    else
      LEDActiveState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LEDActive, LEDActiveState);
  }
  // --------------------------------------------------------------------------------
  // ------------------------- Calculate Zero-Point ---------------------------------
  // ------------------------------- SENSOR 1 ---------------------------------------
  if(sensor1State < 1)
  {
    if(flagAdc0Read == 1 &&  count1FirstRead < 4)
    {    // read the analog in value: sensor1DiffFirst
      sensor1DiffFirst = sensor1DiffFirst + analogRead(sensor1InPin);
      count1FirstRead++;
      flagAdc0Read = 0;
    }
    if(count1FirstRead >= 3)
    {
      sensor1DiffFirst = sensor1DiffFirst / 4;
      sensor1State = 1;
    }
  }
  // --------------------------------------------------------------------------------
  // ------------------------- Calculate Zero-Point ---------------------------------
  // ------------------------------- SENSOR 2 ---------------------------------------
  if(sensor2State < 1)
  {
    if(flagAdc1Read == 1 &&  count2FirstRead < 4)
    {    // read the analog in value: sensor2DiffFirst
      sensor2DiffFirst = sensor2DiffFirst + analogRead(sensor2InPin);
      count2FirstRead++;
      flagAdc1Read = 0;
    }
    if(count2FirstRead >= 3)
    {
      sensor2DiffFirst = sensor2DiffFirst / 4;
      sensor2State = 1;
    }
  }
  
  // Hier kann durch eine Verzögerung die Empfindlichkeit erhöt werden.
  // Das geht jedoch auf Kosten der Reaktionsgeschwindigkeit
  // Achtung kein delay() verwenden sonst wird die Bearbeitung unterbrochen

  // --------------------------------------------------------------------------------
  // ------------------------- Calculate Touch-Point --------------------------------
  // ------------------------------- SENSOR 1 ---------------------------------------  
  if(sensor1State >= 1)
  {
    if(flagAdc0Read == 1 &&  count1SecondRead < 4)
    { // read the analog in value: sensor1DiffSecond
      sensor1DiffSecond = sensor1DiffSecond + analogRead(sensor1InPin);
      count1SecondRead++;
      flagAdc0Read = 0;
    }
    if(count1SecondRead >= 3)
    {
      sensor1DiffSecond = sensor1DiffSecond / 4;
      sensor1State = 2;
    }
  }
  // --------------------------------------------------------------------------------
  // ------------------------- Calculate Touch-Point --------------------------------
  // ------------------------------- SENSOR 2 ---------------------------------------
  if(sensor2State >= 1)
  {
    if(flagAdc1Read == 1 &&  count2SecondRead < 4)
    { // read the analog in value: sensor1DiffSecond
      sensor2DiffSecond = sensor2DiffSecond + analogRead(sensor2InPin);
      count2SecondRead++;
      flagAdc1Read = 0;
    }
    if(count2SecondRead >= 3)
    {
      sensor2DiffSecond = sensor2DiffSecond / 4;
      sensor2State = 2;
    }
  }
  
  // --------------------------------------------------------------------------------
  // ------------------------- Calculate Zero-Touch-Diff ----------------------------
  // ------------------------------- SENSOR 1 ---------------------------------------  
  if(sensor1State == 2)
  {
    sensor1Diff = sensor1DiffSecond - sensor1DiffFirst;
    sensor1DiffSecond = 0;
    count1SecondRead = 0;
    sensor1State = 3;
  }
  // --------------------------------------------------------------------------------
  // ------------------------- Calculate Zero-Touch-Diff ----------------------------
  // ------------------------------- SENSOR 2 ---------------------------------------
  if(sensor2State == 2)
  {
    sensor2Diff = sensor2DiffSecond - sensor2DiffFirst;
    sensor2DiffSecond = 0;
    count2SecondRead = 0;
    sensor2State = 3;
  }
  // --------------------------------------------------------------------------------
  // -------------------- Check Zero-Touch-Diff for Trigger -------------------------
  // ------------------------------- SENSOR 1 ---------------------------------------
  if(sensor1Diff >= sensor1Trigger & sensor1State == 3) 
  {
    digitalWrite(LEDCollision1,HIGH);
    digitalWrite(Bumper1OutPin,HIGH);
    wtv020sd16p.asyncPlayVoice(soundBumper1); //Plays asynchronously an audio file  Nr.0
    trigger1Counter++;
    Serial.print("counter 1 = " );
    Serial.print(trigger1Counter);
    Serial.print("\t sensor dif 1 = ");
    Serial.println(sensor1Diff);
  } else if (sensor1State == 3) 
  {
    sensor1State = 0;
    sensor1DiffFirst = 0;
    sensor1DiffSecond = 0;
    count1SecondRead = 0;
    count1FirstRead = 0;
    digitalWrite(LEDCollision1,LOW);
    digitalWrite(Bumper1OutPin,LOW);
  }
  // --------------------------------------------------------------------------------
  // -------------------- Check Zero-Touch-Diff for Trigger -------------------------
  // ------------------------------- SENSOR 2 ---------------------------------------
  if(sensor2Diff >= sensor2Trigger & sensor2State == 3) 
  {
    digitalWrite(LEDCollision2,HIGH);
    digitalWrite(Bumper2OutPin,HIGH);
    wtv020sd16p.asyncPlayVoice(soundBumper2); //Plays asynchronously an audio file Nr.1
    trigger2Counter++;
    Serial.print("counter 2 = " );
    Serial.print(trigger2Counter);
    Serial.print("\t sensor dif 2 = " );
    Serial.println(sensor2Diff);
  } else if (sensor2State == 3) 
  {
    sensor2State = 0;
    sensor2DiffFirst = 0;
    sensor2DiffSecond = 0;
    count2SecondRead = 0;
    count2FirstRead = 0;
    digitalWrite(LEDCollision2,LOW);
    digitalWrite(Bumper2OutPin,LOW);
  }
  
  if(millis() >= playJokeSoundMillis)
  {
    playJokeSoundMillis = millis() + playNextJokeSound;
    if(sensor1State < 3 && sensor2State < 3)
      wtv020sd16p.asyncPlayVoice(jokeSound1); //Plays asynchronously an audio file Nr.3
  }
}// end void loop()
//==================================== END MAIN ======================================
//====================================================================================
