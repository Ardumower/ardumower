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

#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;


// states
enum {
  STATE_FORW,
  STATE_REV,
  STATE_ROLL,
};

class World;

class SimRobot
{
  public:
    float speed;
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
    void move(World &world, float steering, float distance,
             float tolerance = 0.001, float max_steering_angle = M_PI / 4.0);
    // measurement_prob
    //    computes the probability of a measurement
    float measurement_prob(vector <float>measurement);
    // draw robot on surface
    void draw(Mat &img, bool drawAsFilter = false);
    // run robot controller
    void control(World &world, float timeStep);
    void sense(World &world);
};



#endif
