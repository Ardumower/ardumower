
/* Bluetooth RSSI monitor (HC-05 module connected to serial2)
  (Remember to connect KEY pin to 3.3V after powering on)

   Arduino Mega
 */

#include <Arduino.h>

#define pinBTKey 41


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

void sendReadBT(String s){
  sendBT(s);
  delay(500);
  readBT();
}


void runAsMaster(){
  Serial2.begin(19200);      
  sendReadBT("AT\r\n");          
  sendReadBT("AT+VERSION?\r\n");    
  // get sniff params
  // 1024  max time
  // 512   min time
  // 1024  test time
  // 512   limited time
  sendReadBT("AT+IPSCAN?\r\n");         
  sendReadBT("AT+SNIFF?\r\n");         
  // Initialize the SPP profile lib
  sendReadBT("at+init\r\n");      
  sendReadBT("at+role=1\r\n");        
  sendReadBT("at+state?\r\n");        
  // Inquire Bluetooth device has an access code    
  //sendReadBT("AT+IAC=9e8b33\r\n");    
  //sendReadBT("AT+CLASS=0x1f1f\r\n");
  // 1 access mode RSSI
  // 9 max # devices to be discovered
  // 48 timeout
  sendReadBT("AT+INQM=1,9,48\r\n");
  // Query Nearby Discoverable Devices      
  sendBT("AT+INQ\r\n");       
  while(true){
    if (readBT()){
      sendBT("AT+INQ\r\n");              
    }    
  }
}

void configSlave(){
  Serial2.begin(9600);      
  sendReadBT("AT\r\n");          
  sendReadBT("AT+VERSION?\r\n"); 
  sendReadBT("AT+SNIFF?\r\n");           
  //sendReadBT("AT+SNIFF=0,0,0,0\r\n");       
  sendReadBT("AT+IPSCAN?\r\n");            
  sendReadBT("AT+IPSCAN=1024,768,1024,768\r\n");       
  sendReadBT("AT+IPSCAN?\r\n");            
}

void setup()  {  
  Serial.begin(19200);  

  pinMode(pinBTKey, OUTPUT);// this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(pinBTKey, HIGH);  
  
  delay(1000);
  Serial.println("START");    
  
  //configSlave();  
  runAsMaster();  
}

void loop()  {          
}




