
#include <iostream>
#include <vector>
#include <stdio.h>
#include "sim.h"
#include "simrobot.h"
#include "world.h"
#include "../config.h"



// Sim     -- simulator environment (simulation time step, speed etc.)
// World   -- simulator world (garden with perimeter loop etc.)
// Robot   -- simulator robot



int main()
{
	//MotorCtrl.setup();
	//Console.println("START");

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
            World.drawMowedLawn = !World.drawMowedLawn;
            printf("toggled draw mowed lawn\n");
		    break;
          case 's':
            Robot.x = Robot.y = 100;
            break;
		}
		Sim.step();
        Sim.draw();
	}

	return 0;
}

