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
 * $Revision: 1.6 $
 * $Source: /cvsroot/simbad/src/simbad/sim/BlockWorldObject.java,v $
 */
package simbad.sim;
import javax.media.j3d.Material;
import javax.vecmath.Color3f;


/**
 * Base Object for all simple block world objects (box,wall.).
 */
public class BlockWorldObject extends StaticObject {
   

 

    /** Set the object color */
    public void setColor(Color3f color){
        Material mat = appearance.getMaterial();
        Color3f ambient = new Color3f(color);
        ambient.scale(0.3f);
        mat.setAmbientColor(ambient);
        color.clampMax(0.8f);
        mat.setDiffuseColor(color);
        // No specular color
        Color3f specular = new Color3f(0,0,0);
        mat.setSpecularColor(specular);
        
        mat.setShininess(1f);
        
    }
    /** Rotates the object counter clockwise. */
    public void rotate90(int ntimes){
        this.rotateY(ntimes*Math.PI/2.0);
    }
    
   
    
}
