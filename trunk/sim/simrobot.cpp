#include "simrobot.h"
#include "particles.h"
#include <exception>

using namespace std;


SimRobot::SimRobot(double length){
}


void SimRobot::set(double new_x, double new_y, double new_orientation){
}

void SimRobot::set_noise(double new_s_noise, double new_d_noise, double new_m_noise){
}

SimRobot SimRobot::move(World &world, double steering, double distance,
             double tolerance, double max_steering_angle){

}


double SimRobot::measurement_prob(vector <double>measurement){
}


void SimRobot::draw(Mat &img){
  circle( img, Point( x, y), 10.0, Scalar( 255, 255, 255 ), -1, 8 );
}





