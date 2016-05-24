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


#ifndef SIM_H
#define SIM_H

#include <vector>
#include <opencv2/core/core.hpp>



// simulation
class Simulator
{
  public:
    int plotIdx;
    cv::Mat imgBfieldRobot;
    float simTime; // seconds
    float timeStep; // seconds
    int stepCounter;
    Simulator();
    void step();
    void draw();
    void plotXY(cv::Mat &image, int x, int y, int r, int g, int b, bool clearplot);
};


extern Simulator Sim;

#endif


