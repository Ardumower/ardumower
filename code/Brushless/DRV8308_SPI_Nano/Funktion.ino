
// write DRV8309 One Time Programable memory
void burnOTP(){
      if(Burn_Enl){
        if(Serial.available())Serial.read();
       Serial.println ("Write OTP memory? It can programed only once! If yes, type 'Y'");
         do 
           inByte = Serial.read();
        while(!Serial.available());
        inByte = Serial.read();
        Serial.println (inByte);
        if (inByte=='Y'){ 
        Serial.println ("write OTP.");
         writeReg(0x2D,0x1213);
         writeReg(0x2D,0x1415);
         writeReg(0x2D,0x1617);
         writeReg(0x2D,0x1819);
         writeReg(0x39,0x0002);
         delay(25);
         writeReg(0x2D,0x0EDD);
       Serial.println ("OTP memory written.");
        }else Serial.println ("canceled, OTP memory NOT written!");
       } else Serial.println ("OTP memory NOT written!( Burn_Enl = false) ");
      }

// write DRV8309 Reg
void writeReg(int reg, int value)
{
  digitalWrite(SCS, HIGH);
  SPI.transfer(reg);   //Register
  SPI.transfer16(value);
  digitalWrite(SCS, LOW);
  delay(10);
  
}


void printAllReg() 
{
  Serial.println("Reg      Value");
  for (i = 0; i < 12; i++) {
    Serial.print("Reg."); Serial.print(i, HEX); Serial.print(":  ");
    digitalWrite(SCS, HIGH);
    SPI.transfer(0x80 | i);
    Register = SPI.transfer16(0);
    digitalWrite(SCS, LOW);
    Serial.println(Register, BIN);
    delay(25);
  }
  Serial.print("Reg."); Serial.print(0x2A, HEX); Serial.print(":  ");
  
  digitalWrite(SCS, HIGH);
  SPI.transfer(0x80 | 0x2A);
  Register = SPI.transfer16(0);
  digitalWrite(SCS, LOW);
  Serial.println(Register, BIN);
  delay(25);
}


void up_down() {
  Serial.println("acceleration....");
  for (i = 0; i < 4096; i = i + PWMsteps) {
  writeReg(0x0B,i);
   if (Serial.available()&&Serial.read()=='s') 
    {
      writeReg(0x0B,0);
      PWMspeed=0;
      return ;
    }
  } 
   Serial.println("hold speed for 15 sec. .....");
  delay (15000);
  Serial.println("slow down....");
  for (i = 4095; i >= 0; i = i - PWMsteps) {
   writeReg(0x0B,i);
   if (Serial.available()&&Serial.read()=='s') 
    {
      writeReg(0x0B,0);
      PWMspeed=0;
      return ;
    }
   }
   if(dir++)
   {
    writeReg(0x00,Reg00 & 0b1111101111111111);
    
    dir =0;
   }
   else {
      writeReg(0x00,Reg00 | 0b0000010000000000);
    }
 Serial.println("change direction....");   
 PWMspeed=0;  
}

void initDRV8308()
{
  writeReg(0x00,Reg00);
  writeReg(0x01,Reg01);
  writeReg(0x02,Reg02);
  writeReg(0x03,Reg03);
  writeReg(0x04,Reg04);
  writeReg(0x05,Reg05);
  writeReg(0x06,Reg06);
  writeReg(0x07,Reg07);
  writeReg(0x08,Reg08);
  writeReg(0x09,Reg09);
  writeReg(0x0A,Reg0A);
  writeReg(0x0B,Reg0B);
}    
