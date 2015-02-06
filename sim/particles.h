#ifndef PARTICLES_H

#include <vector>
#include <opencv2/core/core.hpp>



//#include "robot.h"

using namespace cv;
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
    Particles();
    // creates particle set with given initial position
    void init(float x, float y, float theta,
              float steering_noise, float distance_noise, float measurement_noise, int N = 100);
    // extract position from a particle set
    void get_position(float &x, float &y, float &orientation);
    // motion of particles
    void move(World &world, float course, float speed);
    // sensing and resampling
    void sense(World &world, float measurement);
    void draw(Mat &img);
    void drawCenter(Mat &img, float x, float y, float theta);
};


#endif
