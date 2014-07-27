/*
 *  Simbad - Robot Simulator
 *  Copyright (C) 2004 Louis Hugues
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 -----------------------------------------------------------------------------
 * $Author: sioulseuguh $ 
 * $Date: 2005/08/07 12:24:56 $
 * $Revision: 1.17 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Agent.java,v $
 * - AGent no more derived from CollidableObject
 */
package simbad.sim;

import java.text.DecimalFormat;
import javax.media.j3d.Appearance;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.media.j3d.Shape3D;
import javax.media.j3d.*;
import javax.swing.JInternalFrame;
import javax.swing.JPanel;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import simbad.gui.AgentInspector;
import com.sun.j3d.utils.geometry.*;



/**
 * This is the  base class for all robot and is considered to be a heavy agent. <br>
 * When deriving a new robot's class from this class, one should override the following methods:
 * <ul>
 * <li> initBehavior : called by the simulator to initialize the controler.</li> 
 * <li>  performBehavior : called by the simulator on each simulation step.</li> 
 * </ul>
 *  * Implementation note : the agent doesnt have synchronized methods.
 * All thread refering to the agent should do explicit synchronization with synchronized(agent){...}.
 * 
 */
public class Agent extends SimpleAgent {
    /** panel dedicated to behavior output - can be null. */
    private JPanel panel;
    /** window  dedicated to behavior output - can be null. */
    JInternalFrame window;
    /** Link back to agent inspector - can be null */
    AgentInspector agentInspector;

    /** Kinematic model used by the agent*/
    protected KinematicModel kinematicModel;
    /** Current linear acceleration applied by  motors. */
    protected Vector3d motorsLinearAcceleration = new Vector3d();
    
    /** Current angular acceleration applied by  motors..*/
    protected Vector3d motorsAngularAcceleration = new Vector3d();

   
    private DecimalFormat format; 
    /** Used for frame rate measure */
    protected FrameMeter frameMeter;
    


    /**
     * Constructs an Agent. 
     * @param pos start position in 3D world.
     * @param name name of the agent.
     */
    public Agent(Vector3d pos, String name) {
        super(pos, name);
        // No UI by default
        this.panel = null;
        agentInspector = null;
        // physical parameters default
        height = 0.5f;
        radius = 0.3f; 
        staticFrictionCoefficient = 0;
        mass = 50;

        
        // display format for numbers
        format = new DecimalFormat();
        format.setMaximumFractionDigits(3);
        format.setMinimumFractionDigits(3);
        format.setPositivePrefix("+");
        format.setMinimumIntegerDigits(1);
        
        // Attached a default kinematic
        kinematicModel = new DefaultKinematic();
        // Performance measure
        frameMeter = new FrameMeter();

    }
    
    /** Resets agent variables  */
    protected void reset(){
        super.reset();
        frameMeter.reset();

    }

    
    /** Resets agent variables and position and kinematic */
   protected void resetPosition(){
        super.resetPosition();
        kinematicModel.reset();
    }
    
    /** Create 3D geometry. */
    protected void create3D(){
  
        Color3f color = new Color3f(0.0f,0.8f,0.0f);
        Color3f color2 = new Color3f(1.0f,0.0f,0.0f);
        // body
        Appearance  appear = new Appearance();
        
        color.clampMax(0.8f);
        material.setDiffuseColor(color);
        
        material.setSpecularColor(black);
        appear.setMaterial(material);
        int flags = Primitive.GEOMETRY_NOT_SHARED | Primitive.ENABLE_GEOMETRY_PICKING | Primitive.GENERATE_NORMALS;
        flags |= Primitive.ENABLE_APPEARANCE_MODIFY;
      
        body = new Cylinder(radius,height,flags,appear);
        
       /* // allow geom intersect on each geom of the primitive cylinder
        allowIntersect(body.getShape(Cylinder.BODY));
        allowIntersect(body.getShape(Cylinder.TOP));*/
        // we must be able to change the pick flag of the agent 
        body.setCapability(Node.ALLOW_PICKABLE_READ);
        body.setCapability(Node.ALLOW_PICKABLE_WRITE);
        body.setPickable(true);
        body.setCollidable(true);
        addChild(body);
        
        // direction indicator
        float coords[]={
                radius/2,height,-radius/2,//
                radius/2,height,radius/2,//
                radius,height,0 //
        };
        float normals[]={
                0,1,0,
                0,1,0,
                0,1,0
        };
        TriangleArray tris = new TriangleArray( coords.length,
    	        GeometryArray.COORDINATES|GeometryArray.NORMALS);
        
        tris.setCoordinates( 0, coords );
        tris.setNormals( 0, normals );
	
	    appear = new Appearance();
	    appear.setMaterial(new Material(color2, black,
	                                  color2, white, 100.0f));

	    Shape3D s = new Shape3D(tris,appear);
	    s.setPickable(false);
	    addChild(s);
	    
	    // Add bounds for interactions and collision
	    Bounds bounds = new BoundingSphere(new Point3d(0,0,0),radius);
	    setBounds(bounds);
   
    }

    
    /** set acceleration applied by motors .*/
    protected  void setMotorsAcceleration(double dt) {
             
      
        // TODO  CHange this !!!
        linearVelocity.set(0,0,0);
        angularVelocity.set(0,0,0);
        
        
        kinematicModel
                .update(dt, rotation, instantTranslation, instantRotation);
        // derive two times  displacement to obtain acceleration
        double scale =  1.0 /(dt*dt);// dt non zero
        motorsLinearAcceleration.set(instantTranslation);
        motorsLinearAcceleration.scale(scale); 
        motorsAngularAcceleration.set(instantRotation);
        motorsAngularAcceleration.scale(scale); 

        
        // contribute to general acceleration
        linearAcceleration.set(motorsLinearAcceleration);
        angularAcceleration.set(motorsAngularAcceleration);
            
    }

    
     
    /** called by simulator. */
    protected void initPreBehavior() {
        // if there's a ui window show it
        if (window != null) window.toFront();
       }
    
    /** called by simulator. */
    protected void initBehavior() { }
 
 
    /** called by simulator. */
    protected void performPreBehavior() {
         frameMeter.measurePoint(1);
     }
  
    /** called by simulator. */
    protected void performBehavior() {}
    
    
    /**
     * Returns the agent's odometer in meters.
     * @return the agent odometer  in meters.
     */
    public double getOdometer(){
        return odometer;
    }
    
    /**
     * Sets rotational velocity in radians per second.
     */
    public final void setRotationalVelocity(double rv) {
        // because it's one of  the default kinematic fucntions we provide it  in the
        // agent's api.
        if (kinematicModel instanceof DefaultKinematic)
            ((DefaultKinematic)kinematicModel).setRotationalVelocity(rv);
    }

    
    /**
     * Sets translational velocity in meter per second.
     */
    public final void setTranslationalVelocity(double tv) {
        // because it's one of  the default kinematic fucntions we provide it  in the
        // agent's api.
        if (kinematicModel instanceof DefaultKinematic)
            ((DefaultKinematic)kinematicModel).setTranslationalVelocity(tv);
    }

    
    /**
     * Gets rotational velocity in radians per second
     */
     public final double getRotationalVelocity() {
         // because it's one of  the default kinematic fucntions we provide it  in the
         // agent's api.
         if (kinematicModel instanceof DefaultKinematic)
             return ((DefaultKinematic)kinematicModel).getRotationalVelocity();
         else return 0.0;
    }

     
     /**
      * Gets translational velocity in meter per second.
      */
    public final double getTranslationalVelocity() {
        // agent's api.
        if (kinematicModel instanceof DefaultKinematic)
            return ((DefaultKinematic)kinematicModel).getTranslationalVelocity();
        else return 0.0;     
    }


    
    /** Sets the kinematic model for this agent */
    protected void setKinematicModel(KinematicModel kinematicModel){
        this.kinematicModel = kinematicModel;
    }
    protected KinematicModel getKinematicModel(){
        return  kinematicModel;
    }
    
    protected void setFrameMeterRate(int rate){
        frameMeter.setUpdateRate(rate);
    }
    
    /**
     * Add a UI panel to the agent. Typically used for displaying behavior outputs.
     * A call to this method will have for consequence the creation of a dedicated window.
     * @param panel
     */
    public void setUIPanel(JPanel panel){
     this.panel = panel;   
    }
    
    /**
     * Returns the UI panel previously set with <code>setUIPanel</code>
     * @return the panel
     */
    public JPanel  getUIPanel(){
        return panel;   
       }
  
    
    /** Creates the UI that may be associated to the agent.
     * If the agent has set a Panel with setUIPanel a window is created containing the panel.
     *  */
    JInternalFrame createUIWindow(){
        JPanel panel = getUIPanel();
        if (panel!=null){
             window = new JInternalFrame("Output",false,false,false,false);
            window.setContentPane(panel);
            window.pack();
        }
        else window = null; 
        return window;
    }
    
    public AgentInspector getAgentInspector(){
        return agentInspector ;
    }
    public void setAgentInspector(AgentInspector ai){
        agentInspector = ai;
    }
    /** Dispose all resources */
    protected void dispose(){
        if (window != null) window.dispose();
    }
	 /**
	  * Returns printable description of the agent.
	 * @return agent description as string.
	 */
	public String asString(){
       
       String s = new String();
       Vector3d t = v1;
       translation.get(t);
       s= 
      "class = " + this.getClass().getName() + "\n" + 
      "name          \t= " + name + "\n" + 
      "fps instant   \t= " + format.format(frameMeter.fps) + "\n"+
      "fps total     \t= " +format.format(frameMeter.fpsSinceStart) +"\n" +
      "counter       \t= " + getCounter() + "\n" +
      "lifetime      \t= " + format.format(getLifeTime()) + " s\n" +
      "collision     \t= " + this.collisionDetected+ "\n" +
   //   "interaction   \t= " + this.interactionDetected+ "\n" +
           kinematicModel.toString(format) +
      "x             \t= " + format.format(t.x) + " m\n" +
      "y             \t= " + format.format(t.y) + " m\n" +
      "z             \t= " + format.format(t.z) + " m\n"+
      "odometer      \t= " + format.format(odometer) + " m\n";
          return s;
   }


    

}
