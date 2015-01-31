#include "particles.h"
#include "simrobot.h"
#include <vector>
#include <algorithm>

using namespace std;


Particles::Particles(double x, double y, double theta,
              double steering_noise, double distance_noise, double measurement_noise, int N)
{
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


void Particles::get_position(double &x, double &y, double &orientation){
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


void Particles::move(World &world, double steer, double speed){
  vector <SimRobot>newdata;
  for (int i=0; i < N; i++){
    SimRobot r = data[i].move(world, steer, speed);
    newdata.push_back(r);
  }
  data = newdata;
}

void Particles::sense(vector<double>Z){
  vector<double>w;
  for (int i=0; i < N; i++){
    w.push_back(data[i].measurement_prob(Z));
  }
  // resampling (careful, this is using shallow copy)
  vector<SimRobot>p3;
  int index = rand() % N;
  double beta = 0.0;
  double mw = *max_element(w.begin(), w.end());
  for (int i=0; i < N; i++){
    beta += fmod(rand(), (2.0 * mw));
    while (beta > w[index]){
      beta -= w[index];
      index = (index + 1) % N;
    }
    p3.push_back(data[index]);
  }
  data = p3;
}


