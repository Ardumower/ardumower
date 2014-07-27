/*
 * Created on 31 mars 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package simbad.demo;

import javax.vecmath.Color3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import simbad.sim.Agent;
import simbad.sim.CherryAgent;
import simbad.sim.Box;
import simbad.sim.SimpleAgent;

/**
 * This demo show a robot picking cherries. When touched, the cherries are either removed or repaint.
 */
public class PickCherriesDemo extends Demo {
    /** The robot used in the demo.*/
    public class Robot extends Agent {
      
        Color3f yellow = new Color3f(0.9f,0.7f,0.1f);
        public Robot(Vector3d position, String name) {
            super(position, name);
         
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
            setTranslationalVelocity(0.5);
        }

      
        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
            if (collisionDetected())
                moveToStartPosition();
            if ((getCounter() % 80) == 0) {
                setRotationalVelocity(Math.PI / 2 * (0.5 - Math.random()));
                setTranslationalVelocity(0.5);
            }
            // Test if there is an agent near . */
            if (anOtherAgentIsVeryNear()){
                SimpleAgent agent = getVeryNearAgent();
                
                if (agent instanceof CherryAgent){
                    // detach it from te scene graph so it is no more visible.
                    agent.detach();
                    System.out.println("cherry picked !");
                }
                // or  change the color of the agent.
                //   ((CherryAgent) agent).setColor(yellow);
                
            }
        }
    }

    public  PickCherriesDemo() {
        showAxis(false);
        setWorldSize(12);
        boxColor = new Color3f(0.6f,0.5f,.3f);
        // add the four walls 
        add(new Box(new Vector3d(-5,0,0),new Vector3f(0.1f,1,10),this,new Color3f(.8f,0.2f,0.2f)));
		add(new Box(new Vector3d(0,0,-5),new Vector3f(10,1,0.1f),this,new Color3f(0.2f,0.8f,0.2f)));
		add(new Box(new Vector3d(5,0,0),new Vector3f(0.1f,1,10),this,new Color3f(0f,0.2f,0.8f)));
		add(new Box(new Vector3d(0,0,5),new Vector3f(10,1,0.1f),this,new Color3f(0.2f,0.2f,0.8f)));
		
		// add the robot
        add(new Robot(new Vector3d(0, 0, 0), "R1"));
        
        // add cherries randomly .
        for( int n =0; n < 30;n++){
            double x =( Math.random()*10 - 5);
            double z = (Math.random()*10 - 5);
            add(new CherryAgent(new Vector3d(x, 0, z), "cherry", 0.15f));
        }
    }

}
