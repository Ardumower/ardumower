// http://onlinesequencer.net/

#define pinBuzzer 53               // Buzzer

unsigned long nextTimeMelody = 0;
unsigned long nextTimeMelodyTone = 0;
int currMelody = 0;
int melodyToneIdx = 0;

enum {  
  //  Cf Df    Ff Gf Af
  // C  D  E  F  G  A  B 
  TONE_C4, TONE_Cf4, TONE_D4, TONE_Df4, TONE_E4, TONE_F4, TONE_Ff4, TONE_G4, TONE_Gf4, TONE_A4, TONE_Af4, TONE_B4,
  TONE_C5, TONE_Cf5, TONE_D5, TONE_Df5, TONE_E5, TONE_F5, TONE_Ff5, TONE_G5, TONE_Gf5, TONE_A5, TONE_Af5, TONE_B5,  
}; 

int frequencies[] = { 
     262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
     520, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988
};

int melodies[] = {
  TONE_F5,  TONE_C5,  TONE_D5,  TONE_A4  
};

void setup(){
  pinMode(pinBuzzer, OUTPUT);    
}

void runBuzzer(){
  if (millis() >= nextTimeMelodyTone){    
    if (millis() > nextTimeMelodyTone+100){              
      int freqIdx = melodies[melodyToneIdx];
      int freq = frequencies[freqIdx];
      tone(pinBuzzer, freq);  
      nextTimeMelodyTone = millis() + 300;    
      melodyToneIdx++;  
      if (melodyToneIdx == 5) {
        noTone(pinBuzzer);
        while (true);
        //melodyToneIdx=0;
      }
    } else noTone(pinBuzzer);
  }
}  
  
void playMelody(int number){
}

void loop(){
  if  (millis() >= nextTimeMelody){
    currMelody = (currMelody + 1) % 2;
    playMelody(currMelody);
  }
  runBuzzer();  
  delay(100);  
}


