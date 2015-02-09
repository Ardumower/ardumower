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
#include "common.h"
#include "pid.h"

using namespace std;
using namespace cv;


// states
enum {
  STATE_OFF,
  STATE_FORW,
  STATE_REV,
  STATE_ROLL,
  STATE_TRACK,
};

class World;
class Sim;

// simulated robot
class SimRobot
{
  public:
    //float robotMap[WORLD_SIZE_Y/10][WORLD_SIZE_X/10];
    PID pidTrack;
    float distanceToChgStation;
    float speed; // meter/sec
    float totalDistance; // meters
    int state;
    float steer;
    float stateTime;
    float bfieldStrength;
    float x;
    float y;
    float orientation;
    float length;
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
    void move(Sim &sim, float course, float distance,
             float tolerance = 0.001, float max_steering_angle = M_PI / 4.0);
    // measurement_prob
    //    computes the probability of a measurement
    float measurement_prob(Sim &sim, float measurement);
    // draw robot on surface
    void draw(Mat &img, bool drawAsFilter = false);
    // run robot controller
    void control(Sim &sim, float timeStep);
    void sense(Sim &sim);
};



#endif
