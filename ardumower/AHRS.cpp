#include <Arduino.h>
#include "AHRS.h"


void AHRS::update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float halfT, bool normalize)
{
      float norm;
      float hx, hy, hz, bx, bz;
      float vx, vy, vz, wx, wy, wz;
      float q0i, q1i, q2i, q3i;
      float exAcc, eyAcc, ezAcc;
      float exMag, eyMag, ezMag;

      // auxiliary variables to reduce number of repeated operations
      float q0q0 = q0*q0;
      float q0q1 = q0*q1;
      float q0q2 = q0*q2;
      float q0q3 = q0*q3;
      float q1q1 = q1*q1;
      float q1q2 = q1*q2;
      float q1q3 = q1*q3;
      float q2q2 = q2*q2;   
      float q2q3 = q2*q3;
      float q3q3 = q3*q3;          
      
      // normalise the measurements
      norm = sqrt(ax*ax + ay*ay + az*az);       
      ax = ax / norm;
      ay = ay / norm;
      az = az / norm;
      norm = sqrt(mx*mx + my*my + mz*mz);          
      mx = mx / norm;
      my = my / norm;
      mz = mz / norm;         
      
      // compute reference direction of flux
      hx = 2*mx*( 0.5 - q2q2 - q3q3) + 2*my*(q1q2 - q0q3) + 2*mz*(q1q3 + q0q2);
      hy = 2*mx*(q1q2 + q0q3) + 2*my*(0.5 - q1q1 - q3q3) + 2*mz*(q2q3 - q0q1);
      hz = 2*mx*(q1q3 - q0q2) + 2*my*(q2q3 + q0q1) + 2*mz*(0.5 - q1q1 - q2q2);         
      bx = sqrt((hx*hx) + (hy*hy));
      bz = hz;        

      // estimated direction of gravity and flux (v and w)
      vx = 2*(q1q3 - q0q2);
      vy = 2*(q0q1 + q2q3);
      vz = q0q0 - q1q1 - q2q2 + q3q3;
      wx = 2*bx*(0.5 - q2q2 - q3q3) + 2*bz*(q1q3 - q0q2);
      wy = 2*bx*(q1q2 - q0q3) + 2*bz*(q0q1 + q2q3);
      wz = 2*bx*(q0q2 + q1q3) + 2*bz*(0.5 - q1q1 - q2q2);  
      
      // error is sum of cross product between reference direction of fields and direction measured by sensors
      exAcc = (ay*vz - az*vy);
      eyAcc = (az*vx - ax*vz);
      ezAcc = (ax*vy - ay*vx);
 
      exMag = (my*wz - mz*wy);
      eyMag = (mz*wx - mx*wz);
      ezMag = (mx*wy - my*wx);

      // integral error scaled integral gain
      exInt = exInt + exAcc*KiAcc + exMag*KiMag;
      eyInt = eyInt + eyAcc*KiAcc + eyMag*KiMag;
      ezInt = ezInt + ezAcc*KiAcc + ezMag*KiMag;

      // adjusted gyroscope measurements
      gx = gx + exAcc*KpAcc + exMag*KpMag + exInt;
      gy = gy + eyAcc*KpAcc + eyMag*KpMag + eyInt;
      gz = gz + ezAcc*KpAcc + ezMag*KpMag + ezInt;

      // integrate quaternion rate and normalise
      q0i = (-q1*gx - q2*gy - q3*gz) * halfT;
      q1i = ( q0*gx + q2*gz - q3*gy) * halfT;
      q2i = ( q0*gy - q1*gz + q3*gx) * halfT;
      q3i = ( q0*gz + q1*gy - q2*gx) * halfT;

      q0 += q0i;
      q1 += q1i;
      q2 += q2i;
      q3 += q3i;

      // normalise quaternion
      norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
      q0 = q0 / norm;
      q1 = q1 / norm;
      q2 = q2 / norm;
      q3 = q3 / norm;
}




