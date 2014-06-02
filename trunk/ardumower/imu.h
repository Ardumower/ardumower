// Arduino robot mower
// Copyright (c) 2013 by Alexander Grau
//
// pitch/roll and heading estimation (IMU sensor fusion)

#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "AHRS.h"

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
  void getEuler(float * angles); 
  void getEulerRad(float * angles);    
  // get yaw,pitch,roll (radiant)      
  void getYawPitchRollRad(float * ypr);   
  // get yaw,pitch,roll (degree)
  void getYawPitchRoll(float * ypr);
  void getMinMaxAcc(point_float_t &vmin, point_float_t &vmax);      
  void setComCalParam(int type, int i, int j, float value);
  void calibAcc();
  void calibComDeviation();
  int getCallCounter();
  int getErrorCounter();
  void printIMU(float * ypr);  
  void printCom();
  void printAcc();
  void printGyro();  
private:
  int callCounter;
  int errorCounter;
  boolean hardwareInitialized;  
  // --------- gyro state -----------------------------
  point_float_t gyro;   // gyro sensor data (degree)
  point_float_t gyroOfs; // gyro calibration data
  float gyroNoise ;      // gyro noise
  int gyroCounter ; 
  ypr_t gyroYpr;  // gyro yaw,pitch,roll
  boolean useGyroCalibration ; // gyro calibration flag
  unsigned long lastGyroTime;
  // --------- acceleration state ---------------------
  point_float_t acc;  // acceleration sensor data
  point_float_t accMin;
  point_float_t accMax;
  int accelCounter ;
  boolean useAccCalibration ; 
  float accPitch ;
  float accRoll ;
  point_float_t accOfs;
  point_float_t accScale;
  // --------- compass state --------------------------
  point_float_t com; // compass sensor data (raw)
  point_float_t comCal; // compass sensor data (calibration corrected)
  float comYaw;         // compass heading (radiant, raw)
  float comCalB[3];
  float comCalA_1[3][3];
  float comDeviation[36]; // compass heading deviation (degree/10 => degree)
  boolean useComDeviation; 
  // ------ AHRS --------------------------------------
  AHRS ahrs;
  unsigned long lastAHRSTime;
  unsigned long now;
  // --------------------------------------------------
  // IMU  
  void getQ(float * q);  
  void read();
  // calibration
  void loadSaveCalib(boolean readflag);  
  void calibGyro();
  void loadCalib();  
  void calibCom();  
  void calcComCal();
  void getComRaw(point_float_t &v);
  void getComCal(point_float_t &v);   
  float compensateComYawDeviation(float degree);
  void gravityCompensateAcc(float * acc, float * q);
  // print IMU values
  void printPt(point_float_t p);
  void printCalib();
  void deleteCalib();
  void saveCalib();
  // helpers
  float scalePI(float v);
  float scale180(float v);
  float distancePI(float x, float w);
  float distance180(float x, float w);
  float invSqrt(float number);
  void arr3_rad_to_deg(float * arr);  
  float fusionPI(float w, float a, float b);  
  float sermin(float oldvalue, float newvalue);
  float sermax(float oldvalue, float newvalue);
  // hardware
  void initADXL345B();
  boolean initL3G4200D();
  void initHMC5883L();
  void readL3G4200D(boolean useTa);
  void readADXL345B();
  void readHMC5883L();
};




#endif

