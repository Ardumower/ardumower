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
 * $Date: 2005/03/17 17:55:54 $ $Revision: 1.3 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/SingleAvoiderDemo.java,v $
 */
package simbad.demo;

import javax.media.j3d.Transform3D;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3f;
import simbad.sim.Agent;
import simbad.sim.Box;
import simbad.sim.RangeSensorBelt;
import simbad.sim.RobotFactory;

/** A collision avoidance demo. */
public class SingleAvoiderDemo extends Demo {

    public class Robot extends Agent {
        Point3d coords = new Point3d();
        Point3d prev = new Point3d();
        Transform3D t3d = new Transform3D();

        RangeSensorBelt sonars, bumpers;

        boolean stop = false;

        public Robot(Vector3d position, String name) {
            super(position, name);
            // Add sensors
            bumpers = RobotFactory.addBumperBeltSensor(this, 12);
            sonars = RobotFactory.addSonarBeltSensor(this, 12);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
            // nothing particular in this case
        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {

            if (!stop) {
                if (bumpers.oneHasHit()) {
                    setTranslationalVelocity(-0.1);
                    setRotationalVelocity(0.5 - (0.1 * Math.random()));

                } else if (sonars.oneHasHit()) {
                    // reads the three front quadrants
                    double left = sonars.getFrontLeftQuadrantMeasurement();
                    double right = sonars.getFrontRightQuadrantMeasurement();
                    double front = sonars.getFrontQuadrantMeasurement();
                    // if obstacle near
                    if ((front < 0.7) || (left < 0.7) || (right < 0.7)) {
                        if (left < right)
                            setRotationalVelocity(-1 - (0.1 * Math.random()));
                        else
                            setRotationalVelocity(1 - (0.1 * Math.random()));
                        setTranslationalVelocity(0);

                    } else {
                        setRotationalVelocity(0);
                        setTranslationalVelocity(0.6);
                    }
                } else {
                    setTranslationalVelocity(0.8);
                    setRotationalVelocity(0);
                }
            }
            prev.set(coords);
            getCoords(coords);
            if ((coords.x < -5.1) || (coords.x > 5.1) || (coords.z < -5.1)
                    || (coords.z > 5.1)) {
              //  stop = true;
                System.out.println(coords.toString() + "prev-->" +prev.toString());
                getTranslationTransform(t3d);
                System.out.println("scale :"+t3d.getScale());
                this.moveToStartPosition();
            }
        
        }
        

    }

    public SingleAvoiderDemo() {
        setUsePhysics(false);
        boxColor = new Color3f(0.6f, 0.5f, .3f);

        setWorldSize(12);
        add(new Box(new Vector3d(-5, 0, 0), new Vector3f(0.1f, 1, 10), this));
        add(new Box(new Vector3d(0, 0, -5), new Vector3f(10, 1, 0.1f), this));
        add(new Box(new Vector3d(5, 0, 0), new Vector3f(0.1f, 1, 10), this));
        add(new Box(new Vector3d(0, 0, 5), new Vector3f(10, 1, 0.1f), this));
        add(new Box(new Vector3d(0, 0, 0), new Vector3f(6, 1, 6), this));

        // Add a robot.
        add(new Robot(new Vector3d(4, 0, 4), "my robot"));

    }
}