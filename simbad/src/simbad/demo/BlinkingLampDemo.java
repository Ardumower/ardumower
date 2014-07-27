/*
 * Simbad - Robot Simulator Copyright (C) 2004 Louis Hugues
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * -----------------------------------------------------------------------------
 * $Author: sioulseuguh $ 
 * $Date: 2005/03/17 17:55:54 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/BlinkingLampDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import simbad.sim.Agent;
import simbad.sim.Arch;
import simbad.sim.Box;
import simbad.sim.LampActuator;
import simbad.sim.RangeSensorBelt;
import simbad.sim.RobotFactory;
import simbad.sim.Wall;
/** A Lamp actuator demo. The lamp blinks when the robot is approaching an obstacle. 
 * The lamp is on when the robot is avoiding an obstacle.
 * The demo also demonstrates the use of quadrants  reading for sonar belt.
 * */
public class BlinkingLampDemo extends Demo {

    public class Robot extends Agent {

        RangeSensorBelt sonars;
        LampActuator lamp;

        public Robot(Vector3d position, String name) {
            super(position, name);
            sonars = RobotFactory.addSonarBeltSensor(this,6);
            lamp = RobotFactory.addLamp(this);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {}

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
            // turn lamp On or Off depending on sonars
            lamp.setBlink(false);
            lamp.setOn(false);
            if (sonars.oneHasHit()) {
                lamp.setBlink(true);
                // reads the three front quadrants
                double left = sonars.getFrontLeftQuadrantMeasurement();
                double right = sonars.getFrontRightQuadrantMeasurement();
                double front = sonars.getFrontQuadrantMeasurement();
                // if obstacle near
                if ((front  < 1)||(left  < 1)||(right  < 1)) {
                    lamp.setBlink(false);
                    lamp.setOn(true);
                    if (left < right)
                        setRotationalVelocity(-1);
                    else
                        setRotationalVelocity(1);
                    setTranslationalVelocity(0.1);
                    
                } else{
                    setRotationalVelocity(0);
                    setTranslationalVelocity(0.3);
                }
            } else if (collisionDetected()) {
              
                lamp.setOn(true);
            } else {
                setTranslationalVelocity(0.8);
                setRotationalVelocity(0);
            }
        }
    }

    public BlinkingLampDemo() {

        Wall w1 = new Wall(new Vector3d(9, 0, 0), 19, 1, this);
        w1.rotate90(1);
        add(w1);
        Wall w2 = new Wall(new Vector3d(-9, 0, 0), 19, 2, this);
        w2.rotate90(1);
        add(w2);
        Wall w3 = new Wall(new Vector3d(0, 0, 9), 19, 1, this);
        add(w3);
        Wall w4 = new Wall(new Vector3d(0, 0, -9), 19, 2, this);
        add(w4);
        Box b1 = new Box(new Vector3d(-3, 0, -3), new Vector3f(1, 1, 2), this);
        add(b1);
        Arch a1 = new Arch(new Vector3d(3, 0, -3), this);
        add(a1);
   
    //    add(new Robot(new Vector3d(-3, 0, 4), "blinker"));
        add(new Robot(new Vector3d(0, 0, 4), "blinker"));
        add(new Robot(new Vector3d(3, 0, 4), "blinker"));
              
    
    }
}