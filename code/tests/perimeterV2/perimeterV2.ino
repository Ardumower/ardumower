
/* Perimeter v2 test
   Arduino Mega
	 
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
#include <Wire.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
#else 
  // Arduino Due
  #include "due.h"
#endif

#include "drivers.h"
#include "adcman.h"
#include "perimeter.h"

#define pinPerimeterLeft A5        // perimeter pin
#define pinPerimeterRight A4       // leave open
#define pinLED 13

// #define USE_DEVELOPER_TEST 1

Perimeter perimeter;
unsigned long nextTime = 0;
int counter = 0;
boolean inside = true;
int mode = 0;


void setup()  {  
  Wire.begin();
  Console.begin(115200);  
  pinMode(pinLED, OUTPUT);

  delay(100);
  Console.println("START");        
  
  ADCMan.init();
  perimeter.setPins(pinPerimeterLeft, pinPerimeterRight);          
  perimeter.useDifferentialPerimeterSignal = true;
  
  perimeter.speedTest();

  Console.println("press...");
  Console.println("  v to toggle between serial chart/console output");  
  Console.println("  c to calibrate zero point (sender must be off!)");   
  delay(1000);
}


void printConsole(){
    Console.print("cnt ");
    Console.print(counter);
    Console.print("\t");    
    Console.print("min ");
    Console.print((int)perimeter.getSignalMin(0));
    Console.print("\t");
    Console.print("max ");
    Console.print((int)perimeter.getSignalMax(0));
    Console.print("\t");
    Console.print("avg ");
    Console.print((int)perimeter.getSignalAvg(0));    
    Console.print("\t\t");
    Console.print("mag ");
    Console.print((int)perimeter.getMagnitude(0));        
    //Console.print(",");
    //Console.print((int)perimeter.getMagnitude(1));        
    Console.print("\t");
    Console.print("\t");    
    Console.print("smag ");    
    Console.print((int)perimeter.getSmoothMagnitude(0));                
    Console.print("\t");    
    Console.print("qty ");        
    Console.print(perimeter.getFilterQuality(0));
    Console.print("\t");
    Console.print("\t");
    Console.print("in ");
    Console.print((int)perimeter.isInside(0));            
    Console.print("\t");
    Console.print("on ");
    Console.print((int)(!perimeter.signalTimedOut(0)));            
    Console.print("\t");
    Console.print("adc ");
    Console.print((int)(ADCMan.getCapturedChannels()));            
    Console.println();   
    delay(500);
}


// https://code.google.com/p/serialchart/
void printSerialChart(){
  static float delta = 0;
  Console.print((int)perimeter.getMagnitude(0));                  
  Console.print(",");                  
  Console.print((int)perimeter.getSmoothMagnitude(0));                
  Console.print(",");                  
  float d = perimeter.getSignalMax(0)-perimeter.getSignalMin(0);
  delta = 0.95 * delta + 0.05 * d;
  Console.print(delta);
  Console.print(",");        
  Console.print(perimeter.getFilterQuality(0));    
  Console.println();
  /*    
  if (!ADCMan.isCaptureComplete(pinPerimeterLeft)) return;
  int8_t *samples = ADCMan.getCapture(pinPerimeterLeft);      
  int sz = ADCMan.getCaptureSize(pinPerimeterLeft);      
  int mag = perimeter.getMagnitude(0);              
  int qty = perimeter.getFilterQuality(0)*100.0;      
  for (int i=0; i < sz; i++){
    for (int w=0; w < 10; w++){
      if (i==0){
        Console.print(qty);
      } else Console.print("0");
      Console.print(",");
      Console.println(samples[i]);
    }
  }
  delay(5000);*/
}

void loop()  {     
      
  ADCMan.run();  
  
  if (Console.available() > 0){
    char ch = (char)Console.read();      
    if (ch == 'v') mode = !mode;
    if (ch == 'c') {
      Console.println("calibrating ADC (power off sender for this!)...");
      Console.flush();
      delay(5000);
      ADCMan.calibrate();
    }
  }
  
  if (millis() >= nextTime){
    nextTime = millis() + 50;
    if (perimeter.isInside(0) != inside){
      inside = perimeter.isInside(0);
      counter++;      
    }
    if (perimeter.isInside(0)) digitalWrite(pinLED, HIGH);    
      else digitalWrite(pinLED, LOW);    

    if (mode == 0){
      printConsole();
    } else {
      printSerialChart();
    }
  }
}



