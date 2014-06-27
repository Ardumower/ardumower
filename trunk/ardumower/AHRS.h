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

#ifndef AHRS_H
#define AHRS_H

/* 
 * Ku = 30 : max value for Kp = Ku / 2.2 = 13.6
 * Ki = 0.2
 */
class AHRS
{
public:
  // quaternion elements representing the estimated orientation
  float q0;
  float q1;
  float q2;
  float q3;

  inline AHRS(float cKpAcc = 13.6, float cKiAcc = 0.2, float cKpMag = 13.6, float cKiMag = 0.2)
    : KpAcc(cKpAcc), KiAcc(cKiAcc), KpMag(cKpMag), KiMag(cKiMag), q0(1), q1(0), q2(0), q3(0), exInt(0), eyInt(0), ezInt(0) {}
   
  void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float halfT, bool normalize = true);

private:
  // proportional gain governs rate of convergence to accelerometer/magnetometer
  float KpAcc;
  float KpMag;
  //integral gain governs rate of convergence of gyroscope biases
  float KiAcc;
  float KiMag;
    
  //scaled integral error
  float exInt;
  float eyInt;
  float ezInt;
};


#endif  // AHRS_h

