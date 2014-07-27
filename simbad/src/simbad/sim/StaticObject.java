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
 * $Date: 2005/04/25 17:54:59 $
 * $Revision: 1.2 $
 * $Source: /cvsroot/simbad/src/simbad/sim/StaticObject.java,v $
 */

package simbad.sim;

import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.Bounds;
import javax.media.j3d.Transform3D;

/**
 * Base Object for all block world objects (box,wall,arch ...).
 * All object which doesnt move. 
 */
public class StaticObject extends BaseObject {
    /** Transformed bounds is the bound object in global coordinates.   */
    protected Bounds transformedBounds;
    /** The local to global transform.*/
    protected Transform3D localToVworld; 
    
    /** Appearance of the object. */
    protected Appearance appearance;

    /** Create object's geometry. */
    void create3D(){
        super.create3D(false);
        appearance = new Appearance();
        compilable = true;
        localToVworld = new Transform3D();
    }
    
    /** Create and pre Compute the transformed bound of the objects.
     * Needs localtoVWorld. */
    protected void createTransformedBounds(){
        
        transformedBounds = (Bounds)(localBounds.clone());
        transformedBounds.transform(localBounds,localToVworld);
         
    }
    
    
    /** Gets the bound of the object taking account of its current position.*/
    protected Bounds getTransformedBounds(){
        return transformedBounds;
    }
    
    /** Create the definitive local to global transform .*/
    protected void createLocalToVworld(){
        group.getLocalToVworld(localToVworld);
    }
    
    /**  Returns true if the object intersect with the given bounding sphere. 
     * This can be overriden.
     * @param bs the boundingsphere to intersect with.*/
    protected boolean intersect(BoundingSphere bs){
        return transformedBounds.intersect(bs);
    }
}
