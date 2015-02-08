#include "simrobot.h"
#include "world.h"
#include "particles.h"
#include <exception>
#include <stdio.h>
#include "common.h"

using namespace std;

SimRobot::SimRobot(){
  //	creates robot and initializes location/orientation to 0, 0, 0
  time_t t;
  time(&t);
  srand((unsigned int)t);

  state = STATE_FORW;
  stateTime = 0;
  x = y = orientation = 0;
  speed = 0;
  steer = 0;
  length = 7;
  steering_noise    = 0.0;
  distance_noise    = 0.0;
  measurement_noise = 0.0;
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


//    steering = front wheel steering angle, limited by max_steering_angle
//    distance = total distance driven, most be non-negative
void SimRobot::move(World &world, float course, float distance,
             float tolerance,  float max_steering_angle){
  /*if (steering > max_steering_angle)
    steering = max_steering_angle;
  if (steering < -max_steering_angle)
    steering = -max_steering_angle;*/

  // apply noise
  // gauss(mean, std)
  //float steering2 = gauss(steering, steering_noise);
  float course2 = gauss(course, steering_noise);
  float distance2 = gauss(distance, distance_noise) ;
  // printf("distance: %3.3f  steering: %3.3f\n", distance2, steering2);

  // Execute motion
  //float turn = tan(steering2) * distance2 / length;
  //float turn = steering2;
  //if (abs(turn) < tolerance){
    // approximate by straight line motion
    //printf("line motion  steering2=%3.3f  turn=%3.3f\n", steering2, turn);
    x = x + (distance2 * cos(course2));
    y = y + (distance2 * sin(course2));
    //orientation = fmod( (orientation + turn) , (2.0 * M_PI) );
    orientation = fmod( course2, (2.0 * M_PI) );
  /*} else {
    // approximate bicycle model for motion
    float radius = distance2 / turn;
    float cx = x - (sin(orientation) * radius);
    float cy = y + (cos(orientation) * radius);
    orientation = fmod( (orientation + turn), (2.0 * M_PI) );
    x = cx + (sin(orientation) * radius);
    y = cy - (cos(orientation) * radius);
  }*/
}


// measures magnetic field
void SimRobot::sense(World &world){
  bfieldStrength = world.getBfield(x, y);
  bfieldStrength += gauss(0.0, measurement_noise);
  //printf("b=%3.4f\n", b);
}

//  computes the probability of a measurement
float SimRobot::measurement_prob(World &world, float measurement){
  float prob = 1.0;

  // calculate Gaussian
  // gaussian(mu, sigma, x)
  prob *= gaussian(world.getBfield(x, y), measurement_noise, measurement);

  return prob;
}

// run robot controller
void SimRobot::control(World &world, float timeStep){
  switch (state) {
    case STATE_FORW:
           speed = 1.0;
           //steer = 0;
           if (bfieldStrength < 0){
             printf("REV\n");
             state=STATE_REV;
             stateTime=0;
           }
           break;
    case STATE_REV:
           speed = -1.0;
           //steer = 0;
           if (stateTime > 1.0){
             printf("ROLL\n");
             state=STATE_ROLL;
             stateTime=0;
           }
           break;
    case STATE_ROLL:
           speed=0;
           //steer = M_PI/16;
           orientation = fmod(orientation + M_PI/16, 2*M_PI);
           if (stateTime > 1.0){
             printf("FORW\n");
             state=STATE_FORW;
             stateTime=0;
           }
           break;
  }

  stateTime += timeStep;
}


void SimRobot::draw(Mat &img, bool drawAsFilter){
  if (drawAsFilter) {
    circle( img, Point( x, y), length, Scalar( 255, 255, 255), 2, 8 );
    line( img, Point(x, y), Point(x + length * cos(orientation), y + length * sin(orientation)), Scalar(255,255,255), 2, 8);
  } else {
    circle( img, Point( x, y), length, Scalar( 0, 0, 0 ), 2, 8 );
    line( img, Point(x, y), Point(x + length * cos(orientation), y + length * sin(orientation)), Scalar(0,0,0), 2, 8);
  }
}





