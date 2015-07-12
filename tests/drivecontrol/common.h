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

#ifndef COMMON_H
#define COMMON_H


using namespace std;


struct point_t {
  float x;
  float y;
};

typedef struct point_t point_t;


float random();
float gaussRandom();
float gauss(float mean, float std_dev);
float gaussian(float mu, float sigma, float x);
float distance(float x1, float y1, float x2, float y2);
float scalePI(float v);
float distancePI(float x, float w);



#endif
