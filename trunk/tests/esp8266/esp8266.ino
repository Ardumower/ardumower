/*
ESP8266 ESP-01 Wifi module - test (Arduino Mega)
http://playground.boxtec.ch/doku.php/wireless/esp8266

wiring (IC side):
                                ESP8266-01
Arduino Mega TX1 ------------RX---1 2---VCC (3.3V)
                          GPIO0---3 4---nRST
               |Antenna|  GPIO2---5 6---nCHPD ---------- connect to VCC (3.3V)
                            GND---7 8---TX-------------- RX  Arduino Mega RX1
*/

// encryption types
enum {
  ENCRYPT_NO, ENCRYPT_WEP, ENCRYPT_WPA_PSK, ENCRYPT_WPA2_PSK, ENCRYPT_WPA_WPA2_PSK, ENCRYPT_AUTO,
};


// Wifi network settings (please adjust!)
String wifiSSID = "GRAUNET";
String wifiPass = "71979";
int wifiEncrypt = ENCRYPT_AUTO;  // do not change
int wifiChannel = 5;  // do not change (only used if used non-auto encryption)


void writeWifi(String s){
  Serial.println("SEND: "+s);
  Serial1.print(s);  
}


String readWifi(int waitMillis = 2000){
  Serial.print("RECV: ");
  String s;
  char data;
  unsigned long startTime = millis();
  while (millis() < startTime + waitMillis){
    while (Serial1.available()){
      data=Serial1.read();
      s += char(data);
      Serial.print(data);
    }
  }
  Serial.println();
  return s;
}

String writeReadWifi(String s, int waitMillis = 2000){
  writeWifi(s);  
  String res = readWifi(waitMillis);        
  return res;
}

// try out baudrate and connect
boolean connectWifi(){
  Serial.println("--------connectWifi--------");
  String s;
  Serial1.setTimeout(5000);
  while (true){    
    Serial.println("trying 115200...");  
    Serial1.begin(115200);   
    s = writeReadWifi("AT\r");
    if (s.indexOf("OK") != -1) break;
    Serial.println("trying 57600...");  
    Serial1.begin(57600);     
    s = writeReadWifi("AT\r");
    if (s.indexOf("OK") != -1) break;
    Serial.println("trying 9600...");  
    Serial1.begin(9600);         
    s = writeReadWifi("AT\r");
    if (s.indexOf("OK") != -1) break;
    Serial.println("ERROR: cannot connect");    
    return false;
  }    
  return true;  
}


// join Wifi network
boolean joinWifi(){
  Serial.println("--------joinWifi--------");
  writeReadWifi("AT+RST\r", 4000);  // reset module  
  writeReadWifi("AT+GMR\r");  // get firmware version
  writeReadWifi("AT+CWMODE=1\r");  // station mode    
  writeReadWifi("AT+CWMODE=3\r");  // station mode      
  writeReadWifi("AT+CIPMODE=1\r");  // data mode        
  writeReadWifi("AT+CIPMUX=1\r");  // multiple connection mode    
  //writeReadWifi("AT+CWLAP\r", 30000);  // get access points      
  boolean res = false;
  // joining network
  for (int retry = 0; retry < 4; retry++){
    String conn = "AT+CWJAP=\"" + wifiSSID + "\",\"" + wifiPass + "\"";
    if (wifiEncrypt != ENCRYPT_AUTO){
      conn += ",";
      conn += String(wifiChannel);
      conn += ",";      
      conn += String(wifiEncrypt);
    }
    String s = writeReadWifi(conn + "\r", 3500);
    res = (s.indexOf("OK") != -1);
    if (res) break;
  }
  if (res) {
    writeReadWifi("AT+CWJAP?\r");  // list access point
    //writeReadWifi("AT+CIPMUX=0\r");  // multiple connection mode        
  } else Serial.println("ERROR joining");      
  return res;
}


void startServer(){
  Serial.println("--------startServer--------");  
  writeReadWifi("AT+CIPSERVER=1,80\r");   // start server
  writeReadWifi("AT+CIPSTO=10\r");   // set server timeout
  for (int retry = 0; retry < 10; retry++){
      Serial.print("waiting for getting IP (DHCP)... retry ");
      Serial.println(retry);
      delay(5000);
      String s = writeReadWifi("AT+CIFSR\r");  // get IP address      
      if (s.indexOf("OK") != -1) break;
  }      
}

void runServer(){
  String s;
  char data;
  while (Serial1.available()){
    data=Serial1.read();
    s += char(data);
    Serial.print(data);
  }
}


void setup(){
  Serial.begin(19200);
  Serial.println("START");
  if (connectWifi()){
    if (joinWifi()){
      startServer();
    }
  }
  Serial.println("--------loop--------");    
}


void loop(){
  runServer();  
}



