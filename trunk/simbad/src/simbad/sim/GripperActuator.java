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
 * $Source: /cvsroot/simbad/src/simbad/sim/GripperActuator.java,v $
 */

package simbad.sim;



import javax.media.j3d.Appearance;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.vecmath.Color3f;

import com.sun.j3d.utils.geometry.Sphere;

/**
 *experimental.
 */
public class GripperActuator extends ActuatorDevice {
    
    GripperActuator(float radius  ) {
        create3D(radius);
    }

    void create3D(float radius) {
        super.create3D(true);
        // body
        if (radius > 0) {
            Color3f color = new Color3f(0.8f, 0.8f, 0.0f);
            Appearance appear = new Appearance();
            appear
                    .setMaterial(new Material(color, black, color, white,
                            100.0f));
            Node node = new Sphere(radius, appear);
            node.setCollidable(false);
            node.setPickable(false);
            addChild(node);
        }
    }
 
}
