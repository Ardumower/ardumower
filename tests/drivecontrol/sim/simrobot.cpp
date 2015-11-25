#include "simrobot.h"
#include "world.h"
#include "sim.h"


SimRobot Robot;


SimRobot::SimRobot(){
  //	creates robot and initializes location/orientation to 0, 0, 0
  //memset(robotMap, 0, sizeof robotMap);
  distanceToChgStation = 0;
  totalDistance = 0;

  x = y = orientation = 0;
  odometryTicksPerRevolution = 1060;
  odometryTicksPerCm = 13.49;
  odometryWheelBaseCm = 36;    // wheel-to-wheel distance (cm)
  leftMotorSpeed = 30;
  rightMotorSpeed = 5;

  steering_noise    = 0.0;
  distance_noise    = 0.0;
  measurement_noise = 0.0;
  motor_noise = 10;
}

//sets a robot coordinate
void SimRobot::set(float new_x, float new_y, float new_orientation){
  x = new_x;
  y = new_y;
  orientation = new_orientation;
}

//	sets the noise parameters
void SimRobot::set_noise(float new_s_noise, float new_d_noise, float new_m_noise){
  // makes it possible to change the noise parameters
  // this is often useful in particle filters
  steering_noise    = new_s_noise;
  distance_noise    = new_d_noise;
  measurement_noise = new_m_noise;
}


//    steering = front wheel steering angle (rad), limited by max_steering_angle
//    distance = total distance driven (cm), most be non-negative
void SimRobot::move(float course, float distance,
             float tolerance,  float max_steering_angle){
  /*if (steering > max_steering_angle)
    steering = max_steering_angle;
  if (steering < -max_steering_angle)
    steering = -max_steering_angle;*/

  float cmPerRound = odometryTicksPerRevolution / odometryTicksPerCm;

  // apply noise
  // gauss(mean, std)
  float leftSpeedNoise  = leftMotorSpeed;
  float rightSpeedNoise = rightMotorSpeed;

  rightSpeedNoise = gauss(rightMotorSpeed, motor_noise);
  leftSpeedNoise = gauss(leftMotorSpeed, motor_noise);

  float left_cm = leftSpeedNoise * cmPerRound/60.0 * Sim.timeStep;
  float right_cm = rightSpeedNoise * cmPerRound/60.0 * Sim.timeStep;

  double avg_cm  = (left_cm + right_cm) / 2.0;
  double wheel_theta = (left_cm - right_cm) / odometryWheelBaseCm;
  orientation = scalePI( orientation + wheel_theta );
  x = x + (avg_cm * cos(orientation)) ;
  y = y + (avg_cm * sin(orientation)) ;

  totalDistance += fabs(avg_cm/100.0);

}


// measures magnetic field
void SimRobot::sense(){
  //bfieldStrength = sim.world.getBfield(x, y, 1);
  //bfieldStrength += gauss(0.0, measurement_noise);
  //printf("b=%3.4f\n", b);
}

//  computes the probability of a measurement
float SimRobot::measurement_prob(float measurement){
  float prob = 1.0;

  // calculate Gaussian
  // gaussian(mu, sigma, x)
  prob *= gaussian(World.getBfield(x, y), measurement_noise, measurement);

  return prob;
}


// run robot controller
void SimRobot::control(float timeStep){

  float deltaDistance = totalDistance - lastTotalDistance;
  distanceToChgStation = distance(x,y, World.chgStationX, World.chgStationY);

}


void SimRobot::draw(cv::Mat &img, bool drawAsFilter){
  float r = odometryWheelBaseCm/2;
  if (drawAsFilter) {
    circle( img, cv::Point( x, y), r, cv::Scalar( 255, 255, 255), 2, 8 );
    line( img, cv::Point(x, y), cv::Point(x + r * cos(orientation), y + r * sin(orientation)), cv::Scalar(255,255,255), 2, 8);
  } else {
    circle( img, cv::Point( x, y), r, cv::Scalar( 0, 0, 0 ), 2, 8 );
    line( img, cv::Point(x, y), cv::Point(x + r * cos(orientation), y + r * sin(orientation)), cv::Scalar(0,0,0), 2, 8);
  }
}





