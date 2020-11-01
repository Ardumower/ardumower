/*
  License
  Copyright (c) 2013-2017 by Alexander Grau

  Private-use only! (you need to ask for a commercial-use)

  The code is open: you can modify it under the terms of the
  GNU General Public License as published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.

  The code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Private-use only! (you need to ask for a commercial-use)
  /************************************************************
  MPU9250_DMP_Quaternion
  Quaternion example for MPU-9250 DMP Arduino Library
  Jim Lindblom @ SparkFun Electronics
  original creation date: November 23, 2016
  https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library

  The MPU-9250's digital motion processor (DMP) can calculate
  four unit quaternions, which can be used to represent the
  rotation of an object.

  This exmaple demonstrates how to configure the DMP to
  calculate quaternions, and prints them out to the serial
  monitor. It also calculates pitch, roll, and yaw from those
  values.

  Development environment specifics:
  Arduino IDE 1.6.12
  SparkFun 9DoF Razor IMU M0





*/
//bber
//the result is ypr.yaw , pitch and roll comming from only gyro accel IMU (very accurate but can drift over time so use as relative)
//and comyaw is the result of the compass  (not accurate but reliable so use as absolute)

#include "imu.h"
#include "SparkFunMPU9250-DMP.h"
#include "mower.h"
//#include "i2c.h"
#include "robot.h"

#include "flashmem.h"


float pitchOffset = 0;
float rollOffset = 0;
int ax_offset, ay_offset, az_offset, gx_offset, gy_offset, gz_offset;


int     Mag_x, Mag_y, Mag_z;                // Raw magnetometer readings
float   Mag_x_dampened,       Mag_y_dampened,       Mag_z_dampened;
float   Mag_x_hor, Mag_y_hor;
float   Mag_pitch, Mag_roll;

float   Gyro_pitch, Gyro_roll, Gyro_yaw;
float   Gyro_pitch_output, Gyro_roll_output;
float resultheading;
float chord_x,  chord_y,  chord_z;                              // Used for calculating scale factors
float chord_average;
MPU9250_DMP imu;


#define ADDR 600
#define MAGIC 6


void IMUClass::begin() {
  if (!robot.imuUse) return;
  loadCalib();
  printCalib();
  Console.println(F("--------------------------------------------------------------------------"));
  Console.println(F("--------------------------------- START IMU GYRO ACCEL -------------------"));
  Console.println(F("--------------------------------------------------------------------------"));

  
  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      Console.println("Unable to communicate with MPU-9250");
      Console.println("Check connections, and try again.");
      delay(5000);
    }
  }
  else {
    Console.println("Connected with MPU-9250/MPU-9255");
  }

  imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10); 
  // imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT , 10);

  // if the IMU not move for small duration it reduce the refresh rate,certainly autocalibration starting issue ?????????????????????????
  // Not Ok at more than 15 Hz ?????? very low response
  // DMP_FEATURE_6X_LP_QUAT is used to not read the compass
  // DMP_FEATURE_GYRO_CAL is used to automaticly calibrate the gyro when no move for 8 secondes but certainly not perfect and need a one shot calibration dev

  nextTimeAdjustYaw = millis();
  Console.println("Wait for GYRO near 10 secondes");
  watchdogReset();
  delay(8000);
  watchdogReset();
  int uu = 0;
  //read again 20 values because the yaw is certainly filtered by DMP
  for (uu = 0; uu < 11; uu++) {
    run();
    Console.print(".");
    delay(100);
  }
  Console.println("");
  Console.print("Initial GYRO/ACCELL Yaw :");
  Console.print(imu.yaw * 180 / PI) ;
  Console.print(" Pitch : ");
  Console.print(imu.pitch * 180 / PI) ;
  Console.print(" Roll : ");
  Console.println(imu.roll * 180 / PI);
  //and use last reading to compute offset
  pitchOffset = 0 - imu.pitch ;
  rollOffset = 0 - imu.roll ;

  if (abs(pitchOffset) > 20)
  {
    Console.println("Please start on flat location or check the IMU PCB orientation");
    Console.print("Ptich Offset is too high : ");
    Console.println(pitchOffset);
  }
  if (abs(rollOffset) > 20)
  {
    Console.println("Please start on flat location or check the IMU PCB orientation");
    Console.print("Roll Offset is too high : ");
    Console.println(rollOffset);
  }
  Console.print("With Offset GYRO/ACCELL Yaw :");
  Console.print((imu.yaw) * 180 / PI) ;
  Console.print(" Pitch : ");
  Console.print((imu.pitch + pitchOffset) * 180 / PI) ;
  Console.print(" Roll : ");
  Console.println((imu.roll + rollOffset) * 180 / PI);
 
  Console.println(F("--------------------------------------------------------------------------"));
  Console.println(F("--------------------------------- START COMPASS --------------------------"));
  Console.println(F("--------------------------------------------------------------------------"));

  if (robot.CompassUse) {

    readCompass();
    Console.print(F("  Compass Yaw: "));
    Console.print(comYaw);
    CompassGyroOffset = distancePI(ypr.yaw, comYaw);
    Console.print(F("  Diff between compass and accelGyro in Radian / Deg"));
    Console.print(CompassGyroOffset);
    Console.print(" / ");
    Console.println(CompassGyroOffset * 180 / PI);
  }
  else
  {
    Console.println("Compass is not used");
    CompassGyroOffset = 0;
  }
  Console.println(F("--------------------------------------------------------------------------"));
  Console.println(F("--------------------------------- IMU READY ------------------------------"));
  Console.println(F("--------------------------------------------------------------------------"));
}




void IMUClass::run() {
  if (!robot.imuUse)  return;
  if (state == IMU_CAL_COM) {
    calibComUpdate();
    return;
  }
  //-------------------read the mpu9250 DMP  --------------------------------
  // Check for new data in the FIFO

  if (imu.fifoAvailable() )
  {
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if (imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      // computeEulerAngles can be used -- after updating the
      // quaternion values -- to estimate roll, pitch, and yaw
      imu.computeEulerAngles(false);//false is use to use radian

    }
    else
    {
      //fail ??????????????????????
      //Console.println("IMU FIFO not update in time ???????????");
    }
  }
  else
  {
    //fail ???????????????
    //Console.println("IMU FIFO not available ???????????");
  }

  //bber4
  //filter to avoid bad reading
  //see this issue with GY87 GY88 and MPU9250 sometime (each 2 or 3 hours)the DMP return only one bad value so i don't use a low filter

  if ((abs(imu.pitch + pitchOffset) - abs(ypr.pitch)) > 0.3490)
  {
    Console.print("Last pitch : ");
    Console.print(ypr.pitch);
    Console.print(" Actual pitch : ");
    Console.println(imu.pitch + pitchOffset);
    Console.println("pitch change more than 20 degres in less than 50 ms ????????? value is skip");
  }
  else
  {
    ypr.pitch = imu.pitch ;
  }

  if ((abs(imu.roll + rollOffset) - abs(ypr.roll)) > 0.3490)
  {
    Console.print("Last roll : ");
    Console.print(ypr.roll);
    Console.print(" Actual roll : ");
    Console.println(imu.roll);
    Console.println("roll change more than 20 degres in less than 50 ms ????????? value is skip");
  }
  else
  {
    ypr.roll = imu.roll;
  }
  //final result for gyro accel part
  ypr.pitch = imu.pitch + pitchOffset ;
  ypr.roll = imu.roll + rollOffset;
  gyroAccYaw = scalePI(imu.yaw);  // the Gyro Yaw very accurate but drift

  if (robot.CompassUse) {
    readCompass();
  }
  else
  {
    comYaw = 0;
    CompassGyroOffset = 0;
  }
  ypr.yaw = scalePI(-1 * gyroAccYaw + CompassGyroOffset) ;


/*
  Console.print(comYaw * 180 / PI);
  Console.print("  ,  ");
  Console.print(ypr.yaw * 180 / PI);
  Console.print("  ,  ");
  Console.print(ypr.pitch * 180 / PI);
  Console.print(",");
  Console.print(ypr.roll * 180 / PI);
  Console.println("");
*/


}

void IMUClass::readCompass() {

  imu.updateCompass();
  com.x = imu.mx;
  com.y = imu.my;
  com.z = imu.mz;
   /*
     MPU-9250 gyro and AK8963 magnetometer XY axes are orientated 90 degrees to each other
     which means that Mag_pitch equates to the Gyro_roll and Mag_roll equates to the Gryro_pitch

     The MPU-9520 and AK8963 Z axes point in opposite directions
     which means that the sign for Mag_pitch must be negative to compensate.
  */
  Mag_pitch = -ypr.roll;
  Mag_roll = ypr.pitch;


  if (useComCalibration) {
    Mag_x = (imu.mx - comOfs.x) * comScale.x;
    Mag_y = (imu.my - comOfs.y) * comScale.y;
    Mag_z = (imu.mz - comOfs.z) * comScale.z;

  }
  else
  {
    Mag_x = imu.mx ;
    Mag_y = imu.my ;
    Mag_z = imu.mz ;

  }

  // ----- Apply the standard tilt formulas
  Mag_x_hor = Mag_x * cos(Mag_pitch) + Mag_y * sin(Mag_roll) * sin(Mag_pitch) - Mag_z * cos(Mag_roll) * sin(Mag_pitch);
  Mag_y_hor = Mag_y * cos(Mag_roll) + Mag_z * sin(Mag_roll);

  // ----- filter any data fluctuations
  // Mag_x_dampened = Mag_x_dampened * 0.9 + Mag_x_hor * 0.1;
  //Mag_y_dampened = Mag_y_dampened * 0.9 + Mag_y_hor * 0.1;
  
  // no filter
  Mag_x_dampened =  Mag_x_hor ;
  Mag_y_dampened =  Mag_y_hor ;


  

  // ----- Calculate the compass heading
  comYaw = atan2(Mag_x_dampened, Mag_y_dampened);  // Magnetic North


}

void IMUClass::loadSaveCalib(boolean readflag) {

  int addr = ADDR;
  short magic = MAGIC;
  if (readflag) Console.println(F("Load Calibration"));
  else Console.println(F("Save Calibration"));
  eereadwrite(readflag, addr, magic); // magic
  //accelgyro offset
  eereadwrite(readflag, addr, ax_offset);
  eereadwrite(readflag, addr, ay_offset);
  eereadwrite(readflag, addr, az_offset);
  eereadwrite(readflag, addr, gx_offset);
  eereadwrite(readflag, addr, gy_offset);
  eereadwrite(readflag, addr, gz_offset);
  //compass offset
  eereadwrite(readflag, addr, comOfs);
  eereadwrite(readflag, addr, comScale);
  Console.print(F("Calibration address Start = "));
  Console.println(ADDR);
  Console.print(F("Calibration address Stop = "));
  Console.println(addr);

}


void IMUClass::printPt(point_float_t p) {
  Console.print(p.x);
  Console.print(",");
  Console.print(p.y);
  Console.print(",");
  Console.println(p.z);
}
void IMUClass::printCalib() {

  Console.println(F("-------- IMU CALIBRATION  --------"));
  Console.print("ACCEL GYRO MPU6050 OFFSET ax: ");
  Console.print(ax_offset);
  Console.print(" ay: ");
  Console.print(ay_offset);
  Console.print(" az: ");
  Console.print(az_offset);
  Console.print(" gx: ");
  Console.print(gx_offset);
  Console.print(" gy: ");
  Console.print(gy_offset);
  Console.print(" gz: ");
  Console.println(gz_offset);
  Console.print("COMPASS OFFSET X.Y.Z AND SCALE X.Y.Z   --> ");
  Console.print(F("comOfs="));
  printPt(comOfs);
  Console.print(F("comScale="));
  printPt(comScale);
  Console.println(F("."));

}

void IMUClass::loadCalib() {

  short magic = 0;
  int addr = ADDR;
  eeread(addr, magic);
  if (magic != MAGIC) {
    Console.println(F("IMU error: no calib data"));
    ax_offset = 376;
    ay_offset = -1768;
    az_offset = 1512;
    gx_offset = 91;
    gy_offset = 12;
    gz_offset = -2;


    comOfs.x = 0.00;
    comOfs.y = 0.00;
    comOfs.z = 0.00;
    comScale.x = 1.00;
    comScale.y = 1.00;
    comScale.z = 1.00;

    useComCalibration = false;


    return;
  }
  //calibrationAvail = true;
  useComCalibration = true;
  Console.println(F("IMU: found calib data"));
  loadSaveCalib(true);

}

void IMUClass::saveCalib() {
  loadSaveCalib(false);
}


void IMUClass::deleteCompassCalib() {

  int addr = ADDR;
  eewrite(addr, (short)0); // magic
  comOfs.x = comOfs.y = comOfs.z = 0;
  comScale.x = comScale.y = comScale.z = 2;
  Console.println("Compass and GYRO calibration deleted");

}
void IMUClass::deleteAccelGyroCalib() {
  
    int addr = ADDR;
    eewrite(addr, (short)0); // magic
    ax_offset = ay_offset = az_offset = 0;
    gx_offset = gy_offset = gz_offset = 0;


    Console.println("AccelGyro calibration deleted ");
  
}


// calculate gyro offsets
void IMUClass::calibGyro() {
  /*
    Console.println("Reading sensors for first time... without any offset");
    watchdogReset();
    // meansensors();
    watchdogReset();
    Console.print("Reading ax: ");
    Console.print(mean_ax);
    Console.print(" ay: ");
    Console.print(mean_ay);
    Console.print(" az: ");
    Console.print(mean_az);
    Console.print(" gx: ");
    Console.print(mean_gx);
    Console.print(" gy: ");
    Console.print(mean_gy);
    Console.print(" gz: ");
    Console.println(mean_gz);

    Console.println("\nCalculating offsets...");
    watchdogReset();
    //calibration();
    watchdogReset();
    //meansensors();
    watchdogReset();
    /*
    Console.print("FINISHED reading Value with new offset,If all is OK need to be close 0 exept the az close to 16384");
    Console.print(" New reading ax: ");
    Console.print(mean_ax);
    Console.print(" ay: ");
    Console.print(mean_ay);
    Console.print(" az: ");
    Console.print(mean_az);
    Console.print(" gx: ");
    Console.print(mean_gx);
    Console.print(" gy: ");
    Console.print(mean_gy);
    Console.print(" gz: ");
    Console.println(mean_gz);
    watchdogReset();
    Console.print("THE NEW OFFSET ax: ");
    Console.print(ax_offset);
    Console.print(" ay: ");
    Console.print(ay_offset);
    Console.print(" az: ");
    Console.print(az_offset);
    Console.print(" gx: ");
    Console.print(gx_offset);
    Console.print(" gy: ");
    Console.print(gy_offset);
    Console.print(" gz: ");
    Console.println(gz_offset);
    watchdogReset();
    saveCalib();
  */

}


void IMUClass::calibComStartStop() {

  while ((!robot.RaspberryPIUse) && (Console.available())) Console.read(); //use to start and stop the calibration

  
  if (state == IMU_CAL_COM) {
    // stop
    Console.println(F("com calib completed"));
    //calibrationAvail = true;

    // ----- Calculate hard-iron offsets
    comOfs.x = (comMax.x + comMin.x) / 2;                     // Get average magnetic bias in counts
    comOfs.y = (comMax.y + comMin.y) / 2;
    comOfs.z = (comMax.z + comMin.z) / 2;

    // ----- Calculate soft-iron scale factors
    chord_x = ((float)(comMax.x - comMin.x)) / 2;                 // Get average max chord length in counts
    chord_y = ((float)(comMax.y - comMin.y)) / 2;
    chord_z = ((float)(comMax.z - comMin.z)) / 2;
    Console.println(chord_x);
    Console.println(chord_y);
    Console.println(chord_z);
    
    chord_average = (chord_x + chord_y + chord_z) / 3;              // Calculate average chord length
    Console.println(chord_average);
    comScale.x = chord_average / chord_x;                          // Calculate X scale factor
    comScale.y = chord_average / chord_y;                          // Calculate Y scale factor
    comScale.z = chord_average / chord_z;




    //bber18
    if ((comScale.x == 0) || (comScale.y == 0) || (comScale.z == 0)) { //jussip bug found div by 0 later
      Console.println(F("*********************ERROR WHEN CALIBRATE : VALUE ARE TOTALY WRONG CHECK IF COMPASS IS NOT TOTALY PERTURBATE **************"));
      comOfs.x = comOfs.y = comOfs.z = 0;
      comScale.x = comScale.y = comScale.z = 2;
    }
    saveCalib();
    printCalib();
    useComCalibration = true;
    state = IMU_RUN;


  }
  else
  {
    // start
    Console.println(F("compass calibration..."));
    Console.println(F("rotate mower 360 degree around all three axis until NO new data are coming"));
    watchdogReset();
    foundNewMinMax = false;
    useComCalibration = false;
    state = IMU_CAL_COM;
    comMin.x = comMin.y = comMin.z = 9999;
    comMax.x = comMax.y = comMax.z = -9999;
  }

}
void IMUClass::calibComUpdate() {

  readCompass();
  watchdogReset();
  boolean newfound = false;
  //if ( (abs(com.x - comLast.x) < 10) &&  (abs(com.y - comLast.y) < 10) &&  (abs(com.z - comLast.z) < 10) ) {
  if (com.x < comMin.x) {
    comMin.x = com.x;
    newfound = true;
  }
  if (com.y < comMin.y) {
    comMin.y = com.y;
    newfound = true;
  }
  if (com.z < comMin.z) {
    comMin.z = com.z;
    newfound = true;
  }
  if (com.x > comMax.x) {
    comMax.x = com.x;
    newfound = true;
  }
  if (com.y > comMax.y) {
    comMax.y = com.y;
    newfound = true;
  }
  if (com.z > comMax.z) {
    comMax.z = com.z;
    newfound = true;
  }
  if (newfound) {
    foundNewMinMax = true;
    watchdogReset();
    Console.print("x:");
    Console.print(comMin.x);
    Console.print(",");
    Console.print(comMax.x);
    Console.print("\t  y:");
    Console.print(comMin.y);
    Console.print(",");
    Console.print(comMax.y);
    Console.print("\t  z:");
    Console.print(comMin.z);
    Console.print(",");
    Console.print(comMax.z);
    Console.println("\t");
  }


}
float IMUClass::rotate360(float x)
{
  x += 360;
  if (x >= 360) x -= 360;
  if (x < 0) x += 360;
  return x;
}


float IMUClass::distance180(float x, float w)
{
  float d = scale180(w - x);
  if (d < -180) d = d + 2 * 180;
  else if (d > 180) d = d - 2 * 180;
  return d;
}

//bb
float IMUClass::scale180(float v)
{
  float d = v;
  while (d < 0) d += 2 * 180;
  while (d >= 2 * 180) d -= 2 * 180;
  if (d >= 180) return (-2 * 180 + d);
  else if (d < -180) return (2 * 180 + d);
  else return d;
}
