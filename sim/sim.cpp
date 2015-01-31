#include "sim.h"
//#include "simrobot.h"
//#include "world.h"



Sim::Sim(){
  state = STATE_FORW;
  stateTime = 0;
  speed = 0;
  robot.orientation = M_PI/8;
  robot.x = 50;
  robot.y = 50;
  plotIdx = 0;
  imgBfieldRobot = Mat(140, 500, CV_8UC3, Scalar(0,0,0));
}

void Sim::plotXY(Mat &image, int x, int y, int r, int g, int b, bool clearplot){
  if (clearplot) for (int y=0; y < image.rows; y++) image.at<Point3_<uchar> >(y, x) = Point3_<uchar>(0,0,0);
  if ( (x< 0) || (y < 0) || (x >= image.cols) || (y >= image.rows)) return;
  image.at<Point3_<uchar> >(image.rows-y-1, x) = Point3_<uchar>(r,g,b);
  //line( image, Point( x, image.rows ), Point( x, image.rows-y-1), Scalar( r, g, b),  1, 8 );
}


void Sim::step(){
  float dt=0.04;
  //printf("stateTime=%1.4f\n", stateTime);
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
            robot.orientation += M_PI/32;
            if (robot.orientation > 2*M_PI) robot.orientation -= 2*M_PI;
            if (robot.orientation < -2*M_PI) robot.orientation += 2*M_PI;
            if (stateTime > 1.0){
              printf("FORW\n");
              state=STATE_FORW;
              stateTime=0;
            }
            break;
  }
  robot.x +=  cos(robot.orientation) * speed * dt ;
  robot.y +=  sin(robot.orientation) * speed * dt ;

  int px = (int)robot.x;
  int py = (int)robot.y;

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
  stateTime += dt;
}


void Sim::draw(){
  world.draw();
  robot.draw(world.imgWorld);
}

