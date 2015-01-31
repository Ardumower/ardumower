#include "sim.h"
//#include "simrobot.h"
//#include "world.h"



Sim::Sim(){
  // place robot onto world
  robot.orientation = M_PI/8;
  robot.x = 50;
  robot.y = 50;
  time = 0;
}


void Sim::step(){
  float dt=0.04;
  //printf("stateTime=%1.4f\n", stateTime);

  // simulate robot movement
  //robot.move(world, robot.orientation, robot.speed);
  robot.x +=  cos(robot.orientation) * robot.speed * dt ;
  robot.y +=  sin(robot.orientation) * robot.speed * dt ;

  // run robot controller
  robot.run(world, dt);

  // simulation time
  time += dt;
}


void Sim::draw(){
  world.draw();
  robot.draw(world.imgWorld);
}

