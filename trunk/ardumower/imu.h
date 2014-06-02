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

struct point_double_t {
  double x;
  double y;
  double z;
};
typedef struct point_double_t point_double_t;

struct ypr_t {
  double yaw;
  double pitch;
  double roll;
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
  void getMinMaxAcc(point_double_t &vmin, point_double_t &vmax);      
  void setComCalParam(int type, int i, int j, float value);
  void calibComDeviation();
  int getCallCounter();
  int getErrorCounter();
  void printIMU(float * ypr);  
private:
  int callCounter;
  int errorCounter;
  boolean hardwareInitialized;  
  // --------- gyro state -----------------------------
  point_double_t gyro;   // gyro sensor data (degree)
  point_double_t gyroOfs; // gyro calibration data
  double gyroNoise ;      // gyro noise
  int gyroCounter ; 
  ypr_t gyroYpr;  // gyro yaw,pitch,roll
  boolean useGyroCalibration ; // gyro calibration flag
  unsigned long lastGyroTime;
  // --------- acceleration state ---------------------
  point_double_t acc;  // acceleration sensor data
  point_double_t accMin;
  point_double_t accMax;
  int accelCounter ;
  boolean useAccCalibration ; 
  double accPitch ;
  double accRoll ;
  point_double_t accOfs;
  point_double_t accScale;
  // --------- compass state --------------------------
  point_double_t com; // compass sensor data (raw)
  point_double_t comCal; // compass sensor data (calibration corrected)
  double comYaw;         // compass heading (radiant, raw)
  double comCalB[3];
  double comCalA_1[3][3];
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
  void calibAcc();
  void calibCom();  
  void calcComCal();
  void getComRaw(point_double_t &v);
  void getComCal(point_double_t &v);   
  double compensateComYawDeviation(double degree);
  void gravityCompensateAcc(float * acc, float * q);
  // print IMU values
  void printPt(point_double_t p);
  void printCom();
  void printAcc();
  void printGyro();
  void printCalib();
  void deleteCalib();
  void saveCalib();
  // helpers
  double scalePI(double v);
  double scale180(double v);
  double distancePI(double x, double w);
  double distance180(double x, double w);
  float invSqrt(float number);
  void arr3_rad_to_deg(float * arr);  
  double fusionPI(double w, double a, double b);  
  double sermin(double oldvalue, double newvalue);
  double sermax(double oldvalue, double newvalue);
  // hardware
  void initADXL345B();
  boolean initL3G4200D();
  void initHMC5883L();
  void readL3G4200D(boolean useTa);
  void readADXL345B();
  void readHMC5883L();
};




#endif

