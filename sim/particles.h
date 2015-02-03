#ifndef PARTICLES_H

#include <vector>

//#include "robot.h"

using namespace std;

class World;
class SimRobot;


class Particles
{
  public:
    int N; // particle count
    float steering_noise;
    float distance_noise;
    float measurement_noise;
    vector <SimRobot>data; // particles
    // creates particle set with given initial position
    Particles(float x, float y, float theta,
              float steering_noise, float distance_noise, float measurement_noise, int N = 100);
    // extract position from a particle set
    void get_position(float &x, float &y, float &orientation);
    // motion of particles
    void move(World &world, float steer, float speed);
    // sensing and resampling
    void sense(vector<float>Z);
};


#endif
