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
 * $Date: 2005/08/07 12:24:57 $
 * $Revision: 1.2 $
 * $Source: /cvsroot/simbad/src/simbad/sim/BlockWorldCompositeObject.java,v $
 */

package simbad.sim;

import java.util.ArrayList;


import javax.media.j3d.BoundingSphere;


/**
 * Base classt for all composite  block world objects (arch...).
 */
public class BlockWorldCompositeObject extends BlockWorldObject {
    /** Keep list of all simple components .*/
    ArrayList components;
   
    BlockWorldCompositeObject(){
        components = new ArrayList();
    }
    
    
    /** Create and pre Compute the transformed bound of the objects. */
    protected void createTransformedBounds(){
        for (int i = 0; i< components.size();i++){
            BlockWorldObject bo = (BlockWorldObject) components.get(i);
            bo.createLocalToVworld();
            bo.createTransformedBounds();
        }
         
    }

    /**  Returns true if the object intersect with the given bounding sphere. 
     * This can be overriden.
     * @param bs the boundingsphere to intersect with.*/
    protected boolean intersect(BoundingSphere bs){
        // If any component intersect
        for (int i = 0; i< components.size();i++){
            if (((BlockWorldObject) components.get(i)).intersect(bs))
                return true;
        }
        return false ;
    }
    
    protected void addComponent(BlockWorldObject o){
        components.add(o);
        addChild(o);
    }
}
