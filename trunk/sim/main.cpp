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
#include "sim.h"

using namespace std;
using namespace cv;



int main()
{
	Sim sim;

	//namedWindow( "Robot mower simulator");
	//imshow("bfield", imgBfield);

	printf("press...\n");
	printf("l   - toggle mowed lawn drawing\n");
	printf("ESC - exit\n");

	while( 1 ){
		// Exit on esc key
		char key = cvWaitKey( 10 );
		switch (key){
		  case 27: return 0;
		  case 'l': sim.world.drawMowedLawn = !sim.world.drawMowedLawn;
		}
		sim.step();
        sim.draw();
	}

	return 0;
}

