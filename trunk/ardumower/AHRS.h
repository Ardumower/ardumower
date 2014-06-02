#ifndef AHRS_H
#define AHRS_H

/*
 * http://starfinder.altervista.org/
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

