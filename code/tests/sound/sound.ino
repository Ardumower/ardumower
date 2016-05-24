// Arduino Sound Sensor test (LM386)

// Arduino A0  --- Arduino Sound Sensor Mic1 --- micro   (pin1)
//                 Arduino Sound Sensor Mic2 --- micro   (pin2)

// The LED will go on if there's noise


#define pinRain A0
#define pinLED 13


unsigned long nextTime = 0;
unsigned long sum = 0;


void setup(){
  Serial.begin(19200);
  Serial.println("START");
  pinMode(pinLED, OUTPUT);
}

void loop(){
  int v = analogRead(pinRain);
  sum += v;
  if (millis() >= nextTime){    
    nextTime = millis() + 1000;
    Serial.print("sum=");
    Serial.println(sum);
    if (sum > 40) digitalWrite(pinLED, HIGH);
      else digitalWrite(pinLED, LOW);  
    sum = 0;
  }
  delay(10);
}


