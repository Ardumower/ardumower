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

#define MAGIC 3

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
  useComDeviation = false;   
  
  // test only
  accOfs.x=2.95; accOfs.y=-17.75; accOfs.z=-22.05;
  accScale.x=517.90;  accScale.y=526.50;  accScale.z=514.50;
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
  int addr = 0;
  short magic = MAGIC;
  /*eereadwrite(readflag, addr, magic); // magic
  eereadwrite(readflag, addr, accOfs);
  eereadwrite(readflag, addr, accScale);    
  eereadwrite(readflag, addr, comCalB);  
  eereadwrite(readflag, addr, comCalA_1);    
  for (int i=0; i < 36; i++){
    eereadwrite(readflag, addr, comDeviation[i]);    
  }*/
}

void IMU::loadCalib(){
  short magic = 0;
  int addr = 0;
  //eeread(addr, magic);
  if (magic != MAGIC) return;
  loadSaveCalib(true);
}

void IMU::saveCalib(){
  loadSaveCalib(false);
}

void IMU::deleteCalib(){
  int addr = 0;
  //eewrite(addr, (short)0); // magic  
  accOfs.x=accOfs.y=accOfs.z=0;
  accScale.x=accScale.y=accScale.z=1;  
  comCalA_1[0][0] = 1; comCalA_1[0][1] = 0; comCalA_1[0][2] = 0;
  comCalA_1[1][0] = 0; comCalA_1[1][1] = 1; comCalA_1[1][2] = 0;
  comCalA_1[2][0] = 0; comCalA_1[2][1] = 0; comCalA_1[2][2] = 1;
  comCalB[0] = comCalB[1] = comCalB[2] = 0;
  for (int i=0; i < 36; i++) comDeviation[i] = i*10-180;
}

void IMU::setComCalParam(int type, int i, int j, float value){  
  if (type == 0){
    comCalB[i]=value;    
  } else if (type == 1){
    comCalA_1[i][j]=value;    
  }
}

void IMU::printPt(point_float_t p){
  Serial.print(p.x);
  Serial.print(",");    
  Serial.print(p.y);  
  Serial.print(",");
  Serial.println(p.z);  
}

void IMU::printCalib(){
  Serial.println(F("--------"));
  Serial.print(F("accOfs="));
  printPt(accOfs);
  Serial.print(F("accScale="));
  printPt(accScale);
  Serial.print(F("comCalB="));
  for (int i=0; i < 3; i++){
    Serial.print(comCalB[i], 6);
    Serial.print("  ");
  }  
  Serial.print(F("comCalA_1="));
  for (int i=0; i < 3; i++){
    for (int j=0; j < 3; j++){
      Serial.print(comCalA_1[i][j], 6);
      Serial.print("  ");
    }    
  }    
  Serial.println();    
  Serial.println(F("comDev"));  
  for (int i=0; i < 36; i++){  
    Serial.print(i*10-180);  
    Serial.print("=");      
    Serial.println(comDeviation[i]);
  }
  Serial.println(F("--------"));
}



// calculate gyro offsets
void IMU::calibGyro(){
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
    Serial.print(F("gyro calib min="));
    Serial.print(zmin);
    Serial.print(F("\tmax="));    
    Serial.print(zmax);
    Serial.print(F("\tofs="));        
    Serial.print(ofs.z);    
    Serial.print(F("\tnoise="));                
    Serial.println(gyroNoise);  
    if (gyroNoise < 20) break; // optimum found    
    gyroOfs = ofs; // new offset found
  }  
  useGyroCalibration = true;
  Serial.print(F("counter="));
  Serial.println(gyroCounter);  
  Serial.print(F("ofs="));
  printPt(gyroOfs);  
}      

// ADXL345B acceleration sensor driver
void  IMU::initADXL345B(){
  I2CwriteTo(ADXL345B, 0x2D, 0);
  I2CwriteTo(ADXL345B, 0x2D, 16);
  I2CwriteTo(ADXL345B, 0x2D, 8);         
}

void IMU::readADXL345B(){  
  int8_t buf[6];
  if (I2CreadFrom(ADXL345B, 0x32, 6, (uint8_t*)buf) != 6){
    errorCounter++;
    return;
  }
  // Convert the accelerometer value to G's. 
  // With 10 bits measuring over a +/-4g range we can find how to convert by using the equation:
  // Gs = Measurement Value * (G-range/(2^10)) or Gs = Measurement Value * (8/1024)
  // ( *0.0078 )
  float x=((float)(((int16_t)buf[1]<<8) | buf[0])) ;
  float y=((float)(((int16_t)buf[3]<<8) | buf[2])) ;
  float z=((float)(((int16_t)buf[5]<<8) | buf[4])) ;  
  if (useAccCalibration){
    x -= accOfs.x;
    y -= accOfs.y;
    z -= accOfs.z;
    x /= accScale.x*0.5;
    y /= accScale.y*0.5;    
    z /= accScale.z*0.5;
    acc.x = x;
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
  uint8_t buf[6];    
  int retry = 0;
  while (true){
    I2CreadFrom(L3G4200D, 0x0F, 1, (uint8_t*)buf);
    if (buf[0] != 0xD3) {        
      Serial.println(F("gyro read error"));
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
  // 2000 dps
  I2CwriteTo(L3G4200D, 0x23, 0b00100000);      
  I2CreadFrom(L3G4200D, 0x23, 1, (uint8_t*)buf);
  if (buf[0] != 0b00100000){
      Serial.println(F("gyro write error")); 
      while(true);
  }  
  //I2CwriteTo(L3G4200D, 0x24, 0b00010000);      
  delay(250);
  calibGyro();    
  return true;
}

void IMU::readL3G4200D(boolean useTa){  
  int8_t buf[6];    
  if (I2CreadFrom(L3G4200D, 0x27, 1, (uint8_t*)buf) != 1){
    errorCounter++;
    return;
  }
  if ((buf[0] & 8) == 0) {
    //Serial.println("gyro busy");
    return;  
  }
  now = micros();
  float Ta = 1;
  if (useTa) {
    Ta = ((now - lastGyroTime) / 1000000.0);    
    //float Ta = ((float)(millis() - lastGyroTime)) / 1000.0; 			    
    lastGyroTime = now;
    if (Ta > 0.5) Ta = 0;   // should only happen for the very first call
    //lastGyroTime = millis();    
  }  
  if (I2CreadFrom(L3G4200D, 0x28, 6, (uint8_t*)buf) != 6){
    //Serial.println("gyro read error");
    errorCounter++;
    return;
  }
  gyro.x = ((float)(((int16_t)buf[1]<<8) | buf[0])) ;  
  //Serial.println(gyro.x);
  gyro.y=((float)(((int16_t)buf[3]<<8) | buf[2])) ;  
  gyro.z=((float)(((int16_t)buf[5]<<8) | buf[4])) ;  
  if (useGyroCalibration){
    gyro.x -= gyroOfs.x;
    gyro.y -= gyroOfs.y;
    gyro.z -= gyroOfs.z;       
    // value should be higher than noise!
    //boolean valid = (abs(gyroZ) > gyroNoise);
    // FS=250 dps (mdps=8.75)  
    // FS=2000 dps (mdps=70)      
    gyro.x *= 0.07 * Ta;
    gyro.y *= 0.07 * Ta;
    gyro.z *= 0.07 * Ta;                
    gyro.x *= PI/180.0;
    gyro.y *= PI/180.0;
    gyro.z *= PI/180.0;
    gyroYpr.yaw -= gyro.z;
    gyroYpr.pitch +=  gyro.y;
    gyroYpr.roll +=  gyro.x;    
    //Serial.println(gyroZ);    
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
  com.x = ((float)(((int16_t)buf[0]<<8) | buf[1])) ;
  com.y = ((float)(((int16_t)buf[4]<<8) | buf[5])) ;
  com.z = ((float)(((int16_t)buf[2]<<8) | buf[3])) ;          
}

float IMU::sermin(float oldvalue, float newvalue){
  if (newvalue < oldvalue) {
    Serial.print(".");
    digitalWrite(pinLED, true);
  }
  return min(oldvalue, newvalue);
}

float IMU::sermax(float oldvalue, float newvalue){
  if (newvalue > oldvalue) {
    Serial.print(".");
    digitalWrite(pinLED, true);
  }
  return max(oldvalue, newvalue);
}

void IMU::calibComDeviation(){    
  Serial.println(F("com calib dev - steady rotate compass"));  
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
    Serial.println(F("next round"));
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
          Serial.print(yaw);
          Serial.print(",");
          Serial.println(time);                      
          comDeviation[yaw] = time;
        }
        if (time > 9){
          if (yaw == startYaw) {
            Serial.println(F("360 degree"));
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
  Serial.println(F("com calib..."));
  Serial.println(F("1. rotate sensor 360 degree around all three axis"));
  Serial.println(F("2. press key"));
  float oldX = 0;
  float oldY = 0;
  float oldZ = 0;
  while(true){        
    delay(200);
    readHMC5883L();      
    if (  (abs(oldX-com.x) > 1) || (abs(oldY-com.y) > 1) || (abs(oldZ-com.z) > 1)  ){
      Serial.print(com.x);
      Serial.print("\t");
      Serial.print(com.y);
      Serial.print("\t");
      Serial.print(com.z);
      Serial.println();      
      oldX = com.x;
      oldY = com.y;
      oldZ = com.z;
    }
    if (Serial.available()) {
      while (Serial.available()) Serial.read();
      break;      
    }
  } 
}



// calculate acceleration sensor offsets
void IMU::calibAcc(){
  Serial.println(F("acc calib..."));
  useAccCalibration = false;
  accOfs.x = accOfs.y = accOfs.z = 0;  
  float xmin =  99999;
  float xmax = -99999;      
  float ymin =  99999;
  float ymax = -99999;        
  float zmin =  99999;
  float zmax = -99999;        
  for (int counter=0; counter < 6; counter++){
    Serial.print(counter+1);
    Serial.print(F(". lay down sensor 'axis "));        
    Serial.print(counter/2+1);
    Serial.print(F("' "));
    if (counter % 2 == 0) Serial.print(F("up")); else Serial.print(F("down"));
    Serial.println(F(", then don't move, and press key"));      
    while (Serial.available()) Serial.read();
    while (!Serial.available()) delay(10);
    while (Serial.available()) Serial.read();
    point_float_t pt = {0,0,0};
    digitalWrite(pinLED, true);
    for (int i=0; i < 10; i++){        
      readADXL345B();            
      pt.x += acc.x / 10.0;
      pt.y += acc.y / 10.0;
      pt.z += acc.z / 10.0;            
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
  /*Serial.println("press key");       
  while (Serial.available()) Serial.read();
  while (!Serial.available()) delay(10);*/
  saveCalib();
}      



void IMU::printCom(){  
  Serial.print(F("\tcom,"));
  Serial.print(com.x);  
  Serial.print(",");
  Serial.print(com.y);  
  Serial.print(",");
  Serial.print(com.z);   
  Serial.print(",");
  Serial.print(comYaw/PI*180.0);   
  Serial.print(",");  
  Serial.print(F("comcal,"));
  Serial.print(comCal.x);  
  Serial.print(",");
  Serial.print(comCal.y);  
  Serial.print(",");
  Serial.print(comCal.z);
  /*Serial.print(comYawCal/PI*180.0);     
  Serial.print("\t");  
  Serial.print("\t");      
  Serial.print("tilt=");
  Serial.print(comTilt.x);  
  Serial.print("\t");
  Serial.print(comTilt.y);  
  Serial.print("\t");
  Serial.print(comTilt.z);
  Serial.print("\t");
  Serial.print(comYawTilt/PI*180.0);       */
}

void IMU::printAcc(){
  Serial.print("\tacc,");
  Serial.print(acc.x);
  Serial.print(",");
  Serial.print(acc.y);
  Serial.print(",");
  Serial.print(acc.z);  
  Serial.print(",");
  //printPt(accMin);  
  //Serial.print(",");
  //printPt(accMax);    
}

void IMU::printGyro(){  
  Serial.print("\tgyro,");
  Serial.print(gyro.x);
  Serial.print(",");
  Serial.print(gyro.y);
  Serial.print(",");
  Serial.print(gyro.z);
  Serial.print(",\t");
  Serial.print(gyroYpr.yaw);  
  Serial.print(",");
  Serial.print(gyroYpr.pitch);  
  Serial.print(",");
  Serial.print(gyroYpr.roll);    
}

void IMU::printIMU(float * ypr){
  Serial2.print(ypr[0]);
  Serial2.print(",");
  Serial2.print(ypr[1]);
  Serial2.print(",");
  Serial2.print(ypr[2]);          
  Serial2.print(",");
  Serial2.print(gyro.x);
  Serial2.print(",");
  Serial2.print(gyro.y);
  Serial2.print(",");
  Serial2.print(gyro.z);
  Serial2.print(",");
  Serial2.print(acc.x);
  Serial2.print(",");
  Serial2.print(acc.y);
  Serial2.print(",");
  Serial2.print(acc.z);
  Serial2.print(",");
  Serial2.print(comCal.x);
  Serial2.print(",");
  Serial2.print(comCal.y);
  Serial2.print(",");
  Serial2.print(comCal.z);  
  Serial2.println();
  /*Serial.print(",");
  Serial.print(comYawTilt/PI*180.0);  */
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


void IMU::getQ(float * q) {
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
  acc.x = accFloat[0];
  acc.y = accFloat[1];
  acc.z = accFloat[2];  
  accMin.x = max(accMin.x, acc.x );    
  accMax.x = max(accMax.x, acc.x );    
  accMin.y = max(accMin.y, acc.y );    
  accMax.y = max(accMax.y, acc.y );    
  accMin.z = max(accMin.z, acc.z );    
  accMax.z = max(accMax.z, acc.z );    
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
  
  arr3_rad_to_deg(ypr);
  ypr[0] = compensateComYawDeviation(ypr[0]);     
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


