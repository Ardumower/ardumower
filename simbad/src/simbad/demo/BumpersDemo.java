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
 *  $Date: 2005/08/07 12:24:56 $
 *  $Revision: 1.4 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/BumpersDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3f;
import simbad.sim.Agent;
import simbad.sim.Box;
import simbad.sim.RangeSensorBelt;
import simbad.sim.RobotFactory;


/** A Bumping  demo.
*/
public class BumpersDemo extends Demo {

    public class Robot extends Agent {

        RangeSensorBelt  bumpers;
        int backcount;
        public Robot(Vector3d position, String name) {
            super(position, name);
            // Add sensors
            bumpers = RobotFactory.addBumperBeltSensor(this,16);
            backcount=0;
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
        // nothing particular in this case
        }

        int max(int a,int b){
            if (a> b) return a; else return b;
        }
        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
            backcount--;
            if (backcount <= 0) {
                if (collisionDetected()){
                    setTranslationalVelocity( (0.5 - Math.random()));
                    setRotationalVelocity( (0.5 - Math.random()));
                    backcount = 20;
                }
                else if (bumpers.oneHasHit()) {
                    int front =bumpers.getFrontQuadrantHits() ;
                    int left = bumpers.getLeftQuadrantHits() ;
                    int right = bumpers.getRightQuadrantHits() ;
                    int back = bumpers.getBackQuadrantHits();
                    int m = max (max(front,back),max(left,right));
                    
                    double r =0,t=0;
                    if (front == m){
                        r=1.5-Math.random()*3 ; t = -0.5;
                    } else if (left == m){
                        r=-1 ; t = 0;
                    } else if (right == m){
                        r=1 ; t = 0;
                    } else if (back == m){
                        r=1.5-Math.random()*3 ; t = 0.5;
                    }
                    setRotationalVelocity(r);
                    setTranslationalVelocity(t);
                    backcount = 20;
                } else if ((getCounter() % 10) == 0) {
                    setRotationalVelocity(Math.PI / 2 * (0.5 - Math.random()));
                    setTranslationalVelocity(0.5);
                }
            }
        }
    }

    public BumpersDemo() {
        setWorldSize(12);
        
        boxColor = new Color3f(0.6f,0.5f,.3f);

		add(new Box(new Vector3d(-5,0,0),new Vector3f(0.1f,1,10),this));
		add(new Box(new Vector3d(0,0,-5),new Vector3f(10,1,0.1f),this));
		add(new Box(new Vector3d(5,0,0),new Vector3f(0.1f,1,10),this));
		add(new Box(new Vector3d(0,0,5),new Vector3f(10,1,0.1f),this));
		add(new Box(new Vector3d(2,0,2),new Vector3f(2,1,3),this));
		add(new Box(new Vector3d(-2,0,-2),new Vector3f(3,1,2),this));
       
		add(new Robot(new Vector3d(4, 0, 4), "bump1"));
        add(new Robot(new Vector3d(4, 0, -4), "bump2"));
        add(new Robot(new Vector3d(-4, 0, 4), "bump3"));
        add(new Robot(new Vector3d(-4, 0, -4), "bump4"));
		
    
    }
}