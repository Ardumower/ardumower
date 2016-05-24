// this is a pololu motor test

// MC33926 motor driver  
// Check http://forum.pololu.com/viewtopic.php?f=15&t=5272#p25031 for explanations.
//(8-bit PWM=255, 10-bit PWM=1023)
// IN1 PinPWM         IN2 IN2
// PWM                L     Forward
// nPWM               H     Reverse

//void setMC33926(int IN2, int pinPWM, int speed){
//  if (speed < 0){
 //   digitalWrite(IN2, HIGH) ;
 //   analogWrite(pinPWM, 255-((byte)abs(speed)));
 // } else {
 //   digitalWrite(IN2, LOW) ;
 //   analogWrite(pinPWM, ((byte)speed));
 // }
//}

//MC33926: PER motorsense
//resolution 525mV / A
//with 0 A is output also 0V and on AD pin I will read 0
//with 5 A is output 2,625 V and on the AD pin I will read 538
//Esempio:
//5A x 0.525V/A = 2.625V
// il pin leggeraà 2.625V x 1023 / 5V = 538
//NB: gli analog pin leggono 0-1023 0-5V

int pwm;
int ledPin = 13;
int statuspin;
int row=0;   //per il seriale

int IN1 = 11;  //----> IN1   (Pin Input PWM, PWM or -PWM)
int IN2= 7;    //----> IN2   (Pin DIR, L o H)
int pinmotorfault= A4;    //----> M2SF    (fault)
int pinmotorsense= A2;    //----> M2FB    (sense) 525mV/A
int motorPinEn= 8;   //----> EN      (abilita motori)

//letture
int ledStat;
int motorStat;
float senseStat;
float senseAmp;
int faultStat;


void setup()
{
  // definizioni 
  pinMode(ledPin,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(pinmotorfault,INPUT);
  pinMode(pinmotorsense,INPUT);
  pinMode(motorPinEn,OUTPUT);


  // settaggi iniziali
  digitalWrite(ledPin,LOW);   // setto il led spento
  digitalWrite(motorPinEn,HIGH);   // non abilito i motori perchè sono su 5V

  analogWrite(IN1,0); // setto la velocità nulla iniziale

  //contatto con la seriale
  Serial.begin(9600);
}



void loop()
{
  // STAMPA TUTTI I VALORI   
  row++;  

  if (row>15)
  {
   row=0;
   Serial.println("ROW,SET,2");
   Serial.println("CLEARDATA");
  }


  //FORWARD
  pwm=50;
  digitalWrite(ledPin,HIGH); //led acceso
  digitalWrite(IN2,LOW); //Forward
  analogWrite(IN1,pwm);

  delay(5);
  ledStat=digitalRead(ledPin);
  motorStat=digitalRead(IN2);

  do {//continua a leggere il valore di corrente fino a che è diverso da 0
    senseStat=analogRead(pinmotorsense);
    delay(5);
    senseAmp = 5*senseStat/1023/0.525*1000; // trasformo in milliAmpere (attenzione: prima divido e poi moltiplico, altrimenti vado fuori con la dimensione della variabile)
  } while(senseAmp==0);

  faultStat=digitalRead(pinmotorfault);
  delay(5);
  Serial.print("DATA,TIME,"); Serial.print("AVANTI"); Serial.print(",LED,"); Serial.print(ledStat); Serial.print(",IN1[PWM],"); Serial.print(pwm);Serial.print(",IN2[DIR],"); Serial.print(motorStat);Serial.print(",sense[mA],"); Serial.print(senseAmp);Serial.print(",fault [1=ok],"); Serial.println(faultStat);
  faultStat=0;
  delay(2000);


  //ZERO
  pwm=1;
  digitalWrite(ledPin,LOW); //led spento
  analogWrite(IN1,pwm);

  delay(5);
  ledStat=digitalRead(ledPin);
  motorStat=digitalRead(IN2);

  senseStat=analogRead(pinmotorsense);
  delay(5);
  senseAmp = 5*senseStat/1023/0.525*1000; // trasformo in milliAmpere (attenzione: prima divido e poi moltiplico, altrimenti vado fuori con la dimensione della variabile)

  faultStat=digitalRead(pinmotorfault);
  delay(5);
  Serial.print("DATA,TIME,"); Serial.print("FERMO"); Serial.print(",LED,"); Serial.print(ledStat); Serial.print(",IN1[PWM],"); Serial.print(pwm);Serial.print(",IN2[DIR],"); Serial.print(motorStat);Serial.print(",sense[mA],"); Serial.print(senseAmp);Serial.print(",fault [1=ok],"); Serial.println(faultStat);
  faultStat=0;
  delay(2000);


  //REVERSE
  pwm=50;
  digitalWrite(ledPin,HIGH); //led acceso
  digitalWrite(IN2,HIGH); //Reverse
  analogWrite(IN1,255-pwm);

  delay(5);
  ledStat=digitalRead(ledPin);
  motorStat=digitalRead(IN2);

  do {//continua a leggere il valore di corrente fino a che è diverso da 0
    senseStat=analogRead(pinmotorsense);
    delay(5);
    senseAmp = 5*senseStat/1023/0.525*1000; // trasformo in milliAmpere (attenzione: prima divido e poi moltiplico, altrimenti vado fuori con la dimensione della variabile)
  } while(senseAmp==0);

  faultStat=digitalRead(pinmotorfault);
  delay(5);
  Serial.print("DATA,TIME,"); Serial.print("INDIETRO"); Serial.print(",LED,"); Serial.print(ledStat); Serial.print(",IN1[PWM],"); Serial.print(pwm);Serial.print(",IN2[DIR],"); Serial.print(motorStat);Serial.print(",sense[mA],"); Serial.print(senseAmp);Serial.print(",fault [1=ok],"); Serial.println(faultStat);
  faultStat=0;
  delay(2000);

  //ZERO
  pwm=1;
  digitalWrite(ledPin,LOW); //led spento
  analogWrite(IN1,255-pwm);

  delay(5);
  ledStat=digitalRead(ledPin);
  motorStat=digitalRead(IN2);

  senseStat=analogRead(pinmotorsense);
  delay(5);
  senseAmp = 5*senseStat/1023/0.525*1000; // trasformo in milliAmpere (attenzione: prima divido e poi moltiplico, altrimenti vado fuori con la dimensione della variabile)

  faultStat=digitalRead(pinmotorfault);
  delay(5);
  Serial.print("DATA,TIME,"); Serial.print("FERMO"); Serial.print(",LED,"); Serial.print(ledStat); Serial.print(",IN1[PWM],"); Serial.print(pwm);Serial.print(",IN2[DIR],"); Serial.print(motorStat);Serial.print(",sense[mA],"); Serial.print(senseAmp);Serial.print(",fault [1=ok],"); Serial.println(faultStat);
  faultStat=0;
  delay(2000);

}


