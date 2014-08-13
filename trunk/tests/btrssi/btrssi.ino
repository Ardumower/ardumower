
/* Bluetooth RSSI monitor (HC-05 module connected to serial2)
   Arduino Mega
 */

#include <Arduino.h>

boolean readBT(){  
  String s;
  if (Serial2.available()){
    Serial.print("receiving: ");
    while (Serial2.available()){
      char data = Serial2.read();
      s += (char)data;          
      if (!Serial2.available()) delay(1);
    }        
    Serial.print(s);
    if (s.endsWith("OK\r\n")) return true;
  } 
  return false; 
}

void sendBT(String s){
  Serial.print("sending: ");
  Serial.println(s);
  Serial2.print(s);
  //Serial2.flush();
}



void setup()  {
  Serial.begin(19200);  
  Serial2.begin(19200);    
  
  delay(1000);
  Serial.println("START");    
  
  /*sendBT("AT\r\n");      
  delay(500);
  readBT();
  
  sendBT("AT+VERSION?\r\n");    
  delay(500);
  readBT();  */
  
  // Initialize the SPP profile lib
  sendBT("at+init\r\n");    
  delay(500);
  readBT();      
  
  sendBT("at+role=1\r\n");    
  delay(500);
  readBT();    
  
  
  sendBT("at+state?\r\n");    
  delay(500);
  readBT();    
  
    
  /*
  // Inquire Bluetooth device has an access code    
  sendBT("AT+IAC=9e8b33\r\n");
  delay(500);  
  readBT();  */
       
  /*
  sendBT("AT+CLASS=0\r\n");
  delay(500);  
  readBT();  
  */
  
  // 1 access mode RSSI
  // 9 max # devices to be discovered
  // 48 timeout
  sendBT("AT+INQM=1,9,48\r\n");
  delay(500);
  readBT();  
  
  // Query Nearby Discoverable Devices      
  sendBT("AT+INQ\r\n");      
}

void loop()  {        
  
  if (readBT()){
    sendBT("AT+INQ\r\n");              
  }    
  /*unsigned long endtime = millis() + 90000;
  while (millis() < endtime){  
    readBT();            
  }*/
}




