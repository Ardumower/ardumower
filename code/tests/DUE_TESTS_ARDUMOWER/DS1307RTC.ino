// ---- I2C helpers --------------------------------------------------------------
void I2CwriteTo(uint8_t device, uint8_t address, uint8_t val) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   Wire.write(val);        // send value to write
   Wire.endTransmission(); //end transmission
}

void I2CwriteTo(uint8_t device, uint8_t address, int num, uint8_t buff[]) {
   Wire.beginTransmission(device); //start transmission to device 
   Wire.write(address);        // send register address
   for (int i=0; i < num; i++){
     Wire.write(buff[i]);        // send value to write
   }
   Wire.endTransmission(); //end transmission
}

int I2CreadFrom(uint8_t device, uint8_t address, uint8_t num, uint8_t buff[], int retryCount = 0) {
  int i = 0;
  for (int j=0; j < retryCount+1; j++){
    i=0;
    Wire.beginTransmission(device); //start transmission to device 
    Wire.write(address);        //sends address to read from
    Wire.endTransmission(); //end transmission
  
    //Wire.beginTransmission(device); //start transmission to device (initiate again)
    Wire.requestFrom(device, num);    // request 6 bytes from device
  
    while(Wire.available())    //device may send less than requested (abnormal)
    {  
      buff[i] = Wire.read(); // receive a byte
      i++;
    }
    //Wire.endTransmission(); //end transmission
    if (num == i) return i;
    if (j != retryCount) delay(3);
  }
  return i;
}

boolean findDS1307(){
  byte buf[8];  
  for (byte addr=81; addr < 127; addr++){    
    Serial.print("testing address=");    
    Serial.print(addr);
    Serial.print(" ");
    if (I2CreadFrom(addr, 0x00, 8, buf, 1) == 8) {
      Serial.println("success!");
      DS1307_ADDRESS = addr;
      return true;
    }  
    Serial.println();
  }        
  Serial.println("error: no RTC module found");
  return false;
}

boolean readDS1307(){
  byte buf[8];  
  if (I2CreadFrom(DS1307_ADDRESS, 0x00, 8, buf, 3) != 8) {
    Serial.println("DS1307 comm error");    
    return false;
  }      
  if (   ((buf[0] >> 7) != 0) || ((buf[1] >> 7) != 0) || ((buf[2] >> 7) != 0) || ((buf[3] >> 3) != 0) 
      || ((buf[4] >> 6) != 0) || ((buf[5] >> 5) != 0) || ((buf[7] & B01101100) != 0) ) {    
    Serial.println("DS1307 data1 error");    
    return false;
  }
  minute    = 10*((buf[1] >>4) & B00000111) + (buf[1] & B00001111);
  hour      = 10*((buf[2] >>4) & B00000111) + (buf[2] & B00001111);
  dayOfWeek = (buf[3] & B00000111);// -1
  day       = 10*((buf[4] >>4) & B00000011) + (buf[4] & B00001111);
  month     = 10*((buf[5] >>4) & B00000001) + (buf[5] & B00001111);
  year      = 10*((buf[6] >>4) & B00001111) + (buf[6] & B00001111);
  if (    (minute > 59) || (hour > 23) || (dayOfWeek > 7)  
       || (month > 12)  || (day > 31)  || (day < 1)         
       || (month < 1)   || (year > 99) ){
    Serial.println("DS1307 data2 error");    
    //addErrorCounter(ERR_RTC_DATA);
    return false;
  }  
  year      += 2000;  
  return true;
}

boolean setDS1307(){
  byte buf[7];
  if (I2CreadFrom(DS1307_ADDRESS, 0x00, 7, buf, 3) != 7){
    Serial.println("DS1307 comm error");    
    return false;
  }
  buf[0] = buf[0] & B01111111; // enable clock
  buf[1] = ((minute / 10) << 4) | (minute % 10);
  buf[2] = ((hour   / 10) << 4) | (hour   % 10);
  buf[3] = dayOfWeek;//+1
  buf[4] = ((day    / 10) << 4) | (day    % 10);
  buf[5] = ((month  / 10) << 4) | (month  % 10);
  buf[6] = ((year % 100  / 10) << 4) | (year % 10);
  I2CwriteTo(DS1307_ADDRESS, 0x00, 7, buf);
  return true;
}


void testRead(){
  if (readDS1307()){
    Serial.print("reading RTC time=");
    Serial.print(hour);   
    Serial.print(":");
    Serial.print(minute);  
    Serial.print("  dateOfWeek=");
    Serial.print(dayOfWeek);
    Serial.print("  date=");
    Serial.print(day);
    Serial.print(".");
    Serial.print(month);
    Serial.print(".");
    Serial.println(year);  
  }  
  Serial.println();
}

void testWriteStatic(){
  Serial.print("writing new (static) RTC time...");  
  hour=20;
  minute=56;
  dayOfWeek=7;
  day=21;
  month=8;
  year=2016;
  setDS1307();
  Serial.println();
}

void testWrite(){
  Serial.print("writing new (random) RTC time...");  
  hour=random(0,24);
  minute=random(0,60);
  dayOfWeek=random(1,7);
  day=random(1,29);
  month=random(1,13);
  year=random(1990,2020);
  setDS1307();
  Serial.println();
}




