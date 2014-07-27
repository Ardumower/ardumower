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
 * $Source: /cvsroot/simbad/src/simbad/sim/KinematicModel.java,v $
 */

package simbad.sim;

import java.text.DecimalFormat;
import javax.media.j3d.Transform3D;
import javax.vecmath.Vector3d;


/**
 * This is the base class for all agent's kinematic.
 * A Kinematic performs the translation and rotation of the agent under the control of specific parameter.
 * 
 */
public abstract class KinematicModel {
    


    /** Compute instant translation and rotation vectors .
     * 
     * @param elapsedSecond time elapsed
     * @param rotation current rotation
     * @param instantTranslation to store translation
     * @param instantRotation to store rotation
     */ 
    protected abstract void   update(double elapsedSecond,Transform3D rotation,Vector3d instantTranslation,Vector3d instantRotation);

    
   /** Resets all control parameters to their initial values. */       
   protected abstract void reset();

    
   /** Returns string representation of the kinematicModel */       
    protected abstract String toString(DecimalFormat format);
}
