
#define CONSOLE SerialUSB


void setup(){
  CONSOLE.begin(115200);
  Serial3.begin(115200);
  delay(2000);
  CONSOLE.println("START");
}

void loop(){
  while(Serial3.available()){
    char ch = Serial3.read();
    CONSOLE.print(ch);
  }
}

