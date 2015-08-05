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


#include "particles.h"
#include "simrobot.h"
#include "sim.h"
#include <vector>
#include <algorithm>

using namespace std;

Particles::Particles(){
}

void Particles::init(float x, float y, float theta,
              float steering_noise, float distance_noise, float measurement_noise, int N)
{
    //	initializes particle set with given initial position
    this->N = N;
    this->steering_noise = steering_noise;
    this->distance_noise = distance_noise;
    this->measurement_noise = measurement_noise;

    for (int i=0; i < N; i++){
       SimRobot r;
       r.set(x, y, theta);
       r.set_noise(steering_noise, distance_noise, measurement_noise);
       data.push_back(r);
    }
}


// extract position from a particle set
void Particles::get_position(float &x, float &y, float &orientation){
  x=0;
  y=0;
  orientation=0;
  for (int i=0; i < N; i++){
    x += data[i].x;
    y += data[i].y;
    // orientation is tricky because it is cyclic. By normalizing
    // around the first particle we are somewhat more robust to
    // the 0=2pi problem
    orientation += ( fmod((data[i].orientation
                    - data[0].orientation + M_PI) , (2.0 * M_PI))
                    + data[0].orientation - M_PI);
  }
  x/=N;
  y/=N;
  orientation/=N;
}


// motion of the particles
void Particles::move(Sim &sim, float course, float speed){
  //vector <SimRobot>newdata;
  for (int i=0; i < N; i++){
    //SimRobot r = data[i].move(world, steer, speed);
    data[i].move(sim, course, speed);
    //newdata.push_back(r);
  }
  //data = newdata;
}


// sensing and resampling
void Particles::sense(Sim &sim, float measurement){
  vector<float>w;
  for (int i=0; i < N; i++){
    w.push_back(data[i].measurement_prob(sim, measurement));
  }
  // resampling (careful, this is using shallow copy)
  vector<SimRobot>p3;
  int index = floor(random() * N);
  float beta = 0.0;
  float mw = *max_element(w.begin(), w.end());
  for (int i=0; i < N; i++){
    beta += random() * 2.0 * mw;
    while (beta > w[index]){
      beta -= w[index];
      index = (index + 1) % N;
    }
    p3.push_back(data[index]);
  }
  data = p3;
}

// draw particle set
void Particles::draw(Mat &img){
  for (int i =0; i < N; i++){
    data[i].draw(img, true);
  }
}

// draw particle set center
void Particles::drawCenter(Mat &img, float x, float y, float theta){
  float length = 7;
  circle( img, Point( x, y), length, Scalar( 255, 0, 0), 2, 8 );
  line( img, Point(x, y), Point(x + 15 * cos(theta), y + length * sin(theta)), Scalar(255,0,0), 2, 8);
}
