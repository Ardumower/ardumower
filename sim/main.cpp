/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  
  Private-use only! (you need to ask for a commercial-use)
 
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
  
  Private-use only! (you need to ask for a commercial-use)
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
	printf("+   - increase step wait\n");
	printf("-   - decrease step wait\n");
	printf("s   - skip tracking\n");
	printf("ESC - exit\n");

    int stepWait = 10;
	while( 1 ){
		// Exit on esc key
		char key = cvWaitKey( stepWait );
		switch (key){
		  case 27:
            return 0;
		  case '+':
            stepWait = min(20, stepWait +1);
            printf("stepWait=%d\n", stepWait);
		    break;
		  case '-':
            stepWait = max(5, stepWait -1);
            printf("stepWait=%d\n", stepWait);
		    break;
		  case 'l':
            sim.world.drawMowedLawn = !sim.world.drawMowedLawn;
            printf("toggled draw mowed lawn\n");
		    break;
          case 's':
            sim.robot.x = sim.robot.y = 100;
            sim.robot.state = STATE_LANE_FORW;
            break;
		}
		sim.step();
        sim.draw();
	}

	return 0;
}

