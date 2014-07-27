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
 * $Author: sioulseuguh $ $Date: 2005/08/07 12:24:56 $ $Revision: 1.7 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/LightSearchDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import simbad.sim.*;

/**
 * This demo shows how to capture the camera image , process it and display it
 * in dedicated window.
 *  
 */
public class LightSearchDemo extends Demo {

    class Robot extends Agent {
        LightSensor sensorLeft;
        LightSensor sensorRight;

        public Robot(Vector3d position, String name) {
            super(position, name);
            sensorLeft = RobotFactory.addLightSensorLeft(this);
            sensorRight = RobotFactory.addLightSensorRight(this);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
         
                // progress at 0.5 m/s
                setTranslationalVelocity(0.5);
                // turn towards light
                float llum = sensorLeft.getAverageLuminance();
                float rlum = sensorRight.getAverageLuminance();
                //setRotationalVelocity((llum - rlum) *  Math.PI);
                setRotationalVelocity((llum - rlum) *  Math.PI/4);
                if (collisionDetected()) moveToStartPosition();
        }
    }

    public LightSearchDemo() {
        light1IsOn = true;
        light1SetPosition(6,.7f,5);
        light2IsOn = false;
         ambientLightColor = darkgray;
        light1Color = white;
        light2Color = white;
        wallColor = blue;
        archColor = green;
        boxColor = red;
        floorColor = white;
        backgroundColor = black;
        hasAxis = true;
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
        add(new Robot(new Vector3d(-3, 0, -5), "DemoRobot"));
        add(new Robot(new Vector3d(6, 0, -5), "DemoRobot"));
        add(new Robot(new Vector3d(-6, 0, -8), "DemoRobot"));
        add(new Robot(new Vector3d(-8, 0, -5), "DemoRobot"));
        add(new Robot(new Vector3d(-1, 0, -8), "DemoRobot"));
    }
}