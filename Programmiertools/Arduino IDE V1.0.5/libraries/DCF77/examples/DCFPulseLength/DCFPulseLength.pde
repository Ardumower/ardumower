/*
 * DCFPulseLength.ino - DCF77 debug Example
 * Thijs Elenbaas, 2012
 * This example code is in the public domain.
 
  This simple example shows the pulse-to-pulse time and pulse lengths
  coming from the DCF decoder.
  
  Notice that will the DCF specification says that pulses should be either
  100 or 200 ms, we notice longer pulse lengths. This is likely due to to
  the hardware of the decoder. For optimal distinction between long and 
  short pulses in the DCF library, set the parameter 
  #define DCFSplitTime in DCF77.h to (Tlongpulse+Tlongpulse)/2		  
*/
 
#define BLINKPIN 13
#define DCF77PIN 2

int flankUp = 0;
int flankDown = 0;
int PreviousflankUp;
bool Up = false;

void setup() {
  Serial.begin(9600);
  pinMode(DCF77PIN, INPUT);
  pinMode(BLINKPIN, OUTPUT);
}

void loop() {
  int sensorValue = digitalRead(DCF77PIN);
    if (sensorValue) {
      if (!Up) {
        flankUp=millis();
        Up = true;
        digitalWrite(BLINKPIN, HIGH);
      }
    } else {
      if (Up) {
        flankDown=millis();
        Serial.print("Cycle: ");
        Serial.print(flankUp-PreviousflankUp);
        Serial.print(" Pulse :");
        Serial.println(flankDown - flankUp);
        PreviousflankUp = flankUp;
        Up = false;
		digitalWrite(BLINKPIN, LOW);
      }              
    }
  
}


