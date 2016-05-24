
/* Bluetooth RSSI monitor (HC-05 module connected to serial2)
  (Remember to connect KEY pin to 3.3V after powering on)

   Arduino Mega
 */

#include <Arduino.h>

#define pinBTKey 41
#define FREQ 2457
  

// convert RSSI to distance (meters)
// http://en.wikipedia.org/wiki/FSPL
// FSPL explicitly requires “free space” for calculation, while most Wifi signals are obstructed by walls and other materials.
// Ideally, we will want to sample the signal strength many times (10+) to account for varying interference.

float calculateDistance(double levelInDb, double freqInMHz)    {
   float exp_ = (27.55 - (20 * log10(freqInMHz)) + abs(levelInDb)) / 20.0;
   return pow(10.0, exp_);
}


// Trilateration algorithm ("three distances known")
void getCoordinateWithBeacon(float ax, float ay, float dA, // 1st distance
                             float bx, float by, float dB, // 2nd distance
                             float cx, float cy, float dC, // 3rd distance
                             float &rx, float &ry) {       // result
    float W, Z, x, y, y2;
    W = dA*dA - dB*dB - ax*ax - ay*ay + bx*bx + by*by;
    Z = dB*dB - dC*dC - bx*bx - by*by + cx*cx + cy*cy;

    x = (W*(cy-by) - Z*(by-ay)) / (2 * ((bx-ax)*(cy-by) - (cx-bx)*(by-ay)));
    y = (W - 2*x*(bx-ax)) / (2*(by-ay));
    //y2 is a second measure of y to mitigate errors
    y2 = (Z - 2*x*(cx-bx)) / (2*(cy-by));

    y = (y + y2) / 2;
    
    rx = x;
    ry = y;    
}


int hex2int(String a)
{
    int i;
    unsigned int val = 0;

    for(i=0;i<a.length();i++)
       if(a[i] <= 57)
        val += (a[i]-48)*(1<<(4*(a.length()-1-i)));
       else
        val += (a[i]-55)*(1<<(4*(a.length()-1-i)));
    return (signed int)val;
}

int stringToInt(String &s){
  float v;
  char tmp[20];  
  s.toCharArray(tmp, sizeof(tmp));
  v = atoi(tmp);    
  //v = strtod(tmp, NULL);
  /*Console.print(s);
  Console.print("=");
  Console.println(v, 6);   */
  return v;
}

boolean readBT(String &s){  
  if (Serial2.available()){    
    while (Serial2.available()){
      char data = Serial2.read();
      s += (char)data;          
      if (!Serial2.available()) delay(1);      
    }            
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
  String r;
  readBT(r);
  Serial.print("receiving: ");
  Serial.print(r);  
}

// +INQ:1234:56:0,1F1F,FFC0
// +INQ:1234:56:0,1F1F,FFC0
// +INQ:1234:56:0,1F1F,FFC0
// OK
void parseRSSI(String s){  
  /*Serial.print("parsing ");
  Serial.println(s);  
  Serial.println();  */
  while (true){
    int idx = s.indexOf('+INQ');
    if (idx == -1) break;
    
    idx = s.indexOf(',');
    if (idx == -1) break;
    String addr = s.substring(0, idx);                
    s = s.substring(idx+1);                
    
    idx = s.indexOf(',');
    if (idx == -1) break;
    String equip = s.substring(0, idx);                
    s = s.substring(idx+1);                
        
    idx = s.indexOf('\r');
    if (idx == -1) break;
    String rssi = s.substring(0, idx);                        
    int rssiValue = hex2int(rssi);
    float dist = calculateDistance(rssiValue, FREQ);
    Serial.print("rssi=");
    Serial.print(rssi);
    Serial.print("\t");
    Serial.print(rssiValue);
    Serial.print("\t");
    Serial.println(dist);
    s = s.substring(idx+24);
  }
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
  //sendReadBT("AT+IPSCAN=1024,512,1024,512\r\n");         
  sendReadBT("AT+IPSCAN=1024,512,1024,512\r\n");         
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
  String r;
  while(true){    
    if (readBT(r)){
      parseRSSI(r);
      sendBT("AT+INQ\r\n");              
      r = "";
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
  sendReadBT("AT+IPSCAN=1024,512,1024,512\r\n");       
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




