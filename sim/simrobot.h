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
    Mat imgBfieldRobot;
    float speed;
    int state;
    float stateTime;
    int plotIdx;
    double x;
    double y;
    double orientation;
    double length;
    double steering_noise;
    double distance_noise;
    double measurement_noise;
    int num_collision;
    int num_steps;
    // initializes robot
    SimRobot(double length = 0.5);
    // sets a robot coordinate
    void set(double new_x, double new_y, double new_orientation);
    // sets the noise parameters
    void set_noise(double new_s_noise, double new_d_noise, double new_m_noise);
    // move:
    //    steering = front wheel steering angle, limited by max_steering_angle
    //    distance = total distance driven, most be non-negative
    SimRobot move(World &world, double steering, double distance,
             double tolerance = 0.001, double max_steering_angle = M_PI / 4.0);
    // measurement_prob
    //    computes the probability of a measurement
    double measurement_prob(vector <double>measurement);
    // draw robot on surface
    void draw(Mat &img);
    // run robot controller
    void run(World &world, float timeStep);

    void plotXY(Mat &image, int x, int y, int r, int g, int b, bool clearplot);
};



#endif
