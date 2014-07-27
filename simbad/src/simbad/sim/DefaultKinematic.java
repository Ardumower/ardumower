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
 * $Date: 2005/03/17 17:49:37 $
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/sim/DefaultKinematic.java,v $
 */

package simbad.sim;

import java.text.DecimalFormat;
import javax.media.j3d.Transform3D;
import javax.vecmath.Vector3d;


/**
 * This is the standard kinematic with two control parameters : translation and rotation.
 * Each agent use this kinematic by default.
 */
public class DefaultKinematic extends KinematicModel {
    
  
    /** Translational velocity  in meters per second. */
    private double translationalVelocity;
    /** Rotational velocity  in radians per second */
    private double rotationalVelocity;
  
    
    DefaultKinematic(){
        reset();
    }
    
    /** Resets all control parameters to their initial values. */       
   protected void reset(){
        rotationalVelocity=0;
        translationalVelocity=0;
    }
   /** Compute instant translation and rotation vectors .
    * 
    * @param elapsedSecond time elapsed
    * @param rotation current rotation
    * @param instantTranslation to store translation
    * @param instantRotation to store rotation
    */ 

     protected void   update(double elapsedSecond,Transform3D rotation,Vector3d instantTranslation,Vector3d instantRotation) {
        
         
        instantTranslation.set(translationalVelocity * elapsedSecond, 0.0, 0.0);
        // apply current rotation (on y axis)
        rotation.transform(instantTranslation);
    
        // perform rotation - on y axis
        instantRotation.set(0,elapsedSecond * rotationalVelocity,0);
        
    }

    /**
     * Sets rotational velocity in radians per second.
     */
    public final void setRotationalVelocity(double rv) {
        rotationalVelocity = rv;
    }

    /**
     * Sets translational velocity in meter per second.
     */
    public final void setTranslationalVelocity(double tv) {
        translationalVelocity = tv;
    }
    
    
    /**
     * Gets rotational velocity in radians per second
     */
     public final double getRotationalVelocity() {
        return rotationalVelocity;
    }

     /**
      * Gets translational velocity in meter per second.
      */
    public final double getTranslationalVelocity() {
        return translationalVelocity;
    }
    
    
    /** Resets all control parameters to their initial values. */       
    protected String toString(DecimalFormat format){
    return "kinematic \t= DefaultKinematic\n" +
    "rotVelocity   \t= " + format.format(rotationalVelocity) + " rad/s\n" +
    "transVelocity \t= " + format.format(translationalVelocity) + " m/s\n";
    }
}
