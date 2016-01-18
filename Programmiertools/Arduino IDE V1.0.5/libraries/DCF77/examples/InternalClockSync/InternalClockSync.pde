/*
 * InternalClockSync.pde
 * example code illustrating time synced from a DCF77 receiver
 * Thijs Elenbaas, 2012
 * This example code is in the public domain.
 
  This example shows how to fetch a DCF77 time and synchronize
  the internal clock. In order for this example to give clear output,
  make sure that you disable logging  from the DCF library. You can 
  do this by commenting out   #define VERBOSE_DEBUG 1   in Utils.cpp. 
 */

#include "DCF77.h"
#include "Time.h"

#define DCF_PIN 2	         // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0		 // Interrupt number associated with pin

time_t time;
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);


void setup() {
  Serial.begin(9600); 
  DCF.Start();
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
}

void loop() {
  delay(1000);
  time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
  if (DCFtime!=0)
  {
    Serial.println("Time is updated");
    setTime(DCFtime);
  }	
  digitalClockDisplay();  
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}