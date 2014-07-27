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
 * $Date: 2005/08/07 12:24:56 $
 * $Revision: 1.4 $
 * $Source: /cvsroot/simbad/src/simbad/demo/KheperaDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3f;
import simbad.sim.*;
/** A Khepera Robot demo.
 * 
 **/
public class KheperaDemo extends Demo {

    // derive from class KheperaRobot instead of class Agent 
    public class Robot extends KheperaRobot {
        public Robot(Vector3d position, String name) {
            super(position, name);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
           setWheelsVelocity(0.01,0.01);
            if (collisionDetected()) moveToStartPosition();
      }

    }

    public KheperaDemo() {
        setWorldSize(1f);
        boxColor = new Color3f(0.6f,0.5f,.3f);

			
        add(new Box(new Vector3d(0,0,-0.07),new Vector3f(0.10f,0.03f,0.055f),this));
		
		add(new Box(new Vector3d(0.2,0,0),new Vector3f(0.055f,0.1f,0.055f),this));
			

		// Add a robot.
        add(new Robot(new Vector3d(0, 0, 0),"khepera"));
        
    
    }
}