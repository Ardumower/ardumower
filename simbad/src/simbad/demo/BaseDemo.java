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
 * $Date: 2005/03/17 17:55:54 $ $Revision: 1.6 $ $Source: /cvsroot/simbad/src/simbad/demo/BaseDemo.java,v $
 */
package simbad.demo;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import simbad.sim.*;
/** A Basic demo with camera sensor, sonars and bumpers.
 * The robot wanders and stops when it collides.
 *
 */
public class BaseDemo extends Demo {

    public class Robot extends Agent {
        RangeSensorBelt sonars;
        CameraSensor camera;
        public Robot (Vector3d position, String name) {     
            super(position,name);
            // Add sensors
            camera = RobotFactory.addCameraSensor(this);
            RobotFactory.addBumperBeltSensor(this);
           // Add sonars and get corresponding object.
           sonars  = RobotFactory.addSonarBeltSensor(this);
          
        }
        
        /** Initialize Agent's Behavior*/
        public void initBehavior() {
            // nothing particular in this case
        }
        
        /** Perform one step of Agent's Behavior */
        public void performBehavior() {

          
                // progress at 0.5 m/s
                setTranslationalVelocity(0.5);
                // frequently change orientation 
                if ((getCounter() % 100)==0) setRotationalVelocity(Math.PI/2 * (0.5 - Math.random()));
            
            // print front sonar every 100 frames
            if(getCounter() %100==0)
                System.out.println("Sonar num 0  = "+sonars.getMeasurement(0));
           
        }
    }
    public BaseDemo() {
        light1IsOn = true;
        light2IsOn = false;
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
        Box b1 = new Box(new Vector3d(-3, 0, -3), new Vector3f(1, 1, 1), this);
        add(b1);
        add( new Arch(new Vector3d(3, 0, -3), this));
        add(new Robot(new Vector3d(0, 0, 0), "robot 1"));
       
    }
}