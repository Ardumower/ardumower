/*
  pfodApp test
  Android remote control (pfod App)
  For a detailed specification of the pfodApp protocol, please visit:  http://www.forward.com.au/pfod/  
*/

#define BAUDRATE 19200            // serial output baud rate
#define PFOD_BAUDRATE 19200       // pfod app serial output baud rate


#define Console Serial
#define Bluetooth Serial2

int values[30] = {0};
int counter = 0;
unsigned long nextCounterTime = 0;
String pfodCmd;
boolean pfodCmdComplete = false;


int stringToInt(String &s){
  int v;
  char tmp[20];  
  s.toCharArray(tmp, sizeof(tmp));
  v = atoi(tmp);    
  return v;
}


void sendYesNo(int value){
  if (value == 1) Bluetooth.print("YES");
    else Bluetooth.print("NO");
}


void sendMainMenu(boolean update){
  if (update) Bluetooth.print("{:"); else {
    Bluetooth.print(F("{.Test`1000"));      
  }
  Bluetooth.print("|c00~Counter is ");    
  Bluetooth.print(counter);  
  for (int i=0; i < 30; i++){
    Bluetooth.print("|m");
    Bluetooth.print(i);
    Bluetooth.print("~Item ");
    Bluetooth.print(i);
    Bluetooth.print(" ");  
    sendYesNo(values[i]);  
  }  
  Bluetooth.println(F("}"));        
}

void processMainMenu(String pfodCmd){
  int idx = pfodCmd.indexOf('m');
  String s = pfodCmd.substring(idx + 1);      
  idx = stringToInt(s);
  //Console.print("idx=");
  //Console.println(idx);
  values[idx] =! values[idx];
  sendMainMenu(true);  
}

void readSerial(){
  while(Bluetooth.available() > 0){
    if (Bluetooth.available() > 0) {
      char ch = Bluetooth.read();
      if (ch == '}') pfodCmdComplete = true; 
        else if (ch == '{') pfodCmd = "";
        else pfodCmd += ch;                
    }
    if (pfodCmdComplete) {
      Console.print("PFOD CMD=");
      Console.println(pfodCmd);      
      if (pfodCmd == ".") sendMainMenu(false);              
        else if (pfodCmd.startsWith("m")) processMainMenu(pfodCmd);            
        else {
          // no match
          Bluetooth.println("{}");         
        }
      Bluetooth.flush();
      pfodCmd = "";
      pfodCmdComplete = false;
    }
  }  
}

void setup(){
  Console.begin(BAUDRATE);    
  Bluetooth.begin(PFOD_BAUDRATE);
  Console.println("START");
}

void loop(){
  readSerial();
  if (millis() >= nextCounterTime) {
    counter++;
    nextCounterTime = millis() + 1000;
    Console.print("counter=");
    Console.println(counter);
  }
}



