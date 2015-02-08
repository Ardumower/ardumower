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

#ifndef WORLD_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>


using namespace std;
using namespace cv;

// world size (1/10 meter)
#define SIZE_X 500
#define SIZE_Y 350

struct point_t {
  float x;
  float y;
};

typedef struct point_t point_t;


// world (perimeter wire etc.)
class World
{
    // magnetic field
    float bfield[SIZE_Y][SIZE_X];
    // lawn mow status
    float lawnMowStatus[SIZE_Y][SIZE_X];
  public:
    Mat imgBfield;
    Mat imgWorld;
    bool drawMowedLawn;
    World();
    // return world size (1/10 meter)
    int sizeX(){ return SIZE_X; };
    int sizeY(){ return SIZE_Y; };
    // return magnetic field strength at world position
    float getBfield(int x, int y);
    void setLawnMowed(int x, int y);
    void draw();
};



#endif
