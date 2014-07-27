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
 *  $Date: 2005/04/25 17:58:17 $
 *  $Revision: 1.2 $ 
 * $Source: /cvsroot/simbad/src/simbad/demo/PushBallsDemo.java,v $
 */
package simbad.demo;

import javax.vecmath.Vector3d;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3f;
import simbad.sim.*;

/** Shows a robot pushing balls.
 * This demo shows simple physical interactions between agents.
*/
public class PushBallsDemo extends Demo {

    public class Robot extends Agent {

        
            public Robot(Vector3d position, String name) {
                super(position, name);
                //RobotFactory.addCameraSensor(this);
            }

            /** Initialize Agent's Behavior */
            public void initBehavior() {
                setTranslationalVelocity(0.5);
            }

            public void contactWith(SimpleAgent a){
              //  System.out.println(getName()+" interacts with "+a.getName());
            }
            /** Perform one step of Agent's Behavior */
            public void performBehavior() {
               // if (collisionDetected()&& (! interactionDetected()))
               //     moveToStartPosition();
                if ((getCounter() % 80) == 0) {
                    setRotationalVelocity(Math.PI / 2 * (0.5 - Math.random()));
                    setTranslationalVelocity(0.5);
                }
                
            }
        }

        public PushBallsDemo() {
            showAxis(false);
            setUsePhysics(true);
            setWorldSize(12);
            boxColor = new Color3f(0.6f,0.5f,.3f);

    		add(new Box(new Vector3d(-5,0,0),new Vector3f(0.1f,1,10),this));
    		add(new Box(new Vector3d(0,0,-5),new Vector3f(10,1,0.1f),this));
    		add(new Box(new Vector3d(5,0,0),new Vector3f(0.1f,1,10),this));
    		add(new Box(new Vector3d(0,0,5),new Vector3f(10,1,0.1f),this));
    		
            add(new Robot(new Vector3d(0, 0, 0), "Maradonna"));
            // Set up the ball agents
           int n = 1;
            
            Color3f c ;
            for (int x = -n; x <= n; x++) {
                for (int z = -n; z <= n; z++) {
                    if (!((x == 0) && (z == 0))) {
                        c =  new Color3f(x/(float)n, 0.3f, z/(float)n);
                        add(new BallAgent(new Vector3d(x, 0, z), "ball", c,0.25f,0.25f));
                    }
                }
            }
            
        }
}