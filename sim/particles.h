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
    double steering_noise;
    double distance_noise;
    double measurement_noise;
    vector <SimRobot>data; // particles
    // creates particle set with given initial position
    Particles(double x, double y, double theta,
              double steering_noise, double distance_noise, double measurement_noise, int N = 100);
    // extract position from a particle set
    void get_position(double &x, double &y, double &orientation);
    // motion of particles
    void move(World &world, double steer, double speed);
    // sensing and resampling
    void sense(vector<double>Z);
};


#endif
