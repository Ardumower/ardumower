/*

ESP8266 ESP-01 Wifi module - test (Arduino Mega)

wiring (IC side):
                                ESP8266-01
Arduino Mega TX1 ------------RX---1 2---VCC (3.3V)
                          GPIO0---3 4---nRST
               |Antenna|  GPIO2---5 6---nCHPD ---------- connect to VCC (3.3V)
                            GND---7 8---TX-------------- RX  Arduino Mega RX1

*/



String wifiSSID = "GRAUNET";
String wifiPass = "19779";



void setup(){
  Serial.begin(19200);
  Serial.println("START");
  
  Serial1.begin(115200); // some older modules: 57600
  Serial1.setTimeout(5000);
  
  writeReadWifi("AT+RST\r");
}


void writeWifi(String s){
  Serial.print("send: "+s);
  Serial1.print(s);
}


String readWifi(){
  Serial.print("received:");
  String s;
  char data;
  while (Serial1.available()){
    data=Serial1.read();
    s += char(data);
    Serial.print(data);
  }
  return s;
}

void writeReadWifi(String s){
  writeWifi(s);
  delay(1000);
  String res = readWifi();    
  int counter = 0;
  while ((res.startsWith("ERROR") && counter < 4)){
    // retry 
    writeWifi(s);
    delay(1000);    
    readWifi();
    counter++;
  }        
  Serial.println();
}


void loop(){
  
    
}



