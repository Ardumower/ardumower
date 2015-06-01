#include "sim.h"
#include <ctime>
#include "simrobot.h"
#include "world.h"


Simulator Sim;

// simulation initialization
Simulator::Simulator(){
  stepCounter = 0;
  plotIdx = 0;
  imgBfieldRobot = cv::Mat(140, 500, CV_8UC3, cv::Scalar(0,0,0));
  timeStep = 0.01; // one simulation step (seconds)
  simTime = 0;
  // start random generator
  time_t t;
  time(&t);
  srand((unsigned int)t);
  // place robot onto world
  Robot.orientation = 0;
  Robot.x = World.chgStationX+5; //+ 10;
  Robot.y = World.chgStationY-5; // + 10;
  //robot.x = 100;
  //robot.y = 100;
  float steering_noise    = 0.01;
  float distance_noise    = 0.2;
  float measurement_noise = 0.5;
  Robot.set_noise(steering_noise, distance_noise, measurement_noise);
}


// simulation step
void Simulator::step(){
  //printf("stateTime=%1.4f\n", stateTime);

  // simulate robot movement
  Robot.move(0, 0);
  //filter.move(*this, robot.orientation, robot.speed*10 * timeStep);
  World.setLawnMowed(Robot.x, Robot.y);

  Robot.sense();
  //filter.sense(*this, robot.bfieldStrength);

  // run robot controller
  Robot.control(timeStep);

  // simulation time
  simTime += timeStep;

  if ((stepCounter % 100) == 0){
    printf("time=%5.1fs  orient=%3.1f  distChg=%3.1fm  totalDist=%3.1fm\n",
           simTime,
           Robot.orientation/M_PI*180.0,
           Robot.distanceToChgStation/10,
           Robot.totalDistance);
  }
  stepCounter++;
}


// draw world, robot, particles etc.
void Simulator::draw(){
  World.draw();

  float x,y,theta;
  //filter.get_position(x,y,theta);
  //filter.drawCenter(world.imgWorld, x,y,theta);

  Robot.draw(World.imgWorld);

  // plot robot bfield sensor
  //float bfieldStrength = max(-2.0f, min(24.0f, robot.bfieldStrength));
  //plotXY(imgBfieldRobot, plotIdx % imgBfieldRobot.cols, 15+bfieldStrength*5, 255,255,255, true);
  imshow("bfieldrobot", imgBfieldRobot);
  plotIdx++;
}


void Simulator::plotXY(cv::Mat &image, int x, int y, int r, int g, int b, bool clearplot){
  if (clearplot) for (int y=0; y < image.rows; y++) image.at<cv::Point3_<uchar> >(y, x) = cv::Point3_<uchar>(0,0,0);
  if ( (x< 0) || (y < 0) || (x >= image.cols) || (y >= image.rows)) return;
  image.at<cv::Point3_<uchar> >(image.rows-y-1, x) = cv::Point3_<uchar>(r,g,b);
  //line( image, Point( x, image.rows ), Point( x, image.rows-y-1), Scalar( r, g, b),  1, 8 );
}

