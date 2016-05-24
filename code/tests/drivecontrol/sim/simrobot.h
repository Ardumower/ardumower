/*
  Ardumower (www.ardumower.de)

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


#ifndef SIMROBOT_H
#define SIMROBOT_H

#include <opencv2/core/core.hpp>
//#include "common.h"



// states
enum {
  STATE_OFF,
  STATE_TRACK,
  STATE_LANE_FORW,
  STATE_LANE_REV,
  STATE_LANE_ROLL,
  STATE_GOAL,
};


// simulated robot
class SimRobot
{
  public:
    int odometryTicksPerRevolution;
    float odometryTicksPerCm;
    float odometryWheelBaseCm;
    float distanceToChgStation;
    float leftMotorSpeed; // meter/sec
    float rightMotorSpeed;
    float totalDistance; // meters
    float lastTotalDistance;
    float x; // cm
    float y;
    float orientation; // rad
    float motor_noise; // motor speed 'noise'
    float steering_noise;
    float distance_noise;
    float measurement_noise;
    int num_collision;
    int num_steps;
    // initializes robot
    SimRobot();
    // sets a robot coordinate
    void set(float new_x, float new_y, float new_orientation);
    // sets the noise parameters
    void set_noise(float new_s_noise, float new_d_noise, float new_m_noise);
    // move:
    //    steering = front wheel steering angle, limited by max_steering_angle
    //    distance = total distance driven, most be non-negative
    void move(float course, float distance,
             float tolerance = 0.001, float max_steering_angle = M_PI / 4.0);
    // measurement_prob
    //    computes the probability of a measurement
    float measurement_prob(float measurement);
    // draw robot on surface
    void draw(cv::Mat &img, bool drawAsFilter = false);
    // run robot controller
    void control(float timeStep);
    void sense();
};

extern SimRobot Robot;

#endif
