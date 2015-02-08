#include "world.h"


World::World(){
  drawMowedLawn = true;
  memset(lawnMowStatus, 0, sizeof lawnMowStatus);
  imgBfield = Mat(WORLD_SIZE_Y, WORLD_SIZE_X, CV_8UC3, Scalar(0,0,0));
  imgWorld = Mat(WORLD_SIZE_Y, WORLD_SIZE_X, CV_8UC3, Scalar(0,0,0));

  // perimeter lines coordinates (1/10 meter)
  std::vector<point_t> list;
  list.push_back( (point_t) {30, 35 } );
  list.push_back( (point_t) {400, 40 } );
  list.push_back( (point_t) {410, 110 } );
  list.push_back( (point_t) {210, 250 } );
  list.push_back( (point_t) {50, 310 } );

  // compute magnetic field (compute distance to perimeter lines)
  int x1 = list[list.size()-1].x;
  int y1 = list[list.size()-1].y;
  // for each perimeter line
  for (int i=0; i < list.size(); i++){
    int x2 = list[i].x;
    int y2 = list[i].y;
    int dx = (x2-x1);
    int dy = (y2-y1);
    int len=(sqrt( dx*dx + dy*dy )); // line length
    float phi = atan2(dy,dx); // line angle
    // compute magnetic field for points (x,y) around perimeter line
    for (int y=-200; y < 200; y++){
      for (int x=-100; x < len*2+100-1; x++){
        int px= x1 + cos(phi)*x/2 - sin(phi)*y;
        int py= y1 + sin(phi)*x/2 + cos(phi)*y;
        int xend = max(0, min(len, x/2)); // restrict to line ends
        int cx = x1 + cos(phi)*xend;  // cx on line
        int cy = y1 + sin(phi)*xend;  // cy on line
        if ((py >= 0) && (py < WORLD_SIZE_Y)
           && (px >=0) && (px < WORLD_SIZE_X)) {
          float r = max(0.000001, sqrt( (cx-px)*(cx-px) + (cy-py)*(cy-py) ) ) / 10; // distance to line (meter)
          float b=100.0/(2.0*M_PI*r); // field strength
          if ((y<=0) || (bfield[py][px] < 0)){
            b=b*-1.0;
            bfield[py][px] =  min(bfield[py][px], b);
          } else bfield[py][px] = max(bfield[py][px], b);
        }
      }
    }
    x1=x2;
    y1=y2;
  }

  // draw magnetic field onto image
  for (int y=0; y < WORLD_SIZE_Y; y++){
    for (int x=0; x < WORLD_SIZE_X; x++) {
      float b=30 + 30*sqrt( abs(getBfield(x,y)) );
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
      imgBfield.at<Vec3b>(y, x) = intensity;
    }
  }
}

float World::getBfield(int x, int y){
  float res = 0;
  if ((x >= 0) && (x < WORLD_SIZE_X) && (y >= 0) && (y < WORLD_SIZE_Y)){
    res = bfield[y][x];
  }
  //float measurement_noise = 0.5;
  //res += gauss(0.0, measurement_noise);
  return res;
}

void World::draw(){
  char buf[64];
  sprintf(buf, " (%dm x %dm)", WORLD_SIZE_X/10, WORLD_SIZE_Y/10);
  imshow("world " + std::string(buf), imgWorld);
  imgBfield.copyTo(imgWorld);
  // draw lawn mowed status
  if (drawMowedLawn){
    Vec3b intensity;
    intensity.val[0]=0;
    intensity.val[1]=255;
    intensity.val[2]=0;
    for (int y=0; y < WORLD_SIZE_Y; y++){
      for (int x=0; x < WORLD_SIZE_X; x++){
        if (lawnMowStatus[y][x] > 0) imgWorld.at<Vec3b>(y, x) = intensity;
      }
    }
  }
}

// approximate circle pattern
// 010
// 111
// 010
void World::setLawnMowed(int x, int y){
  if (  (x <= 5) || (x >= WORLD_SIZE_X-5 ) || (y <= 5) || (y >= WORLD_SIZE_Y-5 )  )return;
  for (int i=-2; i <= 2; i++){
    for (int j=-2; j <= 2; j++){
      lawnMowStatus[y+i][x+j] = 1.0;
    }
  }
}

