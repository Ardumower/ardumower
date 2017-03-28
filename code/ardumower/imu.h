/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  
  Private-use only! (you need to ask for a commercial-use)
 
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
  
  Private-use only! (you need to ask for a commercial-use)

*/

/* pitch/roll and heading estimation (IMU sensor fusion)  
   requires: GY-80 module (L3G4200D, ADXL345B, HMC5883L) 
   
How to use it (example):     
  1. initialize IMU:                 IMU imu;  imu.init(); 
  2. read IMU (yaw/pitch/roll:       Serial.println( imu.ypr.yaw );
*/


#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

// IMU state
enum { IMU_RUN, IMU_CAL_COM };


struct point_int_t {
  int16_t x;
  int16_t y;
  int16_t z;
};
typedef struct point_int_t point_int_t;

struct point_long_t {
  long x;
  long y;
  long z;
};
typedef struct point_long_t point_long_t;

struct point_float_t {
  float x;
  float y;
  float z;
};
typedef struct point_float_t point_float_t;

struct ypr_t {
  float yaw;
  float pitch;
  float roll;
};
typedef struct ypr_t ypr_t;


class IMU
{
public:
  IMU();    
  boolean init();   
  void update();  
  int getCallCounter();
  int getErrorCounter();
  void deleteCalib();  
  int callCounter;
  int errorCounter;
  boolean hardwareInitialized;  
  byte state;
  unsigned long lastAHRSTime;
  unsigned long now;  
  ypr_t ypr;  // gyro yaw,pitch,roll    
  // --------- gyro state -----------------------------
  point_float_t gyro;   // gyro sensor data (degree)    
  point_float_t gyroOfs; // gyro calibration data
  float gyroNoise ;      // gyro noise
  int gyroCounter ; 
  boolean useGyroCalibration ; // gyro calibration flag
  unsigned long lastGyroTime;
  // --------- acceleration state ---------------------
  point_float_t acc;  // acceleration sensor data
  point_float_t accGrav;  // acceleration sensor data (gravity corrected)
  point_float_t accMin;
  point_float_t accMax;
  int accelCounter ;
  boolean useAccCalibration ; 
  float accPitch ;
  float accRoll ;
  point_float_t accOfs;
  point_float_t accScale;
  int calibAccAxisCounter;
  // calibrate acceleration sensor  
  boolean calibAccNextAxis();  
  boolean calibrationAvail;
  // --------- compass state --------------------------  
  point_float_t com; // compass sensor data (raw)
  point_float_t comLast;
  point_float_t comMin; // compass sensor data (raw)
  point_float_t comMax; // compass sensor data (raw)  
  point_float_t comTilt; // compass sensor data (tilt corrected)
  point_float_t comOfs;
  point_float_t comScale;  
  float comYaw;         // compass heading (radiant, raw)
  boolean useComCalibration;
  // calibrate compass sensor  
  void calibComStartStop();  
  void calibComUpdate();    
  boolean newMinMaxFound();
  // --------------------------------------------------
  // helpers
  float scalePI(float v);
  float scale180(float v);
  float distancePI(float x, float w);
  float distance180(float x, float w);
  float fusionPI(float w, float a, float b);    
private:  
  void read();
  void loadSaveCalib(boolean readflag);  
  void calibGyro();
  void loadCalib();  
  // print IMU values
  void printPt(point_float_t p);
  void printCalib();
  void saveCalib();
  float sermin(float oldvalue, float newvalue);
  float sermax(float oldvalue, float newvalue);
  // hardware
  void initADXL345B();
  boolean initL3G4200D();
  void initHMC5883L();
  void readL3G4200D(boolean useTa);
  void readADXL345B();
  void readHMC5883L();
  boolean foundNewMinMax;
};




#endif

