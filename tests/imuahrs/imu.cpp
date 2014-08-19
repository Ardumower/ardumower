/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "imu.h"
#include <Arduino.h>
#include <Wire.h>
#include "AHRS.h"
#include "drivers.h"

// -------------I2C addresses ------------------------
#define ADXL345B (0x53)          // ADXL345B acceleration sensor (GY-80 PCB)
#define HMC5883L (0x1E)          // HMC5883L compass sensor (GY-80 PCB)
#define L3G4200D (0xD2 >> 1)     // L3G4200D gyro sensor (GY-80 PCB)

#define pinLED 13

#define ADDR 256
#define MAGIC 4


struct {
  uint8_t xl;
  uint8_t xh;
  uint8_t yl;
  uint8_t yh;
  uint8_t zl;
  uint8_t zh;
} gyroFifo[32];



IMU::IMU(){
  hardwareInitialized = false;
  callCounter = 0;  
  errorCounter = 0;
  
  gyroOfs.x=gyroOfs.y=gyroOfs.z=0;  
  gyroNoise = 0;      
  gyroCounter = 0; 
  gyroYpr.yaw=gyroYpr.pitch=gyroYpr.roll=0;
  useGyroCalibration = false;
  lastGyroTime = millis();
  
  accelCounter = 0;
  useAccCalibration = true; 
  accPitch = 0;
  accRoll = 0;
  
  accMin.x=accMin.y=accMin.z = 0;
  accMax.x=accMax.y=accMax.z = 0;  
  accOfs.x=accOfs.y=accOfs.z = 0;
  accScale.x=accScale.y=accScale.z = 2;
  com.x=com.y=com.z=0;  
  comCal.x=comCal.y=comCal.z=0;  
  comCalB[0]=comCalB[1]=comCalB[2]=0;
  
  comCalA_1[0][0] = 1; 
  comCalA_1[0][1] = 0; 
  comCalA_1[0][2] = 0;   
  
  comCalA_1[1][0] = 0; 
  comCalA_1[1][1] = 1; 
  comCalA_1[1][2] = 0;   
  
  comCalA_1[2][0] = 0; 
  comCalA_1[2][1] = 0; 
  comCalA_1[2][2] = 1;     

  // compass heading deviation (degree/10 => degree)    
  for (int i=0; i < 36; i++){
    comDeviation[i] = i*10;
  }
  useComDeviation = true;     
}

// rescale to -PI..+PI
float IMU::scalePI(float v)
{
  float d = v;
  while (d < 0) d+=2*PI;
  while (d >= 2*PI) d-=2*PI;
  if (d >= PI) return (-2*PI+d); 
  else if (d < -PI) return (2*PI+d);
  else return d;  
}

// rescale to -180..+180
float IMU::scale180(float v)
{
  float d = v;
  while (d < 0) d+=2*180;
  while (d >= 2*180) d-=2*180;
  if (d >= 180) return (-2*180+d); 
  else if (d < -180) return (2*180+d);
  else return d;  
}


// computes minimum distance between x radiant (current-value) and w radiant (set-value)
float IMU::distancePI(float x, float w)
{
  // cases:   
  // w=330 degree, x=350 degree => -20 degree
  // w=350 degree, x=10  degree => -20 degree
  // w=10  degree, x=350 degree =>  20 degree
  // w=0   degree, x=190 degree => 170 degree
  // w=190 degree, x=0   degree => -170 degree 
  float d = scalePI(w - x);
  if (d < -PI) d = d + 2*PI;
  else if (d > PI) d = d - 2*PI;  
  return d;
}

float IMU::distance180(float x, float w)
{
  float d = scale180(w - x);
  if (d < -180) d = d + 2*180;
  else if (d > 180) d = d - 2*180;  
  return d;
}


// weight fusion (w=0..1) of two radiant values (a,b)
float IMU::fusionPI(float w, float a, float b)
{ 
  float c;
  if ((b >= PI/2) && (a <= -PI/2)){
    c = w * a + (1.0-w) * (b-2*PI);
  } else if ((b <= -PI/2) && (a >= PI/2)){
    c = w * (a-2*PI) + (1.0-w) * b;
  } else c = w * a + (1.0-w) * b;
  return scalePI(c);
}

void IMU::loadSaveCalib(boolean readflag){
  int addr = ADDR;
  short magic = MAGIC;
  eereadwrite(readflag, addr, magic); // magic
  eereadwrite(readflag, addr, accOfs);
  eereadwrite(readflag, addr, accScale);    
  eereadwrite(readflag, addr, comCalB);  
  eereadwrite(readflag, addr, comCalA_1);    
  for (int i=0; i < 36; i++){
    eereadwrite(readflag, addr, comDeviation[i]);    
  }
}

void IMU::loadCalib(){
  short magic = 0;
  int addr = ADDR;
  eeread(addr, magic);
  if (magic != MAGIC) {
    Console.println(F("IMU error: no calib data"));
    return;  
  }
  Console.println(F("IMU: found calib data"));
  loadSaveCalib(true);
}

void IMU::saveCalib(){
  loadSaveCalib(false);
}

void IMU::deleteCalib(){
  int addr = ADDR;
  eewrite(addr, (short)0); // magic  
  accOfs.x=accOfs.y=accOfs.z=0;
  accScale.x=accScale.y=accScale.z=2;  
  comCalA_1[0][0] = 1; comCalA_1[0][1] = 0; comCalA_1[0][2] = 0;
  comCalA_1[1][0] = 0; comCalA_1[1][1] = 1; comCalA_1[1][2] = 0;
  comCalA_1[2][0] = 0; comCalA_1[2][1] = 0; comCalA_1[2][2] = 1;
  comCalB[0] = comCalB[1] = comCalB[2] = 0;
  for (int i=0; i < 36; i++) comDeviation[i] = i*10-180;
  Console.println("IMU calibration deleted");  
}

void IMU::setComCalParam(int type, int i, int j, float value){  
  if (type == 0){
    comCalB[i]=value;    
  } else if (type == 1){
    comCalA_1[i][j]=value;    
  }
}

void IMU::printPt(point_float_t p){
  Console.print(p.x);
  Console.print(",");    
  Console.print(p.y);  
  Console.print(",");
  Console.println(p.z);  
}

void IMU::printCalib(){
  Console.println(F("--------"));
  Console.print(F("accOfs="));
  printPt(accOfs);
  Console.print(F("accScale="));
  printPt(accScale);
  Console.print(F("comCalB="));
  for (int i=0; i < 3; i++){
    Console.print(comCalB[i], 6);
    Console.print("  ");
  }  
  Console.print(F("comCalA_1="));
  for (int i=0; i < 3; i++){
    for (int j=0; j < 3; j++){
      Console.print(comCalA_1[i][j], 6);
      Console.print("  ");
    }    
  }    
  Console.println();    
  Console.println(F("comDev"));  
  for (int i=0; i < 36; i++){  
    Console.print(i*10-180);  
    Console.print("=");      
    Console.println(comDeviation[i]);
  }
  Console.println(F("--------"));
}



// calculate gyro offsets
void IMU::calibGyro(){
  Console.println(F("calibGyro"));  
  useGyroCalibration = false;
  gyroOfs.x = gyroOfs.y = gyroOfs.z = 0;
  point_float_t ofs;
  while(true){    
    float zmin =  99999;
    float zmax = -99999;  
    gyroNoise = 0;
    ofs.x = ofs.y = ofs.z = 0;      
    for (int i=0; i < 50; i++){
      delay(10);
      readL3G4200D(true);      
      zmin = min(zmin, gyro.z);
      zmax = max(zmax, gyro.z);
      ofs.x += ((float)gyro.x)/ 50.0;
      ofs.y += ((float)gyro.y)/ 50.0;
      ofs.z += ((float)gyro.z)/ 50.0;          
      gyroNoise += sq(gyro.z-gyroOfs.z) /50.0;   // noise is computed with last offset calculation
    }
    Console.print(F("gyro calib min="));
    Console.print(zmin);
    Console.print(F("\tmax="));    
    Console.print(zmax);
    Console.print(F("\tofs="));        
    Console.print(ofs.z);    
    Console.print(F("\tnoise="));                
    Console.println(gyroNoise);  
    if (gyroNoise < 20) break; // optimum found    
    gyroOfs = ofs; // new offset found
  }  
  useGyroCalibration = true;
  Console.print(F("counter="));
  Console.println(gyroCounter);  
  Console.print(F("ofs="));
  printPt(gyroOfs);  
}      

// ADXL345B acceleration sensor driver
void  IMU::initADXL345B(){
  I2CwriteTo(ADXL345B, 0x2D, 0);
  I2CwriteTo(ADXL345B, 0x2D, 16);
  I2CwriteTo(ADXL345B, 0x2D, 8);         
}

void IMU::readADXL345B(){  
  uint8_t buf[6];
  if (I2CreadFrom(ADXL345B, 0x32, 6, (uint8_t*)buf) != 6){
    errorCounter++;
    return;
  }
  // Convert the accelerometer value to G's. 
  // With 10 bits measuring over a +/-4g range we can find how to convert by using the equation:
  // Gs = Measurement Value * (G-range/(2^10)) or Gs = Measurement Value * (8/1024)
  // ( *0.0078 )
  float x=(int16_t) (((uint16_t)buf[1]) << 8 | buf[0]); 
  float y=(int16_t) (((uint16_t)buf[3]) << 8 | buf[2]); 
  float z=(int16_t) (((uint16_t)buf[5]) << 8 | buf[4]); 
  //Console.println(z);
  if (useAccCalibration){
    x -= accOfs.x;
    y -= accOfs.y;
    z -= accOfs.z;
    x /= accScale.x*0.5;    
    y /= accScale.y*0.5;    
    z /= accScale.z*0.5;
    acc.x = x;
    //Console.println(z);
    acc.y = y;
    acc.z = z;
  } else {
    acc.x = x;
    acc.y = y;
    acc.z = z;
  }
  /*float accXreal = x + sin(gyroYpr.pitch);
  accXmax = max(accXmax, accXreal );    
  accXmin = min(accXmin, accXreal );        */
  //float amag = sqrt(Xa*Xa + Ya*Ya + Za*Za);
  //Xa /= amag;
  //Ya /= amag;
  //Za /= amag;  
  accelCounter++;
}

// L3G4200D gyro sensor driver
boolean IMU::initL3G4200D(){
  Console.println(F("initL3G4200D"));
  uint8_t buf[6];    
  int retry = 0;
  while (true){
    I2CreadFrom(L3G4200D, 0x0F, 1, (uint8_t*)buf);
    if (buf[0] != 0xD3) {        
      Console.println(F("gyro read error"));
      retry++;
      if (retry > 2){
        errorCounter++;
        return false;
      }
      delay(1000);            
    } else break;
  }
  // Normal power mode, all axes enabled, 100 Hz
  I2CwriteTo(L3G4200D, 0x20, 0b00001100);    
  // 2000 dps (degree per second)
  I2CwriteTo(L3G4200D, 0x23, 0b00100000);      
  I2CreadFrom(L3G4200D, 0x23, 1, (uint8_t*)buf);
  if (buf[0] != 0b00100000){
      Console.println(F("gyro write error")); 
      while(true);
  }  
  // fifo mode 
 // I2CwriteTo(L3G4200D, 0x24, 0b01000000);        
 // I2CwriteTo(L3G4200D, 0x2e, 0b01000000);          
  delay(250);
  calibGyro();    
  return true;
}

void IMU::readL3G4200D(boolean useTa){  
  now = micros();
  float Ta = 1;
  //if (useTa) {
    Ta = ((now - lastGyroTime) / 1000000.0);    
    //float Ta = ((float)(millis() - lastGyroTime)) / 1000.0; 			    
    lastGyroTime = now;
    if (Ta > 0.5) Ta = 0;   // should only happen for the very first call
    //lastGyroTime = millis();    
  //}  
  uint8_t fifoSrcReg = 0;  
  I2CreadFrom(L3G4200D, 0x2F, sizeof(fifoSrcReg), &fifoSrcReg);         // read the FIFO_SRC_REG
   // FIFO_SRC_REG
   // 7: Watermark status. (0: FIFO filling is lower than WTM level; 1: FIFO filling is equal or higher than WTM level)
   // 6: Overrun bit status. (0: FIFO is not completely filled; 1:FIFO is completely filled)
   // 5: FIFO empty bit. (0: FIFO not empty; 1: FIFO empty)
   // 4..0: FIFO stored data level
   //Console.print("FIFO_SRC_REG: "); Console.println(fifoSrcReg, HEX);
  uint8_t countOfData = (fifoSrcReg & 0x1F) + 1;   
  //  if (bitRead(fifoSrcReg, 6)==1) Console.println(F("IMU error: FIFO overrun"));

  memset(gyroFifo, 0, sizeof(gyroFifo[0])*32);
  I2CreadFrom(L3G4200D, 0xA8, sizeof(gyroFifo[0])*countOfData, (uint8_t *)gyroFifo);         // the first bit of the register address specifies we want automatic address increment
  //I2CreadFrom(L3G4200D, 0x28, sizeof(gyroFifo[0])*countOfData, (uint8_t *)gyroFifo);         // the first bit of the register address specifies we want automatic address increment

  gyro.x = gyro.y = gyro.z = 0;
  //Console.print("fifo:");
  //Console.println(countOfData);
  if (!useGyroCalibration) countOfData = 1;
  for (uint8_t i=0; i<countOfData; i++){
      gyro.x += (int16_t) (((uint16_t)gyroFifo[i].xh) << 8 | gyroFifo[i].xl);
      gyro.y += (int16_t) (((uint16_t)gyroFifo[i].yh) << 8 | gyroFifo[i].yl);
      gyro.z += (int16_t) (((uint16_t)gyroFifo[i].zh) << 8 | gyroFifo[i].zl);
      if (useGyroCalibration){
        gyro.x -= gyroOfs.x;
        gyro.y -= gyroOfs.y;
        gyro.z -= gyroOfs.z;               
      }
  }
  if (useGyroCalibration){
    gyro.x *= 0.07 * PI/180.0;  // convert to radiant per second
    gyro.y *= 0.07 * PI/180.0; 
    gyro.z *= 0.07 * PI/180.0;  
    gyroYpr.yaw   = scalePI( gyroYpr.yaw   -  gyro.z  * Ta ); // integrate over time
    gyroYpr.pitch = scalePI( gyroYpr.pitch +  gyro.y  * Ta );
    gyroYpr.roll  = scalePI( gyroYpr.roll  +  gyro.x  * Ta );     
  }
  gyroCounter++;
}


// HMC5883L compass sensor driver
void  IMU::initHMC5883L(){
  I2CwriteTo(HMC5883L, 0x00, 0x70);  // 8 samples averaged, 75Hz frequency, no artificial bias.       
  //I2CwriteTo(HMC5883L, 0x01, 0xA0);      // gain
  I2CwriteTo(HMC5883L, 0x01, 0x20);   // gain
  I2CwriteTo(HMC5883L, 0x02, 00);    // mode         
}

void IMU::readHMC5883L(){    
  int8_t buf[6];  
  if (I2CreadFrom(HMC5883L, 0x03, 6, (uint8_t*)buf) != 6){
    errorCounter++;
    return;
  }
  // scale +1.3Gauss..-1.3Gauss  (*0.00092)  
  com.x = (int16_t) (((uint16_t)buf[0]) << 8 | buf[1]);
  com.y = (int16_t) (((uint16_t)buf[4]) << 8 | buf[5]);
  com.z = (int16_t) (((uint16_t)buf[2]) << 8 | buf[3]);
}

float IMU::sermin(float oldvalue, float newvalue){
  if (newvalue < oldvalue) {
    Console.print(".");
    digitalWrite(pinLED, true);
  }
  return min(oldvalue, newvalue);
}

float IMU::sermax(float oldvalue, float newvalue){
  if (newvalue > oldvalue) {
    Console.print(".");
    digitalWrite(pinLED, true);
  }
  return max(oldvalue, newvalue);
}

void IMU::calibComDeviation(){    
  Console.println(F("com calib dev - steady rotate compass"));  
  useComDeviation = false;     
  float ypr[3];  
  float time;
  float duration;  
  boolean retry = true;
  boolean ledState = LOW;
  int startYaw, lastYaw, startYawDegree;  
  unsigned long now;
  while (retry){     
    startYaw = -200;     
    for (int i=0; i < 36; i++) comDeviation[i]=-1;    
    Console.println(F("next round"));
    unsigned long startTime = millis();
    now = startTime;
    getEuler(ypr);        
    int lastYaw = ((int)((ypr[0]+180)/10));
    while (true){ 
      now = millis();                                      
      getEuler(ypr);              
      int yaw = ((int)((ypr[0]+180)/10));
      if (yaw != lastYaw){
        if (startYaw == -200){
          startYaw = yaw;
          startYawDegree = yaw*10-180;
          startTime = now;          
        } 
        time = ((float)(now - startTime)) / 1000.0;                        
        if (comDeviation[yaw] < 0) {
          digitalWrite(pinLED, HIGH);                    
          Console.print(yaw);
          Console.print(",");
          Console.println(time);                      
          comDeviation[yaw] = time;
        }
        if (time > 9){
          if (yaw == startYaw) {
            Console.println(F("360 degree"));
            duration = time;
            break;
          }         
        }  
      }                   
      delay(10);    
      digitalWrite(pinLED, LOW);                      
      lastYaw=yaw;      
    }
    retry=false;
    for (int i=0; i < 36; i++) if (comDeviation[i] < 0) retry = true;
  }  
  for (int i=0; i < 36; i++){
    comDeviation[i] = scale180(startYawDegree + comDeviation[i] / duration * 360.0);
  }  
  digitalWrite(pinLED, LOW);            
  useComDeviation = true;   
  printCalib();
  saveCalib();  
}

float IMU::compensateComYawDeviation(float degree){
  if (isnan(comDeviation[0])) return degree;
  int yaw = ((int)((degree+180)/10));    
  float dx = (degree - (yaw*10-180));
  float y1 = comDeviation[yaw];
  float y2 = comDeviation[(yaw+1)%36];
  float dy = distance180(y1, y2);  
  return scale180( y1 + dy/10.0 * dx );  
}

void IMU::calibCom(){
  Console.println(F("com calib..."));
  Console.println(F("1. rotate sensor 360 degree around all three axis"));
  Console.println(F("2. press key"));
  float oldX = 0;
  float oldY = 0;
  float oldZ = 0;
  while(true){        
    delay(200);
    readHMC5883L();      
    if (  (abs(oldX-com.x) > 1) || (abs(oldY-com.y) > 1) || (abs(oldZ-com.z) > 1)  ){
      Console.print(com.x);
      Console.print("\t");
      Console.print(com.y);
      Console.print("\t");
      Console.print(com.z);
      Console.println();      
      oldX = com.x;
      oldY = com.y;
      oldZ = com.z;
    }
    if (Console.available()) {
      while (Console.available()) Console.read();
      break;      
    }
  } 
}



// calculate acceleration sensor offsets
void IMU::calibAcc(){
  Console.println(F("acc calib..."));
  useAccCalibration = false;
  accOfs.x = accOfs.y = accOfs.z = 0;  
  float xmin =  99999;
  float xmax = -99999;      
  float ymin =  99999;
  float ymax = -99999;        
  float zmin =  99999;
  float zmax = -99999;        
  for (int counter=0; counter < 6; counter++){
    Console.print(counter+1);
    Console.print(F(". lay down sensor 'axis "));        
    Console.print(counter/2+1);
    Console.print(F("' "));
    if (counter % 2 == 0) Console.print(F("up")); else Console.print(F("down"));
    Console.println(F(", then don't move, and press key"));      
    while (Console.available()) Console.read();
    while (!Console.available()) delay(10);
    while (Console.available()) Console.read();
    point_float_t pt = {0,0,0};
    digitalWrite(pinLED, true);
    for (int i=0; i < 100; i++){        
      readADXL345B();            
      pt.x += acc.x / 100.0;
      pt.y += acc.y / 100.0;
      pt.z += acc.z / 100.0;                  
      Console.print(acc.x);
      Console.print(",");
      Console.print(acc.y);
      Console.print(",");
      Console.println(acc.z);
      delay(1);
    }
    xmin = min(xmin, pt.x);
    xmax = max(xmax, pt.x);         
    ymin = min(ymin, pt.y);
    ymax = max(ymax, pt.y);
    zmin = min(zmin, pt.z);
    zmax = max(zmax, pt.z);            
    digitalWrite(pinLED, false);
  } 
  float xrange = xmax - xmin;
  float yrange = ymax - ymin;
  float zrange = zmax - zmin;
  accOfs.x = xrange/2 + xmin;
  accOfs.y = yrange/2 + ymin;
  accOfs.z = zrange/2 + zmin;
  accScale.x = xrange;
  accScale.y = yrange;  
  accScale.z = zrange;
  useAccCalibration = true;  
  printCalib();
  /*Console.println("press key");       
  while (Console.available()) Console.read();
  while (!Console.available()) delay(10);*/
  saveCalib();
}      



void IMU::printCom(){  
  Console.print(F("\tcom,"));
  Console.print(com.x);  
  Console.print(",");
  Console.print(com.y);  
  Console.print(",");
  Console.print(com.z);   
  Console.print(",");
  Console.print(comYaw/PI*180.0);   
  Console.print(",");  
  Console.print(F("comcal,"));
  Console.print(comCal.x);  
  Console.print(",");
  Console.print(comCal.y);  
  Console.print(",");
  Console.print(comCal.z);
  /*Console.print(comYawCal/PI*180.0);     
  Console.print("\t");  
  Console.print("\t");      
  Console.print("tilt=");
  Console.print(comTilt.x);  
  Console.print("\t");
  Console.print(comTilt.y);  
  Console.print("\t");
  Console.print(comTilt.z);
  Console.print("\t");
  Console.print(comYawTilt/PI*180.0);       */
}

void IMU::printAcc(){
  Console.print("\tacc,");
  Console.print(acc.x);
  Console.print(",");
  Console.print(acc.y);
  Console.print(",");
  Console.print(acc.z);  
  Console.print(",");
  //printPt(accMin);  
  //Console.print(",");
  //printPt(accMax);    
}

void IMU::printGyro(){  
  Console.print("\tgyro,");
  Console.print(gyro.x);
  Console.print(",");
  Console.print(gyro.y);
  Console.print(",");
  Console.print(gyro.z);
  Console.print(",\t");
  Console.print(gyroYpr.yaw);  
  Console.print(",");
  Console.print(gyroYpr.pitch);  
  Console.print(",");
  Console.print(gyroYpr.roll);    
}

void IMU::printIMU(float * ypr){
  Bluetooth.print(ypr[0]);
  Bluetooth.print(",");
  Bluetooth.print(ypr[1]);
  Bluetooth.print(",");
  Bluetooth.print(ypr[2]);          
  Bluetooth.print(",");
  Bluetooth.print(gyro.x);
  Bluetooth.print(",");
  Bluetooth.print(gyro.y);
  Bluetooth.print(",");
  Bluetooth.print(gyro.z);
  Bluetooth.print(",");
  Bluetooth.print(acc.x);
  Bluetooth.print(",");
  Bluetooth.print(acc.y);
  Bluetooth.print(",");
  Bluetooth.print(acc.z);
  Bluetooth.print(",");
  Bluetooth.print(com.x);
  Bluetooth.print(",");
  Bluetooth.print(com.y);
  Bluetooth.print(",");
  Bluetooth.print(com.z);  
  Bluetooth.println();
  /*Console.print(",");
  Console.print(comYawTilt/PI*180.0);  */
}


/**
 * Fast inverse square root implementation
 * @see http://en.wikipedia.org/wiki/Fast_inverse_square_root
*/
float IMU::invSqrt(float number) {
  volatile long i;
  volatile float x, y;
  volatile const float f = 1.5F;

  x = number * 0.5F;
  y = number;
  i = * ( long * ) &y;
  i = 0x5f375a86 - ( i >> 1 );
  y = * ( float * ) &i;
  y = y * ( f - ( x * y * y ) );
  return y;
}

void IMU::update(){
  read();  
  now = micros();
  float Ta = (now - lastAHRSTime) / 1000000.0;
  lastAHRSTime = now;
  ahrs.update( 
             gyro.x, gyro.y, gyro.z,             
             acc.x,  acc.y,  acc.z, 
             comCal.x,  comCal.y,  comCal.z,
             Ta/2
             );    
}  
 

void IMU::getQ(float * q) {  
  q[0] = ahrs.q0;
  q[1] = ahrs.q1;
  q[2] = ahrs.q2;
  q[3] = ahrs.q3;
  
  // gravity compensation
  float accFloat[3];
  accFloat[0] = acc.x;
  accFloat[1] = acc.y;
  accFloat[2] = acc.z;
  gravityCompensateAcc(accFloat, q);      
  accGrav.x = accFloat[0];
  accGrav.y = accFloat[1];
  accGrav.z = accFloat[2];  
  accMin.x = max(accMin.x, accGrav.x );    
  accMax.x = max(accMax.x, accGrav.x );    
  accMin.y = max(accMin.y, accGrav.y );    
  accMax.y = max(accMax.y, accGrav.y );    
  accMin.z = max(accMin.z, accGrav.z );    
  accMax.z = max(accMax.z, accGrav.z );    
}


/**
 * Compensates the accelerometer readings in the 3D vector acc expressed in the sensor frame for gravity
 * @param acc the accelerometer readings to compensate for gravity
 * @param q the quaternion orientation of the sensor board with respect to the world
*/
void IMU::gravityCompensateAcc(float * acc, float * q) {
  float g[3];
  
  // get expected direction of gravity in the sensor frame
  g[0] = 2 * (q[1] * q[3] - q[0] * q[2]);
  g[1] = 2 * (q[0] * q[1] + q[2] * q[3]);
  g[2] = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];
  
  // compensate accelerometer readings with the expected direction of gravity
  acc[0] = acc[0] - g[0];
  acc[1] = acc[1] - g[1];
  acc[2] = acc[2] - g[2];
}

/**
 * Returns the Euler angles in radians defined in the Aerospace sequence.
 * See Sebastian O.H. Madwick report "An efficient orientation filter for 
 * inertial and intertial/magnetic sensor arrays" Chapter 2 Quaternion representation
 * 
 * @param angles three floats array which will be populated by the Euler angles in radians
*/

void IMU::getEulerRad(float * angles) {
  float q[4]; // quaternion
  getQ(q);
  angles[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1); // psi
  angles[1] = -asin(2 * q[1] * q[3] + 2 * q[0] * q[2]); // theta
  angles[2] = atan2(2 * q[2] * q[3] - 2 * q[0] * q[1], 2 * q[0] * q[0] + 2 * q[3] * q[3] - 1); // phi
}


/**
 * Returns the Euler angles in degrees defined with the Aerospace sequence.
 * See Sebastian O.H. Madwick report "An efficient orientation filter for 
 * inertial and intertial/magnetic sensor arrays" Chapter 2 Quaternion representation
 * 
 * @param angles three floats array which will be populated by the Euler angles in degrees
*/
void IMU::getEuler(float * angles) {
  getEulerRad(angles);  
  arr3_rad_to_deg(angles);
  if (useComDeviation) angles[0] = compensateComYawDeviation(angles[0]);
}


/**
 * Returns the yaw pitch and roll angles, respectively defined as the angles in radians between
 * the Earth North and the IMU X axis (yaw), the Earth ground plane and the IMU X axis (pitch)
 * and the Earth ground plane and the IMU Y axis.
 * 
 * @note This is not an Euler representation: the rotations aren't consecutive rotations but only
 * angles from Earth and the IMU. For Euler representation Yaw, Pitch and Roll see FreeIMU::getEuler
 * 
 * @param ypr three floats array which will be populated by Yaw, Pitch and Roll angles in radians
*/
void IMU::getYawPitchRoll(float * ypr) {
  float q[4]; // quaternion
  float gx, gy, gz; // estimated gravity direction
  getQ(q);
  
  gx = 2 * (q[1]*q[3] - q[0]*q[2]);
  gy = 2 * (q[0]*q[1] + q[2]*q[3]);
  gz = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];
  
  ypr[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1);
  ypr[1] = atan(gx / sqrt(gy*gy + gz*gz));
  ypr[2] = atan(gy / sqrt(gx*gx + gz*gz));
  
  //arr3_rad_to_deg(ypr);
  if (useComDeviation) ypr[0] = compensateComYawDeviation(ypr[0]);     
}


// compute calibrated compass values
void IMU::calcComCal(){  
    if (isnan(comCalB[0])) {
      comCal.x = com.x;
      comCal.y = com.y;
      comCal.z = com.z;
    } else {
      // (rawA - B)
      float x = com.x - comCalB[0];
      float y = com.y - comCalB[1];
      float z = com.z - comCalB[2];    
      // calA = A_1 * (rawA - B)
      comCal.x = (comCalA_1[0][0] * x + comCalA_1[1][0] * y + comCalA_1[2][0] * z) ;
      comCal.y = (comCalA_1[0][1] * x + comCalA_1[1][1] * y + comCalA_1[2][1] * z) ;
      comCal.z = (comCalA_1[0][2] * x + comCalA_1[1][2] * y + comCalA_1[2][2] * z) ;
    }
  
    //comYawCal = scalePI( atan2(comCal.y, comCal.x)  );          
}

void IMU::getComRaw(point_float_t &v){
  v.x = com.x;
  v.y = com.y;
  v.z = com.z;
}

void IMU::getComCal(point_float_t &v){
  v.x = comCal.x;
  v.y = comCal.y;
  v.z = comCal.z;
}

void IMU::getMinMaxAcc(point_float_t &vmin, point_float_t &vmax){
  vmin = accMin;
  vmax = accMax;
  accMin.x = accMin.y = accMin.z = 0;
  accMax.x = accMax.y = accMax.z = 0;
}

/**
 * Converts a 3 elements array arr of angles expressed in radians into degrees
*/
void IMU::arr3_rad_to_deg(float * arr) {
  arr[0] *= 180/M_PI;
  arr[1] *= 180/M_PI;
  arr[2] *= 180/M_PI;
}


boolean IMU::init(){    
  loadCalib();
  printCalib();    
  if (!initL3G4200D()) return false;
  initADXL345B();
  initHMC5883L();    
  now = 0;  
  hardwareInitialized = true;
  return true;
}

int IMU::getCallCounter(){
  int res = callCounter;
  callCounter = 0;
  return res;
}

int IMU::getErrorCounter(){
  int res = errorCounter;
  errorCounter = 0;
  return res;
}

void IMU::read(){  
  if (!hardwareInitialized) {
    errorCounter++;
    return;
  }
  callCounter++;    
  readL3G4200D(false); // false for AHRS
  readADXL345B();
  readHMC5883L();  
  calcComCal();
}


