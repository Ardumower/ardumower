/* PCB-Tester  - Read/write to digital/analog pins via serial user interface
 * 23.03.2017
 */

#include <Arduino.h>

#define pinBuzzer 53               // Buzzer


void setup(){
  Serial.begin(115200);           // Baudrate 115200
  pinMode(pinBuzzer, OUTPUT);
  printMenu();
}

void printMenu(){
  serialPurge();
  Serial.println("PCB-TESTER");  
  Serial.println("1 - Read pin");
  Serial.println("2 - Write pin");
}

void serialPurge(){
  delay(100);
  while (Serial.available()) Serial.read();
}

void readTest(){      
  serialPurge();
  Serial.println("READ - Enter pin number (D1,D2,...,D53,A0,A1,...,A15): ");           
  while (!Serial.available());
  delay(100);  
  char type = Serial.read();    
  int number = Serial.parseInt();        
  Serial.println();
  serialPurge();
  Serial.println("(press any key to exit)");           
  pinMode(number, INPUT);
  while (true){    
    Serial.print(type);
    Serial.print(number);
    Serial.print("=");    
    if (type == 'D'){
      boolean state = digitalRead(number);
      Serial.println(state);
    } else {
      int value = analogRead(A0 + number);
      Serial.println(value);
    }
    if (Serial.available()) break;
    delay(1000);
  }
}

void writeTest(){      
  serialPurge();
  Serial.println("WRITE - Enter expression (examples: D13=1, D13=0, A0=100): ");           
  while (!Serial.available());
  delay(100);
  char type = Serial.read();    
  int number = Serial.parseInt();        
  int value = Serial.parseInt();        
  Serial.println();
  serialPurge();    
  pinMode(number, OUTPUT);
  Serial.print(type);
  Serial.print(number);
  Serial.print("=");       
  Serial.println(value);  
  if (type == 'D'){
    digitalWrite(number, value);     
  } else {
    analogWrite(A0 + number, value);    
  }    
}



void loop(){    
  if (Serial.available()){
    char ch = Serial.read();
    switch (ch) {
         case '1': 
           readTest();                      
           break;
         case '2':
           writeTest();
           break;                       
    }
    printMenu();
  }
}



