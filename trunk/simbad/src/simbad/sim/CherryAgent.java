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
 * $Author: sioulseuguh $ $Date: 2005/04/25 17:54:58 $ $Revision: 1.1 $ $Source: /cvsroot/simbad/src/simbad/sim/CherryAgent.java,v $
 */
package simbad.sim;

import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.Bounds;

import javax.media.j3d.Material;
import javax.media.j3d.Node;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import com.sun.j3d.utils.geometry.Primitive;
import com.sun.j3d.utils.geometry.Sphere;


/** This simple agent can be used for 'pacman' expermiment. See PickCherries Demo.
 */
public class CherryAgent extends SimpleAgent {

    Color3f color;
    
    /**
     * Construct an AppleAgent.
     * @param pos
     * @param name
     */
    public CherryAgent(Vector3d pos, String name, float radius) {
        super(pos, name);
        // to avoid collision indication
        setCanBeTraversed(true);

        this.radius = radius;
        this.height = 2 * radius;
        this.color = new Color3f(0.8f, 0, 0);
      

    }

    /** Create 3D geometry. */
    protected void create3D() {
        Appearance appear = new Appearance();
        
        material.setCapability(Material.ALLOW_COMPONENT_WRITE);
        material.setDiffuseColor(color);
        material.setSpecularColor(black);
        appear.setMaterial(material);
        int flags = Primitive.GEOMETRY_NOT_SHARED
                | Primitive.ENABLE_GEOMETRY_PICKING
                | Primitive.GENERATE_NORMALS;

        body = new Sphere(radius, flags, appear);

        // we must be able to change the pick flag of the agent
        body.setCapability(Node.ALLOW_PICKABLE_READ);
        body.setCapability(Node.ALLOW_PICKABLE_WRITE);
        body.setPickable(true);
        body.setCollidable(true);
        addChild(body);

        // Add bounds for interactions
        Bounds bounds = new BoundingSphere(new Point3d(0, 0, 0), radius);
        setBounds(bounds);

    }

   
}

