// watch dog test for Arduino Due

#define pinBuzzer 53               // Buzzer

int counter = 0;

void watchdogSetup(void) {
  // do what you want here
}

void setup() 
{
  pinMode(pinBuzzer, OUTPUT);
	watchdogEnable(10000);
  Serial.begin(115200);
}

void loop() 
{
  delay(500);
  Serial.println(counter);
  if(counter >= 10)
  { 
    while(true)
    {
      Serial.println("loop");
      delay(100);
    }
  }
  counter++;
}
