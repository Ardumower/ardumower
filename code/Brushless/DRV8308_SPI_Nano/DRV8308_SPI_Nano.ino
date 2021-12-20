/*
 * Adrumover DIY Brushless Driver test & evaluation program
 * You will find more informaztion on 
 * https://wiki.ardumower.de/index.php?title=DIY_Brushless_Driver_Board
 * 
 * This is a tiny program to evaluate and test the DRV8308 programming parameters 
 * with your motors. For more information refer to the DRC8308 datasheet. 
 * The register description starts on page 38 of the datasheet PDF. 
 * For questions contact BerndS in the ArduMower.de forum.
 * 
 * ATTENTION motor can start turning unexpected!!
 * This is only for testing, take care of the turning motor!! Don't tuch the motor!
 * 
 * Version 1.0.2  /  last change 20.12.2021
 * change 28.07.2021 : #define Reg00 0b1001001101010101 to #define Reg00 0b1101001101010101  
 * change 20.12.2021 : p - Comand added in ?-Massage
 * 
 * Use an Arduino Nano
 * Setup Baud to 115200
*/
#include <SPI.h>

//Ardumower BL  Motorparameter                 
#define Reg00 0b1101001101010101   
//                  ^^^   ^^
//                 EN BRK Control-MODE: 01=PWM , 10=SPI Register 0B PWM
//                   Dir
#define Reg01 30                   
#define Reg02 0b0000001110110100    
#define Reg03 0b1110100000000000    // MOD 120 = 2048(0b0101100000000000) if MOD 120 = 3970 use 0b0101111110000010
#define Reg04 0b0000010010010010     
#define Reg05 0b0011100000000111    
#define Reg06 0b0000010010110000    
#define Reg07 950
#define Reg08 0b0000000100101100      //300
#define Reg09 0b0000001001011000      //600
#define Reg0A 0b10000011100101100
#define Reg0B 0

//SPI definition 
#define SCS  10
#define MOSI 11 //  MOSI, for "Master Out / Slave In".
#define MISO 12 //  MISO, for "Master In / Slave Out".
#define SCLK 13 //  clk
#define adress 0x2A

//Pin definition
#define MotDirPin 6
#define MotBRKPin 4
#define MotSpdPin 3
#define MotEnlPin 8

#define PWMsteps 4

#define Burn_Enl false // evaluation the right parameter, let Burn_Enl false / if you will burn OTP change Burn_Enl true

int i,dir, PWMspeed, CTRL_DRV8308;
char  inByte, cmd;
bool cw=1;
unsigned int Register;

void setup() { 
  pinMode(SCS, OUTPUT);
  pinMode(MotDirPin, OUTPUT);
  pinMode(MotBRKPin, OUTPUT);
  pinMode(MotSpdPin, INPUT);
  pinMode(MotBRKPin, OUTPUT);
  pinMode(MotEnlPin, OUTPUT);
    
  digitalWrite(MotBRKPin,HIGH);
  digitalWrite(MotDirPin,HIGH);
  digitalWrite(SCS, LOW);
  digitalWrite(MotEnlPin,LOW);

  Serial.begin(115200);
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  Serial.println ("Reg. before initialisation");
  printAllReg();
  initDRV8308();
  Serial.println ("Reg. after initialisation");
  printAllReg();
  if(Burn_Enl)Serial.println ("Take care BURN functionist enabled !!");
}


void loop() {
  if (Serial.available()) {
    inByte = Serial.read();
    Serial.println (inByte);
  }
  switch (inByte){
    case 'B':
    {
     cmd = 'B';
     burnOTP();
     inByte=' ';
    }
      break;
      
    case 'd':
    {
     cmd = 'd';
     cw=!cw;
     writeReg(0x0B,0);
     delay(100);
     if (cw)writeReg(0x00,Reg00 & 0b1111101111111111);
       else writeReg(0x00,Reg00 | 0b0000010000000000);
    }
      break;
      
    case 'f':
    {
     cmd = 'f';
     PWMspeed=4095;
    }
      break; 
      
    case 'h':
    {
     cmd = "h"; 
     PWMspeed=2047;
    }
      break;  
       
    case 'l':
    {
     cmd = "l"; 
     PWMspeed=512;
    }
      break;

    case 'o':
    {
     cmd = 'o';
     inByte = 'o' ;
     up_down();
    }
      break; 
            
    case 'p':
    {
     cmd = 'p'; 
     printAllReg();
    }
      break;
      
    case 's':
    {
     cmd = 's';
     PWMspeed=0; 
     cmd="s";
    }
      break;  
      
    case 't':
    {
     cmd = 't';
     inByte = ' ' ;
     up_down();
    }
      break; 
      
    case '+':
    {
     cmd = '+'; 
     PWMspeed=PWMspeed+128;
    }
      break; 
      
        case '-':
    {
     cmd = '-'; 
     PWMspeed=PWMspeed-128;
    }
      break;   
         
    case '?':
    {
     cmd = '-'; 
       Serial.println ("valid commands");
       Serial.println ("B : burn OTP memory (set ' #define Burn_Enl true ' befor burning) ");
       Serial.println ("d : change direction ");
       Serial.println ("f : full speed 4095");
       Serial.println ("h : half speed 2047");
       Serial.println ("l : low speed 512");
       Serial.println ("o : ongoing test, use s to stop");
       Serial.println ("p : print screen OTP-Reg.");
       Serial.println ("s : stop");
       Serial.println ("t : speed up & down, only one time");
       Serial.println ("- : decrease speed +128");
       Serial.println ("+ : increase speed +128");
       Serial.println ("? : this help text");
    }
      break;  
        
    default :
     {
     }
    break;
  }
  writeReg(0x0B,PWMspeed);
}
