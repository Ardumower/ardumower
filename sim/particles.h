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


#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include <opencv2/core/core.hpp>



//#include "robot.h"

using namespace cv;
using namespace std;

class World;
class SimRobot;
class Sim;

// particle filter (with N particles)
class Particles
{
  public:
    int N; // particle count
    float steering_noise;
    float distance_noise;
    float measurement_noise;
    vector <SimRobot>data; // particles
    Particles();
    // creates particle set with given initial position
    void init(float x, float y, float theta,
              float steering_noise, float distance_noise, float measurement_noise, int N = 100);
    // extract position from a particle set
    void get_position(float &x, float &y, float &orientation);
    // motion of particles
    void move(Sim &sim, float course, float speed);
    // sensing and resampling
    void sense(Sim &sim, float measurement);
    void draw(Mat &img);
    void drawCenter(Mat &img, float x, float y, float theta);
};


#endif
