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
 * $Date: 2005/01/27 22:08:44 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/DifferentialKinematicDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3f;
import simbad.sim.*;
/** A differential drive (two wheels) kinematic  demo. This demo demonstrates the usage of 
 * the DifferentialKinematic instead of the standard one.
 * 
 **/
public class DifferentialKinematicDemo extends Demo {

    public class Robot extends Agent {
        DifferentialKinematic kinematic;
        int state;
        public Robot(Vector3d position, String name) {
            super(position, name);
            // Change the  kinematic to differentialDrive 
           kinematic = RobotFactory.setDifferentialDriveKinematicModel(this);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
            state =0;
        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
           
            // here we do not use SetTranslationalVelocity and SetRotationalVelocity.
            // Instead we control directly the wheels velocity.
            // We need to use  the kinematic object to do so.
            
            if (getCounter()% 300==0){

                switch(state){
                
                // turn right
                	case 0:  kinematic.setWheelsVelocity(0.8,0.5);break;
                	// turn left
                	case 1:  kinematic.setWheelsVelocity(0.5,0.8);break;
                	
                	case 2:  kinematic.setWheelsVelocity(-0.8,0.5);break;
                	// on place
                	case 3:  kinematic.setWheelsVelocity(0.8,0);break;
                	// forward
                	case 4:  kinematic.setWheelsVelocity(0.1,0.1);break;
                   	// backward
                	case 5:  kinematic.setWheelsVelocity(-0.5,-0.5);state=-1;break;
                  	
                }
                state++;
            }
            
            if (collisionDetected()) moveToStartPosition();
      }

    }

    public DifferentialKinematicDemo() {
      boxColor = new Color3f(0.6f,0.5f,.3f);

		add(new Box(new Vector3d(-8,0,0),new Vector3f(0.1f,1,16),this));
		add(new Box(new Vector3d(0,0,-8),new Vector3f(16,1,0.1f),this));
		add(new Box(new Vector3d(8,0,0),new Vector3f(0.1f,1,16),this));
		add(new Box(new Vector3d(0,0,8),new Vector3f(16,1,0.1f),this));
		

		// Add a robot.
        add(new Robot(new Vector3d(0, 0, 0),"my robot"));
        
    
    }
}