// freewheel sensor
// https://wiki.ardumower.de/index.php?title=Free_wheel_sensor

#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_HMC5883_U.h"


#define pinLED 13
#define pinFreeWheelOutput 8

volatile boolean motorMowRpmLastState = LOW;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}



void setup(){
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  pinMode(pinFreeWheelOutput, OUTPUT);

  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }

  mag.setMagGain(HMC5883_MAGGAIN_8_1);
  //mag.setMagGain(HMC5883_MAGGAIN_4_0);

  /* Display some basic information on this sensor */
  displaySensorDetails();  
      
}


unsigned int measure_median(uint8_t it) {
  unsigned int uS[it], last;
  uint8_t j, i = 0;
  uS[0] = 0;
  while (i < it) {
    last = analogRead(A0);           // Send ping.    
	if (i > 0) {               // Don't start sort till second ping.
		for (j = i; j > 0 && uS[j - 1] < last; j--) // Insertion sort loop.
		  uS[j] = uS[j - 1]; // Shift ping array to correct position for sort insertion.
	 } else j = 0;              // First ping is starting point for sort.
	 uS[j] = last;              // Add last ping to array in sorted position.
         i++;                       // Move to next ping.
     if (i < it) delay(1);
   }
   return (uS[it >> 1]); // Return the ping distance median.
}


float curr = 0;
unsigned long counter = 0;
unsigned long timeout = millis() + 2000;
unsigned long ledTimeout = 0;
float smooth = 0;
float x = 0;
float y = 0;
float z = 0;

/*
void loop(){  
  int v = analogRead(A0);
  smooth = 0.9 * smooth + ((double)v) * 0.1;
  if (millis() > timeout){
    timeout = millis() + 0;
    if (abs(smooth-curr) > 2){
      digitalWrite(pinLED, HIGH);
      ledTimeout = millis() + 1000;
      curr = smooth;  
      Serial.print("counter=");
      Serial.print(counter);
      Serial.print(", ");
      Serial.print("adc=");
      Serial.println(v);    
      counter++;    
    }
  }  
  if (millis() > ledTimeout){
    digitalWrite(pinLED, LOW);
  }
  delay(10);
       
*/


void loop(){
   sensors_event_t event; 
   mag.getEvent(&event);

   /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
   //float mag = sqrt(sq(event.magnetic.x) + sq(event.magnetic.y) + sq(event.magnetic.z));  
   //Serial.println(mag);
   //if (abs(mag-curr) > 1.0){
   float delta = 5.0;
   if ( (abs(x-event.magnetic.x) > delta) ||  (abs(y-event.magnetic.y) > delta) || (abs(z-event.magnetic.z) > delta) ){
      x = event.magnetic.x;
      y = event.magnetic.y;
      z = event.magnetic.z;
      digitalWrite(pinLED, HIGH);
      digitalWrite(pinFreeWheelOutput, HIGH);
      ledTimeout = millis() + 500;
      /*Serial.print("counter=");
      Serial.print(counter);
      Serial.print("  ");*/
      Serial.print("$");
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.print(z);
      Serial.print(";");
      Serial.println();    
      counter++;          
   }
   delay(50); 
   if (millis() > ledTimeout){
     digitalWrite(pinLED, LOW);
     digitalWrite(pinFreeWheelOutput, LOW);
   }
}


