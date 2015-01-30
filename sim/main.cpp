/*
  Ardumower (www.ardumower.de)

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
*/


#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
using namespace cv;


// states
enum {
  STATE_FORW,
  STATE_REV,
  STATE_ROLL,
};

struct point_t {
  int x;
  int y;
};

typedef struct point_t point_t;

// world size
#define SIZE_X 500
#define SIZE_Y 350

// magnetic field
float bfield[SIZE_Y][SIZE_X] = {0};
Mat bfieldImg(SIZE_Y, SIZE_X, CV_8UC3, Scalar(0,0,0));
Mat worldImg(SIZE_Y, SIZE_X, CV_8UC3, Scalar(0,0,0));

// robot state
float dir; // direction (rad)
float speed;
point_t realpos = (point_t){ 50, 50 }; // real position
int state = STATE_FORW;
float stateTime = 0;


void createMagneticField(){
  std::vector<point_t> list;
  list.push_back( (point_t) {30, 35 } );
  list.push_back( (point_t) {400, 40 } );
  list.push_back( (point_t) {410, 110 } );
  list.push_back( (point_t) {210, 250 } );
  list.push_back( (point_t) {50, 310 } );

  int x1 = list[list.size()-1].x;
  int y1 = list[list.size()-1].y;
  for (int i=0; i < list.size(); i++){
    int x2 = list[i].x;
    int y2 = list[i].y;
    int dx = (x2-x1);
    int dy = (y2-y1);
    int len=(sqrt( dx*dx + dy*dy ));
    float phi = atan2(dy,dx);
    for (int y=-200; y < 200; y++){
      for (int x=-100; x < len*2+100-1; x++){
        int px= x1 + cos(phi)*x/2 - sin(phi)*y;
        int py= y1 + sin(phi)*x/2 + cos(phi)*y;
        int xend = max(0, min(len, x/2));
        int cx = x1 + cos(phi)*xend;
        int cy = y1 + sin(phi)*xend;
        if ((py >= 0) && (py < SIZE_Y)
           && (px >=0) && (px < SIZE_X)) {
          float r = max(0.000001, sqrt( (cx-px)*(cx-px) + (cy-py)*(cy-py) ) );
          float b=1000/(2*M_PI*r);
          if ((y<=0) || (bfield[py][px] < 0)){
            b=b*-1;
            bfield[py][px] =  min(bfield[py][px], b);
          } else bfield[py][px] = max(bfield[py][px], b);
        }
      }
    }
    x1=x2;
    y1=y2;
  }

  for (int y=0; y < SIZE_Y; y++){
    for (int x=0; x < SIZE_X; x++) {
      float b=30 + 30*sqrt( abs(bfield[y][x]));
      //b:=10 + bfield[y][x];
      int v = min(255, max(0, (int)b));
      Vec3b intensity;
      if (bfield[y][x] > 0){
        intensity.val[0]=255-v;
        intensity.val[1]=255-v;
        intensity.val[2]=255;
      } else {
        intensity.val[0]=255;
        intensity.val[1]=255-v;
        intensity.val[2]=255-v;
      }
      bfieldImg.at<Vec3b>(y, x) = intensity;
    }
  }
}

/*void drawLine(cx: integer; cy: integer; phi: real;
    x1: integer; y1: integer;
    x2: integer; y2: integer);
var
  px,py: integer;
begin
  px:= round(cx + cos(phi)*x1 - sin(phi)*y1);
  py:= round(cy + sin(phi)*x1 + cos(phi)*y1);
  canvas.moveto(px, py);
  px:= round(cx + cos(phi)*x2 - sin(phi)*y2);
  py:= round(cy + sin(phi)*x2 + cos(phi)*y2);
  canvas.lineto(px, py );
end;*/


void simulationStep(){
  float dt=0.04;
  switch (state) {
    case STATE_FORW: speed = 40; break;
    case STATE_REV:
           speed = -40;
           if (stateTime > 0.5){
             state=STATE_ROLL;
             stateTime=0;
           }
           break;
    case STATE_ROLL:
            speed=40;
            dir += M_PI/8;
            if (dir > 2*M_PI) dir -= 2*M_PI;
            if (dir < -2*M_PI) dir += 2*M_PI;
            if (stateTime > 0.7){
              state=STATE_FORW;
              stateTime=0;
            }
            break;
  }
  realpos.x +=  cos(dir) * speed * dt ;
  realpos.y +=  sin(dir) * speed * dt ;

  if ((realpos.y >= 0) && (realpos.y < SIZE_Y)
     && (realpos.x >=0) && (realpos.x < SIZE_X) ) {
    float b=max(-2.0f, min(15.0f, bfield[realpos.y][realpos.x]));
    if (b < 0){
      state=STATE_REV;
      stateTime=0;
    }
  }
  stateTime += dt;

  bfieldImg.copyTo(worldImg);
  circle( worldImg, Point( realpos.x, realpos.y ), 10.0, Scalar( 255, 255, 255 ), -1, 8 );
  //paintbox1.canvas.ellipse(realpos.x-10,realpos.y-10,realpos.x+10,realpos.y+10);
  //  drawLine(paintbox1.canvas, realpos.x, realpos.y, dir, -15, -10, 5,-10);
  //drawLine(paintbox1.canvas, realpos.x, realpos.y, dir, -15,  10, 5, 10);
  imshow("world", worldImg);
}


int main()
{
	createMagneticField();
	// Initialize Kalman filter object, window, number generator, etc
	namedWindow( "Robot mower simulator");
	//imshow("bfield", bfieldImg);
	imshow("world", worldImg);

	while( 1 ){
		// Exit on esc key
		if( cvWaitKey( 10 ) == 27 )
			break;
        simulationStep();
	}

	return 0;
}

