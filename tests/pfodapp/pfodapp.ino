/*
  pfodApp test
  Android remote control (pfod App)
  For a detailed specification of the pfodApp protocol, please visit:  http://www.forward.com.au/pfod/  
*/

#define BAUDRATE 19200            // serial output baud rate
#define PFOD_BAUDRATE 19200       // pfod app serial output baud rate


#define Console Serial
#define Bluetooth Serial2

//int values[30] = {0};
int counter = 0;
float sliderValue0 = 42;
float sliderValue1 = 42;
float sliderValue2 = 42;
float sliderValue3 = 42;
float sliderValue4 = 42;
float sliderValue5 = 42;
float sliderValue6 = 42;
float sliderValue7 = 42;
float sliderValue8 = 42;
float sliderValue9 = 42;
float sliderValue10 = 42;
float sliderValue11 = 42;
float sliderValue12 = 42;
float sliderValue13 = 42;
float sliderValue14 = 42;
float sliderValue15 = 42;
float sliderValue16 = 42;
float sliderValue17 = 42;
float sliderValue18 = 42;
float sliderValue19 = 42;
float sliderValue20 = 42;
float sliderValue21 = 42;
float sliderValue22 = 42;
float sliderValue23 = 42;
float sliderValue24 = 42;
float sliderValue25 = 42;
float sliderValue26 = 42;
float sliderValue27 = 42;
float sliderValue28 = 42;
float sliderValue29 = 42;
float sliderValue30 = 42;
float sliderValue31 = 42;
float sliderValue32 = 42;
float sliderValue33 = 42;
float sliderValue34 = 42;
float sliderValue35 = 42;
float sliderValue36 = 42;
float sliderValue37 = 42;
float sliderValue38 = 42;
float sliderValue39 = 42;
float sliderValue40 = 42;
float sliderValue41 = 42;
float sliderValue42 = 42;
float sliderValue43 = 42;
float sliderValue44 = 42;
float sliderValue45 = 42;





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
  
  sendSlider("m100", F("Slider1 "), sliderValue0, "", 1, 1000, 0);
  sendSlider("m101", F("Slider2 "), sliderValue1, "", 1, 1000, 0);    
  sendSlider("m102", F("Slider3 "), sliderValue2, "", 1, 1000, 0);  
  sendSlider("m103", F("Slider4 "), sliderValue3, "", 1, 1000, 0);    
  sendSlider("m104", F("Slider5 "), sliderValue4, "", 1, 1000, 0);      
  sendSlider("m105", F("Slider6 "), sliderValue5, "", 1, 1000, 0);      
  sendSlider("m106", F("Slider7 "), sliderValue6, "", 1, 1000, 0);      
  sendSlider("m107", F("Slider8 "), sliderValue7, "", 1, 1000, 0);      
  sendSlider("m108", F("Slider9 "), sliderValue8, "", 1, 1000, 0);      
  sendSlider("m109", F("Slider10 "), sliderValue9, "", 1, 1000, 0);      
  sendSlider("m110", F("Slider11 "), sliderValue10, "", 1, 1000, 0);      
  sendSlider("m111", F("Slider12 "), sliderValue11, "", 1, 1000, 0);      
  sendSlider("m112", F("Slider13 "), sliderValue12, "", 1, 1000, 0);      
  sendSlider("m113", F("Slider14 "), sliderValue13, "", 1, 1000, 0);      
  sendSlider("m114", F("Slider15 "), sliderValue14, "", 1, 1000, 0);      
  sendSlider("m115", F("Slider16 "), sliderValue15, "", 1, 1000, 0);      
  sendSlider("m116", F("Slider17 "), sliderValue16, "", 1, 1000, 0);      
  sendSlider("m117", F("Slider18 "), sliderValue17, "", 1, 1000, 0);      
  sendSlider("m118", F("Slider19 "), sliderValue18, "", 1, 1000, 0);      
  sendSlider("m119", F("Slider20 "), sliderValue19, "", 1, 1000, 0);      
  sendSlider("m120", F("Slider21 "), sliderValue20, "", 1, 1000, 0);      
  sendSlider("m121", F("Slider22 "), sliderValue21, "", 1, 1000, 0);      
  sendSlider("m122", F("Slider23 "), sliderValue22, "", 1, 1000, 0);      
  sendSlider("m123", F("Slider24 "), sliderValue23, "", 1, 1000, 0);      
  sendSlider("m124", F("Slider25 "), sliderValue24, "", 1, 1000, 0);      
  sendSlider("m125", F("Slider26 "), sliderValue25, "", 1, 1000, 0);      
  sendSlider("m126", F("Slider27 "), sliderValue26, "", 1, 1000, 0);      
  sendSlider("m127", F("Slider28 "), sliderValue27, "", 1, 1000, 0);      
  sendSlider("m128", F("Slider29 "), sliderValue28, "", 1, 1000, 0);      
  sendSlider("m129", F("Slider30 "), sliderValue29, "", 1, 1000, 0);      
  sendSlider("m130", F("Slider31 "), sliderValue30, "", 1, 1000, 0);      
  sendSlider("m131", F("Slider32 "), sliderValue31, "", 1, 1000, 0);      
  sendSlider("m132", F("Slider33 "), sliderValue32, "", 1, 1000, 0);      
  sendSlider("m133", F("Slider34 "), sliderValue33, "", 1, 1000, 0);      
  sendSlider("m134", F("Slider35 "), sliderValue34, "", 1, 1000, 0);      
  sendSlider("m135", F("Slider36 "), sliderValue35, "", 1, 1000, 0);      
  sendSlider("m136", F("Slider37 "), sliderValue36, "", 1, 1000, 0);      
  sendSlider("m137", F("Slider38 "), sliderValue37, "", 1, 1000, 0);      
  sendSlider("m138", F("Slider39 "), sliderValue38, "", 1, 1000, 0);      
  sendSlider("m139", F("Slider40 "), sliderValue39, "", 1, 1000, 0);      
  sendSlider("m140", F("Slider41 "), sliderValue40, "", 1, 1000, 0);      
  sendSlider("m141", F("Slider42 "), sliderValue41, "", 1, 1000, 0);      
  sendSlider("m142", F("Slider43 "), sliderValue42, "", 1, 1000, 0);      
  sendSlider("m143", F("Slider44 "), sliderValue43, "", 1, 1000, 0);      
  sendSlider("m144", F("Slider45 "), sliderValue44, "", 1, 1000, 0);      
  sendSlider("m145", F("Slider46 "), sliderValue45, "", 1, 1000, 0);      
  
  
  Bluetooth.println(F("}"));        
}

void processMainMenu(String pfodCmd){
  if (pfodCmd.startsWith("m100")) processSlider(pfodCmd, sliderValue0, 1);    
   else if (pfodCmd.startsWith("m101")) processSlider(pfodCmd, sliderValue1, 1); 
   else if (pfodCmd.startsWith("m102")) processSlider(pfodCmd, sliderValue2, 1); 
   else if (pfodCmd.startsWith("m103")) processSlider(pfodCmd, sliderValue3, 1); 
   else if (pfodCmd.startsWith("m104")) processSlider(pfodCmd, sliderValue4, 1); 
   else if (pfodCmd.startsWith("m105")) processSlider(pfodCmd, sliderValue5, 1); 
   else if (pfodCmd.startsWith("m106")) processSlider(pfodCmd, sliderValue6, 1); 
   else if (pfodCmd.startsWith("m107")) processSlider(pfodCmd, sliderValue7, 1); 
   else if (pfodCmd.startsWith("m108")) processSlider(pfodCmd, sliderValue8, 1); 
   else if (pfodCmd.startsWith("m109")) processSlider(pfodCmd, sliderValue9, 1); 
   else if (pfodCmd.startsWith("m110")) processSlider(pfodCmd, sliderValue10, 1); 
   else if (pfodCmd.startsWith("m111")) processSlider(pfodCmd, sliderValue11, 1); 
   else if (pfodCmd.startsWith("m112")) processSlider(pfodCmd, sliderValue12, 1); 
   else if (pfodCmd.startsWith("m113")) processSlider(pfodCmd, sliderValue13, 1); 
   else if (pfodCmd.startsWith("m114")) processSlider(pfodCmd, sliderValue14, 1); 
   else if (pfodCmd.startsWith("m115")) processSlider(pfodCmd, sliderValue15, 1); 
   else if (pfodCmd.startsWith("m116")) processSlider(pfodCmd, sliderValue16, 1); 
   else if (pfodCmd.startsWith("m117")) processSlider(pfodCmd, sliderValue17, 1); 
   else if (pfodCmd.startsWith("m118")) processSlider(pfodCmd, sliderValue18, 1); 
   else if (pfodCmd.startsWith("m119")) processSlider(pfodCmd, sliderValue19, 1); 
   else if (pfodCmd.startsWith("m120")) processSlider(pfodCmd, sliderValue20, 1); 
   else if (pfodCmd.startsWith("m121")) processSlider(pfodCmd, sliderValue21, 1); 
   else if (pfodCmd.startsWith("m122")) processSlider(pfodCmd, sliderValue22, 1); 
   else if (pfodCmd.startsWith("m123")) processSlider(pfodCmd, sliderValue23, 1); 
   else if (pfodCmd.startsWith("m124")) processSlider(pfodCmd, sliderValue24, 1); 
   else if (pfodCmd.startsWith("m125")) processSlider(pfodCmd, sliderValue25, 1); 
   else if (pfodCmd.startsWith("m126")) processSlider(pfodCmd, sliderValue26, 1); 
   else if (pfodCmd.startsWith("m127")) processSlider(pfodCmd, sliderValue27, 1); 
   else if (pfodCmd.startsWith("m128")) processSlider(pfodCmd, sliderValue28, 1); 
   else if (pfodCmd.startsWith("m129")) processSlider(pfodCmd, sliderValue29, 1); 
   else if (pfodCmd.startsWith("m130")) processSlider(pfodCmd, sliderValue30, 1); 
   else if (pfodCmd.startsWith("m131")) processSlider(pfodCmd, sliderValue31, 1); 
   else if (pfodCmd.startsWith("m132")) processSlider(pfodCmd, sliderValue32, 1); 
   else if (pfodCmd.startsWith("m133")) processSlider(pfodCmd, sliderValue33, 1); 
   else if (pfodCmd.startsWith("m134")) processSlider(pfodCmd, sliderValue34, 1); 
   else if (pfodCmd.startsWith("m135")) processSlider(pfodCmd, sliderValue35, 1); 
   else if (pfodCmd.startsWith("m136")) processSlider(pfodCmd, sliderValue36, 1); 
   else if (pfodCmd.startsWith("m137")) processSlider(pfodCmd, sliderValue37, 1); 
   else if (pfodCmd.startsWith("m138")) processSlider(pfodCmd, sliderValue38, 1); 
   else if (pfodCmd.startsWith("m139")) processSlider(pfodCmd, sliderValue38, 1); 
   else if (pfodCmd.startsWith("m140")) processSlider(pfodCmd, sliderValue40, 1); 
   else if (pfodCmd.startsWith("m141")) processSlider(pfodCmd, sliderValue41, 1); 
   else if (pfodCmd.startsWith("m142")) processSlider(pfodCmd, sliderValue42, 1); 
   else if (pfodCmd.startsWith("m143")) processSlider(pfodCmd, sliderValue43, 1); 
   else if (pfodCmd.startsWith("m144")) processSlider(pfodCmd, sliderValue44, 1); 
   else if (pfodCmd.startsWith("m145")) processSlider(pfodCmd, sliderValue45, 1); 

    
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
    Console.println("variables =");
    Console.print("Slider Value6 = ");
    Console.println(sliderValue6);
    Console.print("Slider Value7 = ");
    Console.println(sliderValue7);
    Console.print("Slider Value8 = ");
    Console.println(sliderValue8);
    Console.print("Slider Value9 = ");
    Console.println(sliderValue9);
    Console.print("Slider Value10 = ");
    Console.println(sliderValue10);
    Console.print("Slider Value11 = ");
    Console.println(sliderValue11);
    Console.print("Slider Value12 = ");
    Console.println(sliderValue12);
    Console.print("Slider Value13 = ");
    Console.println(sliderValue13);


  }
}



