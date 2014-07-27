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
 * $Date: 2005/04/25 17:54:58 $
 * $Revision: 1.4 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Arch.java,v $
 */
package simbad.sim;

import javax.vecmath.Vector3f;
import javax.vecmath.Vector3d;


/**
 * An Arch object to put in  the  environement.
 */
public class Arch extends BlockWorldCompositeObject {
    
    public Arch(Vector3d pos,EnvironmentDescription wd) {
        create3D(wd);
        translateTo(pos);
    }
    void create3D(EnvironmentDescription wd){
        super.create3D();
        // Use 3 boxes to construct the arch.
        Box b1 = new Box(new Vector3d(-1.5,0,0),new Vector3f(1,1.5f,1),wd);
        Box b2 = new Box(new Vector3d(1.5,0,0),new Vector3f(1,1.5f,1),wd);
        Box b3 = new Box(new Vector3d(0,1.5f,0),new Vector3f(4,0.5f,1),wd);
        b1.setColor(wd.archColor);
        b2.setColor(wd.archColor);
        b3.setColor(wd.archColor);
        addComponent(b1);
        addComponent(b2);
        addComponent(b3);
    }     
}
