// Arduino robot mower
// Copyright (c) 2014 by Alexander Grau
//
// Bluetooth programmer
 

#include "bt.h"
#include "ardumower.h"


enum {
  BT_UNKNOWN,
  BT_LINVOR_HC06, // Linvor / HC06
  BT_HC05,        // HC05                 
  BT_FBT06_MBTV4, // ModiaTek FBT06/MBTV4 
};


void BluetoothConfig::setConfigs(byte *config){
  for (int i=0; i < 24; i++){
    btTestConfig[i] = config[i];
  }
}

BluetoothConfig::BluetoothConfig(){
  btType = BT_UNKNOWN;
  btRate = 9600;    
#ifdef __AVR__
  byte configs[24] =  { SERIAL_8N1, SERIAL_5N1, SERIAL_6N1, SERIAL_7N1, 
                    SERIAL_5N2, SERIAL_6N2, SERIAL_7N2, SERIAL_8N2,
                    SERIAL_5E1, SERIAL_6E1, SERIAL_7E1, SERIAL_8E1,  
                    SERIAL_5E2, SERIAL_6E2, SERIAL_7E2, SERIAL_8E2,
                    SERIAL_5O1, SERIAL_6O1, SERIAL_7O1, SERIAL_8O1,
                    SERIAL_5O2, SERIAL_6O2, SERIAL_7O2, SERIAL_8O2 };               
  setConfigs(configs);
  btConfig = SERIAL_8N1;                                                
#else
  btTestConfig[1] = { 0 }; 
  btConfig = 0;  
#endif                            
}

void BluetoothConfig::writeBT(String s){
  Serial.print("send: "+s);
  Serial2.print(s);
}

void BluetoothConfig::readBT(){
  btResult = "";
  if (Serial2.available()){
    Serial.print(F("  received: "));
    while (Serial2.available()){
      btData=Serial2.read();
      btResult += char(btData);
      Serial.print(btData);
    }    
  }  
  //Serial.print("btResult=");
  //Serial.println(btResult);
}

void BluetoothConfig::writeReadBT(String s){
  writeBT(s);
  delay(2000);
  readBT();    
  int counter = 0;
  while ((btResult.startsWith("ERROR") && counter < 4)){
    // retry 
    writeBT(s);
    delay(2000);    
    readBT();
    counter++;
  }        
  Serial.println();
}


void BluetoothConfig::setName(String name){
  boolean res = false;
  Serial.println();
  Serial.print(F("setting name "));
  Serial.print(name);
  Serial.println("...");
  switch (btType){
    case BT_LINVOR_HC06:
      writeReadBT("AT+NAME"+name);     
      res = btResult.startsWith("OKsetname");
      break;
    case BT_HC05:
      writeReadBT("AT+NAME="+name+"\r\n");     
      res = (btResult.indexOf("OK") != -1);      
      break;
    case BT_FBT06_MBTV4:
      writeReadBT("AT+NAME"+name+"\r\n");     
      res = (btResult.indexOf("OK") != -1);
      break;  
  }    
  if (res) Serial.println(F("=>success"));
    else Serial.println(F("=>error setting name"));
}


void BluetoothConfig::setPin(int pin){
  boolean res = false;
  Serial.println();
  Serial.print(F("setting pin "));
  Serial.print(pin);
  Serial.println(F("..."));
  switch (btType){
    case BT_LINVOR_HC06:
      writeReadBT("AT+PIN"+String(pin));     
      res = (btResult.startsWith("OKsetPIN"));
      break;
    case BT_HC05:
      writeReadBT("AT+PSWD="+String(pin)+"\r\n");     
      res = (btResult.indexOf("OK") != -1);      
      break;
    case BT_FBT06_MBTV4:
      writeReadBT("AT+PIN"+String(pin)+"\r\n");     
      res = (btResult.indexOf("OK") != -1);      
      break;
  }  
  if (res) Serial.println(F("=>success"));
    else Serial.println(F("=>error setting pin"));
}


void BluetoothConfig::setBaudrate(long rate){    
  Serial.println();
  Serial.print(F("setting baudrate "));
  Serial.print(rate);
  Serial.println(F("..."));
  byte n=4;
  boolean res = false;
  switch (btType){
    case BT_LINVOR_HC06:
      switch (rate){
        case 1200: n=1; break;
        case 2400: n=2; break;
        case 4800: n=3; break;
        case 9600: n=4; break;
        case 19200: n=5; break;
        case 38400: n=6; break;
        case 57600: n=7; break;
        case 115200: n=8; break;
      }      
      writeReadBT("AT+PN"); // no parity
      writeReadBT("AT+BAUD"+String(n));     
      res = (btResult.startsWith("OK"+String(rate)));
      break;
    case BT_HC05:
      writeReadBT("AT+UART="+String(rate)+",0,0"+"\r\n");     
      res = (btResult.indexOf("OK") != -1);          
      break;
    case BT_FBT06_MBTV4:
      switch (rate){
        case 1200: n=1; break;
        case 2400: n=2; break;
        case 4800: n=3; break;
        case 9600: n=4; break;
        case 19200: n=5; break;
        case 38400: n=6; break;
        case 57600: n=7; break;
        case 115200: n=8; break;
      }          
      writeReadBT("AT+BAUD"+String(n)+"\r\n");     
      res = (btResult.indexOf("OK") != -1);
      break;
  }  
  if (res){
    btRate = rate;
    Serial.println(F("=>success"));
  } else {
    Serial.println(F("=>error setting baudrate"));
  } 
}  

boolean BluetoothConfig::detectBaudrate(boolean quickBaudScan){
  Serial.println();
  Serial.println(F("detecting baudrate..."));
  for (int i=0; i < 8; i++){    
    switch(i){
      case 0: btRate = 9600; break;
      case 1: btRate = 38400; break;      
      case 2: btRate = 19200; break;      
      case 3: btRate = 57600; break;            
      case 4: btRate = 115200; break;                  
      case 5: btRate = 4800; break;
      case 6: btRate = 2400; break;      
      case 7: btRate = 1200; break;            
    }      
    for (int j=0; j < sizeof btTestConfig; j++){
      btConfig = btTestConfig[j];
      Serial.print(F("trying baudrate "));
      Serial.print(btRate);
      Serial.print(F(" config "));
      Serial.print(j);
      Serial.println(F("..."));
      #ifdef __AVR__
        Serial2.begin(btRate, btConfig);
      #else
        Serial2.begin(btRate);      
      #endif
      writeReadBT("AT");  // linvor/HC06 does not want a terminator!    
      if (btResult.startsWith("OK")){
        Serial.println(F("=>success"));
        return true;
      }
      writeReadBT("AT\r\n");  // HC05 wants a terminator!          
      if (btResult.startsWith("OK")){
        Serial.println(F("=>success"));
        return true;
      }      
      if (quickBaudScan) break;      
    }
    //writeReadBT("ATI1\n"); // BTM info   
    //writeReadBT("ATZ0\n"); // BTM factory    
    //writeReadBT("ATC0\r\nATQ1\r\nATI1\r\n"); // BTM    
  }
  Serial.println(F("=>error detecting baudrate"));
  return false;
}

void BluetoothConfig::detectModuleType(){
  Serial.println();
  Serial.println(F("detecting BT type..."));
  writeReadBT("AT+VERSION");  
  if (btResult.startsWith("OKlinvor")){
    Serial.println(F("=>it's a linvor/HC06"));
    btType = BT_LINVOR_HC06;
    return;
  }     
  writeReadBT("AT+VERSION?\r\n");  
  if (btResult.indexOf("OK") != -1){
    Serial.println(F("=>must be a HC03/04/05 ?"));      
    btType = BT_HC05;
  }  
  writeReadBT("AT+VERSION\r\n");
  if (btResult.indexOf("ModiaTek") != -1){
    Serial.println(F("=>it's a FBT06/MBTV4"));
    btType = BT_FBT06_MBTV4;
  }
}

void BluetoothConfig::setParams(String name, int pin, long baudrate, boolean quickBaudScan) {
  //delay(2000);
  Serial.println(F("HC-03/04/05/06/linvor/ModiaTek Bluetooth config programmer")); 
  if (detectBaudrate(quickBaudScan)){
    detectModuleType();
    if (btType != BT_UNKNOWN){      
      setName(name);
      setPin(pin);
      setBaudrate(baudrate);
      Serial.println(F("You may restart BT module now!"));  
    }
  }
}



