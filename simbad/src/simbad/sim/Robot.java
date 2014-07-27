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
 * $Author: sioulseuguh $ $Date: 2005/08/07 12:24:57 $ $Revision: 1.9 $ $Source:
 * /cvsroot/simbad/src/simbad/sim/Robot.java,v $
 */
package simbad.sim;


import javax.vecmath.Vector3d;

public class Robot extends Agent {

    
    Plan plan;

    public Robot(Vector3d position, String name) {
        super(position, name);
     // a square movement plan
        double deg90=Math.PI/2;
        plan = new Plan(this);
        plan.forward(3, 2);
        plan.turn(-deg90, 2);
        plan.forward(3, 2);
        plan.turn(-deg90, 2);
        plan.forward(3, 2);
        plan.turn(-deg90, 2);
        plan.forward(3, 2);
        plan.turn(-deg90, 2);
        plan.loop();
        
    }

    public void initBehavior() {
    //    plan.reset();
    }

    public void performBehavior() {
       if (collisionDetected()){
            // Change plan
        }
        plan.doStep();
       
    }
}