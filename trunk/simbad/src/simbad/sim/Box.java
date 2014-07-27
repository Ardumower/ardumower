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
 * 07/02/2005 - now use Box Primitive instead of QuadArray
 * $Author: sioulseuguh $ 
 * $Date: 2005/04/25 17:54:58 $
 * $Revision: 1.7 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Box.java,v $
 */
package simbad.sim;

import javax.media.j3d.*;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import com.sun.j3d.utils.geometry.Primitive;
/**
 * A box object which can be put in the environment. 
 * @author Louis Hugues
 */
public class Box extends BlockWorldObject {
    
    /** Object dimension.s */
    float sx,sy,sz;
     
    /** Constructs a box object.
     * 
     * @param pos position of the center of the object. 
     * @param extent - extent in the three directions.
     * @param wd	EnvironmentDescription for global parameters.
     */
    public Box(Vector3d pos,  Vector3f extent,EnvironmentDescription wd) {        
        this(pos,extent,wd,wd.boxColor);
    }
    
    /** Constructs a box object.
     * 
     * @param pos position of the center of the object. 
     * @param extent - extent in the three directions.
     * @param wd	EnvironmentDescription for global parameters.
     * @param color  color of the object.
     */
    public Box(Vector3d pos,  Vector3f extent,EnvironmentDescription wd, Color3f color) {        
        this.sx = extent.x;
        this.sy = extent.y;
        this.sz = extent.z;
        // put it on the floor
        pos.y += sy/2;
        create3D(wd,color);
        translateTo(pos);
    }
    /** Create the 3d object */
    protected void create3D(EnvironmentDescription wd,Color3f color){
        // create the box using a primitive
        super.create3D();
        Material mat = new Material();
        appearance.setMaterial(mat);
        
        int flags = Primitive.GEOMETRY_NOT_SHARED | Primitive.ENABLE_GEOMETRY_PICKING | Primitive.GENERATE_NORMALS;
        flags |= Primitive.ENABLE_APPEARANCE_MODIFY;
       // com.sun.j3d.utils.geometry.Box box =new com.sun.j3d.utils.geometry.Box(sx,sy,sz,flags,appearance,0);
        // bug in j3d api doc . must give half values.
        com.sun.j3d.utils.geometry.Box box =new com.sun.j3d.utils.geometry.Box(sx/2,sy/2,sz/2,flags,appearance,0);
         // Enable  sensor  detection 
        box.setPickable(true);
	    
        //  define the boundsfFor collision  detection
	    BoundingBox bounds = new BoundingBox();
	    bounds.setUpper(sx/2,sy/2,sz/2);
	    bounds.setLower(-sx/2,-sy/2,-sz/2);
	    setBounds(bounds);
	    
	    setColor(color);
	    addChild(box);
      
    }

}

