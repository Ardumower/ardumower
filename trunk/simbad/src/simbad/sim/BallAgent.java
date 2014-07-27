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
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/sim/BallAgent.java,v $
 */

package simbad.sim;

import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.Bounds;
import javax.media.j3d.Node;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import com.sun.j3d.utils.geometry.Primitive;
import com.sun.j3d.utils.geometry.Sphere;

/**
 * @author louis
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class BallAgent extends SimpleAgent {

    Color3f color;
    /**
     * @param pos
     * @param name
     */
    public BallAgent(Vector3d pos, String name, Color3f color,float  radius,float mass) {
        super(pos, name);
        this.radius = radius;
        this.height = 2*radius;
        this.mass =mass;
        staticFrictionCoefficient = 0.1f;
        this.color = color;
        
        
    }
    public BallAgent(Vector3d pos, String name,float  radius) {
        this(pos, name, new Color3f(1f,0.2f,0.05f),radius,0.25f);
        
    }

   
    /** Create 3D geometry. */
    protected void create3D(){
         Appearance  appear = new Appearance();
        
        material.setDiffuseColor(color);
        material.setSpecularColor(black);
        appear.setMaterial(material);
        int flags = Primitive.GEOMETRY_NOT_SHARED | Primitive.ENABLE_GEOMETRY_PICKING | Primitive.GENERATE_NORMALS;
        
      
        body = new Sphere(radius,flags,appear);
        
        // we must be able to change the pick flag of the agent 
        body.setCapability(Node.ALLOW_PICKABLE_READ);
        body.setCapability(Node.ALLOW_PICKABLE_WRITE);
        body.setPickable(true);
        body.setCollidable(true);
        addChild(body);
     	    
	    // Add bounds for interactions
	    Bounds bounds = new BoundingSphere(new Point3d(0,0,0),radius);
	    setBounds(bounds);
   
    }

}
