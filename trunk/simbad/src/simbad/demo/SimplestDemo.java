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
 * $Date: 2005/03/17 17:55:54 $ $Revision: 1.4 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/SimplestDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import simbad.sim.Agent;
import simbad.sim.Box;


/** This the simplest Demo. Robot has no sensors.
 * The robot progress until it reaches a box.
*
 */ 
public class SimplestDemo extends Demo {
    
    public class Robot extends Agent {
        
        public Robot(Vector3d position, String name) {
            super(position, name);
        }
        
        /** Initialize Agent's Behavior */
        public void initBehavior() {
            setTranslationalVelocity(1f);
        }
        
        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
 
        }
    }    
        public SimplestDemo() {
            add(new Box(new Vector3d(10, 0, 0), new Vector3f(3f, 3f, 3f), this));
            add(new Robot(new Vector3d(0, 0, 0), "robot"));
        }
    }