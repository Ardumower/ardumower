/*
ESP8266 ESP-01 Wifi module - test (Arduino Mega)
http://playground.boxtec.ch/doku.php/wireless/esp8266

wiring (IC side):
                                ESP8266-01
Arduino Mega TX1 ------------RX---8 4---VCC (3.3V)
                          GPIO0---7 3---nRST
               |Antenna|  GPIO2---6 2---nCHPD ---------- connect to VCC (3.3V)
                            GND---5 1---TX-------------- RX  Arduino Mega RX1
*/

// encryption types
enum {
  ENCRYPT_NO, ENCRYPT_WEP, ENCRYPT_WPA_PSK, ENCRYPT_WPA2_PSK, ENCRYPT_WPA_WPA2_PSK, ENCRYPT_AUTO,
};

// Wifi network settings (please adjust!)
String wifiSSID = "GRAUNET";
String wifiPass = "11111";
unsigned long wifiBaudrate = 9600;
int wifiEncrypt = ENCRYPT_AUTO;  // do not change
int wifiChannel = 5;  // do not change (only used if used non-auto encryption)

unsigned long probeBauds[34] =  { 19200, 115200, 57600, 9600 };


String connData;
boolean pfodCmdComplete = false;
String pfodCmd = "";


void writeWifi(String s){
  Serial.print("SEND: "+s);
  Serial1.print(s);  
}


String readWifi(int waitMillis = 500){
  Serial.print("RECV: ");
  String s;
  char data;
  unsigned long startTime = millis();
  while (millis() < startTime + waitMillis) {
    while (Serial1.available()){
      data=Serial1.read();
      s += char(data);
      Serial.print(data);      
    }
  }
  Serial.println();
  return s;
}

String writeReadWifi(String s, int waitMillis = 500){
  String res;
  writeWifi(s);    
  res = readWifi(waitMillis);          
  return res;
}

// try out baudrate and connect
boolean connectWifi(){
  Serial.println("--------connectWifi--------");
  String s;
  Serial1.setTimeout(5000);
  boolean foundBaud = 0;
  for (int i=0; i < 4; i++){
    Serial.print("trying ");  
    Serial.println(probeBauds[i]);
    Serial1.begin(probeBauds[i]);   
    s = writeReadWifi("AT\r\n");
    if (s.indexOf("OK") != -1) {
      foundBaud = probeBauds[i];
      break;    
    }
  } 
  if (foundBaud == 0){
    Serial.println("ERROR: cannot connect");    
    return false;
  }   
  if (foundBaud != wifiBaudrate){
    writeReadWifi("AT+CIOBAUD=" + String(wifiBaudrate) + "\r\n");     
    Serial1.begin(wifiBaudrate);     
  }
  return true;  
}


// join Wifi network
boolean joinWifi(){
  Serial.println("--------joinWifi--------");
  //writeReadWifi("AT+RST\r\n", 4000);  // reset module  
  //writeReadWifi("AT+GMR\r\n");  // get firmware version
  writeReadWifi("AT+CWMODE=1\r\n");  // station mode    
  //writeReadWifi("AT+CIPMODE=0\r\n");  // data mode        
  writeReadWifi("AT+CIPMUX=1\r\n");  // multiple connection mode    
  //writeReadWifi("AT+CWLAP\r\n", 4000);  // get access points        
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
    String s = writeReadWifi(conn + "\r\n", 5000);
    res = (s.indexOf("OK") != -1);
    if (res) break;
  }
  if (res) {
    for (int retry = 0; retry < 10; retry++){
      Serial.print("waiting for getting IP (DHCP)... retry ");
      Serial.println(retry);
      String s = writeReadWifi("AT+CIFSR\r\n", 500);  // get IP address      
      if (s.indexOf("OK") != -1) break;
      delay(1500);
    }          
    //writeReadWifi("AT+CWJAP?\r\n");  // list access point
    //writeReadWifi("AT+CIPMUX=0\r\n");  // multiple connection mode        
  } else Serial.println("ERROR joining");      
  return res;
}


void startServer(){
  Serial.println("--------startServer--------");  
  writeReadWifi("AT+CIPSERVER=1,80\r\n");   // start server
  writeReadWifi("AT+CIPSTO=5\r\n");   // set server timeout
}

void sendWifiTCP(String connId, String s){  
  //Serial.print("SEND=");
  //Serial.println(s);
  //return;  
  String data = "AT+CIPSEND=";
  data += connId;
  data += ",";
  data += s.length() + 2;
  data += "\r\n" + s;
  writeReadWifi(data + "\r\n", 1500);
  // close connection
  /*data = "AT+CIPCLOSE=";
  data += connId;
  writeReadWifi(data + "\r\n", 1500);*/
}

void runServer(){
  char data;
  while (Serial1.available()){
    data=Serial1.read();
    connData += char(data);
    Serial.print(data);
  }
  // +IPD,<id>,<len>,<data>  
  int idx1 = connData.indexOf("+IPD");
  if (idx1 != -1){    
    String msg = connData.substring(idx1);
    int idx2 = msg.indexOf("\r\n\r\n");
    if (idx2 != -1){
      connData = "";
      String connId = msg.substring(5,6);
      Serial.print("connId=");
      Serial.println(connId);
      String res = "HTTP/1.0 200 OK\r\n";
      res += "Content-Type: text/html\r\n";
      res += "Connection: close\r\n";
      String content = "<html><body><h1>Hello, this is your Arduino!</h1>";
      content += "<p>D5=" + String(digitalRead(5)) + "</p>"; 
      content += "<p>ADC0=" + String(analogRead(A0)) + "</p>"; 
      content += "</body></html>";
      res += "Content-Length: " + String(content.length()) + "\r\n";
      res += "\r\n";    
      res += content;
      sendWifiTCP(connId, res);
    }
  }
}

void readWifiSerial(){
  while(Serial1.available() > 0){
    if (Serial1.available() > 0) {
      char ch = Serial1.read();
      //Console.print("pfod ch=");
      //Console.println(ch);
      if (ch == '}') pfodCmdComplete = true; 
        else if (ch == '{') pfodCmd = "";
        else pfodCmd += ch;                
    }
    if (pfodCmdComplete) {
      Serial.print("pfod cmd=");
      Serial.println(pfodCmd);      
      if (pfodCmd == ".") {
        // main menu
        Serial1.println(F("{.mainmenu|m1~submenu1|m2~submenu2|m3~submenu3}"));        
      } else if (pfodCmd == "m1") {
          // submenu1
          Serial1.print(F("{.submenu1"));
          Serial1.print("|c1~D5=");
          Serial1.print(digitalRead(5));
          Serial1.print("|c2~A0=");
          Serial1.print(analogRead(A0));
          Serial1.println("}");                  
        }
        else {
          // no match
          Serial1.println("{}");         
        }
      Serial1.flush();
      pfodCmd = "";
      pfodCmdComplete = false;
    }
  }  
}



void setup(){  
  Serial.begin(19200);
  Serial.println("START");  
  if (connectWifi()){
    if (joinWifi()){
      startServer();
      Serial.println("------now waiting for incoming connections on IP shown above-----");    
    }
  }  
}

void loop(){
  runServer();  
}



