/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  
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


#include "simrobot.h"
#include "world.h"
#include "particles.h"
#include "sim.h"

using namespace std;

SimRobot::SimRobot(){
  //	creates robot and initializes location/orientation to 0, 0, 0
  //memset(robotMap, 0, sizeof robotMap);
  distanceToChgStation = 0;
  totalDistance = 0;
  state = STATE_TRACK;
  //state = STATE_LANE_FORW;
  pidTrack.Kp    = 0.08;  // perimeter PID controller
  pidTrack.Ki    = 0.02;
  pidTrack.Kd    = 0.08;

  pidHeading.Kp    = 0.08;  // heading PID controller
  pidHeading.Ki    = 0.02;
  pidHeading.Kd    = 0.08;

  stateTime = 0;
  x = y = orientation = 0;
  laneHeading = M_PI/4;
  laneDistance = 0;
  laneCounter = 0;
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


//    steering = front wheel steering angle (rad), limited by max_steering_angle
//    distance = total distance driven (1/10m), most be non-negative
void SimRobot::move(Sim &sim, float course, float distance,
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
  totalDistance += fabs(distance2);
  // printf("distance: %3.3f  steering: %3.3f\n", distance2, steering2);

  // Execute motion
  //float turn = tan(steering2) * distance2 / length;
  //float turn = steering2;
  //if (abs(turn) < tolerance){
    // approximate by straight line motion
    //printf("line motion  steering2=%3.3f  turn=%3.3f\n", steering2, turn);
    x = x + (distance2 * cos(course2)) ;
    y = y + (distance2 * sin(course2)) ;
    //orientation = scalePI( orientation + turn);
    orientation = scalePI( course2 );
  /*} else {
    // approximate bicycle model for motion
    float radius = distance2 / turn;
    float cx = x - (sin(orientation) * radius);
    float cy = y + (cos(orientation) * radius);
    orientation = scalePI((orientation + turn );
    x = cx + (sin(orientation) * radius);
    y = cy - (cos(orientation) * radius);
  }*/
}


// measures magnetic field
void SimRobot::sense(Sim &sim){
  bfieldStrength = sim.world.getBfield(x, y, 1);
  bfieldStrength += gauss(0.0, measurement_noise);
  //printf("b=%3.4f\n", b);
}

//  computes the probability of a measurement
float SimRobot::measurement_prob(Sim &sim, float measurement){
  float prob = 1.0;

  // calculate Gaussian
  // gaussian(mu, sigma, x)
  prob *= gaussian(sim.world.getBfield(x, y), measurement_noise, measurement);

  return prob;
}


// run robot controller
void SimRobot::control(Sim &sim, float timeStep){
  float laneHeadingTurn = M_PI*0.15;
  if (laneCounter % 2 != 0) laneHeadingTurn *= -1;

  float deltaDistance = totalDistance - lastTotalDistance;
  distanceToChgStation = distance(x,y, sim.world.chgStationX, sim.world.chgStationY);

  switch (state) {
    case STATE_OFF:
           speed = 0;
           break;
    case STATE_TRACK:
           if (sim.simTime > 10) {
             if (distanceToChgStation < 10){
               printf("LANE_REV\n");
               state=STATE_LANE_REV;
               stateTime=0;
             }
           }
           pidTrack.x = 0;
           if (bfieldStrength < 0) pidTrack.x = -1;
            else if (bfieldStrength > 0) pidTrack.x = 1;
           pidTrack.w = 0;
           pidTrack.y_min = -M_PI;
           pidTrack.y_max = M_PI;
           pidTrack.max_output = M_PI;
           pidTrack.compute(sim.simTime);
           orientation = scalePI(orientation + pidTrack.y);
           speed = 0.5;
           break;
    case STATE_LANE_FORW:
           laneDistance += deltaDistance;
           if (laneDistance < 2){
            pidHeading.x = distancePI(orientation, scalePI(laneHeading+laneHeadingTurn));
           } else {
            pidHeading.x = distancePI(orientation, laneHeading);
           }
           pidHeading.w = 0;
           pidHeading.y_min = -M_PI/4;
           pidHeading.y_max = M_PI/4;
           pidHeading.max_output = M_PI/4;
           pidHeading.compute(sim.simTime);
           orientation = scalePI(orientation - pidHeading.y);
           speed = 0.5;
           //steer = 0;
           if (bfieldStrength < 0) { //|| (laneDistance > 300)) {
             printf("LANE_REV\n");
             state=STATE_LANE_REV;
             stateTime=0;
             laneDistance =0;
           }
           break;
    case STATE_LANE_REV:
           laneDistance += deltaDistance;
           speed = -0.5;
           //steer = 0;
           if (laneDistance > 15.0){
             printf("LANE_ROLL\n");
             state=STATE_LANE_ROLL;
             stateTime=0;
             laneDistance =0;
             laneHeading = scalePI(laneHeading + M_PI);
           }
           break;
    case STATE_LANE_ROLL:
           speed=0;
           //steer = M_PI/16;
           float e = distancePI(orientation, scalePI(laneHeading+laneHeadingTurn));
           if (e > 0)
             orientation = scalePI(orientation + M_PI/72);
           else
             orientation = scalePI(orientation - M_PI/72);
           if (abs(e) < M_PI/36){
             //printf("err=%3.1f\n", e/M_PI*180);
             //getchar();
             printf("LANE_FORW\n");
             state=STATE_LANE_FORW;
             stateTime=0;
             laneDistance =0;
             laneCounter++;
           }
           break;
  }

  lastTotalDistance = totalDistance;
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





