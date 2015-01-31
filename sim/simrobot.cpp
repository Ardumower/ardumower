#include "simrobot.h"
#include "world.h"
#include "particles.h"
#include <exception>
#include <stdio.h>

using namespace std;


SimRobot::SimRobot(double length){
  state = STATE_FORW;
  stateTime = 0;
  speed = 0;
  plotIdx = 0;
  imgBfieldRobot = Mat(140, 500, CV_8UC3, Scalar(0,0,0));
}

void SimRobot::plotXY(Mat &image, int x, int y, int r, int g, int b, bool clearplot){
  if (clearplot) for (int y=0; y < image.rows; y++) image.at<Point3_<uchar> >(y, x) = Point3_<uchar>(0,0,0);
  if ( (x< 0) || (y < 0) || (x >= image.cols) || (y >= image.rows)) return;
  image.at<Point3_<uchar> >(image.rows-y-1, x) = Point3_<uchar>(r,g,b);
  //line( image, Point( x, image.rows ), Point( x, image.rows-y-1), Scalar( r, g, b),  1, 8 );
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

void SimRobot::run(World &world, float timeStep){
  switch (state) {
    case STATE_FORW: speed = 40; break;
    case STATE_REV:
           speed = -40;
           if (stateTime > 1.0){
             printf("ROLL\n");
             state=STATE_ROLL;
             stateTime=0;
           }
           break;
    case STATE_ROLL:
            speed=40;
            orientation += M_PI/32;
            if (orientation > 2*M_PI) orientation -= 2*M_PI;
            if (orientation < -2*M_PI) orientation += 2*M_PI;
            if (stateTime > 1.0){
              printf("FORW\n");
              state=STATE_FORW;
              stateTime=0;
            }
            break;
  }
  int px = (int)x;
  int py = (int)y;

  float b = max(-2.0f, min(30.0f, world.getBfield(px, py)));
  //printf("b=%3.4f\n", b);
  plotXY(imgBfieldRobot, plotIdx % imgBfieldRobot.cols, 15+b*5, 255,255,255, true);
  imshow("bfieldrobot", imgBfieldRobot);
  plotIdx++;
  if (b < 0){
    printf("REV\n");
    state=STATE_REV;
    stateTime=0;
  }
  stateTime += timeStep;
}

void SimRobot::draw(Mat &img){
  circle( img, Point( x, y), 10.0, Scalar( 255, 255, 255 ), -1, 8 );
}





