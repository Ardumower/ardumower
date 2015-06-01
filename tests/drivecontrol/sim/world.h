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
#define WORLD_H

#include "../common.h"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>




// world size (cm)
#define WORLD_SIZE_X 500
#define WORLD_SIZE_Y 350


// world (perimeter wire etc.)
class SimWorld
{
    // magnetic field
    float bfield[WORLD_SIZE_Y][WORLD_SIZE_X];
    // lawn mow status
    float lawnMowStatus[WORLD_SIZE_Y][WORLD_SIZE_X];
    int pnpoly(std::vector<point_t> &vertices, float testx, float testy);
  public:
    int chgStationX, chgStationY; // cm
    cv::Mat imgBfield;
    cv::Mat imgWorld;
    bool drawMowedLawn;
    SimWorld();
    // return world size (cm)
    int sizeX(){ return WORLD_SIZE_X; };
    int sizeY(){ return WORLD_SIZE_Y; };
    // return magnetic field strength at world position
    float getBfield(int x, int y, int resolution=1);
    void setLawnMowed(int x, int y);
    void draw();
};

extern SimWorld World;

#endif
