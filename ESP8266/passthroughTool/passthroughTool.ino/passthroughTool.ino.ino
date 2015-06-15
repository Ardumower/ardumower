// Helper tool that links the Arduino Serial port that is connected to the USB to the Arduino Serial port that is connected to the ESP8266 module.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  
  //Serial.print("esp8266 passthrough\n");
}

void loop() {
  while (Serial1.available()>0){
    Serial.write(Serial1.read());
  }
  while (Serial.available()>0){
    Serial1.write(Serial.read());
  }

}
