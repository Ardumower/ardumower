/* 

R/C gasoline mower, steer robot by model R/C ( Motortreiber ansteuern mit Funke)
requires: Arduino Nano, BTS7960 motor drivers

License
Copyright (c) 2013-2017 by Alexander Grau

Private-use only! (you need to ask for a commercial-use)
 
The code is open: you can modify it under the terms of the 
GNU General Public License as published by the Free Software Foundation, 
either version 3 of the License, or (at your option) any later version.

The code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Private-use only! (you need to ask for a commercial-use)
 
 */

#include <Arduino.h>

#define pinLeft_R_EN   A1  
#define pinLeft_L_EN   A0
#define pinLeft_R_PWM  9
#define pinLeft_L_PWM  10

#define pinRight_R_EN   A3
#define pinRight_L_EN   A2
#define pinRight_R_PWM  3
#define pinRight_L_PWM  11

#define pinRemoteSteer   5  // PCINT21
#define pinRemoteSpeed   6  // PCINT22

// motor speed
#define motorSpeedMax 255
#define motorMowSpeedMax 255


// R/C measurement
int remoteSteer ;  // range -100..100
int remoteSpeed ;  // range -100..100
unsigned long remoteSteerLastTime ;
unsigned long remoteSpeedLastTime ;
boolean remoteSteerLastState ;
boolean remoteSpeedLastState ;


unsigned long nextInfoTime = 0;


// BTS7960 motor driver
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 PinDir
// PWM                L     Forward
// nPWM               H     Reverse
void setBTS7960(int pinR_PWM, int pinL_PWM, int speed){
  if (speed < 0){
    digitalWrite(pinR_PWM, HIGH) ;
    analogWrite(pinL_PWM, 255-((byte)abs(speed)));
  } else {
    digitalWrite(pinR_PWM, LOW) ;
    analogWrite(pinL_PWM, ((byte)speed));
  }
}

int rcValue(int ppmTime){
  int value = (int) (((double)((ppmTime) - 1500)) / 3.4);
  if ((value < 5) && (value > -5)) value = 0;
  return value;
}

// RC remote control driver
void setRemotePPMState(unsigned long timeMicros, boolean remoteSpeedState, boolean remoteSteerState){
  if (remoteSpeedState != remoteSpeedLastState) {    
    remoteSpeedLastState = remoteSpeedState;
    if (remoteSpeedState) remoteSpeedLastTime = timeMicros; else remoteSpeed = rcValue(timeMicros - remoteSpeedLastTime);
  }
  if (remoteSteerState != remoteSteerLastState) {    
    remoteSteerLastState = remoteSteerState;
    if (remoteSteerState) remoteSteerLastTime = timeMicros; else remoteSteer = rcValue(timeMicros - remoteSteerLastTime);
  }
}


// remote control (RC) ppm signal change interrupt
ISR(PCINT2_vect){   
  unsigned long timeMicros = micros();
  boolean remoteSpeedState = digitalRead(pinRemoteSpeed);
  boolean remoteSteerState = digitalRead(pinRemoteSteer);
  setRemotePPMState(timeMicros, remoteSpeedState, remoteSteerState);    
}

void setup(){
  Serial.begin(115200); // setup baud rate 

  pinMode(pinLeft_R_EN, OUTPUT);  
  pinMode(pinLeft_L_EN, OUTPUT);
  pinMode(pinLeft_R_PWM, OUTPUT);
  pinMode(pinLeft_L_PWM, OUTPUT);

  pinMode(pinRight_R_EN, OUTPUT);
  pinMode(pinRight_L_EN, OUTPUT);
  pinMode(pinRight_R_PWM, OUTPUT);
  pinMode(pinRight_L_PWM, OUTPUT);

  // enable outputs
  digitalWrite(pinLeft_R_EN, HIGH);
  digitalWrite(pinLeft_L_EN, HIGH);

  digitalWrite(pinRight_R_EN, HIGH);
  digitalWrite(pinRight_L_EN, HIGH);
  
  // R/C  (enable interrupts)  
  pinMode(pinRemoteSteer, INPUT);
  pinMode(pinRemoteSpeed, INPUT);        

  attachInterrupt(pinRemoteSpeed, PCINT2_vect, CHANGE);            
  attachInterrupt(pinRemoteSteer, PCINT2_vect, CHANGE);          


  //---------------------------------------------- Set PWM frequency for D9 & D10 ------------------------------ 
  TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
  //TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  //---------------------------------------------- Set PWM frequency for D3 & D11 ------------------------------
  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

  //-------------------------------------------------------------------------
	// R/C
	//-------------------------------------------------------------------------
	PCICR |= (1<<PCIE2);	
	PCMSK2 |= (1<<PCINT21);
	PCMSK2 |= (1<<PCINT22);	
 	

  /*unsigned long endTime = millis() + 2000;
  while (millis() < endTime){
    setMC33926(pinMotorLeftDir, pinMotorLeftPWM, -127);
    setMC33926(pinMotorRightDir, pinMotorRightPWM, 127);
    delay(100);
  }*/
}

void loop(){
  // R/C conversion to motor speed (left/right)
  float steer = ((double)motorSpeedMax/2) * (((double)remoteSteer)/100.0);
  if (remoteSpeed < 0) steer *= -1;
  int motorLeftSpeed  = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) - steer; 
  int motorRightSpeed = ((double)motorSpeedMax) * (((double)remoteSpeed)/100.0) + steer; 
  motorLeftSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorLeftSpeed));
  motorRightSpeed = max(-motorSpeedMax, min(motorSpeedMax, motorRightSpeed));
  
  setBTS7960(pinLeft_R_PWM, pinLeft_L_PWM, motorLeftSpeed);
  setBTS7960(pinRight_R_PWM, pinRight_L_PWM, motorRightSpeed); 
  
  if (millis() >= nextInfoTime){
      nextInfoTime = millis() + 1000; // choose time interval here
      // serial console output
      Serial.print("steer=");
      Serial.print(remoteSteer);
      Serial.print("  speed=");
      Serial.print(remoteSpeed);
      Serial.print("  mleft=");
      Serial.print(motorLeftSpeed);
      Serial.print("  mright=");
      Serial.print(motorRightSpeed);      
      Serial.println();    
  }
  
  //delay(15);
}

