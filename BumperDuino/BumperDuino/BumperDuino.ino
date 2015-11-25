/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  Copyright (c) 2013-2015 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri    
  Copyright (c) 2015 by Uwe Zimprich
  Copyright (c) 2015 by Jürgen Lange
  
  
  Autor: Jürgen Lange
  Stand: 05.08.2015
  Version: 0.00 Testversion
  
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

int sensor1Diff = 0;
int sensor1DiffFirst = 0;        // value read from the pot
int sensor1DiffSecond = 0;        // value read from the pot
int sensor1MAP = 0;        // value output to the PWM (analog out)
int sensor1Trigger = 7;
int trigger1Counter = 0;
byte sensor1State = 0;
byte count1FirstRead = 0;
byte count1SecondRead = 0;
byte flagAdc0Read = 0;

int sensor2Diff = 0;
int sensor2DiffFirst = 0;        // value read from the pot
int sensor2DiffSecond = 0;        // value read from the pot
int sensor2MAP = 0;        // value output to the PWM (analog out)
int sensor2Trigger = 7;
int trigger2Counter = 0;
byte sensor2State = 0;
byte count2FirstRead = 0;
byte count2SecondRead = 0;
byte flagAdc1Read = 0;

unsigned long previousMillis = 0;        // will store last time Timer was updated
const long interval = 10;           // interval at which ADC was read (milliseconds)
const long intervalLedActive = 250; // interval at which LED was blink (milliseconds)
unsigned long previousMillisLedActive = 0;
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
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;   
    flagAdc0Read = 1;
    flagAdc1Read = 1;
  }
  
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
  
  
  if(sensor1State == 2)
  {
    sensor1Diff = sensor1DiffSecond - sensor1DiffFirst;
    sensor1DiffSecond = 0;
    count1SecondRead = 0;
    sensor1State = 3;
  }
  
  if(sensor2State == 2)
  {
    sensor2Diff = sensor2DiffSecond - sensor2DiffFirst;
    sensor2DiffSecond = 0;
    count2SecondRead = 0;
    sensor2State = 3;
  }
  
  
  if(sensor1Diff >= sensor1Trigger & sensor1State == 3) 
  {
    digitalWrite(LEDCollision1,HIGH);
    digitalWrite(Bumper1OutPin,HIGH);
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
  
  if(sensor2Diff >= sensor2Trigger & sensor2State == 3) 
  {
    digitalWrite(LEDCollision2,HIGH);
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
  }
  
}// end void loop()
//==================================== END MAIN ======================================
//====================================================================================
