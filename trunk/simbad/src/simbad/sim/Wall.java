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
 * $Revision: 1.6 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Wall.java,v $
 * 
 * MODIF - LH 02 oct 2006 - add a constructor with width.
 */
package simbad.sim;


import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;


/**
 * A wall which can be put in the environnement. 
 */
public class Wall extends Box{
    final static  float thickness = 0.3f;
 
    public Wall(Vector3d pos ,float length,float height ,EnvironmentDescription wd) {
        super(pos,new Vector3f(length,height,thickness),wd);
        setColor(wd.wallColor);
    }
    

    public Wall(Vector3d pos ,float length,float width, float height, EnvironmentDescription wd) {
        super(pos,new Vector3f(length,height,width),wd);
        setColor(wd.wallColor);
    }
  }
