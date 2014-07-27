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
 * $Author: sioulseuguh $ $Date: 2005/08/07 12:24:55 $ $Revision: 1.7 $ $Source: /cvsroot/simbad/src/simbad/demo/AvoidersDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import simbad.sim.Agent;
import simbad.sim.Arch;
import simbad.sim.Box;
import simbad.sim.RangeSensorBelt;
import simbad.sim.RobotFactory;
import simbad.sim.Wall;

/** A collision avoidance demo.
 * This demo shows several robot with sonars 
 * and bumpers performing a collision avoidance behavior*/ 
public class AvoidersDemo extends Demo {

    public class Robot extends Agent {

        RangeSensorBelt sonars, bumpers;

        public Robot(Vector3d position, String name) {
            super(position, name);
            // Add sensors
            bumpers = RobotFactory.addBumperBeltSensor(this);
            sonars = RobotFactory.addSonarBeltSensor(this,24);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
        // nothing particular in this case
        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
            
            if (bumpers.oneHasHit()) {
                setTranslationalVelocity(-0.1);
                setRotationalVelocity(0.1 * Math.random());

            } else {
                // Front left obstacle ?
                if (sonars.hasHit(0) && (sonars.hasHit(1))) {
                    setRotationalVelocity(-Math.PI / 4);
                    setTranslationalVelocity(0.1);
                }
                // Front right obstacle ?
                else if (sonars.hasHit(0) && (sonars.hasHit(23))) {
                    setRotationalVelocity(Math.PI / 4);
                    setTranslationalVelocity(0.1);
                }
                // left obstacle ?
                else if (sonars.hasHit(3) || sonars.hasHit(4)) {
                    setRotationalVelocity(-Math.PI / 8);
                    setTranslationalVelocity(0.1);
                }
                // right obstacle ?
                else if (sonars.hasHit(21) || sonars.hasHit(20)) {
                    setRotationalVelocity(Math.PI / 8);
                    setTranslationalVelocity(0.1);
                } else if ((getCounter() % 100) == 0) {
                    setRotationalVelocity(Math.PI / 2 * (0.5 - Math.random()));
                    setTranslationalVelocity(0.5);
                }
            }
        }
    }

    public AvoidersDemo() {
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
        add(new Robot(new Vector3d(0, 0, 0), "avoider1"));
        add(new Robot(new Vector3d(1, 0, 1), "avoider2"));
        add(new Robot(new Vector3d(2, 0, 2), "avoider3"));
        add(new Robot(new Vector3d(3, 0, 3), "avoider4"));
    
    }
}