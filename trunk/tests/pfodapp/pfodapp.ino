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
float sliderValue = 42;

unsigned long nextCounterTime = 0;
String pfodCmd;
boolean pfodCmdComplete = false;


float stringToFloat(String &s){
  float v;
  char tmp[20];  
  s.toCharArray(tmp, sizeof(tmp));
  v = atof(tmp);    
  return v;
}

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

// NOTE: pfodApp rev57 changed slider protocol:  displayValue = (sliderValue + offset) * scale
void sendSlider(String cmd, String title, float value, String unit, double scale, float maxvalue, float minvalue){
  Bluetooth.print("|"); 
  Bluetooth.print(cmd);  
  Bluetooth.print("~");    
  Bluetooth.print(title);
  Bluetooth.print(" `");      
  Bluetooth.print(((int)(value/scale)));
  Bluetooth.print("`");  
  Bluetooth.print(((int)(maxvalue/scale)));
  Bluetooth.print("`");
  Bluetooth.print(((int)(minvalue/scale)));
  Bluetooth.print("~ ~");
  if (scale == 10) Bluetooth.print("10");
    else if (scale == 1) Bluetooth.print("1");
    else if (scale == 0.1) Bluetooth.print("0.1");
    else if (scale == 0.01) Bluetooth.print("0.01");
    else if (scale == 0.001) Bluetooth.print("0.001");
    else if (scale == 0.0001) Bluetooth.print("0.0001");
}


void processSlider(String result, float &value, double scale){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  float v = stringToFloat(s);
  value = v * scale;  
}

void sendMainMenu(boolean update){
  if (update) Bluetooth.print("{:"); else {
    Bluetooth.print(F("{.Test`1000"));      
  }
  Bluetooth.print("|m0_0~Counter is ");    
  Bluetooth.print(counter);  
  
  sendSlider("m1_0", F("Slider1 "), sliderValue, "", 1, 1000, 0);
  sendSlider("m1_1", F("Slider2 "), sliderValue, "", 1, 1000, 0);    
  sendSlider("m1_2", F("Slider3 "), sliderValue, "", 1, 1000, 0);  
  sendSlider("m1_3", F("Slider4 "), sliderValue, "", 1, 1000, 0);    
  sendSlider("m1_4", F("Slider5 "), sliderValue, "", 1, 1000, 0);      
  
  for (int i=0; i < 30; i++){
    Bluetooth.print("|m2_");
    Bluetooth.print(i);
    Bluetooth.print("~Item ");
    Bluetooth.print(i);
    Bluetooth.print(" ");  
    sendYesNo(values[i]);  
  }  
  Bluetooth.println(F("}"));        
}

void processMainMenu(String pfodCmd){
  if (pfodCmd.startsWith("m1")){
    processSlider(pfodCmd, sliderValue, 1);    
  } else if (pfodCmd.startsWith("m2")) {  
    int idx = pfodCmd.indexOf('_');
    String s = pfodCmd.substring(idx + 1);      
    idx = stringToInt(s);
    //Console.print("idx=");
    //Console.println(idx);
    values[idx] =! values[idx];
  } 
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



